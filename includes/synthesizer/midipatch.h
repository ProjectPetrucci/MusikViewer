//Copyright (C) 2018 Michail Montesatnos <musikviewer@imslp.org>
//=============================================================================
//  MusE Score
//  Linux Music Score Editor
//  $Id: synti.h 4917 2011-10-29 13:30:40Z wschweer $
//
//  Copyright (C) 2011 Werner Schweer and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================

#ifndef __MIDIPATCH_H__
#define __MIDIPATCH_H__

namespace Ms {

//---------------------------------------------------------
//   MidiPatch
//---------------------------------------------------------

struct MidiPatch {
      bool drum;
      QString synti;
      int bank, prog;
      QString name;
      };

}
#endif

