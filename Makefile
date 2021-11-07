#* ************************************************************************** *#
#*                                                                            *#
#*                                                                            *#
#*   Makefile                                                                 *#
#*                                                                            *#
#*   By: yhetman <yhetman@student.unit.ua>                                    *#
#*                                                                            *#
#*   Created: 2021/10/19 00:52:56 by yhetman                                  *#
#*   Updated: 2021/10/19 00:52:59 by yhetman                                  *#
#*                                                                            *#
#* ************************************************************************** *#

SRCS = salsa20.c

SRCS_DIR = src/

OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

OBJ_DIR = obj/

LIB_NAME = libsalsa20.a

SALSA20 = salsa20

FLAGS = -I includes -Wall -Wextra -Werror

DEBUG_FLAGS = -g3 -fsanitize=address

SALSA20_MAIN = src/main.c

all: make_obj_dir $(SALSA20)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	gcc $(FLAGS) -c $< -o $@

$(LIB_NAME): $(OBJ)
	ar -rv $(LIB_NAME) $^
	ranlib $(LIB_NAME)

$(SALSA20): $(LIB_NAME) $(SALSA20_MAIN)
	gcc $(FLAGS) $(SALSA20_MAIN) $(LIB_NAME) -o $(SALSA20)

make_obj_dir:
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(SALSA20)
	rm -f $(LIB_NAME)

re: fclean all

.PHONY: all clean flcean re debug


