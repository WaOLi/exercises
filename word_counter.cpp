#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<map>
#include<limits>
#include<iomanip>
#include<set>

void make_pure(std::string&);
void counter(std::ifstream&, std::map<std::string, int>&);
void counter(std::ifstream&, std::map<std::string, std::set<int>>&);
void fill_map(std::ifstream& in, std::map<std::string, int>& m);
void fill_map(std::map<std::string, int>&, std::map<std::string, std::set<int>>& m);
std::ostream& operator<<(std::ostream& os, std::map<std::string, int>& m);
std::ostream& operator<<(std::ostream& os, std::map<std::string, std::set<int>> m);

int main()
{
	std::ifstream in_file("words.txt");
	if (!in_file)
	{
		std::cerr << "Fail to open";
		return 1;
	}
	std::map<std::string, int> w_c;

	fill_map(in_file, w_c);

	/*to reset the pointer close and open file*/
	in_file.close();
	in_file.open("words.txt");

	counter(in_file, w_c);
	//std::cout << w_c;

	std::map<std::string, std::set<int>> m2;
	fill_map(w_c, m2);
	in_file.close();
	in_file.open("words.txt");
	if (!in_file)
		std::cerr << "fail";
	counter(in_file, m2);
	std::cout << m2;
	in_file.close();
}

void make_pure(std::string& w)
{
	std::string temp;
	bool started{ false };

	for (const auto& c : w)
	{
		if (!started)
			started = true;
		if (isalpha(c))
			temp += toupper(c);
		else
		{
			if (!started)
				started = true;
			break;
		}
	}
	w = temp;
}

void counter(std::ifstream& in, std::map<std::string, int>& m)
{
	std::string temp{};
	std::map<std::string, int>::iterator it;
	while (in >> temp)
	{
		make_pure(temp);
		it = m.find(temp);
		it->second++;
	}
}

std::ostream& operator<<(std::ostream& os, std::map<std::string, int>& m)
{
	os
		<<std::left<< std::setw(6)<<"Word"
		<<std::right<<std::setw(10)<<"count\n"
		<< std::setfill('-') << std::setw(20) << "" << std::setfill(' ') << std::endl;
	for (const auto& e : m)
		os 
			<< std::setw(15) << std::left << e.first 
			<< " : " 
			<< std::setw(2) << std::right << e.second << std::endl << std::left;
	os<< std::setfill('-') << std::setw(20) << "" << std::setfill(' ') << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, std::map<std::string, std::set<int>> m)
{
	os
		<< std::left << std::setw(6) << "Word"
		<< std::right << std::setw(10) << "count\n"
		<< std::setfill('-') << std::setw(15) << "" << std::setfill(' ') << std::endl;
	for (const auto& e : m)
	{
		os
			<< std::setw(10) << std::left << e.first
			<< " : [ ";
		for (const auto& ep : e.second)
			os << ep << " ";
		os << "]\n";
	}
	return os;
}

void fill_map(std::ifstream& in, std::map<std::string, int>& m)
{
	std::string word;
	while (in >> word)
	{
		make_pure(word);
		m.emplace(word, 0);
	}
}

void fill_map(std::map<std::string, int>& m1, std::map<std::string, std::set<int>>& m)
{
	for (const auto& e : m1)
		m.emplace(e.first, std::set<int>{});
}

void counter(std::ifstream& in, std::map<std::string, std::set<int>>& m)
{
	std::string temp;
	std::string s;
	int line_cntr{};

	while (std::getline(in, s))
	{
		std::stringstream ss{ s };
		line_cntr++;
		while (ss >> temp)
		{
			make_pure(temp);
			auto it = m.find(temp);
			it->second.emplace(line_cntr);
		}
	}

}