# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkang <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/17 22:22:40 by junkang           #+#    #+#              #
#    Updated: 2021/02/17 22:22:43 by junkang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCL = philo_three.h
SRCS = main.c \
	   create_philo.c \
	   process_create.c \
	   utils.c

all : ${NAME}

${NAME} :
	${CC} ${CFLAGS} ${SRCS} -o ${NAME}

clean :
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

re : fclean all
