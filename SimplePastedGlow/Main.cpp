
#include "DriverAndUtility.h"
#include "Offsets.h"
#include "XorStr.hpp"



//a majority of this code is credit to $urge got tapped. East Arctica also helped me a little with the glow

//if I forgot any credits leave an issue on the github so I can include them
int main() 
{
	Driver.Init();
	

	uint64_t process_id = GetPid(xorstr_(L"r5apex.exe"));
	if (!process_id) 
	{
		std::cout << xorstr_("nyoo proc id failerd");
		Sleep(69420);
		return -2;
	}
	std::cout << process_id << std::endl;
	
	uint64_t base_address = Driver.GetModuleBase(process_id);
	if (!base_address) 
	{
		std::cout << xorstr_("nyoo bas drrdaress failerd");
		Sleep(69420);
		return -1;
	}
	std::cout << base_address << std::endl;


	while (true)
	{
		for (int i = 0; i < 100; i++)
		{
			DWORD64 Entity = GetEntityById(i, base_address);
			if (Entity == 0)
				continue;
			DWORD64 EntityHandle = Driver.rpm<DWORD64>(Entity + 0x589); //determines if player
			std::string Identifier = Driver.ReadString(EntityHandle);
			LPCSTR IdentifierC = Identifier.c_str();
			
			if (strcmp(IdentifierC, xorstr_("player"))) //if player do glow
			{
				Driver.wpm<int>(Entity + 0x3C8, 1); //some glow shit EA gave me
				Driver.wpm<int>(Entity + 0x3D0, 2); //some glow shit EA gave me
				Driver.wpm<GlowMode>(Entity + 0x2C4, { 101,101,46,90 }); //glow mode
				Driver.wpm<float>(Entity + 0x1D0, 61.f); //r
				Driver.wpm<float>(Entity + 0x1D4, 2.f); //g
				Driver.wpm<float>(Entity + 0x1D8, 2.f); //b
			}
		}
		Sleep(10);
	}
}
