#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct _iobuf {
    int cnt;            // characters left
    char *ptr;          // next character position
    char *base;         // location of buffer
    struct {
        unsigned is_read  : 1;    // file open for reading
        unsigned is_write : 1;    // file open for writing
        unsigned is_unbuf : 1;    // file is unbuffered
        unsigned is_eof   : 1;    // EOF has occurred on this file
        unsigned is_err   : 1;    // error occurred on this file
    } flags;
    int fd;             // file descriptor
} FILE;

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     ((p)->flags.is_eof != 0)
#define ferror(p)   ((p)->flags.is_err != 0)
#define fileno(p)   ((p)->fd)

#define getc(p)     (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p)  (--(p)->cnt >= 0 ? *(p)->ptr++ = x : _flushbuf((x),p))

#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)