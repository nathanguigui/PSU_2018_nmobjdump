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

#include "flags.h"

typedef struct elfData_s
{
    Elf64_Ehdr *_ehdr;
    Elf64_Shdr *_shdr;
    size_t _len;
    char *arg;
    int flags;
} elfData_t;


//utils.c
char *give_arch(elfData_t *, int);
bool isPrint(char);
void print_indent(int, int);

//parser.c
void quit(char *, elfData_t *);
bool check_overtake(elfData_t *, void *);
bool check_magick(elfData_t *);
void init_data(elfData_t *);
int elf_parser(elfData_t *, int);


#endif /* !OBJDUMP_H_ */