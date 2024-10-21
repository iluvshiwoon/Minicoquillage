C_FILES = $(wildcard ../Tokenizer/*.c ../Tokenizer/*/*.c ../*.c ../Parser/*.c ../Utils/*.c ../Exec/*.c)
C_FLAGS = -Wall -Werror -Wextra
INTERACTIVE = 0
TOKENIZER = 1
PARSER = 2

NAME = Minicoquillage
TEST = ./test

.PHONY: clean fclean re parser build build test

test: parser

parser: $(NAME)
	@bash $(TEST)/parser_build.sh $(TEST)/parser_cmd.txt $(TEST)/parser_test.csv
	@bash $(TEST)/parser_test.sh $(TEST)/parser_test.csv

$(NAME): $(C_FILES) | build
	@cc -g $(C_FLAGS) -D MODE=$(PARSER) $^ -o $(NAME) -L ../42_MyLibC -lft -lreadline

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
