/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** objdump
*/

#include "objdump.h"

int main(int argc, char const *argv[])
{
    elfData_t *data = malloc(sizeof(elfData_t));

    if (argc == 1)
        data->arg = "a.out";
    else
        data->arg = (char *)argv[1];
    elf_parser(data->arg, data, open(data->arg, O_RDONLY));
}