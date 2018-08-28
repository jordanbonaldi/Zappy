##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

PROJECT = project/

ZAPPY_AI = ai/

ZAPPY_GRAPHIC = graphic/

ZAPPY_SERVER = $(PROJECT)server/

ZAPPY_CONTROLLER = controller/

all:
	make -C $(ZAPPY_AI)
	make -C $(ZAPPY_SERVER)
	make -C $(ZAPPY_GRAPHIC)
	make -C $(ZAPPY_CONTROLLER)

controller:
	make -C $(ZAPPY_CONTROLLER)

graphic:
	make -C $(ZAPPY_GRAPHIC)

server:
	make re -C $(ZAPPY_SERVER)

ai:
	make -C $(ZAPPY_AI)

re_controller:
	make re -C $(ZAPPY_CONTROLLER)

re_graphic:
	make re -C $(ZAPPY_GRAPHIC)

re_server:
	make re -C $(ZAPPY_SERVER)

re_ai:
	make re -C $(ZAPPY_AI)

clean:
	make clean -C $(ZAPPY_SERVER)
	make clean -C $(ZAPPY_AI)
	make clean -C $(ZAPPY_GRAPHIC)
	make clean -C $(ZAPPY_CONTROLLER)

fclean:
	make fclean -C $(ZAPPY_SERVER)
	make fclean -C $(ZAPPY_AI)
	make fclean -C $(ZAPPY_GRAPHIC)
	make fclean -C $(ZAPPY_CONTROLLER)

re:
	make re -C $(ZAPPY_AI)
	make re -C $(ZAPPY_SERVER)
	make re -C $(ZAPPY_GRAPHIC)
	make re -C $(ZAPPY_CONTROLLER)

.PHONY: all clean fclean re controller graphic ai server re_controller re_graphic re_ai re_server
