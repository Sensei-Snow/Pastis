#include <windows.h>
#include <stdio.h>

#include "clipboard.h"

StateCodeProcess getClipboardText(wchar_t *text, size_t size)
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

StateCodeProcess setClipboardText(wchar_t *text, size_t size) {
    if (!OpenClipboard(NULL)) {
        return STATE_ERROR;
    }

    if (!EmptyClipboard()) {
        CloseClipboard();
        return STATE_WARNING;
    }

    HGLOBAL hMemory = GlobalAlloc(GMEM_MOVEABLE, size);

    if (hMemory == NULL) {
        CloseClipboard();
        return STATE_WARNING;
    }

    wchar_t *ptr = GlobalLock(hMemory);

    if (ptr == NULL) {
        GlobalFree(hMemory);
        CloseClipboard();
        return STATE_WARNING;
    }

    memcpy(ptr, text, size);
    GlobalUnlock(hMemory);

    HANDLE hClipboardData = SetClipboardData(CF_UNICODETEXT, hMemory);

    if (hClipboardData == NULL) {
        GlobalFree(hMemory);
        CloseClipboard();
        return STATE_WARNING;
    }

    CloseClipboard();
    return STATE_OK;
}