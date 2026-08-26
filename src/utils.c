#include <windows.h>

size_t getStringSize(wchar_t *text) {
    return (wcslen(text) + 1) * sizeof(wchar_t);
}