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
		brackets.c

OBJS = $(SRCS:.c=.o)

RM = rm -f
#CFLAGS = -Wall -Wextra -Werror
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	cc $(OBJS) -o $(NAME) -lreadline libft/libft.a -g3 -fsanitize=address
clean:
	$(RM) $(OBJS)

fclean:			clean
	$(RM) $(NAME)

re: fclean $(NAME)