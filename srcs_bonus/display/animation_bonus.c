/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:59:18 by lboudjem          #+#    #+#             */
/*   Updated: 2023/08/04 20:56:11 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	ft_animation_h(t_game *game, t_sprite *sprite, t_vec2d pos, float speed)
{
	int	ry;
	int	rx;
	int	count;

	count = 0;
	ry = sprite->img.height;
	rx = sprite->img.width / sprite->frame;
	if (game->ms >= speed)
		sprite->x += rx;
	if (sprite->x >= rx * sprite->frame)
	{
		sprite->x = 0;
		++count;
	}
	draw_on(&game->view, (t_vec2d) {pos.x,pos.y}, sprite->img, \
		(t_area) {sprite->x,sprite->x + rx,sprite->y,sprite->y + ry});
	return (count);
}

void	ft_animation(t_game *game, t_sprite *sprite, t_vec2d pos)
{
	int			ry;
	int			rx;

	ry = sprite->img.height / sprite->frame;
	rx = sprite->img.width;
	if (game->ms >= 0.02)
		sprite->y += ry;
	if (sprite->y >= ry * sprite->frame)
		sprite->y = 0;
	draw_on(&game->view, (t_vec2d) {pos.x,pos.y}, sprite->img, \
		(t_area) {sprite->x,sprite->x + rx,sprite->y,sprite->y + ry});
}

void	animation_fire(t_game *game)
{
	if (game->player == 1)
	{
		ft_draw_img(&game->view, game->anim[1][2], 1100, 750);
		ft_animation_h(game, &game->sprite[8], (t_vec2d){1250, 590}, 0.02);
	}
	else if (game->player == 2)
	{
		ft_draw_img(&game->view, game->anim[1][2], 1100, 750);
		ft_animation_h(game, &game->sprite[7], (t_vec2d){1250, 590}, 0.02);
	}
	else if (game->player == 3)
	{
		ft_draw_img(&game->view, game->anim[1][2], 1100, 750);
		ft_animation_h(game, &game->sprite[9], (t_vec2d){1250, 590}, 0.02);
	}
	if (game->ms >= 0.02)
		game->ms -= 0.02;
}
