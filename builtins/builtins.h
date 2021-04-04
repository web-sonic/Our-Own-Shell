/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 18:44:42 by sgath             #+#    #+#             */
/*   Updated: 2021/04/04 14:12:42 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	ft_echo(char **line);
int	ft_pwd(void);
int	ft_exit(char **line);
int	ft_env(t_list *envlst);
int	ft_export(char **line, t_list *envlst, int pipe);
int	ft_unset(char **line, t_list **envlst, int pipe);
int	ft_cd(char **line, t_list *envlst, int pipe);

#endif
