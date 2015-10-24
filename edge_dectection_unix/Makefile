# var
CC = gcc
NAME = edge
UNAME_S := $(shell uname -s)
CFLAGS = -Wall -Wextra -Werror

ifeq ($(UNAME_S),Linux)
LIB = -lm -L libft -lft -L minilibx -lmlx -L /usr/X11/lib -lX11 -lXext
INCLUDES = -I libft/includes -I minilibx
endif
ifeq ($(UNAME_S),Darwin)
INCLUDES = -I libft/includes -I /usr/include/
LIB = -I /usr/include/mlx.h -L/usr/local/lib -lmlx -framework OPENGL -framework AppKit \
		-L libft -lft
endif

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
	corner.c \
	img2.c \
	kernel.c

HEADER = edge_detection.h
OBJS = $(addprefix $(OBJDIR),$(subst .c,.o,$(SRCS)))

.PHONY: all clean fclean re proper libft

all: libft $(NAME)

$(NAME): libft/libft.a $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES) $(LIB)

debug: clean libft/libft.a $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIB) $(INC) $(OBJS) -o $(NAME) -g

libft:
	make -C libft

$(OBJS): | $(OBJDIR)

$(OBJDIR)%.o : %.c $(HEADER)
	$(CC) -c $< -o $@ $(INCLUDES)

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
