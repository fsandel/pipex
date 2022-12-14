# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: florian <florian@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:53:10 by fsandel           #+#    #+#              #
#    Updated: 2022/12/14 20:56:45 by florian          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

DEFINITIONS		=-D BONUS=0

OBJ				= $(SRC:.c=.o)

LIBFT_DIR		= libft
LIBFT_LIB		= libft.a
LIBFT			= $(LIBFT_DIR)/$(LIBFT_LIB)
LIBFT_GIT		= https://github.com/fsandel/libft

SRC				= main.c utils.c

HDR				= pipex.h


all:			$(LIBFT) $(NAME)

bonus: make change_def $(LIBFT) $(NAME)

change_def:
				$(MAKE) DEFINITIONS="-D BONUS=1"

$(NAME):$(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $@ $(CFLAGS) $(DEFINITIONS)

$(OBJ):$(SRC) $(HDR)
	$(CC) -c $(SRC) $(CFLAGS) $(DEFINITIONS)

clean:
				@$(RM) $(OBJ)
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
