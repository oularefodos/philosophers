# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: foulare <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/07 18:24:14 by foulare           #+#    #+#              #
#    Updated: 2022/02/04 03:04:56 by foulare          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME= philo_bonus
SRCS = philo_bns.c utils_bns.c ft_init_bns.c ft_strcmp_bns.c

OBJS :=$(SRCS:.c=.o)

OBJS_BNS :=$(SRCS_BNS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(CFLAGS) -lpthread $^ -o $@

%.o: %.c philo_bns.h 
	gcc $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(OBJS_BNS)

fclean: clean
	rm -f $(NAME)

re: fclean all
