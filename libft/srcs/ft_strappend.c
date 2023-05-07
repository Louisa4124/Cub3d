/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:18:59 by tlegrand          #+#    #+#             */
/*   Updated: 2023/03/30 23:31:26 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strappend(char *self, char *to_append)
{
	size_t	len_s;
	size_t	len_ta;
	char	*new_str;

	if (!self && !to_append)
		return (NULL);
	len_s = ft_strlen2(self);
	len_ta = ft_strlen2(to_append);
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
