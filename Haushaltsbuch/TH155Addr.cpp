#include "pch.hpp"
#include "TH155AddrDef.h"
#include "Haushaltsbuch.hpp"

#define MINIMAL_USE_PROCESSHEAPSTRING
#include "MinimalPath.hpp"

static int (WINAPI *func_TH155AddrStartup)(int, HWND, UINT);
static int (WINAPI *func_TH155AddrCleanup)();
static DWORD_PTR (WINAPI *func_TH155AddrGetParam)(int);
static TH155STATE (WINAPI *func_TH155AddrGetState)();

static const TH155CHARNAME s_charNames[] = {
	{ _T("����얲"), _T("�얲") },
	{ _T("���J������"), _T("������") },
	{ _T("�_�����"), _T("���") },
	{ _T("�����@"), _T("���@") },
	{ _T("�����z�s"), _T("�z�s") },
	{ _T("�L�����_�q"), _T("�_�q") },
	{ _T("�͏�ɂƂ�"), _T("�ɂƂ�") },
	{ _T("�Ö��n������"), _T("������") },
	{ _T("��c��}�~�]�E"), _T("�}�~�]�E") },
	{ _T("�`������"), _T("������") },
	{ _T("��؉ؐ�") , _T("�ؐ�") },
	{ _T("�������g"), _T("���g") },
	{ _T("�����j����"), _T("�j����") },
	{ _T("�F����俎q"), _T("俎q") },
	{ _T("���EU�E�C�i�o"), _T("���") },
	{ _T("�h���~�[�E�X�C�[�g"), _T("�h���~�[") },
	{ _T("��ߖ����V�q"), _T("�V�q") },
	{ _T("���_��"), _T("��") },
	{ _T("�ː_����"), _T("����") }
};

int TH155AddrInit(HWND callbackWnd, int callbackMsg)
{
	TCHAR TH155AddrPath[1024];
	g_settings.ReadString(_T("Path"), _T("TH155Addr"), _T("TH155Addr.dll"), TH155AddrPath, sizeof(TH155AddrPath));
	
	HMODULE TH155Addr = LoadLibrary(TH155AddrPath);
	if (TH155Addr == nullptr) {
		return 0;
	}

	*reinterpret_cast<FARPROC*>(&func_TH155AddrStartup) = GetProcAddress(TH155Addr, "TH155AddrStartup");
	*reinterpret_cast<FARPROC*>(&func_TH155AddrCleanup) = GetProcAddress(TH155Addr, "TH155AddrCleanup");
	*reinterpret_cast<FARPROC*>(&func_TH155AddrGetParam) = GetProcAddress(TH155Addr, "TH155AddrGetParam");
	*reinterpret_cast<FARPROC*>(&func_TH155AddrGetState) = GetProcAddress(TH155Addr, "TH155AddrGetState");
	if (func_TH155AddrStartup == nullptr || func_TH155AddrCleanup == nullptr || func_TH155AddrGetParam == nullptr || func_TH155AddrGetState == nullptr) {
		return 0;
	}

	return func_TH155AddrStartup(1, callbackWnd, callbackMsg) != 0;
}

int TH155AddrFinish()
{
	return func_TH155AddrCleanup != nullptr ? func_TH155AddrCleanup(): 0;
}

TH155STATE TH155AddrGetState()
{
	return func_TH155AddrGetState();
}

DWORD_PTR TH155AddrGetParam(int param)
{
	return func_TH155AddrGetParam(param);
}

const TH155CHARNAME * const TH155AddrGetCharName(int index)
{
	if (TH155AddrGetCharCount() <= index) return NULL;
	return &s_charNames[index];
}

int TH155AddrGetCharCount()
{
	return _countof(s_charNames);
}
