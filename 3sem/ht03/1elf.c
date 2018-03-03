#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <elf.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

int
main(int argc, char **argv)
{
    int fd;
    if(!(fd = open(argv[1], O_RDONLY))) {
        fprintf(stderr, "Couldn't open input file\n");
        exit(1);
    }
    Elf32_Ehdr hdr;
    if(read(fd, &hdr, sizeof(hdr)) != sizeof(hdr)) {
        fprintf(stderr, "Error while reading ELF Header\n");
        exit(1);
    }
    if (hdr.e_ident[0] != '\x7f' || hdr.e_ident[1] != 'E' ||
hdr.e_ident[2] != 'L' || hdr.e_ident[3] != 'F') {
        fprintf(stderr, "Not an ELF file\n");
        exit(1);
    }
    if (hdr.e_ident[4] != 1 || hdr.e_ident[5] != 1 || hdr.e_ident[6] != 1 ||
hdr.e_ident[7] != 0 || hdr.e_ident[8] != 0) {
        fprintf(stderr, "Not supported ELF file\n");
        exit(1);
    }
    if (hdr.e_type == 0) {
        printf("TYPE: NONE\n");
    } else if (hdr.e_type == 1) {
        printf("TYPE: REL\n");
    } else if (hdr.e_type == 2) {
        printf("TYPE: EXEC\n");
    } else if (hdr.e_type == 3) {
        printf("TYPE: DYN\n");
    } else if (hdr.e_type == 4) {
        printf("TYPE: CORE\n");
    }
    Elf32_Shdr shnm, name_ind;
    lseek(fd, hdr.e_shoff + hdr.e_shstrndx * hdr.e_shentsize, SEEK_SET);
    read(fd, &name_ind, sizeof(name_ind));
    lseek(fd, name_ind.sh_offset, SEEK_SET);
    char *buf = calloc(1, name_ind.sh_size);
    read(fd, buf, name_ind.sh_size);
    printf("                NAME       ADDR     OFFSET       SIZE   ALGN\n");
    for (int i = 1; i < hdr.e_shnum; i++) {
        lseek(fd, hdr.e_shoff + i * hdr.e_shentsize, 0);
        read(fd, &shnm, sizeof(shnm));
        printf("%20s 0x%08x %10d %10d 0x%04x\n", buf + shnm.sh_name,
shnm.sh_addr, shnm.sh_offset, shnm.sh_size, shnm.sh_addralign);
    }
    return 0;
}
