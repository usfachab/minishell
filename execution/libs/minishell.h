/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:54:44 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/09 15:31:47 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../../parssing/include/lib.h"

char	*join_with_path(char **splited_path, t_data *data, char *str);
void	_dupping(t_data *data, int *fd);
void	parent_closing_pipe_part(t_data *data, int *fd);
int		count_data(t_parser_var *var);
void	wait__signal(t_parser_var *var, int stat);
void	_pwd(t_list *env);
void	_echo(char **cmd);
void	ft_unset(t_parser_var *var);
int		ft_cd(t_parser_var *var, t_data *data, int flag);
int		ft_exit(t_data *data);
bool	heredoc(t_parser_var *var);
int		open_file_loop(t_data *data);
void	save_last_in_out(t_parser_var *var);
int		run_builtin(t_data *data, t_parser_var *var);
void	_export(t_parser_var *var);
int		alphaunder(char c);
int		alphanumunder(char *cmd);
t_list	*check_for_variable_existance(char *var_name, t_list *env);
void	handling_solo_variable(char *cmd, t_list *env);
void	execute(t_parser_var *var, t_data *data, int *fd);
long	ft_atoi(char *str);
void	ft_print_exit_err(char *str);

#endif