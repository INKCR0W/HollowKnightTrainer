#include "Offset.h"

namespace offset {
	using namespace std;

	ValueOffset::ValueOffset() : p_module(), p_offsets() {}
	ValueOffset::ValueOffset(const wstring& p_module, const vector<ADDRPOINT>& p_offsets) : p_module(p_module), p_offsets(p_offsets) {}

	bool ValueOffset::set_module(const wstring& module_name) {
		p_module = module_name;
		return p_module == L"" ? false : true;
	}

	bool ValueOffset::set_offset(const vector<ADDRPOINT>& offset_array) {
		p_offsets = offset_array;
		return p_offsets.size() == 0 ? false : true;
	}

	const wstring& ValueOffset::module() const {
		return p_module;
	}

	const vector<ADDRPOINT>& ValueOffset::offset() const {
		return p_offsets;
	}



	ObjectOffset::ObjectOffset() : ValueOffset(), p_values() {}
	ObjectOffset::ObjectOffset(const wstring& p_module, const vector<ADDRPOINT>& p_offsets, const map<wstring, vector<ADDRPOINT>>& p_values) : ValueOffset(p_module, p_offsets), p_values(p_values) {}

	bool ObjectOffset::set_values(const map<wstring, vector<ADDRPOINT>>& values_offsets) {
		p_values = values_offsets;
		return p_values.size() == 0 ? false : true;
	}

	const map<wstring, vector<ADDRPOINT>>& ObjectOffset::values() const {
		return p_values;
	}
}