#include "Textbook.h"

void Textbook::print(std::ostream& os) const
{
	os << std::boolalpha << this->title << " (" << this->author << "), course - " << this->course
		<< ", id:" << this->id << "|is rented: " << this->is_rntd;
	if (this->is_rntd)
		os << ". by " << this->renter << std::endl;
	else
		os << std::endl;
}

Textbook::Textbook(std::string& t, std::string& a, std::string& c)
	:Book(t,a), course{c}{}