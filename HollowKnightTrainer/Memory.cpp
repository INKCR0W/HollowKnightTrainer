#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>

#include "Memory.h"
#include "Error.h"
#include "DEBUGGING.h"

namespace memory {
	using namespace std;
	using error::get_error;
	using std::map;

	Memory::Memory() : process_name(), process_id(0), process_handle(nullptr), module_list() {}
	Memory::Memory(const wstring& process_name) : process_name(process_name) {
		process_handle = get_process_handle(process_name);
		if (process_handle == nullptr) {
			cerr << "CAN NOT FOUND GAME PROCESS, ERROR: " << get_error(GetLastError()) << endl;
			exit(0);
		}

		if (!update_module_list()) {
			cerr << "CAN NOT UPDATE MODULE LIST, ERROR: " << get_error(GetLastError()) << endl;
			exit(0);
		}
	}

	const map<wstring, ADDRPOINT>& Memory::list() const
	{
		return module_list;
	}

	const ADDRPOINT Memory::addr(const wstring& module_name) const
	{
		return module_list.find(module_name)->second;
	}

	HANDLE Memory::get_process_handle(const std::wstring& processName) {
		DWORD processId = 0;
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (snapshot != INVALID_HANDLE_VALUE) {
			PROCESSENTRY32 entry{};
			entry.dwSize = sizeof(PROCESSENTRY32);

			if (Process32First(snapshot, &entry)) {
				do {
					if (processName == entry.szExeFile) {
						processId = entry.th32ProcessID;
						break;
					}
				} while (Process32Next(snapshot, &entry));
			}

			CloseHandle(snapshot);
		}

		process_id = processId;
		return OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	}

	bool Memory::update_module_list() {
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_id);

		if (snapshot != INVALID_HANDLE_VALUE) {
			MODULEENTRY32 module_entry{};
			module_entry.dwSize = sizeof(MODULEENTRY32);

			if (Module32First(snapshot, &module_entry)) {
				do {
					module_list[wstring(module_entry.szModule)] = reinterpret_cast<ADDRPOINT>(module_entry.modBaseAddr);
				} while (Module32Next(snapshot, &module_entry));
			}

			CloseHandle(snapshot);
		}
		else {
			return false;
		}
		return true;
	}

}