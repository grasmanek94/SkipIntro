/*
	Startup GTA V Faster (Disable/Skip Intro & Legal Messages)

	Saves 30 Seconds of your life each time you run GTA V

	Copyright (c) 2015 - Rafa³ 'grasmanek94/Gamer_Z' Grasman

	License: MIT

	grasmanek94 at gmail dot com
*/

#include <Windows.h>
#include <Psapi.h>

#pragma comment(lib, "Psapi.lib")

bool memory_compare(const BYTE *data, const BYTE *pattern, const char *mask)
{
	for (; *mask; ++mask, ++data, ++pattern)
	{
		if (*mask == 'x' && *data != *pattern)
			return false;
	}
	return (*mask) == NULL;
}

UINT64 FindPattern(char *pattern, char *mask)
{	//Edited, From YSF by Kurta999
	UINT64 i;
	UINT64 size;
	UINT64 address;

	MODULEINFO info = { 0 };

	address = (UINT64)GetModuleHandle(NULL);
	GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &info, sizeof(MODULEINFO));
	size = (UINT64)info.SizeOfImage;

	for (i = 0; i < size; ++i)
	{
		if (memory_compare((BYTE *)(address + i), (BYTE *)pattern, mask))
		{
			return (UINT64)(address + i);
		}
	}
	return 0;
}

void DisableRockstarLogos()
{
	UINT64 logos = FindPattern("platform:/movies/rockstar_logos", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	if (logos != 0)
	{
		memset((void*)(logos + 0x11), 0x00, 0x0E);
	}
}

void DisableLegalMessagesCompletely()
{	
	UINT64 address = FindPattern("\x72\x1F\xE8\x12\x8D\xFB\x00\x8B\x0D\x34\x7F\xC3\x01\xFF\xC1\x48","xxx???xxx???xxxx");

	if (address != 0)
	{
		unsigned long dwProtect;
		unsigned long dwProtect2;

		VirtualProtect((LPVOID)address, 2, PAGE_EXECUTE_READWRITE, &dwProtect);
		*(unsigned short*)(address) = 0x9090;
		VirtualProtect((LPVOID)address, 2, dwProtect, &dwProtect2);
	}
}

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableRockstarLogos();
		DisableLegalMessagesCompletely();
		break;
	case DLL_PROCESS_DETACH:
		break;
	}		
	return TRUE;
}
