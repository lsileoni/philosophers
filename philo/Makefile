NAME=philo
SRC=main.c argument_parsing.c initialization.c timeutils.c parsing_helpers.c
OBJ := $(SRC:.c=.o)
DEP := $(OBJ:%.o=%.d)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) -o $(NAME) -Wall -Wextra -Werror -Ofast -march=native

-include $(DEP)

$(OBJ): $(SRC)
	cc -c $(SRC) -Wall -Wextra -Werror -Ofast -march=native

debug: $(OBJ)
	cc $(OBJ) -o $(NAME) -Wall -Wextra -Werror

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ)
	rm -f $(NAME)

re: fclean all
