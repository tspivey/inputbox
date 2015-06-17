#define _UNICODE
#define UNICODE
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

struct DialogInfo {
	TCHAR *title;
	TCHAR *caption;
	TCHAR *result;
	TCHAR *default;
};

BOOL CALLBACK dlgproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HINSTANCE hinstance = NULL;

BOOL APIENTRY DllMain(HANDLE module, DWORD reason, LPVOID reserved)
{
	hinstance = (HINSTANCE)module;
	return TRUE;
}

extern "C" __declspec(dllexport) TCHAR *InputBox(TCHAR *title, TCHAR *caption, TCHAR *default)
{
	DialogInfo *info = (DialogInfo *)malloc(sizeof(DialogInfo));
	memset(info, 0, sizeof(DialogInfo));
	info->title = title;
	info->caption = caption;
	info->default = default;
	DialogBoxParam((HINSTANCE)hinstance, MAKEINTRESOURCE(1001), NULL, dlgproc, (LPARAM)info);
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
		if (info->default) {
			SendDlgItemMessage(hwnd, 101, WM_SETTEXT, 0, (LPARAM)(info->default));
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

extern "C" __declspec(dllexport) void free_string(TCHAR *s)
{
	free(s);
}
