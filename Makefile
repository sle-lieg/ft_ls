NAME 	= ft_ls
FLAGS 	= -Wall -Wextra -Werror
SRCS	= ft_ls.c ft_parse.c ft_dir_lst.c ft_fil_lst.c
OBJ		= $(SRCS:.c=.o)
LIB		= libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	gcc -c $(SRCS)
	gcc $(OBJ) $(LIB) -o $(NAME)
	#gcc -o $@ $(OBJ) $(LIB)

$(OBJ):
	gcc -c $(FLAGS) $(SRCS)

clean: $(OBJ)
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
