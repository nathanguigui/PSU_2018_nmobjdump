/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** parser
*/

#include "objdump.h"

void quit(char *error, elfData_t *data)
{
    fprintf(stderr, "objdump: %s: %s\n", data->arg, error);
    exit(84);
}

bool check_overtake(elfData_t *data, void *ptr)
{
    if (ptr > (void *)(data->_ehdr) + data->_len)
        return (false);
    return (true);
}

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
    data->_len = 0;
    data->flags = 0;
}

int elf_parser(elfData_t *data, int fd)
{
    struct stat statbuf;

    init_data(data);
    if (fd == -1)
        quit("Cannot open file", data);
    if (fstat(fd, &statbuf) == -1)
        quit("Cannot stat file", data);
    data->_len = statbuf.st_size;
    if ((data->_ehdr = mmap(NULL, data->_len, PROT_READ, MAP_SHARED, fd, 0))
    == (void *)-1)
        quit("Cannot mmap the file", data);
    if (!check_magick(data))
        quit("File format not recognized", data);
    if (data->_ehdr->e_shoff == 0)
        quit("File format not recognized", data);
    data->_shdr = (Elf64_Shdr*) (((void *)data->_ehdr) + data->_ehdr->e_shoff);
    if (data->_len < data->_ehdr->e_shoff)
        quit("File format not recognized", data);
    data->_ehdr->e_type == ET_EXEC ? data->flags |= EXEC_P : 0;
    return (true);
}