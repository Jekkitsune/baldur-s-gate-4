/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prefabs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:33:13 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 13:33:32 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_prefabs2(t_data *data)
{
	init_one_prefab(data, "prefabs/bow+2", "bow+2");
	init_one_prefab(data, "prefabs/bow+3", "bow+3");
	init_one_prefab(data, "prefabs/dagger+1", "dagger+1");
	init_one_prefab(data, "prefabs/dagger+2", "dagger+2");
	init_one_prefab(data, "prefabs/dagger+3", "dagger+3");
	init_one_prefab(data, "prefabs/staff+1", "staff+1");
	init_one_prefab(data, "prefabs/staff+2", "staff+2");
	init_one_prefab(data, "prefabs/staff+3", "staff+3");
	init_one_prefab(data, "prefabs/helm of intellect", "helm of intellect");
	init_one_prefab(data, "prefabs/stylish hat", "stylish hat");
	init_one_prefab(data, "prefabs/dexterity gloves", "dexterity gloves");
	init_one_prefab(data, "prefabs/strength gloves", "strength gloves");
	init_one_prefab(data, "prefabs/cloth of wisdom", "cloth of wisdom");
	init_one_prefab(data, "prefabs/velocity boots", "velocity boots");
	init_one_prefab(data, "prefabs/bracers of defense", "bracers of defense");
	init_one_prefab(data, "prefabs/acid gloves", "acid gloves");
	init_one_prefab(data, "prefabs/gigantic helm", "gigantic helm");
	init_one_prefab(data, "prefabs/giver", "giver");
	init_one_prefab(data, "prefabs/merchant", "merchant");
	init_one_prefab(data, "prefabs/tree", "tree");
	init_one_prefab(data, "prefabs/tavern", "tavern");
	init_one_prefab(data, "prefabs/gobelin king", "gobelin king");
	init_one_prefab(data, "prefabs/gobelin princess", "gobelin princess");
	init_one_prefab(data, "prefabs/dungeon key", "dungeon key");
	init_one_prefab(data, "prefabs/boss", "boss");
}

void	init_prefabs3(t_data *data)
{
	init_one_prefab(data, "prefabs/speed potion", "speed potion");
	init_one_prefab(data, "prefabs/enlarge potion", "enlarge potion");
	init_one_prefab(data, "prefabs/armor+1", "armor+1");
	init_one_prefab(data, "prefabs/armor+2", "armor+2");
	init_one_prefab(data, "prefabs/armor+3", "armor+3");
	init_one_prefab(data, "prefabs/sword+1", "sword+1");
	init_one_prefab(data, "prefabs/sword+2", "sword+2");
	init_one_prefab(data, "prefabs/sword+3", "sword+3");
	init_one_prefab(data, "prefabs/bow+1", "bow+1");
	init_one_prefab(data, "prefabs/boss key", "boss key");
	init_prefabs2(data);
}

void	init_prefabs(t_data *data)
{
	init_one_prefab(data, "prefabs/warlock", "warlock");
	init_one_prefab(data, "prefabs/wizard", "wizard");
	init_one_prefab(data, "prefabs/barbarian", "barbarian");
	init_one_prefab(data, "prefabs/rogue", "rogue");
	init_one_prefab(data, "prefabs/ranger", "ranger");
	init_one_prefab(data, "prefabs/monk", "monk");
	init_one_prefab(data, "prefabs/gobelin", "gobelin");
	init_one_prefab(data, "prefabs/gold", "gold");
	init_one_prefab(data, "prefabs/gobelin barbarian", "gobelin barbarian");
	init_one_prefab(data, "prefabs/gobelin rogue", "gobelin rogue");
	init_one_prefab(data, "prefabs/gobelin ranger", "gobelin ranger");
	init_one_prefab(data, "prefabs/gobelin warlock", "gobelin warlock");
	init_one_prefab(data, "prefabs/gobelin wizard", "gobelin wizard");
	init_one_prefab(data, "prefabs/amogus", "amogus");
	init_one_prefab(data, "prefabs/healing potion", "healing potion");
	init_one_prefab(data, "prefabs/greater healing potion",
		"greater healing potion");
	init_prefabs3(data);
}
