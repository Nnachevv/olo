#include "TextTransformator.h"
int main()
{
	char buffer[255];
	std::cout << "Enter file path" << std::endl;
	std::cin >> buffer;
	TextTransformator textTransformator(buffer);
	std::cout << "Enter input";
	textTransformator.makeHeading(2);
	//textTransformator.makeItalic(2, 1, 3);
	

}