#include "so_long.h"

/*
**opens image in file path and maps it into img pointer
*/
static void	load_texture(t_root *root, void **img, char *path)
{
	int	width;
	int	height;

	*img = mlx_xpm_file_to_image(root->mlx, path, &width, &height);
	if (!img)
		error("Error: mlx_xpm_file_to_image() failure\n");
}

/*
**function thats inits the game structure inside a root struct
*/
static void	init_game(t_root *root, char *map_path)
{
	root->game = (t_game *)malloc(sizeof(t_game));
	if (!root->game)
	{
		destroy_root(root);
		error("Error: malloc() failure in root->game\n");
	}
	root->game->map = 0;
	root->game->height = 0;
	root->game->width = 0;
	root->game->player_left = 0;
	root->game->player_right = 1;
	root->game->player_move = 0;
	root->game->player_coll = 0;
	root->game->coll = 0;
	root->game->count_coll = 0;
	root->game->count_exit = 0;
	root->game->count_player = 0;
	init_map(root, map_path);
}

/*
**call helper funcs to populate the images
*/
static void	init_textures(t_root *root)
{
	load_texture(root, &(root->player), "xpm/player.xpm");
	load_texture(root, &(root->player_mir), "xpm/player_mirror.xpm");
	load_texture(root, &(root->coll), "xpm/coll.xpm");
	load_texture(root, &(root->exit), "xpm/exit.xpm");
	load_texture(root, &(root->wall), "xpm/wall.xpm");
	load_texture(root, &(root->bg), "xpm/bg.xpm");
	load_texture(root, &(root->enemy), "xpm/enemy.xpm");
	load_texture(root, &(root->black), "xpm/black.xpm");
}

/*
**does all the mlx init commmands and throws err incase failure
*/
static void	init_renderer(t_root *root)
{
	root->mlx = mlx_init();
	if (!root->mlx)
		error("Error : mlx_init() failure\n");
	root->mlx_win = mlx_new_window(root->mlx, root->game->width * 50, 30 + (root->game->height * 50), "so_long");
	if (!root->mlx_win)
		error("Error : mlx_new_window() failure\n");
}

/*
	1. tries to malloc memory for root struct (throes err if fails)
	2. set all values to 0
	3. call helpers to init textures, game and renderer
*/
t_root	*init_root(char *map_path)
{
	t_root	*res;

	res = (t_root *)malloc(sizeof(t_root));
	if (!res)
		error("Error: malloc failed\n");
	res->mlx = 0;
	res->mlx_win = 0;
	res->mlx_img = 0;
	res->game = 0;
	res->player = 0;
	res->exit = 0;
	res->coll = 0;
	res->wall = 0;
	res->bg = 0;
	init_game(res, map_path);
	init_renderer(res);
	init_textures(res);
	return (res);
}