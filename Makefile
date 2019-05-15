##
## EPITECH PROJECT, 2019
## PSU_zappy_2018
## File description:
## Makefile
##


SRC_SERV =	./server/src/sockets/client.c		\
			./server/src/sockets/list_close.c	\
			./server/src/sockets/list_event.c	\
			./server/src/sockets/list_utils.c	\
			./server/src/sockets/server.c		\
			./server/src/loop.c					\
			./server/src/main.c					\
			./server/src/events.c				\
			./server/src/commands.c				\
			./server/src/utils/array.c			\
			./server/src/utils/ioutils.c		\
			./server/src/utils/read.c			\
			./server/src/utils/strings.c		\
			./server/src/fct_cli.c
			# ./server/src/commands/buffer_cmd/buffer_cmd.c

INC_DIR =	-I ./server/include

OBJ_SERV =  $(SRC_SERV:.c=.o)

CFLAGS +=	$(INC_DIR) -W -Wall -Wextra

RM =		@rm -rf

ECHO =		/bin/echo -e

DEFAULT =	"\033[00m"

GREEN =		"\033[1;32m"

TEAL =		"\033[1;37m"

RED =		"\033[1;33m"

SANG =		"\033[1;31m"

all:		zappy_server zappy_ai

titre_server:
			@$(ECHO) $(RED)¶ Building server$(TEAL):$(DEFAULT)

titre_ai:
			@$(ECHO) $(RED)¶ Building ai$(TEAL):$(DEFAULT)

zappy_server: titre_server $(OBJ_SERV)
			@gcc -o zappy_server $(OBJ_SERV) && $(ECHO) $(GREEN)✓$(TEAL)" BUILD SUCCESS !"$(TEAL) $(DEFAULT) || $(ECHO) $(SANG)✗$(TEAL)" BUILD FAILED !"$(TEAL) $(DEFAULT)

zappy_ai:	titre_ai
			@echo "#!/usr/bin/php" > zappy_ai
			@cat ai/index.php >> zappy_ai
			@chmod +x zappy_ai
			@$(ECHO) $(GREEN)✓$(TEAL)" BUILD SUCCESS !"$(TEAL) $(DEFAULT)

clean:
			@$(ECHO) $(RED)¶ Cleaning$(TEAL):$(DEFAULT)
			@$(ECHO) $(GREEN)  " [OK]" $(TEAL)"Clean obj"$(TEAL)
			$(RM) $(OBJ_SERV) zappy_ai zappy_server
			@($(ECHO) $(GREEN)✓$(TEAL)" CLEAN SUCCESS !"$(TEAL))

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

%.o : %.c
			@gcc -c -o $@ $^ $(CFLAGS) && $(ECHO) -n $(GREEN)"  [OK] "$(TEAL) || $(ECHO) -n $(SANG)"  [NO] "$(TEAL) && $(ECHO) $< | rev | cut -d'/' -f 1 | rev

.PHONY:		all fclean re clean zappy_ai zappy_server