# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 14:25:53 by ncasteln          #+#    #+#              #
#    Updated: 2023/12/13 11:59:40 by fahmadia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GENERAL INSTRUCTIONS
#	Installing readline in Debian: apt-get install libreadline-dev
#	kill -9 $(jobs -ps) - kill all the suspended job, done with ctrl-Z

VPATH = ./src/ \
	./src/builtins \
	./src/builtins/export \
	./src/env \
	./src/executor \
	./src/expansion \
	./src/here_doc \
	./src/lexer \
	./src/parser \
	./src/print_utils \
	./src/signals \
	./src/utils

BUILTINS = cd.c \
	print_env.c \
	echo.c \
	export.c \
	sort_env.c \
	sort_env_utils.c \
	pwd.c \
	unset.c \
	exit.c \
	update_env.c

EXECUTOR = executor.c \
	execute_single_cmd.c \
	execute_pipechain.c \
	child_pipechain.c \
	child_single_cmd.c \
	resolve_cmd_path.c \
	cmd_path_utils.c \
	redirect_to_pipes.c \
	redirect_to_explicit.c \
	run_builtin.c \
	parent.c \

ENV = init_env.c \
	create_var_content.c \
	del_var_content.c \
	get_env_custom.c \
	convert_to_dptr.c \
	create_essential_env.c

EXPANSION = check_expansion.c \
	expansion.c \
	expansion_utils.c \
	build_str.c \
	check_quote_removal.c \
	quote_removal.c \
	translation_op.c

HERE_DOC = here_doc.c \
	eofs.c \
	get_interactive_input.c \
	tmp_file_creation.c

LEXER = lexer.c \
	tokenize_input.c \
	del_tokens.c \
	store_tokens_in_nodes.c \
	read_each_char.c \
	check_each_token_string.c \
	handle_quotes.c \
	assign_quote_status_to_tokens.c \
	assign_type_to_tokens.c \
	merge_two_less_or_greater_than.c \
	delete_spaces.c \
	merge_dollar_char_with_next_token.c \
	merge_quoted_tokens.c \
	check_following_space.c \
	join_content_str_of_two_nodes.c \
	remove_a_token_node.c \
	merge_strings.c

PARSER = check_for_syntax_err.c \
	build_syntax_tree.c \
	update_cmd_node.c \
	update_cmd_args.c \
	update_cmd_redir.c \
	free_syntax_tree.c \
	parser.c

PRINT_UTILS = print_syntax_tree.c \
	print_tokens.c \
	print_expansion.c \
	print_tree_construction.c

SIGNALS = sig_handler.c

UTILS = terminal_config.c \
	free_data.c \
	ft_strcmp.c \
	error.c \
	get_wd.c

SRCS = minishell.c \
	$(BUILTINS) \
	$(ENV) \
	$(EXECUTOR) \
	$(EXPANSION) \
	$(HERE_DOC) \
	$(LEXER) \
	$(PARSER) \
	$(PRINT_UTILS) \
	$(SIGNALS) \
	$(UTILS)

OBJS_PATH = ./objs
OBJS = $(patsubst %.c, $(OBJS_PATH)/%.o, $(SRCS))

CC = cc
CFLAGS = -c -g -Wall -Wextra -Werror
NAME = minishell
MYLIB_PATH = ./mylib
MYLIB = $(MYLIB_PATH)/libmylib.a
INCLUDE = -I./include -I./mylib/libft -I./mylib/ft_printf

COLOR_GREEN = \033[0;32m
COLOR_YELLOW = \033[0;33m
COLOR_END = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(MYLIB) Makefile
	@$(CC) $(OBJS) -L$(MYLIB_PATH) -lreadline -lmylib -ltermcap -o $(NAME)
	@echo "$(COLOR_GREEN)minishell is created.$(COLOR_END)"

$(OBJS_PATH)/%.o: %.c
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

$(MYLIB):
	@cd $(MYLIB_PATH) && make

clean:
	@rm -f $(OBJS)
	@cd ./$(MYLIB_PATH) && make clean
	@echo "$(COLOR_YELLOW)minishell object files are deleted.$(COLOR_END)"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJS_PATH)
	@cd ./$(MYLIB_PATH) && make fclean
	@echo "$(COLOR_YELLOW)minishell object files and minishell executable file are deleted.$(COLOR_END)"

re: fclean all

.PHONY: all clean fclean re test
