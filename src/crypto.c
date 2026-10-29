/*
 * @file        crypto.c
 * @see         crypto.h
 * @author      $now_
 * @updated     29/10/2026
 * @brief       Contient les définitions des variables globales pour stocker les adresses de cryptomonnaies.
 */

#include <windows.h>

#include "crypto.h"
#include "utils.h"

wchar_t bitcoin_buffer[ADDRESS_SIZE];
wchar_t litecoin_buffer[ADDRESS_SIZE];
wchar_t cardano_buffer[ADDRESS_SIZE];