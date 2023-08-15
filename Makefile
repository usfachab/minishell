NAME		=	minishell

CC			=	gcc-11

CFALGS		=	-Wall -Wextra -Werror -fcommon #-g3 -fsanitize=address

NONE		=	\033[0m
YALLOW		=	\033[1;93m
Green		=	\033[1;32m
Red			=	\033[0;31m


SRC_PAR		=	main.c main.0.1.c reset.c assets/lexer.c assets/parser.0.0.c assets/parser.0.1.c assets/syntax.0.0.c assets/syntax.0.1.c assets/syntax.0.2.c \
				assets/expand.0.0.c assets/expand.0.1.c assets/expand.0.2.c assets/extra.c assets/token.c assets/removeQuote.c \
				helper/find_and_replace.c helper/ft_split.c helper/util.0.0.c helper/util.0.1.c helper/util.0.2.c helper/util.0.3.c \
				helper/util.0.4.c helper/util.0.5.c helper/ft_itoa.c

SRC_EXE		=	execution.0.0.c execution.0.1.c execution.0.2.c execution.0.3.c srcs/here_doc.c srcs/openFile.c \
				srcs/convertToArray.c srcs/linked_list_utils.c build/export.0.0.c build/export.0.1.c  build/export.0.2.c build/export.0.3.c \
				build/cd.0.0.c build/cd.0.1.c build/echo.c build/exit.0.0.c build/exit.0.1.c srcs/here_doc_help.c build/pwd.c build/unset.0.0.c build/unset.0.1.c \
				build/run_builtin.c

PRE_PAR 	=	$(addprefix parssing/, $(SRC_PAR))

PRE_EXE		=	$(addprefix execution/, $(SRC_EXE))

OBJ_PAR		=	$(PRE_PAR:.c=.o)

OBJ_EXE		=	$(PRE_EXE:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ_PAR) $(OBJ_EXE)
	@$(CC) $(CFALGS) -o $@ $^ -lreadline
	@echo  "$(Green)Compiled success$(NONE)"

%.o : %.c
	@$(CC) $(CFALGS) -c $< -o $@

git : 
	make fclean && git add . && git commit -m "FINAL VERSION" && git push -f origin master

clean :
	@echo "$(YALLOW)Cleaning$(NONE)"
	@rm -fr $(OBJ_PAR) $(OBJ_EXE)

fclean : clean
	@echo "$(Red)Fcleaning$(NONE)"
	@rm -fr $(OBJ_PAR) $(OBJ_EXE) $(NAME)

re : fclean all