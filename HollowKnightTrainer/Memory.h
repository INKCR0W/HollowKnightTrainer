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

	typedef void* ADDRPOINT;
	typedef unsigned long long ULL;

	class Memory : private Uncopyable::Uncopyable {
	private:
		wstring process_name;
		DWORD process_id;
		HANDLE process_handle;

		map<wstring, ADDRPOINT> module_list;

		HANDLE get_process_handle(const std::wstring& processName);
		bool update_module_list();

	public:
		Memory();
		Memory(const wstring& process_name);
		~Memory() {};

		const map<wstring, ADDRPOINT>& list() const;
		const ADDRPOINT addr(const wstring& module_name) const;

		template<typename T>
		bool read_addr(ADDRPOINT offset, T* value);
		template<typename T>
		bool write_addr(ADDRPOINT offset, T value);
	};

	template<typename T>
	inline bool Memory::read_addr(ADDRPOINT offset, T* value)
	{
		return ReadProcessMemory(process_handle, offset, value, sizeof(T), NULL);
	}
	template<typename T>
	inline bool Memory::write_addr(ADDRPOINT offset, T value)
	{
		return WriteProcessMemory(process_handle, offset, &value, sizeof(T), NULL);
	}
}