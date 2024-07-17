C_FILES = $(wildcard ./Tokenizer/*.c ./Tokenizer/*/*.c)
# C_FLAGS = -Wall -Werror -Wextra
INTERACTIVE = 0
DEBUG = 1
TOKEN = 2
EXPANSION = 3

NAME = Minicoquillage
TEST = ./Tokenizer/test

.PHONY: all clean fclean re syntax token
.DEFAULT: all

all: $(NAME)

$(NAME): $(C_FILES) | build
	cc -g $(C_FLAGS) $^ -o $(NAME) -L ./42_MyLibC -lft -lreadline

syntax: $(C_FILES) | build
	cc -g $(C_FLAGS) -D MODE=$(DEBUG) $^ -o $(NAME) -L ./42_MyLibC -lft -lreadline
	bash $(TEST)/tester_syntax.sh $(TEST)/syntax_error_test.csv $(CURDIR)/$(NAME)

token: $(C_FILES) | build
	cc -g $(C_FLAGS) -D MODE=$(DEBUG) $^ -o $(NAME) -L ./42_MyLibC -lft -lreadline
	bash $(TEST)/tester_tokens.sh $(TEST)/tokens_test.csv $(CURDIR)/$(NAME)

leak: $(C_FILES) | build
	cc -g $(C_FLAGS) -D MODE=$(DEBUG) $^ -o $(NAME) -L ./42_MyLibC -lft -lreadline
	bash $(TEST)/leak.sh $(TEST)/leak_test.csv $(CURDIR)/$(NAME)

expansion: $(C_FILES) | build
	cc -g $(C_FLAGS) -D MODE=$(EXPANSION) $^ -o $(NAME) -L ./42_MyLibC -lft -lreadline
	bash $(TEST)/expansion.sh $(TEST)/expansion_test.csv $(CURDIR)/$(NAME)

build:
	$(MAKE) -C 42_MyLibC

clean:
	$(MAKE) -C 42_MyLibC clean

fclean: clean
	-rm -f $(NAME)
	-rm -f $(CHECKER)
	$(MAKE) -C 42_MyLibC fclean


re: fclean all
