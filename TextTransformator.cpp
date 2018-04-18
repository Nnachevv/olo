#include "TextTransformator.h"


///
///Constructor with file location parameter.
///
TextTransformator::TextTransformator(const char filePath[255]):lines(nullptr),numberOfLines(0),filePath(filePath)
{
	openFile(filePath);
	getNumberOfLines();
	setAllLines(numberOfLines);
	readLine(numberOfLines);
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
///Open file.Throw exception if cant open file.
///TO DO THROW EXCEPTION
void TextTransformator::openFile(const char filePath[255])
{
	file.open(filePath, std::ios::in);
	if (!file)
	{
		delete[] lines;
	}
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
void TextTransformator::setAllLines(unsigned numberOfLines)
{
	lines = new (std::nothrow) Line[numberOfLines];
	if (!lines)
	{
		throw std::exception("Bad alloc");
	}
}


///
///Geting number of lines in file
///
void TextTransformator::getNumberOfLines()
{
	char character = 'n';
	char buffer[1024];
	while (!file.eof())
	{
		file.getline(buffer,1024);		
		if (file.eof())
		{
			break;
		}
		if (!file)
		{
			fileReset();
			throw std::exception("Cant read file");
		}

			++this->numberOfLines;
	}
	//Reset position in pointer in file
	fileReset();
}


///
///Reading Line and creating
///
void TextTransformator::readLine(unsigned numberOfLines)
{
	for (unsigned i = 0; i < numberOfLines; i++)
	{
		int lettersCount = 0;
		char buffer[1024];
		char character = 'n';
		//reading characters
		file.getline(buffer,1024);
		if (!file)
		{
			fileClose();
			throw std::exception("Error open file");
		}
		if (!file.eof())
		{
			lines[i].setLine(buffer);
		}
		
	}
}



///
///Saving to txt file to save changes
///To DO FILE CATCH ERRORS;
void TextTransformator::saveToTxtFile()
{
	std::ofstream saveFile;
	saveFile.open(filePath, std::ios::out);
	for (unsigned i = 0; i < numberOfLines; i++)
	{
		saveFile << lines[i].getLine();
		saveFile << '\n';
	}
	saveFile.clear();
	saveFile.close();

}


///
///Make a header line in program
////
void TextTransformator::makeHeading(unsigned line)
{
	this->lines[line - 1].header();
	saveToTxtFile();
}

///
///Adding Line to textTransformator TO DO...
///
void TextTransformator::addLine(const char * lineContent)
{
	numberOfLines += 1;
	fileReset();
	setAllLines(numberOfLines);
	readLine(numberOfLines - 1);
	lines[numberOfLines-1].setLine(lineContent);
	saveToTxtFile();

}


///
//Remove line in textTransformator
///
void TextTransformator::removeLine(unsigned row)
{
	row -= 1;
	if (row<0 || numberOfLines<row)throw ;//to do
	for (unsigned i = row; i < numberOfLines-1; i++)
	{
		lines[i].setLine(lines[i+1].getLine());
	}
	numberOfLines -= 1;
	saveToTxtFile();
	fileReset();
	setAllLines(numberOfLines);
	readLine(numberOfLines);
}



///
//Make given  words in line bold
///
void TextTransformator::makeBold(unsigned row, unsigned from, unsigned to)
{
	row -= 1;;
	lines[row].bold(from,to,4);
	saveToTxtFile();

}

void TextTransformator::makeItalic(unsigned row, unsigned from, unsigned to)
{
	row -= 1;;
	lines[row].italic(from, to, 2);
	saveToTxtFile();
}

void TextTransformator::makeCombine(unsigned row, unsigned from, unsigned to)
{
	row -= 1;;
	lines[row].combine(from, to, 6);
	saveToTxtFile();
}






