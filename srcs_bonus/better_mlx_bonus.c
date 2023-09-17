/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_mlx_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:49:29 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/17 13:42:41 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/extensions/Xfixes.h>
#include "../mlx-linux/mlx_int.h"

int	better_mlx_mouse_hide(t_xvar *xvar, t_win_list *win, int *cursor)
{
	if (*cursor == 1)
	{
		XFixesHideCursor(xvar->display, win->window);
		*cursor = 0;
		return (0);
	}
	return (1);
}

int	better_mlx_mouse_show(t_xvar *xvar, t_win_list *win, int *cursor)
{
	if (*cursor == 0)
	{
		XFixesShowCursor(xvar->display, win->window);
		*cursor = 1;
		return (0);
	}
	return (1);
}
