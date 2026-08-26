#ifndef PASTIS_CLIPBOARD_H
    #define PASTIS_CLIPBOARD_H

    #include <windows.h>

    typedef enum {
        STATE_OK,
        STATE_WARNING,
        STATE_ERROR
    } StateCode;

    StateCode getClipboardText(wchar_t *text, size_t size);
    BOOL setClipboardText(wchar_t *text, size_t size);

#endif
