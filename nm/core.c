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
    data->symbolList[i]->value = symbol->st_value;
    data->symbolList[i]->letter = '?';
    data->symbolList[i]->ptr = symbol;
}

void printSym(elfData_t *data)
{
    for (int i = 0; data->symbolList[i]; i++) {
        if (data->symbolList[i]->value) {
            printf(
                "%016x %c %s\n",
                data->symbolList[i]->value,
                data->symbolList[i]->letter,
                data->symbolList[i]->name
            );
        } else {
            printf(
                "                 %c %s\n",
                data->symbolList[i]->letter,
                data->symbolList[i]->name
            );
        }
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
    data->symbolList = malloc(sizeof(symList_t *) * (i + 1));
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
    if (!check_overtake(data, (void *)data->_shdr))
        quit("File format not recognized", data);
    if (!check_each_section_header(data))
        quit("File format not recognized", data);
    getSymList(data);
    return (true);
}

int main(int argc, char const *argv[])
{
    nm(argc, argv);
    return (0);
}
