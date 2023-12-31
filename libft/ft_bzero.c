/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 01:12:29 by ysakahar          #+#    #+#             */
/*   Updated: 2023/01/13 01:12:29 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*s1;

	if (n == 0)
		return ;
	s1 = (char *)s;
	while (n > 0)
	{
		*s1 = '\0';
		s1++;
		n--;
	}
}
