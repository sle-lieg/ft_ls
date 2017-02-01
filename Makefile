NAME 	= ft_ls
FLAGS 	= -Wall -Wextra -Werror
SRCS	= ft_ls.c ft_parse.c ft_create_lst.c
OBJ		= $(SRCS:.c=.o)
LIB		= libft/libft.a

all : $(NAME)

$(NAME) : $(OBJ)
	gcc -o $@ $^ $(LIB)

$(OBJ) :
	gcc -c $(FLAGS) $(SRCS)

clean : $(OBJ)
	rm -rf $^

fclean : clean
	rm -rf $(NAME)

re : all
	clean
