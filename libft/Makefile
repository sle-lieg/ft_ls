NAME = libft.a

FLAGS = -g -Wall -Wextra -Werror

SRC = ft_memset.c ft_bzero.c ft_memcpy.c\
	  ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c\
	  ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c\
	  ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c\
	  ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c\
	  ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isupper.c\
	  ft_islower.c ft_isdigit.c ft_isalnum.c ft_isascii.c\
	  ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c\
	  ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c\
	  ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c\
	  ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c\
	  ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c\
	  ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c\
	  ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	  ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c\
	  ft_lstiter.c ft_lstmap.c ft_isupper.c ft_islower.c\
	  ft_lstaddend.c ft_d_lstaddfront.c ft_d_lstaddend.c \
	  ft_d_lstdel.c ft_d_lstdelone.c ft_switchchar.c ft_itoa.c\
	  ft_count_n.c ft_pow.c ft_itoa_base.c ft_get_next_line.c\
	  ft_str_is_inc.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@echo "\033[1;32m◊ +++++ CREATING $(NAME)	: √\033[0m"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@gcc -c $(FLAGS) $(SRC)	
	@echo "\033[1;32m◊ +++++ CREATING $(NAME) OBJECTS: √\033[0m"

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[1;31m◊ ----- DELETING $(NAME)	        : √\033[0m"

clean :
	@rm -rf $(OBJ)
	@echo "\033[1;31m◊ ----- DELETING $(NAME) OBJECTS: √\033[0m"

re : fclean all