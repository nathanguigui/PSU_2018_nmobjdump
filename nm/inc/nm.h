/*
** EPITECH PROJECT, 2019
** nm
** File description:
** nm
*/

#ifndef NM_H_
#define NM_H_
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
#pragma GCC diagnostic ignored "-Wunused-parameter"

typedef struct symList_s
{
    char *name;
    char letter;
    void *ptr;
} symList_t;

typedef struct elfData_s
{
    Elf64_Ehdr *_ehdr;
    Elf64_Shdr *_shdr;
    size_t _len;
    symList_t *symbolList;
    Elf64_Sym *symStart;
    Elf64_Sym *symStop;
    char **symStrTab;
} elfData_t;

//error.c
void quit(char*);
bool check_overtake(elfData_t*, void*);
bool check_each_section_header(elfData_t*);

//parser.c
int elf_parser(char*, elfData_t*);
#endif /* !NM_H_ */
