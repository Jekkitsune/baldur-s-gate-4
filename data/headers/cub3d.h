/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:21:26 by fparis            #+#    #+#             */
/*   Updated: 2024/10/13 09:19:08 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MacroLibX/includes/mlx.h"
# include "../libft/libft.h"

# define M_PI 0

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>

# define GROUND '0'
# define WALL '1'
# define VOID ' '
# define NB_TEX 4

# define NB_RAYS 1600
# define FOV 0.7
# define HEIGHT 900
# define WIDTH 1600


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
}	t_texture;

typedef struct s_entity
{
	char		type;
	void		*id;
	t_texture	*tex;
	t_vector	pos;
	t_vectorf	offset;
}	t_entity;

typedef	struct s_cell
{
	char		type;
	t_texture	*tex[4];
	t_list		*entities;
}	t_cell;

typedef struct s_impact
{
	t_vector	wall_pos;
	float		length;
	int			face;
	t_vectorf	direc;
	float		angle;
	t_cell		*cell;
}	t_impact;

typedef	struct s_map
{
	int			index;
	t_vector	size;
	t_cell		**arr;
}	t_map;

typedef struct s_player
{
	t_vector	pos;
	t_vectorf	offset;
	float		angle;
	int			movement[6];
	int			rotation[4];
	int			speed;
	int			is_running;
	t_impact	vision[NB_RAYS];
	t_vectorf	camera_plane;
	t_vectorf	direction;
	int			pitch;
	int			height;
	int			focus_mode;
	float		focus_dist;
	float		pos_z;

	t_vector	target_pos;
	t_vectorf	target_offset;
}	t_player;

typedef struct minimap
{
	int			UI_size;
	int			fig_size;
	t_vector	pos;
	int			chunk_size;
	char		**chunk;
	void		*img;
}	t_minimap;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_texture	*textures[4];
	char		floor_color[9];
	char		ceiling_color[9];
	t_vector	win_size;
	t_map		*current_map;
	t_minimap	minimap;
	t_player	player;
	int			scale;
	int			render_distance;
	int			test_key;
	float		test_length;
	int			(*check_shape[2])(struct s_data *data, t_vector vec);
	void		*screen_display;
	int			on_screen;
	uint32_t	**screen_buffer;
} t_data;

typedef	struct s_linfo
{
	int		color;
	int		width;
	void	*img;
	int		(*check)(t_data *data, t_vector vec);
}	t_linfo;

void		print_map(t_map *map);
void		print_chunk(t_data *data);

int			in_bound(t_map map, t_vector vec);
t_vector	vec_sum(t_vector vec1, t_vector vec2);
int			create_minimap(t_data *data, int UI_size, int fig_size);
void		update_chunk(t_data *data);
void		show_minimap(t_data *data);
int			key_up_manager(int key, void *param);
int			key_down_manager(int key, void *param);
void		init_player(t_data *data);
void		move(t_data *data);
t_vector	vec(int x, int y);
void		draw_line(t_data *data, t_vector p1, t_vector p2, t_linfo info);
t_vector	vec_add(t_vector vec, int add);
t_impact	get_impact(t_vector start, t_vectorf direc, t_data *data);
t_vector	vec_mult(t_vector vec, int mult);
int			in_window(t_vector win_size, t_vector vec);
void		get_all_rays(t_data *data);
void		show_screen(t_data *data);
t_data		*init_data(t_data *data);
int			default_shape(__attribute__((unused)) t_data *data, __attribute__((unused)) t_vector vec);
int			in_minimap(t_data *data, t_vector vec);
t_linfo		linfo(int color, int width, int (*check_shape)(t_data *data, t_vector vec), void *img);
void		draw_square(t_data *data, t_vector pos, t_linfo info);
float		angle_add(float angle, float add);
void		draw_line_raycast(t_data *data, int x, int start, int end, int color, t_impact *ray);

bool		parsing(int argc, char *argv[], t_data *data);
bool		vec_cmp(t_vector vec1, t_vector vec2);

void		get_all_rays_old(t_data *data);
void		camera_move(t_data *data);
void		correct_pos(t_data *data, t_vector *pos, t_vectorf *offset);
void		rotate_focus(t_data *data);
int			window_manager(int event, void *param);
void		free_tex(t_texture *tex);
t_texture	*new_texture(int size);
t_vectorf	vecf(float x, float y);
bool		check_textures(t_texture **tex_tab);
t_texture	*path_to_tex(t_data *data, char *path);
void		show_tex(t_data *data, t_texture *tex, t_vector pos);
t_texture	*resize(t_texture *tex, int new_size);
void		draw_wall(t_data *data, int x, t_vector pos, t_impact *ray);
void		free_map(t_map *map);

#endif
