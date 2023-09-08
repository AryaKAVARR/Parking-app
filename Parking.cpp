/* Citation and Sources...

Final Project Milestone 5

Module: Parking.h
Filename: Parking.cpp

Version 1.0
Name: Arya Rajeshbhai Kavar
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Menu.h"
#include "Parking.h"
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

namespace sdds
{
	Parking::Parking()
	{
		this->setEmpty();
		for (int i = 0; i < this->numOfSpots; i++)
		{
			this->vh[i] = nullptr;
		}
	}

	Parking::Parking(const char* cstr,int noOfSpots)
	{
		if (cstr == nullptr || cstr[0] == '\0' || noOfSpots > MAX_PARKING_SPOT || noOfSpots < 10)
		{
			int i;
			this->setEmpty();
			for ( i = 0; i < this->numOfSpots; i++)
			{
				this->vh[i] = nullptr;
			}
			cout << "Error in data file" << endl;
		}
		else
		{
			this->fileName = new char[strlen(cstr) + 1];
			strcpy(this->fileName, cstr);
			this->numOfSpots = noOfSpots;

			if (this->loadData() == false)
			{
				cout << "Error in data file" << endl;
			}
			else
			{
				this->menu = "Parking Menu, select an action:";
				this->menu.add("Park Vehicle");
				this->menu.add("Return Vehicle");
				this->menu.add("List Parked Vehicles");
				this->menu.add("Find Vehicle");
				this->menu.add("Close Parking (End of day)");
				this->menu.add("Exit Program");
				this->menu.indent = 0;

				this->menu1 = "Select type of the vehicle:";
				this->menu1.add("Car");
				this->menu1.add("Motorcycle");
				this->menu1.add("Cancel");
				this->menu1.indent = 1;
			}
		}
	}

	Parking::~Parking()
	{
		this->saveDataFile();
		delete[] this->fileName;
		this->setEmpty();

		int i;
		for (i = 0; i < MAX_PARKING_SPOT; i++)
		{
			delete this->vh[i];
			this->vh[i] = nullptr;
		}
	}

	bool Parking::isEmpty()const
	{
		return this->fileName == nullptr;
	}

	void Parking::status() const
	{
		int cnt = 0;
		cout << "****** Valet Parking ******" << endl;
		for (int i = 0; i < this->numOfSpots; i++)
		{
			if (this->vh[i] == nullptr)
			{
				cnt += 1;
			}
		}
		cout << "*****  Available spots: " << cnt << "    *****" << endl;
	}

	void Parking::parkVehicle()
	{
		if (this->returnPos())
		{
			int menu_num = this->menu1.run();

			if (menu_num == 3)
			{
				cout << "Cancelled parking" << endl;
			}
			else if (menu_num == 2)
			{
				int posi = this->returnPos();
				this->vh[posi] = new Motorcycle();
				this->vh[posi]->setCsv(false);
				this->vh[posi]->read();
				this->vh[posi]->setParkingSpot(posi + 1);

				cout << endl << "Parking Ticket" << endl;
				this->vh[posi]->write();
			}
			else if (menu_num == 1)
			{
				int posi = this->returnPos();
				this->vh[posi] = new Car();
				this->vh[posi]->setCsv(false);
				this->vh[posi]->read();
				this->vh[posi]->setParkingSpot(posi + 1);
				
				cout << endl << "Parking Ticket" << endl;
				this->vh[posi]->write();
			}
		}
		else
		{
			cout << "Parking is full";
		}

		cout << endl;
		cin.clear();
	}

	void Parking::returnVehicle()
	{
		char licensePlate[9];
		bool flag = false;
		cout << "Return Vehicle" << endl;

		cout << "Enter License Plate Number: ";

		do
		{
			cin.getline(licensePlate, 8 , '\n');

			int Length = strlen(licensePlate);
			if (Length < 1 || Length > 8)
			{
				cout << "Invalid Licence Plate, try again: ";
			}
			else
				break;
		} while (1);

		int i;
		for (i = 0; i < this->numOfSpots; i++)
		{
			if (this->vh[i] != nullptr && *(this->vh[i]) == licensePlate)
			{
				cout << endl << "Returning:" << endl;
				this->vh[i]->write();
				flag = true;
				delete this->vh[i];
				this->vh[i] = nullptr;
				cout << endl;
				break;
			}
		}

		if (flag == false)
		{
			int len = strlen(licensePlate);
			for (int i = 0; i < len; i++)
			{
				licensePlate[i] = toupper(licensePlate[i]);
			}
			cout << endl << "License plate " << licensePlate << " Not found" << endl << endl;
		}

		this->pause();
	}

	void Parking::listParkedVehicle() const
	{
		cout << "*** " << "List of parked vehicles ";
		cout << "***" << endl;
		for (int i = 0; i < this->numOfSpots; i++)
		{
			if(this->vh[i] != nullptr)
			{
				this->vh[i]->write();
				cout << "-------------------------------" << endl;
			}
		}
		this->pause();
	}

	void Parking::findVehicle() const
	{
		char licensePlate[9];
		bool flag = false;

		cout << "Vehicle Search" << endl;

		cout << "Enter Licence Plate Number: ";
		do
		{
			cin.getline(licensePlate, 8);
			int Length = strlen(licensePlate);
			if (Length < 1 || Length > 8)
			{
				cout << "Invalid Licence Plate, try again: ";
			}
			else
				break;     
		} while (1);

		int i;
		for (i = 0; i < this->numOfSpots; i++)
		{
			if (this->vh[i] != nullptr && *this->vh[i] == licensePlate)
			{
				cout << endl << "Vehicle found:" << endl;
				flag = true;
				this->vh[i]->write();
				cout << endl;
			}
		}

		if (flag == false)
		{
			int len = strlen(licensePlate);
			for (int i = 0; i < len; i++)
			{
				licensePlate[i] = toupper(licensePlate[i]);
			}
			cout << endl <<"License plate " << licensePlate << " Not found" << endl << endl;
		}

		this->pause();
	}

	bool Parking::closeParking() 
	{
		bool check = false;
		char option;
		
		if (this->isEmpty())
		{
			cout << "Closing Parking" << endl;
			check = true;
		}
		else
		{
			cout << "This will Remove and tow all remaining vehicles from the parking!" << endl;
			cout << "Are you sure? (Y)es/(N)o: ";
			

			while (!check)
			{
				cin >> option;

				if (option == 'Y' || option == 'y')
				{
					cout << "Closing Parking" << endl;
					for (int i = 0; i < this->numOfSpots; i++)
					{
						if (this->vh[i] != nullptr)
						{
							cout << endl << "Towing request" << endl;
							cout << "*********************" << endl;
							this->vh[i]->write();
							delete this->vh[i];
							this->vh[i] = nullptr;
						}
					}
					check = true;
				}
				else if (option == 'N' || option == 'n')
				{
					return false;
				}
				else
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
					cin >> option;
				}
			}
		}

		return check;
	}

	bool Parking::exitProgram() const
	{
		bool check = false;
		char option;
		cout << "This will terminate the program!" << endl;
		cout << "Are you sure? (Y)es/(N)o: ";

		while (!check)
		{
			cin >> option;

			if (option == 'Y' || option == 'y')
			{
				cout << "Exiting program!" << endl;
				check = true;
			}
			else if (option == 'N' || option == 'n')
			{
				return false;
			}
			else
			{
				cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				cin >> option;
			}
		}

		return check;
	}

	void Parking::saveDataFile() const
	{
		if (!this->isEmpty())
		{
			ofstream ofntr(this->fileName, ios::out);

			//oftr.open(this->fileName);

			if (ofntr.is_open())
			{
				for (int i = 0; i < this->numOfSpots; i++)
				{
					if (this->vh[i] != nullptr)
					{
						this->vh[i]->setCsv(true);
						this->vh[i]->write(ofntr);
					}
				}
			}

			ofntr.close();
		}
	}

	bool Parking::loadData() 
	{
		bool check = false;

		if (this->isEmpty())
			check = true;

		else {
			/*cout << "---------------------------------" << endl;
			cout << "loading data from " << this->fileName << endl;
			cout << "---------------------------------" << endl << endl;*/
			ifstream ifntr(this->fileName, ios::in);
			char rd;
			Vehicle* vehicleTemp = nullptr;

			if (ifntr.is_open())
			{
				while (ifntr.get(rd))
				{
					if (ifntr.fail())
						break;
					else
					{
						check = true;
						//string data;
						ifntr.ignore(1000, ',');
						if (rd == 'C')
						{
							vehicleTemp = new Car();
							vehicleTemp->setCsv(true);
							vehicleTemp->read(ifntr);
							vehicleTemp->setCsv(false);
						}
						else if (rd == 'M')
						{
							vehicleTemp = new Motorcycle();
							vehicleTemp->setCsv(true);
							vehicleTemp->read(ifntr);
							vehicleTemp->setCsv(false);
						}
					}

					if (ifntr)
					{
						if (vehicleTemp != nullptr) {
							int index = vehicleTemp->getParkingSpot();
							this->vh[index - 1] = vehicleTemp;
						}
					}
					else
					{
						delete vehicleTemp;
						vehicleTemp = nullptr;
					}
				}
			}
			else 
				check = true;

			ifntr.close();
		}

		return check;
	}

	int Parking::run()
	{
		int choice = 0;
		bool loopRun = true;

		if (!this->isEmpty())
		{
			do
			{
				this->status();
				choice = this->menu.run();

				switch (choice)
				{
				case 1:
					this->parkVehicle();
					this->pause();
					break;

				case 2:
					this->returnVehicle();
					break;

				case 3:
					this->listParkedVehicle();
					break;

				case 4:
					this->findVehicle();
					break;

				case 5:
					if (this->closeParking())
						loopRun = false;
					break;

				case 6:
					if (this->exitProgram())
						loopRun = false;
					break;
				}

			} while (loopRun);
		}

		return this->isEmpty();
	}

	void Parking::setEmpty()
	{
		this->fileName = nullptr;
		this->numOfSpots = 0;
	}
	int Parking::returnPos()const
	{
		int posi = -1;
		bool vgot = false;

		for (int i = 0; i < this->numOfSpots && !vgot; i++)
		{
			if (this->vh[i] == nullptr)
			{
				vgot = true;
				posi = i;
			}
		}

		return posi;
	}

	void Parking::pause()const {
		cout << "Press <ENTER> to continue....";
		cin.ignore(5000, '\n');
	}
};