/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:24:35 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/24 15:24:35 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_substring;

	count = 0;
	in_substring = 0;
	while (*s != '\0')
	{
		if (in_substring == 1 && *s == c)
			in_substring = 0;
		if (in_substring == 0 && *s != c)
		{
			in_substring = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*malloc_word(char const *s, char c)
{
	char	*word;
	int		length;

	length = 0;
	while (s[length] != c && s[length] != '\0')
		length++;
	word = malloc(sizeof(char) * (length + 1));
	ft_strlcpy(word, s, length + 1);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			split[i] = malloc_word(s, c);
			i++;
			while (*s != c && *s != '\0')
				s++;
		}
		else
			s++;
	}
	split[i] = NULL;
	return (split);
}
