/*This program handles {name,age} sets; reads names & ages, sorts {name,age} class object sets, prnts {name,age} sets*/


//#define DEBUG
#ifndef DEBUG
#include"std_lib_facilities.h"

class Name_pairs
{
public:
	void read_names(Name_pairs& np);
	void read_ages(Name_pairs& np);
	int get_size() const { return names.size(); }
	void print_pairs(const Name_pairs& np) const;
	void sort_pairs(Name_pairs& np);
	vector<string> get_names() const { return names; }
	vector<double> get_ages() const { return ages; }
private:
	vector<string> names;
	vector<double> ages;
};

void Name_pairs::read_names(Name_pairs& np)
{
	cout << "Please, enter names (\"stop\" terminates input): \n";
	string temp;
	cin >> temp;
	while (temp != "stop")
	{
		np.names.push_back(temp);
		cin >> temp;
	}
}//reads input into names-vector

void Name_pairs::read_ages(Name_pairs& np)
{
	if (np.get_names().size() < 1) return;
	int size = np.get_size();

	double temp = 0;

	cout << "\nPlease enter ages (5 to 90): \n";

	for (int i = 0; i < size; i++)
	{
		cout << names[i] << "'s age: ";
		cin >> temp;

		if (temp < 5.0 || temp > 90.0) simple_error("Age out of range");
		np.ages.push_back(temp);
		cout << endl;
	}
}//reads ages for the list of names

void Name_pairs::print_pairs(const Name_pairs& np) const
{
	int size = np.get_size();

	for (int i = 0; i < size; i++)
	{
		cout << np.get_names()[i] << ": " << np.get_ages()[i] << endl;
	}
}

void Name_pairs::sort_pairs(Name_pairs& np)
{
	vector<string>temp_names = np.get_names();
	vector<double>temp_ages = np.get_ages();

	sort(np.names);

	for (int i = 0; i < temp_ages.size(); i++)
	{
		for (int j = 0; j < temp_ages.size() ; j++)
		{
			if (names[i] == temp_names[j]) np.ages[i] = temp_ages[j];
		}
	}
}//sorts {name,age} obj. according to names (lexicographically)

ostream& operator<<(ostream& os, const Name_pairs& np)
{
	for (int i = 0; i < np.get_size(); i++)
	{
		os << np.get_names()[i] << ", " << np.get_ages()[i] << endl;
	}
	return os;
}

int main()
{
	Name_pairs np;
	np.read_names(np);
	np.read_ages(np);
	np.print_pairs(np);
	np.sort_pairs(np);
	np.print_pairs(np);
}
#endif