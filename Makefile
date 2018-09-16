
NAME =		lem-in

SRC_PATH =	src/
LIB_PATH =	libft/
OBJ_PATH =	.obj/

CC =		clang
CFLAGS =	-g #-Wall -Werror -Wextra

INC_PATH =	includes/
IFLAGS =	-I $(LIB_PATH)$(INC_PATH) -I $(INC_PATH)

HFILES =	lem_in
FILES =		lem_in validation algorithm

LIB =	$(LIB_PATH)libftprintf.a

HDRS =	$(addprefix $(INC_PATH), $(addsuffix .h, $(HFILES)))
SRCS =	$(addprefix $(SRC_PATH), $(addsuffix .c, $(FILES)))
OBJS =	$(addprefix $(OBJ_PATH), $(SRCS:%.c=%.o))


all: $(NAME)

$(NAME): $(LIB) $(OBJ_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LIB) -o $(NAME)
$(LIB): 
	make -C $(LIB_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)$(SRC_PATH)
$(OBJ_PATH)%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean: mclean
	make clean -C $(LIB_PATH)
fclean: mfclean
	make fclean -C $(LIB_PATH)
re: fclean all

mclean:
	rm -f $(OBJS) $(DEPS)
mfclean:
	rm -f $(NAME)
	rm -rf $(OBJ_PATH)
mre: mfclean all

.PHONY: all clean fclean re mclean mfclean mre
