#pragma once
#include "I_Printable.h"
#include<vector>
#include<fstream>
#include<cstring>

class Rent_err{};
class Menu_err {};

class Book : public I_Printable
{
private:
	static int count;
protected:
	std::string title;
	std::string author;
	int id;
	bool is_rntd;

	std::string renter;
public:
	void sw_stat() { is_rntd = !is_rntd; }
	bool get_stat() { return is_rntd; }
	void set_rntr(std::string& r) { renter = r; }
	std::string& rntr() { return renter; }
	int get_id(){ return id; }

	Book(std::string&, std::string&);
	virtual ~Book() = default;
};

