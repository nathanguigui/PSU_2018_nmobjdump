/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_
#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <regex.h>

typedef struct elfData_s
{
    Elf64_Ehdr *_ehdr;
    Elf64_Shdr *_shdr;
    size_t _len;
    char *arg;
} elfData_t;


//error.c
void quit(char *, elfData_t *);
bool check_overtake(elfData_t *, void *);

//parser.c
int elf_parser(char *, elfData_t *, int);


#endif /* !OBJDUMP_H_ */
