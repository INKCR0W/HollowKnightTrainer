#include <iostream>
#include <string>

#include "Offset.h"

using std::string;
using std::cout;
using std::endl;

int main() {
	offset::ValueOffset offset;

	offset.set_module("123");

	cout << offset.module() << endl;


	return 0;
}