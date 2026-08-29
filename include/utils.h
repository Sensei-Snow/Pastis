#ifndef PASTIS_UTILS_H
    #define PASTIS_UTILS_H

    typedef enum {
        STATE_OK,
        STATE_WARNING,
        STATE_ERROR
    } StateCodeProcess;

    size_t getStringSize(wchar_t *text);

#endif
