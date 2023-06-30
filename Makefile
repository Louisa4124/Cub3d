# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/12 20:46:19 by tlegrand          #+#    #+#              #
#    Updated: 2023/06/30 16:50:24 by tlegrand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



#	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	PROJECT VARIABLES	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	#

#	==============================	NAMES	==============================	#
NAME		=	cub3D


#	==============================	SOURCES	==============================	#
DIR_SRCS		=	srcs/

LST_SRCS		=	main.c clear.c debug.c \
					math.c utils.c fps.c
SRCS			=	${addprefix ${DIR_SRCS}, ${LST_SRCS}}

DIR_SRCS_PARSE	=	srcs/parsing/
LST_SRCS_PARSE	=	parser.c extract_texture.c extract_map.c parser_utils.c
SRCS_PARSE		=	${addprefix ${DIR_SRCS_PARSE}, ${LST_SRCS_PARSE}}

DIR_SRCS_ALGO	=	srcs/algo/
LST_SRCS_ALGO	=	algo_k_plan.c algo_switch_plan.c algo_utils.c 
SRCS_ALGO		=	${addprefix ${DIR_SRCS_ALGO}, ${LST_SRCS_ALGO}}

DIR_SRCS_DISP	=	srcs/display/
LST_SRCS_DISP	=	color.c display.c draw.c 
SRCS_DISP		=	${addprefix ${DIR_SRCS_DISP}, ${LST_SRCS_DISP}}

DIR_SRCS_INIT	=	srcs/init/
LST_SRCS_INIT	=	init_game.c init_mlx.c init_struct.c
SRCS_INIT		=	${addprefix ${DIR_SRCS_INIT}, ${LST_SRCS_INIT}}

DIR_SRCS_EVENT	=	srcs/event_mlx/
LST_SRCS_EVENT	=	event.c move.c
SRCS_EVENT		=	${addprefix ${DIR_SRCS_EVENT}, ${LST_SRCS_EVENT}}


#	==============================	OBJECTS	==============================	#
DIR_OBJS	=	.objs/
OBJS		=	${patsubst ${DIR_SRCS}%.c, ${DIR_OBJS}%.o, ${SRCS}} \
				${patsubst ${DIR_SRCS_PARSE}%.c, ${DIR_OBJS}%.o, ${SRCS_PARSE}} \
				${patsubst ${DIR_SRCS_ALGO}%.c, ${DIR_OBJS}%.o, ${SRCS_ALGO}} \
				${patsubst ${DIR_SRCS_DISP}%.c, ${DIR_OBJS}%.o, ${SRCS_DISP}} \
				${patsubst ${DIR_SRCS_INIT}%.c, ${DIR_OBJS}%.o, ${SRCS_INIT}} \
				${patsubst ${DIR_SRCS_EVENT}%.c, ${DIR_OBJS}%.o, ${SRCS_EVENT}}

#	==============================	HEADERS	==============================	#
DIR_HEADER	=	include/
LST_HDR		=	${NAME}.h math.h struct.h
HEADER		=	${addprefix ${DIR_HEADER}, ${LST_HDR}}


#	==============================	LIBRARY	==============================	#
DIR_LIBFT	=	libft/
LIBFT		=	$(addprefix $(DIR_LIBFT), libft.a)
DIR_LIBMLX	=	mlx-linux/
LIBMLX		=	$(addprefix $(DIR_LIBMLX), libmlx.a)


#	==============================	COMMANDS	==============================	#
CC 			=	cc
MKDIR 		=	mkdir -p
RM			=	rm -rf
MAKE		=	make -s


#	==============================	FLAGS	==============================	#
CFLAGS		=	-O3 -Wall -Wextra #-fsanitize=address -fsanitize=leak -fsanitize=pointer-subtract -fsanitize=pointer-compare -fsanitize=undefined -g3
FTFLAGS		=	-L${DIR_LIBFT} -lft
MLXFLAGS	=	-L${DIR_LIBMLX} -lmlx -lXext -lX11


#	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	RULES	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	#
.PHONY : all clean fclean re bonus FORCE nn

#	==============================	BASIC	==============================	#
all		:	${NAME}

clean	:
		@${RM} ${DIR_OBJS}
		@$(MAKE) -C ${DIR_LIBFT} clean

fclean	:	clean
		@${RM} ${NAME} ${NAME_B}
		@$(MAKE) -C ${DIR_LIBFT} fclean
		@${MAKE} -C ${DIR_LIBMLX} clean
		@printf "$(GREEN)All clean !\n$(END)"

re		:	fclean
		@${MAKE} all


#	==============================	COMPILATION	==============================	#
${NAME}			:	${LIBFT} ${LIBMLX} ${DIR_OBJS} ${OBJS}
				@${CC} -I${DIR_HEADER} ${CFLAGS} ${OBJS} ${FTFLAGS} ${MLXFLAGS} -o ${NAME} -lm
				@printf "$(GREEN_LIGHT)${NAME} created !\n$(END)"

${DIR_OBJS}%.o	:	${DIR_SRCS}%.c ${HEADER}
				@printf "$(YELLOW)Making $@...\n$(END)"
				@${CC} ${CFLAGS} -c $< -o $@

${DIR_OBJS}%.o	:	${DIR_SRCS_PARSE}%.c ${HEADER}
				@printf "$(YELLOW)Making $@...\n$(END)"
				@${CC} ${CFLAGS} -c $< -o $@

${DIR_OBJS}%.o	:	${DIR_SRCS_ALGO}%.c ${HEADER}
				@printf "$(YELLOW)Making $@...\n$(END)"
				@${CC} ${CFLAGS} -c $< -o $@

${DIR_OBJS}%.o	:	${DIR_SRCS_DISP}%.c ${HEADER}
				@printf "$(YELLOW)Making $@...\n$(END)"
				@${CC} ${CFLAGS} -c $< -o $@

${DIR_OBJS}%.o	:	${DIR_SRCS_INIT}%.c ${HEADER}
				@printf "$(YELLOW)Making $@...\n$(END)"
				@${CC} ${CFLAGS} -c $< -o $@

${DIR_OBJS}%.o	:	${DIR_SRCS_EVENT}%.c ${HEADER}
				@printf "$(YELLOW)Making $@...\n$(END)"
				@${CC} ${CFLAGS} -c $< -o $@


#	==============================	UTILS/LIB	==============================	#
${DIR_OBJS}	:
			@${MKDIR} ${DIR_OBJS}
			
nn			:
			@norminette $(sort ${DIR_SRCS} ${HEADER} )

$(LIBFT)	:	FORCE
			@$(MAKE) -C ${DIR_LIBFT}

${LIBMLX}	:	FORCE
			@$(MAKE) -C ${DIR_LIBMLX}

FORCE		:



#	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	OPERATING VARIABLES	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	#

#	==============================	COLORS	==============================	#
BLACK		=	\033[0;30m
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
BLUE		=	\033[0;34m
PURPLE		=	\033[0;35m
CYAN		=	\033[0;36m
GRAY_LIGHT	=	\033[0;37m
GRAY_DARK	=	\033[1;30m
RED_LIGHT	=	\033[1;31m
GREEN_LIGHT	=	\033[1;32m
YELLOW 		=	\033[1;33m
BLUE_LIGHT	=	\033[1;34m
VIOLET		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m
END			=	\033[0m
BOLD		=	\033[1m
FAINT		=	\033[2m
ITALIC		=	\033[3m
UNDERLINE	=	\033[4m
BLINK_SLOW	=	\033[5m
BLINK_FAST	=	\033[6m
BLINK_OFF	=	\033[25m
REV_V		=	\033[7m
CONCEAL		=	\033[8m
CONCEAL_OFF	=	\033[28m
CROSS_OUT	=	\033[9m
CROSS_OUT_O	=	\033[29m
ERASE		=	\033[2K
RERASE		=	\r\033[2K