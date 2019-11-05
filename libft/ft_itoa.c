/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 15:34:41 by thdervil          #+#    #+#             */
/*   Updated: 2019/11/05 12:02:28 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int nb)
{
	int	size;

	size = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

static void	is_neg(int *nb, int *neg, int *size)
{
	if (*nb < 0)
	{
		*nb *= -1;
		*neg = 1;
		*size += 1;
	}
}

char		*ft_itoa(int nb)
{
	char	*result;
	int		size;
	int		neg;

	neg = 0;
	size = 0;
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	if (nb == 2147483647)
		return (ft_strdup("2147483647"));
	is_neg(&nb, &neg, &size);
	size += ft_size((long)nb) + 1;
	if (!(result = ft_strnew(sizeof(char) * size - 1)))
		return (NULL);
	result[--size] = '\0';
	while (size--)
	{
		result[size] += ((nb % 10) + '0');
		nb /= 10;
	}
	if (neg)
		result[0] = '-';
	return (result);
}
