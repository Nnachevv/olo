#include "TextTransformator.h"


///
///Constructor with file location parameter.
///
TextTransformator::TextTransformator(const char filePath[255]):lines(nullptr),numberOfLines(0)
{
	openFile(filePath);
	getNumberOfLines();
	setLine(numberOfLines);
}


///
/// Destructor
///
TextTransformator::~TextTransformator()
{

	delete[] this->lines;
}


///
///Copy constructor
///
TextTransformator::TextTransformator(const TextTransformator & rhs)
{
	copy(rhs);
}


///
///Operator= constructor
///
TextTransformator & TextTransformator::operator=(const TextTransformator & rhs)
{
	if (this != &rhs)
	{
		delete[] lines;
		lines = nullptr;
		copy(rhs);
	}
	return *this;
}
;


///
///Copy function
///
void TextTransformator::copy(const TextTransformator & rhs)
{
	delete[] this->lines;
	if (!rhs.lines) throw "Bad alloc";
	this->lines = new Line[rhs.numberOfLines];
	*lines = *rhs.lines;
}


///
///Adding Line to textTransformator TO DO...
///
void TextTransformator::addLine(const char * lineContent)
{
	numberOfLines += 1;
	fileReset();
	setLine(numberOfLines);
	//lines[numberOfLines]. TO DO.

}

void TextTransformator::removeLine(unsigned number)
{
}


///
///Open file.Throw exception if cant open file.
///
void TextTransformator::openFile(const char filePath[255])
{
	file.open(filePath, std::ios::in);
	if (!file)
	{
		delete[] lines;
	}
}


///
///Geting lines in file
///
void TextTransformator::getNumberOfLines()
{
	char character = 'n';
	while (!file.eof())
	{
		file.get(character);
		if (file.eof())break;
		if (!file)
		{
			fileReset();
			throw std::exception("Cant read file");
		}

		if ('\n' == character)
			++this->numberOfLines;
	}
	//Reset position in pointer in file
	fileReset();
}


///
///Reset file position.
///
void TextTransformator::fileReset()
{
	file.clear();
	file.seekg(0, std::ios::beg);
}


///
///Close file
///
void TextTransformator::fileClose()
{
	file.clear();
	file.close();
}



///
///Set number of lines in file.
///
void TextTransformator::setLine(unsigned numberOfLines)
{
	lines = new (std::nothrow) Line[numberOfLines];
	if(!lines)
	{
		throw std::exception("Bad alloc");
	}
	readLines(numberOfLines);
}


///
///Reading lines.
///
void TextTransformator::readLines(unsigned numberOfLines)
{
	for (unsigned i = 0; i < numberOfLines; i++)
	{
		lines[i].readCountOfLine(file);
	}
	fileReset();
	for (unsigned i = 0; i < numberOfLines; i++)
	{
		lines[i].readLetters(file);
	}
	//closing file
	fileClose();
}




