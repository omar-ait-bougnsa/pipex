
name = pipex
BNS = pipex_bonus
CC = cc -ggdb 
FLAGS = -Wall -Wextra -Werror 
SRC = pipex.c pipex_utilis.c ft_split.c check_path.c ft_strjoin.c
BSRC = pipex_bonus.c pipex_utilis.c  ft_split.c check_path.c pipex_utilis_bon.c ft_strjoin.c
BOBG = $(BSRC:.c=.o)
OBG = $(SRC:.c=.o)

all: $(name)

$(name) : $(OBG)
	$(CC) $(FLAGS) $(OBG) -o $(name) 
bonus: $(BNS)

$(BNS) : $(BOBG)
	$(CC) $(FLAGS) $(BOBG) -o $(BNS) 
%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@
clean : 
	rm -f $(OBG) $(BOBG)
fclean : clean
	rm -f $(name) $(BNS)

re : fclean all
