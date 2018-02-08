#ifndef IVDE_H
#define IVDE_H

#include <iostream>

class Invalid_Date_Exceptions 
{
private: const char * why;
public:
	Invalid_Date_Exceptions(char *p) :why(p) {}
	~Invalid_Date_Exceptions() { std::cout << "  Destructor Exeption   " << std::endl; }
	void what() const
	{
		std::cout << this->why << std::endl;
	}
};

#endif // !IVDE_H
