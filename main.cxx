/*
	Startup GTA V Faster (Disable/Skip Intro & Legal Messages)

	Saves 30 Seconds of your life each time you run GTA V

	Copyright (c) 2015 - Rafa³ 'grasmanek94/Gamer_Z' Grasman

	License: MIT

	grasmanek94 at gmail dot com
*/

#include <Windows.h>

//STEAM Build 372 Online 1.27
void SetLegalMessageShowtime(unsigned short showtime)
{
	*(unsigned short*)((UINT64)GetModuleHandleA(NULL) + 0x1AAE11C) = showtime;
}

void DisableLegalMessagesCompletely()
{
	UINT64 address = (UINT64)GetModuleHandleA(NULL) + 0x1A05CB;
	unsigned long dwProtect;
	VirtualProtect((LPVOID)address, 2, PAGE_EXECUTE_READWRITE, &dwProtect);
	*(unsigned short*)(address) = 0x9090;
}

void DisableRockstarLogos()
{
	UINT64 logos = (UINT64)GetModuleHandleA(NULL) + 0x1762039;
	memset((void*)logos, 0x00, 0x0E);
}

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableLegalMessagesCompletely();
		DisableRockstarLogos();
		SetLegalMessageShowtime(1);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}		
	return TRUE;
}

