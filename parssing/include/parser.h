/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:17:03 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/12 17:26:57 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct FILE_STRUCT
{
	char					*file_name;
	int						type;
	struct FILE_STRUCT		*next;
}	t_file;

typedef struct DATA_STRUCT
{
	char					**cmd_args;
	t_file					*file;
	t_file					*last_in;
	t_file					*last_out;
	int						in;
	int						out;
	int						prev;
	int						unopened_file;
	int						last_hdc;
	int						ambiguous;
	struct DATA_STRUCT		*next;
}	t_data;

typedef struct LEXER_STRUCT
{
	char			c;
	unsigned int	i;
	char			*content;
}	t_lexer;

typedef struct TOKEN_STRUCT
{
	enum
	{
		TOKEN_STRING,
		TOKEN_PIPE,
		TOKEN_INFILE,
		TOKEN_OUTFILE,
		TOKEN_APPAND,
		TOKEN_HDC,
		TOKEN_HDCX,
		TOKEN_AMBIGOUS
	} e_type;
	char	*value;
}	t_token;

typedef struct SKIP_QUOTE_STRUCT
{
	char	*string;
	char	*tmp;
	int		len;
	char	quote;
	int		num_of_quote;
}	t_skip_quote;

typedef struct PARSER_VARIABLES
{
	char			**_command;
	t_data			*data;
	t_lexer			*lexer;
	t_token			*token;
	t_file			*file;
	char			*command;
	t_skip_quote	*skip;
	int				fd[2];
	int				flag;
	pid_t			*pid;
	int				list_size;
	int				size;
	t_list			*altered_node;
	char			*first;
	char			*variable;
	char			*equal;
	char			*last;
	char			*last_saved;
	char			*tmp;
}	t_parser_var;

typedef struct s_expand
{
	char	*string;
	char	*buffer;
	char	*variable;
	int		i;
	int		j;
	int		len;
	char	s;
	char	d;
}	t_expand;

typedef struct s_glob
{
	char	**splited_path;
	char	**envp;
	t_list	*env;
	int		interapt_main_signal;
	int		exit_status;
	int		ambiguous;
}	t_glob;
t_glob	g_glob;
#endif
