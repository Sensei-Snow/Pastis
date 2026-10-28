#include <windows.h>
#include <stdio.h>

#include "clipboard.h"

/*
 * Lecture du texte présent dans le presse-papiers Windows.
 * On ouvre d'abord l'accès au clipboard, puis on récupère le contenu au format Unicode.
 * Si l'ouverture ou la lecture échoue, on renvoie un état d'erreur ou d'avertissement.
 */
StateCodeProcess getClipboardText(wchar_t *text, size_t size)
{
    /*
     * On demande l'accès exclusif au presse-papiers pour éviter qu'un autre programme
     * n'écrive pendant que l'on lit les données.
     */
    if (!OpenClipboard(NULL)) {
        return STATE_ERROR;
    }

    /*
     * On récupère le bloc de données Unicode disponible dans le clipboard.
     * CF_UNICODETEXT correspond au format texte UTF-16 utilisé par Windows.
     */
    HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);

    /*
     * Si aucun texte n'est disponible, on ferme proprement le clipboard et on signale
     * un état warning, car la lecture a été impossible sans être fatale pour le programme.
     */
    if (hClipboardData == NULL) {
        CloseClipboard();
        return STATE_WARNING;
    }

    /*
     * Le pointeur obtenu par GetClipboardData n'est pas directement utilisable comme un buffer
     * tampon normal ; il faut le verrouiller pour accéder à la mémoire Windows.
     */
    wchar_t *clipboardText = GlobalLock(hClipboardData);

    /*
     * En cas d'échec du verrouillage, on libère les ressources et on quitte proprement.
     */
    if (clipboardText == NULL) {
        GlobalUnlock(hClipboardData);
        CloseClipboard();
        return STATE_WARNING;
    }

    /*
     * On copie le texte dans le buffer fourni par l'appelant, en limitant la copie à la taille
     * disponible pour éviter un débordement de mémoire. _TRUNCATE force la troncature sécurisée.
     */
    wcsncpy_s(text, size, clipboardText, _TRUNCATE);

    /*
     * On libère le verrou et on ferme le clipboard pour rendre les ressources disponibles.
     */
    GlobalUnlock(hClipboardData);
    CloseClipboard();

    return STATE_OK;
}

/*
 * Écriture du texte dans le presse-papiers Windows.
 * Le code vide d'abord le clipboard, puis alloue une zone mémoire Windows pouvant accueillir
 * le texte en UTF-16, avant de la publier dans le système.
 */
StateCodeProcess setClipboardText(wchar_t *text, size_t size) {
    /*
     * On demande l'accès exclusif au presse-papiers pour éviter qu'un autre programme
     * n'écrive pendant que l'on lit les données.
     */
    if (!OpenClipboard(NULL)) {
        return STATE_ERROR;
    }

    /*
     * EmptyClipboard supprime tout contenu précédent pour éviter de fusionner des données obsolètes.
     * Si la vidange échoue, on clôt la session proprement.
     */
    if (!EmptyClipboard()) {
        CloseClipboard();
        return STATE_WARNING;
    }

    /*
     * On alloue une mémoire globale Windows, de taille suffisante pour stocker le texte.
     * Cette mémoire est destinée au clipboard et doit rester accessible au système.
     */
    HGLOBAL hMemory = GlobalAlloc(GMEM_MOVEABLE, size);

    /*
     * Si l'allocation échoue, le clipboard est déjà vide mais la mise à jour ne peut pas être faite.
     */
    if (hMemory == NULL) {
        CloseClipboard();
        return STATE_WARNING;
    }

    /*
     * On verrouille la mémoire allouée pour obtenir un pointeur exploitable en écriture.
     */
    wchar_t *ptr = GlobalLock(hMemory);

    /*
     * Si le verrouillage échoue, on libère la mémoire allouée pour éviter une fuite.
     */
    if (ptr == NULL) {
        GlobalFree(hMemory);
        CloseClipboard();
        return STATE_WARNING;
    }

    /*
     * On copie exactement le texte dans la mémoire du clipboard avant de la publier.
     * Le paramètre size détermine la quantité de bytes à transférer.
     */
    memcpy(ptr, text, size);
    GlobalUnlock(hMemory);

    /*
     * Enregistrement du bloc mémoire dans le clipboard au format Unicode.
     * Si SetClipboardData échoue, on libère la mémoire car elle n'a pas été validée par Windows.
     */
    HANDLE hClipboardData = SetClipboardData(CF_UNICODETEXT, hMemory);

    if (hClipboardData == NULL) {
        GlobalFree(hMemory);
        CloseClipboard();
        return STATE_WARNING;
    }

    /*
     * Le contenu a bien été enregistré, on ferme le presse-papiers proprement.
     */
    CloseClipboard();
    return STATE_OK;
}