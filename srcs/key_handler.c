#include "so_long.h"

/*
	Move player up
	1. store the original x and y coords
	2. does all the checking before moving
	3. switch the og x and y coods into 0
	4. switch the desired x and y coods into entity
*/
static void	move_up(t_root *root, int *og_y, int *new_y)
{
	int	x;

	*og_y = root->game->player.y;
	x = root->game->player.x;
	if (!check_move(root, 1, x, *og_y) || check_exit(root, 1, x, *og_y))
		return ;
	check_p2e(root, 1, x, *og_y);
	check_coll(root, 1, x, *og_y);
	*new_y = --root->game->player.y;
	root->game->map[*og_y][x] = '0';
	root->game->map[*new_y][x] = 'P';
	root->game->player_move++;
}

/*
	Move player down
	1. store the original x and y coords
	2. does all the checking before moving
	3. switch the og x and y coods into 0
	4. switch the desired x and y coods into entity
*/
static void	move_down(t_root *root, int *og_y, int *new_y)
{
	int	x;

	*og_y = root->game->player.y;
	x = root->game->player.x;
	if (!check_move(root, 3, x, *og_y) || check_exit(root, 3, x, *og_y))
		return ;
	check_p2e(root, 3, x, *og_y);
	check_coll(root, 3, x, *og_y);
	*new_y = ++root->game->player.y;
	root->game->map[*og_y][x] = '0';
	root->game->map[*new_y][x] = 'P';
	root->game->player_move++;
}

/*
	Move player left
	1. store the original x and y coords
	2. does all the checking before moving
	3. switch the og x and y coods into 0
	4. switch the desired x and y coods into entity
*/
static void	move_left(t_root *root, int *og_x, int *new_x)
{
	int	y;

	*og_x = root->game->player.x;
	y = root->game->player.y;
	if (!check_move(root, 4, *og_x, y) || check_exit(root, 4, *og_x, y))
		return ;
	check_p2e(root, 4, *og_x, y);
	check_coll(root, 4, *og_x, y);
	*new_x = --root->game->player.x;
	root->game->map[y][*og_x] = '0';
	root->game->map[y][*new_x] = 'P';
	root->game->player_move++;
	root->game->player_left = 1;
	root->game->player_right = 0;
}

/*
	Move player right
	1. store the original x and y coords
	2. does all the checking before moving
	3. switch the og x and y coods into 0
	4. switch the desired x and y coods into entity
*/
static void	move_right(t_root *root, int *og_x, int *new_x)
{
	int	y;

	*og_x = root->game->player.x;
	y = root->game->player.y;
	if (!check_move(root, 2, *og_x, y) || check_exit(root, 2, *og_x, y))
		return ;
	check_p2e(root, 2, *og_x, y);
	check_coll(root, 2, *og_x, y);
	*new_x = ++root->game->player.x;
	root->game->map[y][*og_x] = '0';
	root->game->map[y][*new_x] = 'P';
	root->game->player_move++;
	root->game->player_left = 0;
	root->game->player_right = 1;
}

//calls helpers according to key pressed and prints out player move
int	key_handler(int keycode, t_root *root)
{
	int	og_x;
	int	og_y;
	int	new_x;
	int	new_y;

	if (keycode == 'w')
		move_up(root, &og_y, &new_y);
	if (keycode == 's')
		move_down(root, &og_y, &new_y);
	if (keycode == 'a')
		move_left(root, &og_x, &new_x);
	if (keycode == 'd')
		move_right(root, &og_x, &new_x);
	if (keycode == 65307)
		exit(0);
	ft_putstr_fd("Player move : ", 1);
	ft_putnbr_fd(root->game->player_move, 1);
	ft_putstr_fd("\n", 1);
	draw(root);
	return (1);
}
