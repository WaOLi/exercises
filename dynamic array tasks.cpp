#include<iostream>
#define pi 3.1415
using namespace std;
class Error {};
void init_arr(int*& arr, int &size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand()%10;
	}
}//initializes array to random 0-9 ints

void print_arr(int*& arr, int& size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << '\t';
	}
}

void push_front(int *&arr, int &size, const int num)
{
	size++;
	int* temp_arr = new int[size];
	temp_arr[0] = num;

	for (int i = 1; i < size; i++)
	{
		temp_arr[i] = arr[i - 1];
	}

	delete[] arr;
	arr = temp_arr;
}//push the specified number into 0 index

void push_custom(int *&arr, int &size)
{
	cout << "\nEnter the index of the array member you want to change 0-" <<
		size - 1 << " :\n";
	int index;
	cin >> index;
	cout << "\nNow enter the int you wanna change it to:\n";
	int num;
	cin >> num;

	if (index < 0 || index >= size) throw Error();
	size++;
	int* temp_arr = new int[size];
	
	for (int i = 0; i < index; i++)
	{
		temp_arr[i] = arr[i];
	}
	temp_arr[index] = num;
	for (int i = index + 1; i < size; i++)
	{
		temp_arr[i] = arr[i - 1];
	}
	delete[] arr;	
	arr = temp_arr;
}//push a specified int into a specified index


int main()
try
{
	int size;
	cout << "enter size:\n";
	cin >> size;
	int* pnt = new int[size];
	init_arr(pnt, size);
	print_arr(pnt, size);
	push_custom(pnt, size);
	cout << endl << endl;
	print_arr(pnt, size);


	delete[] pnt;
}
catch (const Error e)
{
	cout << "bruh, waaay outta line...";
}