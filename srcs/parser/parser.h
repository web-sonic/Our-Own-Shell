/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:15:29 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/19 14:07:05 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../includes/minishell.h"

# define SPACES " \t"
# define QUOTE 39
# define DQUOTE 34
# define PIPE 124
# define SEMICOLON 59
# define GREAT 62
# define LOW 60
# define BACKSLASH 92
# define DOLLAR 36
# define DIEZ 35
# define STOP_SYMBOLS "\\\"'<>\t "
# define SPEC_SYMBOLS "\\\"'~"
# define STRANGE_STR "@!#$&*(){}[]`\"'-><"

char	*treat_dollar(char **str, t_bool *is_quest);
char	*treat_quotes(char **str, int quote, char *dir_addr);
char	*treat_tilda(char **str, char *dir_addr);
char	*treat_backslash(char **str, int quote, char *dir_addr);
char	*parse_vars(char *str, t_list *envlst, int *is_quote);
void	skip_spaces(char **str, char *spaces);
char	*goto_stopsymbol(char **str, char stop_symbol);
t_cmd	*parser(char *str, t_list *envlst, char *dir_addr);
char	*parse_token(char **str, char *dir_addr);
int		add_token(t_cmd *cmd, char *token, t_bool is_redirect);
int		check_redirect(char *token, int *flag);
int		add_fdout(t_cmd *cmd, char *token);
int		add_fdin(t_cmd *cmd, char *token);

#endif
