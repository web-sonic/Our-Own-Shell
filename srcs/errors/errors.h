/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:43:55 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/06 14:12:50 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define PARSE_UNDEF "undefined behavior. Quotes are not closed"
# define PARSE_ERROR "syntax error near unexpected token"

# define NUM_COMMAND_NOT_FOUND 127
# define NUM_ERROR_DIR 2
# define NUM_ERROR_PARSE 258

# define FLAG_ERROR_EXP ": usage: export [-nf] [name[=value] ...] or export -p)"
# define FLAG_ERROR_CD "cd: usage: cd [-L|-P] [dir]"
# define FLAG_ERROR_ENV1 "usage: env [-iv] [-P utilpath] [-S string] [-u name]"
# define FLAG_ERROR_ENV2 "           [name=value ...] [utility [argument ...]]"
# define FLAG_ERROR_PWD "pwd: usage: pwd [-LP]"
# define FLAG_ERROR_UNSET "unset: usage: unset [-f] [-v] [name ...]"

int		cd_error(char *dir_str, char *old_str);
void	exit_error(char *line);
int		valid_error(char *name, char *str);
int		flag_error(char *name, char *arg);
char	*validate_cmd(char *cmd);
void	exceptions(char c);
t_list	*error_parse(char *str, int c);
void	file_error(char *file, char *error);
int		empty_lst(char *name);

#endif
