# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 17:14:26 by ohladkov          #+#    #+#              #
#    Updated: 2024/04/07 16:53:45 by ohladkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# List of source files
SRCS	= ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		ft_isprint.c ft_strlcpy.c ft_memset.c ft_strlen.c ft_strncmp.c \
		ft_strnstr.c ft_tolower.c ft_toupper.c ft_strlcat.c ft_bzero.c \
		ft_memcpy.c ft_strdup.c ft_calloc.c ft_strchr.c ft_strrchr.c \
		ft_memchr.c ft_memcmp.c ft_substr.c ft_strjoin.c ft_memmove.c \
		ft_striteri.c ft_strmapi.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_itoa.c \
		../gnl/get_next_line.c ../gnl/get_next_line_utils.c

SRCSB	= ft_lstnew.c ft_lstsize.c ft_lstadd_front.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

# Name of the library
NAME	= libft.a

# List of objects files to be created
OBJS	= $(SRCS:.c=.o)

OBJSB	= $(SRCSB:.c=.o)

# Comiler
CC		= cc

# Compiler flags
CFLAGS	= -Wall -Wextra -Werror

# Header file
HEAD 	= libft.h

# Remove files
RM	= rm -f

# Build eveything
all:		$(NAME)

# Rule to built the library
$(NAME):	$(OBJS) 
		ar -rcs $(NAME) $(OBJS)

# Rule to built object files from source files
%.o: %.c	$(HEAD)
		$(CC) $(CFLAGS) -c -o $@ $<

bonus:		$(OBJSB)
		ar -rcs $(NAME) $(OBJSB)

# Clean up
clean:
		$(RM) $(OBJS)

# Remove built files
fclean:		clean
		$(RM) $(NAME)

# Rebuild everything~
re:		fclean all

# Mark phony targets
.PHONY:		all bonus clean fclean re
