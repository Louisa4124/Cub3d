/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:36:20 by tlegrand          #+#    #+#             */
/*   Updated: 2023/03/28 15:38:12 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen2(s1);
	len_s2 = ft_strlen2(s2);
	str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (s1)
		ft_strlcpy(str, s1, len_s1 + 1);
	if (s2)
		ft_strlcpy(str + len_s1, s2, len_s2 + 1);
	return (str);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_s3;
	char	*str;

	len_s1 = ft_strlen2(s1);
	len_s2 = ft_strlen2(s2);
	len_s3 = ft_strlen2(s3);
	str = (char *)malloc((len_s1 + len_s2 + len_s3 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (s1)
		ft_strlcpy(str, s1, len_s1 + 1);
	if (s2)
		ft_strlcpy(str + len_s1, s2, len_s2 + 1);
	if (s3)
		ft_strlcpy(str + len_s1 + len_s2, s3, len_s3 + 1);
	return (str);
}
