/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** parser
*/

#include "nm.h"

bool check_magick(elfData_t *data)
{
    if (memcmp(data->_ehdr->e_ident, ELFMAG, SELFMAG) != 0)
        return (false);
    return (true);
}

void init_data(elfData_t *data)
{
    data->_ehdr = NULL;
    data->_shdr = NULL;
    data->symStrTab = NULL;
}

int elf_parser(char *path, elfData_t *data)
{
    int fd;
    struct stat statbuf;

    init_data(data);
    if ((fd = open(path, O_RDONLY)) == -1)
        quit("Cannot open file");
    if (fstat(fd, &statbuf) == -1)
        quit("Cannot stat file");
    data->_len = statbuf.st_size;
    if ((data->_ehdr = mmap(NULL, data->_len, PROT_READ, MAP_SHARED, fd, 0))
    == (void*)-1)
        quit("Cannot mmap the file");
    if (!check_magick(data))
        quit("File not elf file");
    if (data->_ehdr->e_shoff == 0)
        quit("File doesn't contain section header");
    data->_shdr = (Elf64_Shdr*) ( ((void *) data->_ehdr) + data->_ehdr->e_shoff);
    if (data->_len < data->_ehdr->e_shoff)
        quit("Section header offset greater than file size");
    return (true);
}