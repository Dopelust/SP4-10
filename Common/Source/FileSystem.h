#pragma once

#include <fstream>
#include <string>
#include <vector>
using namespace::std;

#define File FileSystem::Instance()

class FileSystem
{
public:
	static FileSystem& Instance();

	bool Exists(const char* filepath);
	void Remove(const char* filepath);

	ofstream* BeginWriting(const string& filepath);
	void EndWriting();

	vector<string> GetLines(const string& filepath);
private:
	FileSystem();
	~FileSystem();

	ofstream output;
	void Broadcast(string message);
};