NAME=philo
SRC=main.c \
	argument_parsing.c \
	initialization.c \
	timeutils.c \
	parsing_helpers.c \
	philo_utils.c \
	philo_actions.c \
	philo.c assignments.c
INCLUDE=./philo.h
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) -o $(NAME) -Wall -Wextra -Werror -I$(INCLUDE)

$(OBJ): $(SRC)
	cc -c $(SRC) -Wall -Wextra -Werror

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
