#include "fd.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char * FileDescriptor::GetFileName()
{
	return file;
}

bool FileDescriptor::IsOpen()
{
	return (fp != NULL);
}

char * FileDescriptor::GetCurrLine()
{
	if (!feof(fp)) {
		if (fgets(buffer, buf_size, fp) == NULL)return NULL;
	}
	else {
		return NULL;
	}
	line_number++;
	char_number = 0;
	currentBufferLength = 0;

	for (int i = 0; buffer[i]!= '\n'; i++) {
		currentBufferLength++;
	}
	
	//cout << buffer << currentBufferLength;
	return buffer;
}

int FileDescriptor::GetLineNum()
{
	return line_number;
}

int FileDescriptor::GetCharNum()
{
	return char_number;
}

FileDescriptor::FileDescriptor(char * FileName)
{
	////store file name
	file = FileName;
	//initaialize buffer size
	buf_size = BUFFER_SIZE;
	buffer = new char[buf_size];
	//////initialize line number
	line_number = 0;
	char_number = 0;

	fp = fopen(FileName, "r");
	//

	if (fp == NULL) perror("Error opening file");
	
}

FileDescriptor::~FileDescriptor()
{
	fclose(fp);
}

void FileDescriptor::Close()
{
	fclose(fp);
}

char FileDescriptor::GetChar()
{
	if(char_number < currentBufferLength)
		return buffer[char_number++];
	return NULL;
}

void FileDescriptor::ReportError(char * msg)
{
	cout << msg;
	cout << "on line " << GetLineNum()<< "of prog.COMP2016" << endl;
}

void FileDescriptor::unGetChar(char c)
{
	char_number--;
}
