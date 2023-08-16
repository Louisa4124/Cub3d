/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:59:18 by lboudjem          #+#    #+#             */
/*   Updated: 2023/08/16 16:37:38 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	ft_animation_h(t_game *game, t_sprite *sprite, t_vec2d pos, float speed)
{
	int	count;
	int	ry;
	int	rx;

	count = 0;
	ry = sprite->img.height;
	rx = sprite->img.width / sprite->frame;
	if (game->ms >= speed)
		sprite->x += rx;
	if (sprite->x >= rx * sprite->frame - 1)
	{
		sprite->x = 0;
		++count;
	}
	draw_on(&game->view, (t_vec2d){pos.x, pos.y}, sprite->img, \
		(t_area){sprite->x, sprite->x + rx, sprite->y, sprite->y + ry});
	return (count);
}

int	ft_animation_v(t_game *game, t_sprite *sprite, t_vec2d pos, float speed)
{
	int	ry;
	int	rx;
	int	count;

	count = 0;
	ry = sprite->img.height / sprite->frame;
	rx = sprite->img.width;
	if (game->ms >= speed)
		sprite->y += ry;
	if (sprite->y >= ry * sprite->frame)
	{
		sprite->y = 0;
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
	draw_on(&game->view, (t_vec2d){pos.x, pos.y}, sprite->img, \
		(t_area){sprite->x, sprite->x + rx, sprite->y, sprite->y + ry});
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

void	ft_animation_cat(t_game *game, float speed)
{
	static int	x = 20;
	static int	count = 0;

	if (count < 1)
		count += ft_animation_h(game, &game->sprite[11], (t_vec2d) {x, 985}, 0.08);
	else if (count < 4)
	{
		if (game->ms >= speed && game->pause == 5)
			++x;
		count += ft_animation_h(game, &game->sprite[15], (t_vec2d) {x, 985}, 0.08);
	}
	else if (count < 5)
		count += ft_animation_h(game, &game->sprite[11], (t_vec2d) {x, 985}, 0.08);
	else if (count < 6)
		count += ft_animation_h(game, &game->sprite[14], (t_vec2d) {x, 985}, 0.08);
	else if (count < 7)
		count += ft_animation_h(game, &game->sprite[12], (t_vec2d) {x, 985}, 0.08);
	else
		ft_draw_img(&game->view, game->sprite[16].img, x, 985);
}