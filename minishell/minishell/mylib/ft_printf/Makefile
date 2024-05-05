# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 19:48:22 by fahmadia          #+#    #+#              #
#    Updated: 2023/10/17 15:49:37 by fahmadia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = count_num_of_digits.c\
	find_format_spec.c\
	to_power.c\
	ft_printf.c\
	print_c.c\
	print_i.c\
	print_p.c\
	print_percent.c\
	print_s.c\
	print_x.c\
	putnbr_long_int.c\
	print_without_format_spec.c\

OBJS_PATH = ./objs
OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -c -g -Wall -Wextra -Werror

NAME = libftprintf.a

LIBFT_LIB = ../libft/libft.a

LIBFT = ../libft

COLOR_GREEN = \033[0;32m
COLOR_YELLOW = \033[0;33m
COLOR_END = \033[0m

all: $(NAME)

$(NAME): $(SRCS) $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(COLOR_GREEN)ft_printf.a is created without bonus object files.$(COLOR_END)"

%.o: %.c
	@$(CC) $(CFLAGS) $< -o $@

clean: 
	@rm -f $(OBJS)
	@echo "$(COLOR_YELLOW)ft_printf object files are deleted.$(COLOR_END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR_YELLOW)ft_printf object files and ft_printf.a are deleted.$(COLOR_END)"

re: 
	@make fclean
	@make fclean -C $(LIBFT)
	@make $(NAME)

.PHONY: all clean fclean re
