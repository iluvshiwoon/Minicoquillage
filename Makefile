C_FILES = $(wildcard ./*.c)
C_FLAGS = -Wall -Werror -Wextra
NAME = minishell

.PHONY: all clean fclean re
.DEFAULT: all

all: $(NAME)

$(NAME): $(C_FILES) | build
	$(CC) -O2 -g $^ -o $(NAME)

build:
	mkdir -p build

clean:
	rm -rf build

fclean: clean
	-rm -f $(NAME)

re: fclean all
