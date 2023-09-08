/* Citation and Sources...

Final Project Milestone 5

Module: ReadWritable.h
Filename: ReadWritable.cpp

Version 1.0
Name: Arya Rajeshbhai Kavar
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include "ReadWritable.h"

using namespace std;

namespace sdds
{

	ReadWritable::ReadWritable()
	{
		this->commaSeparated = false;
	}

	bool ReadWritable::isCsv() const
	{
		return this->commaSeparated;
	}

	void ReadWritable::setCsv(bool value)
	{
		this->commaSeparated = value;
	}

	std::ostream& operator<<(std::ostream& onpstr, const ReadWritable& ReadWrite)
	{
		return ReadWrite.write(onpstr);
	}

	std::istream& operator>>(std::istream& inpstr, ReadWritable& ReadWrite)
	{
		return ReadWrite.read(inpstr);
	}
};