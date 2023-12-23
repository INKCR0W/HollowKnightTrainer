/*
*  ┏┓　　　┏┓
*┏┛┻━━━┛┻┓
*┃              ┃ 　
*┃　　　━　　　┃
*┃　┳┛　┗┳　┃
*┃              ┃
*┃　　　┻　　　┃
*┃              ┃
*┗━┓　　　┏━┛
*　　┃　　　┃神兽保佑		THE MYTHICAL BEAST BLESS
*　　┃　　　┃代码无BUG！	THE CODE WITHOUT BUGS!
*　　┃　　　┗━━━┓
*　　┃              ┣┓
*　　┃              ┏┛
*　　┗┓┓┏━┳┓┏┛
*　　　┃┫┫　┃┫┫
*　　　┗┻┛　┗┻┛ 　
*/


#include <iostream>
#include <string>
#include <vector>

#include "Offset.h"
#include "Memory.h"

using namespace std;
using offset::ObjectOffset;

int main() {		// DEBUGGING
	ObjectOffset offset(L"mono-2.0-bdwgc.dll", { 0x497DE8, 0x90, 0xE20, 0x11C }, {
		{ L"health", 0x74 },
		{ L"maxHealth", 0x78 },
		{ L"maxHealthBase", 0x7C },
		{ L"healthBlue", 0x80 },
		{ L"heartPieces", 0x8C },
		{ L"geo", 0xA8 },
		{ L"maxMP", 0xAC },
		{ L"MPCharge", 0xB0 },
		{ L"vesselFragments", 0xC0 },
		});

	memory::Memory memory(L"hollow_knight.exe");

	while (1) {
		memory.write_object(offset, L"health", 5);
		Sleep(500);
	}


	system("pause");
	return 0;
}