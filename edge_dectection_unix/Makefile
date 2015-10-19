# var
CC = gcc
NAME = edge
CFLAGS = -lm -I minilibx -L minilibx -lmlx -L /usr/X11/lib -lX11 -lXext
OBJDIR = obj/
HEADERDIR = .
SRCS = main.c \
	edge_detection.c \
	gaussian.c \
	lightness.c \
	apply_kernel.c \
	luminance.c \
	average.c \
	contrast.c \
	tools.c \
	corner.c

HEADER = edge_detection.h
OBJS = $(addprefix $(OBJDIR),$(subst .c,.o,$(SRCS)))
INCLUDES = -I libft/includes minilibx/mlx.a

.PHONY: all clean fclean re proper libft

all: libft $(NAME)

$(NAME): libft/libft.a $(OBJS) $(HEADER)
	gcc $(OBJS) -o $(NAME) $(INCLUDES) -L libft -lft $(CFLAGS)

debug: clean libft/libft.a $(OBJS) $(HEADER)
	gcc $(CFLAGS) $(OBJS) -g -o $(NAME) $(INCLUDES) -L libft -lft

libft:
	make -C libft

$(OBJS): | $(OBJDIR)

$(OBJDIR)%.o : %.c $(HEADER)
	$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDES)

$(OBJDIR):
	@if [ ! -d "$(OBJDIR)" ]; then \
		mkdir $(OBJDIR);\
		fi

clean:
	@make clean -C libft
	rm -rf $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf libft/libft.a
	rm -rf $(NAME)

proper: all clean

re: fclean all
