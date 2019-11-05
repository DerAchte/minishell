# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 15:14:58 by thdervil          #+#    #+#              #
#    Updated: 2019/11/03 14:29:55 by thdervil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRC		= main.c \
		  builtins.c \
		  deletes.c \
		  expansions.c \
		  strings_ops.c \
		  checks.c \
		  env_ops.c \
		  init.c \
		  valid_prog.c \
		  commands_ops.c \
		  execs.c \
		  vars_ops.c \
		  cd_opts.c

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -ggdb

FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft

SRCDIR	= ./srcs/
INCDIR	= ./incs/
OBJDIR	= ./obj/

all: $(NAME)

$(OBJDIR)%.o:$(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $< 

$(NAME): $(OBJ) 
	make -C $(FT) 
	$(CC) $(OBJ) $(FT_LNK) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all

.PHONY: all obj fclean clean re
