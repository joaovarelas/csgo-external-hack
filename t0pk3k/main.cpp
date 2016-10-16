#include "main.h"

bool funcoes::hook(char* processo){
	HANDLE PHANDLE = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 procENTRY;
	procENTRY.dwFlags = sizeof(procENTRY);
	do{
		if(!strcmp(procENTRY.szExeFile, processo)){
			_pid = procENTRY.th32ProcessID;
			CloseHandle(PHANDLE);
			_processo = OpenProcess(PROCESS_VM_READ, FALSE, _pid);
			return true;
		}
	}while(Process32Next(PHANDLE, &procENTRY));
	return false;
}

DWORD funcoes::modulo(char* modulo){
	HANDLE HModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _pid);
	MODULEENTRY32 modEntry;
	modEntry.dwSize = sizeof(modEntry);
	do{
		if(!strcmp(modEntry.szModule, modulo)){
			CloseHandle(HModule);
			return (DWORD)modEntry.modBaseAddr;
		}
	}while (Module32Next(HModule, &modEntry));
	return false;
}
DWORD funcoes::ler(DWORD endereco){
	DWORD valor;
	ReadProcessMemory(_processo, (DWORD*)endereco, &valor, sizeof(valor), NULL); 
	return valor;
}

void funcoes::escrever(DWORD address, int value){
	//WriteProcessMemory(_processo,(DWORD*)address, &value, sizeof(value), NULL); //write memory = vacation
}


void player_t::info(){
	localp = funcs.ler(dwClient + dwLocalPlayer);
	flag = funcs.ler(localp + m_fFlags);
	equipa = funcs.ler(localp + m_iTeam);
	chid = funcs.ler(localp + m_iCrosshairID);
}

void entlist_t::info(int player){
	basent = funcs.ler(dwClient + dwEntityList +(player*entityJump));
	flag = funcs.ler(basent + m_fFlags);
	equipa = funcs.ler(basent + m_iTeam);
	//bSpotted = funcs.ler(basent + m_bSpotted);
}

/*
void __fastcall bunny(){

//bhop
DWORD localp = funcs.ler(dwClient + dwLocalPlayer);
int iFlags = funcs.ler(localp + m_fFlags);

if(iFlags & (0x1 == 1)){
keybd_event(MapVirtualKey(VK_SPACE, 0), 0x39, 0, 0);
Sleep(20);
keybd_event(MapVirtualKey(VK_SPACE, 0), 0x39, KEYEVENTF_KEYUP, 0);

}
}
*/

void __fastcall trig(){
	//trigg
	player.info();
	for(int i=0;i<32;i++){
		entlist[i].info(i);
	}

	if(player.chid != 0 && player.chid > 0 && player.chid < 32 && entlist[player.chid-1].equipa != player.equipa){
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0,0,0);
		Sleep(10);
	}

}


BOOL APIENTRY DllMain( HMODULE hModule,
					  DWORD  ul_reason_for_call,
					  LPVOID lpReserved
					  )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		while(!funcs.hook("csgo.exe")){
			MessageBox(0,"failed to hook csgo.exe","error",0); // -> muli-byte character set <-
		}

		dwClient = funcs.modulo("engine.dll"); //-> client.dll <-

		MessageBox(0,"injected to client.dll","success",0);


		while(!GetAsyncKeyState(VK_END))
		{ 
			/*
			if(GetAsyncKeyState(VK_SPACE)&0x8000){
			bunny();
			}
			*/

			while(GetAsyncKeyState(VK_MENU)){ //triggerkey
				void trig(null); // -> trig(); <-
			}

			Sleep(30);
		}

		MessageBox(0,"panic key","bye",0);
		FreeLibraryAndExitThread(hModule, 0);
		exit(0);

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

