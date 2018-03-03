#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<
int
main(int argc, char **argv)
{
    unsigned long long total_size = 0;
    unsigned long long max_size;
    unsigned long long max_file = 0;
    char max_name[PATH_MAX] = "";
    char *path = argv[1];
    char *suff = argv[3];
    sscanf(argv[2], "%lld", &max_size);
    DIR *d = opendir(path);
    struct dirent *dd;
    while ((dd = readdir(d))) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
            continue;
        }
        struct stat buf;
        char fullname[PATH_MAX] = "";
        snprintf(fullname, PATH_MAX, "%s/%s", path, dd->d_name);
        if (lstat(fullname, &buf) < 0) {
            continue;
        }
        if (S_ISREG(buf.st_mode)) {
            if (buf.st_size >= max_file) {
                if (strstr(dd->d_name, suff)) {
                    if (buf.st_size == max_file) {
                        if (strcmp(dd->d_name, max_name) < 0) {
                            strcpy(max_name, dd->d_name);
                        }
                    } else {
                        max_file = buf.st_size;
                        strcpy(max_name, dd->d_name);
                    }
                }
            }
            total_size += buf.st_size;
        }
    }
    if (total_size > max_size) {
        printf("%s\n", max_name);
    }
    return 0;
}
