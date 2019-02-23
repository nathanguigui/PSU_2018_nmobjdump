##
## EPITECH PROJECT, 2019
## PSU_2018_nmobjdump
## File description:
## Makefile
##

NM_NAME			=	my_nm

OBJDUMP_NAME	=	my_objdump

CC				=	gcc

RM				=	rm -f

NM_SRCS			=	./nm/core.c \
					./nm/error.c \
					./nm/parser.c \
					./nm/symbol.c \
					./nm/letter.c \
					./nm/nm.c

OBJDUMP_SRCS	=	./objdump/objdump.c \
					./objdump/parser.c \
					./objdump/utils.c

NM_OBJS			=	$(NM_SRCS:.c=.o)

OBJDUMP_OBJS	=	$(OBJDUMP_SRCS:.c=.o)

CFLAGS			=	-Wall -Wextra -g3 -I ./inc



nm: $(NM_NAME)

$(NM_NAME): $(NM_OBJS)
	$(CC) $(NM_OBJS) -o $(NM_NAME) $(LDFLAGS)

nm_clean:
	$(RM) $(NM_OBJS)

nm_fclean: nm_clean
	$(RM) $(NM_NAME)

nm_re: nm_fclean nm



objdump: $(OBJDUMP_NAME)

$(OBJDUMP_NAME): $(OBJDUMP_OBJS)
	$(CC) $(OBJDUMP_OBJS) -o $(OBJDUMP_NAME) $(LDFLAGS)

objdump_clean:
	$(RM) $(OBJDUMP_OBJS)

objdump_fclean: objdump_clean
	$(RM) $(OBJDUMP_NAME)

objdump_re: objdump_fclean objdump



clean: nm_clean objdump_clean

fclean: nm_fclean objdump_fclean

re: nm_re objdump_re

all: nm objdump

.PHONY: all nm objdump fclean clean nm_clean nm_fclean nm_re objdump_clean objdump_fclean objdump_re