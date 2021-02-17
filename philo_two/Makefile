NAME = philo_one
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCL = philo_one.h
SRCS = main.c \
	   create_philo.c \
	   utils.c

all : ${NAME}

${NAME} :
	${CC} ${CFLAGS} ${SRCS} -o ${NAME}

clean :
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

re : fclean all
