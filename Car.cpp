/* Citation and Sources...

Final Project Milestone 5

Module: Car.h
Filename: Car.cpp

Version 1.0
Name: Arya Rajesbhai Kavar
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#include "Car.h"
#include <cstring>
#include <string>

using namespace std;

namespace sdds {

	Car::Car() : Vehicle()
	{
		this->carWash = false;
	}

	Car::Car(const char* licensePlate, const char* makeModel) : Vehicle(licensePlate, makeModel)
	{
		if (licensePlate == nullptr || licensePlate[0] == '\0' || makeModel == nullptr || makeModel[0] == '\0')
		{
			this->setEmpty();
			this->carWash = false;
		}
	}

	Car::Car(const Car& car) : Vehicle(car)
	{
		this->carWash = car.carWash;
	}

	std::ostream& Car::writeType(std::ostream& onpstr) const
	{
		if (this->isCsv())
			onpstr << "C,";
		else
			onpstr << "Vehicle type: Car" << endl;

		return onpstr;
	}

	std::istream& Car::read(std::istream& inpstr)
	{
		char choice[3];

		if (this->isCsv())
		{
			Vehicle::read(inpstr);
			inpstr >> this->carWash;
			inpstr.ignore(1000, '\n');
		}
		else
		{
			cout << endl << "Car information entry" << endl;
			Vehicle::read(inpstr);
			cout << "Carwash while parked? (Y)es/(N)o: ";
			do
			{
				inpstr >> choice;
				inpstr.ignore(1000, '\n');

				int Length = strlen(choice);
				if (Length > 1)
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
				else if (toupper(choice[0]) == 'Y')
				{
					this->carWash = true;
					break;
				}
				else if (toupper(choice[0]) == 'N')
				{
					this->carWash = false;
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

	std::ostream& Car::write(std::ostream& onpstr) const
	{
		if (this->isEmpty())
		{
			onpstr << "Invalid Car Object" << endl;;
		}
		else
		{
			Vehicle::write(onpstr);
			if (this->isCsv())
			{
				onpstr << this->carWash << endl;
			}
			else
			{
				if (this->carWash)
					onpstr << "With Carwash" << endl;
				else
					onpstr << "Without Carwash" << endl;
			}
		}

		return onpstr;
	}
}