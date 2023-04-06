NAME := cub3d
NAME_BONUS := cub3d_bonus
TEST := test3d
PATH_INCLUDES := includes
PATH_INCLUDES_BONUS := includes_bonus
PATH_SRCS := srcs
PATH_SRCS_BONUS := srcs_bonus/
PATH_OBJS := objs
PATH_OBJS_BONUS := objs_bonus
PATH_LIBFT := libft
PATH_MLX := mlx
PATH_TESTS := tests
LIBFT := ${PATH_LIBFT}/libft.a
MLX := ${PATH_MLX}/libmlx.a
GARBAGE := .vscode
INCLUDES := -I./${PATH_INCLUDES} -I./${PATH_LIBFT}/includes -I./${PATH_MLX}
INCLUDES_BONUS := -I./${PATH_INCLUDES_BONUS} -I./${PATH_LIBFT}/includes -I./${PATH_MLX}
CC := cc -Wall -Wextra -Werror -O3 -g3
VALGRIND := valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -q
YEET := 1>/dev/null 2>/dev/null
MLX_REPO := git@github.com:42Paris/minilibx-linux.git
LIBRARIES := -L${PATH_LIBFT} -lft -L${PATH_MLX} -lmlx -lXext -lX11 -lm
GREEN := "\033[1;32m"
RESET := "\033[0;0m"

# vpath %.c ${PATH_SRCS}
# SRCS += debug # TODO remove

# vpath %.c ${PATH_SRCS}/display
# SRCS += draw_column render_frame

# vpath %.c ${PATH_SRCS}/mlx_tools
# SRCS += handle_key_down init_minilibx

# vpath %.c ${PATH_SRCS}/parsing
# SRCS += parse_color parse_file parse_infos parse_map
# SRCS += get_lines is_map_walled valid_characters

# vpath %.c ${PATH_SRCS}/utils
# SRCS += arrays clean complain init_data math

# vpath %.c ${PATH_SRCS}/vec2
# SRCS += vec2a vec2b vec2c

vpath %.c ${PATH_SRCS_BONUS}
SRCS_BONUS += debug # TODO remove

vpath %.c ${PATH_SRCS_BONUS}/display
SRCS_BONUS += draw_column render_frame

vpath %.c ${PATH_SRCS_BONUS}/mlx_tools
SRCS_BONUS += handle_key_down init_minilibx

vpath %.c ${PATH_SRCS_BONUS}/parsing
SRCS_BONUS += parse_color parse_file parse_infos parse_map
SRCS_BONUS += get_lines is_map_walled valid_characters

vpath %.c ${PATH_SRCS_BONUS}/utils
SRCS_BONUS += arrays clean complain init_data math

vpath %.c ${PATH_SRCS_BONUS}/vec2
SRCS_BONUS += vec2a vec2b vec2c

ifeq (bonus, $(findstring bonus, $(MAKECMDGOALS)))
	HEADERS_BONUS := cub3d
	SRCS_BONUS += main
	SRCS = 0
	SRCS = SRCS_BONUS
else
	HEADERS := cub3d
	SRCS += main
endif

# ifeq (test, ${findstring test, ${MAKECMDGOALS}})
# 	HEADERS := test3d
# 	vpath %.c ${PATH_TESTS}
# 	SRCS += test3d test_parse_file
# else
# 	HEADERS := cub3d
	# SRCS += main
# endif

SRCS_BONUS := ${addsuffix .c, ${SRCS_BONUS}}
SRCS := ${addsuffix .c, ${SRCS}}
OBJS_BONUS := ${patsubst %.c, ${PATH_OBJS_BONUS}/%.o, ${SRCS_BONUS}}
OBJS := ${patsubst %.c, ${PATH_OBJS}/%.o, ${SRCS}}
HEADERS := ${addprefix ${PATH_INCLUDES}/, ${addsuffix .h, ${HEADERS}}}
HEADERS_BONUS := ${addprefix ${PATH_INCLUDES_BONUS}/, ${addsuffix .h, ${HEADERS_BONUS}}}

bonus: ${NAME_BONUS}

all: ${NAME}

${OBJS}: ${PATH_OBJS}/%.o: %.c ${HEADERS}
	@mkdir -p ${PATH_OBJS}
	${CC} -c $< -o $@ ${INCLUDES}

${OBJS_BONUS}: ${PATH_OBJS_BONUS}/%.o: %.c ${HEADERS_BONUS}
	@mkdir -p ${PATH_OBJS_BONUS}
	${CC} -c $< -o $@ ${INCLUDES_BONUS}

${NAME} ${TEST}: ${LIBFT} ${MLX} ${OBJS}
	${CC} ${OBJS} ${LIBRARIES} -o $@

${NAME_BONUS}: ${LIBFT} ${MLX} ${OBJS_BONUS}
	${CC} ${OBJS_BONUS} ${LIBRARIES} -o $@

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
	rm -rf ${PATH_OBJS} ${PATH_OBJS_BONUS} ${PATH_MLX} ${GARBAGE}

fclean: clean
	rm -f ${NAME} ${TEST} ${NAME_BONUS}

re: fclean ${NAME}

norm:
	./scripts/niih ${PATH_LIBFT} ${PATH_INCLUDES} ${PATH_SRCS} ${PATH_TESTS}

test: ${TEST}
	@${VALGRIND} ./${TEST}

.PHONY: all clean fclean norm re test

.SILENT: norm test ${MLX} ${PATH_MLX}
