/*
 * @file        utils.h
 * @see         utils.c
 * @author      $now_
 * @updated     29/10/2026
 * @brief       Fichier d'en-tête pour l'implémentation des fonctions utilitaires.
 */

#ifndef PASTIS_UTILS_H
    #define PASTIS_UTILS_H

    #define ADDRESS_SIZE 256

    typedef enum {
        STATE_OK,
        STATE_WARNING,
        STATE_ERROR
    } StateCodeProcess;

    size_t getStringSize(wchar_t *text);

#endif
