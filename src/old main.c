

/*static void       print_debug(t_conf *conf)
{
    int x, y;

    printf("R: %dx%d\n", conf->res.x, conf->res.y);
    printf("NO: %s\n", conf->textures[TEXTURE_NO]);
    printf("SO: %s\n", conf->textures[TEXTURE_SO]);
    printf("WE: %s\n", conf->textures[TEXTURE_WE]);
    printf("EA: %s\n", conf->textures[TEXTURE_EA]);
    printf("S: %s\n", conf->textures[TEXTURE_S]);
    printf("F: %d,%d,%d\n", conf->floor_color[0], conf->floor_color[1], conf->floor_color[2]);
    printf("C: %d,%d,%d\n", conf->ceil_color[0], conf->ceil_color[1], conf->ceil_color[2]);
    printf("Map: %dx%d\n", conf->map_dim.y, conf->map_dim.x);
    y = 0;
    while (y < conf->map_dim.y)
    {
        x = 0;
        printf("[ ");
        while (x < conf->map_dim.x)
        {
            if (conf->pos.x == x && conf->pos.y == y)
                printf(" %d ", (int)conf->direction);
            else
                printf(" %d ", conf->map[y][x]);
            x++;
        }
        printf(" ]\n");
        y++;
    }
}*/

/*

    t_reso  screen_res;
    t_conf  *conf;
    int     err;

    conf = NULL;
    err = 0;
    if ((err = check_args(&conf, argc, argv)) != 0)
    {
        print_error(err);
        return (-1);
    }
    if ((err = parse_config(conf)) != 0)
    {
        print_error(err);
        free_config(conf);
        return (-1);
    }
    int x, y;
    y = 0;
    while (y < conf->map_dim.y)
    {
        x = 0;
        printf("[ ");
        while (x < conf->map_dim.x)
        {
            if (conf->cur_pos.x == x && conf->cur_pos.y == y)
                printf(" %f ", conf->direction);
            else
                printf(" %d ", conf->map[y][x]);
            x++;
        }
        printf(" ]\n");
        y++;
    }
    printf("map[0][0]: %d\n", conf->map[0][0]);
    conf->mlx = mlx_init();
    if (!conf->mlx)
    {
        print_error(ERR_MLX_INIT_FAIL);
        free_config(conf);
        return (-1);
    }
    mlx_get_screen_size(conf->mlx, &screen_res.x, &screen_res.y);
    conf->res.x = (conf->res.x > screen_res.x) ? screen_res.x : conf->res.x;
    conf->res.y = (conf->res.y > screen_res.y) ? screen_res.y : conf->res.y;
    conf->win = mlx_new_window(conf->mlx, conf->res.x, conf->res.y, "Cub3D");
    if (!conf->win)
    {
        print_error(ERR_MLX_NEW_WINDOW_FAIL);
        free_config(conf);
        return (-1);
    }
*/