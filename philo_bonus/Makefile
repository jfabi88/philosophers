# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfabi <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 11:23:36 by jfabi             #+#    #+#              #
#    Updated: 2021/09/20 11:23:38 by jfabi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus

SRCS	=	\
			action.c \
			cheack.c \
			error.c \
			init.c \
			main.c \
			utils.c \
			utils2.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

%.o	:	%.c
		gcc -c -g $< -o $@

$(NAME):	$(OBJS)
			gcc $(CFLAGS) -pthread $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
