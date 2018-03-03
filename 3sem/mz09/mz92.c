/* Программе в аргументах командной строки передаются три команды для выполнения, затем два имени файла (всего 5 аргументов командной строки). Программа должна запустить на выполнение процессы, чтобы они выполнялись в конфигурации, соответствующей команде shell:

( cmd1 < file1 && cmd2 ) | cmd3 >> file2

Родительский процесс должен дождаться завершения всех созданных им процессов и сам завершить выполнение.

Считайте, что команды cmd1, cmd2, cmd3 можно запускать на выполнение с помощью execlp.

Запись CMD1 && CMD2 означает, что процесс CMD2 должен быть запущен только после успешного завершения процесса CMD1.

Запись ( CMD ) используется для группировки, при этом вся командная строка CMD выполняется в отдельном процессе, порожденном основным процессом. */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
    int st;
    if (!fork()) {
        int fd = open(argv[4], O_RDONLY, 0777);
        dup2(fd, 0);
        close(fd);
        execlp(argv[1], argv[1], NULL);
        exit(1);
    } else {
        wait(&st);
        int fd1[2];
        pipe(fd1);
        dup2(fd1[1], 1);
        close(fd1[1]);
        if(!fork()) {
            dup2(fd1[0], 0);
            close(fd1[0]);
            int fd2 = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0777);
            dup2(fd2, 1);
            close(fd2);
            int st2;
            wait(&st2);
            execlp(argv[2], argv[2], NULL);
            exit(1);
        } else {
            close(fd1[0]);
            if(WIFEXITED(&st)) {
                execlp(argv[3], argv[3], NULL);
                exit(1);
            }
        }
    }
    return 0;
}
