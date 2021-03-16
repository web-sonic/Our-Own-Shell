/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:22 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/16 17:06:00 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int
	main(int argc, char **argv, char **env)
{
	while (argc)
		shell_loop(argv[0], env);
	return 0;
}