/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:21:26 by fparis            #+#    #+#             */
/*   Updated: 2024/11/22 19:31:39 by fparis           ###   ########.fr       */
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
# define DOOR '2'
# define NB_TEX 17
# define NB_BUTTON 20

# define NB_RAYS (1600 / 2)
# define FOV 0.7
# define HEIGHT (900 / 2)
# define WIDTH (1600 / 2)
# define HEIGHT_CAP 5000


# define CLOSE 0
# define OPEN 1
# define OPENING 2
# define CLOSING 3

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

typedef struct s_animation
{
	t_texture	**tab;
	int			size;
	char		*name;
	int			interval;
	void		(*anim_sound)(int index, int clock);
}	t_animation;

typedef struct s_button
{
	t_bool		active;
	void		(*func)(void *data, void *entity);
	t_texture	*img;
	t_vector	start;
	t_vector	end;
}	t_button;

typedef struct s_sheet
{
	t_button	buttons[NB_BUTTON];
}	t_sheet;

typedef struct s_entity
{
	t_bool		visible;
	t_texture	*tex[4];
	float		angle;
	t_vector	pos;
	t_vectorf	offset;
	float		distance;
	t_vectorf	true_pos;
	int			nb_impact;
	t_vector	draw_x;
	t_vector	draw_y;
	t_bool		active;
	void		(*behavior)(void *data, void *entity);
	t_bool		possess_control;
	t_animation	*anim;
	t_animation	*current_anim;
	int			nb_anim;
	int			anim_index;
	int			anim_clock;
	t_sheet		sheet;
}	t_entity;

typedef	struct s_cell
{
	char		type;
	t_texture	*tex[4];
	t_list		*entities;
	int			status;
	int			timer;
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
	t_list		*active_entities;
	char		*path;
}	t_map;

typedef struct s_player
{
	t_vector	pos;
	t_vectorf	offset;
	float		angle;
	int			movement[6];
	int			rotation[4];
	int			mouse_wheel;
	int			mouse_button[3];
	t_vector	mouse_pos;
	double		speed;
	int			is_running;
	t_impact	vision[NB_RAYS];
	t_vectorf	camera_plane;
	t_vectorf	direction;
	int			pitch;
	int			height;
	int			focus_mode;
	float		focus_dist;

	t_entity	*possession;
	t_button	*active_button;
	t_entity	*arrow;

	t_list		*visible_entities;
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
	t_texture	*textures[NB_TEX];
	char		floor_color[9];
	char		ceiling_color[9];
	t_vector	win_size;
	t_list		*map_list;
	t_map		*current_map;
	t_minimap	minimap;
	t_player	player;
	int			scale;
	int			render_distance;
	int			test_key;
	int			(*check_shape[2])(struct s_data *data, t_vector vec);
	void		*screen_display;
	int			on_screen;
	uint32_t	**screen_buffer;
	bool		sky_box;
	int			fps;
	t_entity	**prefab_tab;
	int			nb_prefab;
	int			button_scale_size;
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
//void		draw_wall(t_data *data, int x, t_vector pos, t_impact *ray);
void		free_map(t_data *data, t_map *map);
void		draw_thing(t_data *data, t_vector pos, t_vectorf offset, t_texture *tex);
void		ft_pixel_put(t_data *data, int y, int x, uint32_t color);
void		draw_entities(t_data *data);
t_entity	*create_entity(t_data *data, t_vector pos, t_texture *tex);
void		calculate_entity_info(t_data *data, t_entity *entity);
void		move_entity(t_data *data, t_entity *entity, t_vectorf move);
void		follow_player(void *arg_data, void *arg_entity);
void		ft_nothing(void *data, void *entity);
t_list		*ft_lstpop(t_list **lst_start, void *check);
void		destroy_active(t_data *data, t_entity *entity);
t_bool		check_activity(t_data *data, t_entity *entity);
int			ft_inlst(t_list *lst, void *check);
void		destroy_entity(t_data *data, t_entity *entity);
t_entity	*add_active(t_data *data, t_entity *entity, void (*behavior)(void *, void *));
void		remove_active(t_data *data, t_entity *entity);
void		update_all_active(t_data *data);
int			mouse_wheel_manager(int key, void *param);
void		possess(t_data *data, t_entity *entity);
void		unpossess(t_data *data);
void		possess_control(t_entity *entity, t_bool value);
void		teleport_entity(t_data *data, t_entity *entity, t_vector pos, t_vectorf offset);
float		get_angle_diff(float angle1, float angle2);
t_entity	*set_entity_tex(t_entity *entity, t_texture *tex2, t_texture *tex3, t_texture *tex4);
int			mouse_down_manager(int key, void *param);
int			mouse_up_manager(int key, void *param);
void		exit_free(t_data *data, char *error);
void		free_visible_lst(t_data *data);
void		free_data(t_data *data);
t_texture	*get_correct_tex(t_entity *entity, int face);
int			get_anim_index(t_entity *entity, char *name);
void		change_anim(t_entity *entity, char *name);
void		init_anim(t_data *data, t_animation *anim, int size, char *path);
void		continue_anim(t_data *data, t_entity *entity);
void		free_prefab_entity(t_data *data, t_entity *entity);
int			get_anim_size(char *path);
t_animation	*add_anim(t_animation **tab, t_animation *new, int *nb_anim);
t_entity	*get_prefab_data(t_data *data, char *directory);
t_entity	*spawn_entity(t_data *data, t_entity *prefab, t_vector pos);
void		add_prefab(t_data *data, t_entity *prefab);
void		draw_possession_button(t_data *data, t_button *buttons);
void		check_button_click(t_data *data);
int			get_hover_index(t_data *data);
void		draw_hover(t_data *data, t_vector start, uint32_t color);
t_texture	*get_tex(t_data *data, char *name);
void		update_button_action(t_data *data);
void		remove_arrow(t_data *data);


void	exemple_action(void *data_param, void *entity_param);
void		init_test(t_data *data);

#endif
