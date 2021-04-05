/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:40:21 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/05 12:53:36 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void
	dub_and_free(char **rem_str, char *str)
{
	if (*rem_str)
	{
		free(*rem_str);
		*rem_str = 0;
	}
	*rem_str = ft_strdup(str);
}
