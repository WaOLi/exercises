#include"Literature.h"


Literature::Literature(const char* author,
	const char* name, const int& id, const int& stock, const char* genre)
	:Book(author, name, id, stock), genre{genre}{}

void Literature::print(std::ostream& os) const
{
	os << name << " (" << author << ") genre " 
		<< genre << ", id: " << id << ", in quantity of " << stock;
}

void Literature::rent(const char* renter, const int& st_id)
{
	if (stock > 0)
	{
		stock--;
		this->renters.push_back(renter);
	}
}