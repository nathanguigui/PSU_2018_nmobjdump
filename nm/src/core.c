/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** core
*/

#include "nm.h"

void getSymList(elfData_t *data)
{
    Elf64_Sym *tmp = data->symStart;
    // while (tmp < data->symStop) {
        // printf("%ld\n", tmp->st_value);
        tmp++;
    // }
}

int core(elfData_t *data)
{
    // printf("sh offset: %ld", data->_shdr->sh_offset);
    if (!check_overtake(data, (void*)data->_shdr))
        quit("Wrong section header");
    if (!check_each_section_header(data))
        quit("Cannot find symbol table");
    getSymList(data);
}

int main(int argc, char const *argv[])
{
    elfData_t *data = malloc(sizeof(elfData_t));

    elf_parser((char*)argv[1], data);
    core(data);
    return 0;
}
