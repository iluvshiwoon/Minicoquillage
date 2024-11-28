C_FILES = assign_quote.c assign_token.c assign_token_utils.c atom.c cd.c cd_utils.c check_syntax.c check_syntax_utils1.c check_syntax_utils.c close_pipe.c Debug_utils.c echo.c env.c Error.c error_exit.c exec.c exec_tree.c exec_utils.c exit.c expand_assign.c expand.c expand_utils1.c expand_utils.c exp_exp.c exp_exp_utils.c exp_glob.c export.c export_utils.c exp_split.c exp_split_utils.c Free.c globbing.c glob.c glob_utils.c heredoc.c heredoc_clean.c heredoc_quote.c heredoc_utils.c malloc_wrap.c Minicoquillage.c mini_ft_itoa.c mini_ft_split.c mini_ft_strdup.c mini_ft_strjoin.c mini_ft_strtrim.c mini_ft_substr.c parser.c parser_utils.c path.c path_utils.c pipeline.c pipeline_utils.c Prompt.c pwd.c redirect.c redirect_utils1.c redirect_utils.c signal.c Tokenizer.c Tokens.c unset.c Utils.c Utils_Tokens1.c Utils_Tokens2.c Utils_Tokens3.c Utils_Tokens.c
C_FLAGS = -Wall -Werror -Wextra

NAME = minicoquillage
TEST = ./final_test

.PHONY: all clean fclean re syntax token
.DEFAULT: all

all: $(NAME)

$(NAME): $(C_FILES) | build
	cc -g $(C_FLAGS) $^ -o $(NAME) -L ./42_MyLibC -lft -lreadline

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
	expect -f $(TEST)/expect_leak $(TEST)/cmds_leak.txt ./$(NAME)
	$(MAKE) clean

build:
	$(MAKE) -C 42_MyLibC

clean:
	$(MAKE) -C 42_MyLibC clean
	-rm -f HOLA 'bonjour hello' d e hey hola* pwd a b c ls1

fclean: clean
	-rm -f $(NAME)
	$(MAKE) -C 42_MyLibC fclean

re: fclean all
