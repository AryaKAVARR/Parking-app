#ifndef SDDS_Car
#define SDDS_Car
#include <iostream>
#include "Vehicle.h"

namespace sdds
{
	class Car : public Vehicle
	{
		bool carWash;

	public:
		Car();
		Car(const char* licensePlate, const char* makeModel);

		//copy constructor
		Car(const Car& car);

		
		std::ostream& writeType(std::ostream& onpstr)const;
		
		std::istream& read(std::istream& inpstr = std::cin);
		
		std::ostream& write(std::ostream& onpstr = std::cout)const;
	};

}

#endif // !SDDS_Car
