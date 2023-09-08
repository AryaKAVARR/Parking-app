#ifndef SDDS_Menu
#define SDDS_Menu
#include <iostream>

namespace sdds
{
	const int MAX_NO_OF_ITEMS = 10;

	class Menu;

	class MenuItem
	{
		friend class Menu;
		char menuData[51];

		//member function
		MenuItem();
		MenuItem(const char* cstr);
		MenuItem(const MenuItem&) = delete;
		void operator=(const MenuItem&) = delete;
		std::ostream& display(std::ostream& onpstr = std::cout)const;
	};

	class Menu
	{
		char menuStr[51];
		int cnt;
		MenuItem mItem[MAX_NO_OF_ITEMS];

	public:
		int indent;
		Menu();
		Menu(const char* cstr, int Number = 0);

		//operator overloading
		operator int()const;
		operator bool()const;
		//copy constructor
		Menu(const Menu&) = delete;

		//check the empty state of the code
		bool isEmpty()const;

		//display function
		std::ostream& display(std::ostream& onpstr = std::cout)const;

		//assignment operator
		Menu& operator=(const char* cstr);

		void add(const char* cstr);

		//left shift operator overloading
		Menu& operator<<(const char* cstr);

		int run()const;

		void clear();

		void Indentspace()const;
	};
}
#endif