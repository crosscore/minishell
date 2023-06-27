/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 05:35:07 by ysakahar          #+#    #+#             */
/*   Updated: 2023/05/26 19:58:08 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	return (i);
}

char	*ft_strjoin_v2(char *remain_data, char *buffer)
{
	char	*result;
	int		i;
	int		j;

	if (!remain_data)
	{
		remain_data = malloc(sizeof(char) * 1);
		remain_data[0] = '\0';
	}
	if (!remain_data || !buffer)
		return (NULL);
	result = malloc(sizeof(char) * \
			(ft_strlen(remain_data) + ft_strlen(buffer) + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (remain_data[++i])
		result[i] = remain_data[i];
	j = -1;
	while (buffer[++j])
		result[i + j] = buffer[j];
	result[i + j] = '\0';
	free(remain_data);
	return (result);
}

char	*ft_strchr_v2(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0' && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_new_remain_data(char *remain_data)
{
	char	*ptr;
	char	*new_remain_data;
	size_t	len;
	size_t	i;

	ptr = ft_strchr_v2(remain_data, '\n');
	if (!ptr)
	{
		free(remain_data);
		return (NULL);
	}
	len = ft_strlen(ptr + 1);
	new_remain_data = malloc(sizeof(char) * (len + 1));
	if (!new_remain_data)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_remain_data[i] = ptr[i + 1];
		i++;
	}
	new_remain_data[len] = '\0';
	free(remain_data);
	return (new_remain_data);
}

char	*ft_get_line(char *remain_data)
{
	int		i;
	char	*line;

	i = 0;
	if (!remain_data[i])
		return (NULL);
	while (remain_data[i] != '\n' && remain_data[i])
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (remain_data[i] != '\n' && remain_data[i])
	{
		line[i] = remain_data[i];
		i++;
	}
	if (remain_data[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}
