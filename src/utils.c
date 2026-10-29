/*
 * @file        utils.c
 * @see         utils.h
 * @author      $now_
 * @updated     29/10/2026
 * @brief       Fichier d'implémentation pour les fonctions utilitaires.
 */

#include <windows.h>

size_t getStringSize(wchar_t *text)
{
    return (wcslen(text) + 1) * sizeof(wchar_t);
}