NAME=philosophers
LIBFT=./libft/build/libft.a
SRC=main.c argument_parsing.c
OBJ := $(SRC:.c=.o)
DEP := $(OBJ:%.o=%.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	cc $(OBJ) -o philosophers -Wall -Wextra -Werror -L./libft/build -lft -I./libft/src/

-include $(DEP)

$(OBJ): $(SRC)
	cc -c $(SRC) -Wall -Wextra -Werror -I./libft/src/

$(LIBFT):
	make all -C ./libft/

clean:
	rm -f $(OBJ)
	make clean -C ./libft/

fclean:
	make fclean -C ./libft/
	rm -f $(OBJ)
	rm -f $(NAME)

re: fclean all
