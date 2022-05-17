#pragma once

#include"Book.h"

void rent(Book* b, std::string& r);
void rtrn(Book* b);

std::ostream& operator<<(std::ostream& os, std::vector<Book*> b);