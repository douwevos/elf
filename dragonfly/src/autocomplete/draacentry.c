/*
   File:    draacentry.c
   Project: dragonfly
   Author:  Douwe Vos
   Date:    Oct 17, 2015
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

#include "draacentry.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_WARN
#define CAT_LOG_CLAZZ "DraAcEntry"
#include <logging/catlog.h>

struct _DraAcEntryPrivate {
	CatStringWo *entry_text;
	CatStringWo *type_text;
	gboolean enabled;
	int color_code;
	int type_color_code;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(DraAcEntry, dra_ac_entry, G_TYPE_OBJECT,
		G_ADD_PRIVATE(DraAcEntry)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void dra_ac_entry_class_init(DraAcEntryClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void dra_ac_entry_init(DraAcEntry *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
	DraAcEntry *instance = DRA_AC_ENTRY(object);
	DraAcEntryPrivate *priv = dra_ac_entry_get_instance_private(instance);
	cat_unref_ptr(priv->entry_text);
	G_OBJECT_CLASS(dra_ac_entry_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(dra_ac_entry_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


void dra_ac_entry_construct_full(DraAcEntry *entry, CatStringWo *entry_text, CatStringWo *type_text, gboolean enabled, int color_code, int type_color_code) {
	DraAcEntryPrivate *priv = dra_ac_entry_get_instance_private(entry);
	priv->entry_text = cat_string_wo_clone(entry_text, CAT_CLONE_DEPTH_NONE);
	priv->type_text = cat_string_wo_clone(type_text, CAT_CLONE_DEPTH_NONE);
	priv->enabled = enabled;
	priv->color_code = color_code;
	priv->type_color_code = type_color_code;
}


void dra_ac_entry_construct(DraAcEntry *entry, CatStringWo *entry_text) {
	DraAcEntryPrivate *priv = dra_ac_entry_get_instance_private(entry);
	priv->entry_text = cat_string_wo_clone(entry_text, CAT_CLONE_DEPTH_NONE);
	priv->color_code = 0;
	priv->type_text = NULL;
	priv->type_color_code = 0;
	priv->enabled = TRUE;
}

DraAcEntry *dra_ac_entry_new(CatStringWo *entry_text) {
	DraAcEntry *result = g_object_new(DRA_TYPE_AC_ENTRY, NULL);
	cat_ref_anounce(result);
	dra_ac_entry_construct(result, entry_text);
	return result;
}


CatStringWo *dra_ac_entry_get_filter_text(DraAcEntry *entry) {
	DraAcEntryPrivate *priv = dra_ac_entry_get_instance_private(entry);
	return priv->entry_text;
}

static void l_apply_pango_color_code(PangoAttrList *pango_attrs, int start_index, int end_index, int color_code, gboolean enabled, gboolean selected) {
	PangoAttribute *attr_color;
	if (enabled || selected) {
		if (color_code>7) {
			color_code = color_code & 0x7;
			PangoAttribute *attr_bold = pango_attr_weight_new(PANGO_WEIGHT_SEMIBOLD);
			attr_bold->start_index = start_index;
			attr_bold->end_index = end_index;
			pango_attr_list_change(pango_attrs, attr_bold);
		}

		if (selected) {
			attr_color = pango_attr_foreground_new(0xFFFF,0xFFFF,0xFFFF);
		} else {
			switch(color_code) {
				case 0 : attr_color = pango_attr_foreground_new(0,0,0); break;
				case 1 : attr_color = pango_attr_foreground_new(0,0,0xDDDD); break;
				case 2 : attr_color = pango_attr_foreground_new(0,0xDDDD,0x0); break;
				case 3 : attr_color = pango_attr_foreground_new(0,0x7777,0x7777); break;
				case 4 : attr_color = pango_attr_foreground_new(0xDDDD,0x0,0x0); break;
				case 5 : attr_color = pango_attr_foreground_new(0x7777,0x0,0x7777); break;
				case 6 : attr_color = pango_attr_foreground_new(0x7777,0x7777,0x0); break;
				case 7 : attr_color = pango_attr_foreground_new(0x5555,0x5555,0x5555); break;
			}
		}
	} else {
		attr_color = pango_attr_foreground_new(0xAAAA,0xAAAA,0xAAAA);
	}
	attr_color->start_index = start_index;
	attr_color->end_index = end_index;
	pango_attr_list_change(pango_attrs, attr_color);
}

static void l_setup_pango(DraAcEntryPrivate *priv, PangoLayout *pango_layout, gboolean selected) {
	PangoAttrList *pango_attrs = pango_attr_list_new();

	PangoAttribute *pango_attr = pango_attr_foreground_new(0,0,0);
	pango_attr->start_index = 0;
	pango_attr->end_index = 100000;
	pango_attr_list_insert(pango_attrs, pango_attr);


	CatStringWo *full = NULL;
	const char *pango_text;
	int pango_text_len;
	if (priv->type_text) {
		full = cat_string_wo_new();
		cat_string_wo_append(full, priv->entry_text);
		cat_string_wo_append_chars_len(full, " : ", 3);
		cat_string_wo_append(full, priv->type_text);
		pango_text = cat_string_wo_getchars(full);
		pango_text_len = cat_string_wo_length(full);

		int colon_start = cat_string_wo_length(priv->entry_text);
		int type_start = colon_start+3;

		PangoAttribute *attr_for_colon = pango_attr_foreground_new(0xAAAA, 0xAAAA, 0xAAAA);
		attr_for_colon->start_index = colon_start;
		attr_for_colon->end_index = type_start;
		pango_attr_list_change(pango_attrs, attr_for_colon);

		l_apply_pango_color_code(pango_attrs, 0, colon_start, priv->color_code, priv->enabled, selected);
		l_apply_pango_color_code(pango_attrs, type_start, pango_text_len, priv->type_color_code, priv->enabled, selected);

	} else {
		pango_text = cat_string_wo_getchars(priv->entry_text);
		pango_text_len = cat_string_wo_length(priv->entry_text);
		l_apply_pango_color_code(pango_attrs, 0, pango_text_len, priv->color_code, priv->enabled, selected);
	}


	pango_layout_set_text(pango_layout, pango_text, pango_text_len);
	pango_layout_set_attributes(pango_layout, pango_attrs);
	pango_attr_list_unref(pango_attrs);
	cat_unref_ptr(full);
}

int dra_ac_entry_get_width(DraAcEntry *entry, PangoLayout *pango_layout) {
	DraAcEntryPrivate *priv = dra_ac_entry_get_instance_private(entry);
	l_setup_pango(priv, pango_layout, TRUE);
	PangoRectangle ink_rect;
	PangoRectangle logical_rect;
	pango_layout_get_pixel_extents(pango_layout, &ink_rect, &logical_rect);
	return logical_rect.width;
}

void dra_ac_entry_paint(DraAcEntry *entry, GtkWidget *widget, cairo_t *cairo, PangoLayout *pango_layout, int ypos, int entry_height, gboolean selected) {
	DraAcEntryPrivate *priv = dra_ac_entry_get_instance_private(entry);

	int width = gtk_widget_get_allocated_width(widget);

	if (selected) {
//		cairo_set_source_rgb(cairo, 0, 0, 0.2);
//		cairo_rectangle(cairo, 0,ypos,width,entry_height);
//		cairo_stroke(cairo);

		GtkStyleContext *w_style_ctx = gtk_widget_get_style_context(widget);
		gtk_style_context_save(w_style_ctx);
		gtk_style_context_set_state(w_style_ctx, GTK_STATE_FLAG_SELECTED);
		gtk_render_background(w_style_ctx, cairo, 0, ypos, width, entry_height);
		gtk_style_context_restore(w_style_ctx);

	} else {
//		cairo_rectangle(cairo, 0,ypos,width,entry_height);
//		cairo_fill(cairo);
	}

	const char *pango_text = cat_string_wo_getchars(priv->entry_text);
	int pango_text_len = cat_string_wo_length(priv->entry_text);

	cairo_set_source_rgb(cairo, 0, 0, 0.2);
	pango_cairo_update_layout(cairo, pango_layout);

	l_setup_pango(priv, pango_layout, selected);

	cairo_move_to(cairo, 0, ypos);
	pango_cairo_show_layout(cairo, pango_layout);
}

void dra_ac_entry_run(DraAcEntry *entry, struct _DraAcContext *ac_context) {
	DraAcEntryClass *entry_class = DRA_AC_ENTRY_GET_CLASS(entry);
	entry_class->run(entry, ac_context);

}

/********************* start CatIStringable implementation *********************/

static void l_stringable_print(CatIStringable *self, struct _CatStringWo *append_to) {
	DraAcEntry *instance = DRA_AC_ENTRY(self);
	DraAcEntryPrivate *priv = dra_ac_entry_get_instance_private(instance);
	const char *iname = g_type_name_from_instance((GTypeInstance *) self);

	cat_string_wo_format(append_to, "%s[%p entry_text=%o]", iname, self, priv->entry_text);
}

static void l_stringable_iface_init(CatIStringableInterface *iface) {
	iface->print = l_stringable_print;
}

/********************* end CatIStringable implementation *********************/
