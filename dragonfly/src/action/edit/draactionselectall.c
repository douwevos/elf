/*
   File:    draactionselectall.c
   Project: dragonfly
   Author:  Douwe Vos
   Date:    Jun 20, 2015
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

#include "draactionselectall.h"

#include <chameleon.h>

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_WARN
#define CAT_LOG_CLAZZ "DraActionSelectAll"
#include <logging/catlog.h>

struct _DraActionSelectAllPrivate {
	DraEditorPanel *editor_panel;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(DraActionSelectAll, dra_action_select_all, LEA_TYPE_ACTION,
		G_ADD_PRIVATE(DraActionSelectAll)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);
static void l_action_run(LeaAction *self);

static void dra_action_select_all_class_init(DraActionSelectAllClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;

	LeaActionClass *action_class = LEA_ACTION_CLASS(clazz);
	action_class->action_run = l_action_run;
}

static void dra_action_select_all_init(DraActionSelectAll *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
	DraActionSelectAll *instance = DRA_ACTION_SELECT_ALL(object);
	DraActionSelectAllPrivate *priv = dra_action_select_all_get_instance_private(instance);
	cat_unref_ptr(priv->editor_panel);
	G_OBJECT_CLASS(dra_action_select_all_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(dra_action_select_all_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


DraActionSelectAll *dra_action_select_all_new() {
	DraActionSelectAll *result = g_object_new(DRA_TYPE_ACTION_SELECT_ALL, NULL);
	cat_ref_anounce(result);
	DraActionSelectAllPrivate *priv = dra_action_select_all_get_instance_private(result);
	priv->editor_panel = NULL;
	lea_action_construct((LeaAction *) result, cat_string_wo_new_with("action.select.all"), cat_string_wo_new_with("Select _All"), cat_string_wo_new_with("edit-select-all"));
	lea_action_set_default_key_sequence(LEA_ACTION(result), lea_key_sequence_from_string(cat_string_wo_new_with("Ctrl+A")));
	lea_action_set_sensitive_self(LEA_ACTION(result), FALSE);
	return result;
}



static void l_action_run(LeaAction *self) {
	DraActionSelectAllPrivate *priv = dra_action_select_all_get_instance_private((DraActionSelectAll *) self);
	if (priv->editor_panel) {
		ChaUowSelect *select_uow = cha_uow_select_new(CHA_UOW_SELECT_ALL);
		ChaEditor *editor = (ChaEditor *) dra_editor_panel_get_editor(priv->editor_panel);
		cha_editor_run(editor, (ChaUow *) select_uow);
		cat_unref_ptr(select_uow);
	}
}

void dra_action_select_all_set_editor_panel(DraActionSelectAll *action, DraEditorPanel *editor_panel) {
	DraActionSelectAllPrivate *priv = dra_action_select_all_get_instance_private(action);
	cat_ref_swap(priv->editor_panel, editor_panel);
	lea_action_set_sensitive_self(LEA_ACTION(action), editor_panel!=NULL);
}


/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	DraActionSelectAll *instance = DRA_ACTION_SELECT_ALL(self);
	DraActionSelectAllPrivate *priv = dra_action_select_all_get_instance_private(instance);
	const char *iname = g_type_name_from_instance((GTypeInstance *) self);

	cat_string_wo_format(append_to, "%s[%p editor=%o]", iname, self, priv->editor_panel);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
