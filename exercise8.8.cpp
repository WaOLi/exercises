/*
* The program that accepts string inputs (names) until "stop" is entered,
* then accepts the same number of ints (ages)
*/


#include"std_lib_facilities.h"
vector<string> name;

vector<int> age;





void accept_names()
{
	string temp_name = "";
	while (true)
	{
		cin >> temp_name;
		if (temp_name == "stop") return;
		name.push_back(temp_name);
	}
}//push input strings into name vector, until stop is entered

void accept_ages()
{
	int temp_age = 0;
	for (int i = 0; i < name.size(); i++)
	{
		cin >> temp_age;
		age.push_back(temp_age);
	}
}//push name.size() int inputs into age vector (after name inputs have been accepted)

void print(vector<string>nams, vector<int> ags)
{
	for (int i = 0; i < nams.size(); i++)
	{
		cout << nams[i] << ", " << ags[i] << endl;
	}
	cout << "\n\n";
}//prints out {nams, ags} - pairs

int ind_from_seq(string s, vector<string>& nams)
{
	for (int i = 0; i < nams.size(); i++)
	{
		if (s == nams[i]) return i;
	}
	simple_error("something went wrong");
}//returns the index of s in nams

void sort_pairs(vector<int>& age, vector<string>& name)
{
	vector<int> ages = age;
	vector<string> names = name;
	sort(name);

	for (int i = 0, a = 0; i < name.size(); i++)
	{
		a = ind_from_seq(name[i], names);
		age[i] = ages[a];
	}
}//lexicographically sorts out name-vector and consequently age-vector accordingly

int main()
{
	cout << "Enter five names (enter \"stop\" to terminate input)\n";
	accept_names();

	cout << "\nok, now enter" << name.size() << " ages: \n";
	accept_ages();

	print(name, age);

	sort_pairs(age, name);

	print(name, age);

}

