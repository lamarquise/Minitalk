
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

NAME		=	minitalk
CLIENT		=	client
SERVER		=	server

DIR_SRCS		=	./srcs/

DIR_CLIENT		=	$(DIR_SRCS)
SRCS_CLIENT		=	client_main.c \

DIR_SERVER		=	$(DIR_SRCS)
SRCS_SERVER		=	server_main.c \

# we can add shit if do bonus.

	# we may not use everything...

DIR_MINILIB		=	./minilib/
SRCS_MINILIB	=	atoi_funcs.c \
					big_str_funcs.c \
					ft_split.c \
					ft_strjoin.c \
					list_funcs.c \
					nlist_funcs.c \
					nlstdel_n_one.c \
					ilist_funcs.c \
					put_funcs.c \
					str_funcs.c \
					error_funcs.c \
					tab_funcs.c \
					gnl.c \
					gnl_utils.c \

DIR_INC		=	./
INCS		=	-I$(DIR_INC)

ALL_INCS	=	$(INCS) -I./minilib/

DIR_OBJ		=	./objs/

OBJ_MINILIB		=	$(SRCS_MINILIB:.c=.o)
OBJ_CLIENT		=	$(SRCS_CLIENT:.c=.o) $(OBJ_MINILIB)
OBJ_SERVER		=	$(SRCS_SERVER:.c=.o) $(OBJ_MINILIB)

OBJS_CLIENT		=	$(addprefix $(DIR_OBJ),$(OBJ_CLIENT))
OBJS_SERVER		=	$(addprefix $(DIR_OBJ),$(OBJ_SERVER))


# we can add shit if do bonus

	### Rules ###

all: $(NAME)

	# we will sort out how to do bonuses later...
#bonus: $(NAME) $(CHECKER)

	### EXECUTABLE CREATION ###
$(NAME): $(CLIENT) $(SERVER)

$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(ALL_INCS) $(OBJS_CLIENT) -o $(CLIENT)
	printf "$(_GREEN)\r\33[2K\r$(CLIENT) created  😎\n$(_END)"

$(SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(ALL_INCS) $(OBJS_SERVER) -o $(NAME)
	printf "$(_GREEN)\r\33[2K\r$(NAME) created  😎\n$(_END)"


	### BINARY CREATION ###

$(DIR_OBJ)%.o: $(DIR_CLIENT)%.c
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) $(ALL_INCS) -c $< -o $@
	printf "$(_CYAN)\r\33[2K\rCompling $@$(_END)"

$(DIR_OBJ)%.o: $(DIR_SERVER)%.c
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) $(ALL_INCS) -c $< -o $@
	printf "$(_CYAN)\r\33[2K\rCompling $@$(_END)"

$(DIR_OBJ)%.o: $(DIR_MINILIB)%.c
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) $(ALL_INCS) -c $< -o $@
	printf "$(_CYAN)\r\33[2K\rCompling $@$(_END)"


	### CLEANING ###

clean:
	rm -rf $(DIR_OBJ)
	echo "$(_RED).o Files Deleted  😱$(_END)"

fclean: clean
	rm -rf $(CLIENT) $(SERVER)
	echo "$(_RED)$(CLIENT) and $(SERVER) Deleted  😱$(_END)"

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re testlc testlp testsc testsp

.SILENT:

##################
##    COLORS    ##
##################

_GREY=$ \033[30m
_RED=$ \033[31m
_GREEN=$ \033[32m
_YELLOW=$ \033[33m
_BLUE=$ \033[34m
_PURPLE=$ \033[35m
_CYAN=$ \033[36m
_WHITE=$ \033[37m
_END=$ \033[0m