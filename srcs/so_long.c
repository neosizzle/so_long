#include "so_long.h"

//function to quit program
static int	quit(void)
{
	exit(0);
	return (1);
}

//the programs entry point
/*
	1. checks for valid argc and map file
	2. initialises mlx as well as game data
	3. draw them to the screen using said data
	4. spawns enemies into the map
	5. attach a key handler to handle keys
	6. attach a hook to quit program when x is clicked
	7. attach a loop hook to keep rendering 24/7
*/
int	main(int argc, char **argv)
{
	t_root			*root;

	if (argc != 2)
		error("Usage: ./so_long [map]\n");
	if (!valid_ber(argv[1]))
		error("Error: not a map file\n");
	root = init_root(argv[1]);
	draw(root);
	spawn_enemy(root);
	mlx_key_hook(root->mlx_win, key_handler, root);
	mlx_hook(root->mlx_win, 17, 0, quit, root);
	mlx_loop_hook(root->mlx, draw, root);
	mlx_loop(root->mlx);
	return (0);
}
