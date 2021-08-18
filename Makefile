NAME=so_long
SRCS=srcs/*.c
OBJ=srcs/*.o
INC=/usr/include
MLX_FLAGS=-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
GCC=gcc -Wall -Wextra -fsanitize=address

all : ${NAME}

$(NAME):
	${GCC} libft/*.c ${SRCS} ${MLX_FLAGS} -I . -o $(NAME)

# %.o: %.c
# 	${GCC} -I /usr/include -Imlx_linux -O3 -c $< -o $@

clean : 
	rm -f *.o libft/*.o

fclean : 
	rm -f *.o libft/*.o ${NAME}

re : fclean all

.PHONY : clean re fclean all