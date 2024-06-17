C_FILES = $(wildcard ./*/*.c)
# C_FLAGS = -Wall -Werror -Wextra
NAME = a.out
TEST = ./Tokenizer/test

.PHONY: all clean fclean re syntax token
.DEFAULT: all

all: $(NAME)

$(NAME): $(C_FILES) | build
	cc $(C_FLAGS) $^ -o $(NAME) -L ./42_MyLibC -lft -lreadline

syntax: all
	bash $(TEST)/tester_syntax.sh $(TEST)/syntax_error_test.csv $(CURDIR)/$(NAME)

token: all
	bash $(TEST)/tester_tokens.sh $(TEST)/tokens_test.csv $(CURDIR)/$(NAME)

build:
	$(MAKE) -C 42_MyLibC

clean:
	$(MAKE) -C 42_MyLibC clean

fclean: clean
	-rm -f $(NAME)
	-rm -f $(CHECKER)
	$(MAKE) -C 42_MyLibC fclean


re: fclean all
