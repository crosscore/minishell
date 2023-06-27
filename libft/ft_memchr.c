/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 01:13:24 by ysakahar          #+#    #+#             */
/*   Updated: 2023/01/13 01:13:24 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int ch, size_t n)
{
	size_t			i;
	unsigned char	*b;
	unsigned char	c;

	b = (unsigned char *)buf;
	c = (unsigned char)ch;
	i = 0;
	while (i < n)
	{
		if (b[i] == c)
			return (&b[i]);
		i++;
	}
	return (NULL);
}
