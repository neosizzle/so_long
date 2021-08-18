#include "so_long.h"

//this funtion will display the total number of steps on the screen
void	draw_info(t_root *root)
{
	char	*steps;
	char	*res;
	char	*prefix;

	steps = ft_itoa(root->game->player_move);
	prefix = ft_strdup("Player move : ");
	res = ft_strcat(prefix, steps);
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->black, 0,
		root->game->height * 50);
	mlx_string_put(root->mlx, root->mlx_win, 60,
		root->game->height * 50 + 15, 16777215, res);
	free(steps);
	free(res);
	free(prefix);
}
