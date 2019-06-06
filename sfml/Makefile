##
## EPITECH PROJECT, 2019
## CCP_plazza_2018
## File description:
## Makefile
##

CC = g++

LDFLAGS =  -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR =	$(realpath src)

HEA_DIR =	$(realpath include)

INC_DIR =	-I$(HEA_DIR)

SRC =		$(SRC_DIR)/Main.cpp			\
			$(SRC_DIR)/Application.cpp	\
			$(SRC_DIR)/Server.cpp		\
			$(SRC_DIR)/Client.cpp		\
			$(SRC_DIR)/Utils.cpp		\
			$(SRC_DIR)/Render.cpp		\
			$(SRC_DIR)/Team.cpp			\
			$(SRC_DIR)/Player.cpp

NAME =		graphic

OBJ =		$(SRC:.cpp=.o)

RM =		@rm -rf

ECHO =		/bin/echo -e

DEFAULT =	"\033[00m"

GREEN =		"\033[1;32m"

TEAL =		"\033[1;37m"

RED =		"\033[1;33m"

SANG =		"\033[1;31m"

all:		titre $(NAME)

titre:
			@$(ECHO) $(RED)¶ Building $(NAME)$(TEAL):$(DEFAULT)

$(NAME):	$(OBJ)
			@$(CC) -o $(NAME) $(OBJ) $(INC_DIR) $(LDFLAGS) && $(ECHO) $(GREEN)✓$(TEAL)" BUILD SUCCESS !"$(TEAL) $(DEFAULT) || $(ECHO) $(SANG)✗$(TEAL)" BUILD FAILED !"$(TEAL) $(DEFAULT)

clean:
			@$(ECHO) $(RED)¶ Cleaning$(TEAL):$(DEFAULT)
			@$(ECHO) $(GREEN)  " [OK]" $(TEAL)"Clean obj"$(TEAL)
			$(RM) $(OBJ)
			@($(ECHO) $(GREEN)✓$(TEAL)" CLEAN SUCCESS !"$(TEAL))

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.cpp.o:
			@$(CC) -c -o $@ $^ $(INC_DIR) && $(ECHO) -n $(GREEN)"  [OK] "$(TEAL) || $(ECHO) -n $(SANG)"  [NO] "$(TEAL) && $(ECHO) $< | rev | cut -d'/' -f 1 | rev

.PHONY:		all fclean re clean
