
SRC_NAME = fractol.c \
	  mandelbrot.c \
	  colors.c \
	  mouse.c \
	  hooks.c \
	  make_new_lines.c \
	  julia.c \
	  buddhabrot.c \
	  mandel_julia_power.c

NAME = fractol

CC = clang

CFLAGS = -I./include -I./libft/include -I./minilibx-linux -Wall -Wextra -O3

SRCF = ./srcs/

OBJF = ./obj/

OBJS = $(addprefix $(OBJF), $(SRC_NAME:.c=.o))

LFT = libft/libft.a

all : $(NAME)

$(NAME) : $(LFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -L./libft -lft -lXext -lX11 -lbsd -L./minilibx-linux -lmlx -lpthread -lm -O3

$(LFT):
	make -C ./libft

$(OBJF)%.o: $(SRCF)%.c
	@mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $(addprefix $(SRCF), $*.c)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

