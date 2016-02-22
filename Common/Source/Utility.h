#ifndef UTILITY_H
#define UTILITY_H

void Fall(float& value, float by, float until);
void Rise(float& value, float by, float until);

void LerpAngle(float & angle, float target, float dt);

#include <vector>
#include <string>
#include <sstream>

void RemoveChar(std::string& line, char c);

std::vector<std::string> DivideLine(const std::string& line, char divider = ',');
std::vector<std::string> ParseLine(const std::string& line, const char* ignore = "[] ,	");
std::vector<float> VectorStoF(const std::vector<std::string>& list);

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