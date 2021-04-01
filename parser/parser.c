/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:52:46 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/01 17:55:15 by yu               ###   ########.fr       */
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
	cmd->fdin = -1;
	cmd->fdout = -1;
	cmd->add_fd = -1;
	cmd->is_fdin = FALSE;
	cmd->is_fdin = FALSE;
	return (cmd);
}

static int
	add_fdin(t_cmd *cmd, char *token)
{
	if (cmd->is_fdin)
		close(cmd->fdin);
	if ((cmd->fdin = open(token, O_CREAT | O_RDONLY, S_IRWXU)) < 0)
	{
		g_error = errno;
		file_error(token, strerror(errno));
		return (0);
	}
	cmd->is_fdin = TRUE;
	cmd->add_fd = -1;
	return (1);
}

static int
	add_fdout(t_cmd *cmd, char *token)
{
	if (cmd->is_fdout)
		close(cmd->fdout);
	if (cmd->add_fd == 1)
	{
		cmd->fdout = open(token, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, S_IRWXU);
		if (cmd->fdout < 0)
		{
			g_error = errno;
			file_error(token, strerror(errno));
			return (0);
		}
		cmd->is_fdout = TRUE;
		cmd->add_fd = -1;
		return (1);
	}
	if ((cmd->fdout = open(token, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU)) < 0)
	{
		g_error = errno;
		file_error(token, strerror(errno));
		return (0);
	}
	cmd->is_fdout = TRUE;
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
	//free(token);
	*token = 0;
	return (error);
}

static char
	*treat_backslash(char **str, int quote, t_list *envlst, char *dir_addr)
{
	char	*left_token;
	char	*right_token;
	char	*token;

	(*str)++;
	if (!**str)
		return (ft_calloc(sizeof(char), 1));
	left_token = ft_substr(*str, 0, 1);
	(*str)++;
	if (quote)
	{
		(*str)--;
		right_token = treat_quotes(str, quote, envlst, dir_addr);
	}
	else if (**str)
		right_token = parse_token(str, envlst, dir_addr);
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

	(*str)++;
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
		token = ft_substr(*str, 0, len);
	}
	(*str) += len;
	return(ft_getenv(token, envlst));
}

static char
	*get_tilda_var(char **str, char *dir_addr)
{
	char	*token;

	(*str)++;
	if (!(**str))
		token = ft_strdup(dir_addr);
	else if ((**str) == '/')
		token = ft_strdup(dir_addr);
	else
		token = ft_strdup("~");
	return(token);
}

char
	*treat_dollar(char **str, int quote, t_list *envlst, char *dir_addr)
{
	char	*left_token;
	char	*right_token;
	char	*token;


	if (**str == DOLLAR)
		left_token = get_dollar_var(str, envlst);
	else
		left_token = get_tilda_var(str, dir_addr);
	if (quote)
	{
		(*str)--;
		right_token = treat_quotes(str, quote, envlst, dir_addr);
	}
	else if (**str)
		right_token = parse_token(str, envlst, dir_addr);
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
	*treat_quotes(char **str, int quote, t_list *envlst, char *dir_addr)
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
	left_token = ft_substr(*str, 0, len);
	*str += len;
	if (**str == BACKSLASH)
		token = ft_strjoin(left_token, treat_backslash(str, quote, envlst, dir_addr));
	else if (**str == DOLLAR)
		token = ft_strjoin(left_token, treat_dollar(str, quote, envlst, 0));
	else if (*(*str)++)
		token = ft_strjoin(left_token, parse_token(str, envlst, dir_addr));
	else
		token = ft_calloc(sizeof(char), 1);
	free(left_token);
	return (token);
}


char
	*parse_token(char **str, t_list *envlst, char *dir_addr)
{
	size_t	len;
	char	*token;
	char	*left_token;

	len = 0;
	while ((*str)[len] && !ft_strchr(STOP_SYMBOLS, (*str)[len]))
		len++;
	left_token = ft_substr(*str, 0, len);
	(*str) += len;
	if (**str == QUOTE || **str == DQUOTE)
		token = ft_strjoin(left_token, treat_quotes(str, **str, envlst, dir_addr));
	else if (**str == BACKSLASH)
		token = ft_strjoin(left_token, treat_backslash(str, 0, envlst, dir_addr));
	else if (**str == DOLLAR || **str == '~')
		token = ft_strjoin(left_token, treat_dollar(str, 0, envlst, dir_addr));
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
		token = ft_substr(*str, 0, 2);
		*str += 2;
	}
	else
		token = ft_substr((*str)++, 0, 1);
	
	return (token);
}

t_cmd
	*parser(char *str, t_list *envlst, char *dir_addr)
{
	t_cmd	*cmd;
	char	*token;
	t_bool	is_redirect;

	cmd = init_cmd();
	token = 0;
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
			token = parse_token(&str, envlst, dir_addr);
			is_redirect = FALSE;
		}
		if (token && *token)
			if (add_token(cmd, token, is_redirect))
				return (cmd_clear(cmd));
	}
	if (is_redirect)
	{
		error_parse(PARSE_ERROR, 0);
		return(cmd_clear(cmd));
	}
	return (cmd);
}