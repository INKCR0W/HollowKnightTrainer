#pragma once

#include <vector>
#include <map>
#include <string>
#include <Windows.h>

namespace offset {
	using std::vector;
	using std::string;
	using std::map;

	class Uncopyable {
	protected:
		Uncopyable() {}
		virtual ~Uncopyable() {}
	private:
		Uncopyable(const Uncopyable&);
		Uncopyable& operator=(const Uncopyable&);
	};

	class ValueOffset : private Uncopyable {
	protected:
		string p_module;
		vector<DWORD> p_offsets;

	public:
		ValueOffset() : p_module(), p_offsets() {}
		ValueOffset(const string& p_module, const vector<DWORD>& p_offsets) : p_module(p_module), p_offsets(p_offsets) {}
		~ValueOffset() {}

		bool set_module(const string& module_name);
		bool set_offset(const vector<DWORD>& offset_array);

		const string& module() const;
		const vector<DWORD>& offset() const;
	};

	class ObjectOffset : public ValueOffset {
	private:
		map<string, vector<DWORD>> p_values;

	public:
		ObjectOffset() : ValueOffset(), p_values() {}
		ObjectOffset(const string& p_module, const vector<DWORD>& p_offsets, const map<string, vector<DWORD>>& p_values) : ValueOffset(p_module, p_offsets), p_values(p_values) {}
		~ObjectOffset() {}

		bool set_values(const map<string, vector<DWORD>>& values_offsets);

		const map<string, vector<DWORD>>& values() const;
	};
}