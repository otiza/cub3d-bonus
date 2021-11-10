NAME = cub3D

CFLAGS = -O3 

MLX = ./minilibx_opengl

LXFLAGS =  -Imlx_linux

HEADER = cub3d.h \
	get_next_line.h

CC = gcc

SRCS =	get_next_line.c \
	get_next_line_utils.c \
	check.c	cub3d.c	ft_bmp.c \
	ft_sprites.c \
	ft_sprites2.c \
	ft_tools.c \
	game.c \
	parse.c	parse_2.c \
	parse_3.c \
	raycast.c \
	render.c

FIL = $(addprefix ./srcs/, $(SRCS))

OBJ = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(FIL)
	$(CC) $(CFLAGS)  -L $(MLX) $(LXFLAGS) $(FIL) -o $(NAME)

run:
	./$(NAME) map.cub

save:
	./$(NAME) map.cub --save

clean:
	@rm -rf $(OBJ)
	@rm -f bitmap.bmp

fclean: clean
	rm -f $(NAME)

re: fclean all

me:
	@echo $(NAME)
	@echo "#    #  ####   ####  #####   #    #  ####   ####  #####  "
	@echo "##   # #    # #    # #    #  ##   # #    # #    # #    # "
	@echo "# #  # #    # #    # #####   # #  # #    # #    # #####  "
	@echo "#  # # #    # #    # #    #  #  # # #    # #    # #    # "
	@echo "#   ## #    # #    # #    #  #   ## #    # #    # #    # "
	@echo "#    #  ####   ####  #####   #    #  ####   ####  #####  "

norm:
	norminette $(FIL) $(addprefix ./inc/, $(HEADER))

leaks:
	leaks $(NAME) > leak