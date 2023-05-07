NAME := cub3D
TEST := test3D
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
CC := cc -Wall -Wextra -Werror -O3 -g3
VALGRIND := valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -q
YEET := 1>/dev/null 2>/dev/null
MLX_REPO := git@github.com:42Paris/minilibx-linux.git
LIBRARIES := -L${PATH_LIBFT} -lft -L${PATH_MLX} -lmlx -lXext -lX11 -lm
GREEN := "\033[1;32m"
RESET := "\033[0;0m"
HEADERS := cub3d

vpath %.c ${PATH_SRCS}/mlx_tools
SRCS += handle_key_down init_minilibx

vpath %.c ${PATH_SRCS}/parsing
SRCS += parse_color parse_file parse_infos parse_map
SRCS += get_lines is_map_walled valid_characters

vpath %.c ${PATH_SRCS}/render_frame
SRCS += draw_column render_frame update_player

vpath %.c ${PATH_SRCS}/utils
SRCS += arrays clean complain init_data math vec2

ifeq (test, ${findstring test, ${MAKECMDGOALS}})
	HEADERS += test3d
	vpath %.c ${PATH_TESTS}
	SRCS += test3d test_parse_file
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
	@${VALGRIND} ./${TEST}

.PHONY: all clean fclean norm re test

.SILENT: norm test ${MLX} ${PATH_MLX}
