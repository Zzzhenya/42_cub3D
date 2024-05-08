# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/15 18:20:36 by ohladkov          #+#    #+#              #
#    Updated: 2024/04/21 16:19:21 by ohladkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS_DIR	= src_2/

SRCS	= src_2/parce/cub_main.c src_2/parce/hook_key.c src_2/parce/file_handler.c \
		src_2/parce/utils_cub.c src_2/parce/texture_handler.c src_2/parce/utils_file.c \
		src_2/parce/utils_arr.c  src_2/parce/utils_str.c src_2/parce/utils_free.c \
		src_2/parce/validation_player.c src_2/parce/game_init.c \
		src_2/parce/mini_map.c src_2/parce/utils_intersection.c src_2/parce/raycasting.c \
		

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

CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address

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


# NAME        = cub3D

# SUBFOLDERSRC = . parce
# BASEPATHSRC = ./src_2/
# PATHSRC     = $(addprefix $(BASEPATHSRC), $(SUBFOLDERSRC))

# SRCS        = $(foreach dir,$(PATHSRC),$(wildcard $(dir)/*.c)) // not allowed
# OBJS_DIR    = build
# OBJS        = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

# INCLUDE_DIR = ./include
# HEADERS     = cub3d_2.h

# MLX_PATH    = minilibx-linux
# MLX_NAME    = libmlx.a
# MLX         = $(MLX_PATH)/$(MLX_NAME)

# LIBFT_PATH  = libft
# LIBFT_NAME  = libft.a
# LIBFT       = $(LIBFT_PATH)/$(LIBFT_NAME)

# GNL         = gnl/get_next_line.h

# CC          = cc
# CFLAGS      = -Wall -Wextra -Werror #-g -fsanitize=address
# LFLAGS      = -Llibft -lft -L$(MLX_PATH) -lmlx -lX11 -lXext -lXrandr -lm

# VPATH       = $(PATHSRC)

# .PHONY: all clean fclean re

# all:        $(NAME)

# $(NAME):	$(OBJS) $(LIBFT) $(MLX)
# 			$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

# $(LIBFT):
# 	@make -sC $(LIBFT_PATH)

# $(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
# 			$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(MLX_PATH) -c -o $@ $<

# $(OBJS_DIR):
# 			mkdir -p $(OBJS_DIR)

# $(HEADERS):         $(INCLUDE_DIR)
# 			cp your_header.h $(INCLUDE_DIR)

# $(INCLUDE_DIR):
# 			mkdir -p $(INCLUDE_DIR)

# clean:
# 	@make -sC $(LIBFT_PATH) clean
# 	rm -rf $(OBJS_DIR)

# fclean: clean
# 	@make -sC $(LIBFT_PATH) fclean
# 	rm -f $(NAME)

# re:	fclean all


