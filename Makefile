NAME		=		pipex

CFLAGS 		=		-Wall -Wextra -Werror 

SRCS		=		main.c utils.c

LIBFT_DIR	=	 	libft

LIBFT		=		$(LIBFT_DIR)/libft.a


all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -L$(LIBFT_DIR) -lft -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re 