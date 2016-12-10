NAME = fractol

SRC = fractol.c \
	  mandelbrot.c \
	  colors.c \
	  mouse.c

LIBFT = libft/libft.a

all : $(NAME)

$(NAME) :
	cd ./libft && make
	gcc -o fractol $(SRC) $(LIBFT) -L/usr/local/lib -I/usr/local/include \
-lmlx -framework OpenGL -framework appkit -Wall -Wextra -Werror

clean :
	cd ./libft && make clean

fclean : clean
	rm -rf fractol

re : fclean all

