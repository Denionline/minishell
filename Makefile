# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/19 17:13:48 by dximenes          #+#    #+#              #
#    Updated: 2025/08/19 17:25:33 by dximenes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                    Colors                                    #
# **************************************************************************** #

C_STD = \033[0;39m
C_GRAY = \033[0;90m
C_RED = \033[0;91m
C_GREEN = \033[0;92m
C_YELLOW = \033[0;93m
C_BLUE = \033[0;94m
C_MAGENTA = \033[0;95m
C_CYAN = \033[0;96m
C_WHITE = \033[0;97m

# **************************************************************************** #
#                                    Files                                     #
# **************************************************************************** #

NAME				= minishell
LIBFT				= $(LIBFT_PATH)libft.a

# **************************************************************************** #
#                                   Path's                                     #
# **************************************************************************** #

INC_PATH			= include/
SRC_PATH			= src/
BUILD_PATH			= .build/

LIBFT_PATH			= $(INC_PATH)/libft/

# **************************************************************************** #
#                                   Files                                      #
# **************************************************************************** #

MAIN				= main

FILES				+= parse

SRC_FILES			+= $(MAIN)
SRC_FILES			+= $(addprefix $(SRC_PATH), $(FILES))

OBJ_FILES			+= $(MAIN)
OBJ_FILES			+= $(FILES)

SRCS				= $(addprefix ./, $(addsuffix .c, $(SRC_FILES)))
OBJS				= $(addprefix $(BUILD_PATH), $(addsuffix .o, $(OBJ_FILES)))

# **************************************************************************** #
#                                    Git                                       #
# **************************************************************************** #

LIBFT_URL		= https://github.com/Denionline/libft.git

# **************************************************************************** #
#                                  Compiler                                    #
# **************************************************************************** #

CC							= cc
LIBS						= $(LIBFT)
CFLAGS						= -Werror -Wextra -Wall
MAKE						= make --no-print-directory

# **************************************************************************** #
#                                  Commands                                    #
# **************************************************************************** #

all: start check_libraries $(NAME)
	@printf "$(C_MAGENTA)===========End [$(NAME)]===========$(C_STD)\n"

start:
	@printf "$(C_MAGENTA)===========Program [$(NAME)]===========$(C_STD)\n"

$(NAME): compile_files
	@$(CC) $(CFLAGS) -I$(INC_PATH) $(OBJS) $(LIBS) -o $(NAME)

compile_files: $(BUILD_PATH)
	@printf "$(C_YELLOW)Compile $(NAME) files:$(C_STD)\n"
	@TOTAL=$$(echo $(SRCS) | wc -w);\
	CUR=1;\
	for SRC in $(SRCS); do\
		OBJ=$(BUILD_PATH)$$(basename $$SRC .c).o;\
		$(CC) $(CFLAGS) -I$(INC_PATH) -c $$SRC -o $$OBJ;\
		PERC=$$(printf "%d" $$((100 * CUR / TOTAL)));\
		FILLED=$$(printf "%0.f" $$((20 * PERC / 100)));\
		EMPTY=$$((20 - FILLED));\
		BAR=$$(printf "$(C_GREEN)%*s$(C_STD)" $$FILLED "" | tr " " "#")$$(\
		printf "%*s" $$EMPTY "" | tr " " ".");\
		printf "\rCompiling [%s] %3d%%" $$BAR $$PERC;\
		CUR=$$((CUR + 1)); \
	done;\
	printf "\n";

$(BUILD_PATH):
	@mkdir $(BUILD_PATH)

clean:
	@rm -rf $(BUILD_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

check_libraries: verify_libft

verify_libft:
	@if test ! -d "$(LIBFT_PATH)"; then $(MAKE) get_libft; \
		else printf "libft: $(C_GREEN)✅$(C_STD)\n"; fi
	@$(MAKE) -C $(LIBFT_PATH)

get_libft:
	@git clone $(FTPRINTF_URL) $(LIBFT_PATH)