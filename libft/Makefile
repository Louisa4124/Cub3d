# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 14:39:06 by tlegrand          #+#    #+#              #
#    Updated: 2023/05/06 22:18:25 by tlegrand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	PROJECT VARIABLES	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	#

#	==============================	NAMES	==============================	#
NAME		=	libft.a


#	==============================	SOURCES	==============================	#
DIR_SRCS	=	srcs/
LST_SRCS	= 	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isprint.c ft_isascii.c \
				ft_toupper.c ft_tolower.c ft_atoi.c \
				ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_strlen.c \
				ft_strdup.c ft_calloc.c ft_strlcpy.c ft_strlcat.c \
				ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
				ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strappend.c \
				ft_strmapi.c ft_striteri.c \
				ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c \
				ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
				ft_printf.c ft_printf_buffer.c ft_printf_extract_number.c ft_printf_get_flags.c ft_printf_get_value.c \
				ft_printf_padding.c ft_printf_utils.c \
				get_next_line.c get_next_line_utils.c \
				ft_free.c ft_close.c ft_print_tab.c \
				 math_utils.c
SRCS		=	${addprefix ${DIR_SRCS}, ${LST_SRCS}}


#	==============================	OBJECTS	==============================	#
DIR_OBJS	=	.objs/
OBJS	=	${patsubst ${DIR_SRCS}%.c, ${DIR_OBJS}%.o, ${SRCS}}


#	==============================	HEADERS	==============================	#
HEADER 		=	libft.h


#	==============================	COMMANDS	==============================	#
CC 			=	cc
MKDIR 		=	mkdir -p
RM			=	rm -rf


#	==============================	FLAGS	==============================	#
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g3
ARFLAGS		=	rcs



#	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	RULES	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	#
.PHONY : all clean fclean re


#	==============================	BASIC	==============================	#
all		:	${NAME}

clean	:
		@${RM} ${DIR_OBJS}

fclean	:	clean
		@${RM} ${NAME}
		@printf "$(GREEN)All clean !\n$(END)"

re		:	fclean
		@${MAKE} all


#	==============================	COMPILATION	==============================	#
${NAME}			:	${DIR_OBJS} ${OBJS} 
				@${AR} ${ARFLAGS} $@ ${OBJS}
				@printf "\n$(GREEN_LIGHT)${NAME} created !\n$(END)"

${DIR_OBJS}%.o	:	${DIR_SRCS}%.c ${HEADER}
				@printf "$(RERASE)$(ORANGE)Making ${NAME}...$(END)"
				@${CC} ${CFLAGS} -c $< -o $@

${DIR_OBJS}		:
				@${MKDIR} $@



#	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	OPERATING VARIABLES	/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\/*\	#

#	==============================	COLORS	==============================	#
BLACK		=	\033[0;30m
RED			=	\033[0;31m
GREEN		=	\033[0;32m
ORANGE		=	\033[0;33m
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
ERASE		=	\033[2K
RERASE		=	\r\033[2K
