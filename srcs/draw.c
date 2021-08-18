#include "so_long.h"

static void	get_xoffset(int *x_draw, int x)
{
	if (x > 26)
	{
		while (x > 26)
		{
			*x_draw -= 1300;
			x -= 26;
		}
	}
}

static void	get_yoffset(int *y_draw, int y)
{
	if (y > 13)
	{
		while (y > 13)
		{
			*y_draw -= 650;
			y -= 13;
		}
	}
}

static void	*get_bg(t_root *root, int x, int y)
{
	if (x > root->game->width || y >= root->game->height || y < 0)
		return (root->wall);
	if (root->game->map[y][x] == '1')
		return (root->wall);
	if (root->game->map[y][x] == '0')
		return (root->bg);
	if (root->game->map[y][x] == 'P' && root->game->player_right)
		return (root->player);
	else if (root->game->map[y][x] == 'P' && root->game->player_left)
		return (root->player_mir);
	if (root->game->map[y][x] == 'C')
		return (root->coll);
	if (root->game->map[y][x] == 'E')
		return (root->exit);
	return (root->wall);
}

static void	draw_map(t_root *root)
{
	int		x_map;
	int		y_map;
	int		x_draw;
	int		y_draw;
	void	*curr_bg;

	y_draw = 0;
	y_map = 0;
	get_yoffset(&y_draw, root->game->player.y);
	while (y_draw < root->game->height * 50)
	{
		x_draw = 0;
		x_map = 0;
		get_xoffset(&x_draw, root->game->player.x);
		while (x_draw < root->game->width * 50)
		{
			curr_bg = get_bg(root, x_map++, y_map);
			mlx_put_image_to_window(root->mlx, root->mlx_win,
				curr_bg, x_draw, y_draw);
			x_draw += 50;
		}
		++y_map;
		y_draw += 50;
	}
}

/*
	Entry point of draw functions
	1. call helper to draw all components
	
*/
int	draw(t_root *root)
{
	draw_map(root);
	draw_info(root);
	return (1);
}
