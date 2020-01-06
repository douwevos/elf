/*
   File:    draformatprogram.c
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

#include "draformatprogram.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_ALL
#define CAT_LOG_CLAZZ "DraFormatProgram"
#include <logging/catlog.h>

struct _DraFormatProgramPrivate {
	CatArrayWo *entries;
};

G_DEFINE_TYPE_WITH_CODE(DraFormatProgram, dra_format_program, G_TYPE_OBJECT,  // @suppress("Unused static function")
	G_ADD_PRIVATE(DraFormatProgram)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void dra_format_program_class_init(DraFormatProgramClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void dra_format_program_init(DraFormatProgram *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
//	DraFormatProgram *instance = DRA_FORMAT_PROGRAM(object);
//	DraFormatProgramPrivate *priv = dra_format_program_get_instance_private(instance);
	G_OBJECT_CLASS(dra_format_program_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(dra_format_program_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


DraFormatProgram *dra_format_program_new() {
	DraFormatProgram *result = g_object_new(DRA_TYPE_FORMAT_PROGRAM, NULL);
	cat_ref_anounce(result);
	DraFormatProgramPrivate *priv = dra_format_program_get_instance_private(result);
	priv->entries = cat_array_wo_new();
	return result;
}

void dra_format_program_add(DraFormatProgram *program, DraFormatAction *action) {
	DraFormatProgramPrivate *priv = dra_format_program_get_instance_private(program);
	cat_array_wo_append(priv->entries, (GObject *) action);
}

void dra_format_program_apply(DraFormatProgram *program, ChaRevisionWo *e_revision) {
	DraFormatProgramPrivate *priv = dra_format_program_get_instance_private(program);

	int indent = 0;
	int out_row = 0;
	int out_column = 0;
	int out_offset = 0;

	gboolean done = FALSE;


	ChaLineEnd line_end = cha_revision_wo_get_line_ends(e_revision);
	if (line_end == CHA_LINE_END_NONE) {
		line_end = CHA_LINE_END_LF;
	}
	CatStringWo *empty_str = cat_string_wo_new_anchored("", 0);
	int count = cat_array_wo_size(priv->entries);
	int row = 0;
	int column = 0;
	int page_index;

	for(int idx=0; idx<count; idx++) {
		DraFormatAction *action = (DraFormatAction *) cat_array_wo_get(priv->entries, idx);
		cat_log_debug("idx=%d, action=%O", idx, action);

		DraFormatLocation in_left = dra_format_action_get_in_left(action);
		DraFormatLocation in_right = dra_format_action_get_in_right(action);

		ChaCursorMWo *sOne = cha_cursorm_wo_new(in_left.row, in_left.offset);
		ChaCursorMWo *sTwo = cha_cursorm_wo_new(in_right.row, in_right.offset);

		if (in_left.offset!=in_right.offset || in_left.row!=in_right.row) {
			cat_log_debug("removing between %O and %O, line-count=%ld", sOne, sTwo, cha_revision_wo_count_lines(e_revision));
			cha_revision_wo_remove_between_cursors(e_revision, sOne, sTwo, TRUE, NULL);
			cat_log_debug("finished remove");
		}

		DraFormatLocation out_left = dra_format_action_get_out_left(action);
		DraFormatLocation out_right = dra_format_action_get_out_right(action);


		CatArrayWo *lines_to_insert = cat_array_wo_new();
		long long ro = out_left.row;
		while(ro<out_right.row) {
			ChaLineWo *empty_line = cha_line_wo_new_anchored(cat_ref_ptr(empty_str), line_end);
			cat_array_wo_append(lines_to_insert, (GObject *) empty_line);
			ro++;
			cat_unref_ptr(empty_line);
		}

		int space_count = 0;
		if (out_left.row==out_right.row) {
			space_count = out_right.offset- out_left.offset;
		} else {
			space_count = out_right.offset;
		}

		CatStringWo *sl = cat_string_wo_new();
		while(space_count>0) {
			cat_log_trace("space_count=%d", space_count);
			if (space_count>=4) {
				cat_string_wo_append_chars_len(sl, "    ", 4);
				space_count-=4;
			} else {
				cat_string_wo_append_chars_len(sl, "    ", space_count);
				space_count = 0;
			}
		}
		ChaLineWo *sl_line = cha_line_wo_new_anchored(sl, CHA_LINE_END_NONE);
		cat_array_wo_append(lines_to_insert, (GObject *) sl_line);
		cat_unref_ptr(sl_line);

		cha_revision_wo_insert_lines(e_revision, sOne, lines_to_insert, TRUE);
		cat_unref_ptr(lines_to_insert);
		cat_unref_ptr(sOne);
		cat_unref_ptr(sTwo);
	}

	cat_log_debug("done");

	ChaCursorWo *eco = cha_cursor_wo_new();
	cha_revision_wo_set_cursor(e_revision, eco);
	cat_unref_ptr(eco);
	cat_unref_ptr(empty_str);


//		if (mtoken_out_ahead!=NULL) {
//
//			ChaCursorMWo *sOne = cha_cursorm_wo_new(mtoken_in->end_row, mtoken_in->end_offset);
//			ChaCursorMWo *sTwo = cha_cursorm_wo_new(mtoken_in_ahead->start_row, mtoken_in_ahead->start_offset);

//
//			CatArrayWo *lines_to_insert = cat_array_wo_new();
//			long long ro = mtoken_out->end_row;
//			while(ro<mtoken_out_ahead->start_row) {
//				ChaLineWo *empty_line = cha_line_wo_new_anchored(cat_ref_ptr(empty_str), line_end);
//				cat_array_wo_append(lines_to_insert, (GObject *) empty_line);
//				ro++;
//				cat_unref_ptr(empty_line);
//			}
//
//			int space_count = 0;
//			if (mtoken_out->end_row==mtoken_out_ahead->start_row) {
//				space_count = mtoken_out_ahead->start_column - mtoken_out->end_column;
//			} else {
//				space_count = mtoken_out_ahead->start_column;
//			}
//
//			CatStringWo *sl = cat_string_wo_new();
//			while(space_count>0) {
//				cat_log_trace("space_count=%d", space_count);
//				if (space_count>=4) {
//					cat_string_wo_append_chars_len(sl, "    ", 4);
//					space_count-=4;
//				} else {
//					cat_string_wo_append_chars_len(sl, "    ", space_count);
//					space_count = 0;
//				}
//			}
//			ChaLineWo *sl_line = cha_line_wo_new_anchored(sl, CHA_LINE_END_NONE);
//			cat_array_wo_append(lines_to_insert, (GObject *) sl_line);
//			cat_unref_ptr(sl_line);
//
//			cha_revision_wo_insert_lines(e_revision, sOne, lines_to_insert, TRUE);
//			cat_unref_ptr(lines_to_insert);
//			cat_unref_ptr(sOne);
//			cat_unref_ptr(sTwo);
//		}
//
//		mtoken_out_ahead = mtoken_out;
//		mtoken_in_ahead = mtoken_in;
//
//	}
//
//	cat_log_debug("done");
//
//	ChaCursorWo *eco = cha_cursor_wo_new();
//	cha_revision_wo_set_cursor(e_revision, eco);
//	cat_unref_ptr(eco);
//
//	cha_document_anchor_document(document);
//
//	cat_unref_ptr(token_out);
//	cat_unref_ptr(token_in);
//
//	cat_unref_ptr(a_revision);
//
//	cat_unref_ptr(empty_str);

}
