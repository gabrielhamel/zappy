##
## EPITECH PROJECT, 2019
## PSU_zappy_2018
## File description:
## Makefile
##


SRC_SERV =	./server/src/sockets/client.c				\
			./server/src/sockets/list_close.c			\
			./server/src/sockets/list_event.c			\
			./server/src/sockets/list_utils.c			\
			./server/src/sockets/server.c				\
			./server/src/game/link_map.c				\
			./server/src/game/random.c					\
			./server/src/game/map.c						\
			./server/src/loop.c							\
			./server/src/main.c							\
			./server/src/events.c						\
			./server/src/execution.c					\
			./server/src/utils/array.c					\
			./server/src/utils/ioutils.c				\
			./server/src/utils/read.c					\
			./server/src/utils/strings.c				\
			./server/src/fct_cli.c						\
			./server/src/parsing/checking.c				\
			./server/src/parsing/team_name.c			\
			./server/src/parsing/arguments.c			\
			./server/src/parsing/types.c				\
			./server/src/commands/buffer_cmd/list_fct.c \
			./server/src/commands/graphic/list.c 		\
			./server/src/commands/graphic/get_player_by_id.c	\
			./server/src/commands/graphic/msz.c			\
			./server/src/commands/graphic/bct.c			\
			./server/src/commands/graphic/pin.c			\
			./server/src/commands/graphic/mct.c			\
			./server/src/commands/graphic/tna.c			\
			./server/src/commands/graphic/ppo.c			\
			./server/src/commands/graphic/plv.c			\
			./server/src/commands/graphic/sgt.c			\
			./server/src/commands/graphic/sst.c			\
			./server/src/commands/graphic/send_all.c	\
			./server/src/commands/ai/list.c 			\
			./server/src/commands/ai/fork.c				\
			./server/src/commands/ai/forward.c			\
			./server/src/commands/ai/broadcast.c		\
			./server/src/commands/ai/eject.c			\
			./server/src/commands/ai/inventory.c		\
			./server/src/commands/ai/left.c				\
			./server/src/commands/ai/right.c			\
			./server/src/commands/ai/settake_parser.c	\
			./server/src/commands/ai/set.c				\
			./server/src/commands/ai/take.c				\
			./server/src/commands/ai/connect_nbr.c		\
			./server/src/teams/check_team_names.c		\
			./server/src/game/const_dest_game.c			\
			./server/src/game/direction.c				\
			./server/src/time_manage.c

SRC_AI =	./ai/src/Main.cpp							\
			./ai/src/Server.cpp							\
			./ai/src/Client.cpp							\
			./ai/src/Application.cpp					\
			./ai/src/Parser.cpp							\
			./ai/src/Utils.cpp							\
			./ai/src/Inventory.cpp						\
			./ai/src/Message.cpp						\
			./ai/src/Ia.cpp

INC_DIR =	-I ./server/include \
			-I ./ai/include

OBJ_SERV =  $(SRC_SERV:.c=.o)

OBJ_AI =  	$(SRC_AI:.cpp=.o)

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

zappy_ai:	titre_ai $(OBJ_AI)
			@g++ -o zappy_ai $(OBJ_AI) && $(ECHO) $(GREEN)✓$(TEAL)" BUILD SUCCESS !"$(TEAL) $(DEFAULT) || $(ECHO) $(SANG)✗$(TEAL)" BUILD FAILED !"$(TEAL) $(DEFAULT)

clean:
			@$(ECHO) $(RED)¶ Cleaning$(TEAL):$(DEFAULT)
			@$(ECHO) $(GREEN)  " [OK]" $(TEAL)"Clean obj"$(TEAL)
			$(RM) $(OBJ_SERV) $(OBJ_AI)
			@($(ECHO) $(GREEN)✓$(TEAL)" CLEAN SUCCESS !"$(TEAL))

fclean:		clean
			$(RM) zappy_ai zappy_server

re:			fclean all

%.o : %.c
			@gcc -c -o $@ $^ $(CFLAGS) && $(ECHO) -n $(GREEN)"  [OK] "$(TEAL) || $(ECHO) -n $(SANG)"  [NO] "$(TEAL) && $(ECHO) $< | rev | cut -d'/' -f 1 | rev

%.o : %.cpp
			@g++ -c -o $@ $^ $(CFLAGS) && $(ECHO) -n $(GREEN)"  [OK] "$(TEAL) || $(ECHO) -n $(SANG)"  [NO] "$(TEAL) && $(ECHO) $< | rev | cut -d'/' -f 1 | rev

.PHONY:		all fclean re clean zappy_ai zappy_server
