# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmuravch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/25 12:07:56 by hmuravch          #+#    #+#              #
#    Updated: 2018/10/25 13:18:22 by hmuravch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		lem-in

DEF =		\x1b[0m
GRN =		\x1b[32m
YLW =		\x1b[33m
RED =		\x1b[31m

SRC_PATH =	src/
LIB_PATH =	libft/
OBJ_PATH =	.obj/

CC =		clang
CFLAGS =	-Wall -Werror -Wextra

INC_PATH =	includes/
IFLAGS =	-I $(LIB_PATH)$(INC_PATH) -I $(INC_PATH)

HFILES =	lem_in
FILES =		lem_in reading fill_links algorithm fill_len find_way helper

LIB =		$(LIB_PATH)libftprintf.a

HDRS =		$(addprefix $(INC_PATH), $(addsuffix .h, $(HFILES)))
SRCS =		$(addprefix $(SRC_PATH), $(addsuffix .c, $(FILES)))
OBJS =		$(addprefix $(OBJ_PATH), $(SRCS:%.c=%.o))


all: $(NAME)

$(NAME): $(LIB) $(OBJ_PATH) $(OBJS)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LIB) -o $(NAME)
	@echo "$(GRN)Lem-in is ready$(DEF)"
$(LIB): 
	@make -C $(LIB_PATH)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)$(SRC_PATH)
	@echo "$(YLW)Directory for objects was created$(DEF)"
$(OBJ_PATH)%.o: %.c $(HDRS)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@echo "$(YLW)$(subst $(OBJ_PATH)$(SRC_PATH),,$@) was created$(DEF)"

clean: mclean
	@make clean -C $(LIB_PATH)
fclean: mfclean
	@make fclean -C $(LIB_PATH)
re: fclean all

mclean:
	@rm -f $(OBJS) $(DEPS)
	@echo "$(RED)Objects were deleted$(DEF)"
mfclean:
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)	
	@echo "$(RED)Directory with objects was deleted$(DEF)"
	@echo "$(RED)Lem-in was deleted$(DEF)"
mre: mfclean all

.PHONY: all clean fclean re mclean mfclean mre
