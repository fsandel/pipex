# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:53:10 by fsandel           #+#    #+#              #
#    Updated: 2022/12/03 16:35:56 by fsandel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

OBJ_DIR			= obj
OBJ_FILES		= $(SRC_FILES:.c=.o)
OBJ				= $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

LIBFT_DIR		= libft
LIBFT_LIB		= libft.a
LIBFT			= $(LIBFT_DIR)/$(LIBFT_LIB)
LIBFT_GIT		= https://github.com/fsandel/libft


SRC_DIR			= src
SRC				= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRC_FILES		= main.c

$(NAME): $(LIBFT) $(OBJ)
				@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ): $(SRC)
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)


all:			$(NAME)

clean:
				@$(RM) $(OBJ)
				@rmdir $(OBJ_DIR)
				@make clean -C $(LIBFT_DIR)

fclean:			
				make clean
				$(RM) $(NAME)
				make fclean -C $(LIBFT_DIR)

re:
				make fclean
				make all

libft:			$(LIBFT)

$(LIBFT):
				make clone_libft
				make -C $(LIBFT_DIR)

clone_libft:
ifeq ($(shell (ls | grep libft)), libft)
				@echo "libft found"
else
				@echo "no libft found, downloading now"
				@git clone $(LIBFT_GIT) $(LIBFT_DIR)
endif

.PHONY:			all clean fclean re lib 
