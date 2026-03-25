NAME= codexion

CC= cc
CFLAGS= -Wall -Wextra -Werror -pthread
RM= rm -f

SRCS= check_args.c \
gearing.c \
helper.c \
main.c \
routine.c \
starting.c

OBJS= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c codexion.h
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    $(RM) $(OBJS)

fclean: clean
    $(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re