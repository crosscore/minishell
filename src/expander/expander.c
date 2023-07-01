/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:11:07 by ysakahar          #+#    #+#             */
/*   Updated: 2023/07/01 23:34:34 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	loop_if_dollar_sign(t_state *state, char *str, char **tmp, int j)
{
	int		k;
	int		ret;
	char	*tmp2;
	char	*tmp3;

	k = 0;
	ret = 0;
	while (state->envp[k])
	{
		if (ft_strncmp(str + j + 1, state->envp[k],
				equal_sign(state->envp[k]) - 1) == 0
			&& after_dol_lenght(str, j) - j == (int)equal_sign(state->envp[k]))
		{
			tmp2 = ft_strdup(state->envp[k] + equal_sign(state->envp[k]));
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			ret = equal_sign(state->envp[k]);
		}
		k++;
	}
	if (ret == 0)
		ret = after_dol_lenght(str, j) - j;
	return (ret);
}

int	handle_digit_after_dollar(int j, char *str)
{
	int	i;

	i = j;
	if (str[j] == '$')
	{
		if (ft_isdigit(str[j + 1]) == 1)
		{
			j += 2;
		}
	}
	return (j - i);
}

char	*detect_dollar_sign(t_state *state, char *str)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = 0;
	tmp = ft_strdup("\0");
	while (str[j])
	{
		j += handle_digit_after_dollar(j, str);
		if (str[j] == '$' && str[j + 1] == '?')
			j += question_mark(&tmp);
		else if (str[j] == '$' && (str[j + 1] != ' ' && (str[j + 1] != '"'
					|| str[j + 2] != '\0')) && str[j + 1] != '\0')
			j += loop_if_dollar_sign(state, str, &tmp, j);
		else
		{
			tmp2 = char_to_str(str[j++]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free(tmp2);
		}
	}
	return (tmp);
}

char	**expander(t_state *state, char **str)
{
	int		i;
	size_t	dollar_pos;
	char	*tmp;
	bool	is_single_quoted;

	i = 0;
	tmp = NULL;
	while (str[i] != NULL)
	{
		is_single_quoted = false;
		// Check if the entire string is enclosed in single quotes
		int len = strlen(str[i]);
		if (str[i][0] == '\'' && str[i][len-1] == '\'')
			is_single_quoted = true;
		else if ((dollar_pos = find_dollar_pos(str[i])) >= 2 && str[i][dollar_pos - 2] == '\'')
			is_single_quoted = true;

		if (!is_single_quoted && dollar_pos >= 1 && str[i][dollar_pos - 1] != '\''
			&& str[i][dollar_pos] != '\0')
		{
			tmp = detect_dollar_sign(state, str[i]);
			free(str[i]);
			str[i] = tmp;
		}
		else
		{
			// Memory re-allocation can be avoided if str[i] is not changed
			if (ft_strncmp(str[0], "export", ft_strlen(str[0]) - 1) != 0)
			{
				str[i] = delete_quotes(str[i], '\"');
				str[i] = delete_quotes(str[i], '\'');
			}
		}
		i++;
	}
	return (str);
}

char	*expander_str(t_state *state, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (find_dollar_pos(str) >= 1 && str[find_dollar_pos(str) - 1] != '\''
		&& find_dollar_pos(str) != 0 && str[find_dollar_pos(str)] != '\0')
	{
		tmp = detect_dollar_sign(state, str);
		free(str);
		str = tmp;
	}
	str = delete_quotes(str, '\"');
	str = delete_quotes(str, '\'');
	return (str);
}
