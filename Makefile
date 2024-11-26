C_FILES = $(filter-out $(wildcard ./*/test_*.c) ,$(wildcard ./42_MyLibC/libft/ft_strchr.c ./glob/*.c ./Builtins_V2/*.c ./Expand/*.c ./Tokenizer/*.c ./Tokenizer/*/*.c ./*.c ./Parser/*.c ./Utils/*.c ./Exec/*.c))
C_FLAGS = -Wall -Werror -Wextra

NAME = minicoquillage
TOKENIZER = ./Tokenizer/test
PARSER = ./Parser/test

TEST = ./final_test

.PHONY: all clean fclean re syntax token
.DEFAULT: all

all: $(NAME)

$(NAME): $(C_FILES) | build
	cc -g $(C_FLAGS) $^ -o $(NAME) -L ./42_MyLibC -lft -lreadline

# tokenizer:
# 	@$(MAKE) -sC ./Tokenizer

# parser:
# 	@$(MAKE) -sC ./Parser

test: $(C_FILES) | build
	@cc -g $(C_FLAGS) -D MODE=TEST $^ -o m_test -L ./42_MyLibC -lft -lreadline
	@echo "Amour Tu es Horrible" > a
	@echo "0123456789" > b
	@echo "prout" > c
	bash $(TEST)/final.sh $(TEST)/cmds_test.txt
	$(MAKE) clean


leak: $(NAME)
	echo "Amour Tu es Horrible" > a
	echo "0123456789" > b
	echo "prout" > c
	expect -f $(TEST)/expect_leak $(TEST)/cmds_leak.txt $(CURDIR)/$(NAME)
	$(MAKE) clean

ml: $(NAME)
	expect $(TEST)/expect_ml

build:
	$(MAKE) -C 42_MyLibC

clean:
	$(MAKE) -C 42_MyLibC clean
	-rm -f HOLA 'bonjour hello' d e hey hola* pwd a b c ls1
	-rm -rf dir/

fclean: clean
	-rm -f $(NAME)
	$(MAKE) -C 42_MyLibC fclean

re: fclean all
