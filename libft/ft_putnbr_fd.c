/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:39:41 by ysakahar          #+#    #+#             */
/*   Updated: 2023/01/13 16:39:41 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr_fd(unsigned long un, int fd)
{
	if (un >= 10)
	{
		ft_putunbr_fd(un / 10, fd);
		ft_putunbr_fd(un % 10, fd);
	}
	else
		ft_putchar_fd(un + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putunbr_fd(-(long)n, fd);
	}
	else
		ft_putunbr_fd(n, fd);
}
