# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 12:24:20 by fahmadia          #+#    #+#              #
#    Updated: 2023/10/11 11:01:42 by fahmadia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_itoa.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_split.c\
	ft_strchr.c\
	ft_strdup.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strmapi.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strtrim.c\
	ft_substr.c\
	ft_tolower.c\
	ft_toupper.c

BONUS = ft_lstadd_back.c\
	ft_lstadd_front.c\
	ft_lstclear.c\
	ft_lstdelone.c\
	ft_lstiter.c\
	ft_lstlast.c\
	ft_lstmap.c\
	ft_lstnew.c\
	ft_lstsize.c

CC = cc

CFLAGS = -c -g -Wall -Wextra -Werror

NAME = libft.a

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

COLOR_GREEN = \033[0;32m
COLOR_YELLOW = \033[0;33m
COLOR_END = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(COLOR_GREEN)libft.a is created without bonus object files.$(COLOR_END)"

%.o: %.c
	@$(CC) $(CFLAGS) $< -o $@
	
clean:
	@rm -f $(OBJS) $(BONUS_OBJS)
	@echo "$(COLOR_YELLOW)libft object files are deleted.$(COLOR_END)"

fclean: clean
	@rm -f $(NAME) 
	@echo "$(COLOR_YELLOW)libft object files and libft.a are deleted.$(COLOR_END)"

re: fclean $(NAME)

bonus: $(OBJS) $(BONUS_OBJS)
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "$(COLOR_GREEN)libft.a is created with bonus object files.$(COLOR_END)"
	
.PHONY: all clean fclean re bonus
