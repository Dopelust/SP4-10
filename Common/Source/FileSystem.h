#pragma once

#include <fstream>
#include <string>
#include <vector>
using namespace::std;

class FileSystem
{
public:
	static FileSystem* Instance();

	ofstream* BeginWriting(string filepath);
	void EndWriting();

	vector<string> GetLines(string filepath);
	vector<float> ParseLine(const string& line, const char* ignore = " [,]");

private:
	FileSystem();
	~FileSystem();

	static FileSystem file;

	ofstream output;
	ifstream input;

	void Broadcast(string message);
};