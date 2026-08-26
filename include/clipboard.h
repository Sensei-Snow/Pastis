#ifndef PASTIS_CLIPBOARD_H
    #define PASTIS_CLIPBOARD_H

    #include <windows.h>

    BOOL getClipboardText(wchar_t *text, size_t size);
    BOOL setClipboardText(wchar_t *text, size_t size);

#endif
