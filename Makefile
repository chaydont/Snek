NAME=game
LIBFT=libft.a
LIBFT_PATH=./libft
SDL_PATH=./sdl

SRC_NAME=display.c \
		 game.c \
		 main.c \
		 algo.c

SRC=$(addprefix srcs/, $(SRC_NAME))
OBJ=$(patsubst srcs/%.c, obj/%.o, $(SRC))

OBJ_DIR=obj

CC=gcc
INC=-I includes -I libft/includes -I $(SDL_PATH)/include
SDL=-L $(SDL_PATH)/lib -l SDL2-2.0.0
CFLAGS=-Wall -Wextra -Werror -g $(INC) -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@echo "Compile the game"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_PATH)/$(LIBFT) $(SDL)

obj/%.o: srcs/%.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C libft clean
	@rm -rf obj

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all
