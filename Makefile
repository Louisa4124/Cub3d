# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/12 20:46:19 by tlegrand          #+#    #+#              #
#    Updated: 2023/08/06 00:21:35 by tlegrand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



#	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	PROJECT VARIABLES	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	#

#	==============================	NAMES	==============================	#
NAME		=	cub3D
NAME_B		=	cub3D_bonus

#	==============================	SOURCES	==============================	#
DIR_SRCS_M		=	srcs_m/
LST_SRCS		=	algo.c clear.c color.c display.c event.c math.c main.c \
					parser.c extract_texture.c extract_map.c parser_utils.c \
					init_game.c init_mlx.c init_struct.c view_update.c utils.c
SRCS_M			=	${addprefix ${DIR_SRCS_M}, ${LST_SRCS}}

DIR_SRCS_PARSE	=	parsing/
LST_SRCS_PARSE	=	parser_bonus.c extract_texture_bonus.c extract_map_bonus.c parser_utils_bonus.c
SRCS_PARSE		=	${addprefix ${DIR_SRCS_PARSE}, ${LST_SRCS_PARSE}}

DIR_SRCS_ALGO	=	algo/
LST_SRCS_ALGO	=	algo_switch_plan_bonus.c algo_utils_bonus.c thread_bonus.c job_bonus.c 
SRCS_ALGO		=	${addprefix ${DIR_SRCS_ALGO}, ${LST_SRCS_ALGO}}

DIR_SRCS_DISP	=	display/
LST_SRCS_DISP	=	color_bonus.c display_bonus.c draw_bonus.c blur_bonus.c image2_bonus.c \
					animation_bonus.c
SRCS_DISP		=	${addprefix ${DIR_SRCS_DISP}, ${LST_SRCS_DISP}}

DIR_SRCS_INIT	=	init/
LST_SRCS_INIT	=	init_game_bonus.c init_mlx_bonus.c init_struct_bonus.c load_bonus.c init_img_bonus.c
SRCS_INIT		=	${addprefix ${DIR_SRCS_INIT}, ${LST_SRCS_INIT}}

DIR_SRCS_EVENT	=	move/
LST_SRCS_EVENT	=	event_bonus.c view_update_pos_bonus.c view_update_dir_bonus.c
SRCS_EVENT		=	${addprefix ${DIR_SRCS_EVENT}, ${LST_SRCS_EVENT}}

DIR_SRCS_B		=	srcs_bonus/
LST_SRCS_B		=	main_bonus.c clear_bonus.c debug_bonus.c math_bonus.c utils_bonus.c fps_bonus.c \
					${SRCS_PARSE} ${SRCS_ALGO} ${SRCS_DISP} ${SRCS_INIT} ${SRCS_EVENT}
SRCS_B			=	${addprefix ${DIR_SRCS_B}, ${LST_SRCS_B}}


#	==============================	OBJECTS	==============================	#
DIR_OBJS	=	.objs/
LST_OBJS	=	${LST_SRCS:.c=.o}
OBJS		=	${addprefix ${DIR_OBJS}, ${LST_OBJS}} 
LST_OBJS_B	=	${LST_SRCS_B:.c=.o}
OBJS_B		=	${addprefix ${DIR_OBJS}, ${LST_OBJS_B}}

DIR			=	${DIR_SRCS_PARSE} ${DIR_SRCS_ALGO} ${DIR_SRCS_DISP} ${DIR_SRCS_INIT} ${DIR_SRCS_EVENT}


#	==============================	HEADERS	==============================	#
DIR_HEADER	=	include/
LST_HDR		=	${NAME}.h
HEADER		=	${addprefix ${DIR_HEADER}, ${LST_HDR}}
LST_HDR_B	=	${NAME_B}.h struct.h
HEADER_B	=	${addprefix ${DIR_HEADER}, ${LST_HDR_B}}


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
DEBUG		=	no

#	==============================	FLAGS	==============================	#
CFLAGS		=	-O3 -Wall -Wextra -pthread 
FTFLAGS		=	-L${DIR_LIBFT} -lft
MLXFLAGS	=	-L${DIR_LIBMLX} -lmlx -lXext -lX11
DFLAGS		=	-g3 -fsanitize=address -fsanitize=leak -fsanitize=pointer-subtract -fsanitize=pointer-compare -fsanitize=undefined 
DFLAGS_TH	=	-g3 -fsanitize=thread

ifeq ($(DEBUG), base)
CFLAGS += $(DFLAGS)
endif

ifeq ($(DEBUG), thread)
CFLAGS += $(DFLAGS)
endif


#	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	RULES	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	#
.PHONY : all clean fclean re bonus FORCE nn

#	==============================	BASIC	==============================	#
all		:	${NAME}

bonus	:	${NAME_B}

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
				@printf "$(GREEN_LIGHT)$@ created !\n$(END)"

${NAME_B}		:	${LIBFT} ${LIBMLX} ${DIR_OBJS} ${OBJS_B}
				@${CC} -I${DIR_HEADER} ${CFLAGS} ${OBJS_B} ${FTFLAGS} ${MLXFLAGS} -o ${NAME_B} -lm
				@printf "$(GREEN_LIGHT)$@ created !\n$(END)"

${DIR_OBJS}%.o	:	${DIR_SRCS_M}%.c ${HEADER}
				@printf "$(YELLOW)Making $@...\n$(END)"
				@${CC} ${CFLAGS} -c $< -o $@

${DIR_OBJS}%.o	:	${DIR_SRCS_B}%.c ${HEADER_B}
				@printf "$(YELLOW)Making $@...\n$(END)"
				@${CC} ${CFLAGS} -c $< -o $@


#	==============================	UTILS/LIB	==============================	#
reb			:	clean_p
			@${MAKE} bonus

mdebug		:	clean_p
			@${MAKE} DEBUG=base ${NAME}

bdebug		:	clean_p
			@${MAKE} DEBUG=base ${NAME_B}		

tdebug		:	clean_p
			@${MAKE} DEBUG=thread ${NAME_B}

nn			:
			@norminette $(sort  ${HEADER} ${DIR_SRCS_M} ${HEADER_B} ${DIR_SRCS_B})
		
${DIR_OBJS}	:
			@${MKDIR} ${DIR_OBJS} ${addprefix ${DIR_OBJS}, ${DIR}}

$(LIBFT)	:	FORCE
			@$(MAKE) -C ${DIR_LIBFT}

${LIBMLX}	:	FORCE
			@$(MAKE) -C ${DIR_LIBMLX}

clean_p		:
			@${RM} ${DIR_OBJS}
			@${RM} ${NAME}
			@${RM} ${NAME_B}
			
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
