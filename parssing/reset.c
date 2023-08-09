/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 22:33:07 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/09 14:39:11 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/lib.h"

void	restofrest(t_parser_var *var)
{
	free(var->command);
	free(var->file);
	free(var->lexer);
	free(var->token);
	free(var->data);
	if (var->pid)
		free(var->pid);
}

void	reset(t_parser_var *var)
{
	int		i;
	t_file	*file_next;
	t_data	*data_next;

	if (var)
	{
		while (var->data)
		{
			i = -1;
			while (var->data->cmd_args && var->data->cmd_args[++i])
				free(var->data->cmd_args[i]);
			while (var->data && var->data->file)
			{
				if (var->data->last_hdc != 0)
					close(var->data->last_hdc);
				if (var->data->in != 0)
					close(var->data->in);
				if (var->data->out != 1)
					close(var->data->out);
				file_next = var->data->file->next;
				free(var->data->file->file_name);
				free(var->data->file);
				var->data->file = file_next;
			}
			data_next = var->data->next;
			free(var->data->cmd_args);
			free(var->data);
			var->data = data_next;
		}
		restofrest(var);
	}
}
