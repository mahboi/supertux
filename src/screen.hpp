//  $Id: worldmap.hpp 2800 2005-10-02 22:57:31Z matzebraun $
// 
//  SuperTux
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

class DrawingContext;

class Screen
{
public:
  virtual ~Screen()
  {}

  virtual void setup()
  {}

  virtual void draw(DrawingContext& context) = 0;

  virtual void update(float elapsed_time) = 0;
};

#endif
