void    ft_print_texture_no_we(t_game *game, int wall, int i, int j)
{
        int     x;
        int     y;

        x = 0;
        y = 0;
        x = (int)(((game->pos.x + game->point.x) - (int)(game->pos.x + \
                 game->point.x)) * game->texture.wall[wall].width);
        y = game->texture.wall[wall].height - (int)((game->point.z - \
                (int)(game->point.z)) * game->texture.wall[wall].height) - 1;
        game->color = *(unsigned int *)(game->texture.wall[wall].addr + \
                y * game->texture.wall[wall].ll + x * (game->texture.wall[wall].bpp / 8));
}

void    ft_print_texture_so_ea(t_game *game, int wall, int i, int j)
{
        int     x;
        int     y;

        x = 0;
        y = 0;

        x = (int)(((game->pos.y + game->point.y) - (int)(game->pos.y + \
                 game->point.y)) * game->texture.wall[1].width); //wall
        y = game->texture.wall[wall].height - (int)((game->point.z - \
                (int)(game->point.z)) * game->texture.wall[wall].height) - 1;
        game->color = *(unsigned int *)(game->texture.wall[wall].addr + \
                y * game->texture.wall[wall].ll + x * (game->texture.wall[wall].bpp / 8)); //dark
}

void    ft_print_texture(t_game *game, int i, int j)
{
        game->point.x = game->u_rays.x * game->close_t;
        game->point.y = game->u_rays.y * game->close_t;
        game->point.z = 0.5 + game->u_rays.z * game->close_t;
        if (game->u_plan.x == 0 && (game->pos.y + game->point.y) < game->pos.y 
                && (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) < game->map.y_size 
                && (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) >= 0 
                && game->map.layout[(int)(-game->plan[game->u_plan.x] \
                [game->u_plan.y].d - 1)][(int)(game->pos.x + game->point.x)] == 1)
                ft_print_texture_no_we(game, 0, i, j);
        else if (game->u_plan.x == 1 && (game->pos.x + game->point.x) < game->pos.x 
                && (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) < game->map.x_size 
                && (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) >= 0 
                && game->map.layout[(int)(game->pos.y + game->point.y)][(int)\
                (-game->plan[game->u_plan.x][game->u_plan.y].d - 1)] == 1)
                ft_print_texture_so_ea(game, 1, i, j);
        else if (game->u_plan.x == 0 && (game->pos.y + game->point.y) > game->pos.y \
                && (int)(-game->plan[game->u_plan.x][game->u_plan.y].d) < game->map.y_size \
                && (int)(-game->plan[game->u_plan.x][game->u_plan.y].d) >= 0 
                && game->map.layout[(int)(-game->plan[game->u_plan.x][game->u_plan.y].d)] \
                [(int)(game->pos.x + game->point.x)] == 1)
                ft_print_texture_no_we(game, 2, i, j);
        else
                ft_print_texture_so_ea(game, 0, i, j); //3
}