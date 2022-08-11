#include <sys/errno.h>
#include <sys/stat.h>

#include "stx7105.h"

#define CONSOLE_ASC ASC2

#define HEAP_SIZE 0x10000

extern char     _end;
static uint32_t s_heap_size = 0U;

caddr_t _sbrk(int incr) {
    char *heap_base = &_end;

    caddr_t ret = heap_base + s_heap_size;

    if (s_heap_size + incr >= HEAP_SIZE) {
        return (void *)(-ENOMEM);
    }

    s_heap_size += incr;

    return ret;
}

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        if (ptr[i] == '\n') {
            while (CONSOLE_ASC->STA & 1 << 9U) {
                // wait for TX FIFO slot.
            }
            CONSOLE_ASC->TX_BUF = '\r';
        }

        while (CONSOLE_ASC->STA & 1 << 9U) {
            // wait for TX FIFO slot.
        }
        CONSOLE_ASC->TX_BUF = ptr[i];
    }
    return len;
}

int _open(const char *name, int flags, int mode) {
    return -1;
}

int _read(int file, char *ptr, int len) {
    return 0;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _close(int file) {
    return -1;
}

int _isatty(int file) {
    return -1;
}

pid_t _getpid(void) {
    return -1;
}

void _kill(int pid, int sig) {
    return;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}
