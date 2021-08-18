#include "so_long.h"

/*
	game over
*/
void	game_over(void)
{
	ft_putstr_fd("YOU DIE\n", 1);
	exit(0);
}

/*
Check enemy to player collision
*/
void	check_e2p(t_root *root, int direction, int og_x, int og_y)
{
	if (direction == 1)
	{
		if (root->game->map[og_y - 1][og_x] == 'P')
			game_over();
	}
	if (direction == 2)
	{
		if (root->game->map[og_y][og_x + 1] == 'P')
			game_over();
	}
	if (direction == 3)
	{
		if (root->game->map[og_y + 1][og_x] == 'P')
			game_over();
	}
	if (direction == 4)
	{
		if (root->game->map[og_y][og_x - 1] == 'P')
			game_over();
	}	
}

/*
**Check if next move is coll for enemies
*/
int	check_coll_enemy(t_root *root, int direction, int og_x, int og_y)
{
	if (direction == 1)
	{
		if (root->game->map[og_y - 1][og_x] == 'C')
			return (1);
	}
	if (direction == 2)
	{
		if (root->game->map[og_y][og_x + 1] == 'C')
			return (1);
	}
	if (direction == 3)
	{
		if (root->game->map[og_y + 1][og_x] == 'C')
			return (1);
	}
	if (direction == 4)
	{
		if (root->game->map[og_y][og_x - 1] == 'C')
			return (1);
	}
	return (0);
}
