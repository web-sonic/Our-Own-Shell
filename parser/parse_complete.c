/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_complete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:52:46 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/25 16:09:04 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	init_cmd(t_cmd  *cmd)
{
	cmd->args = malloc(sizeof(char *));
	(cmd->args)[0] = ft_calloc(sizeof(char), 1);
	cmd->fderr = 0;
	cmd->fdin = 0;
	cmd->fdout = 0;
}

static void
	add_newarg(char **args, size_t s_len, char **str)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = args;
	args = malloc(sizeof(char *) * (ft_wordtab_count(args) + 2));
	while (tmp[++i])
		args[i] = tmp[i];
	args[i] = ft_strldup(*str, s_len + 1);
	args[i + 1] = 0;
	ft_wordtab_clear(tmp);
	*str += s_len;
}

static void
	treat_stopsymbol(t_cmd *cmd, char **str)
{
	
}

t_cmd
	parse_complete(char *str, char **env)
{
	t_list
	size_t  len;

	init_cmd(&cmd);
	while (*str || *str != DIEZ)
	{
		len = 0;
		while (ft_strchr(SPACES, *str))
			str++;
		while (!ft_strchr(STOP_SYMBOLS, str[len]))
		{
			if (str[len] == '2' && str[len + 1] == GREAT)
				break;
			len++;
		}
		if (len)
			add_newarg(cmd.args, len, &str);
		treat_stopsymbol(&cmd, &str);
	}
	return (cmd);
}