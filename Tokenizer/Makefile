C_FILES = $(wildcard ../Tokenizer/*.c ../Tokenizer/*/*.c ../*.c ../Parser/*.c)
C_FLAGS = -Wall -Werror -Wextra
INTERACTIVE = 0
TOKENIZER = 1

NAME = Minicoquillage
TEST = ./test

.PHONY: clean fclean re syntax token
.DEFAULT: test

syntax: $(C_FILES) | build
	@cc -g $(C_FLAGS) -D MODE=$(TOKENIZER) $^ -o $(NAME) -L ../42_MyLibC -lft -lreadline
	@bash $(TEST)/tester_syntax.sh $(TEST)/syntax_error_test.csv $(CURDIR)/$(NAME)

token: $(C_FILES) | build
	@cc -g $(C_FLAGS) -D MODE=$(TOKENIZER) $^ -o $(NAME) -L ../42_MyLibC -lft -lreadline
	@bash $(TEST)/tester_tokens.sh $(TEST)/tokens_test.csv $(CURDIR)/$(NAME)

test: | syntax token

# leak: $(C_FILES) | build
# 	cc -g $(C_FLAGS) -D MODE=$(DEBUG) $^ -o $(NAME) -L ./42_MyLibC -lft -lreadline
# 	bash $(TEST)/leak.sh $(TEST)/leak_test.csv $(CURDIR)/$(NAME)

# expansion: $(C_FILES) | build
# 	cc -g $(C_FLAGS) -D MODE=$(EXPANSION) $^ -o $(NAME) -L ./42_MyLibC -lft -lreadline
# 	bash $(TEST)/expansion.sh $(TEST)/expansion_test.csv $(CURDIR)/$(NAME)

build:
	@$(MAKE) -C ../42_MyLibC >/dev/null

clean:
	@$(MAKE) -C ../42_MyLibC clean >/dev/null

fclean: clean
	@-rm -f $(NAME)
	@$(MAKE) -C ../42_MyLibC fclean >/dev/null

re: fclean test
