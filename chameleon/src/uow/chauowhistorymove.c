/*
   File:    chauowhistorymove.c
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

#include "chauowhistorymove.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_ALL
#define CAT_LOG_CLAZZ "ChaUowHistoryMove"
#include <logging/catlog.h>

struct _ChaUowHistoryMovePrivate {
	gboolean forward;
};

G_DEFINE_TYPE_WITH_CODE(ChaUowHistoryMove, cha_uow_history_move, CHA_TYPE_UOW,  // @suppress("Unused static function")
	G_ADD_PRIVATE(ChaUowHistoryMove)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);
static void l_uow_run(ChaUow *self, struct _ChaEditor *editor, ChaDocumentView *document_view);

static void cha_uow_history_move_class_init(ChaUowHistoryMoveClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;


	ChaUowClass *uow_class = CHA_UOW_CLASS(clazz);
	uow_class->run = l_uow_run;
}

static void cha_uow_history_move_init(ChaUowHistoryMove *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
//	ChaUowHistoryMove *instance = CHA_UOW_HISTORY_MOVE(object);
//	ChaUowHistoryMovePrivate *priv = cha_uow_history_move_get_instance_private(instance);
	G_OBJECT_CLASS(cha_uow_history_move_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(cha_uow_history_move_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


ChaUowHistoryMove *cha_uow_history_move_new(gboolean forward) {
	ChaUowHistoryMove *result = g_object_new(CHA_TYPE_UOW_HISTORY_MOVE, NULL);
	cat_ref_anounce(result);
	ChaUowHistoryMovePrivate *priv = cha_uow_history_move_get_instance_private(result);
	cha_uow_construct((ChaUow *) result, FALSE);
	priv->forward = forward;
	return result;
}

static void l_uow_run(ChaUow *self, struct _ChaEditor *editor, ChaDocumentView *document_view) {
	ChaUowHistoryMovePrivate *priv = cha_uow_history_move_get_instance_private(CHA_UOW_HISTORY_MOVE(self));
	ChaDocument *document = cha_document_view_get_document(document_view);

	cha_document_view_remove_selection(document_view);

	if (priv->forward) {
		cha_document_history_forward(document);
	} else {
		cha_document_history_back(document);
	}
	cha_document_view_move_view_to_focus(document_view, TRUE);
}
