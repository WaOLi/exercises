#include "I_Printable.h"
std::ostream& operator<<(std::ostream& os, const I_Printable& p)
{
	p.print(os);
	return os;
}