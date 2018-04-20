#ifndef HEADER_LINE_INCLUDED
#define HEADER_LINE_INCLUDED

#include <iostream>
#include <fstream>
class Line
{
public:
	Line();
	~Line();
	Line(const Line & rhs);
	Line & operator=(const Line & rhs);
	
private:
	char* line;
	unsigned lettersCount;

private:
	void copy(const Line &rhs);
public:

	void setLine(const char* line);
	const char* getLine()const { return this->line; };

public:
	void header();
	void bold(unsigned from, unsigned to,unsigned count );
	void italic(unsigned from, unsigned to, unsigned count);
	void combine(unsigned from, unsigned to, unsigned count);

private:
	int checkHowMuchSymbolsToAdd(unsigned start,unsigned count,char *line);
	void checkAndAddSymbols(char* temporary, unsigned &i, unsigned &j, unsigned from, unsigned to, unsigned wordCurrent, unsigned countTimes, unsigned numberOfSymbolsToAdd);///function to add
	unsigned countToAdd(unsigned from, unsigned to, unsigned countToAdd);

};
#endif // !HEADER_LINE_INCLUDED
