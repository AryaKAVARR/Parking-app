#ifndef SDDS_ReadWritable
#define SDDS_ReadWritable
#include <iostream>

namespace sdds
{
	class ReadWritable
	{
		bool commaSeparated;

	public:
		//constructor
		ReadWritable();
		//destructor
		virtual ~ReadWritable() {};
		
		bool isCsv()const;
		void setCsv(bool value);

		//virtual read and write classes
		virtual std::ostream& write(std::ostream& onpstr = std::cout)const = 0;
		virtual std::istream& read(std::istream& inpstr = std::cin) = 0;

		//insertion and extraction operator
		friend std::ostream& operator<<(std::ostream& onpstr, const ReadWritable& ReadWrite);
		friend std::istream& operator>>(std::istream& inpstr, ReadWritable& ReadWrite);
	};
};

#endif // !SDDS_ReadWritable