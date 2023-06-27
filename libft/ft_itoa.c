/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:12:23 by ysakahar          #+#    #+#             */
/*   Updated: 2023/04/05 16:52:04 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len = 1;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static char	*ft_num_to_str(char *str, int nbr, int len)
{
	int	pos;

	pos = ft_num_len(nbr) - 1;
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	while (nbr >= 10)
	{
		str[pos--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[pos] = nbr + '0';
	str[len] = '\0';
	return (str);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	int		len;

	len = ft_num_len(nbr);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	return (ft_num_to_str(str, nbr, len));
}
