
ASM				:= nasm -f elf64

SRC				:=	ft_calloc.s 			\
					ft_read.s				\
					ft_strcmp.s 			\
					ft_strcpy.s				\
					ft_strdup.s 			\
					ft_strlen.s				\
					ft_write.s	

SRC_BONUS		:=	ft_list_push_front.s	\
					ft_list_remove_if.s		\
					ft_list_size.s			\
					ft_list_sort.s

SRC_MISC		:= 	ft_exit.s

SOURCES			:= $(SRC)
SOURCES_BONUS	:= $(SRC_BONUS) $(SRC_MISC)

NAME			:= libasm.a
TEST_NAME		:= libasm_tester
BONUS_DONE		:= .bonus	# Prevent bonus relink

OBJ				 = $(addprefix $(OBJ_DIR)/,$(SOURCES:%.s=%.o))
OBJ_BONUS		 = $(addprefix $(OBJ_DIR)/,$(SOURCES_BONUS:%.s=%.o))
OBJ_DIR			:= obj


all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.s
	@mkdir -p $(@D)
	@$(ASM) $< -o $@

bonus: $(BONUS_DONE)

$(BONUS_DONE): $(OBJ) $(OBJ_BONUS)
	@ar -rcs $(NAME) $(OBJ) $(OBJ_BONUS)
	@touch $(BONUS_DONE)

test: $(TEST_NAME)

$(TEST_NAME): $(NAME) $(BONUS_DONE) main.c
	@cc main.c -L. -lasm -o $(TEST_NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME) $(TEST_NAME)
	@rm -rf $(BONUS_DONE)

flcean: fclean

re: fclean all

rebuild: re

.PHONY: all bonus clean fclean re test

