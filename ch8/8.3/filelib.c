#include <fcntl.h>
#include <unistd.h>
#include "syscalls.h"

#define PERMS 0666

FILE _iob[OPEN_MAX] = {
    { 0, (char *) 0, (char *) 0, _READ, 0 },            // stdin
    { 0, (char *) 0, (char *) 0, _WRITE, 1 },           // stdout
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 },  // stderr
};

void *malloc(size_t);
void free(void *);

// fileopen: open file, return file pointer
FILE *fileopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if ((fp->flag & (_READ | _WRITE)) == 0) { // found a free slot
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
    fp->flag = (*mode == 'r') ? _READ : _WRITE;

    return fp;
}

// _fillbuf: allocate and fill input buffer
int _fillbuf(FILE *fp) {
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
        write(1, "5", 1);
        return EOF;
    }

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) {
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            write(1, "6", 1);
            return EOF;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag |= _EOF;
        } else {
            fp->flag |= _ERR;
        }
        fp->cnt = 0;
        write(1, "7", 1);
        return EOF;
    }

    return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp) {
    unsigned nc;
    int bufsize;

    if (fp < _iob || fp >= _iob + OPEN_MAX) {
        write(1, "1", 1);
        return EOF;
    }

    if ((fp->flag & (_WRITE | _ERR)) != _WRITE) {
        write(1, "2", 1);
        return EOF;
    }

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) {
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            fp->flag |= _ERR;
            write(1, "3", 1);
            return EOF;
        }
    } else {
        nc = fp->ptr - fp->base;
        if ((write(fp->fd, fp->base, nc)) != nc) {
            fp->flag |= _ERR;
            write(1, "4", 1);
            return EOF;
        }
    }

    fp->ptr = fp->base;
    *fp->ptr++ = (char) c;
    fp->cnt = bufsize-1;
    return c;
}

// fflush: flush the buffer of fp
int fflush(FILE *fp) {
    if ((fp->flag & _WRITE) == 0) {
        fp->flag |= _ERR;
        return EOF;
    }

    if (_flushbuf('0', fp) == EOF) {
        return EOF;
    }

    fp->ptr = fp->base;
    fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    return 0;
}

// fileclose: close file
int fileclose(FILE *fp) {
    int c;
    if ((c = fflush(fp)) != EOF) {
        fp->ptr = NULL;
        fp->cnt = 0;
        fp->flag &= ~(_READ | _WRITE);
        free(fp->base);
        fp->base = NULL;
    }
    return c;
}

// test code
int main(void) {
    FILE *fp;
    char c;

    if ((fp = fileopen("filelib.c", "r")) == NULL) {
        write(1, "error: couldn't open file\n", 26);
        return 1;
    }

    while ((c = getc(fp)) != EOF) {
        putc(c, stdout);
    }

    return 0;
}