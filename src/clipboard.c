#include <windows.h>
#include <stdio.h>

#include "clipboard.h"

StateCode getClipboardText(wchar_t *text, size_t size)
{
    if (!OpenClipboard(NULL)) {
        return STATE_ERROR;
    }

    HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);

    if (hClipboardData == NULL) {
        CloseClipboard();
        return STATE_WARNING;
    }

    wchar_t *clipboardText = GlobalLock(hClipboardData);

    if (clipboardText == NULL) {
        GlobalUnlock(hClipboardData);
        CloseClipboard();
        return STATE_WARNING;
    }

    wcsncpy_s(text, size, clipboardText, _TRUNCATE);

    GlobalUnlock(hClipboardData);
    CloseClipboard();

    return STATE_OK;
}

BOOL setClipboardText(wchar_t *text, size_t size) {
    if (!OpenClipboard(NULL)) {
        return FALSE;
    }

    if (!EmptyClipboard()) {
        CloseClipboard();
        return FALSE;
    }

    HGLOBAL hMemory = GlobalAlloc(GMEM_MOVEABLE, size);

    if (hMemory == NULL) {
        CloseClipboard();
        return FALSE;
    }

    wchar_t *ptr = GlobalLock(hMemory);

    if (ptr == NULL) {
        GlobalFree(hMemory);
        CloseClipboard();
        return FALSE;
    }

    memcpy(ptr, text, size);
    GlobalUnlock(hMemory);

    HANDLE hClipboardData = SetClipboardData(CF_UNICODETEXT, hMemory);

    if (hClipboardData == NULL) {
        GlobalFree(hMemory);
        CloseClipboard();
        return FALSE;
    }

    CloseClipboard();
    return TRUE;
}