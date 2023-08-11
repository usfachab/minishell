/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertToArray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:25:48 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/11 16:24:37 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

static char	*find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

static char	**splitpath(t_parser_var *var)
{
	char	**splited_path;
	char	*path;

	path = find_path(var->envp);
	if (!path)
		return (NULL);
	splited_path = split(path, ':');
	return (splited_path);
}

void	convert_to_array_help(t_parser_var *var)
{
	if (var->envp)
	{
		free(var->envp);
		var->envp = NULL;
	}
}

void	convert_to_array(t_parser_var *var)
{
	t_list			*envp;
	int				i;

	envp = var->env;
	convert_to_array_help(var);
	var->envp = malloc((ft_lstsize(envp) + 1) * sizeof(char *));
	i = 0;
	while (envp)
	{
		var->envp[i] = envp->content;
		i++;
		envp = envp->next;
	}
	var->envp[i] = NULL;
	i = 0;
	while (var->splited_path && var->splited_path[i])
	{
		free(var->splited_path[i]);
		i++;
	}
	if (var->splited_path)
		free(var->splited_path);
	var->splited_path = splitpath(var);
}
