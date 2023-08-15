/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.0.0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:54:44 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/15 15:50:09 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	set_pwd_and_oldpwd(char *oldpwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd && !oldpwd)
	{
		write (2, "cd: error retrieving current directory: getcwd:", 47);
		write (2, " cannot access parent directories: ", 35);
		write (2, "No such file or directory\n", 26);
		g_glob.exit_status = 0;
		return ;
	}
	set_pwd("PWD", pwd);
	set_pwd("OLDPWD", oldpwd);
	free(pwd);
}

void	go_dir(char *arg, char *oldpwd)
{
	if (!chdir(arg))
		set_pwd_and_oldpwd(oldpwd);
	else
	{
		if (errno == 116)
			errno = 2;
		perror("minishell: cd: ");
		g_glob.exit_status = 1;
	}
}

void	go_home(char *oldpwd)
{
	char	*home_path;

	home_path = node_content(g_glob.env, "HOME");
	if (home_path && ft_strlen(home_path) >= 5)
	{
		if (!home_path[5])
			return ;
		if (!chdir(home_path + 5))
			set_pwd_and_oldpwd(oldpwd);
		else
		{
			perror("minishell: cd: ");
			g_glob.exit_status = 1;
		}
	}
	else
	{
		write (2, "cd: HOME not set\n", 17);
		g_glob.exit_status = 1;
	}
}

int	_cd(char **arg)
{
	char	*oldpwd;

	if (arg[1] && arg[2])
	{
		write(2, "minishell: cd: ", 16);
		write(2, "too many arguments\n", 20);
		g_glob.exit_status = 1;
		return (0);
	}
	oldpwd = getcwd(NULL, 0);
	if ((!arg[1] || arg[1][0] == '~'))
		go_home(oldpwd);
	else
		go_dir(*(arg + 1), oldpwd);
	free(oldpwd);
	convert_to_array();
	return (0);
}
