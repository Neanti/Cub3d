# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: augay <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 14:46:12 by augay             #+#    #+#              #
#    Updated: 2020/01/17 14:46:13 by augay            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftcub3d.a
OPTION = -c
FLAG = -Wall -Wextra -Werror
OBJLIB_PATH = libft/
SRC = body.c calc_2.c locate.c parsing.c prepare_4.c \
body_1.c deal_color.c prepare_1.c save_body.c \
body_2.c error_1.c others.c prepare_2.c save_utils.c \
calc.c error_2.c others_2.c prepare_3.c
OBJ = $(SRC:.c=.o)
OBJLIB = ft_isdigit.o ft_memmove.o ft_strchr.o ft_strncmp.o ft_atoi.o ft_isprint.o ft_memset.o \
ft_strdup.o ft_strnstr.o ft_bzero.o ft_itoa.o ft_putchar_fd.o ft_strjoin.o ft_strrchr.o ft_calloc.o \
ft_memccpy.o ft_putendl_fd.o ft_strlcat.o ft_strtrim.o ft_isalnum.o ft_memchr.o ft_putnbr_fd.o ft_strlcpy.o \
ft_substr.o ft_isalpha.o ft_memcmp.o ft_putstr_fd.o ft_strlen.o ft_tolower.o ft_isascii.o ft_memcpy.o \
ft_split.o ft_strmapi.o ft_toupper.o get_next_line.o get_next_line_utils.o
OBJLIBP = $(addprefix $(OBJLIB_PATH),$(OBJLIB))

all: $(NAME)

$(NAME): mlibft $(OBJ)
	@ar rc $(NAME) $(OBJ) $(OBJLIBP)
clean:
	@rm -f $(OBJ)
	@cd libft && make clean
fclean: clean
	@rm -f $(NAME)
mlibft :
	cd libft && make
$(OBJ) :
	gcc $(FLAG) $(OPTION) $(SRC)
re: fclean all

.PHONY: all clean fclean re $(NAME)