#include "Utility.h"

void Fall(float& value, float by, float until)
{
	value = value - by < until ? until : value - by;
}

void Rise(float& value, float by, float until)
{
	value = value + by > until ? until : value + by;
}

void RemoveChar(std::string & line, char c)
{
	std::string newstring;

	for (auto& ch : line)
	{
		if (ch != c)
			newstring.push_back(ch);
	}

	line = newstring;
}

std::vector<std::string> DivideLine(const std::string & line, char divider)
{
	std::stringstream ss(line);
	std::vector<std::string> data;

	while (ss.good())
	{
		std::string str;
		getline(ss, str, ',');
		data.push_back(str);
	}

	return data;
}

std::vector<std::string> ParseLine(const std::string & line, const char * ignore)
{
	std::vector<std::string> data;

	char * dup = strdup(line.c_str());
	char * token = strtok(dup, " [,]");

	while (token != NULL)
	{
		data.push_back(token);
		token = strtok(NULL, " [,]");
	}

	free(dup);

	return data;
}

std::vector<float> VectorStoF(const std::vector<std::string>& list)
{
	std::vector<float> data;

	for (auto& str : list)
	{
		data.push_back(atof(str.c_str()));
	}

	return data;
}
