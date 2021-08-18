#include "so_long.h"

/*
** Sets the coords of entities in the root struct
*/
static void set_coords(t_root *root, char *map_data, int k)
{
	static int count;
	if (map_data[k] == 'P')
	{
		root->game->player.x = k % (root->game->width + 1);
		root->game->player.y = k / (root->game->width + 1);
		map_data[k] = '0';
	}
	else if (map_data[k] == 'E')
	{
		root->game->exit.x = k % (root->game->width + 1);
		root->game->exit.y = k / (root->game->width + 1);
		map_data[k] = '0';
	}
	else if (map_data[k] == 'C')
	{
		root->game->coll[count].x = k % (root->game->width + 1);
		root->game->coll[count].y = k / (root->game->width + 1);
		map_data[k] = '0';
		count++;
	}
}

/*
	1. traverse the hieght and witdh of the map_data
	2. when entering a new height, malloc a string with width
	3. traverse that width and store the character in the x y of map
	4. set coords of entities if needed
	5. null term width and height
*/
static void	map_parse(t_root *root, char *map_data)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = -1;
	while (++i < root->game->height)
	{
		j = -1;
		(root->game->map)[i] = (char *)malloc(sizeof (char) * (root->game->width + 1));
		while (++j < root->game->width)
		{
			root->game->map[i][j] = map_data[++k];
			set_coords(root, map_data, k);
		}
		++k;
		root->game->map[i][j] = 0;
	}
	root->game->map[i] = 0;
}

/*
	1. does all the map height/width validation
	2. does all the map type validation
	3. allocates mem for the collectable coordinates
	4. allocates memory for the map layout (2d char arr)
	5. start parsing the map into 2d char arr
*/
static void	map_read(t_root *root, char *map_data)
{
	map_width(root, map_data);
	map_height(root, map_data);
	if (!map_valid(root, map_data))
	{
		free(map_data);
		destroy_root(root);
		error("Error: Invalid map\n");
	}
	root->game->coll
		= (t_coord *)malloc(sizeof(t_coord) * root->game->count_coll);
	if (!root->game->coll)
	{
		free(map_data);
		destroy_root(root);
		error("Error: malloc() failed\n");
	}
	root->game->map = (char **)malloc(sizeof(char *) * (root->game->height + 1));
	if (!root->game->map)
	{
		free(map_data);
		destroy_root(root);
		error("Error: malloc() failed\n");
	}
	map_parse(root, map_data);
}

static void	read_to_buf(int fd, char **temp, char **data, char **buff)
{
	*temp = ft_strjoin(*data, *buff);
	free(*data);
	free(*buff);
	*data = *temp;
	*buff = get_next_line(fd);
}

/*
	1.open the map_data specified in map_datapath and throw err if needed
	2.call get_next_line in a loop to get all contents in a map_data
	3.join all contents in buff and passes to map reading
*/
void	init_map(t_root *root, char *map_path)
{
	int		fd;
	char	*data;
	char	*buff;
	char	*temp;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		destroy_root(root);
		error("Error: invalid fd open()\n");
	}
	buff = get_next_line(fd);
	data = ft_bzero(0);
	while (buff)
		read_to_buf(fd, &temp, &data, &buff);
	close(fd);
	map_read(root, data);
	root->game->width--;
	free(data);
}