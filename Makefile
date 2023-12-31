# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/17 13:45:55 by sdeeyien          #+#    #+#              #
#    Updated: 2023/10/17 16:48:57 by sdeeyien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
#CFLAGS =
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	READLINEFLAGS = -L /usr/include/readline -l readline -l history
	READLINEINCLUDE =
else
	READLINEFLAGS = -L /usr/local/opt/readline/include/readline -l readline -l history
	READLINEINCLUDE = -I/usr/local/opt/readline/include
endif
LIBDIR = ./libft
LIBOBJ = libft.a
SRCDIR = ./src/
OBJDIR =
DEPS = minishell.h

SRC = minishell.c get_token.c cd.c utils.c utils2.c export.c unset.c  \
		parsing_util.c parsing_util2.c parsing_util4.c \
		parsing_util3_1.c parsing_1.c parsing_util5.c parsing_util6.c \
		pwd.c echo.c env.c exec_single_builtin.c parsing_util5a.c \
		utils3.c
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
	$(CC) -c $(CFLAGS) $(DEPS) $< $(READLINEINCLUDE)

clean :
	rm -f *.o
	make -C $(LIBDIR) clean

fclean : clean
	rm -f $(NAME) $(BONUS_NAME)
	make -C $(LIBDIR) fclean

re : fclean all

.PHONY : all clean fclean re bonus
