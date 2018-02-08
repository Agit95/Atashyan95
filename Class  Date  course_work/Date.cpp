#include "stdafx.h"
#include <string.h>
#include <sstream>
#include <Windows.h>
#include  "Date.h"

Date::Date() :day(24), mon(month(11)), year(1995) {}

Date::Date(int d, month m, int y) 
{
	this->setYear(y);
	this->setMon(month(m));
	this->setDay(d);
}

Date::Date(const Date &obj) : day(obj.day), mon(obj.mon), year(obj.year) {}

//Վերադարձնում  է  տվյալ  պահին  եղած  օրը
inline  int    Date::getDay() const
{
	return  this->day;
}

//Վերադարձնում  է  տվյալ  պահին եղած  ամիսը
inline  month  Date::getMon() const
{
	return  this->mon;
}

//Վերադարձնում է  տվյալ  պահին եղած  տարին 
inline  int    Date::getYear() const
{
	return  this->year;
}

//Մուտքա  անում տարին ստուգելով  սահմանված  երկարությունը
void   Date::setYear(int y)
{
	if (y>1970 && y<2040)
		this->year = y;
	else
		throw Invalid_Date_Exceptions("Invalid Year");
}

// Մուտքա  անում  ամիսը ստուգելով ներմուծման ճշտությունը
void   Date::setMon(month m )
{
	if (int(m) >= 1 && int(m) <= 12)
		this->mon = m;
	else
		throw Invalid_Date_Exceptions("Invalid  Month");
}

// Մուքա  անում  օրը ստուգելով ներմուծման ճշտությունը ըստ  ամիսների  
void   Date::setDay(int d)
{
	month k = this->mon;
	switch (k)
	{
	case januar:
	case march:
	case may:
	case july:
	case august:
	case october:
	case december:
	{
		if (d >= 1 && d <= 31)
			this->day = d;
		else
			throw Invalid_Date_Exceptions("Invalid Day");
	}   break;
	case april:
	case june:
	case september:
	case november:
	{
		if (d >= 1 && d <= 30)
			this->day = d;
		else
			throw Invalid_Date_Exceptions("Invalid Day");
	}   break;
	case february:
	{
		if (d >= 1 && d <= 28 + is_leapyear(*this))
			this->day = d;
		else
			throw Invalid_Date_Exceptions("Invalid Day");
	}   break;
	default:
		break;
	}
}

//Վերադարձնում է  տվյալ  պահին եղած  ամիս  ամսաթիվը  ցուցիչների  միջոցով;
void  Date::getDate(int *Year, int *Month, int *Day) const
{
	*Year = this->getYear();
	*Month = static_cast<int>(this->getMon());
	*Day = this->getDay();
}

//Ամբողջական  օբյեկտի  տվյալների  փոփոխություն եթե  ճիշտ  մուտք  է յատարված  հակառակդեպքում  կատարվում սխալ վերագրում  և  վերադաձնում է սխալ
bool  Date::setDate(int Year, int Month, int Day)
{
	bool b = true;
	if (Date::static_isValid(Year, Month, Day))
	{
		this->year = Year;
		this->mon = month(Month);
		this->day = Day;
		b = true;
	}
	else
	{
		this->year = Year;
		this->mon = month(Month);
		this->day = Day;
		b = false;
	}
	return b;
}

//Վերադարձնում  է  թե   տարվա  որ  օրն  է
int   Date::dayOfYear() const
{
	int count;
	month o = this->getMon();
	switch (o)
	{
	case januar:    count = this->getDay();
		break;
	case february:  count = this->getDay() + 31;
		break;
	case march:	    count = this->getDay() + 31 + 28 + is_leapyear(*this);
		break;
	case april:     count = this->getDay() + 31 * 2 + 28 + is_leapyear(*this);
		break;
	case may:		count = this->getDay() + 31 * 2 + 30 + 28 + is_leapyear(*this);
		break;
	case june:		count = this->getDay() + 31 * 3 + 30 + 28 + is_leapyear(*this);
		break;
	case july:	    count = this->getDay() + 31 * 3 + 30 * 2 + 28 + is_leapyear(*this);
		break;
	case august:	count = this->getDay() + 31 * 4 + 30 * 2 + 28 + is_leapyear(*this);
		break;
	case september:	count = this->getDay() + 31 * 5 + 30 * 2 + 28 + is_leapyear(*this);
		break;
	case october:	count = this->getDay() + 31 * 5 + 30 * 3 + 28 + is_leapyear(*this);
		break;
	case november:	count = this->getDay() + 31 * 6 + 30 * 3 + 28 + is_leapyear(*this);
		break;
	case december:	count = this->getDay() + 31 * 6 + 30 * 4 + 28 + is_leapyear(*this);
		break;
	default:
		break;
	}
	return count;
}

//վերադարձնում է  Օպերացիոն համակարգի  վերդարձրած  օրը  շաբաթվա  որ  օրն է
inline int  Date::dayofWeek_System() const
{
	SYSTEMTIME T;
	return 	T.wDayOfWeek;
}

//Վերադարձնում  է  թե  շաբաթվա որ  օրն է սկսած  կիակի  օրվանից  [0,6] միջակայքում 
int   Date::dayOfWeek() const
{
	int m;
	int w;
	int c = this->getYear() / 100;
	int y = this->getYear() % 100;
	int Y = this->getYear();
	int d = this->getDay();
	if (this->getMon() == month(1))
	{
		m = 11;
		y = Y % 100 - 1;
		c = Y  / 100;
	}
	else  if (this->getMon() == month(2))
	{
		m = 12;
		y = Y % 100 - 1;
		c = Y / 100;
	}
	else  m = int(this->getMon()) - 2;
	int s =static_cast<int>( 2.6*m - 0.2);
	w = (d + s + y + y / 4 + c / 4 - 2 * c) % 7;
	if (w == 0)
		return 	7;
	return w;

}

//Վերադարձնում է  ամսվա  օրերի  քանակը
int   Date::daysInMonth() const
{
	int q = 0;
	month m = this->getMon();
	switch (m)
	{
	case januar:
	case march:
	case may:
	case july:
	case august:
	case october:
	case december:  q = 31; break;
	case april:
	case june:
	case september:
	case november:  q = 30; break;
	case february:	q = 28 + is_leapyear(*this); break;
	}
	return q;
}

//Վերադարձնում  է  տարվա օրերի քանակը
inline int   Date::daysInYear() const
{
	return 365 + is_leapyear(*this);
}

//Վերադարձնում է գործող  և  փոխանցված ամսաթվի  ամսաթվերի  տարբերությունը
long   Date::daysTo(Date obj) const
{	
	int q = 0;
	int t = this->getYear() - obj.getYear();
	if (t == 0)
		return this->dayOfYear() - obj.dayOfYear();
	else  if (t > 0)
	{
		q = this->dayOfYear() + (this->daysInYear() - obj.dayOfYear());
		while (t != -1)
		{
			--obj.year;
			q += 365 + is_leapyear(obj);
			--t;
		}
		q = -q;
	}  
	else 
	{
		q = this->dayOfYear() + (this->daysInYear() - obj.dayOfYear());
		while (t != 1)
		{
			++obj.year;
			q += 365 + is_leapyear(obj);
			++t;
		}
	}
	return q;
}

//Ավելացնում  է  նշված   քանակով   օրեր  
Date&   Date::addDay(int d)
{
	if (d == 0) return *this;
	if (d > 0)
	{
		while (d != 0)
		{
			++(*this);
			--d;
		}
	}
	else  
	{
		while (d != 0)
		{
			--(*this);
			++d;
		}
	}
	if (this->year < 1970 || this->year > 2040)
		Invalid_Date_Exceptions("You  are add Invalid Day");
	return *this;
}

//Ավելացնում  է  նշված  քանակով  օրեր
Date&   Date::addMonth(int m)
{
	int q = 0;
	int k = 0;
	int c = 0;
	int t = 0;
	int e = 0;
	int f = 0;
	if (m == 0) return *this;
	if (m > 0)
	{
		k = m / 12;
		c = m % 12;
		t = (int)this->mon + c;
		e = t / 12;
		f = t % 12;
		this->year += k + e;
		this->mon = month(f);
	}
	else
	{
		k = m / 12;
		c = m % 12;
		t = -(int)this->mon + c;
		e = t / 12;
		f = -(f % 12);
		this->year += k + e;
		if (f == 0)
		{
			f = 12;
			--this->year;
		}
		this->mon = month(f);
	}
	return *this;
}

//Ավելացնում  է  նշված  քանակով  տարիներ
Date&   Date::addYear(int y)
{
	this->year += y;
	if (this->day == 29 && this->mon == month(2) && !is_leapyear(*this))
	{
		if (this->year >= 1970 && this->year <= 2040)
		{
			this->day = 1;
			this->mon = month(3);
		}
	}
	else if (this->year < 1970 || this->year > 2040)
			 Invalid_Date_Exceptions("You add Invalid Year");
	return *this;
}

//Վերադարձնում է  օպերացիոն համակարգի  ամիս ամսաթիվը
Date&   Date::SystemDate(Date& obj)
{
	SYSTEMTIME obj1;
	GetSystemTime(&obj1);
	obj.setYear(obj1.wYear);
	obj.setMon(month(obj1.wMonth));
	obj.setDay(obj1.wDay);
	return obj;
}
														       
//Ամիսը ,  ամսաթիվը  և  տարին վերադարձնում  է  տողով  
const  char*  Date::ToString(const char*& format) const
{
	int i = 0;
	std::stringstream ss;
	while (i <= strlen(format))
	{
		switch (format[i])
		{
		case 'd':
		case 'D':
		{
			if ((format[i + 1] == 'd' || format[i + 1] == 'D') &&
				(format[i + 2] == 'd' || format[i + 2] == 'D') &&
				(format[i + 3] == 'd' || format[i + 3] == 'D'))
			{
					ss << Date::longDayName(this->dayOfWeek());
					i += 4;
			} 
			else  if ((format[i + 1] == 'd' || format[i + 1] == 'D') &&
				      (format[i + 2] == 'd' || format[i + 2] == 'D'))
			{
				ss << Date::shortDayName(this->dayOfWeek());
				i += 3;
			}
			else if ((format[i + 1] == 'd' || format[i + 1] == 'D'))
			{
				if (this->day < 10)
				{
					ss << 0;
					ss << this->day;
					i += 2;
				}	
				else
				{
					ss << this->day;
					i += 2;
				}

			}
			else  if (format[i + 4] == 'd' || format[i + 4] == 'D')
			{
				throw Invalid_Date_Exceptions("You  are input infalid format Day");
			}
			else 
			{
				ss << this->day;
				i += 1;
			}
		}	  break;
		case 'm':
		case 'M':
		{
			if ((format[i + 1] == 'm' || format[i + 1] == 'M') &&
				(format[i + 2] == 'm' || format[i + 2] == 'M') &&
				(format[i + 3] == 'm' || format[i + 3] == 'M'))
			{
				ss << Date::longMonthName(this->mon);
				i += 4;
			}
			else  if ((format[i + 1] == 'm' || format[i + 1] == 'M') &&
				      (format[i + 2] == 'm' || format[i + 2] == 'M'))
			{
				ss << Date::shortMonthName(this->mon);
				i += 3;
			}
			else if ((format[i + 1] == 'm' || format[i + 1] == 'M'))
			{
				if (this->mon < 10)
				{
					ss << 0;
					ss << this->mon;
					i += 2;
				}
				else
				{
					ss << this->mon;
					i += 2;
				}

			}
			else if (format[i + 4] == 'm' || format[i + 4] == 'D')
			{
				throw Invalid_Date_Exceptions("You  are  input invalid format month");
			}
			else
			{
				ss << this->mon;
				i += 1;
			}
		}	break;
		case 'y':
		case 'Y':
		{
			if ((format[i + 1] == 'y' || format[i + 1] == 'Y') &&
				(format[i + 2] == 'y' || format[i + 2] == 'Y') &&
				(format[i + 3] == 'y' || format[i + 3] == 'Y'))
			{
				ss << this->year;
				i += 4;
			}
			else if ((format[i + 1] == 'y' || format[i + 1] == 'Y'))
			{
				int f = this->getYear() / 1000;
				int y = (this->getYear() - 1000 * f) / 100;
				int z = ((this->getYear() - 1000 * f) - 100 * y) / 10;
				int k = ((this->getYear() - 1000 * f) - 100 * y) % 10;
				ss << z << k;
				i += 2;
			}
			else
				throw Invalid_Date_Exceptions("You  are input invalid type Year");
		}	break;
		default:  
			ss << format[i];
			i += 1;
			break;
		}
	}

	std::string s;
	s = ss.str();
	const char* _Format = s.c_str();
	char * Format =new char[strlen(_Format)+1] ;
	for (int i = 0;i < strlen(_Format) + 1;++i)
	{
		Format[i] = _Format[i];
	}
	
	return  Format;
}			 

//Լռելայնությամբ  սահմանված  ամիս  ամսաթիվ  և տարի
Date  Date::default_date(24, month(11), 1995);

//Ամիս  ամսաթվի  ճշտությունը  ստուգող  ստատիկ  ֆունկցիա  
bool  Date::static_isValid(int Year, int Month, int Day)
{
	if (Year < 1970 || Year>2040)
		return false;
	else  if (Month < 1 || Month>12)
		return false;
	bool b = true;
	switch (Month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
	{
		if (Day < 1 || Day > 31)
			b = false;
	}   break;
	case 4:
	case 6:
	case 9:
	case 11:
	{
		if (Day < 1 || Day > 30)
			b = false;
	}   break;
	case 2:
	{
		if (Day < 1 || Day > 28 + Date::static_is_leapyear(Year))
			b = false;
	}   break;
	default:
		b = true;
		break;
	}
	return b;
}

//Վերադարծնում  է  true  եթե  ներմուծված  օրը  ճիշտ  է  հակառակ  դեպքում false
bool  Date::isValid() const
{
	bool isvalid;
	if (this->year >= 1970 && this->year <= 2040)
		if (this->mon >= month(1) && this->mon <= month(12))
			if ((this->mon == month(1) || this->mon == month(3) ||
				this->mon == month(5) || this->mon == month(7) ||
				this->mon == month(8) || this->mon == month(10) ||
				this->mon == month(12)) && (this->day >= 1 && this->day <= 31))
				isvalid = true;
		else if (this->mon == month(2) && this->day >= 1 && this->day <= 28 + is_leapyear(*this))
				isvalid = true;
		else if (this->mon != month(2) && this->day >= 1 && this->day <= 30)
				isvalid = true;
		else 
			isvalid = false;
		return isvalid;
}

inline bool  Date::isNull() const
{
	return !isValid();
}

//Ստուգում  է  արդյոք   նահանջ  տարի  է  թե  ոչ
int   is_leapyear(const Date& obj)
{
	if ((obj.year % 4 == 0)  || (obj.year / 100 == 0) && (obj.year % 400 == 0))
		return 1;
	return 0;
}

//Նահանջ   տարին ստուգող ստատիկ  ֆունկցիա
int   Date::static_is_leapyear(int Year)
{
	if ((Year % 4 == 0) || (Year / 100 == 0) && (Year % 400 == 0))
		return 1;
	return 0;
}

//Սաբաթվա  օրվա  անունը  տողով վերադարձնող  ստատիկ ֆունկցիա
const char* Date::longDayName(int WeekDayNumber)
{
	char *x = new char[10];
	switch (WeekDayNumber)
	{
	case 1: x = "Monday";	 break;
	case 2:	x = "Tuesday";	 break;
	case 3:	x = "Wednesday"; break;
	case 4: x = "Thursday";  break;
	case 5:	x = "Friday";    break;
	case 6: x = "Saturday";  break;
	case 7: x = "Sunday";    break;
	default:
		throw Invalid_Date_Exceptions("Your  input Invalid Day");
		break;
	}
	return x;
}

//Շաբաթվա  օրվա կրճատ  անունը  տողով  վերադարձնող  ստատիկ  ֆունկցիա
const char* Date::shortDayName(int WeekDayNumber)
{
	char *x = new char[4];
	switch (WeekDayNumber)
	{
	case 1: x = "Mon";	 break;
	case 2:	x = "Tue";	 break;
	case 3:	x = "Wed";   break;
	case 4: x = "Thu";   break;
	case 5:	x = "Fri";   break;
	case 6: x = "Sat";   break;
	case 7: x = "Sun";   break;
	default:
		throw Invalid_Date_Exceptions("Your  input Invalid Day");
		break;
	}
	return x;
}

//Ամսվա  անվանում  վերադարձնող  ստատիկ  ֆունկցիա 
const char* Date::longMonthName(int Month)
{
	char* format = new  char[10];
	switch (Month)
	{
	case 1:  format = "January";   break;
	case 2:  format = "February";  break;
	case 3:  format = "March";     break;
	case 4:  format = "April";	   break;
	case 5:  format = "May";	   break;
	case 6:  format = "June";      break;
	case 7:  format = "July";      break;
	case 8:  format = "August";    break;
	case 9:  format = "September"; break;
	case 10: format = "October";   break;
	case 11: format = "November";  break;
	case 12: format = "December";  break;
	default:
		throw Invalid_Date_Exceptions("Your  input Invalid Month");
		break;
	}
	return  format;
}

//Ամսվա  կրճատ  անվանումը  վերադարձնող  ստատիկ  ֆունկցիա
const char* Date::shortMonthName(int Month)
{
	char * format = new char[4];
	switch (Month)
	{
	case 1:  format = "Jan";   break;
	case 2:  format = "Feb";   break;
	case 3:  format = "Mar";   break;
	case 4:  format = "Apr";   break;
	case 5:  format = "May";   break;
	case 6:  format = "Jun";   break;
	case 7:  format = "Jul";   break;
	case 8:  format = "Aug";   break;
	case 9:  format = "Sep";   break;
	case 10: format = "Oct";   break;
	case 11: format = "Nov";   break;
	case 12: format = "Dec";   break;
	default:
		throw Invalid_Date_Exceptions("Your  input Invalid Month");
		break;
	}
	return  format;
}

//Տպումա  օր/ամիս/տարի հաջորդականությամբ
std::ostream& operator<<(std::ostream& output, const Date& obj)
{
	output << obj.getDay() << ":" << obj.getMon() << ":" << obj.getYear() << std::endl;
	return output;
}

//Մուտքա  անում օր/ամիս/տարի հաջորդականությամբ
std::istream& operator>>(std::istream& input, Date& obj)
{
	int d;
	int m;
	int y;
	input >> d >> m >> y;
	obj.setYear(y);
	obj.setMon(month(m));
	obj.setDay(d);
	return input;
}
