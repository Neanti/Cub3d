# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: augay <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/10 12:59:44 by augay             #+#    #+#              #
#    Updated: 2019/10/21 10:40:34 by augay            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
OPTION = -c
FLAG = -Wall -Wextra -Werror
SRC = get_next_line.c get_next_line_utils.c ft_isdigit.c ft_memmove.c ft_strchr.c ft_strncmp.c ft_atoi.c ft_isprint.c ft_memset.c ft_strdup.c ft_strnstr.c ft_bzero.c ft_itoa.c ft_putchar_fd.c ft_strjoin.c ft_strrchr.c ft_calloc.c ft_memccpy.c ft_putendl_fd.c ft_strlcat.c ft_strtrim.c ft_isalnum.c ft_memchr.c ft_putnbr_fd.c ft_strlcpy.c ft_substr.c ft_isalpha.c ft_memcmp.c ft_putstr_fd.c ft_strlen.c ft_tolower.c ft_isascii.c ft_memcpy.c	ft_split.c ft_strmapi.c ft_toupper.c
OBJ = get_next_line.o get_next_line_utils.o ft_isdigit.o ft_memmove.o ft_strchr.o ft_strncmp.o ft_atoi.o ft_isprint.o ft_memset.o ft_strdup.o ft_strnstr.o ft_bzero.o ft_itoa.o ft_putchar_fd.o ft_strjoin.o ft_strrchr.o ft_calloc.o ft_memccpy.o ft_putendl_fd.o ft_strlcat.o ft_strtrim.o ft_isalnum.o ft_memchr.o ft_putnbr_fd.o ft_strlcpy.o ft_substr.o ft_isalpha.o ft_memcmp.o ft_putstr_fd.o ft_strlen.o ft_tolower.o ft_isascii.o ft_memcpy.o	ft_split.o ft_strmapi.o ft_toupper.o


all: $(NAME)

$(NAME):
	gcc $(FLAG) $(OPTION) $(SRC)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)

re: fclean all
