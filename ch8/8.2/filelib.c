#include <fcntl.h>
#include "syscalls.h"

#define PERMS 0666

FILE _iob[OPEN_MAX] = {
        { 0, (char *) 0, (char *) 0, { 1, 0, 0, 0, 0 }, 0 },    // stdin
        { 0, (char *) 0, (char *) 0, { 0, 1, 0, 0, 0 }, 1 },    // stdout
        { 0, (char *) 0, (char *) 0, { 0, 1, 1, 0, 0 }, 2 },    // stderr
};

void *malloc(size_t);
off_t lseek(int, off_t, int);
user_ssize_t read(int, void *, size_t);
user_ssize_t write(int, const void *, size_t);

// fileopen: open file, return file pointer
FILE *fileopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if (fp->flags.is_read == 0 && fp->flags.is_write == 0) { // found a free slot
            break;
        }
    }
    if (fp >= _iob + OPEN_MAX) { // no free slots
        return NULL;
    }

    if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1) {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }

    if (fd == -1) { // couldn't access name
        return NULL;
    }

    fp->fd   = fd;
    fp->cnt  = 0;
    fp->base = NULL;

    // set flags
    fp->flags.is_unbuf  = 0;
    fp->flags.is_eof    = 0;
    fp->flags.is_err    = 0;
    fp->flags.is_read   = (*mode == 'r') ? 1 : 0;
    fp->flags.is_write  = (*mode == 'r') ? 0 : 1;

    return fp;
}

// _fillbuf: allocate and fill input buffer
int _fillbuf(FILE *fp) {
    int bufsize;

    if (fp->flags.is_read && (fp->flags.is_eof || fp->flags.is_err)) {
        return EOF;
    }

    bufsize = (fp->flags.is_unbuf) ? 1 : BUFSIZ;
    if (fp->base == NULL) {
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            return EOF;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flags.is_eof = 1;
        } else {
            fp->flags.is_err = 1;
        }
        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++;
}

// test code
int main(void) {
    FILE *fp;
    char c;

    if ((fp = fileopen("fileopen.c", "r")) == NULL) {
        write(1, "error: couldn't open file\n", 26);
        return 1;
    }

    while ((c = getc(fp)) != EOF) {
        write(1, &c, 1);
    }

    return 0;
}