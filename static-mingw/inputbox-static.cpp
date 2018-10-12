/*
Statically-linkable mingw version of inputbox.cpp
Author: Yukio Nozawa <personal@nyanchangames.com>
*/

#define UNICODE
#include <windows.h>
#include "inputbox-static.h"

struct DialogInfo {
	TCHAR *title;
	TCHAR *caption;
	TCHAR *result;
	TCHAR *defaultText;
};

BOOL CALLBACK dlgproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

TCHAR *InputBox(const TCHAR *title, const TCHAR *caption, const TCHAR *defaultText)
{
	DialogInfo *info = (DialogInfo *)malloc(sizeof(DialogInfo));
	memset(info, 0, sizeof(DialogInfo));
	info->title = const_cast<TCHAR*>(title);
	info->caption = const_cast<TCHAR*>(caption);
	info->defaultText = const_cast<TCHAR*>(defaultText);
	DialogBoxParam((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(1001), NULL, dlgproc, (LPARAM)info);
	TCHAR *text = info->result;
	free(info);
	return text;
}

BOOL CALLBACK dlgproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	DialogInfo *info = (DialogInfo *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	switch (message) {
	case WM_INITDIALOG:
		info = (DialogInfo *)lParam;
		SetWindowText(hwnd, info->title);
		if (info->caption) {
			SetWindowText(GetDlgItem(hwnd, 102), info->caption);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (INT_PTR)info);
		if (info->defaultText) {
			SendDlgItemMessage(hwnd, 101, WM_SETTEXT, 0, (LPARAM)(info->defaultText));
		}
		return TRUE;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			info->result = (TCHAR *)malloc(sizeof(TCHAR) * 1024);
			GetDlgItemText(hwnd, 101, info->result, 1024);
			EndDialog(hwnd, 0);
			return TRUE;
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			return TRUE;
		}
		return TRUE;
		break;
	}
	return FALSE;
}

void free_string(TCHAR *s)
{
	free(s);
}
