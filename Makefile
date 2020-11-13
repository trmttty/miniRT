CC			= gcc
FLAGS		= -Wall -Wextra -Werror
NAME 		= miniRT
DIR_LIB		= libft
LIBFT		= $(DIR_LIB)/libft.a
SRC_RT_DIR 	= ./src/
OBJ_DIR 	= ./obj/

SRC_RT = main.c \
			get_next_line.c \
			parse.c \
			parse_resolution.c \
			parse_ambient.c \
			parse_camera.c \
			parse_light.c \
			parse_sphere.c \
			parse_plane.c \
			parse_square.c \
			parse_cylinder.c \
			parse_triangle.c \
			parse_utils.c \
			create_img.c \
			raytrace_setting.c \
			raytrace_1.c \
			raytrace_2.c \
			vector_1.c \
			vector_2.c \
			color_utils.c \
			bmp.c \
			error.c \
			find_cylinder.c \
			find_intersection.c \
			find_plane.c \
			find_sphere.c \
			find_square.c \
			find_triangle.c \
			utils.c

OBJ_RT = $(addprefix $(OBJ_DIR),$(SRC_RT:%.c=%.o))
OBJ = $(OBJ_RT)
HEADERS = includes

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ_RT)
	$(CC) -I $(HEADERS) -L minilibx -lmlx -framework OpenGL -framework AppKit -lz -L libft -lft $(OBJ) libmlx.dylib -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_RT_DIR)%.c
	$(CC) -I $(HEADERS) -o $@ -c $<

$(LIBFT):
	make bonus -C $(DIR_LIB)

clean :
	make clean -C $(DIR_LIB)
	rm -rf $(OBJ_DIR)

fclean : clean
	make fclean -C $(DIR_LIB)
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re run
