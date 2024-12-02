# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 13:35:51 by rpepi             #+#    #+#              #
#    Updated: 2024/12/02 14:13:10 by rpepi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g3
MLXPATH = ./minilibx
LIBFT = ./libft
LIBFTA = ./libft/libft.a
MLXFLAGS := -L$(MLXPATH) -lmlx -framework OpenGL -framework AppKit 
RM := @rm -f
SRC := src/main.c \
		src/display/window.c \
		src/get_next_line/get_next_line.c \
		src//get_next_line/get_next_line_utils.c \
		src/process_cub/map_reader.c \
		src/process_cub/file_reader.c \
		src/process_cub/struct_handler.c \
		src/process_cub/parse_map.c \
		src/error.c \
		src/raycasting/raycasting.c \
		src/raycasting/moves.c \
		src/raycasting/rotation.c \
		src/raycasting/events.c \
		src/raycasting/doors.c

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

NAME = cub3D

all: $(NAME)

$(LIBFTA):
	@echo $(Y)"Compiling libft..."$(X)
	@$(MAKE) -C $(LIBFT)
	@echo $(G)"libft compiled successfully."$(X)

$(NAME): $(SRC) $(LIBFTA) $(MLXPATH)/libmlx.a
	@echo $(Y)"Compiling $(NAME)..."$(X)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LIBFTA) $(MLXFLAGS)
	@echo $(G)"$(NAME) compiled successfully."$(X)

$(MLXPATH)/libmlx.a:
	@$(MAKE) -C $(MLXPATH) clean
	@echo $(Y)"Compiling MiniLibX..."$(X)
	@$(MAKE) -C $(MLXPATH)
	@echo $(G)"MiniLibX compiled successfully."$(X)

clean:
	@$(RM) $(NAME)
	@echo $(R)"Cleaned $(NAME)"$(X)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(MLXPATH) clean
	@echo $(R)"Cleaned libft and MiniLibX"$(X)

re: fclean all