/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:52:46 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/05 12:44:14 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char
	*parse_token(char **str, char *dir_addr)
{
	int		len;
	char	*token;
	char	*right_token;

	len = -1;
	while ((*str)[++len] && !ft_strchr(STOP_SYMBOLS, (*str)[len]))
	{
		if ((*str)[len] == '~' && (!len || (*str)[len - 1] == ' '))
			break ;
	}
	token = ft_substr(*str, 0, len);
	right_token = 0;
	(*str) += len;
	if (**str && ft_strchr(SPEC_SYMBOLS, **str))
	{
		if (**str == QUOTE || **str == DQUOTE)
			right_token = treat_quotes(str, **str, dir_addr);
		else if (**str == BACKSLASH)
			right_token = treat_backslash(str, 0, dir_addr);
		else
			right_token = treat_tilda(str, dir_addr);
		token = ft_ownrealloc(&ft_strjoin, &token, right_token);
		free(right_token);
	}
	return (token);
}

static char
	*add_redirect(char **str)
{
	char	*token;

	if ((*str)[1] == GREAT)
	{
		token = ft_substr(*str, 0, 2);
		*str += 2;
	}
	else
		token = ft_substr((*str)++, 0, 1);
	return (token);
}

int
	add_token(t_cmd *cmd, char *token, t_bool is_redirect)
{
	t_bool	error;

	error = FALSE;
	if (is_redirect)
	{
		if (check_redirect(token, &(cmd->add_fd)))
			return (TRUE);
	}
	else if (!cmd->add_fd)
	{
		if (!add_fdin(cmd, token))
			error = TRUE;
	}
	else if (cmd->add_fd == 1 || cmd->add_fd == 2)
	{
		if (!add_fdout(cmd, token))
			error = TRUE;
	}
	else
		cmd->args = ft_wordtab_realloc(cmd->args, token);
	free(token);
	*token = 0;
	return (error);
}

t_cmd
	*parse_cmd(char *str, char *dir_addr)
{
	char	*token;
	t_bool	is_redirect;
	t_cmd	*cmd;

	cmd = init_cmd();
	while (*str && *str != DIEZ)
	{
		token = 0;
		skip_spaces(&str, SPACES);
		if ((*str == GREAT || *str == LOW) && (is_redirect = TRUE))
			token = add_redirect(&str);
		else if (*str && !(is_redirect = FALSE))
			token = parse_token(&str, dir_addr);
		if (token && add_token(cmd, token, is_redirect))
			return (cmd_clear(cmd));
	}
	if (is_redirect)
	{
		error_parse(PARSE_ERROR, 0);
		return (cmd_clear(cmd));
	}
	return (cmd);
}

t_cmd
	*parser(char *str, t_list *envlst, char *dir_addr)
{
	t_cmd	*cmd;
	char	*tmp;
	int		quote;

	quote = 0;
	tmp = parse_vars(str, envlst, &quote);
	cmd = parse_cmd(tmp, dir_addr);
	free(tmp);
	return (cmd);
}
