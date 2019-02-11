NAME	= my_nm

CC	= gcc

RM	= rm -f

SRCS	= ./src/core.c \
	  ./src/error.c \
	  ./src/parser.c 

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./inc/
CFLAGS += -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	@$(RM) $(OBJS)
	@echo "cleaning nm"

fclean: clean
	@$(RM) $(NAME)
	@echo "full cleaning nm"

re: fclean all

.PHONY: all clean fclean re
