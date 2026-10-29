/*
 * @file        config_read.h
 * @see         config_read.c
 * @author      $now_
 * @updated     29/10/2026
 * @brief       Fichier d'en-tête pour l'implémentation de la lecture des fichiers de configuration en ".ini".
 */

#ifndef PASTIS_CONFIG_READ_H
    #define PASTIS_CONFIG_READ_H

    #include "crypto.h"
    #include "utils.h"

    StateCodeProcess config_read(const char *filename);

#endif
