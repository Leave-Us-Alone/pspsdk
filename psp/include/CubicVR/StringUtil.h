#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <stdio.h>
#include <stdarg.h>

#include <iostream>
#include <string>
#include <vector>

#include <sstream>
#include <stdexcept>

using namespace std;

void str_replace(const string &needle, const string &replacement, string &haystack);
void str_explode(vector<string> &vect_out, const string &seperator, const string &in_str);
void str_implode(string &str_out, const string &seperator, vector<string> &str_vect);
void str_file_extract(string path_in, string &path_str,string &file_str,string &file_base,string &file_ext);

class BadConversion : public std::runtime_error {
public:
	BadConversion(const std::string& s) : std::runtime_error(s)
	{
	}
};

/* convert double to std::string */
inline std::string stringify(double x)
{
	std::ostringstream o;

	if (!(o << x))
		throw BadConversion("stringify(double)");

	return o.str();
}

/* convert unsigned long to std::string */
inline std::string stringify(unsigned long x)
{
	std::ostringstream o;

	if (!(o << x))
		throw BadConversion("stringify(unsigned long)");

	return o.str();
}

/* convert double to std::string */
inline double convertToDouble(const std::string& s)
{
	std::istringstream i(s);
	double x;
	if (!(i >> x))
		throw BadConversion("convertToDouble(\"" + s + "\")");
	return x;
}

/* convert unsigned long to std::string */
inline unsigned long convertToUnsignedLong(const std::string& s)
{
	std::istringstream i(s);
	unsigned long x;
	if (!(i >> x))
		throw BadConversion("convertToUnsignedLong(\"" + s + "\")");
	return x;
}

inline char *va(char *format, ...)
{
	va_list ap;
	static char strtmp[4096];
	
	va_start(ap, format);
	vsnprintf(strtmp, sizeof(strtmp), format, ap);
	va_end(ap);
	
	return strtmp;
}

#endif