NAME=philo
SRC=main.c \
	argument_parsing.c \
	timeutils.c \
	simulation.c \
	parsing_helpers.c \
	philo_utils.c \
	philo_actions.c \
	philo.c assignments.c
INCLUDE=./philo.h
OBJ:=$(SRC:.c=.o)
CFLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) -o $(NAME) $(CFLAGS) -I$(INCLUDE) -g

%.o: %.c
	cc -c $< -o $@ $(CFLAGS) -I$(INCLUDE) -g

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
