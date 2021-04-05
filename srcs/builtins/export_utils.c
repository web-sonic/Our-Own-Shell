/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 15:27:00 by sgath             #+#    #+#             */
/*   Updated: 2021/04/05 12:47:25 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void
	check_line_export(char *line, t_exp *exp)
{
	int	j;

	j = -1;
	while (line[++j] && line[j] != '=' && exp->error == 0)
	{
		if (!(line[j] == '_' || ft_isalnum(line[j])))
		{
			if (line[j] == '+' && line[j + 1] == '=')
				exp->plus = 1;
			else
				exp->error = export_error(line);
		}
	}
}
