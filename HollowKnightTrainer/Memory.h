#pragma once

#include <vector>
#include <string>
#include <map>

#include "Offset.h"
#include "Uncopyable.h"


namespace memory {
	using offset::ObjectOffset;
	using std::wstring;
	using std::map;

	class Memory : private Uncopyable::Uncopyable {
	private:
		wstring process_name;
		DWORD process_id;
		HANDLE process_handle;

		map<wstring, DWORD> module_list;

		HANDLE get_process_handle(const std::wstring& processName);
		bool update_module_list();

	public:
		Memory();
		Memory(const wstring& process_name);
		~Memory() {};

		const map<wstring, DWORD>& list() const;
		const DWORD addr(const wstring& module_name) const;
	};
}