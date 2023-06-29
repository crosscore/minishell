/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:12:02 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/29 22:51:47 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_path(t_tools *tools)
{
	char	*tmp;

	tmp = ft_strdup(tools->pwd);
	free(tools->old_pwd);
	tools->old_pwd = tmp;
	free(tools->pwd);
	tools->pwd = getcwd(NULL, sizeof(NULL));
}

size_t	equal_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*delete_quotes_value(char *str)
{
	char	**split_quotes;

	split_quotes = ft_split(str, '"');
	if (!split_quotes[1])
	{
		free_array(split_quotes);
		split_quotes = ft_split(str, '\'');
	}
	free(str);
	str = ft_strjoin(split_quotes[0], split_quotes[1]);
	free_array(split_quotes);
	return (str);
}

int	check_valid_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~'
		|| c == '=' || c == '-' || c == '?' || c == '&' || c == '*');
}

// "\'\"\\$ ,.:/[{]}+=-?&*^%#@!~"