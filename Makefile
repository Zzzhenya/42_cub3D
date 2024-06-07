# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/15 18:20:36 by ohladkov          #+#    #+#              #
#    Updated: 2024/06/07 15:33:12 by ohladkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D


SRCS		=	src/cub_main.c \
				src/parce/file_handler.c \
				src/parce/elem_handler.c \
				src/parce/utils_cub.c \
				src/parce/utils_angle.c \
				src/parce/utils_file.c \
				src/parce/utils_arr.c \
				src/parce/utils_str.c \
				src/parce/utils_free.c \
				src/parce/utils_free_data.c \
				src/parce/validation_player.c \
				src/parce/validation_map.c \
				src/parce/validation_map_utils.c \
				src/parce/map_duplication.c \
				src/game/start_game.c \
				src/game/mini_map.c \
				src/game/hook_key.c \
				src/game/utils_draw.c \
				src/game/utils_draw2.c \
				src/game/color_buf.c \
				src/raycasting/raycasting.c \
				src/raycasting/render_walls.c \
				src/raycasting/ray_init.c \
				src/raycasting/utils_raycasting.c

OBJS	= $(SRCS:.c=.o)

MLX_PATH	= minilibx-linux
MLX_NAME 	= libmlx.a
MLX			= $(MLX_PATH)/$(MLX_NAME)

LIBFT_PATH	= libft
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)/$(LIBFT_NAME)

GNL 		= gnl/get_next_line.h

CC			= cc
HEAD		= $(LIBFT_PATH)/libft.h $(MLX_PATH)/libmlx.h $(GNL)

CFLAGS	= -Wall -Wextra -Werror -O3

LFLAGS	= -lX11 -lXext -lm

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT) $(MLX)
		$(CC) $(LFLAGS) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft -lm $(MLX) -o $(NAME)

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

