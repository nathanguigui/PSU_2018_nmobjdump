/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** objdump
*/

#include "objdump.h"

bool isPrint(char c)
{
    if (c >= 32 && c <= 126)
        return (true);
    return (false);
}

void print_indent(int i, int status)
{
    if (status == 1) {
        for (int off = i; off < 16; off++) {
            printf("  ");
            (off) % 4 == 0 ? printf(" ") : 0;
        }
    } if (status == 2) {
        for (int off = i; off < 16; off++)
            printf(" ");
    }
}

void print_section_info(elfData_t *data, int ic, char *tmp)
{
    tmp += data->_shdr[ic].sh_info;
    int off1 = 0;
    int off2 = 0;

    for (int i = 0; i < (int)data->_shdr[ic].sh_size; i += 16) {
        printf(" %04x ", (int)(data->_shdr[ic].sh_addr + i));
        for (off1 = 0; off1 < 16 && i + off1 < (int)data->_shdr[ic].sh_size; off1++) {
            printf("%02x", (unsigned char)tmp[i + off1]);
            ((off1 + 1) % 4 == 0) ? printf(" ") : 0;
        }
        print_indent(off1, 1);
        printf(" ");
        for (off2 = 0; off2 < 16 && i + off2 < (int)data->_shdr[ic].sh_size; off2++)
            printf("%c", isPrint(tmp[i + off2]) ? tmp[i + off2] : '.');
        print_indent(off2, 2);
        printf("\n");
    }
}

void print_section(elfData_t *data)
{
    char *tmp = NULL;

    for (size_t i = 0; i < data->_ehdr->e_shnum; i++) {
        if (!check_overtake(data, (void *)&(data->_shdr[i])))
            quit("File truncated", data);
        if ((data->_shdr[i].sh_type != SHT_SYMTAB &&
        data->_shdr[i].sh_type != SHT_NOBITS &&
        data->_shdr[i].sh_type != SHT_STRTAB &&
        data->_shdr[i].sh_size) ||
        (data->_shdr[i].sh_type == SHT_STRTAB &&
        data->_shdr[i].sh_flags == SHF_ALLOC)) {
            printf("Contents of section %s:\n", ((char*)((void *)data->_ehdr
            + data->_shdr[data->_ehdr->e_shstrndx].sh_offset))
            + data->_shdr[i].sh_name);
            tmp = (char *)data->_ehdr + data->_shdr[i].sh_offset;
            if (!check_overtake(data, (void *)tmp))
                quit("File format not recongnized", data);
            print_section_info(data, i, tmp);
        }
    }
}

char *give_arch(elfData_t *data, int status)
{
    if (status == 1) {
        if (data->_ehdr->e_ident[EI_CLASS] == ELFCLASS64)
            return ("64-x86-64");
        else
            return ("32-i386");
    } if (status == 2) {
        if (data->_ehdr->e_ident[EI_CLASS] == ELFCLASS64)
            return (":x86-64");
        else
            return ("");
    }
    return ("");
}

void print_header(elfData_t *data)
{
    printf("\n%s:     file format elf%s\n", data->arg, give_arch(data, 1));
    printf("architecture: i386%s, flags 0x%08x:\n", give_arch(data, 2), data->flags);
    
    printf("\n");
    printf("start address 0x%016lx\n\n", data->_ehdr->e_entry);
}

void core(elfData_t *data)
{
    char *tmp;
    for (int i = 0; i < data->_ehdr->e_shnum; i++) {
        if (!check_overtake(data, (void *)&(data->_shdr[i])))
            quit("File truncated", data);
        tmp = ((char*)((void *)data->_ehdr
        + data->_shdr[data->_ehdr->e_shstrndx].sh_offset))
        + data->_shdr[i].sh_name;
        strcmp(".dynamic", tmp) == 0 ? data->flags |= DYNAMIC : 0;
        strcmp(".dynstr", tmp) == 0 ? data->flags |= DYNAMIC : 0;
        strcmp(".dynsym", tmp) == 0 ? data->flags |= DYNAMIC + HAS_SYMS : 0;
        strcmp(".symtab", tmp) == 0 ? data->flags |= HAS_SYMS : 0;
        data->_shdr[i].sh_type == SHT_REL ? data->flags |= HAS_RELOC : 0;
        data->_shdr[i].sh_type == SHT_RELA ? data->flags |= HAS_RELOC : 0;
        data->_shdr[i].sh_type == SHT_HASH ? data->flags |= D_PAGED : 0;
    }
}

void quit(char *error, elfData_t *data)
{
    fprintf(stderr, "objdump: %s: %s\n", data->arg, error);
    exit(84);
}

bool check_overtake(elfData_t *data, void *ptr)
{
    if (ptr > (void *)(data->_ehdr) + data->_len)
        return (false);
    return (true);
}
bool check_magick(elfData_t *data)
{
    if (memcmp(data->_ehdr->e_ident, ELFMAG, SELFMAG) != 0)
        return (false);
    return (true);
}

void init_data(elfData_t *data)
{
    data->_ehdr = NULL;
    data->_shdr = NULL;
    data->_len = 0;
    data->flags = 0;
}

int elf_parser(elfData_t *data, int fd)
{
    struct stat statbuf;

    init_data(data);
    if (fd == -1)
        quit("Cannot open file", data);
    if (fstat(fd, &statbuf) == -1)
        quit("Cannot stat file", data);
    data->_len = statbuf.st_size;
    if ((data->_ehdr = mmap(NULL, data->_len, PROT_READ, MAP_SHARED, fd, 0))
    == (void *)-1)
        quit("Cannot mmap the file", data);
    if (!check_magick(data))
        quit("File format not recognized", data);
    if (data->_ehdr->e_shoff == 0)
        quit("File format not recognized", data);
    data->_shdr = (Elf64_Shdr*) (((void *)data->_ehdr) + data->_ehdr->e_shoff);
    if (data->_len < data->_ehdr->e_shoff)
        quit("File format not recognized", data);
    data->_ehdr->e_type == ET_EXEC ? data->flags |= EXEC_P : 0;
    return (true);
}

int main(int argc, char const *argv[])
{
    elfData_t *data = malloc(sizeof(elfData_t));
    if (argc == 1)
        data->arg = "a.out";
    else
        data->arg = (char *)argv[1];
    elf_parser(data, open(data->arg, O_RDONLY));
    core(data);
    data->flags |= D_PAGED;
    print_header(data);
    print_section(data);
}