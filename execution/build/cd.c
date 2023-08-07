/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:54:44 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/01 16:33:40 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	ft_store_pwd(t_parser_var *var)
{
	t_list	*tmp;

	tmp = var->env;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (ft_strnstr(tmp->content, "PWD=", 4))
		{
			free(tmp->content);
			free(tmp->next->content);
			tmp->content = ft_strjoin("PWD=", g_glob.pwd);
			tmp->next->content = ft_strjoin("OLDPWD=", g_glob.oldpwd);
		}
		tmp = tmp->next;
	}
}

int	is_not_dir(char *name)
{
	struct stat	file_stat;

	if (!access(name, F_OK))
	{
		if (stat(name, &file_stat) == 0)
		{
			if (!S_ISDIR(file_stat.st_mode))
			{
				write(2, "minishell: ", 11);
				write(2, name, ft_strlen(name));
				write(2, ": not a directory\n", 19);
				g_glob.exit_status = 1;
				return (0);
			}
		}
	}
	return (1);
}

int	ft_cd_help_1(t_list *tmp)
{
	while (tmp)
	{
		if (ft_strnstr(tmp->content, "HOME=", 5))
		{
			chdir(tmp->content + 5);
			if (g_glob.pwd)
				free(g_glob.pwd);
			g_glob.pwd = getcwd(NULL, 0);
			return (0);
		}
		tmp = tmp->next;
	}
	write (2, "cd: HOME not set\n", 17);
	g_glob.exit_status = 1;
	return (1);
}

int	ft_cd_help_2(t_parser_var *var)
{
	if (!is_not_dir(var->data->cmd_args[1]))
		return (1);
	if (access(var->data->cmd_args[1], F_OK)
		|| access(var->data->cmd_args[1], R_OK)
		|| access(var->data->cmd_args[1], X_OK))
	{
		write (2, "minishell: cd: ", 15);
		perror(var->data->cmd_args[1]);
		g_glob.exit_status = 1;
		return (1);
	}
	else if (var->data->cmd_args[1])
	{
		chdir(var->data->cmd_args[1]);
		if (g_glob.pwd)
			free(g_glob.pwd);
		g_glob.pwd = getcwd(NULL, 0);
		if (g_glob.pwd)
			g_glob.pwd_helper = g_glob.pwd;
	}
	return (0);
}

int	ft_cd(t_parser_var *var)
{
	t_list	*tmp;

	tmp = var->env;
	if (g_glob.oldpwd)
		free(g_glob.oldpwd);
	g_glob.oldpwd = getcwd(NULL, 0);
	if (!var->data->cmd_args[1] || var->data->cmd_args[1][0] == '~')
		return (ft_cd_help_1(tmp));
	else
	{
		if (ft_cd_help_2(var))
			return (1);
		if (g_glob.pwd == NULL && g_glob.oldpwd == NULL)
		{
			write (2, "cd: error retrieving current directory: getcwd:", 47);
			write (2, " cannot access parent directories: ", 35);
			write (2, "No such file or directory\n", 26);
			g_glob.exit_status = 0;
			return (1);
		}
	}
	ft_store_pwd(var);
	return (0);
}
