#ifndef SDDS_Parking
#define SDDS_Parking
#include <iostream>
#include "Menu.h"
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"

using namespace std;

namespace sdds
{
	const int MAX_PARKING_SPOT = 100;

	class Parking
	{
		Menu menu{};
		Menu menu1{};

		Vehicle* vh[MAX_PARKING_SPOT]{};
		int numOfSpots{};

		char* fileName{};
		char selection[51]{};

		//Private member function
		bool isEmpty()const;

		//Parking Status function
		void status()const;

		//Parking vehicle functions
		void parkVehicle();

		//Returning the vehicle
		void returnVehicle();

		//Listing the parked vehicle
		void listParkedVehicle()const;

		//Finding a vehicle
		void findVehicle()const;

		//Close parking function
		bool closeParking();

		//Exit program
		bool exitProgram()const;

		void saveDataFile()const;

	public:
		//Constructor
		Parking();
		Parking(const char* cstr,int noOfSpots);

		//Destructor
		~Parking();
		
		//Load data file function
		bool loadData();

		//Copy and assignment function
		Parking(const Parking&) = delete;
		void operator=(const Parking&) = delete;

		//Run function
		int run();

		//Set empty
		void setEmpty();

		//Return empty spot position to the user
		int returnPos()const;

		//Pause
		void pause()const;
		
	};
}

#endif 
