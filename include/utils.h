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
