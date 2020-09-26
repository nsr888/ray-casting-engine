# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/20 00:26:23 by ksinistr          #+#    #+#              #
#    Updated: 2020/09/20 17:48:14 by ksinistr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRC = cub3d.c \
	  cub3d_utils.c \
	  events.c \
	  parser.c \
	  parser_map_init.c \
	  parser_switch.c \
	  parser_map_fill_content.c \
	  game_loop.c \
	  game_loop_update.c \
	  game_loop_update2.c \
	  draw_minimap.c \
	  draw_minimap_utils.c \
	  raycasting.c \
	  raycasting_hit_vertical.c \
	  raycasting_hit_horizontal.c \
	  raycasting_utils.c \
	  render3d.c \
	  render3d_colors.c \
	  color.c \
	  draw_sprites.c \
	  draw_sprites_render.c \
	  writebmp.c \
	  checkmap.c
SRCS := $(addprefix src/, $(SRC)) \
	  gnl/get_next_line.c \
	  gnl/get_next_line_utils.c
INCLUDES = includes/cub3d.h \
	  includes/struct.h \
	  gnl/get_next_line.h
OBJ = $(patsubst %.c, %.o, $(SRCS))
CFLAGS = -Wall -Wextra -Werror -ggdb3
CC = gcc
LMLX = libmlx.dylib

.PHONY: all clean fclean re

all: $(NAME)

bonus: all

$(NAME): $(OBJ)
	cd libft && make bonus
	cd mlx && make && cp $(LMLX) ../
	$(CC) -Llibft -lft -Lmlx -lmlx -framework OpenGL \
		-framework AppKit $(OBJ) -o $(NAME)

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -Ilibft -Ignl -Imlx -c $< -o $@

clean:
	cd libft && make $@
	cd mlx && make $@ 
	rm -f $(OBJ)

fclean: clean
	cd libft && make $@
	rm -f $(LMLX)
	rm -f $(NAME)

re: fclean $(NAME)
