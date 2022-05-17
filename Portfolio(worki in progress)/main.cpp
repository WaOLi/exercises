#include<limits>
#include"Textbook.h"
#include"utilities.h"
#include<string>
#pragma warning(disable : 4996)
struct Shelf;

void intro(Shelf& s);
void menu(Shelf& s);
void reg_a_book(std::vector<Book*>&, Book*);
char browse(Shelf& s);

struct Shelf
{
	std::vector<Book*> textbooks;
	std::vector<Book*> dictionaries;
	std::vector<Book*> literature;

	Shelf();
	~Shelf()
	{
		for (auto& e : textbooks)
			delete e;
		for (auto& e : dictionaries)
			delete e;
		for (auto& e : literature)
			delete e;
	}

	std::vector<Book*>& get_kind(const char& c)
	{
		switch (c)
		{
		case 'T':
			return textbooks;
		case 'D':
			return dictionaries;
		case 'L':
			return literature;
		default:
			std::cerr << "Invalid choice";
			return get_kind(c);
		}
	}
};

Shelf::Shelf()
{
	std::ifstream in_file("Textbooks.txt");
	if (!in_file)
	{
		std::cerr << "Fail to open file";
		throw Menu_err();
	}
	std::string buff_t, buff_a, buff_c;
	while (in_file >> buff_t >> buff_a >> buff_c)
	{
		Book* t = new Textbook(buff_t, buff_a, buff_c);
		this->textbooks.push_back(t);
	}
	in_file.close();

}

void intro(Shelf& s);
void menu(Shelf& s);
void reg_a_book(std::vector<Book*>&,  Book*);
char browse(Shelf& s);

int main()
{
	Shelf shelf;
	try 
	{
		intro(shelf);
	}
	catch (Rent_err&)
	{
		std::cerr << "Encountered a renting error";
	}
	catch (Menu_err&) 
	{
		std::cerr << "Encountered a menu error"; 
	}
}

void intro(Shelf& s)
{
	std::cout << "welcome to VS-library"
		<< " select operation\n";
	menu(s);
}

void menu(Shelf& s)
{
	char temp;
	do
	{
		std::cout << "B - browse\nA - register a book\nR - rent a book\nI - return a book\n"
			<<std::setfill('-')<<std::setw(40)<<""<<std::endl << "Q - quit\n" <<std::setfill(' ');
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get(temp);
		switch (temp)
		{
		case 'B':
			browse(s);
			break;
		case 'Q':
			break;
		case 'R':
		{
			std::cout << "Enter renter's name: ";
			std::string r;
			std::cin >> r;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			char c = browse(s);
			std::cout << "Enter ID of the book you want to rent: ";
			int id;
			std::cin >> id;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (auto& e : s.get_kind(c))
				if (e->get_id() == id)
					rent(e, r);
			break;
		}
		case 'I':
		{
			char c = browse(s);
			int id;
			std::cout << "ID of the book: ";
			std::cin >> id;
			for (auto& e : s.get_kind(c))
				if (e->get_id() == id)
					rtrn(e);
			break;

		}
		default:
			std::cerr << "Invalid operation choice\n";
			throw Menu_err();
		}
	} while (temp != 'Q');
}

void reg_a_book(std::vector<Book*>& b_v, Book* b)
{
	b_v.push_back(b);
}

char browse(Shelf& s)
{
	std::cout << "\nWhat kind of book?\nT - textbook\nD - dictionary\nL - literature\n";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	char temp;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get(temp);
	std::cout << s.get_kind(temp);
	return temp;
}