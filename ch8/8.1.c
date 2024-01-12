#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define PERMS 0666  // read write permission for user, group, other
#define STDOUT 1    // file descriptor for stdout is 1

// cat: prints content of all file arguments to stdout (syscall version)
int main(int argc, char *argv[]) {
    int f, n;
    char buf[BUFSIZ];

    char *prog = argv[0];

    if (argc == 1) {
        fprintf(stderr, "usage: %s file1 file2 ...\n", prog);
        exit(1);
    }

    while (--argc > 0) {
        if ((f = open(*++argv, O_RDONLY, PERMS)) == -1) {
            fprintf(stderr, "%s: cannot open %s\n", prog, *argv);
            exit(1);
        } else {
            while ((n = read(f, buf, BUFSIZ)) > 0) {
                if (write(STDOUT, buf, n) != n) {
                    fprintf(stderr, "%s: error writing to stdout\n", prog);
                    exit(1);
                }
            }
            close(f);
        }
    }

    return 0;
}