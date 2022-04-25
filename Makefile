# -*- MakeFile -*-

NAME = pipex

# -*- Compiler -*-
GCC = gcc
FLAGS = -Wall -Wextra -Werror -ggdb3

# -*- Includes -*-
SRC_PATH	= src
OBJ_PATH	= obj
LIBFT		= libft
INCL		= incl
GNL_PATH	= 42-get-next-line

# -*- Source Files -*-
SRC	=	pipex_bonus.c \
		child_bonus.c \
		files_bonus.c \
		free_bonus.c \

GNL			=	get_next_line.c \
				get_next_line_utils.c
# -*- Objects -*-
OBJS	=	$(addprefix $(OBJ_PATH)/,$(SRC:.c=.o)) \
			$(addprefix $(GNL_PATH)/,$(GNL:.c=.o))

.PHONY: tmp, lib, re, fclean, clean

all: lib tmp $(NAME)

tmp:
	@mkdir -p obj

lib:
	make -C $(LIBFT)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(GCC) $(FLAGS) -c $< -o $@


$(NAME): $(OBJS) $(LIBFT)/libft.a
	$(GCC) $(FLAGS) $^ -L $(LIBFT) -o $(NAME)


# bonus: lib tmp $(BONUS_OBJS) $(LIBFT)/libft.a
# 	$(GCC) $(FLAGS) $(BONUS_OBJS) $(LIBFT)/libft.a -L $(LIBFT) -o $(NAME)

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_PATH)
	rm test_out*
	rm -f $(addprefix $(GNL_PATH)/,$(GNL:.c=.o))

fclean:
	make clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)
	rm -f $(addprefix $(GNL_PATH)/,$(GNL:.c=.o))


re:	fclean all

bonusre: fclean bonus 