// Date_class_cource_work.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Date.h"
#include "Invalid_Date_Exceptions.h"




int main()
{
	Date e(25, month(11), 1995);
	Date d;
	/*std::cin >> e;
		std::cout << e.dayOfYear() << "   " << e.dayOfWeek() <<
			 "  " << e.daysInYear() << "  " << e.daysTo(e) << std::endl;   */


		std::cout << e.getDay() << std::endl;
	//	std::cout << e.addDay(365) << std::endl;
		std::cout << e.addYear(21)<< std::endl;
		std::cout << e.isValid() << std::endl;
		const char * t = "MMM.DDD/DD/MM/YY";
		const char * p = e.ToString(t);	 

		for (int i = 0; i < strlen(p) + 1; ++i)
		{
			std::cout << p[i];
		}
		std::cout << " " << std::endl;		   

		std::cout << e.SystemDate(e) << std::endl;
		std::cout << e.addMonth(25) << std::endl;
		std::cout << e.addMonth(-25) << std::endl;
		std::cout << e.dayOfWeek() << std::endl;
		//std::cout << e.setDate(1995, 11, 24) << std::endl;
		int k = Date::static_isValid(1990, 2, 30);

		std::cout << k << std::endl;
		delete[] p;
		std::cout << e.daysTo(d) << std::endl;

	return 0;
}
			    