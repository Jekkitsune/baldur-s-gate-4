/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:21:26 by fparis            #+#    #+#             */
/*   Updated: 2025/01/27 05:48:11 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../macroLibX/includes/mlx.h"
# include "../libft/libft.h"

# define M_PI 0

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <time.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>

# define GROUND '0'
# define WALL '1'
# define VOID ' '
# define DOOR '2'
# define NB_BUTTON 20
# define INVENTORY_SIZE 20
# define MAX_PARTIC_ICON 8

# define NB_RAYS (1600 / 2)
# define FOV 0.7
# define HEIGHT (900 / 2)
# define WIDTH (1600 / 2)
# define HEIGHT_CAP 5000
# define DEFAULT_FONT "Paul.ttf"
//# define DEFAULT_FONT "default"

# define HITBOX_VALUE 5.0

# define MAX_SCREEN_INFO 10

# define FPS_CAP 60

//Stats

# define STR 0
# define DEX 1
# define CON 2
# define INT 3
# define WIS 4
# define CHA 5

//Doors

# define CLOSE 0
# define OPEN 1
# define OPENING 2
# define CLOSING 3

//Dices

# define D1 7
# define D100 6
# define D20 5
# define D12 4
# define D10 3
# define D8 2
# define D6 1
# define D4 0

# define NB_DICE 8

typedef int	t_dice[NB_DICE];

//Properties

typedef enum e_property
{
	finesse = 1,
	range = 1 << 1,
	restrained = 1 << 2,
	melee = 1 << 3,
	heal_effect = 1 << 4,
	hit_effect = 1 << 5,
	shop_keeper = 1 << 6,
	unarmored_defense = 1 << 7,
	enraged = 1 << 8,
	reckless_atk = 1 << 9,
	giant_rage = 1 << 10,
	giant = 1 << 11,
	hellish_rebuke = 1 << 12,
	acid_puddle_prop = 1 << 13,
	blinded = 1 << 14,
	invisible = 1 << 15,
	true_sight = 1 << 16,
	agonizing_blast = 1 << 17,
	seasoned_spellcaster = 1 << 18,
	shadow_sword_prop = 1 << 19,
	hunger_of_hadar_prop = 1 << 20,
	difficult_terrain = 1 << 21,
	banished = 1 << 22,
	eldritch_lifesteal = 1 << 23,
	webbed = 1 << 24,
	paralyzed = 1 << 25,
	hypnotized = 1 << 26,
	dominated = 1 << 27,
	concentration_plus = 1 << 28,
}	t_property;

# define NB_PROPERTIES 29

# define PROPERTIES_TAB ((char * const[NB_PROPERTIES]) { \
    "finesse", \
    "range", \
    "restrained",  \
	"melee",\
	"heal_effect",\
	"hit_effect",\
	"shop_keeper",\
	"unarmored_defense",\
	"enraged",\
	"reckless_atk",\
	"giant_rage",\
	"giant",\
	"hellish_rebuke",\
	"acid_puddle_prop",\
	"blinded",\
	"invisible",\
	"true_sight",\
	"agonizing_blast",\
	"seasoned_spellcaster",\
	"shadow_sword_prop",\
	"hunger_of_hadar_prop",\
	"difficult_terrain",\
	"banished",\
	"eldritch_lifesteal",\
	"webbed",\
	"paralyzed",\
	"hypnotized",\
	"dominated",\
	"concentration_plus",\
})

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

typedef	struct s_map t_map;
typedef struct s_entity t_entity;

typedef	struct s_cell
{
	char		type;
	t_texture	*tex[4];
	t_list		*entities;
	t_list		*timer_property;
	int			status;
	float		timer;
	uint32_t	fog_color;
	bool		ceiling;
	t_texture	*upper_wall;
	t_entity	*key;
	t_map		*travel;
}	t_cell;

typedef struct s_animation
{
	t_texture		**tab;
	int				size;
	char			*name;
	int				interval;
}	t_animation;

typedef enum e_type
{
	weapon_1 = 0,
	weapon_2 = 1,
	head = 2,
	body = 3,
	hands = 4,
	feet = 5,
	living = 6,
	object = 7,
	consumable = 8,
	gold = 9,
	effect = 10,
}	t_type;

# define NON_EQUIP 6

typedef enum e_spelltype
{
	offensive = 0,
	debuff = 1,
	buff = 2,
	heal = 3,
	take_type = 4,
	move_type = 5,
	check_type = 6,
}	t_spelltype;

typedef struct s_spellinfo
{
	void		(*effect)(void *data, void *spell);
	t_vector	pos;
	t_vectorf	pos_offset;
	int			radius;
	t_entity	*caster;
	t_entity	*target;
	t_entity	*summon;
	t_dice		dice;
	int			nb;
	int			stat;
	float		range;
	t_bool		visible_target;
	t_bool		target_self;
	char		*anim;
	float		timer;
	t_spelltype	type;
	int			cost_action;
	int			cost_attack;
	int			cost_bonus;
	int			cost_spell_slot;
	int			concentration;
}	t_spellinfo;

typedef struct s_timer_effect
{
	t_spellinfo		spell;
	long 			duration;
	t_bool			in_round;
}	t_timer_effect;

typedef struct s_timer_property
{
	t_property		property;
	t_entity		*caster;
	t_entity		*entity;
	t_cell			*cell;
	long 			duration;
	t_bool			in_round;
	int				id_concentration;
	uint32_t		color;
}	t_timer_property;

typedef struct s_button
{
	int			active;
	void		(*func)(void *data, void *entity, t_spellinfo spellinfo);
	t_texture	*img;
	t_vector	start;
	t_vector	end;
	t_spellinfo	spellinfo;
	char		*description;
	char		*name;
	t_entity	*user;
}	t_button;

# define LEVEL_NB_BUTTON 4
# define MAX_LEVEL 5
# define SPELL_MAX_LV 4

typedef	struct s_level
{
	t_button	buttons[LEVEL_NB_BUTTON];
	t_property	properties;
	int			add_stats[6];
	int			add_pv;
	int			add_pb;
	int			add_nb_attack;
	int			add_spell_slot[SPELL_MAX_LV];
	t_dice		current_bonus_dice;
}	t_level;

typedef struct s_class
{
	char	*name;
	int		cast_stat;
	t_level	level[MAX_LEVEL];
}	t_class;

typedef struct s_sheet
{
	t_button	buttons[NB_BUTTON];
	int			stats[6];
	int			saving[6];
	int			level;
	int			pb;
	int			speed;
	int			walked;
	int			ac;
	int			hp;
	int			max_hp;
	int			hit_dice;
	int			death_save;
	t_dice		dice_dmg;
	int			atk_bonus;
	int			spell_bonus;
	int			spell_dc;
	char		*name;
	int			weight;
	int			carry;
	t_bool		alive;
	int			action;
	int			bonus_action;
	int			spell_slot[SPELL_MAX_LV];
	int			nb_attack;
	int			attack_left;
	int			reaction;
	t_entity	*inventory[INVENTORY_SIZE];
	t_bool		inventory_open;
	t_button	inventory_button;
	t_type		type;
	t_texture	*portrait;
	int			properties : NB_PROPERTIES + 1;
	int			team;
	int			default_team;
	t_bool		in_fight;
	int			initiative;
	float		range;
	char		*description; //Lie au prefab, non personnel a l'entite
	t_entity	*prefab;
	t_class		*class;
	void		(*wander_ia)(void *data, void *entity);
	void		(*fight_ia)(void *data, void *entity);
	t_list		*timer_property;
	t_list		*timer_concentration;
	int			price;
	int			concentration;
}	t_sheet;

typedef struct s_path
{
	t_vector		pos;
	t_vector		from;
	struct s_path	*next;
}	t_path;

typedef struct s_behavior
{
	void			(*func)(void *data, void *entity);
	unsigned long	start_time;
	t_vector		pos;
	void			(*next)(void *data, void *entity);
	t_path			*path;
	t_entity		*target;
	t_spellinfo		spell;
	t_bool			was_dominated;
	t_bool			dominated_player;
}	t_behavior;

typedef struct s_round_manager
{
	t_bool	combat;
	t_list	*party;
	t_list	*participants;
	int		party_lvl;
}	t_round_manager;

typedef struct s_floor
{
	t_vectorf	ray_dir_0;
	t_vectorf	ray_dir_1;
	float		row_distance;
	t_vectorf	floor_step;
	t_vectorf	floor;
	t_vector	cell;
	t_vector	t;
	float		cam_z;
	int			horizon;
}	t_floor;

typedef struct s_skybox
{
	float		tiniest_gap;
	float		closest_card;
	int			pixel_length;
	t_vector	left_seg;
	t_vector	right_seg;
	int			index;
	t_texture	*left_tex;
	t_texture	*right_tex;
}	t_skybox;

typedef struct s_ceiling
{
	t_vectorf	ray_dir_0;
	t_vectorf	ray_dir_1;
	float		row_distance;
	t_vectorf	floor_step;
	t_vectorf	floor;
	t_vector	cell;
	t_vector	t;
	int			st;
	int			pli;
	int			horizon;
	int			lim;
	float		cam_z;
	t_skybox	*s;
	uint32_t	color;
}	t_ceiling;

typedef struct s_dialog
{
	t_bool	is_talking;
	char	**dialog_tab;
	int		dialog_size;
	int		dialog_i;
}	t_dialog;

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
	t_behavior	behavior;
	t_bool		possess_control;
	t_animation	*anim;
	t_animation	*current_anim;
	char		*next_anim;
	int			nb_anim;
	int			anim_index;
	double		anim_clock;
	t_bool		anim_loop;
	t_sheet		sheet;
	float		size_scale;
	uint32_t	color_filter;
	t_bool		anim_no_move;
	t_dialog	dialog;
}	t_entity;

typedef struct s_fog
{
	uint32_t		fog_color;
	t_cell			*cell;
	float			length;
	int				i;
	struct s_fog	*next;
}	t_fog;


typedef struct s_impact
{
	t_vector	wall_pos;
	float		length;
	float		upper_wall_length;
	t_cell		*upper_wall_cell;
	int			face;
	int			upper_wall_face;
	t_vectorf	direc;
	float		angle;
	t_cell		*cell;
	t_vectorf	slope_coef;
	t_bool		has_fog;
	int			i;
}	t_impact;

typedef	struct s_map
{
	int			index;
	t_vector	size;
	t_cell		**arr;
	t_list		*active_entities;
	char		*path;
	t_vector	start;
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
	t_impact	vision[NB_RAYS];
	t_vectorf	camera_plane;
	t_vectorf	direction;
	int			pitch;
	int			height;
	int			focus_mode;
	float		focus_dist;
	t_vectorf	last_angle;
	t_entity	*possession;
	t_button	*active_button;
	t_entity	*arrow;
	t_list		*visible_entities;
	t_fog		*visible_fog;
	t_bool		description_mode;
	t_bool		shop_mode;
	int			gold;
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

typedef struct	s_strput
{
	char			*str;
	t_vector		pos;
	uint32_t		color;
	float			size;
	long 			duration;
}	t_strput;

typedef struct s_button_lst t_button_lst;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_list			*textures;
	char			floor_color[9];
	char			ceiling_color[9];
	t_vector		win_size;
	t_list			*map_list;
	t_map			*current_map;
	t_minimap		minimap;
	t_player		player;
	int				scale;
	int				render_distance;
	int				(*check_shape[2])(struct s_data *data, t_vector vec);
	void			*screen_display;
	int				on_screen;
	uint32_t		**screen_buffer;
	bool			sky_box;
	t_entity		**prefab_tab;
	int				nb_prefab;
	int				button_scale_size;
	t_texture		*ceiling;
	t_texture		*floor;
	t_texture		*wall_tex[4];
	t_texture		*sky_box_tex[4];
	t_list			*string_to_put;
	t_list			*timer_effect;
	t_strput		*screen_info[MAX_SCREEN_INFO];
	t_list			*class_lst;
	unsigned long 	frame_time;
	struct timeval 	current_time;
	t_round_manager	round_manager;
	char 			**properties_tab;
	t_button_lst	*button_lst;
	t_bool			shown_other_inventory;
}	t_data;

typedef struct s_button_lst
{
	char				*name;
	void				(*button_init)(t_data *data, t_button *button);
	struct s_button_lst	*next;
}	t_button_lst;

typedef	struct s_linfo
{
	int		color;
	int		width;
	int		(*check)(t_data *data, t_vector vec);
}	t_linfo;

void		print_map(t_map *map);
void		print_chunk(t_data *data);

int			in_bound(t_map *map, t_vector vec);
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
t_impact	get_impact(t_vector start, t_vectorf direc, t_data *data, int i);
t_vector	vec_mult(t_vector vec, int mult);
int			in_window(t_vector win_size, t_vector vec);
void		get_all_rays(t_data *data);
void		show_screen(t_data *data);
t_data		*init_data(t_data *data);
int			default_shape(__attribute__((unused)) t_data *data, __attribute__((unused)) t_vector vec);
int			in_minimap(t_data *data, t_vector vec);
t_linfo		linfo(int color, int width, int (*check_shape)(t_data *data, t_vector vec));
void		draw_square(t_data *data, t_vector pos, t_linfo info);
float		angle_add(float angle, float add);

bool		parsing(int argc, char *argv[], t_data *data);
bool		vec_cmp(t_vector vec1, t_vector vec2);

void		camera_move(t_data *data);
void		correct_pos(t_data *data, t_vector *pos, t_vectorf *offset);
void		rotate_focus(t_data *data);
int			window_manager(int event, void *param);
void		free_tex(t_texture *tex);
t_texture	*new_texture(int size);
t_vectorf	vecf(float x, float y);
bool		check_textures(t_texture *default_tex[4]);
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
//void		follow_player(void *arg_data, void *arg_entity);
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
void		change_anim(t_entity *entity, char *name, t_bool loop);
void		init_anim(t_data *data, t_animation *anim, int size, char *path);
void		continue_anim(t_data *data, t_entity *entity);
void		free_prefab_entity(t_data *data, t_entity *entity);
int			get_anim_size(char *path);
t_animation	*add_anim(t_animation **tab, t_animation *new, int *nb_anim);
t_entity	*get_prefab_data(t_data *data, char *directory);
t_entity	*spawn_entity(t_data *data, t_entity *prefab, t_vector pos, char *name);
void		add_prefab(t_data *data, t_entity *prefab, char *name);
void		draw_possession_button(t_data *data, t_button *buttons);
void		check_button_click(t_data *data);
int			get_hover_index(t_data *data);
void		draw_hover(t_data *data, t_vector start, uint32_t color);
t_texture	*get_tex(t_data *data, char *name);
//void		update_button_action(t_data *data);
void		remove_selector(t_data *data, t_bool reset_angle);
void		load_spells_prefab(t_data *data);
void		expire(void *arg_data, void *arg_entity);
t_entity	*get_prefab(t_data *data, char *name);
void		select_target(t_data *data);
t_bool		confirm(t_button *pushed);
void		death(void *arg_data, void *arg_entity);
float		get_dist(t_vector p1, t_vector p2);
t_bool		has_obstacle(t_data *data, t_entity *from, t_entity *target);
t_impact	get_simple_impact(t_vector start, t_vectorf direc, t_data *data);
t_bool		check_dist_obstacle(t_data *data, t_entity *entity, float dist, t_bool visible_target);
void		damage(t_data *data, t_entity *entity, int dmg);
void		add_tex(t_data *data, t_texture *tex, char *name);
void		show_health_bar(t_data *data);
void		put_screen(t_data *data);
void		clear_string_put(t_data *data, t_bool force);
int			screen_string_put(t_data *data, t_strput *to_put, float time);
t_strput	*strput(char *str, t_vector pos, float size, uint32_t color);
t_texture	*get_resized_free(t_texture *texture, int size);
void		draw_inventory(t_data *data, t_entity *inventory[INVENTORY_SIZE]);
int			inventory_hover_index(t_data *data);
int			roll(t_dice dice);
int			roll_one(int dice, int nb);
void		set_dice(t_dice to_set, int dice, int nb);
int			modif(int nb);
void		copy_dice(t_dice to_set, t_dice copy);
t_bool		check_properties(t_property properties, t_property check);

t_entity	*cycle_entity_cell(t_data *data, int move);
void		inventory_swap(t_data *data, t_entity *entity, int index1, int index2);
void		free_path(t_path **path);
void		print_path(t_path *path);
t_path		*get_path(t_data *data, t_vector start, t_vector goal, t_bool closest);
t_path		*pop_path(t_path **path);
void		entity_moving_to(void *arg_data, void *arg_entity);
void		move_to(t_data *data, t_entity *entity, t_vector pos);
void		change_anim_next(t_entity *entity, char *anim1, char *anim2, t_bool loop);
t_bool		is_empty_cell(t_data *data, t_vector pos);
t_bool		is_ground(t_data *data, t_vector pos);

void		add_timer_effect(t_data *data, t_spellinfo spell, float time, t_bool in_round);
void		update_all_timer_effects(t_data *data, t_bool round);
void		clear_entity_timer_effect(t_data *data, t_entity *entity);
void		show_info(t_data *data, char *str, ...);
void		add_to_str(char **res, char *str);

t_timer_property	*new_timer_property(t_property property, t_entity *entity,
	t_entity *caster, t_cell *cell);
void				add_timer_property(t_data *data, t_timer_property *tproperty, float time, t_bool in_round);
void				update_entity_properties(t_data *data, t_entity *entity, t_bool round);
void				clear_entity_timer_prop(t_data *data, t_entity *entity);
void				set_all_entity_timer_prop(t_data *data, t_entity *entity);


void		update_doors(t_data *data);
void		open_door(t_data *data);

void		add_class(t_list **class_lst, t_class *class);
void		init_all_classes(t_data *data);
t_class		*get_class(t_list *class_lst, char *name);
void		refresh_entity_class(t_entity *entity, int level);
void		sum_stat_tab(int *stats1, int *stats2, int len);
void		copy_stat_tab(int *stats1, int *stats2, int len);
void		refresh_stats(t_data *data, t_entity *entity);

void		party_follow(t_data *data);
void		draw_all_actions_box(t_data *data, t_entity *entity);
void		draw_box_points(t_data *data, t_vector pos, int nb_point, uint32_t color);
void		show_action_cost(t_data *data, t_spellinfo *info);
t_bool		apply_action_cost(t_data *data, t_spellinfo *spell);
void		round_refresh_stat(t_entity *entity);
void		show_party_icon(t_data *data);
void		check_click_party_icon(t_data *data, t_vector mouse);
void		show_participants_icon(t_data *data);
void		check_click_participants_icon(t_data *data, t_vector mouse);
void		mouse_up(t_data *data, int key);
void		mouse_down(t_data *data, int key);
void		leave_combat(t_data *data, t_entity *entity);
t_bool		is_turn(t_data *data, t_entity *entity);
void		check_combat_end(t_data *data);
void		party_refresh(t_data *data);
void		draw_borders(t_data *data, t_vector start);
void		draw_button_img(t_data *data, t_texture *img, t_vector start);
void		finish_gnl(int fd);
int			dice_i(int dice);
int			index_dice(int i);
void		get_prefab_stat(t_data *data, t_entity *prefab, char *directory);
t_bool		has_dice(t_dice dice);
t_property	get_property(t_data *data, char *name);
void		next_turn(t_data *data);
void		enter_combat(t_data *data, t_entity *entity);
void		show_end_turn_button(t_data *data);
void		check_click_end_turn(t_data *data, t_vector mouse);
int			get_dice_average(t_dice dice);
t_bool		check_action_cost(t_spellinfo *spell);
void		move_closest_to(t_data *data, t_entity *entity, t_entity *target);
t_bool		get_best_spell_pos(t_data *data, t_spellinfo *spell, t_entity *caster);
t_bool		has_obstacle_pos(t_data *data, t_vector from, t_vector to);
t_entity	*get_closest_target(t_data *data, t_entity *entity);
void		compare_buttons(t_data *data, t_button **current_best,
			t_button *compare, t_entity *entity);
t_button	*get_best_action(t_data *data, t_entity *entity, int min_range,
			t_spelltype type);
void		init_textures(t_data *data);
void		init_mlx_events(t_data *data);
t_impact	*found_wall(t_impact *impact, t_vectorf length);
void		change_pos(t_data *data, t_vectorf *offset, float angle);
void		change_pos_collide(t_data *data, t_vector pos, t_vectorf *offset,
				float angle);
void		draw_rectangle(t_data *data, t_vector start, t_vector end,
			uint32_t color);
void		leave_party(t_data *data, t_entity *entity);
bool		prep_map(t_data *data, int fd, t_map *level);
bool		format_test(char *name);
bool		create_color(char color[9], char *code);
bool		process_first_infos(t_data *data, char *lines[7]);
bool		is_map_closed(char **map);
bool		check_char(char **map, t_vector i, t_data *data, t_map *level);
char		**get_map_infos(t_data *data, int fd, t_map *level);
void		set_up_data(t_data *data, t_cell *cell, t_vector it, char **map);
bool		special_atoi(char *str, int *res);
void		get_hexa(char hexa[2], int value);
void		draw_wall(t_data *data, int x, t_vector pos, t_impact *ray);
void		show_floor(t_data *data);
void		show_ceiling(t_data *data);
void		skybox(t_data *data, t_skybox *s);
void		free_button_lst(t_data *data);
void		pop_free_property(t_data *data, t_timer_property *prop);
void		break_concentration(t_data *data, t_entity *entity, int id_concentration);
void		add_cell_property_entity(t_data *data, t_entity *entity);
void		set_entity_dialog(t_entity *entity, char *str);
t_button	*get_button_pointer(t_button *tab, char *name);
void		draw_other_inventory(t_data *data, t_entity *inventory[INVENTORY_SIZE]);
void		show_other_inventory(t_data *data);
void		open_door_pos(t_data *data, t_vector pos);
t_bool		in_party(t_data *data, t_entity *entity);
void		init_game(t_data *data);
t_map		*get_map_pointer(t_data *data, char *name);
uint32_t	average_filter(uint32_t color1, uint32_t color2);
void		entity_filter(t_entity *entity, uint32_t color);
float		get_distf(t_vectorf p1, t_vectorf p2);
void		smooth_possess(t_data *data, t_entity *entity);
void		add_prop_refresh(t_data *data, t_entity *entity, t_property prop);
void		long_rest(t_data *data, t_entity *entity);
int			class_bonus_dmg(t_entity *entity);
int			advantage(t_entity *caster, t_entity *target);
void		level_up_party(t_data *data);
void		reset_active_button(t_data *data);
void		damage_cell(t_data *data, t_vector pos, int nb);
int			roll_atk(t_data *data, t_spellinfo *spell, int atk_bonus);
void		atk_dmg(t_data *data, t_spellinfo *spell, int atk, int rand_res);
char		*stat_to_str(int stat);
t_bool		saving_throw(t_data *data, t_entity *entity, int stat, int dc);
t_bool		remove_specific_prop(t_data *data, t_entity *entity, t_property property);
void		zone_effect_cell(t_data *data, t_spellinfo *spel,
	void (*ef)(t_data *data, t_spellinfo *spel, t_cell *cell));
void		start_turn_effect(t_data *data, t_entity *entity);
void		sort_fog(t_data *data, t_impact *ray, float fog_length);
void		draw_fog(t_data *data, float diff, t_fog *fog);
void		draw_entities_fog(t_data *data, float diff);
t_bool		targetable(t_entity *caster, t_entity *target);
t_bool		dont_draw(t_data *data, t_entity *entity);
int			add_concentration(t_data *data, t_entity *entity);
void		heal_entity(t_data *data, t_entity *entity, int heal);
void		join_party(t_data *data, t_entity *entity);

//ia
void		base_aggro(void *data_param, void *entity_param);
void		martial_ia(void *data_param, void *entity_param);
void		projectile_ia(void *data_param, void *entity_param);

//spells
void		init_button_lst(t_data *data);
void		(*get_button(t_data *data, char *name))(t_data *data, t_button *button);

void		action_select(void *data_param, void *entity_param, t_spellinfo spell);
void		zone_effect(t_data *data, t_spellinfo spell, void (*effect)(void *data, t_entity *target, t_entity *caster, int nb));

void		take(void *data_param, void *spell_param);
void		talk(void *data_param, void *spell_param);

void		init_atk_button(t_data *data, t_button *button, t_entity *entity);

void		init_check_button(t_data *data, t_button *button);
void		init_move_button(t_data *data, t_button *button);
void		init_interact_button(t_data *data, t_button *button);
void		init_inventory_button(t_data *data, t_button *button);

void		init_fireball_button(t_data *data, t_button *button);
void		fireball(void *data_param, void *spell_param);

void		init_rage_button(t_data *data, t_button *button);
void		init_reckless_button(t_data *data, t_button *button);
void		init_man_throw_button(t_data *data, t_button *button);
void		man_throw_select(void *data_param, void *entity_param,
			t_spellinfo spell);

void		init_eldritch_blast_button(t_data *data, t_button *button);
void		init_hellish_rebuke_button(t_data *data, t_button *button);
void		hellish_rebuke_effect(t_data *data, t_entity *caster, t_entity *hitter);

void		init_acid_puddle_button(t_data *data, t_button *button);
void		acid_puddle_dmg(t_data *data, t_entity *entity);

void		init_darkness_button(t_data *data, t_button *button);

void		init_misty_step_button(t_data *data, t_button *button);

void		init_shadow_sword_button(t_data *data, t_button *button);
void		init_shadow_sword(t_data *data, t_button *button, t_entity *entity);

void		init_hadar_button(t_data *data, t_button *button);
void		hunger_of_hadar_dmg(t_data *data, t_entity *entity);

void		init_blight_button(t_data *data, t_button *button);
void		init_banishment_button(t_data *data, t_button *button);

void		init_fire_bolt_button(t_data *data, t_button *button);
void		init_healing_word_button(t_data *data, t_button *button);

void		init_web_button(t_data *data, t_button *button);
void		web_effect(t_data *data, t_entity *entity);

void		init_hold_person_button(t_data *data, t_button *button);

void		init_trapdoor_button(t_data *data, t_button *button);
	
void		init_group_invi_button(t_data *data, t_button *button);

void		init_hypnotic_button(t_data *data, t_button *button);

void		init_dominate_button(t_data *data, t_button *button);

#endif
