/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerase_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:07:52 by tlegrand          #+#    #+#             */
/*   Updated: 2023/03/30 18:37:51 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strerase_end(char *str, char *end)
{
	char	*tmp;

	if (!end || !str)
		return (str);
	tmp = ft_strndup(str, ft_strlen2(str) - ft_strlen2(end));
	free(str);
	return (tmp);
}
