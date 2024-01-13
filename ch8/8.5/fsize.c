#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define MAX_PATH 1024
#define TIMELEN 32

void fsize(char *);
void dirwalk(char *, void (*func)(char *));
void printmode(mode_t);
void printuser(uid_t);
void printgroup(gid_t);
void printaccess(struct timespec);

// prints the contents of all directories given as arguments; emulates `ls -l`
int main(int argc, char *argv[]) {
    if (argc == 1) {
        fsize(".");
    } else {
        while (--argc > 0) {
            fsize(*++argv);
        }
    }
    return 0;
}

// fsize: print size and other information about file "name"
void fsize(char *name) {
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }

    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    }

    printmode(stbuf.st_mode);
    printf("%u ", stbuf.st_nlink);
    printuser(stbuf.st_uid);
    printgroup(stbuf.st_gid);
    printf("%7lld ", stbuf.st_size);
    printaccess(stbuf.st_atimespec);
    printf("%s\n", name);
}

// dirwalk: apply func to all files in dir
void dirwalk(char *dir, void (*func)(char *)) {
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }

    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            // skip self and parent
            continue;
        }
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) {
            fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
            return;
        } else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*func)(name);
        }
    }

    closedir(dfd);
}

// printmode: print the file mode (i.e. permissions)
void printmode(mode_t st_mode) {
    printf("%c", ((st_mode & S_IFMT) == S_IFDIR) ? 'd' : '-');
    printf("%c", (st_mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (st_mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (st_mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (st_mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (st_mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (st_mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (st_mode & S_IROTH) ? 'r' : '-');
    printf("%c", (st_mode & S_IWOTH) ? 'w' : '-');
    printf("%c ", (st_mode & S_IXOTH) ? 'x' : '-');
}

// printuser: print the name of the user of the file
void printuser(uid_t uid) {
    struct passwd *pw;
    if ((pw = getpwuid(uid)) == NULL) {
        fprintf(stderr, "printuser: cannot find user %u\n", uid);
        return;
    }
    printf("%s ", pw->pw_name);
}

// printgroup: print the group name of the file
void printgroup(gid_t gid) {
    struct group *gr;
    if ((gr = getgrgid(gid)) == NULL) {
        fprintf(stderr, "printgroup: cannot find group %u\n", gid);
        return;
    }
    printf(" %s ", gr->gr_name);
}

void printaccess(struct timespec atimespec) {
    char time[TIMELEN];
    strftime(time, TIMELEN, "%d %b %H:%M", localtime(&atimespec.tv_sec));
    printf("%s ", time);
}
