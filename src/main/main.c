/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:59:06 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 13:40:25 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_state	state;

	if (argc != 1 || argv[1])
	{
		printf("No arguments allowed.\n");
		exit(0);
	}
	initialization(&state, envp);
	minishell_loop(&state);
	return (0);
}

/*
__attribute__((destructor)) static void	destructor(void)
{
	system("leaks -q minishell");
}
*/
