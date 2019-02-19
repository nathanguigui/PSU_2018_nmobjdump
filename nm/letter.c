/*
** EPITECH PROJECT, 2019
** PSU_2018_nmobjdump
** File description:
** letter
*/

#include "nm.h"

SymTypTab_t STYP_TAB[] = {
    { STT_NOTYPE, SHT_PROGBITS, 0, 'n' },
    { STT_NOTYPE, SHT_PROGBITS, 2, 'r' },
    { STT_NOTYPE, SHT_PROGBITS, 50, 'r' },
    { STT_NOTYPE, SHT_PROGBITS, 3, 'd' },
    { STT_NOTYPE, SHT_PROGBITS, 6, 't' },
    { STT_NOTYPE, SHT_NOBITS, 3, 'b' },
    { STT_OBJECT, SHT_DYNAMIC, 3, 'd' },
    { STT_OBJECT, SHT_NOTE, 2, 'r' },
    { STT_OBJECT, SHT_FINI_ARRAY, 3, 't' },
    { STT_OBJECT, SHT_INIT_ARRAY, 3, 't' },
    { STT_OBJECT, SHT_PROGBITS, 0, 'n' },
    { STT_OBJECT, SHT_PROGBITS, 2, 'r' },
    { STT_OBJECT, SHT_PROGBITS, 50, 'r' },
    { STT_OBJECT, SHT_PROGBITS, 3, 'd' },
    { STT_OBJECT, SHT_NOBITS, 3, 'b' },
    { STT_FUNC, SHT_PROGBITS, 6, 't' },
    { STT_TLS, SHT_PROGBITS, 1027, 'd' },
    { STT_TLS, SHT_NOBITS, 1027, 'b' },
    { STT_LOOS, SHT_PROGBITS, 6, 'i' }
};

SymTypTab_t GTYP_TAB[] = {
    { STT_NOTYPE, SHT_PROGBITS, 3, 'D' },
    { STT_OBJECT, SHT_PROGBITS, 3, 'D' },
    { STT_OBJECT, SHT_PROGBITS, 2, 'R' },
    { STT_OBJECT, SHT_NOBITS, 3, 'B' },
    { STT_FUNC, SHT_NULL, 0, 'U' },
    { STT_FUNC, SHT_PROGBITS, 6, 'T' },
    { STT_LOOS, SHT_PROGBITS, 6, 'i' }
};

char weakLetter(Elf64_Sym *sym)
{
    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
        if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
            return (sym->st_shndx != SHN_UNDEF ? 'V' : 'v');
        return (sym->st_shndx != SHN_UNDEF ? 'W' : 'w');
    }
    return ('?');
}

char setLetter(elfData_t *data, Elf64_Sym *sym)
{
    if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL) {
        for (int i = 0; i < 20; i++) {
            if (data->_shdr[sym->st_shndx].sh_type == STYP_TAB[i].sht &&
            data->_shdr[sym->st_shndx].sh_flags == STYP_TAB[i].flag &&
            ELF64_ST_TYPE(sym->st_info) == STYP_TAB[i].stt)
                return (STYP_TAB[i].type);
        }
    } else if (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL) {
        for (int i = 0; i < 7; i++) {
            if (data->_shdr[sym->st_shndx].sh_type == GTYP_TAB[i].sht &&
            data->_shdr[sym->st_shndx].sh_flags == GTYP_TAB[i].flag &&
            ELF64_ST_TYPE(sym->st_info) == GTYP_TAB[i].stt)
                return (GTYP_TAB[i].type);
        }
        return ('U');
    }
    return (weakLetter(sym));
}