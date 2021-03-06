NAME=so_long
SRCS=srcs/*.c
INC=/usr/include
MLX_FLAGS=-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
GCC=gcc -Wall -Wextra -Werror

all : ${NAME}

$(NAME):
	cd mlx_linux && ./configure
	${GCC} libft/*.c ${SRCS} ${MLX_FLAGS} -I . -o $(NAME)

# %.o: %.c
# 	${GCC} -I /usr/include -Imlx_linux -O3 -c $< -o $@

clean : 
	rm -f *.o libft/*.o
	make -C libft clean

fclean : 
	rm -f *.o libft/*.o ${NAME}
	make -C libft fclean

re : fclean all

.PHONY : clean re fclean all