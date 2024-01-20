CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3 -fsanitize=thread
INCLUDE = -I./includes
VPATH = srcs srcs/activities srcs/utils srcs/threads
RM = rm -rf
NAME = philo


SRCS = eat.c psleep.c think.c\
	   error.c input.c thread.c monitoring.c init.c\
	   utils.c utils2.c\
	   main.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR)  $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)

bonus: all

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus