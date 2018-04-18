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
		strcpy_s(this->line,strlen(rhs.line)+1, rhs.line);

};





///
///setLine function.
///
void Line::setLine(const char* line)
{
	delete[] this->line;
	this->lettersCount=strlen(line);
	this->line = new(std::nothrow) char[lettersCount + 1];
	if (!this->line)throw std::exception("Bad alloc");
	for (unsigned i = 0; i < lettersCount; i++)
	{
		this->line[i] = line[i];
	}
	this->line[lettersCount] = '\0';
}


///
///Make header row
///
void Line::header()
{
	this->lettersCount += 2;
	char * temporary = new (std::nothrow) char[this->lettersCount+1];

	if (!temporary)
	{
		throw std::exception("Bad alloc");
	}
	temporary[0] = '#';
	temporary[1] = ' ';
	temporary += 1;
	strcpy_s(temporary, this->lettersCount, line);
	temporary -= 1;
	temporary[this->lettersCount] = '\0';
	setLine(temporary);
	delete[] temporary;
}


////
///function to make text bold
///
void Line::bold(unsigned from, unsigned to,unsigned count)
{
	unsigned numberOfSymbolsToAdd = countToAdd(from, to, count);
	this->lettersCount += numberOfSymbolsToAdd;
	char * temporary = new (std::nothrow) char[this->lettersCount + 1];
	unsigned wordCurrent = 1;
	unsigned i = 0;
	unsigned j = 0;
	checkAndAddSymbols(temporary, i, j, from, to, wordCurrent, 1, numberOfSymbolsToAdd);
}


///
///make italic
///TO DO CHECK TEMPORARY
void Line::italic(unsigned from, unsigned to, unsigned count)
{
	unsigned numberOfSymbolsToAdd = countToAdd(from, to, count);
	this->lettersCount += numberOfSymbolsToAdd;
	char * temporary = new (std::nothrow) char[this->lettersCount + 1];
	unsigned wordCurrent = 1;
	unsigned i = 0;
	unsigned j = 0;
	//function to add symbols into file
	checkAndAddSymbols(temporary, i, j, from, to, wordCurrent, 2, numberOfSymbolsToAdd);
	//add another symbols
	
}



///Make combine of two
// to do errror from to
void Line::combine(unsigned from, unsigned to, unsigned count)
{
	italic(from, to, count-4);
	bold(from, to,count-2);
}



///
///Helper function ot add symbols to file
///
void Line::checkAndAddSymbols(char* temporary, unsigned &i, unsigned &j, unsigned from,unsigned to,unsigned wordCurrent, unsigned countTimes, unsigned numberOfSymbolsToAdd)
{
	if (line[0]=='#')
	{
		temporary[i++] = line[j++];
		temporary[i++] = ' ';
	}
	while (from <= to)
	{

		if (from == wordCurrent)
		{
			int times = 0;
			do
			{
				temporary[i++] = '*';
				times++;
			} while (times==countTimes);
			times = 0;

			from += 1;
			wordCurrent += 1;
			while (line[j] != ' ' && j < lettersCount - numberOfSymbolsToAdd)
			{
				temporary[i++] = line[j++];
			}
			do
			{
				temporary[i++] = '*';
				times++;
			} while (times == countTimes);

			if (from > to)
			{
				break;
			}
			temporary[i++] = line[j++];
		}
		else
		{
			if (line[j] == ' ')
			{
				wordCurrent += 1;
				while (line[j] == ' ')
				{
					temporary[i++] = line[j++];
				}
			}
			else
			{
				temporary[i++] = line[j++];
			}

		}

	}
	for (unsigned countOfLine = j, countOfTemp = i; countOfLine <(this->lettersCount - numberOfSymbolsToAdd); ++countOfLine)
	{
		temporary[countOfTemp++] = line[countOfLine];
	}	
	temporary[lettersCount] = '\0';
	setLine(temporary);

	delete[] temporary;
}



///
///Function used to count for symbols to add
///
unsigned Line::countToAdd(unsigned from, unsigned to, unsigned count)
{
	int currentLetters = 0;
	int countOfSymbolsToAdd = 0;
	int wordCurrent = 1;
	while (from <= to)
	{
		if (from == wordCurrent)
		{
			if (line[currentLetters] != '*' && line[currentLetters+1] !='*' && line[currentLetters+2] != '*')
			{
				countOfSymbolsToAdd += count;
				wordCurrent += 1;
				from += 1;
			}

			while (line[currentLetters] != ' ' && currentLetters<lettersCount)
			{
				currentLetters++;
			}
			currentLetters += 1;
		}
		else
		{
			currentLetters += 1;
			while (line[currentLetters] != ' ' && currentLetters<lettersCount)
			{
				currentLetters++;
			}
			wordCurrent += 1;
		}
	}
	return countOfSymbolsToAdd;
}


///
///Function to add italic and bold
///


