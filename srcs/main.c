/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:36:49 by louisa            #+#    #+#             */
/*   Updated: 2023/06/30 11:14:55 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_man(int num)
{
	if (num == 1)
		printf("Cub3d need a map!\n");
	else if (num > 2)
		printf("Cub3d take only 1 parameter!\n");
	printf("Example : ./cub3D map.cub\n");
	return (0);
}

t_vec3d	**ft_malloc_rayon(t_game *game)
{
	t_vec3d		**rayon;
	int			x;

	x = 0;
	rayon = malloc(sizeof(t_vec3d *) * game->mlx.win_height + 1);
	while (x < game->mlx.win_height)
	{
		rayon[x] = malloc(sizeof(t_vec3d) * game->mlx.win_width + 1);
		x++;
	}
	return (rayon);
}

int	ft_win_event(int keycode, t_game *game)
{
	return (0);
}

t_vec3d	s_vec3d_init(float x, float y, float z)
{
	t_vec3d	u;

	u.x = x;
	u.y = y;
	u.z = z;
	return (u);
}

// verifier que x et y sont dans la map
int	ft_in_wall(t_game *game, int x, int y)
{
	if (x >= 0 && y >= 0 && game->map.layout[y][x] == 1)
		return (1);
	return (0);
}

int ft_hit_wall(t_game *game, float x, float y)
{
	if (ft_in_wall(game, x - 0.1, y + 0.1)
		|| ft_in_wall(game, x + 0.1, y + 0.1)
		|| ft_in_wall(game, x - 0.1, y - 0.1)
		|| ft_in_wall(game, x + 0.1, y - 0.1))
		return (1);
	return (0);
}

int	ft_move(t_game *game)
{
	t_vec3d	z_axis;
	t_vec3d	dir;
	t_vec3d	new_pos;

	z_axis = s_vec3d_init(0, 0, 1);
	new_pos = s_vec3d_init(game->pos.x, game->pos.y, game->pos.z);
	dir = ft_rotate_vec_z(s_vec3d_init(0, -DIR_OFFSET, 0), game->angle_z);
	if (game->bit_key & BFLAG_W)
	{
		new_pos = math_vec_op(new_pos, dir, '+');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = math_vec_op(game->pos, dir, '+');
	}
	if (game->bit_key & BFLAG_S)
	{
		new_pos = math_vec_op(new_pos, dir, '-');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = math_vec_op(game->pos, dir, '-');
	}
	if (game->bit_key & BFLAG_A)
	{
		new_pos = math_vec_op(new_pos, math_vec_op(dir, z_axis, '^'), '+');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = math_vec_op(game->pos, math_vec_op(dir, z_axis, '^'), '+');
	}
	if (game->bit_key & BFLAG_D)
	{
		new_pos = math_vec_op(new_pos, math_vec_op(dir, z_axis, '^'), '-');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = math_vec_op(game->pos, math_vec_op(dir, z_axis, '^'), '-');
	}
	if (game->bit_key & BFLAG_RIGHT)
		game->angle_z += ANG_OFFSET;
	if (game->bit_key & BFLAG_LEFT)
		game->angle_z -= ANG_OFFSET;
	if (game->bit_key & BFLAG_UP && game->angle_x > -0.5)
		game->angle_x -= ANG_OFFSET;
	if (game->bit_key & BFLAG_DOWN&& game->angle_x < 0.5)
		game->angle_x += ANG_OFFSET;
	if (game->angle_z >= PI * 2)
		game->angle_z -= PI * 2;
	else if (game->angle_z <= -PI * 2)
		game->angle_z += PI * 2;
	return (0);
}

int	ft_press(int keycode, t_game *game)
{
	if (keycode == 53 || keycode == KEY_ESCAPE)
		close_event(game);
	else if (keycode == KEY_W)
		game->bit_key |= BFLAG_W;
	else if (keycode == KEY_UP)
		game->bit_key |= BFLAG_UP;
	else if (keycode == KEY_S)
		game->bit_key |= BFLAG_S;
	else if (keycode == KEY_DOWN)
		game->bit_key |= BFLAG_DOWN;
	else if (keycode == KEY_A)
		game->bit_key |= BFLAG_A;
	else if (keycode == KEY_D)
		game->bit_key |= BFLAG_D;
	else if (keycode == KEY_RIGHT)
		game->bit_key |= BFLAG_RIGHT;
	else if (keycode == KEY_LEFT)
		game->bit_key |= BFLAG_LEFT;
	return (0);
}

void	event_mouse(int x, int y, t_game *game)
{
	int	x_quarter;

	x_quarter = game->mlx.win_width >> 2;
	if (x < x_quarter)
	{
		game->angle_z -= 0.007;
		game->dir = ft_rotate_vec_z(game->dir, -0.007);
	}
	else if (x > x_quarter * 3)
	{
		game->angle_z += 0.007;
		game->dir = ft_rotate_vec_z(game->dir, 0.007);
	}
	if (game->angle_z >= PI * 2)
		game->angle_z -= PI * 2;
	else if (game->angle_z <= -PI * 2)
		game->angle_z += PI * 2;
	mlx_mouse_move(game->mlx.ptr, game->mlx.win, game->mlx.win_width >> 1, game->mlx.win_height >> 1);
}

int	ft_unpress(int keycode, t_game *game)
{	
	if (keycode == KEY_W)
		game->bit_key ^= BFLAG_W;
	else if (keycode == KEY_UP)
		game->bit_key ^= BFLAG_UP;
	else if (keycode == KEY_S)
		game->bit_key ^= BFLAG_S;
	else if (keycode == KEY_DOWN)
		game->bit_key ^= BFLAG_DOWN;
	else if (keycode == KEY_A)
		game->bit_key ^= BFLAG_A;
	else if (keycode == KEY_D)
		game->bit_key ^= BFLAG_D;
	else if (keycode == KEY_RIGHT)
		game->bit_key ^= BFLAG_RIGHT;
	else if (keycode == KEY_LEFT)
		game->bit_key ^= BFLAG_LEFT;
	return (0);
}

void	ft_create_vector(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->mlx.win_height)
	{
		j = 0;
		while (j < game->mlx.win_width)
		{
			game->rays[i][j].x = ((j - game->mlx.win_width * 0.5) * game->r_h);
			game->rays[i][j].y = -1.0;
			game->rays[i][j].z = ((game->mlx.win_height * 0.5 - i) * game->r_v);
			j++;
		}
		i++;
	}
}

//LOULOU EST SUPER FORTE NANMEOH!!!!!!

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argv;
	int res = write(1, "Bonjour ! Je suis le cub3D de Tilou et j'ai treeees sommeil.... \nShmimimimimi\n rommpshhhhh\n", 91);
	(void) res;
	if (argc != 2)
		return (ft_man(argc));
	if (ft_init_mlx(&game))
		return (1);
	s_map_init(&game.map);
	s_texture_init(&game.texture);
	if (parser(argv[1], &game))
		return (1);
	ft_init_game(&game);
	game.rays = ft_malloc_rayon(&game);
    ft_create_vector(&game);
	if (ft_creat_plans(&game) == 0)
		return (1);
	game.view.id = mlx_new_image(game.mlx.ptr, game.mlx.win_width, game.mlx.win_height);
	if (game.view.id != NULL)
	{
		game.view.addr = mlx_get_data_addr \
			(game.view.id, &game.view.bpp, &game.view.ll, &game.view.endian);
		// mlx_mouse_move(game.mlx.ptr, game.mlx.win, game.mlx.win_width >> 1, game.mlx.win_height >> 1);
		// mlx_mouse_hide(game.mlx.ptr, game.mlx.win);
		mlx_loop_hook(game.mlx.ptr, ft_update_game, &game);
		//mlx_mouse_hook(game.mlx.win, event_mouse, &game);
        mlx_hook(game.mlx.win, 2, 1L << 0, ft_press, &game);
		mlx_hook(game.mlx.win, 3, 1L << 1, ft_unpress, &game);
		mlx_hook(game.mlx.win, 17, 0L, &close_event, &game);
		mlx_loop(game.mlx.ptr);
	}
	mlx_mouse_show(game.mlx.ptr, game.mlx.win);
	ft_clean_exit(&game, EXIT_FAILURE);
	return (0);
}
