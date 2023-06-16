NAME=philosophers
LIBFT=./libft/build/libft.a

all: $(NAME)

$(NAME): $(LIBFT)
	cc main.c -o philosophers -Wall -Wextra -Werror -L./libft/build -lft -I./libft/src/
 
$(LIBFT):
	make all -C ./libft/

clean:
	make clean -C ./libft/

fclean:
	make clean -C ./libft/
	rm -f $(NAME)
