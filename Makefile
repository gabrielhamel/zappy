##
## EPITECH PROJECT, 2019
## PSU_zappy_2018
## File description:
## Makefile
##


SRC_COMN =	./commons/src/sockets/client.c		\
			./commons/src/sockets/list_close.c	\
			./commons/src/sockets/list_event.c	\
			./commons/src/sockets/list_utils.c	\
			./commons/src/sockets/server.c

SRC_SERV =  ./server/src/main.c

SRC_AI =  	./ai/src/main.c

INC_DIR =	-I ./commons/include	\
			-I ./server/include		\
			-I ./ai/include

OBJ_COMN =  $(SRC_COMN:.c=.o)

OBJ_SERV =  $(SRC_SERV:.c=.o)

OBJ_AI =  	$(SRC_AI:.c=.o)

CFLAGS +=	$(INC_DIR) -W -Wall -Wextra

RM =		@rm -rf

ECHO =		/bin/echo -e

DEFAULT =	"\033[00m"

GREEN =		"\033[1;32m"

TEAL =		"\033[1;37m"

RED =		"\033[1;33m"

SANG =		"\033[1;31m"

all:		titre_comn zappy_server zappy_ai

titre_comn:
			@$(ECHO) $(RED)¶ Building commons files$(TEAL):$(DEFAULT)

titre_server:
			@$(ECHO) $(RED)¶ Building server$(TEAL):$(DEFAULT)

titre_ai:
			@$(ECHO) $(RED)¶ Building ai$(TEAL):$(DEFAULT)

zappy_server: $(OBJ_COMN) titre_server $(OBJ_SERV)
			@gcc -o zappy_server $(OBJ_COMN) $(OBJ_SERV) && $(ECHO) $(GREEN)✓$(TEAL)" BUILD SUCCESS !"$(TEAL) $(DEFAULT) || $(ECHO) $(SANG)✗$(TEAL)" BUILD FAILED !"$(TEAL) $(DEFAULT)

zappy_ai:	$(OBJ_COMN) titre_ai $(OBJ_AI)
			@gcc -o zappy_ai $(OBJ_COMN) $(OBJ_AI) && $(ECHO) $(GREEN)✓$(TEAL)" BUILD SUCCESS !"$(TEAL) $(DEFAULT) || $(ECHO) $(SANG)✗$(TEAL)" BUILD FAILED !"$(TEAL) $(DEFAULT)

clean:
			@$(ECHO) $(RED)¶ Cleaning$(TEAL):$(DEFAULT)
			@$(ECHO) $(GREEN)  " [OK]" $(TEAL)"Clean obj"$(TEAL)
			$(RM) $(OBJ_COMN)
			@($(ECHO) $(GREEN)✓$(TEAL)" CLEAN SUCCESS !"$(TEAL))

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

%.o : %.c
			@gcc -c -o $@ $^ $(CFLAGS) && $(ECHO) -n $(GREEN)"  [OK] "$(TEAL) || $(ECHO) -n $(SANG)"  [NO] "$(TEAL) && $(ECHO) $< | rev | cut -d'/' -f 1 | rev

.PHONY:		all fclean re clean zappy_ai zappy_server