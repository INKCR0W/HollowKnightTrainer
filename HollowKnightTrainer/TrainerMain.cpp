/*
*  ��������������
*�����ߩ��������ߩ�
*��              �� ��
*������������������
*�����ש������ס���
*��              ��
*���������ߡ�������
*��              ��
*������������������
*�����������������ޱ���		THE MYTHICAL BEAST BLESS
*��������������������BUG��	THE CODE WITHOUT BUGS!
*����������������������
*������              �ǩ�
*������              ����
*���������������ש�����
*���������ϩϡ����ϩ�
*���������ߩ������ߩ� ��
*/


#include <iostream>
#include <string>

#include "Offset.h"
#include "Memory.h"

using std::string;
using std::wcout;
using std::cout;
using std::endl;

int main() {		// DEBUGGING
	offset::ValueOffset offset;

	offset.set_module(L"123");

	wcout << offset.module() << endl;

	memory::Memory memory(L"Temp.exe");

	auto myMap = memory.list();

	for (auto it = myMap.begin(); it != myMap.end(); ++it) {
		wcout << it->first << ": ";
		cout << std::hex << std::uppercase << it->second << endl;
	}

	int a = 0;
	cout << memory.read_addr(reinterpret_cast<void*>(0x113FC58), &a) << endl;
	cout << a << endl;

	cout << memory.write_addr(reinterpret_cast<void*>(0x113FC58), 90) << endl;

	cout << memory.read_addr(reinterpret_cast<void*>(0x113FC58), &a) << endl;
	cout << a << endl;

	system("pause");
	return 0;
}