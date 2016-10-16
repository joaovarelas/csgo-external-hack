#pragma once
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <TlHelp32.h>
#include <iostream>

DWORD dwClient, dwEngine;

// Y3t1y3t/CSGO-Dumper to update offsets
const DWORD dwLocalPlayer = 0xA8C53C;
const DWORD dwEntityList = 0x4AADC64;
const DWORD m_iCrosshairID = 0xAA64;

const DWORD dwEntityIndex = 0x64;
const DWORD entityJump = 0x10;
const DWORD m_fFlags = 0x100;
const DWORD m_lifeState = 0x25B;
const DWORD m_iTeam = 0xF0;
const DWORD m_bSpotted = 0x939; //radarh4x


class funcoes{
private:
	HANDLE _processo;
	DWORD _pid;
public:
	bool hook(char* processo);
	DWORD modulo(char* modulo);
	DWORD ler(DWORD endereco);
	void escrever(DWORD address, int value);
};
funcoes funcs;


class player_t{
public:
	DWORD localp;
	int flag;
	int equipa;
	int chid;
	void info();
};
player_t player;


class entlist_t{
public:
	DWORD basent;
	int flag;
	int equipa;
	int bSpotted;
	void info(int player);
};
entlist_t entlist[32];


// github.com/joaovarelas
// unknowncheats.me
// mpgh.net