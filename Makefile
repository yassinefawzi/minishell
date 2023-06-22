SRCS =	commands/commands.c \
		helper.c \
		main.c \
		free.c \
		env.c \
		libft/ft_strlen.c \
		libft/ft_strjoin.c \
		libft/ft_strncmp.c \
		libft/ft_strlcpy.c
 
OBJS = $(SRCS:.c=.o)

RM = rm -f
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean:
	$(RM) $(OBJS)

fclean:			clean
	$(RM) $(NAME)

re: fclean $(NAME)