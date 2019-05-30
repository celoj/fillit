# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/21 15:36:34 by dcelojev          #+#    #+#              #
#    Updated: 2019/05/29 12:27:12 by dcelojev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = fillit
LIB_INC_DIR = libft

SRC = main.c			\
	  map_manager.c		\
	  parser.c			\
	  piece_manager.c	\
	  piece_manager2.c	\
	  solver.c			\

OBJ = main.o			\
	  map_manager.o		\
	  parser.o			\
	  piece_manager.o	\
	  piece_manager2.o	\
	  solver.o			\

all: $(NAME)

$(OBJ):
	gcc -I $(LIB_INC_DIR) -c $(SRC) -Wall -Werror -Wextra

$(NAME): LIB $(OBJ)
	gcc $(OBJ) libft/libft.a -o $(NAME)

LIB:
	$(MAKE) -C libft

clean:
	rm -f *.o
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all
