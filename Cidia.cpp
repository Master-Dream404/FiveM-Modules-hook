#include "cidia.hpp"

namespace Modules
{
	namespace net
	{
		auto module = GetModuleHandleA("net.dll");
	}
	namespace CitizenGame
	{
		auto module = GetModuleHandleA("CitizenGame.dll");
	}
	namespace scripthookv
	{
		auto module = GetModuleHandleA("scripthookv.dll");
	}
	namespace citizen_resources_core
	{
		auto module = GetModuleHandleA("citizen-resources-core.dll");
	}
}

void net::SetPlayerName(const char* new_name) {
	rSetName SetPlayerName = reinterpret_cast<rSetName>(GetProcAddress(Modules::net::module, "?SetPlayerName@NetLibrary@@UEAAXPEBD@Z"));
	SetPlayerName(new_name);
}
int net::GetPort() {
	nGetPort GetPort = reinterpret_cast<nGetPort>(GetProcAddress(Modules::net::module, "?GetPort@NetAddress@@QEAAHXZ"));
	return GetPort();
}
std::string net::GetAddress() {
	nGetAddress GetAddress = reinterpret_cast<nGetAddress>(GetProcAddress(Modules::net::module, "?GetAddress@NetAddress@@QEAA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ"));
	return GetAddress();
}
std::string net::GetWAdress()
{
	nGetAddress GetWAddress = reinterpret_cast<nGetAddress>(GetProcAddress(Modules::net::module, "?GetWAddress@NetAddress@@QEAA?AV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@XZ"));
	return GetWAddress();
}
const char* net::GetPlayerName() {
	nGetPlayerName GetPlayerName = reinterpret_cast<nGetPlayerName>(GetProcAddress(Modules::net::module, "?GetPlayerName@NetLibrary@@UEAAPEBDXZ"));
	return GetPlayerName();
}
int CitizenGame::GetGameVersion()
{
	cGetGameVersion GetGameVersion = reinterpret_cast<cGetGameVersion>(GetModuleHandle(L"CitizenGame.dll") + 0x101BA);//75 0B E8 ? ? ? ? or 83 F8 FF 75 0B 
	return GetGameVersion();
}
void scripthookv::ScriptRegister(HMODULE hMod, void(*function)()) {
	sScriptRegister ScriptRegister = reinterpret_cast<sScriptRegister>(GetProcAddress(Modules::scripthookv::module, "?scriptRegister@@YAXPEAUHINSTANCE__@@P6AXXZ@Z"));
	ScriptRegister(hMod, function);
}
int scripthookv::WorldGetAllVehicles() {
	sWorldGetAllVehicles WorldGetAllVehicles = reinterpret_cast<sWorldGetAllVehicles>(GetModuleHandle(L"scripthookv.dll") + 0x2741D);// 
	return WorldGetAllVehicles();
}
/*
else
int scripthookv::WorldGetAllVehicles(int a1) {
	sWorldGetAllVehicles WorldGetAllVehicles = reinterpret_cast<sWorldGetAllVehicles>(GetProcAddress(Modules::net::module, "?worldGetAllVehicles@@YAHPEAHH@Z"));
	return WorldGetAllVehicles(a1);
}

*/
void scripthookv::NativeCallContext(unsigned __int64 cxt, uint64_t hash) {
	auto hooked_NativeHandler = GetProcAddress(Modules::scripthookv::module, "?GetNativeHandler@scrEngine@rage@@SAP6AXPEAVscrNativeCallContext@2@@Z_K@Z");

	NativeHandler fn = ((GetNativeHandler_t)(hooked_NativeHandler))(hash);

	if (fn != 0)
	{
		//unsigned __fastcall* create_cxt = fn(*(unsigned __int64*)cxt);
		fn(cxt);
	}
}

Resource_Manager_Class* citizen_resources_core::CreateResourceManager()
{
	auto manager = GetProcAddress(Modules::citizen_resources_core::module, "?CreateResourceManager@fx@@YAPEAVResourceManager@1@XZ");

	return (Resource_Manager_Class*)manager;
}

void thx_master_dream()
{
	auto hook = new citizen_resources_core();
	auto new_manager = hook->CreateResourceManager();
	new_manager->CreateResource("test", NULL)->LoadFrom("C:\\Master\\Dream");
	new_manager->GetResource("test")->Start();
}

net* m_cidia::Net()
{
	auto m_net = new net();
	return m_net;
}

CitizenGame* m_cidia::cCitizenGame()
{
	auto m_CitizenGame = new CitizenGame();
	return m_CitizenGame;
}

scripthookv* m_cidia::Cscripthookv()
{
	auto m_scripthookv = new scripthookv();
	return m_scripthookv;
}


