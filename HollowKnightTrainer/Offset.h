#pragma once

#include <vector>
#include <map>
#include <string>
#include <Windows.h>

#include "Uncopyable.h"

namespace offset {
	using std::vector;
	using std::wstring;
	using std::map;

	class ValueOffset : private Uncopyable::Uncopyable {
	protected:
		wstring p_module;
		vector<DWORD> p_offsets;

	public:
		ValueOffset();
		ValueOffset(const wstring& p_module, const vector<DWORD>& p_offsets);
		~ValueOffset() {}

		bool set_module(const wstring& module_name);
		bool set_offset(const vector<DWORD>& offset_array);

		const wstring& module() const;
		const vector<DWORD>& offset() const;
	};

	class ObjectOffset : public ValueOffset {
	private:
		map<wstring, vector<DWORD>> p_values;

	public:
		ObjectOffset();
		ObjectOffset(const wstring& p_module, const vector<DWORD>& p_offsets, const map<wstring, vector<DWORD>>& p_values);
		~ObjectOffset() {}

		bool set_values(const map<wstring, vector<DWORD>>& values_offsets);

		const map<wstring, vector<DWORD>>& values() const;
	};
}