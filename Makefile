# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:53:10 by fsandel           #+#    #+#              #
#    Updated: 2022/12/09 19:49:27 by fsandel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex
CC				= cc
RM				= rm -f
CFLAGS			= #-Wall -Wextra -Werror


OBJ				= $(SRC:.c=.o)

LIBFT_DIR		= libft
LIBFT_LIB		= libft.a
LIBFT			= $(LIBFT_DIR)/$(LIBFT_LIB)
LIBFT_GIT		= https://github.com/fsandel/libft

SRC				= main.c utils.c

HDR				= pipex.h


all:			$(LIBFT) $(NAME)

$(NAME):$(OBJ)
	$(CC) $^ $(LIBFT) -o $@ $(CFLAGS)

$(OBJ):$(SRC)
	$(CC) -c $^ $(CFLAGS)

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

test:
				@echo $(OBJ)
				@echo $(SRC)

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
