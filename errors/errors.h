/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:43:55 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/04 05:39:33 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define PARSE_UNDEF "undefined behavior. Quotes are not closed"
# define PARSE_ERROR "syntax error near unexpected token"

# define NUM_COMMAND_NOT_FOUND 127
# define NUM_ERROR_DIR 2
# define NUM_ERROR_PARSE 258

int		cd_error(char *dir_str, char *old_str);
void	exit_error(char *line);
int		export_error(char *str);
int		flag_error(char *name, char *arg);
void	print_errors(char *str);
void	exceptions(char c);
t_list	*error_parse(char *str, int c);
void	file_error(char *file, char *error);

#endif
