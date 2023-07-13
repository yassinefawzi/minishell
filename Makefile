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
		red.c

OBJS = $(SRCS:.c=.o)

RM = rm -f
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	cc $(OBJS) -o $(NAME) -lreadline libft/libft.a
clean:
	$(RM) $(OBJS)

fclean:			clean
	$(RM) $(NAME)

re: fclean $(NAME)