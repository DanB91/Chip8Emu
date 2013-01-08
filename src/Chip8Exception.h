#pragma once
#include <exception>
#include <string>

class Chip8Exception : public std::exception{

	public:
		Chip8Exception(std::string msg)
			: message(msg)
		{
		}

		const char *what() const throw(){

			return message.c_str();
		}

	protected:

		std::string message;
};

