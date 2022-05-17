#include "utilities.h"

void rent(Book* b, std::string& r)
{
	if ((*b).get_stat())
		throw Rent_err();
	(*b).set_rntr(r);
	(*b).sw_stat();
}

void rtrn(Book* b)
{
	if (!(*b).get_stat())
		throw Rent_err();
	(*b).sw_stat();
	(*b).rntr() = "";
}

std::ostream& operator<<(std::ostream& os, std::vector<Book*> b)
{
	std::cout << std::setfill('=') << std::setw(50) << "" << std::endl;
	for (const auto& e : b)
		os << *e;
	std::cout << std::setw(50) <<""<< std::setfill(' ') << std::endl;
	return os;
}