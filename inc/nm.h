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
#include <regex.h>

typedef struct SymTypTab_s
{
    int stt;
    uint32_t sht;
    uint32_t flag;
    char type;
} SymTypTab_t;

extern SymTypTab_t SYM_TYP_TAB[];

typedef struct symList_s
{
    char *name;
    char letter;
    int value;
    Elf64_Sym *ptr;
} symList_t;

typedef struct elfData_s
{
    Elf64_Ehdr *_ehdr;
    Elf64_Shdr *_shdr;
    size_t _len;
    symList_t **symbolList;
    Elf64_Sym *symStart;
    Elf64_Sym *symStop;
    char *strTab;
    char *arg;
} elfData_t;

void nm(int, const char **);
bool core(elfData_t *);


//error.c
void quit(char *, elfData_t *);
bool check_overtake(elfData_t *, void *);
bool check_each_section_header(elfData_t *);

//parser.c
int elf_parser(char *, elfData_t *, int);
void init_data(elfData_t *);
//symbol.c
void sortSym(elfData_t *);
//letter.c
char setLetter(elfData_t *, Elf64_Sym *);


#endif /* !NM_H_ */
