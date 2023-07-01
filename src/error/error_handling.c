/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:11:55 by ysakahar          #+#    #+#             */
/*   Updated: 2023/07/01 20:53:04 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser_error(int error, t_state *state, t_lexer *lexer)
{
	ft_lexerclear(&lexer);
	ft_error(error, state);
}

int	double_token_error(t_state *state, t_lexer *lexer, t_operators op)
{
	ft_putstr_fd("minishell: parse error near ",
		STDERR_FILENO);
	if (op == REDIRECT_OUTPUT)
		ft_putstr_fd("`>'\n", STDERR_FILENO);
	else if (op == APPEND_OUTPUT)
		ft_putstr_fd("`>>'\n", STDERR_FILENO);
	else if (op == REDIRECT_INPUT)
		ft_putstr_fd("`<'\n", STDERR_FILENO);
	else if (op == HEREDOC)
		ft_putstr_fd("`<<'\n", STDERR_FILENO);
	else if (op == PIPELINE)
		ft_putstr_fd("`|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	ft_lexerclear(&lexer);
	reset_tools(state);
	return (EXIT_FAILURE);
}

int	export_error(char *c)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	if (c)
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(c, STDERR_FILENO);
		ft_putstr_fd("\': is ", STDERR_FILENO);
	}
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	lexer_error(int error, t_state *state)
{
	ft_lexerclear(&state->lexer);
	ft_error(error, state);
}

int	cmd_not_found(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}
