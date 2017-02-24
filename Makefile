NAME 	 = ft_ls

FLAGS 	 = -Wall -Wextra -Werror

SRCS	 = ft_ls.c ft_parse.c ft_dir_lst.c ft_fil_lst.c read_dir.c\
			read_dir2.c print_file.c print_file2.c

OBJ		 = $(SRCS:.c=.o)

LIB_PATH = ./libft

LIB		 = -lft

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_PATH)
	@gcc $(OBJ) -L $(LIB_PATH) $(LIB) -o $(NAME)
	@echo "\033[1;32m◊ +++++ CREATING $(NAME)	        : √\033[0m"

%.o: %.c
	@gcc -c $(FLAGS) $(SRCS)
	@echo "\033[1;32m◊ +++++ CREATING $(NAME) OBJECTS	: √\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;31m◊ ----- DELETING $(NAME)	        : √\033[0m"

clean:
	@make clean -C $(LIB_PATH)
	@rm -rf $(OBJ)
	@echo "\033[1;31m◊ ----- DELETING $(NAME) OBJECTS	: √\033[0m"

re: fclean all