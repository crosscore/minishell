/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 05:35:14 by ysakahar          #+#    #+#             */
/*   Updated: 2023/05/26 19:58:26 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_read_remain_data(int fd, char *remain_data)
{
	char	*buffer;
	int		read_bytes;

	read_bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr_v2(remain_data, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		remain_data = ft_strjoin_v2(remain_data, buffer);
	}
	free(buffer);
	return (remain_data);
}

char	*get_next_line(int fd)
{
	static char	*remain_data;
	char		*read_line;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remain_data = ft_read_remain_data(fd, remain_data);
	if (remain_data == NULL)
		return (NULL);
	read_line = ft_get_line(remain_data);
	remain_data = ft_new_remain_data(remain_data);
	return (read_line);
}
