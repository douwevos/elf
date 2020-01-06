/*
   File:    draformataction.h
   Project: dragonfly
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

#ifndef DRAFORMATACTION_H_
#define DRAFORMATACTION_H_

#include <caterpillar.h>

G_BEGIN_DECLS

#define DRA_TYPE_FORMAT_ACTION              (dra_format_action_get_type())
#define DRA_FORMAT_ACTION(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), dra_format_action_get_type(), DraFormatAction))
#define DRA_FORMAT_ACTION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), DRA_TYPE_FORMAT_ACTION, DraFormatActionClass))
#define DRA_IS_FORMAT_ACTION(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DRA_TYPE_FORMAT_ACTION))
#define DRA_IS_FORMAT_ACTION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), DRA_TYPE_FORMAT_ACTION))
#define DRA_FORMAT_ACTION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), DRA_TYPE_FORMAT_ACTION, DraFormatActionClass))

struct _DraFormatAction {
	GObject parent;
};

struct _DraFormatActionClass {
	GObjectClass parent_class;
};

typedef struct _DraFormatAction               DraFormatAction;
typedef struct _DraFormatActionPrivate        DraFormatActionPrivate;
typedef struct _DraFormatActionClass          DraFormatActionClass;

typedef struct _DraFormatLocation DraFormatLocation;

struct _DraFormatLocation {
	long long row;
	int offset;
};

GType dra_format_action_get_type();

DraFormatAction *dra_format_action_new(DraFormatLocation in_left, DraFormatLocation in_right, DraFormatLocation out_left, DraFormatLocation out_right);

DraFormatLocation dra_format_action_get_in_left(DraFormatAction *action);
DraFormatLocation dra_format_action_get_in_right(DraFormatAction *action);
DraFormatLocation dra_format_action_get_out_left(DraFormatAction *action);
DraFormatLocation dra_format_action_get_out_right(DraFormatAction *action);

G_END_DECLS

#endif /* DRAFORMATACTION_H_ */
