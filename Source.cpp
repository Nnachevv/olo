#include "TextTransformator.h"
int main()
{
	char buffer[255];
	std::cout << "Enter file path :" << std::endl;
	std::cin >> buffer;
	TextTransformator textTransformator(buffer);
	char inputBuffer[40];
	do
	{
		std::cout << "Enter input: makeHeading | makeItalic | makeBold | makeCombine | addLine | remove | quit"<<std::endl;
	
		std::cin >> inputBuffer;
		if (strcmp(inputBuffer, "makeHeading")==0)
		{
			std::cout << "Enter row to change" << std::endl;
			unsigned row;
			std::cin >> row;
			textTransformator.makeHeading(row);
		}
		else if (strcmp(inputBuffer, "makeItalic")==0)
		{
			std::cout << "Enter row, from and to change." << std::endl;
			unsigned row, from, to;
			std::cin >> row >> from >> to;
			textTransformator.makeItalic(row, from, to);
		}
		else if (strcmp(inputBuffer, "makeBold")==0)
		{
			std::cout << "Enter row, from and to change." << std::endl;
			unsigned row, from, to;
			std::cin >> row >> from >> to;
			textTransformator.makeBold(row, from, to);
		}
		else if (strcmp(inputBuffer, "makeCombine")==0)
		{
			std::cout << "Enter row, from and to change." << std::endl;
			unsigned row, from, to;
			std::cin >> row >> from >> to;
			textTransformator.makeCombine(row, from, to);
		}
		else if (strcmp(inputBuffer, "addLine")==0)
		{
			std::cout << "Enter line to add"<<std::endl;
			char lineBuffer[1024];
			textTransformator.addLine(lineBuffer);
		}
		else if (strcmp(inputBuffer, "remove")==0)
		{
			std::cout << "Enter line to remove" << std::endl;
			int lineNumber;
			std::cin >> lineNumber;
			textTransformator.removeLine(lineNumber);
		}
		else if (strcmp(inputBuffer, "quit")==0)
		{
			break;
		}
	} while (inputBuffer != "quit");

	
	
	
	
	
	
	

}