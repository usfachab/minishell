/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:11:11 by yachaab           #+#    #+#             */
/*   Updated: 2023/06/03 17:11:11 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H
# include <sys/stat.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <ctype.h>
# include <stdbool.h>
# include <fcntl.h>
# include <limits.h>
# include <wait.h>
# include "parser.h"

/* ----------------------------- parser  --------------------------------*/
t_parser_var	*parser(char *input, t_parser_var	*var);
/* ----------------------------- parserExtra  ---------------------------*/
char			*skip_white_space(char *input);
void			save_file(t_parser_var	*var);
void			save_heredoc(t_parser_var *var);
/* ----------------------------- src folder -----------------------------*/
void			find_char_and_replace_with_unprintable(char *str);
void			find_unprintable_and_replace_with_char(char *str);
void			find_unprintable_replace_space(char **str);
t_data			*ft_lstnew_node(char **command, t_file *files);
t_file			*ft_lstnew_subnode(char *content, int type);
void			ft_lstadd_back_node(t_data **lst, t_data *new);
void			ft_lstadd_back_subnode(t_file **lst, t_file *new);
char			*_join(char *path, char *cmd);
char			**split(char *str, char *del);
/* ---------------------------- lexer -----------------------------------*/
t_lexer			*init_lexer(char *content);
char			*lexer_collect_string(t_lexer *lexer);
char			*lexer_collect_file_name(t_lexer *lexer);
void			lexer_advence(t_lexer *lexer);
void			lexer_skip_white_space(t_lexer *lexer);
/* ---------------------------- token -----------------------------------*/
t_token			*lexer_get_next_token(t_lexer *lexer);
t_token			*lexer_collect_identifier(t_lexer *lexer);
t_token			*lexer_advence_with_token(t_lexer *lexer, t_token *token);
t_token			*init_token(int type, char *value);
/* ---------------------------- expand ----------------------------------*/
char			*expand(char *input, char **env, int doc);
int				variable_contain_white_space(char *variable);
char			*_getenv(char *buffer, char **env);
int				end_del(char ch);
int				stay(char ch);
int				start_del_ex(char ch);
char			*re_alloc(char *input, char c, int len);
char			*collect_name(char *end);
char			*_bufferin(char *input);
char			*bufferin(char *input);
/* ---------------------------- syntax ----------------------------------*/
void			*syntax_err(char *input);
void			*redirection_error(char *input);
void			*unclosed_quote(char *input);
char			*skip_white_space(char *input);
void			*white_space_only(char *input);
/* ---------------------------- extra -----------------------------------*/
int				_white_space(char c);
int				is_special_character(char ch);
int				variable_contain_white_space(char *variable);
char			*add_quote_to_variable(char *value);
void			lexer_skip_white_space(t_lexer *lexer);
/* ---------------------------- nodeListExtra ---------------------------*/
void			*ft_lstlast_subnode(t_file *lst);
void			*ft_lstlast_node(t_data *lst);
/* ---------------------------- ExitStat --------------------------------*/
void			reset(t_parser_var *var);
/* ---------------------------- SkipQuote -------------------------------*/
char			*remove_quote(char *value);
/* ---------------------------- EnvVariables ----------------------------*/
void			init_var_with_env_variable(char **env);
/* ---------------------------- Execution -------------------------------*/
void			execution(t_parser_var *var);
/* ---------------------------- libft -----------------------------------*/
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s1);
void			*ft_memmove(void *dst, const void *src, size_t len);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
/*----------------------------- signal handle ---------------------------*/
void			sighandler(int sig);
/*------------------------ convert and split path -----------------------*/
void			convert_to_array(void);
char			*_join_path(char *path, char *cmd);
/*-------------------------------- Helper -------------------------------*/
t_list			*ft_lstnew(char *content);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_env(t_list *env);
int				ft_lstsize(t_list *lst);
t_list			*ft_fill_list(char **line);
int				ft_strncmp_2(char *s1, char *s2);
char			*ft_strjoin(char const *s1, char const *s2);
void			internal_error_msg(char *str, unsigned int err);
void			external_error_msg(char *str, unsigned int err);
void			ft_help_1(char *arg, t_list *env, t_parser_var *var);
void			ft_help_2(char *arg, t_list *env, t_parser_var *var);
int				is_limiter(char *str, char *arg);
void			disable_echo_int(void);
char			*ft_itoa(int n);
char			*skip_white_space(char *input);
#endif