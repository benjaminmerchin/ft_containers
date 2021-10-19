NAME	=	ft_containers
NAME_STD=	std_containers
SEED	=	123
CC		=	clang++
OBJDIR	=	objects
SRC		=	main.cpp
SRC_TEST=	main_temp.cpp
OBJ 	=	$(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
OBJ_TEST=	$(addprefix $(OBJDIR)/, $(SRC_TEST:.cpp=.o))
CFLAGS	=	-Wall -Wextra -Werror -std=c++98 -fsanitize=address -g#-Wshadow -Wno-shadow -g3

ifneq (,$(findstring xterm,${TERM}))
	GREEN := $(shell tput -Txterm setaf 2)
	RESET := $(shell tput -Txterm sgr0)
else
	GREEN := ""
	RESET := ""
endif

all: $(NAME)

bonus: all

go: fclean $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "${GREEN}Compilation Done & Executing Program${RESET}"
#	@echo "Default seed: " $(SEED)
	@./$(NAME) $(SEED)

test: fclean $(OBJ_TEST)
	@$(CC) $(CFLAGS) $(OBJ_TEST) -o $(NAME)
	@echo "${GREEN}Compilation Done & Executing Program${RESET}"
#	@echo "Default seed: " $(SEED)
	@./$(NAME) $(SEED)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "${GREEN}Compilation Done${RESET}"

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) -f $(OBJ_TEST)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus go
