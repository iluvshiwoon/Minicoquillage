C_FILES = $(wildcard ../Tokenizer/*.c ../Tokenizer/*/*.c ../*.c ../Parser/*.c ../Utils/*.c)
C_FLAGS = -Wall -Werror -Wextra
INTERACTIVE = 0
TOKENIZER = 1

NAME = Minicoquillage
TEST = ./test

.PHONY: clean fclean re syntax token build leak build test

test: syntax token 

syntax: $(NAME)
	@bash $(TEST)/build_syntax_csv.sh $(TEST)/syntax_error_cmd.txt $(TEST)/syntax_error_test.csv
	@bash $(TEST)/tester_syntax.sh $(TEST)/syntax_error_test.csv $(CURDIR)/$(NAME)

token: $(NAME)
	@bash $(TEST)/tester_tokens.sh $(TEST)/tokens_test.csv $(CURDIR)/$(NAME)

$(NAME): $(C_FILES) | build
	@cc -g $(C_FLAGS) -D MODE=$(TOKENIZER) $^ -o $(NAME) -L ../42_MyLibC -lft -lreadline

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
