/*The task here was to get the incomplete program to compile and clear it of bugs, I worked on grammar polishing the calculator and 
*adding some functionality (sqrt(), pow() etc.)
* 
* 
* Here's grammar for the program:
* 
 Calculation:
	statement
	Print
	Quit
	Calculation ";" statement

 Statement:
	Expression
	Declaration
	Assignment

 Print:
	";"
 Quit:
	"q"
 Expression:
	Term
	Expression + Term
	Expression – Term
 Term:
	Primary
	Term * Primary
	Term / Primary
	Term % Primary
 Primary:
	Number
	"(" Expression ")"
	"–" Primary
	"+" Primary
	"sqrt(" expression ")"
 Number:
	floating-point-literal
	Symbolic constant
	Variable

 Variable:
	(name, value) pair

 Symbolic constant
	const (name, value) pair

 Assignment
	name "=" expression

 Declaration
	"let" name "=" expression
*/


#include "std_lib_facilities.h"

double sphVol();
double Sqrt();
double primary();
double power();

void print_help()
{
	cout << "this is help massage";
}


class Token
{
public:
	char kind;
	double value;
	string name = "";		
	Token() : kind(0) { }										

	Token(char ch) :kind(ch), value(0) { }						

	Token(char ch, double val) :kind(ch), value(val) { }		
																

	Token(char ch, string n) :kind(ch), name(n), value(0) { }	
																
};



class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
};

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';

Token Token_stream::get()
{/*
	
 */
	if (full) { full = false; return buffer; }
	char ch;
	cin.get(ch);
	if (isspace(ch))
	{
		if (ch == '\n') return Token(print);
	}
	cin.unget();
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
	case ',':
	
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	cin.unget();
	double val;
	cin >> val;
	return Token(number, val);
	}
	default:
		if (isalpha(ch) || ch == '_') {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			cin.unget();
			if (s == "q") return Token(quit);
			if (s == "sqrt") return Token(number, Sqrt());
			if (s == "pow") return Token(number, power());
			if (s == "let") return Token(let);
			if (s == "const") return Token(let, (double)1);
			if (s == "sphVol") return Token(number, sphVol());

			return Token(name, s);
		}
		error("Bad token");
	}
}//returns either a number, arithmetic operation, 
//a token with that contains a name for a declared variable, assignment '=', termination ';', encapsulators '(', ')'

void Token_stream::ignore(char c)
{
	/*either erases buffer or all consequtive instances of the next char from the input-stream*/
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

class Variable {
public:
	string name;
	double value;
	bool is_const;
	Variable(string n, double v) :name(n), value(v), is_const(false) { }
	Variable(string n, double v, bool c) :name(n), value(v), is_const(c) {}
};



//-------------------------------------------------------------

class Symbol_table
{
public:
	double declaration(bool cnst);
	bool is_declared(string s);
	void set_value(string s, double d);
	double get_value(string s);
	vector<Variable> names;
};

//-------------------------------------------------------------

Symbol_table st;

double Symbol_table::get_value(string s)
{
	for (int i = 0; i < st.names.size(); ++i)
		if (st.names[i].name == s) return st.names[i].value;
	error("get: undefined name ", s);
}

void Symbol_table::set_value(string s, double d)

//sets value - d to variable - s

{
	for (int i = 0; i <= st.names.size(); ++i)
		if (st.names[i].name == s)
		{
			if (st.names[i].is_const) error("attempting to assign to a const");
			st.names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

bool Symbol_table::is_declared(string s)
{
	for (int i = 0; i < st.names.size(); ++i)
		if (st.names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':
		return -primary();
	case number:
		return t.value;
	case name:
		return st.get_value(t.name);
	default:
		error("primary expected");
	}
}//returns next primary

double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}//returns next term

double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}//returns the next expression

double Symbol_table::declaration(bool cnst)
{
	Token t = ts.get();
	if (t.kind != 'a') error("name expected in declaration");
	string name = t.name;
	if (st.is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	st.names.push_back(Variable(name, d, cnst));
	return d;
}//synthesises a name and a (double) value into a Variable and pushes it into names

double assignment(string s)
{
	double b = expression();
	st.set_value(s, b);
	return b;
}//searches for variable named s and assigns b to it

void clean_up_mess()
{
	ts.ignore(print);
}//clears cin until print

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return st.declaration(t.value);
	case name:
		{
			Token t2 = ts.get();
			if (t2.kind == '=')
			{
				return assignment(t.name);
			}
			else if (t2.kind == ';' && (t.name == "h" || t.name == "H"))
			{
				ts.unget(t2);
				print_help();
				clean_up_mess();
				return 0;
			}
			cin.unget();
		}
		
	default:
		ts.unget(t);
		return expression();
	}
}//checks if the current operation is a declaration, assignment or an expression



const string prompt = "> ";
const string result = "= ";

void calculate()
{																				
	while (true)
		try																		
		{																		//allows calculation to take place
			cout << prompt;														//
			Token t = ts.get();													//
			while (t.kind == print) t = ts.get();								//
			if (t.kind == quit) return;											//
			ts.unget(t);														//
			cout << result << statement() << endl;								//
		}																		//
	catch (runtime_error& e) {													//
		cerr << e.what() << endl;												//
		clean_up_mess();
	}
}

double Sqrt()
{
	char ch;
	cin.get(ch);
	if (ch != '(') error("'(' expected after \"sqrt\"");
	cin.unget();
	double d = 0;
	d = primary();
	if (d < 0) error("square root of a negative number is not a double");
	return sqrt(d);
}

//-------------------------------------------------------------

double power()
{
	char c;
	cin.get(c);
	if (c != '(') error("'(' expected after power command");
	double base = expression();
	Token t = ts.get();
	if (t.kind != ',') error("after base ',' is expected");
	double exponent = expression();
	int exp = narrow_cast<int>(exponent);
	t = ts.get();
	if (t.kind != ')') error("')' expected (pow)");
	double res = 1;

	for (; exp > 0; exp--)
	{
		res *= base;
	}
	return res;
}
double power(double base, double exp)
{
	double result = 1;
	int i_exp = narrow_cast<int>(exp);
	for (; i_exp > 0; i_exp--)
	{
		result *= base;
	}
	return result;
}

//-------------------------------------------------------------

void define_name(string nam, double num)
{
	st.names.push_back(Variable(nam, num));
} //hard-codes a symbol_table names member

//-------------------------------------------------------------

double sphVol()
{
	char c = 'y';
	cin.get(c);
	if (c != '(') error("'(' expected");
	cin.unget();
	double d = 0;
	d = primary();

	return (3.14 * 4 / 3 * power(d, 3));
}

//-------------------------------------------------------------

int main()
try
{
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;

}

