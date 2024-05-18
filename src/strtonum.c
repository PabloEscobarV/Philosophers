/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtonum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:27:56 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/18 17:26:19 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\f' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

static int	ft_isdigit(int arg)
{
	unsigned char	ch;

	ch = (unsigned char)arg;
	return (ch >= '0' && ch <= '9');
}

long	ft_atoi(const char *nptr)
{
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	if (*nptr == '\0')
		return (0);
	while (ft_isspace(*nptr))
		++nptr;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		++nptr;
	}
	while (ft_isdigit(*nptr))
		result = result * 10 + ((*nptr++) - '0');
	return (result * sign);
}
