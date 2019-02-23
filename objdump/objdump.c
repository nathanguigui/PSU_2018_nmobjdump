/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** objdump
*/

#include "objdump.h"

void print_section_info(elfData_t *data, int ic, char *tmp)
{
    tmp += data->_shdr[ic].sh_info;
    int off1 = 0;
    int off2 = 0;

    for (int i = 0; i < (int)data->_shdr[ic].sh_size; i += 16) {
        printf(" %04x ", (int)(data->_shdr[ic].sh_addr + i));
        for (off1 = 0;
        off1 < 16 && i + off1 < (int)data->_shdr[ic].sh_size; off1 ++) {
            printf("%02x", (unsigned char)tmp[i + off1]);
            ((off1 + 1) % 4 == 0) ? printf(" ") : 0;
        }
        print_indent(off1, 1);
        printf(" ");
        for (off2 = 0; off2 < 16 && i + off2 < (int)data->_shdr[ic].sh_size;
        off2 ++)
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
            printf("Contents of section %s:\n", ((char *)((void *)data->_ehdr
            + data->_shdr[data->_ehdr->e_shstrndx].sh_offset))
            + data->_shdr[i].sh_name);
            tmp = (char *)data->_ehdr + data->_shdr[i].sh_offset;
            if (!check_overtake(data, (void *)tmp))
                quit("File format not recongnized", data);
            print_section_info(data, i, tmp);
        }
    }
}

void print_header(elfData_t *data)
{
    printf("\n%s:     file format elf%s\n", data->arg, give_arch(data, 1));
    printf("architecture: i386%s, flags 0x%08x:\n", give_arch(data, 2),
    data->flags);
    printf("\n");
    printf("start address 0x%016lx\n\n", data->_ehdr->e_entry);
}

void core(elfData_t *data)
{
    char *tmp;
    for (int i = 0; i < data->_ehdr->e_shnum; i++) {
        if (!check_overtake(data, (void *)&(data->_shdr[i])))
            quit("File truncated", data);
        tmp = ((char *)((void *)data->_ehdr
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

int main(int ac, char const *av[])
{
    elfData_t *data = malloc(sizeof(elfData_t));

    if (ac < 2) {
        data->arg = "a.out";
        elf_parser(data, open(data->arg, O_RDONLY));
        core(data);
        data->flags |= D_PAGED;
        print_header(data);
        print_section(data);
        return (0);

    } else if (ac == 2) {
        data->arg = strdup(av[1]);
        elf_parser(data, open(data->arg, O_RDONLY));
        core(data);
        data->flags |= D_PAGED;
        print_header(data);
        print_section(data);
        return (0);
    } else {
        for (int i = 1; i != ac; i++) {
            data->arg = strdup(av[i]);
            i != 1 ? printf("\n") : 1;
            printf("%s:\n", data->arg);
            elf_parser(data, open(data->arg, O_RDONLY));
            core(data);
            data->flags |= D_PAGED;
            print_header(data);
            print_section(data);
        }
    }
    return (0);
}