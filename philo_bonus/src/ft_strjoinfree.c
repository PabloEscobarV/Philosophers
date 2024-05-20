/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:08:45 by blackrider        #+#    #+#             */
/*   Updated: 2024/05/20 13:09:57 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strcpy(char *dest, char const *src)
{
	if (!src)
		return (dest);
	while (*src != '\0')
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0';
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		return (count);
	while (str[count] != '\0')
		++count;
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	arr = malloc((size1 + size2 + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	ft_strcpy(ft_strcpy(arr, s1), s2);
	arr[size1 + size2] = '\0';
	return (arr);
}

char	*ft_strjoinfree(char *s1, char *s2, int pos)
{
	char	*data;

	data = ft_strjoin(s1, s2);
	if (pos < 0)
		return (data);
	if (pos == 0)
	{
		free((char *)s1);
		return (data);
	}
	if (pos == 1)
	{
		free((char *)s2);
		return (data);
	}
	free((char *)s1);
	free((char *)s2);
	return (data);
}
