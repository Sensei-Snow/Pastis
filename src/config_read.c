#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "config_read.h"
#include "crypto.h"
#include "utils.h"
#include "../lib/ini.h"

static int config_read_handler(void *user, const char *section, const char *name, const char *value)
{
    (void)user;

    if (strcmp(section, "Wallet") != 0)
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

        while (value[i] != '\0' && i < capacity - 1) {
            unsigned char c = (unsigned char)value[i];

            if (c > 127)
                return 0;

            destination[i] = (wchar_t)c;
            i++;
        }

        if (value[i] != '\0')
            return 0;

        destination[i] = L'\0';
    }

    return 1;
}

StateCodeProcess config_read(const char *filename)
{
    int error = ini_parse(filename, config_read_handler, NULL);

    if (error < 0) {
        fprintf(stderr, "Impossible d'ouvrir %s\n", filename);
        return STATE_ERROR;
    }

    if (error > 0) {
        fprintf(stderr, "Erreur INI à la ligne %d\n", error);
        return STATE_ERROR;
    }

    return STATE_OK;
}