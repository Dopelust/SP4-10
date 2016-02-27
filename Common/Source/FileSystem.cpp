#include "FileSystem.h"

#include <iostream>

FileSystem& FileSystem::Instance()
{
	static FileSystem file;
	return file;
}

bool FileSystem::Exists(const char * filepath)
{
	ifstream infile(filepath);
	return infile.good();
}

void FileSystem::Remove(const char * filepath)
{
	if (remove(filepath) != 0)
		Broadcast("Tried to delete " + string(filepath));
	else
		Broadcast("Deleted " + string(filepath));
}

ofstream* FileSystem::BeginWriting(const string& filepath)
{
	if (output.is_open())
	{
		output.close();
		Broadcast("Force closed previous file. Remember to call EndWriting() after every write.");
	}

	output.open(filepath);

	if (output.is_open())
	{
		Broadcast("Opened " + filepath + " for writing.");
		return &output;
	}

	Broadcast("Failed to open " + filepath  + " for writing.");
	return NULL;
}

void FileSystem::EndWriting()
{
	output.close();
	Broadcast("Done writing.");
}

vector<string> FileSystem::GetLines(const string& filepath)
{
	vector<string> lines;

	ifstream input;
	input.open(filepath);

	if (input.is_open())
	{
		string line;

		while (getline(input, line))
		{
			lines.push_back(line);
		}

		input.close();

		Broadcast("Read " + filepath);
	}
	else
		Broadcast("Failed to read " + filepath);

	return lines;
}

FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
}

void FileSystem::Broadcast(string message)
{
	cout << "[FILE SYSTEM] " << message << endl;
}
