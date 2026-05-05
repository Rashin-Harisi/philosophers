NAME 			:= philo
HEADER			:= philo.h 

COMMON_SRC		:= utils.c \
				destroy_mutexes.c \
				initial.c \
				philo_initial.c \
				threads.c \
				mutexes.c \
				routine.c \
				validation.c
				
MANDATORY_SRC	:= philo.c 

COMMON_OBJ		:= $(COMMON_SRC:.c=.o)
MANDATORY_OBJ	:= $(MANDATORY_SRC:.c=.o)


CC 				:= cc 
CFLAGS			:= -Wall -Wextra -Werror -g 

all	: $(NAME)
$(NAME) : $(MANDATORY_OBJ) $(COMMON_OBJ)
	$(CC) $(CFLAGS) $(MANDATORY_OBJ) $(COMMON_OBJ) -o $(NAME)
	@echo "Mandatory part is build."

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJ) $(COMMON_OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re