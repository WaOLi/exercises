#include "Book.h"

int Book::count{ 0 };

Book::Book(std::string& t, std::string& a)
	:author{ a }, title{ t }, id{ count }, renter{}, is_rntd{ false }
{
	this->count++;
}