/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:51:55 by tlegrand          #+#    #+#             */
/*   Updated: 2023/01/20 14:17:38 by tlegrand         ###   ########.fr       */
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

void	ft_freesplit(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

char	**ft_split(char const *s, char c)
{
	size_t	n_str;
	size_t	i;
	char	**split;

	n_str = ft_countstr(s, c);
	split = (char **)malloc((n_str + 1) * sizeof(char *));
	if (!split || !s)
		return (NULL);
	i = 0;
	while (*s && i < n_str)
	{
		while (*s == c)
			s++;
		split[i] = ft_substr(s, 0, ft_findsize(s, c));
		if (!split[i])
		{
			ft_freesplit(split);
			return (NULL);
		}
		i++;
		s += ft_findsize(s, c);
	}
	split[i] = NULL;
	return (split);
}
