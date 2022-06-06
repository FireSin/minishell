NAME = minishell
CC = cc

CFLAGS = -g -Wall -Wextra -Werror
IREADFL = -I/Users/${USER}/.brew/opt/readline/include
LREADFL = -L/Users/${USER}/.brew/opt/readline/lib

OBJDIR = ./objs
VPATH = ./srcs ./srcs/bultins ./srcs/launcher ./srcs/parser ./srcs/utils ./srcs/wildcard ./srcs/bonus
LIBFT_DIR = libft/
HEADDIR = ./includes

HEADER = minishell.h
LIBFT = libft/libft.a
OBJ = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))
SRC = $(wildcard $(addsuffix /*.c,$(VPATH)))


all:    $(LIBFT) $(NAME)

$(OBJDIR)/%.o :	%.c $^ $(HEADDIR)/$(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@ ${IREADFL}

$(NAME):	$(OBJDIR) $(OBJ)
	@$(CC) $(CFLAGS) -lreadline ${IREADFL} ${LREADFL}  -o $(NAME) $(LIBFT_DIR)libft.a -I$(HEADER) $(OBJ) 
	@echo "minishell compile"

$(OBJDIR):
	@if [ ! -d $(OBJDIR) ] ; then mkdir $(OBJDIR); fi

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@if [ -d $(OBJDIR) ] ; then rm -r $(OBJDIR); fi
	@make fclean -C $(LIBFT_DIR)
	@echo "clean minishell done"


fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
