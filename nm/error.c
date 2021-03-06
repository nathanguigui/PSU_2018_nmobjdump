/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** error
*/

#include "nm.h"

void quit(char *error, elfData_t *data)
{
    fprintf(stderr, "nm: %s: %s\n", data->arg, error);
    exit(84);
}

bool check_overtake(elfData_t *data, void *ptr)
{
    if (ptr > (void *)(data->_ehdr) + data->_len)
        return (false);
    return (true);
}

bool check_each_section_header(elfData_t *data)
{
    for (size_t i = 0; i < data->_ehdr->e_shnum; i++) {
        if (!check_overtake(data, (void *)&(data->_shdr[i])))
            quit("File truncated", data);
        if (data->_shdr[i].sh_type == SHT_SYMTAB) {
            data->symStart = (void *)data->_ehdr + data->_shdr[i].sh_offset;
            data->symStop = (void *)data->_ehdr + data->_shdr[i].sh_offset
            + data->_shdr[i].sh_size;
            if (data->_shdr[i].sh_link > data->_ehdr->e_shnum)
                quit("File format not recognized", data);
            data->strTab = (char *)data->_ehdr
            + data->_shdr[data->_shdr[i].sh_link].sh_offset;
            if (!check_overtake(data, data->strTab))
                quit("File format not recognized", data);
            if (!check_overtake(data, data->symStart) ||
            !check_overtake(data, data->symStop))
                quit("No symbols", data);
        }
    } if ((void *)data->symStop < (void *)data->symStart)
        quit("No symbols", data);
    return (true);
}