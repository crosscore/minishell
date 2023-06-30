/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:55:33 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 22:01:08 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	read_words(int i, char *str, t_lexer **lexer)
{
	int	j;

	j = 0;
	while (str[i + j] && !(check_op(str[i + j])))
	{
		j += handle_quotes(i + j, str, 34);
		j += handle_quotes(i + j, str, 39);
		if (is_delimiter(str[i + j]))
			break ;
		else
			j++;
	}
	if (!add_node(ft_substr(str, i, j), 0, lexer))
		return (-1);
	return (j);
}

static int	token_reader(t_state *state)
{
	int		i;
	int		j;

	i = 0;
	while (state->args[i])
	{
		j = 0;
		i += skip_delimiter(state->args, i);
		if (check_op(state->args[i]))
			j = handle_op(state->args, i, &state->lexer);
		else
			j = read_words(i, state->args, &state->lexer);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}

int	ft_lexer(t_state *state)
{
	if (!count_quotes(state->args))
		return (ft_error(2, state));
	if (!token_reader(state))
		return (ft_error(1, state));
	return (1);
}
