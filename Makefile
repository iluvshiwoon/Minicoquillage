C_FILES = $(filter-out $(wildcard ./*/test_*.c) ,$(wildcard ./glob/*.c ./Builtins/*.c ./Expand/*.c ./Tokenizer/*.c ./Tokenizer/*/*.c ./*.c ./Parser/*.c ./Utils/*.c ./Exec/*.c))
C_FLAGS = -Wall -Werror -Wextra

NAME = Minicoquillage
TOKENIZER = ./Tokenizer/test
PARSER = ./Parser/test
LEAK = $(TOKENIZER)/syntax_error_cmd.txt $(TOKENIZER)/tokens_cmd.txt $(PARSER)/parser_cmd.txt

TEST = ./test

.PHONY: all clean fclean re syntax token
.DEFAULT: all

all: $(NAME)

$(NAME): $(C_FILES) | build
	cc -g $(C_FLAGS) $^ -o $(NAME) -L ./42_MyLibC -lft -lreadline

tokenizer:
	@$(MAKE) -sC ./Tokenizer

parser:
	@$(MAKE) -sC ./Parser

leak: $(NAME)
	cat $(LEAK) > $(TEST)/leak_test.csv
	expect -f $(TEST)/expect_leak $(TEST)/leak_test.csv $(CURDIR)/$(NAME)

ml: $(NAME)
	expect $(TEST)/expect_ml

build:
	$(MAKE) -C 42_MyLibC

clean:
	$(MAKE) -C 42_MyLibC clean

fclean: clean
	-rm -f $(NAME)
	$(MAKE) -C 42_MyLibC fclean


re: fclean all
