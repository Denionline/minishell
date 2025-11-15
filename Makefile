	
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
VALGRINDRC		= ~/.valgrindrc
READLINESUPP	= ~/.readline.supp

# **************************************************************************** #
#                                   Path's                                     #
# **************************************************************************** #

INC_PATH		= include
BUILD_PATH		= .build/

VPATH			+= ./
VPATH			+= src/
VPATH			+= src/aux
VPATH			+= src/aux/env
VPATH			+= src/aux/get
VPATH			+= src/aux/btree
VPATH			+= src/parse
VPATH			+= src/parse/aux
VPATH			+= src/parse/aux/get
VPATH			+= src/parse/aux/string_argument
VPATH			+= src/parse/aux/string_argument/aux
VPATH			+= src/verify
VPATH			+= src/execute
VPATH			+= src/signal
VPATH			+= src/builtin
VPATH			+= src/builtin/aux
VPATH			+= src/builtin/aux/get
VPATH			+= src/error

LIBFT_PATH		= $(INC_PATH)/libft/

# **************************************************************************** #
#                                   Files                                      #
# **************************************************************************** #

FILES			+= main
FILES			+= initializer
FILES			+= minishell
FILES			+= print
FILES			+= end
FILES			+= signal_handler
FILES			+= free_all
FILES			+= new_shlvl
FILES			+= is_variable_exist
FILES			+= is_directory
#parsing
FILES			+= get_size_double_array
FILES			+= parse
FILES			+= heredoc
FILES			+= get_operator
FILES			+= get_valid_path
FILES			+= get_command
FILES			+= handle_file
FILES			+= get_var_path
FILES			+= string_argument
FILES			+= string_argument_size
FILES			+= is_tohandle_backslash
FILES			+= is_var_char
FILES			+= quotes
FILES			+= get_realloc_args
FILES			+= is_valid_argument
FILES			+= is_quotes_valid
#binary_tree
FILES			+= btree_create
FILES			+= btree_add_last_left
FILES			+= btree_add_last_right
FILES			+= btree_add_as_first
FILES			+= btree_set_file_last_cmd
#execute
FILES			+= process_manager
FILES			+= execute
FILES			+= execute_utils
FILES			+= builtin
#built-in
FILES			+= ft_pwd
FILES			+= ft_cd
FILES			+= ft_env
FILES			+= ft_echo
FILES			+= ft_export
FILES			+= ft_unset
FILES			+= ft_exit
FILES			+= get_ascii_order
#error
FILES			+= error


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
CFLAGS			= -Werror -Wextra -Wall -g
MAKE			= make --no-print-directory
RM				= rm -rf
LIBS			= $(LIBFT)

# **************************************************************************** #
#                                  Commands                                    #
# **************************************************************************** #

all: start verify_libft $(VALGRINDRC) $(NAME)
	@printf "$(C_MAGENTA)===========End [$(NAME)]===========$(C_STD)\n"

start:
	@printf "$(C_MAGENTA)===========Program [$(NAME)]===========$(C_STD)\n"

$(NAME): $(BUILD_PATH) $(OBJS)
	@$(CC) $(CFLAGS) -I$(INC_PATH) $(OBJS) -lreadline $(LIBS) -o $(NAME)

$(BUILD_PATH)%.o: %.c
	@$(CC) $(CFLAGS) -I$(INC_PATH) -c $< -o $@
	@printf "$(C_YELLOW)Compiling $< -> $@$(C_STD)\n";

$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH)

clean:
	@$(RM) $(BUILD_PATH)

fclean: clean
	@$(RM) .heredoc_*
	@$(RM) $(NAME)

re: fclean all

$(VALGRINDRC): $(READLINESUPP)
	@echo "--suppressions=$(HOME)/.readline.supp" > $(VALGRINDRC)

$(READLINESUPP):
	@echo "\
	{\n\
		leak readline\n\
		Memcheck:Leak\n\
		...\n\
		fun:readline\n\
	}\n\
	{\n\
		leak add_history\n\
		Memcheck:Leak\n\
		...\n\
		fun:add_history\n\
	}" > $(READLINESUPP)

verify_libft:
	@if test ! -d "$(LIBFT_PATH)"; then $(MAKE) get_libft; \
		else printf "libft: $(C_GREEN)✅$(C_STD)\n"; fi
	@$(MAKE) -C $(LIBFT_PATH)

get_libft:
	@echo "Cloning Libft"
	@git clone $(LIBFT_URL) $(LIBFT_PATH)
	@printf "$(C_GREEN)libft$(C_STD) successfully downloaded\n"

#valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes
# -fsanitize=address,undefined -fno-omit-frame-pointer
