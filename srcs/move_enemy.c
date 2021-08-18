#include "so_long.h"

/*
	Move enemy up
	1. store the original x and y coords
	2. does all the checking before moving
	3. switch the og x and y coods into 0
	4. switch the desired x and y coods into entity
*/
static void	move_up(t_root *root, int i)
{
	int	x;
	int	og_y;
	int	new_y;

	x = root->game->enemies[i].x;
	og_y = root->game->enemies[i].y;
	if (!check_move(root, 1, x, og_y) || check_coll_enemy(root, 1, x, og_y))
		return ;
	check_e2p(root, 1, x, og_y);
	new_y = --root->game->enemies[i].y;
	root->game->map[og_y][x] = '0';
	root->game->map[new_y][x] = 'S';
}

/*
	Move enemy down
	1. store the original x and y coords
	2. does all the checking before moving
	3. switch the og x and y coods into 0
	4. switch the desired x and y coods into entity
*/
static void	move_down(t_root *root, int i)
{
	int	x;
	int	og_y;
	int	new_y;

	x = root->game->enemies[i].x;
	og_y = root->game->enemies[i].y;
	if (!check_move(root, 3, x, og_y) || check_coll_enemy(root, 3, x, og_y))
		return ;
	check_e2p(root, 3, x, og_y);
	new_y = ++root->game->enemies[i].y;
	root->game->map[og_y][x] = '0';
	root->game->map[new_y][x] = 'S';
}

/*
	Move enemy left
	1. store the original x and y coords
	2. does all the checking before moving
	3. switch the og x and y coods into 0
	4. switch the desired x and y coods into entity
*/
static void	move_left(t_root *root, int i)
{
	int	y;
	int	og_x;
	int	new_x;

	og_x = root->game->enemies[i].x;
	y = root->game->enemies[i].y;
	if (!check_move(root, 4, og_x, y) || check_coll_enemy(root, 4, og_x, y))
		return ;
	check_e2p(root, 4, og_x, y);
	new_x = --root->game->enemies[i].x;
	root->game->map[y][og_x] = '0';
	root->game->map[y][new_x] = 'S';
}

/*
	Move enemy right
	1. store the original x and y coords
	2. does all the checking before moving
	3. switch the og x and y coods into 0
	4. switch the desired x and y coods into entity
*/
static void	move_right(t_root *root, int i)
{
	int	y;
	int	og_x;
	int	new_x;

	og_x = root->game->enemies[i].x;
	y = root->game->enemies[i].y;
	if (!check_move(root, 2, og_x, y) || check_coll_enemy(root, 2, og_x, y))
		return ;
	check_e2p(root, 2, og_x, y);
	new_x = ++root->game->enemies[i].x;
	root->game->map[y][og_x] = '0';
	root->game->map[y][new_x] = 'S';
}

/*
	When called, this will call one of the 
	movement helpers randomly for each enemy
*/
void	move_enemy(t_root *root)
{
	int			i;
	static int	rand;

	i = -1;
	while (++i < root->game->count_enemies)
	{
		rand += (i + 3);
		if (rand % 4 == 0)
			move_down(root, i);
		else if (rand % 4 == 1)
			move_right(root, i);
		else if (rand % 4 == 2)
			move_up(root, i);
		else
			move_left(root, i);
	}
}
