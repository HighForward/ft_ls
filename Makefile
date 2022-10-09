SRCS		=	./srcs/main.c \
				./srcs/format.c \
				./srcs/error.c \
				./srcs/parse_dir.c \
				./srcs/free.c \
				./srcs/output.c \
				./srcs/args.c \
				./srcs/utils.c

NAME		=	ft_ls

H           =   ./includes/ft_ls.h

OBJS_DIR	= ./objects/
OBJS		= ${SRCS:%.c=${OBJS_DIR}/%.o}

FLAGS		=	-Iincludes

CC			=	gcc

RM			=	rm -f

${OBJS_DIR}/%.o: %.c
				@mkdir -p ${@D}
				@${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

link:
				@$(MAKE) bonus -C ./libft/

${NAME}: ${OBJS} ${H} link
			    @$(CC) ${OBJS} -Wall -Wextra -Werror -L ./libft -lft -o ${NAME}
			    @echo "\033[1;32m > Building <\033[0m\033[1;36m ${NAME}\033[0m"

clean:
				@${RM} ${OBJS}
				@$(MAKE) clean -C ./libft/
				@echo "\033[1;31m > Deleting <\033[0m\033[1;35m .o files\033[0m"

fclean: clean
			    @${RM} $(NAME)
				@$(MAKE) fclean -C ./libft/
			    @echo "\033[1;31m > Deleting <\033[0m\033[1;35m ${NAME} \033[0m"

run: all
		./ft_ls

re:	fclean all

.PHONY: clean fclean re bonus run