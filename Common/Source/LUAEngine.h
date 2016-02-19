#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <string>
using namespace::std;

#define LUA LUAEngine::Instance()

class LUAEngine
{
public:
	static LUAEngine& Instance();

	bool Load(const char* filepath);
	bool Save(const char* filepath);

	float GetGlobalNumber(const char* tag);
	void SetGlobalNumber(const char* tag, float var);

	string GetGlobalString(const char* tag);
	void SetGlobalString(const char* tag, const char* var);

private:
	LUAEngine();
	~LUAEngine();

	lua_State *L;
	string filepath;

	bool IsString(const string& line);
	string GetTag(const string& line);
};