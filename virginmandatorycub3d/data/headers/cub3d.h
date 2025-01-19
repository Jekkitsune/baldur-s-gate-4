/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:21:26 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 23:51:28 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define M_PI 0

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include "../macroLibX/includes/mlx.h"
# include "../libft/libft.h"

# define HEIGHT 900
# define WIDTH 1600
# define NB_RAYS 1600

# define FPS_CAP 60

# define GROUND '0'
# define WALL '1'
# define VOID ' '

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_vectorf
{
	float	x;
	float	y;
}	t_vectorf;

typedef struct s_texture
{
	uint32_t	**tab;
	int			size;
	char		*name;
}	t_texture;

typedef struct s_cell
{
	char		type;
	t_texture	*tex[4];
}	t_cell;

typedef struct s_map
{
	int			index;
	t_vector	size;
	t_cell		**arr;
	char		*path;
}	t_map;

typedef struct s_impact
{
	t_vector	wall_pos;
	float		length;
	int			face;
	t_vectorf	direc;
	float		angle;
	t_cell		*cell;
	t_vectorf	slope_coef;
}	t_impact;

typedef struct s_player
{
	t_vector	pos;
	t_vectorf	offset;
	float		angle;
	float		speed;
	t_vectorf	camera_plane;
	t_vectorf	direction;
	int			movement[4];
	int			rotation[2];
	t_impact	vision[NB_RAYS];
	int			height;
	int			pitch;
}	t_player;

typedef struct s_data
{
	t_vector	win_size;
	void		*mlx;
	void		*win;
	int			scale;
	int			render_distance;
	uint32_t	**screen_buffer;
	t_map		*map;
	char		floor_color[9];
	char		ceiling_color[9];
	uint32_t	fc;
	uint32_t	cc;
	t_texture	*wall_tex[4];
	t_player	player;
	void		*screen_display;
}	t_data;

t_vector	vec_sum(t_vector vec1, t_vector vec2);
t_vector	vec_mult(t_vector vec, int mult);
t_vector	vec_add(t_vector vec, int add);
t_vector	vec(int x, int y);
bool		vec_cmp(t_vector vec1, t_vector vec2);
t_vectorf	vecf(float x, float y);
void		exit_free(t_data *data, char *error);
t_data		*init_data(t_data *data);
bool		parsing(int argc, char **argv, t_data *data);
t_texture	*path_to_tex(t_data *data, char *path);
void		free_tex(t_texture *tex);
t_texture	*resize(t_texture *tex, int new_size);
t_texture	*new_texture(int size);
bool		is_map_closed(char **map);
bool		check_char(char **map, int i, int j, t_data *data);
bool		check_textures(t_texture *default_tex[4]);
void		init_player(t_data *data);
float		angle_add(float angle, float add);
float		get_angle_diff(float angle1, float angle2);
void		init_mlx_events(t_data *data);
int			key_down_manager(int key, void *param);
int			key_up_manager(int key, void *param);
int			window_manager(int event, void *param);
void		move(t_data *data);
void		get_all_rays(t_data *data);
t_impact	get_impact(t_vector start, t_vectorf direc, t_data *data);
void		show_screen(t_data *data);
void		free_data(t_data *data);
char		**get_map_infos(t_data *data, int fd, t_map *level);
bool		format_test(char *name);
bool		init_level(t_map *level);
void		turn_map(t_data *data, char **map, t_map *level);
int			in_bound(t_map *map, t_vector vec);
t_impact	*found_wall(t_impact *impact, t_vectorf length);
void		get_wall_tex(char **split, t_data *data);
bool		special_atoi(char *str, int *res);
uint32_t	convert(char *color, char *base);
void		get_hexa(char hexa[2], int value);
char		**get_map(t_data *data, int fd, t_map *level);
void		get_lines(int fd, char *lines[7]);

#endif
