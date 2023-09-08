/* Citation and Sources...

Final Project Milestone 5

Module: Menu.h
Filename: Menu.cpp

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
#include <cstring>

using namespace std;

namespace sdds
{
	void Menu::Indentspace()const
	{
		for (int j = 0; j < this->indent; j++)
		{
			cout << "    ";
		}
	}
	MenuItem::MenuItem()
	{
		this->menuData[0] = '\0';
	}

	MenuItem::MenuItem(const char* cstr)
	{
		if (cstr == nullptr)
			this->menuData[0] = '\0';

		else
		{
			if (strlen(cstr) > 50)
			{
				strncpy(this->menuData, cstr, 50);
			}
			else
				strcpy(this->menuData, cstr);
		}
	}

	ostream& MenuItem::display(ostream& onpstr) const
	{
		if (this->menuData[0] != '\0')
		{
			onpstr << this->menuData << endl;
		}

		return onpstr;
	}

	Menu::Menu()
	{
		this->menuStr[0] = '\0';
		this->indent = 0;
		this->cnt = 0;
	}

	Menu::Menu(const char* cstr, int Number)
	{
		if (cstr == nullptr)
		{
			this->menuStr[0] = '\0';
			this->indent = 0;
			this->cnt = 0;
		}

		else
		{
			this->indent = Number;
			this->cnt = 0;
			if (strlen(cstr) > 50)
			{
				strncpy(this->menuStr, cstr, 50);
			}
			else

				strcpy(this->menuStr, cstr);
		}
	}

	Menu::operator bool() const
	{
		return this->menuStr[0] != '\0';
	}

	bool Menu::isEmpty() const
	{
		return this->menuStr[0] == '\0';
	}

	ostream& Menu::display(ostream& onpstr) const
	{
		if (isEmpty())
			onpstr << "Invalid Menu!" << endl;

		else
		{
			Menu::Indentspace();
			onpstr << this->menuStr << endl;

			bool check = false;
			for (int i = 0; i < this->cnt; i++)
			{
				if (this->mItem[i].menuData[0] == '\0')
				{
					check = true;
					break;
				}
			}
			if (check)
			{
				onpstr << "No Items to display!" << endl;
			}
			else
			{
				int i;
				for ( i = 0; i < this->cnt; i++)
				{
					Menu::Indentspace();
					onpstr << i + 1 << "- ";
					this->mItem[i].display();
				}
				Menu::Indentspace();
				onpstr << "> ";
			}

		}

		return onpstr;
	}

	Menu& Menu::operator=(const char* cstr)
	{
		if (cstr == nullptr)
			this->menuStr[0] = '\0';

		else
		{
			if (strlen(cstr) > 50)
			{
				strncpy(this->menuStr, cstr, 50);
			}
			else
				strcpy(this->menuStr, cstr);
		}

		return *this;
	}

	void Menu::add(const char* cstr)
	{
		if (cstr == nullptr)
		{
			int i;
			for (i = 0; i < this->cnt; i++)
			{
				this->mItem[i].menuData[0] = '\0';
			}
			this->menuStr[0] = '\0';
		}

		else
		{
			if (this->cnt < MAX_NO_OF_ITEMS && bool(*this))
			{
				if (strlen(cstr) > 50)
				{
					strncpy(this->mItem[this->cnt].menuData, cstr, 50);
					this->cnt++;
				}
				else
				{
					strcpy(this->mItem[this->cnt].menuData, cstr);
					this->cnt++;
				}
			}
		}
	}

	Menu& Menu::operator<<(const char* cstr)
	{
		Menu::add(cstr);

		return *this;
	}

	int Menu::run() const
	{
		int Number = 0;
		bool watch = true;

		Menu::display();
		if (this->mItem[0].menuData[0] == '\0' || isEmpty())
		{
			return 0;
		}
		else
		{
			while (watch)
			{
				cin >> Number;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Integer, try again: ";
				}
				else if ((Number > this->cnt || Number < 1))
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid selection, try again: ";
				}
				else
				{
					cin.ignore(1000, '\n');
					watch = false;
				}

			}
		}

		return Number;
	}

	void Menu::clear()
	{
		this->menuStr[0] = '\0';
		for (int i = 0; i < this->cnt; i++)
		{
			this->mItem[i].menuData[0] = '\0';
		}
		this->indent = 0;
	}

	Menu::operator int() const
	{
		return this->run();
	}
}
