/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** error
*/

#include "nm.h"

void quit(char *error)
{
    puts(error);
    exit(84);
}

bool check_overtake(elfData_t *data, void *ptr)
{
    if (ptr > (void*)(data->_ehdr) + data->_len)
        return (false);
    return (true);
}

bool check_each_section_header(elfData_t *data)
{

    for (int i = 0; i < data->_ehdr->e_shnum; i++) {
        if (!check_overtake(data, (void*)&(data->_shdr[i])))
            quit("section header overtake");
        if (data->_shdr[i].sh_type == SHT_SYMTAB) {
            data->symStart = (void*)data->_ehdr + data->_shdr[i].sh_offset;
            data->symStop = (void*)data->_ehdr + data->_shdr[i].sh_offset
            + data->_shdr[i].sh_size;
            if (!check_overtake(data, data->symStart) ||
            !check_overtake(data, data->symStop))
                quit("symbol table overtake");
        }
        if (data->_shdr[i].sh_type == SHT_STRTAB) {
            data->symStrTab = (char*)data->_ehdr + data->_shdr[i].sh_offset;
            if (!check_overtake(data, data->symStrTab))
                quit("str symtab overtake");
        }
    } if ((void*)data->symStop < (void*)data->symStart)
        quit("sym stop before sym start");
    return (true);
}