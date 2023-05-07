/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:40:09 by tlegrand          #+#    #+#             */
/*   Updated: 2022/12/25 15:48:36 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_strlen_secure(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*ft_self_append(char *self, char const *to_append)
{
	size_t	len_s;
	size_t	len_ta;
	char	*new_str;

	if (!self && !to_append)
		return (NULL);
	len_s = ft_strlen_secure(self);
	len_ta = ft_strlen_secure(to_append);
	new_str = (char *)malloc((len_s + len_ta + 1) * sizeof(char));
	if (new_str)
	{
		if (self)
			ft_strlcpy(new_str, self, len_s + 1);
		if (to_append)
			ft_strlcpy(new_str + len_s, to_append, len_ta + 1);
	}
	if (self)
		free(self);
	return (new_str);
}
