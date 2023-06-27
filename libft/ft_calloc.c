/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 01:12:44 by ysakahar          #+#    #+#             */
/*   Updated: 2023/01/13 01:12:44 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	allocation_size;

	allocation_size = nmemb * size;
	if (allocation_size != 0
		&& (allocation_size < nmemb || allocation_size < size))
		return (NULL);
	ptr = malloc(allocation_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, allocation_size);
	return (ptr);
}
