/*
 * @file        crypto.h
 * @see         crypto.c
 * @author      $now_
 * @updated     29/10/2026
 * @brief       Fichier d'en-tête pour les définitions des variables globales pour stocker les adresses de cryptomonnaies.
 */

#ifndef PASTIS_CRYPTO_H
    #define PASTIS_CRYPTO_H

    #include "utils.h"

    extern  wchar_t bitcoin_buffer[ADDRESS_SIZE];
    extern  wchar_t litecoin_buffer[ADDRESS_SIZE];
    extern  wchar_t cardano_buffer[ADDRESS_SIZE];

#endif
