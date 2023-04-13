# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 19:14:08 by faksouss          #+#    #+#              #
#    Updated: 2023/04/13 00:10:42 by mfouadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CFLAGS := -Wall -Wextra -Werror -fsanitize=address

READLINE_LIB :=  -lreadline -L/Users/mfouadi/.brew/opt/readline/lib

RM := rm -rf

MAIN :=		main/src/mini_shell.c \
			main/src/sub_main_fncts.c \

PARSE := 	parsing/src/check_redirection.c \
			parsing/src/check_syntax.c \
			parsing/src/init_exc.c \
			parsing/src/lexer.c \
			parsing/src/remove_quotes.c \
			parsing/src/split_by_pp_and_rdrct.c \
			parsing/src/split_by_space.c \
			parsing/src/split_cmd_list.c \
			parsing/src/take_char_cmd.c \
			parsing/src/take_dollar.c \
			parsing/src/take_env.c \
			parsing/src/wild_card.c

EXEC :=  	execution/src/execution.c \
			execution/src/utils.c \
			execution/src/heredocument.c
			

SRC := $(MAIN) $(PARSE) $(EXEC)

OBJDIR := obj

OBJ := $(patsubst %, $(OBJDIR)/%, $(SRC:.c=.o))

HEADERS 	:=	built/inc/built.h \
				execution/inc/execution.h \
				parsing/inc/parsing.h \
				main/inc/mini_shell.h

INC_HEADERS :=	-Ibuilt/inc \
				-Iexecution/inc \
				-Iparsing/inc \
				-Imain/inc \
				-Ilibtool/inc \
				-I/Users/mfouadi/.brew/opt/readline/include


LIBTOOL := libtool/libft.a

all : $(NAME)


# readline is keg-only, which means it was not symlinked into /Users/mfouadi/.brew,
# because macOS provides BSD libedit.

# For compilers to find readline you may need to set:
#   export LDFLAGS="-L/Users/mfouadi/.brew/opt/readline/lib"
#   export CPPFLAGS="-I/Users/mfouadi/.brew/opt/readline/include"

$(NAME): $(LIBTOOL) $(OBJ)
	cc $(CFLAGS) $^ -o $@ $(READLINE_LIB)
	printf "\r\033[0;33mMINISHELL is ready to lunch enjoy 😉\033[0m\n"

$(OBJDIR)/%.o : %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC_HEADERS)

$(LIBTOOL) :
	@printf "\r\033[0;33m⏳ libtool is compiling ...\033[0m"
	@make -C libtool

clean : 
	@printf "\r\033[0;33mclearing object files 🚮🗑️ ...\033[0m"
	@make -C libtool clean
	$(RM) $(OBJDIR)

fclean : clean
	@printf "\r\033[0;33mYOU DELETED MY MINISHELL 😱 YOU !*#^&# 😡🤬\033[0m\n"
	@make -C libtool fclean
	$(RM) $(NAME)

re : fclean all

.PHONY: all fclean clean re

.SILENT: all clean fclean re $(NAME) $(LIBTOOL) img

img:
	clear
	printf "\r\n"
	echo "       	   :~-._                                                 _.-~:       "
	echo "       	   : :.~^o._        ________---------________        _.o^~.:.:       "
	echo "       	   : ::.'?88booo~~~.::::::::...::::::::::::..~~oood88P'.::.:         "
	echo "       	   :  ::: '?88P .:::....         ........:::::. ?88P' :::. :         "
	echo "       	    :  :::. '? .::.            . ...........:::. P' .:::. :          "
	echo "       	     :  :::   ... ..  ...       .. .::::......::.   :::. :           "
	echo "       	     '  :' .... ..  .:::::.     . ..:::::::....:::.  ': .'           "
	echo "       	       :..    ____:::::::::.  . . ....:::::::::____  ... :           "
	echo "       	      :... ':~    ^~-:::::..  .........:::::-~^    ~::.::::          "
	echo "       	      '.::. '\   \033[0;31m(8)\033[0m  \b:::..::.:.:::::::d/  \033[0;31m(8)\033[0m     /'.::::'          "
	echo "       	       ::::.  ~-._v  |b.::::::::::::::d|      v_.-~..:::::             "
	echo "       	       '.:::::... ~~^?888b..:::::::::::d888P^~...::::::::'           "
	echo "       	        '.::::::::::....~~~ .:::::::::~~~:::::::::::::::'            "
	echo "       	         '..:::::::::::   .   ....::::    ::::::::::::,'             "
	echo "       	           '. .:::::::    .     .::::.    ::::::::::'.                "
	echo "       	             '._ .:::    .  |     :::::.    :::::_.'                 "
	echo "       	                '-. :    .        :::::      :,-'                    "
	echo "       	                   :.   :___\    .:::___   .::                       "
	echo "       	         \033[0;33m..--~~~~--:\033[0m+::. ~~^?b..:::dP^~~.::++\033[0;33m:--~~~~--..\033[0m             "
	echo "       	           \033[0;33m___....--'\033[0m+:::.   \'~8~'/   .:::+\033[0;33m'--....___\033[0m               "
	echo "       	         \033[0;33m~~   __..---'\033[0m_=:: ___gd8bg___ :==_\033[0;33m'---..__   ~~\033[0m             "
	echo "       	          \033[0;33m-~~~  _.--~~'\033[0m-.~~~~~~~~~~~~~~~,-\033[0;33m' ~~--._ ~~~-\033[0m              "
	echo "       	              \033[0;33m-~~\033[0m        \ |~~~~~~~~~~~| /           \033[0;33m~~-\033[0m                "
	echo "       	                          \|  ~~~~~~~  |/                              \n"
	echo "\033[0;31m               ▄▄▄██▀▀▀▄▄▄        ▄████  █    ██  ▄▄▄       ██▀███     \033[0m" 
	echo "\033[0;31m                ▒██  ▒████▄     ██▒ ▀█▒ ██  ▓██▒▒████▄    ▓██ ▒ ██▒    \033[0m"
	echo "\033[0;31m                ░██  ▒██  ▀█▄  ▒██░▄▄▄░▓██  ▒██░▒██  ▀█▄  ▓██ ░▄█ ▒    \033[0m"
	echo "\033[0;31m             ▓██▄██▓ ░██▄▄▄▄██ ░▓█  ██▓▓▓█  ░██░░██▄▄▄▄██ ▒██▀▀█▄      \033[0m"
	echo "\033[0;31m              ▓███▒   ▓█   ▓██▒░▒▓███▀▒▒▒█████▓  ▓█   ▓██▒░██▓ ▒██▒    \033[0m"
	echo "\033[0;31m              ▒▓▒▒0   ▒▒   ▓▒█1 0▒   ▒ v▒▓▒ ▒ ▒  ▒▒   ▓▒█░░ ▒▓ ░▒▓░    \033[0m"
	echo "\033[0;31m              1 0▒1    ▒   ▒▒ 2  ?   1 h░▒░ T :   ▒   1▒ 0  0▒ d ▒r    \033[0m"
	echo "\033[0;31m              0 J ;    K   ▒   X !   &  1!1 ; |   3   L     10   Q     \033[0m"
	echo "\033[0;31m                  1        1  0      /    0           ^  Z   1         \033[0m\n"          
