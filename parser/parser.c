/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:52:46 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/31 15:47:16 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd
	*init_cmd()
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = ft_calloc(sizeof(char *), 1);
	(cmd->args)[0] = 0;
	cmd->fdin = 0;
	cmd->fdout = 0;
	cmd->add_fd = -1;

	return (cmd);
}

static int
	add_fdin(t_cmd *cmd, char *token)
{
	if (cmd->fdin)
		close(cmd->fdin);
	if ((cmd->fdin = open(token, O_CREAT | O_RDONLY)) < 0)
	{
		g_error = errno;
		file_error(strerror(errno));
		return (0);
	}
	cmd->add_fd = -1;
	return (1);
}

static int
	add_fdout(t_cmd *cmd, char *token)
{
	if (cmd->fdout)
		close(cmd->fdout);
	if (cmd->add_fd == 1)
	{
		cmd->fdout = open(token, O_CREAT | O_WRONLY | O_TRUNC |O_APPEND);
		if (cmd->fdout < 0)
		{
			g_error = errno;
			file_error(strerror(errno));
			return (0);
		}
		cmd->add_fd = -1;
		return (1);
	}
	if ((cmd->fdout = open(token, O_CREAT | O_WRONLY |O_APPEND)) < 0)
	{
		g_error = errno;
		file_error(strerror(errno));
		return (0);
	}
	cmd->add_fd = -1;
	return (1);
}

static int
	add_token(t_cmd *cmd, char *token, t_bool is_redirect)
{
	t_bool	error;

	error = FALSE;
	if (is_redirect)
	{
		if (cmd->add_fd != -1)
		{
			error_parse(PARSE_ERROR, token[0]);
			return (TRUE);
		}
		if (token[0] == LOW)
			cmd->add_fd = 0;
		if (token[0] == GREAT && !token[1])
			cmd->add_fd = 1;
		else if (token[0] == GREAT)
			cmd->add_fd = 2;
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

static char
	*treat_backslash(char **str, int quote, t_list *envlst)
{
	char	*left_token;
	char	*right_token;
	char	*token;

	(*str)++;
	if (!**str)
		return (ft_calloc(sizeof(char), 1));
	left_token = ft_strldup(*str, 2);
	(*str)++;
	if (quote)
	{
		(*str)--;
		right_token = treat_quotes(str, quote, envlst);
	}
	else if (**str)
		right_token = parse_token(str, envlst);
	else
		right_token = ft_calloc(sizeof(char), 1);
	token = ft_strjoin(left_token, right_token);
	free(left_token);
	free(right_token);
	return(token);
}

static char
	*get_dollar_var(char **str, t_list *envlst)
{
	int		len;
	char	*token;


	if (**str == '?')
	{
		(*str)++;
		return (ft_itoa(g_error));
	}
	len = 0;
	if ((*str)[1] == '_' || ft_isalpha((*str)[1]))
		len++;
	if (!len)
		token = ft_strdup("$");
	else
	{
		while(ft_isalnum((*str)[len]) || (*str)[len] == '_')
			len++;
		token = ft_strldup(*str, len + 1);
	}
	(*str) += len;
	return(ft_getenv(token, envlst));
}

char
	*treat_dollar(char **str, int quote, t_list *envlst)
{
	char	*left_token;
	char	*right_token;
	char	*token;

	(*str)++;
	left_token = get_dollar_var(str, envlst);
	if (quote)
	{
		(*str)--;
		right_token = treat_quotes(str, quote, envlst);
	}
	else if (**str)
		right_token = parse_token(str, envlst);
	else
		right_token = ft_calloc(sizeof(char), 1);
	token = ft_strjoin(left_token, right_token);
	free(left_token);
	free(right_token);
	return(token);
}

/*
** @params: char **str обрабатываемая строка
** 			int quote тип кавычек
** TODO: обрабатывает аргумент с кавычками в строке
** и сдивагет строку на следующую лексему
** @return char *token полученный аргумент
*/
char
	*treat_quotes(char **str, int quote, t_list *envlst)
{
	size_t	len;
	char	*left_token;
	char	*token;
	char	*stop_symbols;

	(*str)++;
	if (quote == QUOTE)
		stop_symbols = "'";
	else
		stop_symbols = "\\\"$";
	len = 0;
	while ((*str)[len] && !ft_strchr(stop_symbols, (*str)[len]))
		len++;
	left_token = ft_strldup(*str, len + 1);
	*str += len;
	if (**str == BACKSLASH)
		token = ft_strjoin(left_token, treat_backslash(str, quote, envlst));
	else if (**str == DOLLAR)
		token = ft_strjoin(left_token, treat_dollar(str, quote, envlst));
	else if (*(*str)++)
		token = ft_strjoin(left_token, parse_token(str, envlst));
	else
		token = ft_calloc(sizeof(char), 1);
	free(left_token);
	return (token);
}


char
	*parse_token(char **str, t_list *envlst)
{
	size_t	len;
	char	*token;
	char	*left_token;

	len = 0;
	while ((*str)[len] && !ft_strchr(STOP_SYMBOLS, (*str)[len]))
		len++;
	left_token = ft_strldup(*str, len + 1);
	(*str) += len;

	if (**str == QUOTE || **str == DQUOTE)
		token = ft_strjoin(left_token, treat_quotes(str, **str, envlst));
	else if (**str == BACKSLASH)
		token = ft_strjoin(left_token, treat_backslash(str, 0, envlst));
	else if (**str == DOLLAR)
		token = ft_strjoin(left_token, treat_dollar(str, 0, envlst));
	else
		token = ft_strdup(left_token);
	free(left_token);
	return (token);
}

/*
** @params: char **str, t_list **tokens
** TODO: записывает в новую строку редирект
**	и сдивагет строку на следующую лексему
** @return char* : строка редирект
*/
static char
	*add_redirect(char **str)
{
	char	*token;

	if ((*str)[1] == GREAT)
	{
		token = ft_strldup(*str, 3);
		*str += 2;
	}
	else
		token = ft_strldup((*str)++, 2);
	
	return (token);
}

t_cmd
	*parser(char *str, t_list *envlst)
{
	t_cmd	*cmd;
	char	*token;
	t_bool	is_redirect;

	cmd = init_cmd();
	while (*str && *str != DIEZ)
	{
		while (*str && ft_strchr(SPACES, *str))
			str++;
		if (*str == GREAT || *str == LOW)
		{
			token = add_redirect(&str);
			is_redirect = TRUE;
		}
		else if (*str)
		{
			token = parse_token(&str, envlst);
			is_redirect = FALSE;
		}
		if (*token)
			if (add_token(cmd, token, is_redirect))
				return (cmd_clear(cmd));
	}
	return (cmd);
}