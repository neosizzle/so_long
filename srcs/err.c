#include "so_long.h"

/*
**Prints error message to screen and exit
*/
void	error(char *message)
{
	ft_putstr_fd(message, 1);
	exit(-1);
}

/*
**Checks if the path given ends with a .ber extension
*/
int		valid_ber(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (!path)
		return (0);
	if (len < 5)
		return (0);
	if (ft_strncmp(path + len - 4, ".ber", len) != 0)
		return (0);
	return (1);
}

/*
Destroys game in root struct and frees memory
*/

static void destroy_game(t_game *game)
{
	int	i;

	if (game != 0)
	{
		if (game->coll != 0)
			free(game->coll);
		if (game->map != 0)
		{
			i = 0;
			while (i < game->height)
				free(game->map[i++]);
			free(game->map);
		}
		free(game);
	}
}

/*
Destroys root struct and frees memory
*/
void	destroy_root(t_root	*root)
{
	if (root != 0)
	{
		if (root->bg != 0)
			mlx_destroy_image(root->mlx, root->bg);
		if (root->wall != 0)
			mlx_destroy_image(root->mlx, root->wall);
		if (root->coll != 0)
			mlx_destroy_image(root->mlx, root->coll);
		if (root->exit != 0)
			mlx_destroy_image(root->mlx, root->exit);
		if (root->player != 0)
			mlx_destroy_image(root->mlx, root->player);
		if (root->mlx_img != 0)
			mlx_destroy_image(root->mlx, root->mlx_img);
		if (root->mlx_win != 0)
			mlx_destroy_window(root->mlx, root->mlx_win);
		if (root->mlx != 0)
			mlx_destroy_display(root->mlx);
		if (root->game != 0)
			destroy_game(root->game);
		free(root);
	}
}