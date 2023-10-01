# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myagiz <myagiz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 14:44:05 by myagiz            #+#    #+#              #
#    Updated: 2023/09/29 12:30:29 by myagiz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -framework OpenGL -framework AppKit

SRC_DIR = src
LIBFT_DIR = libft
MLX_DIR = mlx

LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

SRC_FILES = ./src/main.c \
            ./src/loop.c \
            ./src/error.c \
            ./src/checks.c \
            ./src/map_read.c \
            ./src/dda_func.c \
            ./src/draw.c \
            ./src/draw_rays.c \
            ./src/start_window.c \
            ./src/buttons_func.c \
            ./src/get_xpm_file.c \
            ./src/get_line.c \
            ./src/get_line_utils.c \

OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(SRC_DIR)/*.o
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
