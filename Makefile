# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 17:15:36 by bmunoz-c          #+#    #+#              #
#    Updated: 2025/04/06 15:53:35 by borjamc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

#_____Compiler_____#
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -Ofast

# Detect OS for MLX linking
UNAME_S		:= $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	# macOS frameworks
	MLX_SYS_FLAGS	= -framework Cocoa -framework OpenGL -framework IOKit

	# Homebrew on Mac Intel
	GLFW_LIB		= -L/usr/local/opt/glfw/lib -lglfw
	GLFW_INC		= -I/usr/local/opt/glfw/include

	# Add Homebrew paths
	MLX_SYS_FLAGS	+= $(GLFW_LIB)
	INC				+= $(GLFW_INC)
else
	# Linux (Debian/Ubuntu campus 42)
	MLX_SYS_FLAGS = -ldl -lglfw -pthread -lm

	# Standard include/lib paths on most Linux distros
	GLFW_LIB = -L/usr/lib -lglfw
	GLFW_INC = -I/usr/include

	MLX_SYS_FLAGS += $(GLFW_LIB)
	INC += $(GLFW_INC)
endif


#_____Minilibx_____#
MLX_DIR		= inc/MLX42/
MLX_INC		= -I$(MLX_DIR)/include
MLX_LIB		= $(MLX_DIR)/build/libmlx42.a

#_____Libft_____#
LIBFT_EXEC	= inc/libft/libft.a
LIBS		= $(MLX_LIB) -Linc/libft -lft $(MLX_SYS_FLAGS)
INC			= -Iinc $(MLX_INC)

#_____Headers_____#
HEADER		= inc/test.h

#______Directories______#
SRC_DIR		= src/
OBJ_DIR		= obj/

#______Sources_____#
SRC_F 		:= main.c \
         		test/test.c \
				render/raycasting.c \
				render/raycasting_init.c \
				render/render_loop.c

SRC			= $(addprefix $(SRC_DIR), $(SRC_F))
OBJ			= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

#_____Colors_____#
DEF_COLOR	= \033[1;39m
WHITE_BOLD	= \033[1m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
CIAN		= \033[1;36m

#________Rules________#
all: libmlx libft $(NAME)

$(NAME): $(OBJ) $(LIBFT_EXEC)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS) $(INC)
	@echo "$(RED)$(NAME) $(BLUE)is ready to work!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) Makefile | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "$(WHITE_BOLD)Object$(YELLOW) $@ $(GREEN)compiled!$(DEF_COLOR)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) \
		$(OBJ_DIR)parsing \
		$(OBJ_DIR)textures \
		$(OBJ_DIR)utils \
		$(OBJ_DIR)checker \
		$(OBJ_DIR)test \
		$(OBJ_DIR)render
	@echo "$(WHITE_BOLD)Created obj dir!$(DEF_COLOR)"



libmlx:
	@echo "$(YELLOW)Building MLX42...$(DEF_COLOR)"
	@cmake -S $(MLX_DIR) -B $(MLX_DIR)/build
	@cmake --build $(MLX_DIR)/build -j4

libft: $(LIBFT_EXEC)

$(LIBFT_EXEC):
	@$(MAKE) -C inc/libft --no-print-directory

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C inc/libft fclean --no-print-directory
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)/build

re: fclean all

.PHONY: all clean fclean re libmlx libft