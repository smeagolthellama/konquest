/*
    Copyright 2003 Russell Steffen <rsteffen@bayarea.net>
    Copyright 2003 Stephan Zehetner <s.zehetner@nevox.org>
    Copyright 2006 Dmitry Suzdalev <dimsuz@gmail.com>
    Copyright 2006 Inge Wallin <inge@lysator.liu.se>
    Copyright 2006 Pierre Ducroquet <pinaraf@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "fleet.h"
#include "planet.h"

//---------------------------------------------------------------------------
// class Fleet
//   \---class AttackFleet
//    \---class DefenseFleet
//---------------------------------------------------------------------------


Fleet::Fleet( long long initialShipCount )
  : m_shipCount( initialShipCount )
{
}

void
Fleet::removeShips( long long lostShips )
{
    m_shipCount -= lostShips;
}

AttackFleet::AttackFleet( Planet *src, Planet *dest, long long initialCount, int arrival )
: Fleet( initialCount ), owner( src->player() ), source( src ), destination( dest ), arrivalTurn( arrival )
{
}

DefenseFleet::DefenseFleet( Planet *newHome, long long initialCount ) : Fleet( initialCount ), home( newHome )
{
}

void
DefenseFleet::absorb( AttackFleet *fleet )
{
    m_shipCount += fleet->shipCount();
}

void
DefenseFleet::become( AttackFleet *fleet )
{
    m_shipCount = fleet->shipCount();
}


AttackFleet *
DefenseFleet::spawnAttackFleet( Planet *dest, long long count, int arrivalTurn )
{
    if( m_shipCount < count ) {
        return NULL;
    }

    AttackFleet *newFleet = new AttackFleet( home, dest, count, arrivalTurn  );

    removeShips( count );

    emit update();
    
    return newFleet;
}

void
DefenseFleet::addShips( long long newShips )
{
    m_shipCount += newShips;

    if(m_shipCount < 0) /* to allow for negative production planets */
        m_shipCount = 0;
}

