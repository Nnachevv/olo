#include "Line.h"
#include <iostream>


///
///Default constructor
///
Line::Line():line(nullptr),lettersCount(0)
{

}


///
///Destructor
///
Line::~Line()
{
	delete[] line;
}


///
///Coppy constructor
///
Line::Line(const Line & rhs)
{
	copy(rhs);
}


///
///Operator = construct
///
Line & Line::operator=(const Line & rhs)
{
	if (this != &rhs)
	{
		delete[] line;
		line = nullptr;
		copy(rhs);
	}
	return *this;
}



///
///Copy function
///
void Line::copy(const Line & rhs)
{
	delete[] this->line;
	if (!rhs.line) throw std::exception("Bad alloc");
	this->line = new char[strlen(rhs.line) + 1];
	//Maybe error
	strcpy_s(this->line,strlen(rhs.line)+1, rhs.line);

};



///
///Read how many letter have line
///
void Line::readCountOfLine(std::ifstream & file)
{
	char character = 'n';
	//reading characters
	while (!file.eof())
	{
		file.get(character);
		if (file.eof())break;
		if (!file) 
		{
			//TO DO: FILE CLOSE CLEAR
			throw std::exception("Error open file");
		}
		if ('\n' == character)
			break;
		++lettersCount;
	}
	setLine();
}


///
///setLine function.
///
void Line::setLine()
{
	delete[] this->line;
	this->line = new(std::nothrow) char[lettersCount + 1];
	if (!line)throw std::exception("Bad alloc");
}


///
///Read all letters in current line
///
void Line::readLetters(std::ifstream & file)
{
	char ch = ' ';
	for (unsigned i = 0; i < this->lettersCount; i++)
	{
		file.get(ch);
		if (ch == '\n')
		{
			file.get(ch);
		}
		this->line[i] = ch;
		if (!file)throw std::exception("Error with file");;
	}
	this->line[lettersCount] = '\0';
}


///
///Make header row
///
void Line::header()
{
		this->lettersCount += 1;
	char * temporary = new (std::nothrow) char[this->lettersCount + 1];

	if (!temporary)
	{
		throw std::exception("Bad alloc");
	}
	
	temporary[0] = '#';
	temporary += 1;
	strcpy_s(temporary, lettersCount, line);
	temporary -= 1;

	temporary[this->lettersCount] = '\0';

	setLine();
	strcpy_s(line, lettersCount+1, temporary);
	line[this->lettersCount] = '\0';
	
	delete[] temporary;
}




