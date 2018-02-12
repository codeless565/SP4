#include "LuaInterface.h"
#include <iostream>
#include <string>
using namespace std;

// Allocating and initializing LuaInterface's static data member
// The pointer is allocated but not the object's constructor

LuaInterface *LuaInterface::s_instance = 0;

LuaInterface::LuaInterface()
	:theLuaState(NULL),
	theErrorState(NULL),
	theOptionState(NULL),
	theHSState(NULL)
{
}

LuaInterface::~LuaInterface()
{
}


// Initialisation of the Lua Interface Class
bool LuaInterface::Init()
{
	bool result = false;

	// 1. Create lua state
	theLuaState = lua_open();

	if (theLuaState)
	{
		// 2. Load lua auxiliary libraries
		luaL_openlibs(theLuaState);

		// 3. Load lua script
		luaL_dofile(theLuaState, "Image//DM2240.lua");

		result = true;
	}

	theErrorState = lua_open();

	if (theErrorState)
	{
		// 2. Load lua auxiliary libraries
		luaL_openlibs(theErrorState);

		// 3. Load lua script
		luaL_dofile(theErrorState, "Image//errorLookup.lua");

		result = true;
	}

	theOptionState = lua_open();

	if (theOptionState)
	{
		// 2. Load lua auxiliary libraries
		luaL_openlibs(theOptionState);

		// 3. Load lua script
		luaL_dofile(theOptionState, "Image//Options.lua");

		result = true;
	}

	theHSState = lua_open();

	if (theHSState)
	{
		// 2. Load lua auxiliary libraries
		luaL_openlibs(theHSState);

		// 3. Load lua script
		luaL_dofile(theHSState, "Image//DM2240_HighScore.lua");

		result = true;
	}

	//if (WaypointFile)
	//{
	//	// 2. Load lua auxiliary libraries
	//	luaL_openlibs(WaypointFile);

	//	// 3. Load lua script
	//	luaL_dofile(WaypointFile, "Image//DM2240_WayPoints.lua");

	//	result = true;
	//}

	return result;
}

// Run the Lua Interface Class
void LuaInterface::Run()
{
	if (theLuaState == NULL)
		return;

	// 4. Read the variables
	// lua_getglobal(lua_State*, const char*)
	lua_getglobal(theLuaState, "title");
	// extract value, index -1 as variable is already retrieved using lua_getglobal
	const char *title = lua_tostring(theLuaState, -1);

	lua_getglobal(theOptionState, "width");
	int width = lua_tointeger(theOptionState, -1);

	lua_getglobal(theOptionState, "height");
	int height = lua_tointeger(theOptionState, -1);

	// Display on screen
	cout << title << endl;
	cout << "-----------------------------------------" << endl;
	cout << "Width of screen : " << width << endl;
	cout << "Height of screen : " << height << endl;
}

void LuaInterface::Drop()
{
	// Close the lua state
	if (theLuaState)
		lua_close(theLuaState);

	// Close the lua state
	if (theErrorState)
		lua_close(theErrorState);

	// Close the lua state
	if (theOptionState)
		lua_close(theOptionState);

	// Close the lua state
	if (theHSState)
		lua_close(theHSState);
}

int LuaInterface::getIntValue(const char * varName)
{
	lua_getglobal(theLuaState, varName);
	int tempValue = lua_tointeger(theLuaState, -1);
	return tempValue;
}

float LuaInterface::getFloatValue(const char * varName)
{
	lua_getglobal(theLuaState, varName);
	float tempValue = lua_tonumber(theLuaState, -1);
	return tempValue;
}

bool LuaInterface::getBooleanValue(const char* varName)
{
	lua_getglobal(theLuaState, varName);
	bool tempValue = lua_toboolean(theLuaState, -1);
	return tempValue;
}

char LuaInterface::getcharValue(const char * varName)
{
	lua_getglobal(theLuaState, varName);

	size_t len;
	const char* cstr = lua_tolstring(theLuaState, -1, &len);
	// if the string is not empty, then return the first char
	if (len > 0)
		return cstr[0];
	// else return a default value of <SPACE>
	else
		return ' ';
}

Vector3 LuaInterface::getVector3Values(const char * varName)
{
	lua_getglobal(theLuaState, varName);
	lua_rawgeti(theLuaState, -1, 1);
	int x = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);
	lua_rawgeti(theLuaState, -1, 2);
	int y = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);
	lua_rawgeti(theLuaState, -1, 3);
	int z = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);

	return Vector3(x, y, z);
}

void LuaInterface::saveIntValue(const char * varName, int value, bool overwrite)
{
	std::string temp = varName;
	temp.append(" = ");
	temp.append(std::to_string(value));
	temp.append("\n");

	if (theLuaState)
	{
		lua_getglobal(theLuaState, "SaveToLuaFile");
		lua_pushstring(theLuaState, temp.c_str());
		lua_pushinteger(theLuaState, overwrite);
	}
	lua_call(theLuaState, 2, 0);
}

void LuaInterface::saveFloatValue(const char * varName, float value, bool overwrite)
{
	std::string temp = varName;
	temp.append(" = ");
	temp.append(std::to_string(value));
	temp.append("\n");

	if (theLuaState)
	{
		lua_getglobal(theLuaState, "SaveToLuaFile");
		lua_pushstring(theLuaState, temp.c_str());
		lua_pushinteger(theLuaState, overwrite);
	}
	lua_call(theLuaState, 2, 0);
}

void LuaInterface::saveBooleanValue(const char * varName, bool value, bool overwrite)
{
	std::string temp = varName;
	temp.append(" = ");
	temp.append(std::to_string(value));
	temp.append("\n");

	if (theLuaState)
	{
		lua_getglobal(theLuaState, "SaveToLuaFile");
		lua_pushstring(theLuaState, temp.c_str());
		lua_pushinteger(theLuaState, overwrite);
	}
	lua_call(theLuaState, 2, 0);
}

char LuaInterface::getKeyBoardValue(const char * varName)
{
	lua_getglobal(theOptionState, varName);

	size_t len;
	const char* cstr = lua_tolstring(theOptionState, -1, &len);
	// if the string is not empty, then return the first char
	if (len > 0)
		return cstr[0];
	// else return a default value of <SPACE>
	else
		return ' ';
}

void LuaInterface::saveKeyBoardValue(const char * varName, char value, bool overwrite)
{
	std::string temp = varName;
	temp.append(" = \"");
	temp += value;
	temp.append("\"\n");

#ifdef DEBUG
	cout << temp << endl;
#endif

	if (theLuaState)
	{
		lua_getglobal(theLuaState, "SaveToOptionsFile");
		lua_pushstring(theLuaState, temp.c_str());
		lua_pushinteger(theLuaState, overwrite);
	}
	lua_call(theLuaState, 2, 0);
}

int LuaInterface::getOptionsValue(const char * varName)
{
	lua_getglobal(theOptionState, varName);
	int tempValue = lua_tointeger(theOptionState, -1);
	return tempValue;

}

void LuaInterface::saveOptionsValue(const char * varName, int value, bool overwrite)
{
	std::string temp = varName;
	temp.append(" = ");
	temp.append(std::to_string(value));
	temp.append("\n");

	if (theLuaState)
	{
		lua_getglobal(theLuaState, "SaveToOptionsFile");
		lua_pushstring(theLuaState, temp.c_str());
		lua_pushinteger(theLuaState, overwrite);
	}
	lua_call(theLuaState, 2, 0);
}

int LuaInterface::getHSValue(const char * varName)
{
	lua_getglobal(theHSState, varName);
	int tempValue = lua_tointeger(theHSState, -1);
	return tempValue;
}

Vector3 LuaInterface::getWaypointPos(const char * varName)
{
	lua_getglobal(WaypointFile, varName);
	float x = getField("x");
	float y = getField("y");
	float z = getField("z");

	return Vector3(x, y, z);
}

float LuaInterface::getDistanceSquareValue(Vector3 source, Vector3 destination)
{
	lua_getglobal(theLuaState, "CalculateDistanceSquare");
	lua_pushnumber(theLuaState, source.x);
	lua_pushnumber(theLuaState, source.y);
	lua_pushnumber(theLuaState, source.z);
	lua_pushnumber(theLuaState, destination.x);
	lua_pushnumber(theLuaState, destination.y);
	lua_pushnumber(theLuaState, destination.z);
	lua_call(theLuaState, 6, 1);
	float distanceSquare = (float)lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);
	return distanceSquare;

}

int LuaInterface::getVariableValues(const char * varName, int & a, int & b, int & c, int & d)
{
	lua_getglobal(theLuaState, varName);
	lua_pushnumber(theLuaState, a);
	lua_pushnumber(theLuaState, b);
	lua_pushnumber(theLuaState, c);
	lua_pushnumber(theLuaState, d);
	lua_call(theLuaState, 4, 4);
	a = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);
	b = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);
	c = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);
	d = lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);

	return true;
}

float LuaInterface::getField(const char * key)
{
	int result;
	if (!lua_istable(theLuaState, -1))  // if the pointer is not pointing to a table
		error("error100");

	lua_pushstring(theLuaState, key);
	lua_gettable(theLuaState, -2);

	if (!lua_isnumber(theLuaState, -1)) // if return from table is not a number
		error("error101");

	result = (int)lua_tonumber(theLuaState, -1);
	lua_pop(theLuaState, 1);// remove number
	return result;
}

void LuaInterface::error(const char * errorCode)
{
	if (theErrorState == NULL)
		return;

	lua_getglobal(theErrorState, errorCode);
	const char* errorMsg = lua_tostring(theErrorState, -1);
	if (errorMsg != NULL)
		cout << errorMsg << endl;
	else
		cout << errorCode << " is not value. \n Please contact the developer. " << endl;
}