/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** symbol
*/

#include "nm.h"

char *strEpur(char *str)
{
    int count = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] > 64 && str[i] < 91)
            count++;
    char *res = malloc(sizeof(char) * count + 1);
    count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] > 64 && str[i] < 91) {
            res[count] = str[i];
            count++;
        }
    }
    res[count] = 0;
    return (res);
}

char *strCaps(char *str)
{
    char *tmp = strdup(str);
    for (int i = 0; tmp[i]; i++) {
        if (tmp[i] >= 'a' && tmp[i] <= 'z')
            tmp[i] = tmp[i] - 32;
    }
    return (tmp);
}

int cmpSym(symList_t *sym1, symList_t *sym2)
{
    char *str1 = strEpur(strCaps(sym1->name));
    char *str2 = strEpur(strCaps(sym2->name));
    return (strcmp(str1, str2));
}

bool unsorted(elfData_t *data)
{
    for (int i = 0; data->symbolList[i + 1]; i++) {
        if (cmpSym(data->symbolList[i], data->symbolList[i+1]) > 0)
            return (true);
    }
    return (false);
}

void sortSym(elfData_t *data)
{
    symList_t *tmp = NULL;
    while (unsorted(data)) {
        for (int i = 0; data->symbolList[i + 1]; i++) {
            if (cmpSym(data->symbolList[i], data->symbolList[i+1]) > 0) {
                tmp = data->symbolList[i];
                data->symbolList[i] = data->symbolList[i+1];
                data->symbolList[i+1] = tmp;
            }
        }
    }
}