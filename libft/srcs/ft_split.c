/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:51:55 by tlegrand          #+#    #+#             */
/*   Updated: 2023/03/30 18:15:54 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_countstr(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (s && *s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static size_t	ft_findsize(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (s[size] != c && s[size])
		size++;
	return (size);
}

char	**ft_split(char const *s, char c)
{
	size_t	n_str;
	size_t	i;
	char	**split;

	n_str = ft_countstr(s, c);
	split = ft_calloc((n_str + 1), sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (s && *s && i < n_str)
	{
		while (*s == c)
			s++;
		split[i] = ft_substr(s, 0, ft_findsize(s, c));
		if (!split[i])
		{
			ft_free2d((void **)split, 0);
			return (NULL);
		}
		i++;
		s += ft_findsize(s, c);
	}
	return (split);
}

int	ft_path_splitlen(char **split)
{
	int	len;

	len = 0;
	while (split[len])
		len++;
	return (len);
}
