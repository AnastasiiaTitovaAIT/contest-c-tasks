#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
int main(int argc, const char **argv)
{
    unsigned long long sum = 0;
    const char *path = argv[1];
    DIR *d = opendir(path);//открываем директорию
    struct dirent *dd; //заводим структуру под элементы директории
    while ((dd = readdir(d))) { //считываем
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) { //пропускаем родительские
            continue;
        }
        struct stat buf; //заводим структуру
        char fullname[PATH_MAX] = "";
        snprintf(fullname, PATH_MAX, "%s/%s", path, dd->d_name); //сохраняем имя в буффер
        if (lstat(fullname, &buf) < 0) { //собираем информацию в структуру
            continue;
        }
        if (S_ISREG(buf.st_mode)) {//проверяем на то, регулярный ли файл
            sum += buf.st_size; //суммируем размер регулярные файлы
        }
    }
    printf("%llu", sum);
    return 0;
}
