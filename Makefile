SRCS =	commands/commands.c

OBJS = $(SRCS:.c=.o)

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

all:$(NAME)

$(NAME):$(OBJS)
	cc -Wall -Wextra -Werror $(NAME) $(OBJS) 

clean:
	$(RM) $(OBJS)

fclean:			clean
	$(RM) $(NAME)

re: