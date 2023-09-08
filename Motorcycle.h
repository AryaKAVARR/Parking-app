#ifndef SDDS_Motorcycle
#define SDDS_Motorcycle
#include <iostream>
#include "Vehicle.h"

namespace sdds
{
	class Motorcycle : public Vehicle
	{
		bool hasSideCar;

	public:
		Motorcycle();
		Motorcycle(const char* licensePlate, const char* makeModel);

		//Copy constructor
		Motorcycle(const Motorcycle& motor);

		//Destructor
		~Motorcycle();

		std::ostream& writeType(std::ostream& onpstr)const;
		
		std::istream& read(std::istream& inpstr = std::cin);
	
		std::ostream& write(std::ostream& onpstr = std::cout)const;
	};
}

#endif // !SDDS_Motorcycle
