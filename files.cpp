#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>

int main()
{
	std::ifstream in_file("../Section19Challenge3/romeoandjuliet.txt");
	std::ofstream out_file("cpyPoem.txt");
	if (!in_file || !out_file)
	{
		std::cerr << "Failed to open file";
		return 1;
	}

	std::string line;
	int i{ 1 };
	while (std::getline(in_file, line))
	{
		if (line == "")
			out_file << std::endl;
		else
		{
			out_file << std::left << std::setw(5) << i << line << std::endl;
			i++;
		}
	}
	in_file.close();
	out_file.close();
}