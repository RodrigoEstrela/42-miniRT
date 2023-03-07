SRCS		=	main/main.c main/initializers.c main/free.c \
				utils/put_pxl.c utils/vector.c utils/ft_split.c utils/ft_atoi.c utils/ft_itoa.c\
				utils/fps.c utils/ft_atof.c utils/render_progress_bar.c utils/tab_space_split.c \
				utils/ft_strncmp.c utils/vector2.c utils/vector3.c \
				controls/controls.c controls/controls_utils.c controls/editor_mode_utils.c \
                controls/transform_utils1.c controls/transform_utils2.c \
                controls/key_utils1.c controls/key_utils2.c \
				parsing/parsing.c parsing/obj_counters1.c parsing/obj_counters2.c \
            parsing/parser_utils1.c parsing/sphere_parser.c parsing/plane_parser.c \
            parsing/cylinder_parser.c parsing/triangle_parser.c parsing/camera_parser.c parsing/light_parser.c \
				gnl/get_next_line.c gnl/get_next_line_utils.c \
				raytracer/ray_tracer.c raytracer/shading.c raytracer/background.c \
				raytracer/intersections.c raytracer/no_intersection.c raytracer/cylinder.c raytracer/cylinder2.c \
				raytracer/reflection_refraction.c raytracer/fresnel.c \
				raytracer/sphere.c raytracer/plane.c raytracer/triangle.c raytracer/multi_threading.c \
				raytracer/color.c raytracer/shadows.c \
				textures/plane_checkerboard.c textures/sphere_checkerboard.c \

OBJS		=	$(addprefix objs/,$(SRCS:.c=.o))

MLX			=	mlx_linux/libmlx_Linux.a

THREADS = $(shell nproc --all)

CFLAGS		= 	-g -Wall -Wextra -Werror -D THREADS=$(THREADS)

RM		=	rm -f

NAME		=	miniRT

all:		$(NAME)

objs/%.o: srcs/%.c
			@mkdir -p objs
			@mkdir -p objs/main
			@mkdir -p objs/utils
			@mkdir -p objs/controls
			@mkdir -p objs/parsing
			@mkdir -p objs/gnl
			@mkdir -p objs/raytracer
			@mkdir -p objs/textures
			$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(MLX):
			@make -C mlx_linux

$(NAME): 	$(OBJS) $(MLX)
			$(CC) $(CFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -lpthread -o $(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:		fclean all
