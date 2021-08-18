#include "so_long.h"

/*
	Math to get xoffset
*/
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

/*
	Math to get yoffset
*/
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

/*
	Returns image pointers based on the current
	map character
*/
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
	if (root->game->map[y][x] == 'S')
		return (root->enemy);
	return (root->wall);
}

/*
	This function will draw the map data to the screen
	1. get the offset of vertical pixels to draw
	 and store it in y_draw() based on player position
	2. while y_draw is less than game height, do sth
		- get the offset of horizontal pixels to draw
	 	and store it in x_draw() based on player position
		- call get_bg to put each and evey image to the screen
*/
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
	2. call helper to draw the player move string
	3. call move_enemy() every 50 frames
	4. reset frames to 0 if frames > 150
	5. increment frames
*/
int	draw(t_root *root)
{
	static int	frame;

	draw_map(root);
	draw_info(root);
	if (frame % 50 == 0)
		move_enemy(root);
	if (frame == 150)
		frame = 0;
	frame++;
	return (1);
}
