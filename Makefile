# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 12:48:38 by abentaye          #+#    #+#              #
#    Updated: 2024/11/09 15:31:09 by abentaye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D
CC := cc
CFLAGS := -Wall -Wextra -Werror
MLXPATH = ./minilibx
MLXFLAGS := -L$(MLXPATH) -lmlx -framework OpenGL -framework AppKit
RM := @rm -f
SRC :=	src/main.c \

GNL := get_next_line.c get_next_line_utils.c

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all: $(NAME)

$(NAME): $(SRC) $(MLXPATH)/libmlx.dylib
	@echo $(Y)"Compiling $(NAME)..."$(X)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(MLXFLAGS)
	@echo $(G)"$(NAME) compiled successfully."$(X)

$(MLXPATH)/libmlx.dylib:
	@echo $(Y)"Cleaning MiniLibX..."$(X)
	@$(MAKE) -C $(MLXPATH) clean
	@echo $(Y)"Compiling MiniLibX..."$(X)
	@$(MAKE) -C $(MLXPATH)
	@echo $(G)"MiniLibX compiled successfully."$(X)

clean:
	@echo $(Y)"Cleaning $(NAME)..."$(X)
	@$(RM) $(NAME)
	@echo $(G)"$(NAME) cleaned."$(X)


fclean: clean
	@echo $(Y)"Cleaning all..."$(X)
	@$(RM) $(MLXPATH)/libmlx.dylib
	@echo $(G)"All cleaned."$(X)

re : fclean all