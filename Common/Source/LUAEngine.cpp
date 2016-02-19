#include "LUAEngine.h"

#include <iostream>
#include <string>
using namespace::std;

LUAEngine & LUAEngine::Instance()
{
	static LUAEngine lua;
	return lua;
}


bool LUAEngine::Load(const char * filepath)
{
	if (filepath == this->filepath)
		return true;

	this->filepath = filepath;

	if (luaL_loadfile(L, filepath) || lua_pcall(L, 0, 0, 0))
	{
		printf("error: %s", lua_tostring(L, -1));
		return false;
	}

	lua_pop(L, 1);
	return true;
}

float LUAEngine::GetGlobalNumber(const char * tag)
{
	lua_getglobal(L, tag);

	if (!lua_isnumber(L, -1))
		return 0;

	return  lua_tonumber(L, -1);
}

void LUAEngine::SetGlobalNumber(const char * tag, float var)
{
	lua_pushnumber(L, var);
	lua_setglobal(L, tag);

	lua_pop(L, 1);
}

string LUAEngine::GetGlobalString(const char * tag)
{
	lua_getglobal(L, tag);

	if (!lua_isstring(L, -1))
		return "";

	return lua_tostring(L, -1);
}

void LUAEngine::SetGlobalString(const char * tag, const char * var)
{
	lua_pushstring(L, var);
	lua_setglobal(L, tag);

	lua_pop(L, 1);
}

LUAEngine::LUAEngine()
{
	L = lua_open();
	luaL_openlibs(L);
}

LUAEngine::~LUAEngine()
{
	lua_close(L);
}

#include "FileSystem.h"
#include "Utility.h"

bool LUAEngine::Save(const char* filepath)
{
	if (!Load(filepath))
		return false;

	FileSystem* file = FileSystem::Instance();

	vector<string> lines = file->GetLines(filepath);

	vector<string> newlines;
	newlines.reserve(lines.size());

	for (auto& line : lines)
	{
		string tag = GetTag(line);

		if (!IsString(line))
			newlines.push_back(tag + " = " + ToString(GetGlobalNumber(tag.c_str())));
		else
			newlines.push_back(tag + " = " + "\"" + GetGlobalString(tag.c_str()) + "\"");
	}

	ofstream* output = file->BeginWriting(filepath);

	for (auto& line : newlines)
		*output << line << endl;

	file->EndWriting();

	return true;
}

bool LUAEngine::IsString(const string & line)
{
	for (int i = 0; i < line.size(); ++i)
	{
		if (line[i] == '"')
			return true;
	}

	return false;
}

string LUAEngine::GetTag(const string & line)
{
	string tag;

	for (int i = 0; i < line.size(); ++i)
	{
		if (line[i] == ' ')
			return tag;

		tag += line[i];
	}

	return tag;
}
