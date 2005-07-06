//  $Id$
// 
//  SuperTux
//  Copyright (C) 2005 Matthias Braun <matze@braunis.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.

#include <config.h>

#include "bomb.hpp"

static const float TICKINGTIME = 1;
static const float EXPLOSIONTIME = 1;

Bomb::Bomb(const Vector& pos, Direction dir)
{
  start_position = pos;
  bbox.set_pos(pos);
  bbox.set_size(31.8, 31.8);
  sprite = sprite_manager->create("bomb");
  state = 0;
  timer.start(TICKINGTIME);
  this->dir = dir;
  sprite->set_action(dir == LEFT ? "ticking-left" : "ticking-right");
  countMe = false;
}

void
Bomb::write(lisp::Writer& )
{
  // bombs are only temporarily so don't write them out...
}

HitResponse
Bomb::collision_solid(GameObject& , const CollisionHit& hit)
{
  if(fabsf(hit.normal.y) > .5)
    physic.set_velocity_y(0);

  return CONTINUE;
}

HitResponse
Bomb::collision_player(Player& player, const CollisionHit& )
{
  if(state == 1) {
    player.kill(Player::SHRINK);
  }
  return ABORT_MOVE;
}

HitResponse
Bomb::collision_badguy(BadGuy& badguy, const CollisionHit& )
{
  if(state == 1)
    badguy.kill_fall();
  return ABORT_MOVE;
}

void
Bomb::active_update(float )
{
  switch(state) {
    case 0:
      if(timer.check()) {
        explode();
      }
      break;
    case 1:
      if(timer.check()) {
        remove_me();
      }
      break;
  } 
}

void
Bomb::explode()
{
  state = 1;
  sprite->set_action("explosion");
  sound_manager->play("sounds/explosion.ogg", get_pos());
  timer.start(EXPLOSIONTIME);
}

void
Bomb::kill_fall()
{
  if (state != 1)  // we don't want it exploding again
    explode();
}
