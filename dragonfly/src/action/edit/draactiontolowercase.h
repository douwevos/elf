/*
   File:    draactiontolowercase.h
   Project: dragonfly
   Author:  Douwe Vos
   Date:    Oct 13, 2015
   e-mail:  dmvos2000(at)yahoo.com

   Copyright (C) 2015 Douwe Vos.

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

#ifndef ACTION_EDIT_DRAACTIONTOLOWERCASE_H_
#define ACTION_EDIT_DRAACTIONTOLOWERCASE_H_

#include "../../draeditorpanel.h"
#include <leafhopper.h>
#include <caterpillar.h>

G_BEGIN_DECLS

#define DRA_TYPE_ACTION_TO_LOWER_CASE              (dra_action_to_lower_case_get_type())
#define DRA_ACTION_TO_LOWER_CASE(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), dra_action_to_lower_case_get_type(), DraActionToLowerCase))
#define DRA_ACTION_TO_LOWER_CASE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), DRA_TYPE_ACTION_TO_LOWER_CASE, DraActionToLowerCaseClass))
#define DRA_IS_ACTION_TO_LOWER_CASE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DRA_TYPE_ACTION_TO_LOWER_CASE))
#define DRA_IS_ACTION_TO_LOWER_CASE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), DRA_TYPE_ACTION_TO_LOWER_CASE))
#define DRA_ACTION_TO_LOWER_CASE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), DRA_TYPE_ACTION_TO_LOWER_CASE, DraActionToLowerCaseClass))


typedef struct _DraActionToLowerCase               DraActionToLowerCase;
typedef struct _DraActionToLowerCasePrivate        DraActionToLowerCasePrivate;
typedef struct _DraActionToLowerCaseClass          DraActionToLowerCaseClass;


struct _DraActionToLowerCase {
	LeaAction parent;
};

struct _DraActionToLowerCaseClass {
	LeaActionClass parent_class;
};


GType dra_action_to_lower_case_get_type();

DraActionToLowerCase *dra_action_to_lower_case_new();

void dra_action_to_lower_case_set_editor_panel(DraActionToLowerCase *action, DraEditorPanel *editor_panel);

G_END_DECLS

#endif /* ACTION_EDIT_DRAACTIONTOLOWERCASE_H_ */
