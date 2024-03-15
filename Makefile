SERVER_NAME	=	server
CLIENT_NAME =	client
CC		=	cc
FLAGS 	=	-g -Wall -Werror -Werror
LIBFT_PATH = libft/
LIBFT_FILE = libft/libft.a

SERVER_SRC		=	$(wildcard src_server/*.c)
CLIENT_SRC		=	$(wildcard src_client/*.c)
SERVER_OBJ		=	$(patsubst %.c,%.o,$(SERVER_SRC))
CLIENT_OBJ		=	$(patsubst %.c,%.o,$(CLIENT_SRC))
RM				=	rm -f

.SUFFIXES: .c .o

$(SERVER_NAME): $(SERVER_OBJ)
	make -C libft/
	$(CC) $(FLAGS) $(SERVER_OBJ) $(LIBFT_FILE) -o $(SERVER_NAME) -I includes/

$(CLIENT_NAME): $(CLIENT_OBJ)
	make -C libft/
	$(CC) $(FLAGS) $(CLIENT_OBJ) $(LIBFT_FILE) -o $(CLIENT_NAME) -I includes/

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ -I includes/


all: $(CLIENT_NAME) $(SERVER_NAME)

clean:
	echo "Deleting Obj file in $(LIBFT_PATH)...\n"
	make clean -sC $(LIBFT_PATH)
	@echo "Done\n"
	@echo "Deleting Minitalk object...\n"
	rm -f $(SERVER_OBJ)
	rm -f $(CLIENT_OBJ)
	@echo "Done\n"

fclean: clean
	@echo "Deleting Minitalk executable..."
	rm -f $(SERVER_NAME)
	rm -f $(CLIENT_NAME)
	make fclean -C $(LIBFT_PATH)
	@echo "Done\n"

re: fclean all

.PHONY: all clean fclean re
