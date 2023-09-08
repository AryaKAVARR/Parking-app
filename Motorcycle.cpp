/* Citation and Sources...

Final Project Milestone 5

Module: Motorcycle.h
Filename: Motorcycle.cpp

Version 1.0
Name: Arya Rajeshbhai Kaavar
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#include <cstring>
#include "Motorcycle.h"

using namespace std;

namespace sdds
{
	Motorcycle::Motorcycle() : Vehicle()
	{
		this->hasSideCar = false;
	}

	Motorcycle::Motorcycle(const char* licensePlate, const char* makeModel) : Vehicle(licensePlate, makeModel)
	{
		if (licensePlate == nullptr || licensePlate[0] == '\0' || makeModel == nullptr || makeModel[0] == '\0')
		{
			this->setEmpty();
			this->hasSideCar = false;
		}
	}

	Motorcycle::Motorcycle(const Motorcycle& motor) : Vehicle(motor)
	{
		this->hasSideCar = motor.hasSideCar;
	}

	Motorcycle::~Motorcycle()
	{
		this->hasSideCar = false;
	}

	std::ostream& Motorcycle::writeType(std::ostream& onpstr) const
	{
		if (this->isCsv())
			onpstr << "M,";
		else
			onpstr << "Vehicle type: Motorcycle" << endl;

		return onpstr;
	}

	std::istream& Motorcycle::read(std::istream& inpstr)
	{
		char options[3]{};

		if (this->isCsv())
		{
			Vehicle::read(inpstr);
			inpstr >> this->hasSideCar;
			inpstr.ignore(1000, '\n');
		}
		else
		{
			cout << endl << "Motorcycle information entry" << endl;
			Vehicle::read(inpstr);
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			do
			{
				inpstr >> options;
				inpstr.ignore(1000, '\n');

				int Length = strlen(options);
				if (Length > 1)
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
				else if (toupper(options[0]) == 'Y')
				{
					this->hasSideCar = true;
					break;
				}
				else if (toupper(options[0]) == 'N')
				{
					this->hasSideCar = false;
					break;
				}
				else
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}

			} while (1);
		}

		return inpstr;
	}

	std::ostream& Motorcycle::write(std::ostream& onpstr) const
	{
		if (this->isEmpty())
		{
			onpstr << "Invalid Motorcycle Object" << endl;
		}
		else
		{
			Vehicle::write(onpstr);
			if (this->isCsv())
				onpstr << this->hasSideCar << endl;
			else
			{
				if (this->hasSideCar)
					onpstr << "With Sidecar" << endl;
			}
		}

		return onpstr;
	}

}