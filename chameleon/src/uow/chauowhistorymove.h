/*
   File:    chauowhistorymove.h
   Project: chameleon
   Author:  Douwe Vos
   Date:    Dec 29, 2019
   e-mail:  dmvos2000(at)yahoo.com

   Copyright (C) 2019 Douwe Vos.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef CHAUOWHISTORYMOVE_H_
#define CHAUOWHISTORYMOVE_H_

#include "chauow.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define CHA_TYPE_UOW_HISTORY_MOVE              (cha_uow_history_move_get_type())
#define CHA_UOW_HISTORY_MOVE(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), cha_uow_history_move_get_type(), ChaUowHistoryMove))
#define CHA_UOW_HISTORY_MOVE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), CHA_TYPE_UOW_HISTORY_MOVE, ChaUowHistoryMoveClass))
#define CHA_IS_UOW_HISTORY_MOVE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CHA_TYPE_UOW_HISTORY_MOVE))
#define CHA_IS_UOW_HISTORY_MOVE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), CHA_TYPE_UOW_HISTORY_MOVE))
#define CHA_UOW_HISTORY_MOVE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), CHA_TYPE_UOW_HISTORY_MOVE, ChaUowHistoryMoveClass))

struct _ChaUowHistoryMove {
	ChaUow parent;
};

struct _ChaUowHistoryMoveClass {
	ChaUowClass parent_class;
};

typedef struct _ChaUowHistoryMove               ChaUowHistoryMove;
typedef struct _ChaUowHistoryMovePrivate        ChaUowHistoryMovePrivate;
typedef struct _ChaUowHistoryMoveClass          ChaUowHistoryMoveClass;


GType cha_uow_history_move_get_type();

ChaUowHistoryMove *cha_uow_history_move_new(gboolean forward);

G_END_DECLS

#endif /* CHAUOWHISTORYMOVE_H_ */
