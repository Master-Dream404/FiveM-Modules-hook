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


#include <EventCore.h>
#include <pplx/pplxtasks.h>

class Resource_Class
{
private:
	char pad_0001[96];
	char pad_0000[0x60]; //0x0000
public:
	std::string m_name;
	std::string m_rootPath;
	std::string name;
	std::string resource;

	inline bool LoadFrom(const std::string& rootPath)
	{
		return LoadFrom(rootPath, nullptr);
	}

	virtual bool LoadFrom(const std::string& rootPath, std::string* errorResult) = 0;

	virtual bool Start() = 0;

	virtual bool Stop() = 0;

	virtual void Run(std::function<void()>&& func) = 0;

	//virtual Resource_Manager_Class* GetManager() = 0;

};

class Resource_Manager_Class : public fwRefCountable
{
private:

public:
	virtual pplx::task<fwRefContainer<Resource_Class>> AddResource(const std::string& uri) = 0;

	virtual fwRefContainer<Resource_Class> GetResource(const std::string& identifier, bool withProvides = true) = 0;

	virtual void ForAllResources(const std::function<void(const fwRefContainer<Resource_Class>&)>& function) = 0;

	virtual void ResetResources() = 0;


	virtual void RemoveResource(fwRefContainer<Resource_Class> resource) = 0;

	virtual fwRefContainer<Resource_Class> CreateResource(const std::string& resourceName, int fak) = 0;

	virtual void Tick() = 0;

	virtual void MakeCurrent() = 0;

};

class citizen_resources_core
{
private:
	typedef void(__fastcall* rCreateResourceManager)(Resource_Manager_Class*);
public:
	Resource_Manager_Class* CreateResourceManager();
};



class m_cidia : public net
{
public:

};