/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** utils
*/

#include "objdump.h"

char *give_arch(elfData_t *data, int status)
{
    if (status == 1) {
        if (data->_ehdr->e_ident[EI_CLASS] == ELFCLASS64)
            return ("64-x86-64");
        else
            return ("32-i386");
    } if (status == 2) {
        if (data->_ehdr->e_ident[EI_CLASS] == ELFCLASS64)
            return (":x86-64");
        else
            return ("");
    }
    return ("");
}

bool isPrint(char c)
{
    if (c >= 32 && c <= 126)
        return (true);
    return (false);
}

void print_indent(int i, int status)
{
    if (status == 1) {
        for (int off = i; off < 16; off++) {
            printf("  ");
            (off) % 4 == 0 ? printf(" ") : 0;
        }
    } if (status == 2) {
        for (int off = i; off < 16; off++)
            printf(" ");
    }
}