#include "Chip8Exception.h"
#include <sstream>
class IllegalOpcodeException : public Chip8Exception{

	public:
		IllegalOpcodeException(unsigned short opcode)
			:Chip8Exception("")
		{


			std::stringstream stream;

			stream << "Illegal Opcode: " << opcode;

			message = stream.str();

		}
};
