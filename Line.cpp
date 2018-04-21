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
	*temporary = '#';
	temporary += 1;
	*temporary = ' ';
	temporary += 1;
	strcpy_s(temporary, this->lettersCount-1, line);
	temporary -= 2;
	setLine(temporary);
	temporary[this->lettersCount] = '\0';
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
	checkAndAddSymbols(temporary, i, j, from, to, wordCurrent, count, numberOfSymbolsToAdd);
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
	checkAndAddSymbols(temporary, i, j, from, to, wordCurrent, count, numberOfSymbolsToAdd);
	//add another symbols
	
}



///
///Function to add italic and bold
///
void Line::combine(unsigned from, unsigned to, unsigned count)
{
	italic(from, to, 2);
	bold(from, to,4);
}


//To do bold
int Line::checkHowMuchSymbolsToAdd(unsigned currentLetters, unsigned countToAdd, char * line)
{
	if (line[currentLetters] == '*')
	{

		int numberTimesSeen = 0;
		++numberTimesSeen;
		while (line[++currentLetters] == '*')
		{
			++numberTimesSeen;
		}
		if ((countToAdd == 2) && numberTimesSeen == 2)
		{
			return 2;
		}
		else if ((countToAdd == 2) && numberTimesSeen == 1)
		{
			return 0;
		}
		else if ((countToAdd == 4) && numberTimesSeen == 2)
		{
			return 0;
		}
		else if ((countToAdd == 4) && numberTimesSeen == 1)
		{
			return  4;
		}
		else {
			return 0;
		}
	//	countOfSymbolsToAdd += checkHowMuchSymbolsToAdd(currentLetters, count, line);

	}
	else
	{
		return countToAdd;
	}
	

	
}

///
///Helper function ot add symbols to file
///
void Line::checkAndAddSymbols(char* temporary, unsigned &i, unsigned &j, unsigned from,unsigned to,unsigned wordCurrent, unsigned countTimes, unsigned numberOfSymbolsToAdd)
{
	//escapingHeader symbols
	if (line[0]=='#')
	{
		while ((line[i] == ' ' )||( line[i] =='#'))
		{
			temporary[i++] = line[j++];
		}
		
	}
	while (from <= to)
	{

		if (from == wordCurrent)
		{
			int times = 0;
			unsigned symbolsToAdd = countTimes/2;
			if (line[j]=='*')
			{
				symbolsToAdd = checkHowMuchSymbolsToAdd(j, countTimes, line);
				symbolsToAdd /= 2;
			}
			
			for (unsigned k = 0; k < symbolsToAdd; k++)
			{
				temporary[i++] = '*';
			}

			from += 1;
			wordCurrent += 1;
			while (line[j] != ' ' && j < lettersCount - numberOfSymbolsToAdd)
			{
				temporary[i++] = line[j++];
			}
			for (unsigned k = 0; k < symbolsToAdd; k++)
			{
				temporary[i++] = '*';
			}

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
				temporary[i++] = line[j++];
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
	
	unsigned currentLetters = 0;
	unsigned countOfSymbolsToAdd = 0;
	unsigned wordCurrent = 0;
	///Escaping first letters
	if (line[currentLetters] != '#' && line[currentLetters] != ' ')
	{
		++wordCurrent;
		if (from==wordCurrent)
		{
			countOfSymbolsToAdd += checkHowMuchSymbolsToAdd(currentLetters, count, line);
			++from;
			++wordCurrent;
		}
		else
		{
			while (line[currentLetters] != ' ')
			{
				currentLetters++;
			}
		}
	}
	while (from <= to)
	{
		///checking if had occurence
		if (from == wordCurrent)
		{
			countOfSymbolsToAdd += checkHowMuchSymbolsToAdd(currentLetters, count, line);
			++from;
			++wordCurrent;
			while (line[currentLetters] != ' ' && currentLetters<lettersCount)
			{
				currentLetters++;
			}
			currentLetters += 1;
			continue;
		}
		else
		{
			while (line[currentLetters] != ' ' && currentLetters<lettersCount)
			{
				currentLetters++;
			}
		}

		if (line[currentLetters]=='#' || line[currentLetters] ==' ')
		{
			currentLetters++;
			while (line[currentLetters] == '#' || line[currentLetters] == ' ')
			{
				++currentLetters;
			}
			if (currentLetters>lettersCount)
			{
				break;
			}			
			++wordCurrent;

			continue;
		}
		
	
		
	}
	return countOfSymbolsToAdd;
}




