/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** core
*/

#include "nm.h"

void fillSym(elfData_t *data, Elf64_Sym *symbol, int i)
{
    data->symbolList[i] = malloc(sizeof(symList_t));
    data->symbolList[i]->name = strdup(data->strTab + symbol->st_name);
    data->symbolList[i]->ptr = symbol;
}

void printSym(elfData_t *data)
{
    for (int i = 1; data->symbolList[i]; i++) {
        // if (data->symbolList[i]->ptr->st_info != 4 && data->symbolList[i]->ptr->st_info != 3)
            printf("%s %d\n", data->symbolList[i]->name, data->symbolList[i]->ptr->st_info);
    }
}

void getSymList(elfData_t *data)
{
    Elf64_Sym *tmp = data->symStart;
    int i = 0;
    for (tmp++; tmp < data->symStop; tmp++) {
        if (tmp->st_info != 3 && tmp->st_info != 4)
            i++;
    }
    data->symbolList = malloc(sizeof(symList_t*) * (i + 1));
    i = 0;
    tmp = data->symStart;
    for (tmp++; tmp < data->symStop; tmp++) {
        if (tmp->st_info != 3 && tmp->st_info != 4) {
            fillSym(data, tmp, i);
            i++;
        }
    }
    data->symbolList[i] = NULL;
    sortSym(data);
    printSym(data);
}

bool core(elfData_t *data)
{
    // printf("sh offset: %ld", data->_shdr->sh_offset);
    if (!check_overtake(data, (void*)data->_shdr))
        quit("Wrong section header");
    if (!check_each_section_header(data))
        quit("Cannot find symbol table");
    getSymList(data);
    return (true);
}

int main(int argc, char const *argv[])
{
    elfData_t *data = malloc(sizeof(elfData_t));

    elf_parser((char*)argv[1], data);
    core(data);
    return 0;
}
