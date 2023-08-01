# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/01 05:16:02 by lsileoni          #+#    #+#              #
#    Updated: 2023/08/01 06:50:14 by lsileoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo
SRC=main.c \
	argument_parsing.c \
	assignments.c \
	timeutils.c \
	parsing_helpers.c \
	philo_utils.c \
	philo_checks.c \
	philo_actions.c \
	philo.c
OBJ:=$(SRC:.c=.o)
CFLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) -o $(NAME) $(CFLAGS)

%.o: %.c
	cc -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
