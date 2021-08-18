#include "so_long.h"

//check for winning condition
int	check_win(t_root *root)
{
	if (root->game->count_coll == root->game->player_coll)
	{
		ft_putstr_fd("You win!!!\n", 1);
		exit(0);
	}
	return (1);
}

//check for exit collision
int	check_exit(t_root *root, int direction, int og_x, int og_y)
{
	if (direction == 1)
	{
		if (root->game->map[og_y - 1][og_x] == 'E' )
			return (check_win(root));
	}
	if (direction == 2)
	{
		if (root->game->map[og_y][og_x + 1] == 'E')
			return (check_win(root));
	}
	if (direction == 3)
	{
		if (root->game->map[og_y + 1][og_x] == 'E')
			return (check_win(root));
	}
	if (direction == 4)
	{
		if (root->game->map[og_y][og_x - 1] == 'E' )
			return (check_win(root));
	}
	return (0);
}

/*
Check if next move is coll
*/
void	check_coll(t_root *root, int direction, int og_x, int og_y)
{
	if (direction == 1)
	{
		if (root->game->map[og_y - 1][og_x] == 'C')
			root->game->player_coll++;
	}
	if (direction == 2)
	{
		if (root->game->map[og_y][og_x + 1] == 'C')
			root->game->player_coll++;
	}
	if (direction == 3)
	{
		if (root->game->map[og_y + 1][og_x] == 'C')
			root->game->player_coll++;
	}
	if (direction == 4)
	{
		if (root->game->map[og_y][og_x - 1] == 'C')
			root->game->player_coll++;
	}
}

/*
Check if next move is valid (for wall)
	1 is up 
	2 is right
	3 is down
	4 is left
*/
int	check_move(t_root *root, int direction, int og_x, int og_y)
{
	if (direction == 1)
	{
		if (root->game->map[og_y - 1][og_x] == '1')
			return (0);
	}
	if (direction == 2)
	{
		if (root->game->map[og_y][og_x + 1] == '1')
			return (0);
	}
	if (direction == 3)
	{
		if (root->game->map[og_y + 1][og_x] == '1')
			return (0);
	}
	if (direction == 4)
	{
		if (root->game->map[og_y][og_x - 1] == '1')
			return (0);
	}
	return (1);
}

//Check for player to enemy collision
void	check_p2e(t_root *root, int direction, int og_x, int og_y)
{
	if (direction == 1)
	{
		if (root->game->map[og_y - 1][og_x] == 'S')
			game_over();
	}
	if (direction == 2)
	{
		if (root->game->map[og_y][og_x + 1] == 'S')
			game_over();
	}
	if (direction == 3)
	{
		if (root->game->map[og_y + 1][og_x] == 'S')
			game_over();
	}
	if (direction == 4)
	{
		if (root->game->map[og_y][og_x - 1] == 'S')
			game_over();
	}
}
