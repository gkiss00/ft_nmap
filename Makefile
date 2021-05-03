SRCS				= 	main.c \
						srcs/node.c \
						srcs/error.c \
						srcs/parsing.c \
						srcs/init.c \
						srcs/utils.c \

OBJS				= ${SRCS:.c=.o}

NAME				= ft_nmap

FLAGS				= -Wall -Wextra -Werror

all :				${NAME}

${NAME} :			${OBJS}
					gcc -o ${NAME} ${FLAGS} ${SRCS}

clean :				
					rm -rf ${OBJS}

fclean : 			clean
					rm -rf ${NAME}

re :				fclean all

.PHONY:				all clean fclean re