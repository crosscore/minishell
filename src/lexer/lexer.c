/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:55:33 by ysakahar          #+#    #+#             */
/*   Updated: 2023/07/01 18:02:29 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_words(int i, char *str, t_lexer **lexer)
{
	int	j;
	int	ret;
	int	len;

	len = ft_strlen(str);
	j = 0;
	while ((i + j) < len && str[i + j] && !(check_op(str[i + j])))
	{
		ret = handle_quotes(i + j, str, '\"');
		if (ret < 0)
			return (-1);
		j += ret;
		ret = handle_quotes(i + j, str, '\'');
		if (ret < 0)
			return (-1);
		j += ret;
		if (is_delimiter(str[i + j]))
			break ;
		else
			j++;
	}
	if (!add_node(ft_substr(str, i, j), 0, lexer))
		return (-1);
	return (j);
}

static int	analyze_and_add_tokens(t_state *state)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(state->args);
	i = 0;
	while (i < len)
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
	if (!count_quote_pairs(state->args))
		return (ft_error(2, state));
	if (!analyze_and_add_tokens(state))
		return (ft_error(1, state));
	return (1);
}
