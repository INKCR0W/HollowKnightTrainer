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

	typedef void* ADDRPOINT;

	class ValueOffset : private Uncopyable::Uncopyable {
	protected:
		wstring p_module;
		vector<ADDRPOINT> p_offsets;

	public:
		ValueOffset();
		ValueOffset(const wstring& p_module, const vector<ADDRPOINT>& p_offsets);
		~ValueOffset() {}

		bool set_module(const wstring& module_name);
		bool set_offset(const vector<ADDRPOINT>& offset_array);

		const wstring& module() const;
		const vector<ADDRPOINT>& offset() const;
	};

	class ObjectOffset : public ValueOffset {
	private:
		map<wstring, vector<ADDRPOINT>> p_values;

	public:
		ObjectOffset();
		ObjectOffset(const wstring& p_module, const vector<ADDRPOINT>& p_offsets, const map<wstring, vector<ADDRPOINT>>& p_values);
		~ObjectOffset() {}

		bool set_values(const map<wstring, vector<ADDRPOINT>>& values_offsets);

		const map<wstring, vector<ADDRPOINT>>& values() const;
	};
}