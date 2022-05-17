#pragma once
#include"Book.h"

class Literature:public Book
{
private:
	const char* genre;
public:
	Literature(const char* , const char* , const int&, const int&, const char* genre);
	virtual void print(std::ostream& os) const override;
	virtual void rent(const char* renter, const int& id = 0) override;
};