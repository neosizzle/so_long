#include "so_long.h"

static int	quit()
{
	exit(0);
	return (1);
}

//the programs entry point
/*
1. checks for valid argc and map file
2. initialises mlx as well as game data
3. draw them to the screen using said data
4. attack a key handler to handle keys
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
	mlx_key_hook(root->mlx_win, key_handler, root);
	mlx_hook(root->mlx_win, 17, 0, quit, root);
	mlx_loop_hook(root->mlx, draw, root);
	mlx_loop(root->mlx);
	return (0);
}
