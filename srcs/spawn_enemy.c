#include "so_long.h"

//generates a random number using a and b 
static int	random_num(int a, int b)
{
	int	c;

	a = a * 3;
	b = b * 2;
	c = a + b;
	return (c);
}

static void	fill_ent(t_root *root, int x, int y, int i)
{
	root->game->map[y][x] = 'S';
	root->game->count_enemies ++;
	root->game->enemies[i].x = x;
	root->game->enemies[i].y = y;
}

/*
	Spawns enemies into the map regarding to mapsize
*/
void	spawn_enemy(t_root *root)
{
	int	cnt;
	int	x;
	int	y;
	int	i;

	cnt = root->game->width * root->game->height / 25;
	x = random_num(root->game->width, root->game->height) % root->game->width;
	y = random_num(root->game->height, root->game->width) % root->game->height;
	root->game->enemies
		= (t_coord *)malloc(sizeof(t_coord) * 1024);
	i = 0;
	while (cnt > 0)
	{
		if (x < root->game->width && y < root->game->height
			&& root->game->map[y][x] == '0')
		{
			fill_ent(root, x, y, i);
			i++;
		}
		x = random_num(x, y) % root->game->width;
		y = random_num(y, x + 1) % root->game->height;
		cnt--;
	}
}
