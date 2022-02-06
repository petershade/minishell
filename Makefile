NAME = minishell

NAME_B = minishell_bonus

MAC =

MAC_B =

LIBFT = srcs/my_libft

FLAGS 	= -g -Wall -Wextra

LIB =  -L/usr/include -lreadline

SRCS =  	srcs/minishell.c

SRCS_BONUS =
CC 		= gcc
OBJ 	= ${SRCS:.c=.o}
OBJS 	= *.o
OBJ_B = ${SRCS_BONUS:.c=.o}
OBJS_B = *.o

all :
	@make -C $(LIBFT)
	@make $(NAME)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I include/

get_src:
	@find built_in -type f -name "*.c" | tr "\n" "|" | sed -r 's/["|"]+/\\ \n/g'


$(NAME)	: $(OBJ)
	$(CC) $(FLAGS) -I srcs/libft/includes/ -I include/. $(OBJ) srcs/libft/libft.a -o $(NAME) $(LIB)

$(NAME_B) : $(OBJ_B)
	$(CC) $(FLAGS) -I srcs/libft/includes/ -I include/. $(OBJ_B) srcs/libft/libft.a -o $(NAME_B)

clean :
		@make clean -C $(LIBFT)
		@rm -rf $(OBJ)
		@rm -rf $(OBJ_B)

fclean : clean
		@rm -rf libft.a
		@make fclean -C $(LIBFT)
		@rm -rf $(OBJS)
		@rm -rf $(OBJS_B)
		@rm -rf $(NAME)
		@rm -rf $(NAME_B)

re : fclean all

bonus :
		@make -C $(LIBFT)
		@make ${NAME_B}

rebonus : fclean bonus

