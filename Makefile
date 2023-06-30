SRCS =	commands/commands.c \
		helper.c \
		main.c \
		free.c \
		env.c \
		linkfile.c

OBJS = $(SRCS:.c=.o)

RM = rm -f
#CFLAGS = -Wall -Wextra -Werror
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	cc $(OBJS) -o $(NAME) -lreadline libft/libft.a

clean:
	$(RM) $(OBJS)

fclean:			clean
	$(RM) $(NAME)

re: fclean $(NAME)