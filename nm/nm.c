/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** nm
*/

#include "nm.h"

void nm(int ac, char const **av)
{
    elfData_t *data = malloc(sizeof(elfData_t));

    if (ac < 2) {
        data->arg = "a.out";
        elf_parser(data, open(data->arg, O_RDONLY));
        core(data);
        return;

    } else if (ac == 2) {
        data->arg = strdup(av[1]);
        elf_parser(data, open(data->arg, O_RDONLY));
        core(data);
        return;
    } else {
        for (int i = 1; i != ac; i++) {
            data->arg = strdup(av[i]);
            i != 1 ? printf("\n") : 1;
            printf("%s:\n", data->arg);
            elf_parser(data, open(data->arg, O_RDONLY));
            core(data);
        }
    }
}