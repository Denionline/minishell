
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

NAME			= minishell
LIBFT			= $(LIBFT_PATH)libft.a

# **************************************************************************** #
#                                   Path's                                     #
# **************************************************************************** #

INC_PATH		= include
BUILD_PATH		= .build/

VPATH			+= ./
VPATH			+= src/
VPATH			+= src/aux
VPATH			+= src/parse
VPATH			+= src/verify

LIBFT_PATH		= $(INC_PATH)/libft/

# **************************************************************************** #
#                                   Files                                      #
# **************************************************************************** #

FILES			+= main
FILES			+= initializer
FILES			+= minishell
FILES			+= parse
FILES			+= get_array_len
FILES			+= is_signal
FILES			+= end
FILES			+= print_cmds

SRCS			= $(addprefix ./, $(addsuffix .c, $(FILES)))
OBJS			= $(addprefix $(BUILD_PATH), $(addsuffix .o, $(FILES)))

# **************************************************************************** #
#                                    Git                                       #
# **************************************************************************** #

LIBFT_URL		= https://github.com/Denionline/libft.git

# **************************************************************************** #
#                                  Compiler                                    #
# **************************************************************************** #

CC				= cc
CFLAGS			= -Werror -Wextra -Wall
MAKE			= make --no-print-directory
RM				= rm -rf

# **************************************************************************** #
#                                  Commands                                    #
# **************************************************************************** #

all: start verify_libft $(NAME)
	@printf "$(C_MAGENTA)===========End [$(NAME)]===========$(C_STD)\n"

start:
	@printf "$(C_MAGENTA)===========Program [$(NAME)]===========$(C_STD)\n"

$(NAME): $(BUILD_PATH) $(OBJS)
	@$(CC) $(CFLAGS) -I$(INC_PATH) $(OBJS) -lreadline -lncurses $(LIBFT) -o $(NAME)

$(BUILD_PATH)%.o: %.c
	@$(CC) $(CFLAGS) -I$(INC_PATH) -c $< -o $@
	@printf "$(C_YELLOW)Compiling $< -> $@$(C_STD)\n";

$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH)

clean:
	@$(RM) $(BUILD_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

verify_libft:
	@if test ! -d "$(LIBFT_PATH)"; then $(MAKE) get_libft; \
		else printf "libft: $(C_GREEN)✅$(C_STD)\n"; fi
	@$(MAKE) -C $(LIBFT_PATH)

get_libft:
	@echo "Cloning Libft"
	@git clone $(LIBFT_URL) $(LIBFT_PATH)
	@printf "$(C_GREEN)libft$(C_STD) successfully downloaded\n"
