/*
 This program checks if the input is in fact sentence according to the grammar given below
 
 -----------
 Grammar:
------------
 Complete sentence:
	sentence " ." [there has to be a space before the dot]

 Sentence:
	noun verb
	sentence conjunction sentence

 Verbs:
	"swim"
	"rules"
	"fly"
 Nouns:
	"fish"
	"C++"
	"birds"
	article noun
 Article:
	"The"
	"the"
 Conjunctions:
	"and"
	"or"
	"but"
*/
#include"std_lib_facilities.h"

vector<string> verbs{ "swim","rules","fly" };
vector<string> nouns{ "fish","C++","birds" };
vector<string> conjunctions{ "and", "or", "but" };

bool conj()
{
	string conjunction_tect = "";
	cin >> conjunction_tect;
	for (string s : conjunctions)
	{
		if (conjunction_tect == s)
			return true;
	}
	return false;
}

//-----------------------------------------------------------

bool fullStop()
{
	char fullStop_test = '0';
	cin >> fullStop_test;
	
	if (fullStop_test == '.')
		return true;
	cin.putback(fullStop_test);
	return false;
}//checks if the next string is a dot

//-----------------------------------------------------------

bool article(string a)
{
	if (a == "the" || a == "The")
		return true;
	return false;
}//checks if the next string is an article

//-----------------------------------------------------------

bool noun()
{
	string noun_test;
	cin >> noun_test;

	if (article(noun_test))
		cin >> noun_test;

	for (string s : nouns)
	{
		if (s == noun_test)
			return true;
	}
	return false;
}//checks if the next string is a noun

//-----------------------------------------------------------

bool verb()
{
	string verb_test;
	cin >> verb_test;

	for (string s : verbs)
	{
		if (s == verb_test)
			return true;
	}
	return false;
}//checks if the next string is a verb

//-----------------------------------------------------------

bool sentence()
{
	if (!noun())
		return false;
	if (!verb())
		return false;

	if (fullStop())
		return true;
	else if (conj())
		return sentence();
	else return false;
}//checks if input is sentence

//-----------------------------------------------------------

int main()
{
	while (true)
	{
		if (sentence())
		{
			cout << "\n -- is a sentence\n";
		}
		else cout << "\n -- is not a sentence\n";
	
		cin.ignore(INT_MAX, '\n');
	}
}

