#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <mlx.h>
# include <mlx_int.h>
# include "./libft/libft.h"

//struct to store the x y coords of an obj
typedef struct s_coord
{
	int				x;
	int				y;
}				t_coord;

//struct to store all game related data
typedef struct s_game
{
	char			**map;
	int				height;
	int				width;
	t_coord			player;
	int				player_left;
	int				player_right;
	int				player_move;
	int				player_coll;
	t_coord			exit;
	t_coord			*coll;
	t_coord			*enemies;
	int				count_enemies;
	int				count_coll;
	int				count_exit;
	int				count_player;
}				t_game;

//struct to store all mlx related data
typedef struct s_root
{
	void			*mlx;
	void			*mlx_win;
	void			*mlx_img;
	t_game			*game;
	void			*player;
	void			*player_mir;
	void			*enemy;
	void			*exit;
	void			*coll;
	void			*wall;
	void			*bg;
	void			*black;
}				t_root;

//error handling 
void	error(char *message);
int		valid_ber(char *path);

//root functions
t_root	*init_root(char *map_path);
void	destroy_root(t_root	*root);
void	init_map(t_root *root, char *map_path);
int		draw(t_root *root);
void	draw_info(t_root *root);

//map validation
int		map_valid(t_root *root, char *map_data);
void	map_height(t_root *root, char *map_data);
void	map_width(t_root *root, char *map_data);

//player functions
int		key_handler(int keycode, t_root *root);
int		check_move(t_root *root, int direction, int og_x, int og_y);
int		check_exit(t_root *root, int direction, int og_x, int og_y);
void	check_coll(t_root *root, int direction, int og_x, int og_y);
void	check_p2e(t_root *root, int direction, int og_x, int og_y);

//enemy funcs
void	spawn_enemy(t_root *root);
void	move_enemy(t_root *root);
int		check_coll_enemy(t_root *root, int direction, int og_x, int og_y);
void	check_e2p(t_root *root, int direction, int og_x, int og_y);
void	game_over(void);

//utils
char	*get_next_line(int fd);

#endif