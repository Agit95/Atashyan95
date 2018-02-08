#ifndef DATE_H
#define DATE_H

#include "Invalid_Date_Exceptions.h"
#include "Month.h"



class Date
{
private:
	int day;
	month mon;
	int year;
	static Date  default_date;
public:
	Date();
	Date(int  , month , int );
	Date(const Date &);
	~Date() { std::cout << "Destructor" << std::endl; }

	void  setDay(int);
	void  setMon(month);
	void  setYear(int);
	void  getDate(int*, int*, int*) const;
	bool  setDate(int, int, int);
	bool  isValid() const;
	bool  isNull() const;
	int   getDay() const;
	month getMon() const;
	int   getYear() const;
	int   dayOfYear() const;
	int   dayofWeek_System() const;
	int   dayOfWeek() const;
	int   daysInMonth() const;
	int   daysInYear() const;
	long  daysTo(Date) const;
	const char*  ToString(const char*&) const;
	Date&  addDay(int);
	Date&  addMonth(int);
	Date&  addYear(int);
	Date&  SystemDate(Date&);
	static int   static_is_leapyear(int);
	static bool  static_isValid(int, int, int);
	static const char* longDayName(int);
	static const char* shortDayName(int);
	static const char* longMonthName(int);
	static const char* shortMonthName(int);
	friend int   is_leapyear(const Date&);
	friend std::ostream& operator <<(std::ostream&, const Date&);
	friend std::istream& operator >>(std::istream&, Date&);

	Date& operator++()
	{
		++this->day;
			if (this->day == 32 && this->mon != month(12))
			{
				this->mon = month(this->getMon() + 1);
				this->day = 1;
			}
			else  if (this->day == 32 && this->mon == month(12))
			{
				++this->year;
				this->mon = month(1);
				this->day = 1;
			}
			else  if (this->day == 31 && this->getMon() != month(1) && 
				this->getMon() != month(3) && this->getMon() != month(5) && 
				this->getMon() != month(7) && this->getMon() != month(8) &&
				this->getMon() != month(10) && this->getMon() != month(12))
			{
				this->mon = month(this->getMon() + 1);
				this->day = 1;
			}
			else  if ((this->day == 29 + is_leapyear(*this)) && this->getMon()==month(2))
			{
				this->mon = month(this->getMon() + 1);
				this->day = 1;
			}
		return *this;
	}

	Date& operator++(int)
	{
		Date& d = *this;
		++this->day;
			if (this->day == 32 && this->mon != month(12))
			{
				this->mon = month(this->getMon() + 1);
				this->day = 1;
			}
			else  if (this->day == 32 && this->mon == month(12))
			{
				++this->year;
				this->mon = month(1);
				this->day = 1;
			}
			else  if (this->day == 31 && this->getMon() != month(1) &&
				this->getMon() != month(3) && this->getMon() != month(5) && 
				this->getMon() != month(7) && this->getMon() != month(8) && 
				this->getMon() != month(10) && this->getMon() != month(12))
			{
				this->mon = month(this->getMon() + 1);
				this->day = 1;
			}
			else  if ((this->day == 29 + is_leapyear(*this)) && this->getMon() == month(2))
			{
				this->mon = month(this->getMon() + 1);
				this->day = 1;
			}
		return d;
	}

	Date& operator--()
	{
		--this->day;
			if (this->day == 0 && this->mon == month(1))
			{
				--this->year;
				this->mon = month(12);
				this->day = 31;
			}
			else  if (this->day == 0 && this->mon != month(1))
			{
				this->mon = month(this->getMon() - 1);
				this->day = this->daysInMonth();
			}
		return *this;
	}

	Date& operator--(int)
	{
		Date& d = *this;
		this->day--;
		if (this->day == 0 && this->mon == month(1))
		{
			--this->year;
			this->mon = month(12);
			this->day = 31;
		}
		else  if (this->day == 0 && this->mon != month(1))
		{
			this->mon = month(this->getMon() - 1);
			this->day = this->daysInMonth();
		}
		return d;
	}

	Date& operator -=(int n)
	{
		if (n == 0) return *this;
		if (n > 0)
		{
			while (n != 0)
			{
				--(*this);
				--n;
			}
		}
		else
		{
			while (n != 0)
			{
				++(*this);
				++n;
			}

		}
		return *this;
	}

	Date& operator +=(int n)
	{
		if (n == 0) return *this;
		if (n > 0)
		{
			while (n != 0)
			{
				++(*this);
				--n;
			}
		} 
		else
		{
			while (n != 0)
			{
				--(*this);
				++n;
			}
		}
		return *this;
	}

	Date& operator +(int n)
	{
		if (n == 0) return *this;
		if (n > 0)
		{
			while (n != 0)
			{
				++(*this);
				--n;
			}
		}
		else
		{
			while (n != 0)
			{
				--(*this);
				++n;
			}
		}
		return *this;
	}

	Date& operator -(int n)
	{
		if (n == 0) return *this;
		if (n > 0)
		{
			while (n != 0)
			{
				--(*this);
				--n;
			}
		}
		else
		{
			while (n != 0)
			{
				++(*this);
				++n;
			}
		}
		return *this;
	}

	Date& operator =(const Date& obj)
	{
		if (this != &obj)
		{
			this->year=obj.year;
			this->mon=obj.mon;
			this->day=obj.day;
		}
		return *this;
	}

	bool  operator ==(const Date& obj)
	{
		return obj.day == this->day && obj.mon == this->mon && obj.year == this->year;
	}

	bool  operator !=(const Date& obj)
	{
		return obj.year != this->year || obj.mon != this->mon || obj.day != this->day;
	}

	bool  operator >(const Date& obj)
	{
		if (this->year > obj.year) return true;
		if (this->year < obj.year) return false;
		if (this->mon > obj.mon) return true;
		if (this->mon < obj.mon) return false;
		return this->day > obj.day;
	}

	bool  operator <(const Date& obj)
	{
			if (this->year < obj.year) return true;
			if (this->year > obj.year) return false;
			if (this->mon < obj.mon) return true;
			if (this->mon > obj.mon) return false;
			return this->day < obj.day;
	}

};

#endif DATE_H //!DATE_H	