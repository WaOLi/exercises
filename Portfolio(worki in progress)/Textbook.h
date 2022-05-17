#pragma once
#include "Book.h"

class Textbook : public Book
{
private:
	std::string course;
public:
	virtual void print(std::ostream& os) const override;

	Textbook(std::string&, std::string&, std::string&);
	virtual ~Textbook() = default;
};

