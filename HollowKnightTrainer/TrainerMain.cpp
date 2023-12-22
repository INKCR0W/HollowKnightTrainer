#include <iostream>
#include <string>

#include "Offset.h"
#include "Memory.h"

using std::string;
using std::wcout;
using std::endl;

int main() {		// DEBUGGING
	offset::ValueOffset offset;

	offset.set_module(L"123");

	wcout << offset.module() << endl;

	memory::Memory memory(std::wstring(L"r5apex.exe"));

	auto myMap = memory.list();

	for (auto it = myMap.begin(); it != myMap.end(); ++it) {
		wcout << it->first << ": " << std::hex << std::uppercase << it->second << endl;
	}

	system("pause");
	return 0;
}