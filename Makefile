C_FILES = $(wildcard ./Tokenizer/*.c ./Tokenizer/*/*.c ./*.c ./Parser/*.c)
C_FLAGS = -Wall -Werror -Wextra

NAME = Minicoquillage
TEST = ./test

.PHONY: all clean fclean re syntax token
.DEFAULT: all

all: $(NAME)

$(NAME): $(C_FILES) | build
	cc -g $(C_FLAGS) $^ -o $(NAME) -L ./42_MyLibC -lft -lreadline

tokenizer:
	@$(MAKE) -sC ./Tokenizer

leak: $(NAME)
	expect -f $(TEST)/expect_leak $(TEST)/leak_test.csv $(CURDIR)/$(NAME)

build:
	$(MAKE) -C 42_MyLibC

clean:
	$(MAKE) -C 42_MyLibC clean

fclean: clean
	-rm -f $(NAME)
	$(MAKE) -C 42_MyLibC fclean


re: fclean all
