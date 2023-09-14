# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 13:45:55 by sdeeyien          #+#    #+#              #
#    Updated: 2023/09/14 16:00:58 by sdeeyien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -fdiagnostics-color=always
#CFLAGS =
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	READLINEFLAGS = -L /usr/include/readline -l readline -l history
else
	READLINEFLAGS = -L /usr/opt/readline/lib -l readline
endif
LIBDIR = ./libft
LIBOBJ = libft.a
SRCDIR = ./src/
OBJDIR =
DEPS = minishell.h

SRC = minishell.c get_token.c cd.c utils.c
#SRC = get_token.c try_getpath.c
#SRC = read_line_with_history.c
BONUS =

OBJ := $(patsubst %.c, $(OBJDIR)%.o, $(SRC))
BONUS_OBJ := $(patsubst %.c, $(OBJDIR)%.o, $(BONUS))
SRC := $(addprefix $(SRCDIR), $(SRC))
BONUS := $(addprefix $(SRCDIR), $(BONUS))
DEPS := $(addprefix $(SRCDIR), $(DEPS))

NAME = minishell
BONUS_NAME =

all : $(NAME) $(BONUS_NAME)

$(NAME): $(OBJ)
	make -C $(LIBDIR) all
	$(CC) $(CFLAGS) $^ $(LIBDIR)/$(LIBOBJ) $(READLINEFLAGS) -o $@

bonus : $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	make -C $(LIBDIR) all
	$(CC) $(CFLAGS) $^ $(LIBDIR)/$(LIBOBJ) -o $@

%.o: $(SRCDIR)%.c $(DEPS)
	$(CC) -c $(CFLAGS) $(DEPS) $<


clean :
	rm -f *.o
	make -C $(LIBDIR) clean

fclean : clean
	rm -f $(NAME) $(BONUS_NAME)
	make -C $(LIBDIR) fclean

re : fclean all

.PHONY : all clean fclean re bonus
