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

NAME = cub3d
TMP_PATH = ./tmp/
SRC_PATH = ./srcs/
LIBFT_PATH = ./libft/libft.a
MLX_PATH = /usr/local/lib/libmlx.a
SRCS = body.c       calc_2.c     locate.c     parsing.c    prepare_4.c \
body_1.c     deal_color.c main.c       prepare_1.c  save_body.c \
body_2.c     error_1.c    others.c     prepare_2.c  save_utils.c \
calc.c       error_2.c    others_2.c   prepare_3.c

FLAGS = -Wall -Werror -Wextra -framework OpenGL -framework Appkit
FLAG_C = -Wall -Wextra -Werror
OBJ = $(SRCS:.c=.o)
OBJF = $(addprefix $(TMP_PATH),$(OBJ))
CC = gcc

all: $(NAME)

$(NAME): $(OBJF)
	@cd ./libft && make
	gcc $(FLAGS) -I $(SRC_PATH) $(OBJF) $(LIBFT_PATH) $(MLX_PATH) -o $(NAME)

$(TMP_PATH)%.o: $(SRC_PATH)%.c ./srcs/cub.h
	@mkdir -p $(TMP_PATH)
	@gcc $(FLAG_C) -I./srcs/ -c $< -o $@

clean:
	@rm -rf save.bmp
	@rm -rf $(TMP_PATH)
	@cd ./libft && make fclean

fclean: clean
	@rm -f $(NAME)

re: fclean all