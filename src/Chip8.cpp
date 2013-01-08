#include "Chip8.h"
#include <sstream>

#define MEMORY_SIZE 0x1000
#define ROM_OFFSET 0x200
#define ROM_LEN 0x1000-ROM_OFFSET


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
	static unsigned char RAM[MEMORY_SIZE]; 	


	//methods
	std::string getCPUStatus(){
		std::stringstream stream;

		stream << "Test";

		return stream.str();
	}

	bool shouldDraw(){ return true; }

	void step(){

		Opcode o(RAM[ROM_OFFSET], RAM[ROM_OFFSET + 1]);


			
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

}
