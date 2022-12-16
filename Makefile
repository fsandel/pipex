# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:53:10 by fsandel           #+#    #+#              #
#    Updated: 2022/12/16 10:45:03 by fsandel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex
BONUS			= pipex
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -pedantic

OBJ				= $(SRC:.c=.o)
OBJ_BONUS		= $(SRC_BONUS:.c=.o)

LIBFT_DIR		= libft
LIBFT_LIB		= libft.a
LIBFT			= $(LIBFT_DIR)/$(LIBFT_LIB)
LIBFT_GIT		= https://github.com/fsandel/libft

SRC				= main.c utils.c
SRC_BONUS		= main_bonus.c utils_bonus.c

HDR				= pipex.h
HDR_BONUS		= pipex_bonus.h


all:			$(LIBFT) $(NAME)

bonus:			$(LIBFT) $(BONUS)

$(NAME):		$(OBJ)
				$(CC) $(OBJ) $(LIBFT) -o $@ $(CFLAGS)

$(BONUS):		$(OBJ_BONUS)
				$(CC) $(OBJ_BONUS) $(LIBFT) -o $@ $(CFLAGS)

$(OBJ):			$(SRC) $(HDR)
				$(CC) -c $(SRC) $(CFLAGS)

$(OBJ_BONUS):	$(SRC_BONUS) $(HDR_BONUS)
				$(CC) -c $(SRC_BONUS) $(CFLAGS)

clean:
				@$(RM) $(OBJ) $(OBJ_BONUS)
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

.PHONY:			all clean fclean re libft clone_libft bonus
