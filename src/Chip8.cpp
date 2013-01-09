#include "Chip8.h"
#include "IllegalOpcodeException.h"
#include <sstream>
#include <functional>

#define RAM_SIZE 0x1000
#define ROM_OFFSET 0x200
#define ROM_LEN 0x1000-ROM_OFFSET
#define NUM_REGISTERS 16
#define NUM_OPCODE_FUNCTIONS 16
#define STACK_SIZE 16


namespace Chip8{

	//represents an opcode.  easily access each nibble from the nibbles field
	//access each byte from bytes field
	union Opcode{ 
		
		//holds each nibble of the opcode
		struct {
			unsigned char n1:4;
			unsigned char n2:4;
			unsigned char n3:4;
			unsigned char n4:4;
		} nibbles; 
		
		struct{
			unsigned char lowByte;
			unsigned char highByte;
		
		} bytes;
		
		unsigned short fullOpcode; //full 2-byte opcode

		Opcode(unsigned char highByte, unsigned char lowByte)
		{
			fullOpcode = 0;
			fullOpcode |= static_cast<unsigned short>(highByte) << 8;
			fullOpcode |= lowByte;
		}
		
	};
	
	//globals
	
	/*
	   holds opccode functions. There are 16 indecies of opcode functions 
	   each index holds the series of opcode functions based on the opcodes' 
	   most signifcicant  nibble.

	   Example--  Index 0xE will contain a function that can do the 'EX9E' or 'EXA1' instructions

	 */	   
	static std::function<void (Opcode)> opcodeFunctions[NUM_OPCODE_FUNCTIONS]; 
	static unsigned char RAM[RAM_SIZE]; 	
	static unsigned char V[NUM_REGISTERS]; //scratch registers
	static unsigned short stack[STACK_SIZE]; //used to keep track of calling addrs
	static unsigned char I; //index register
	static unsigned short PC; //program counter register
	static unsigned char SP;  //stack pointer


	//methods
	std::string getCPUStatus(){
		std::stringstream stream;

		stream << "Scratch Registers: ";

		for(int i = 0; i < NUM_REGISTERS; i++){
			stream  << "\tV" << i << ": "<< static_cast<int>(V[i]);
		}

		stream << "\n PC: " << PC << "  I: " << I;

		return stream.str();
	}

	bool shouldDraw(){ return true; }

	void step(){

		unsigned short currentPC = PC;

		Opcode o(RAM[PC], RAM[PC + 1]);

		opcodeFunctions[o.nibbles.n4](o);

		if(currentPC == PC)
			PC += 2;

			
	}

	void updateKeys(){
	}	


	//loads game into ram
	void loadGame(char *fileName){

		FILE *f;

		if((f = fopen(fileName, "r")) == NULL){
			throw Chip8Exception("Cannot open file");
		}

		fread(RAM + ROM_OFFSET, ROM_LEN, 1, f);

		fclose(f);



	}

	static void initOpcodeFunctions(){
		opcodeFunctions[0] =
			[&](Opcode o){ 
				switch(o.bytes.highByte){
					case 0:
						switch(o.bytes.lowByte){
							case 0xE0: //clear screen
								//todo
								break;
							case 0xEE: //return from subroutine
								PC = stack[--SP];
								break;
							default:
								throw IllegalOpcodeException(o.fullOpcode);
						}
						break;
					default:
						throw IllegalOpcodeException(o.fullOpcode);
				}
			};

		opcodeFunctions[1] = [&](Opcode o){ //set PC to address
			unsigned short address = 0;
			address |= static_cast<unsigned short>(o.nibbles.n3) << 8; 
			address |= static_cast<unsigned short>(o.nibbles.n2) << 4; 
			address |= o.nibbles.n1;
		       	PC = address;	
		};

		opcodeFunctions[2] = [&](Opcode o){ //call subroutine
			stack[SP++] = PC + 2;
			opcodeFunctions[1](o);

		};

		opcodeFunctions[3] = [&](Opcode o){ //skip instruction if VX == NN
			if(V[o.nibbles.n3] == o.bytes.lowByte) PC += 2;
		};

		opcodeFunctions[4] = [&](Opcode o){ //skip instruction if VX != NN
			if(V[o.nibbles.n3] != o.bytes.lowByte) PC += 2;
		};

		opcodeFunctions[5] = [&](Opcode o){ //skip instruction if VX == VY
			if(o.nibbles.n1 != 0) 	throw IllegalOpcodeException(o.fullOpcode);
 
			if(V[o.nibbles.n3] == V[o.nibbles.n2]) PC += 2;
		};
		
		opcodeFunctions[6] = [&](Opcode o){ //set VX to NN
			V[o.nibbles.n3] = o.bytes.lowByte;
		};
		
		opcodeFunctions[7] = [&](Opcode o){ //add NN to VX
			V[o.nibbles.n3] += o.bytes.lowByte;
		};


		opcodeFunctions[8] = [&](Opcode o){ //set VX to NN
			switch(o.nibbles.n1){
				case 0: //set VX to VY
					V[o.nibbles.n3] = V[o.nibbles.n2];
					break;
				case 1: //set VX |= VY
					V[o.nibbles.n3] |= V[o.nibbles.n2];
					break;
				case 2: //set VX &= VY
					V[o.nibbles.n3] &= V[o.nibbles.n2];
					break;
				case 3: //set VX ^= VY
					V[o.nibbles.n3] ^= V[o.nibbles.n2];
					break;
				case 4: // add VY to VX.  Set carry flag if neccessary
					V[0xF] = (static_cast<unsigned int>(V[o.nibbles.n3]) + static_cast<unsigned int>(V[o.nibbles.n2])) >> 8;
					V[o.nibbles.n3] += V[o.nibbles.n2];
					break;
				case 5: // subtract VY from VX.  Set carry flag if neccessary
					V[0xF] = (static_cast<unsigned int>(V[o.nibbles.n3]) - static_cast<unsigned int>(V[o.nibbles.n2])) >> 8;
					V[o.nibbles.n3] -= V[o.nibbles.n2];
					break;
				case 6: //shift VX to right by 1. set VF to least sig bit
					V[0xF] = V[o.nibbles.n3] & 1;
					V[o.nibbles.n3] >> 1;
					break;

				case 7: //set VX = VY - VX.  Set carry flag if neccessary
					V[0xF] = (static_cast<unsigned int>(V[o.nibbles.n2]) - static_cast<unsigned int>(V[o.nibbles.n3])) >> 8;
					V[o.nibbles.n3] = V[o.nibbles.n2] - V[o.nibbles.n3];
					break;
				case 0xE: //shift VX to left by 1. set VF to most sig bit
					V[0xF] = V[o.nibbles.n3] & 0x80;
					V[o.nibbles.n3] << 1;
					break;
				default:
					throw IllegalOpcodeException(o.fullOpcode);
			}
		};
		
		opcodeFunctions[9] = [&](Opcode o){ //skip instruction if VX != VY
			if(o.nibbles.n1 != 0) 	throw IllegalOpcodeException(o.fullOpcode);
 
			if(V[o.nibbles.n3] != V[o.nibbles.n2]) PC += 2;
		};
		
		opcodeFunctions[0xA] = [&](Opcode o){ //set I to NNN
			unsigned short address = 0;
			address |= static_cast<unsigned short>(o.nibbles.n3) << 8; 
			address |= static_cast<unsigned short>(o.nibbles.n2) << 4; 
			address |= o.nibbles.n1;
		       	I = address;	
		};

		opcodeFunctions[0xB] = [&](Opcode o){ //set PC to NNN + V0
			unsigned short address = 0;
			address |= static_cast<unsigned short>(o.nibbles.n3) << 8; 
			address |= static_cast<unsigned short>(o.nibbles.n2) << 4; 
			address |= o.nibbles.n1;
		       	PC = address + V[0];	
		};


	}

	//clears memory, sets registers appropriately, 
	//initializes the opcode functions arrray and loads font set
	void init(){

		memset(RAM, 0, RAM_SIZE);
		memset(V, 0, NUM_REGISTERS);
		SP = 0;
		PC = ROM_OFFSET;
		initOpcodeFunctions();


	}

}
