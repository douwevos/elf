/*
   File:    chauownextformfield.c
   Project: chameleon
   Author:  Douwe Vos
   Date:    Oct 14, 2015
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

#include "chauownextformfield.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_WARN
#define CAT_LOG_CLAZZ "ChaUowNextFormField"
#include <logging/catlog.h>

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(ChaUowNextFormField, cha_uow_next_form_field, CHA_TYPE_UOW,
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);
static void l_uow_run(ChaUow *self, struct _ChaEditor *editor, ChaDocumentView *document_view);

static void cha_uow_next_form_field_class_init(ChaUowNextFormFieldClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;

	ChaUowClass *uow_class = CHA_UOW_CLASS(clazz);
	uow_class->run = l_uow_run;
}

static void cha_uow_next_form_field_init(ChaUowNextFormField *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
//	ChaUowNextFormField *instance = CHA_UOW_NEXT_FORM_FIELD(object);
	G_OBJECT_CLASS(cha_uow_next_form_field_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(cha_uow_next_form_field_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


ChaUowNextFormField *cha_uow_next_form_field_new() {
	ChaUowNextFormField *result = g_object_new(CHA_TYPE_UOW_NEXT_FORM_FIELD, NULL);
	cat_ref_anounce(result);
	cha_uow_construct((ChaUow *) result, TRUE);
	return result;
}


gboolean cha_uow_next_form_field_run(ChaUowNextFormField *next_ff, ChaDocumentView *document_view) {
	gboolean result = FALSE;

	ChaDocument *document = cha_document_view_get_document(document_view);
	gboolean is_editable = cha_document_is_editable(document);
	ChaRevisionWo *e_revision = cha_document_get_editable_revision(document);

	ChaCursorWo *cursor = cha_revision_wo_get_cursor(e_revision);
	ChaCursorMWo *mcursor = cha_revision_wo_to_cursorm(e_revision, cursor);

	ChaFormWo *form = cha_revision_wo_get_form(e_revision);
	if (form) {
		int index = cha_form_wo_get_index_of_field_at_location(form, mcursor);
		int next_index = -1;
		if (index<0) {
			next_index = cha_form_wo_get_index_of_field_following_location(form, mcursor);
		} else {
			next_index = cha_form_wo_get_index_of_next_field(form, index);
		}

		cat_log_error("index=%d, next_index=%d", index, next_index);
		if (next_index>=0) {
			ChaFormFieldWo *field = cha_form_wo_get_at(form, next_index);
			ChaCursorMWo *cursor_s = cha_form_field_wo_get_start(field);
			ChaCursorMWo *cursor_e = cha_form_field_wo_get_end(field);

			ChaLineLocationWo *nll = cha_revision_wo_calculate_line_location(e_revision, cha_cursorm_wo_get_row(cursor_s));
			ChaCursorWo *cur_start = cha_cursor_wo_new_ll_offset(nll, cha_cursorm_wo_get_column(cursor_s));
			cat_unref_ptr(nll);

			nll = cha_revision_wo_calculate_line_location(e_revision, cha_cursorm_wo_get_row(cursor_e));
			ChaCursorWo *cur_end = cha_cursor_wo_new_ll_offset(nll, cha_cursorm_wo_get_column(cursor_e));
			cat_unref_ptr(nll);

			cat_log_error("cur_start=%o, cur_end=%o", cur_start, cur_end);

			cha_document_view_set_plain_selection(document_view, cur_start, cur_end);
			cha_revision_wo_set_cursor(e_revision, cur_end);
		} else {
			/* close form */
			cha_revision_wo_set_form(e_revision, NULL);
		}
		result = TRUE;
	}

	if (!is_editable) {
		cha_document_anchor_document(document);
		cha_document_view_move_view_to_focus(document_view, FALSE);
	}
	return result;
}



static void l_uow_run(ChaUow *self, struct _ChaEditor *editor, ChaDocumentView *document_view) {
	cha_uow_next_form_field_run(CHA_UOW_NEXT_FORM_FIELD(self), document_view);
}

/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	const char *iname = g_type_name_from_instance((GTypeInstance *) self);

	cat_string_wo_format(append_to, "%s[%p]", iname, self);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
