SRCS =	commands/commands.c \
		helper.c \
		main.c \
		free.c \
		env.c \
		linkfile.c \
		error.c \
		quotes_check.c \
		spaces_parsing.c \
		pipes.c \
		brackets.c \
		red.c \
		execution/execution.c \
		fd.c

RM = rm -f
NAME = minishell
CFLAGS = -g3 -fsanitize=address

all: $(NAME)

$(NAME):
#	make -C ./libft
	clang $(CFLAGS) $(SRCS) -o $(NAME) -lreadline libft/libft.a
clean:
	make -C ./libft clean

fclean:			clean
#	make -C ./libft fclean
	$(RM) $(NAME)

re: fclean $(NAME)