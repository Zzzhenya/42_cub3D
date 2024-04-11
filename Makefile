# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/15 18:20:36 by ohladkov          #+#    #+#              #
#    Updated: 2024/04/09 19:18:36 by ohladkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS_DIR	= src/

SRCS	= src/parce/cub_main.c src/parce/hook_key.c src/parce/file_handler.c \
		 src/parce/utils_cub.c src/parce/texture_handler.c src/parce/utils_file.c \
		src/parce/utils_arr.c  src/parce/utils_str.c src/parce/utils_free.c \
		src/parce/validation_map.c src/parce/validation_player.c src/parce/game_init.c \
		src/parce/mini_map.c 

OBJS	= $(SRCS:.c=.o)

# DEPS	= minilibx-linux/mlx.h
MLX_PATH	= minilibx-linux
MLX_NAME 	= libmlx.a
MLX			= $(MLX_PATH)/$(MLX_NAME)

LIBFT_PATH	= libft
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)/$(LIBFT_NAME)

GNL 		= gnl/get_next_line.h

CC			= cc
HEAD		= $(LIBFT_PATH)/libft.h $(MLX_PATH)/libmlx.h $(GNL)

CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address

LFLAGS	= -lX11 -lXext -lm

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT) $(MLX)
		$(CC) $(LFLAGS) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft $(MLX) -o $(NAME)

$(MLX):
	@make -sC $(MLX_PATH)

$(LIBFT):
	@make -sC $(LIBFT_PATH)

%.o: %.c
		$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@make -sC $(LIBFT_PATH) clean
	rm -f $(OBJS)

fclean:		clean
	@make -sC $(LIBFT_PATH) fclean
	rm -f $(NAME)

re:		fclean all
