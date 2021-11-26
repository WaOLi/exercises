/*This program calculates permutations and combinations
*/

#include"std_lib_facilities.h"

int factorial(int num)
{
	if (num == 0 || num == 1)
		return 1;
	return num * factorial(num - 1);
}

int permutation(int amount, int sub_amount)
{
	return factorial(amount) / factorial(amount - sub_amount);
}

int combination(int amount, int sub_amount)
{
	return factorial(amount) / (factorial(amount - sub_amount) * factorial(sub_amount));
}

int main()
{
	char op = ' ';
	int amount = 0, sub_amount = 0;
	double amount_d = 0, sub_amount_d = 0;
	while (true)
	{
		cout << "Enter two integers representing a set and a subset: ";
		cin >> amount_d >> sub_amount_d;
		int amount = narrow_cast<int>(amount_d);
		int sub_amount = narrow_cast<int>(sub_amount_d);
		
		cout << "\nEnter what kind of operation you want to perform (permutation/combination = p/c)";
		cin >> op;
		switch (op)
		{
		case 'p':
			cout << permutation(amount, sub_amount) << '\n';
			break;
		case 'c':
			cout << combination(amount, sub_amount) << '\n';
			break;
		default:
			simple_error("invalid operation input");
		}
	}
}

