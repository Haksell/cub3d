NAME := minirt
TEST := minitest
PATH_INCLUDES := includes
PATH_SRCS := srcs
PATH_OBJS := objs
PATH_LIBFT := libft
PATH_MLX := mlx
PATH_TESTS := tests
LIBFT := ${PATH_LIBFT}/libft.a
MLX := ${PATH_MLX}/libmlx.a
GARBAGE := .vscode
INCLUDES := -I./${PATH_INCLUDES} -I./${PATH_LIBFT}/includes -I./${PATH_MLX}
HEADERS := error minirt struct
CC := cc -Wall -Wextra -Werror -O3 -g3 # TODO remove -g3
YEET1 := 1>/dev/null
YEET2 := 2>/dev/null
YEET := ${YEET1} ${YEET2}
MLX_REPO := git@github.com:42Paris/minilibx-linux.git
LIBRARIES := -L${PATH_LIBFT} -lft -lX11 -lXext -L${PATH_MLX} -lmlx -lm
GREEN := "\033[1;32m"
RESET := "\033[0;0m"

vpath %.c ${PATH_SRCS}/display
SRCS += light ray render_frame scatter

vpath %.c ${PATH_SRCS}/hit
SRCS += hit_disk hit_plane hit_sphere hit_tube hit_world

vpath %.c ${PATH_SRCS}/mlx_tools
SRCS += handle_key_down init_minilibx

vpath %.c ${PATH_SRCS}/parsing
SRCS += ft_atod get_words parse_elements
SRCS += parse_objects parse_scene parse_vectors

vpath %.c ${PATH_SRCS}/utils
SRCS += arrays clean complain init_pixels math random_double random_vector
SRCS += print # TODO remove

vpath %.c ${PATH_SRCS}/vec3
SRCS += vec3a vec3b vec3c

ifeq (test, ${findstring test, ${MAKECMDGOALS}})
	HEADERS += minitest
	vpath %.c ${PATH_TESTS}
	SRCS += minitest test_atod_range test_parse_color
	SRCS += test_parse_coord test_parse_scene
else
	vpath %.c ${PATH_SRCS}
	SRCS += main
endif

SRCS := ${addsuffix .c, ${SRCS}}
OBJS := ${patsubst %.c, ${PATH_OBJS}/%.o, ${SRCS}}
HEADERS := ${addprefix ${PATH_INCLUDES}/, ${addsuffix .h, ${HEADERS}}}

all: ${NAME}

${OBJS}: ${PATH_OBJS}/%.o: %.c ${HEADERS}
	@mkdir -p ${PATH_OBJS}
	${CC} -c $< -o $@ ${INCLUDES}

${NAME} ${TEST}: ${LIBFT} ${MLX} ${OBJS}
	${CC} ${OBJS} ${LIBRARIES} -o $@

${LIBFT}:
	${MAKE} -s -C ${PATH_LIBFT}

${PATH_MLX}:
	echo ${GREEN} "==> Cloning mlx" ${RESET}
	git clone ${MLX_REPO} $@ ${YEET}
	rm -rf ${PATH_MLX}/.git*

${MLX}: | ${PATH_MLX}
	echo ${GREEN} "==> Compiling mlx" ${RESET}
	${MAKE} -s -C ${PATH_MLX} ${YEET}

clean:
	${MAKE} -s -C ${PATH_LIBFT} fclean
	rm -rf ${PATH_OBJS} ${PATH_MLX} ${GARBAGE}

fclean: clean
	rm -f ${NAME} ${TEST}

re: fclean ${NAME}

norm:
	./scripts/niih ${PATH_LIBFT} ${PATH_INCLUDES} ${PATH_SRCS} ${PATH_TESTS}

test: ${TEST}
	@./${TEST} ${YEET2}

norm_test: norm test

.PHONY: all clean fclean norm norm_test re test

.SILENT: norm ${MLX} ${PATH_MLX}
