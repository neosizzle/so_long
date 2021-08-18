#include "so_long.h"

/*
** Validates the maps width then set it in root game struct. 
*/
void	map_width(t_root *root, char *map_data)
{
	root->game->width = 0;
	while (map_data[root->game->width] && map_data[root->game->width] != '\n')
		root->game->width++;
	if (root->game->width == 0 || map_data[root->game->width] == 0)
	{
		destroy_root(root);
		free(map_data);
		error("Error: Invalid map dimension!\n");
	}
}

/*
** Validates the maps height then set it in root game struct. 
*/
void	map_height(t_root *root, char *map_data)
{
	int	i;
	int	j;

	root->game->height = 1;
	i = root->game->width + 1;
	while (i < (int) ft_strlen(map_data))
	{
		j = 0;
		while (map_data[i + j] != 0 && map_data[i + j] != '\n')
			j++;
		if (!map_data[i + j])
			j++;
		if (j != root->game->width)
		{
			destroy_root(root);
			free(map_data);
			error("Error: Invalid map dimension!\n");
		}
		i += root->game->width + 1;
		root->game->height++;
	}
}

/*
	checks if current character position is border
	1. check for first row (i < root->game->width)
	2. check for last row (i > root->game->width + 1) * (root->game->height - 1))
	3. check for first col (i % (root->game->width + 1) == 0)
	4. check for last col (i % (root->game->width + 1) == root->game->width - 1))
*/
static int	is_border(t_root *root, int idx)
{
	if (idx < root->game->width
		|| (idx > (root->game->width + 1) * (root->game->height - 1))
		|| (idx % (root->game->width + 1) == 0)
		|| (idx % (root->game->width + 1) == root->game->width - 1))
		return (1);
	return (0);
}

//checks if current character is a valid entity
static void	is_ent(t_root *root, char c, char *map_data)
{
	if (c == 'P')
		root->game->count_player++;
	else if (c == 'E')
		root->game->count_exit++;
	else if (c == 'C')
		root->game->count_coll++;
	else if (c == '1' || c == '0' || c == 'S')
		return ;
	else
	{
		destroy_root(root);
		free(map_data);
		error("Error: Invalid map entity!\n");
	}
}

/*
** Validates the map type and its entities. 
** Map must have at least -
**	1 Exit
**	1 Player position
**	1 Collectable
**	Surrounded by walls
** 	Nothing else.
**
**	1. traverse the map letter by letter
**	2. ignore newline
**	3. check borders if current idx is border
**	4. check valid entity
**	5. after traversing, return result with said rules
*/
int	map_valid(t_root *root, char *map_data)
{
	int	i;

	i = -1;
	while (map_data[++i])
	{
		if (map_data[i] == '\n' || map_data[i] == 13)
			continue ;
		if (is_border(root, i))
		{
			if (map_data[i] != '1')
			{
				destroy_root(root);
				free(map_data);
				error("Error: map is not covered by borders\n");
			}
		}
		is_ent(root, map_data[i], map_data);
	}
	if (root->game->count_exit == 1
		&& root->game->count_player == 1
		&& root->game->count_coll >= 1)
		return (1);
	return (0);
}
