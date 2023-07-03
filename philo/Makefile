NAME=philosophers
LIBFT=./libft/build/libft.a
SRC=main.c argument_parsing.c initialization.c
OBJ := $(SRC:.c=.o)
DEP := $(OBJ:%.o=%.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	cc $(OBJ) -o philosophers -Wall -Wextra -Werror -Ofast -march=native -L./libft/build -lft -I./libft/src/

-include $(DEP)

$(OBJ): $(SRC)
	cc -c $(SRC) -Wall -Wextra -Werror -g -I./libft/src/

$(LIBFT):
	make all -C ./libft/

debug: $(LIBFT) $(OBJ)
	cc $(OBJ) -o philosophers -Wall -Wextra -Werror -L./libft/build -lft -I./libft/src/

clean:
	rm -f $(OBJ)
	make clean -C ./libft/

fclean:
	make fclean -C ./libft/
	rm -f $(OBJ)
	rm -f $(NAME)

re: fclean all
