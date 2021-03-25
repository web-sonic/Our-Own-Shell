/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_complete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:52:46 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/25 15:05:26 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd
    parse_complete(char *str, char **env)
{
    t_cmd   cmd;

    while (*str || *str != DIEZ)
    {
        str++;
    }
    return (cmd);
}