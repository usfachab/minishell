NAME		=	minishell

CC			=	gcc

#CFALGS		=	-Wall -Wextra -Werror -fsanitize=address -g3

NONE	= \033[0m
YALLOW	= \033[1;93m
Green	= \033[1;32m

IDFLAG		=	-I/goinfre/selrhair/homebrew/opt/readline/include

LDFLAG		=	-L/goinfre/selrhair/homebrew/opt/readline/lib -lreadline

SRC_PAR		=	main.c main.0.1.c reset.c assets/lexer.c assets/parser.0.0.c assets/parser.0.1.c assets/syntax.0.0.c assets/syntax.0.1.c assets/syntax.0.2.c \
				assets/expand.0.0.c assets/expand.0.1.c assets/expand.0.2.c assets/extra.c assets/token.c assets/removeQuote.c \
				helper/find_and_replace.c helper/ft_split.c helper/util.0.0.c helper/util.0.1.c helper/util.0.2.c helper/util.0.3.c \
				helper/util.0.4.c helper/util.0.5.c helper/ft_itoa.c

SRC_EXE		=	execution.0.0.c execution.0.1.c execution.0.2.c srcs/here_doc.c srcs/openFile.c \
				srcs/convertToArray.c build/export.0.0.c build/export.0.1.c  build/export.0.2.c \
				build/cd.c build/echo.c build/exit.c srcs/here_doc_help.c build/pwd.c build/unset.c \
				build/run_builtin.c

PRE_PAR 	=	$(addprefix parssing/, $(SRC_PAR))

PRE_EXE		=	$(addprefix execution/, $(SRC_EXE))

OBJ_PAR		=	$(PRE_PAR:.c=.o)

OBJ_EXE		=	$(PRE_EXE:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ_PAR) $(OBJ_EXE)
	@echo  "$(YALLOW)\n[$@]$(NONE)"
	@$(CC) $(CFALGS) $(IDFLAG) $(LDFLAG) -o $@ $^

%.o : %.c
	@echo "$(Green)Compaling file $<$(NONE)"
	@$(CC) $(CFALGS) -c $< -o $@ $(IDFLAG)

git :
	make fclean && git add . && git commit -m "UPDATE: TESTING" && git push -f origin master

clean :
	@echo "$(Green)Cleaning obj files....$(NONE)"
	@rm -fr $(OBJ_PAR) $(OBJ_EXE)

fclean : clean
	@echo "$(Green)Clean all ....$(NONE)"
	@rm -fr $(OBJ_PAR) $(OBJ_EXE) $(NAME)

re : fclean all