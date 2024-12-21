SRC		=	simulation_init.c time_utils.c philosopher_actions.c \
			supervisor.c input_validation.c main.c

NAME	=	philo

CC		=	cc

HEADER	=	philosopher.h

CFLAGS	=	-Wall -Wextra -Werror

OBJS	=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean