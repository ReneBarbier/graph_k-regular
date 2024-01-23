NAME	= Peer2Pong
CFLAGS	= -Wall -Werror -Wextra

OBJ_DIR = obj/
SRC_DIR = src/

SOURCES =	patron_finder.c \
			utils.c \
			get_next_line.c

OBJECTS = $(addprefix $(OBJ_DIR), $(SOURCES:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c peer2pong.h Makefile
	@cc $(CFLAGS) -c $< -o $@
	@echo Compiling $< ...

$(NAME): $(OBJECTS)
	@cc $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "\033[0;32mphilosophers compiled\033[0m"

$(OBJ_DIR):
	-@mkdir -p $(OBJ_DIR);

clean :
	@rm -fr $(OBJ_DIR)
	@echo cleaning objects

fclean : clean
	@rm -f $(NAME)
	@echo cleaning \'$(NAME)\' file
	
re: fclean all

.PHONY: all clean fclean re