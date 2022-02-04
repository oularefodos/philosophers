# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: foulare <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/07 18:24:14 by foulare           #+#    #+#              #
#    Updated: 2022/02/04 03:04:51 by foulare          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME= philo

SRCS= philo.c utils.c ft_init.c ft_atoi.c
CFLAGS= -Wall -Wextra -Werror -g

OBJS :=$(SRCS:.c=.o)

OBJS_BNS :=$(SRCS_BNS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(CFLAGS) -lpthread $^ -o $@

%.o: %.c philo.h 
	gcc $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(OBJS_BNS)

fclean: clean
	rm -f $(NAME) bonus

re: fclean all
