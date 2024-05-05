# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 15:20:22 by fahmadia          #+#    #+#              #
#    Updated: 2023/12/13 12:02:10 by fahmadia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmylib.a
COPY_DEST = ./
OBJS = ./*.o

LIBFT_LIB = ./libft/libft.a
LIBFT = ./libft

LIBFTPRINTF_LIB = ./ft_printf/libftprintf.a
LIBFTPRINTF = ./ft_printf

COLOR_GREEN = \033[0;32m
COLOR_YELLOW = \033[0;33m
COLOR_END = \033[0m

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(LIBFTPRINTF_LIB)
	@make extract
	@make clean
	
extract:
	@cp $(LIBFT_LIB) $(COPY_DEST)
	@cp $(LIBFTPRINTF_LIB) $(COPY_DEST)
	@ar x ./libft.a
	@ar x ./libftprintf.a
	@ar rcs $(NAME) $(OBJS)
	@rm -f $(OBJS) "__.SYMDEF SORTED" ./libft.a ./libftprintf.a
	@echo "$(COLOR_GREEN)libft.a, ft_printf.a are merged and libmylib.a is created.$(COLOR_END)"

$(LIBFT_LIB): 
	@make bonus -C $(LIBFT)

$(LIBFTPRINTF_LIB):
	@make -C $(LIBFTPRINTF)

clean: 
	@rm -f $(OBJS)
	@cd $(LIBFT) && make clean
	@cd $(LIBFTPRINTF) && make clean

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make fclean -C $(LIBFTPRINTF)

re: 
	@make fclean
	@make $(NAME)

.PHONY: all clean fclean re
