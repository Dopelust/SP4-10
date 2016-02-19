#ifndef UTILITY_H
#define UTILITY_H

void Fall(float& value, float by, float until);
void Rise(float& value, float by, float until);

#include <string>
#include <sstream>

template<typename T> std::string ToString(T msg)
{
	static std::ostringstream ss;
	ss.str("");
	ss << msg;
	return ss.str();
}

template<typename T, typename... Arg> std::string ToString(T msg, Arg... arg)
{
	static std::ostringstream ss;
	ss.str("");
	ss << msg << ToString(arg...);
	return ss.str();
}

#endif