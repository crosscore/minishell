/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:05:42 by ysakahar          #+#    #+#             */
/*   Updated: 2023/01/13 02:05:42 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	j = i;
	while (s1[j])
		j++;
	j--;
	while (j > i && is_in_set(s1[j], set))
		j--;
	result = malloc(sizeof(char) * (j - i + 2));
	if (!result)
		return (NULL);
	k = 0;
	while (i <= j)
		result[k++] = s1[i++];
	result[k] = '\0';
	return (result);
}
