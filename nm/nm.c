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

    if (ac <= 1) {
        data->arg = "a.out";
        elf_parser(data->arg, data, open(data->arg, O_RDONLY));
        core(data);

    } else {
        for (int i = 1; i != ac; i++) {
            data->arg = (char *)av[i];
            i != 1 ? printf("\n") : 1;
            printf("%s:\n", data->arg);
            elf_parser(data->arg, data, open(data->arg, O_RDONLY));
            core(data);
            init_data(data);
        }
    }
}