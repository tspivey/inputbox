#ifndef __INPUTBOX_H
#define __INPUTBOX_H
#include <windows.h>
TCHAR *InputBox(const TCHAR *ttl, const TCHAR *caption, const TCHAR *defaultText);
void free_string(TCHAR*);
#endif
