#pragma once
#include <Windows.h>
#include <string>
#include <vector>

class net
{
public:
	typedef void(__fastcall* rSetName)(const char*);
	typedef int(__fastcall* nGetPort)();
	typedef std::string(__fastcall* nGetAddress)();
	typedef const char*(__fastcall* nGetPlayerName)();
	void SetPlayerName(const char* new_client_name);
	int GetPort();
	std::string GetAddress();
	const char* GetPlayerName();
};

class CitizenGame
{
public:
	typedef int(__fastcall* cGetGameVersion)();
	int GetGameVersion();
};

class scripthookv
{
public:
	typedef void(__fastcall* sScriptRegister)(HMODULE hMod, void(*function)());
	typedef int(__fastcall* sWorldGetAllVehicles)(); //typedef int(__fastcall* sWorldGetAllVehicles)(int);
	typedef void(__cdecl* NativeHandler)(unsigned __int64 context);
	using GetNativeHandler_t = NativeHandler(__fastcall*)(__int64 hash);

	void ScriptRegister(HMODULE hMod, void(*function)());
	int WorldGetAllVehicles();
	void NativeCallContext(unsigned __int64 cxt, uint64_t hash);
};



class m_cidia
{
public:
	net* Net();
	CitizenGame* cCitizenGame();
	scripthookv* Cscripthookv();
};
