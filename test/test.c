#include <stdio.h>

#include "clipboard.h"
#include "utils.h"

void testClipboardRead(void) {
    size_t size = 256;
    wchar_t buffer[size];

    if (getClipboardText(buffer, size)) {
        wprintf(L"%ls\n", buffer);
    } else {
        printf("[ERROR] -- Failed to get clipboard text.\n");
    }
}

void testClipboardWrite(void) {
    const wchar_t *text = L"[DEBUG] -- This is a test message.";
    size_t size = getStringSize(text);

    if (setClipboardText(text, size)) {
        printf("[INFO] -- Text copied to clipboard successfully.\n");
    } else {
        printf("[ERROR] -- Failed to set clipboard text.\n");
    }
}