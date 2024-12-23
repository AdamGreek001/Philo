# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/23 22:47:53 by eel-alao          #+#    #+#              #
#    Updated: 2024/12/23 22:47:54 by eel-alao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

NAME = philo
INCLUDES = philo.h
SRC = main.c parse_input.c philo_actions.c simulatioin_innit.c supervisor.c time_utils.c
OBJ = $(SRC:.c=.o)
 
all : $(NAME)

$(NAME) : $(OBJ) $(INCLUDES)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all