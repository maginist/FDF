# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/21 10:08:34 by maginist          #+#    #+#              #
#    Updated: 2019/10/04 12:39:21 by floblanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC_NAME =	run_fdf.c 		\
			parcing_arg.c	\
			main.c			\
			algo_segment.c 	\
			calc_color.c	\

SRC_PATH = ./src/

OBJ_PATH = ./obj/

INC_PATH = ./include/
INC_NAME = fdf.h


LIBFT				=	./libprintf/
LIBFTA				=	libprintf.a
LIBFTINCLUDES		=	./libprintf/include/

FDF_FLAGS = -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

CC = gcc

CFLAGS = -Wall -Werror -Wextra 

# Colors
CK = $'\033[30m$'
_RED = $'\033[31m$'
_GREEN = $'\033[32m$'
_YELLOW = $'\033[33m$'
_BLUE = $'\033[34m$'
_PURPLE = $'\033[35m$'
_CYAN = $'\033[36m$'
_GREY = $'\033[37m$'
_END=$'\033[0m$'


INC	=	$(addprefix $(INC_PATH), $(INC_NAME))
SRC =	$(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ =	$(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))

.PHONY :	all clean fclean re

all: $(NAME)

$(LIBFT)/$(LIBFTA):
	@make -C $(LIBFT) -j 100
	@echo "$(_GREEN)[ LIBPRINTF DONE ]$(_END)"

$(NAME) : $(LIBFT)/$(LIBFTA) $(OBJ)
		@echo "\n"
		@echo "$(_RED)|_-_-_-_-_-_-_-_-_-_-_-_-|$(_END)"
		@echo "|    COMPILING FDF       |"
		@echo "$(_RED)|_-_-_-_-_-_-_-_-_-_-_-_-|$(_END)"
		@echo "\n"
		@$(CC) $(FDF_FLAGS) -o $(NAME) $(OBJ) $(LIBFT)/$(LIBFTA)
		@echo "$(_GREEN)[ FDF DONE ]$(_END)"

clean :
	@make clean -C $(LIBFT)
	@rm -rf $(OBJ_PATH)
	@echo "$(_BLUE)======< CLEAN PROJECT & LIBPRINTF DONE >======$(_END)"
	@rm -f ./libprintf.a

fclean : clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)
	@echo "$(_BLUE)======< FCLEAN PROJECT & LIBPRINTF DONE >======$(_END)"

re : fclean all

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
	@mkdir -p $(OBJ_PATH)
	@$(CC) -I $(LIBFTINCLUDES) -I $(INC_PATH) -c $< -o $@