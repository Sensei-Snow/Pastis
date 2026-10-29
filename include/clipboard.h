/*
 * @file        clipboard.h
 * @see         clipboard.c
 * @author      $now_
 * @updated     29/10/2026
 * @brief       Fichier d'en-tête pour l'implémentation de la gestion du presse-papiers Windows.
 */

#ifndef PASTIS_CLIPBOARD_H
    #define PASTIS_CLIPBOARD_H

    #include <windows.h>

    #include "utils.h"

    StateCodeProcess getClipboardText(wchar_t *text, size_t size);
    StateCodeProcess setClipboardText(wchar_t *text, size_t size);

#endif
