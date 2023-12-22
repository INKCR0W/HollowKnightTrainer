#include "Offset.h"

using namespace std;
using offset::ValueOffset;
using offset::ObjectOffset;
//using std::string;
//using std::vector;
//using std::map;

bool ValueOffset::set_module(const string& module_name) {
	p_module = module_name;
	return p_module == "" ? false : true;
}

bool ValueOffset::set_offset(const vector<DWORD>& offset_array) {
	p_offsets = offset_array;
	return p_offsets.size() == 0 ? false : true;
}

const string& ValueOffset::module() const {
	return p_module;
}

const vector<DWORD>& ValueOffset::offset() const {
	return p_offsets;
}

bool ObjectOffset::set_values(const map<string, vector<DWORD>>& values_offsets) {
	p_values = values_offsets;
	return p_values.size() == 0 ? false : true;
}

const map<string, vector<DWORD>>& ObjectOffset::values() const {
	return p_values;
}