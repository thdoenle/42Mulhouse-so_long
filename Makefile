LIB_SRCS	= get_next_line.c get_next_line_utils.c ft_put.c ft_str.c image.c \
	ft_mem.c lst.c resized_image.c anim.c foe.c move.c
PARS_SRCS	= parsing.c utils.c coords.c
HOOK_SRCS	= closefunc.c keyfunc.c loopfunc.c
GAME_SRCS	= $(HOOK_SRCS:%=hooks/%) start.c init_images.c update.c \
	update_pos.c update_player.c init_background.c which_tile.c which_floor.c \
	put_str_to_image.c update_hud.c animations.c draw_player.c tracks.c \
	foes.c update_foes.c restart.c strtoimage_len.c
SRCS		= main.c error.c free.c \
	$(LIB_SRCS:%=lib/%) $(PARS_SRCS:%=parsing/%) $(GAME_SRCS:%=game/%)
SRCS		:= $(SRCS:%=src/%)
OBJS		= $(SRCS:%.c=%.o)
HEADERS		= so_long.h lib.h get_next_line.h
HEADERS		:= $(HEADERS:%=inc/%)
HFLAGS		= -I inc/ -I /Users/$$USER/MLX42/include/MLX42/
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -Ofast#-fsanitize=address -g3
LDFLAGS		= -lglfw -L/Users/$$USER/.brew/lib/ -lmlx42 -L/Users/$$USER/MLX42/build
RM			= rm -rf
NAME		= so_long

$(NAME): $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(MLX) $(LDFLAGS) -o $@ $(OBJS)

all: $(NAME) bonus

bonus: $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(HFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
