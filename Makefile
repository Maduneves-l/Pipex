##########################################################
#					Instructions						 #
##########################################################

NAME =  pipex
BONUS_NAME = pipex_bonus
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address 
CC = cc

##########################################################
#					SOURCES AND OBJS					 #
##########################################################

SRCS = srcs/pipex.c srcs/utils.c

BONUS_SRCS = srcs/pipex_bonus.c srcs/utils_bonus.c srcs/get_next_line.c srcs/utils.c

OBJS :=$(SRCS:.c=.o)

OBJS_BONUS :=$(BONUS_SRCS:.c=.o)


##########################################################
#					CODIGOS ANSI						 #
##########################################################


CLR_RMV		= \033[0m
RED		    = \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
CLEARBLUE	= \033[1;94m
CYAN 		= \033[1;36m
PURPLE		= \033[1;35m
WHITE 		= \033[1;37m
BLACK 		= \033[1;30m
GREY 		= \033[0;37m

all: $(NAME)

$(NAME) : $(OBJS)
	@echo
	@make -C ./libft/ 
	${CC} -I ${CFLAGS} $(OBJS) ./libft/libft.a -o $(NAME)
	@clear
	@echo "$(YELLOW)---------------------------------------"
	@echo "$(GREEN)Compilation of ${CLR_RMV}${CYAN}$(NAME): ${CLR_RMV}$(GREEN)⭐️"
	@echo "$(CYAN)$(NAME) ${CLR_RMV}$(GREEN)created with sucess ${CLR_RMV} ✔️"
	@echo "$(YELLOW)---------------------------------------${CLR_RMV}"

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJS_BONUS)
	@echo "$(PURPLE)Compiling bonus..."
	@make -C ./libft/
	${CC} -I ${CFLAGS} $(OBJS_BONUS) ./libft/libft.a -o $(BONUS_NAME)
	@clear
	@echo "$(GREEN)Bonus compiled with sucess!⭐️${CLR_RMV}"

bclean:
	rm -f $(OBJS_BONUS)
	rm -f $(BONUS_NAME)
	clear
	@echo "$(RED)Deleting🗑 $(PURPLE)-> $(YELLOW)$(NAME) $(CLR_RMV)$(RED)[objs]$(GREEN) ✔️${CLR_RMV}"


clean:
	rm -f $(OBJS)
	clear
	@echo "$(RED)Deleting🗑 $(PURPLE)-> $(YELLOW)$(NAME) $(CLR_RMV)$(RED)[objs]$(GREEN) ✔️${CLR_RMV}"

fclean: clean
	rm -f $(NAME)
	clear
	@echo "$(RED)Deleting🗑 $(PURPLE)-> $(YELLOW)$(NAME) $(CLR_RMV)$(RED)[objs] $(GREEN)✔️${CLR_RMV}"

re: fclean all

.PHONY: all clean fclean re
