/*******************************************************************
 * File automatically generated by rebuild_wrappers.py (v2.5.0.24) *
 *******************************************************************/
#ifndef __wrappedlibharfbuzzTYPES_H_
#define __wrappedlibharfbuzzTYPES_H_

#ifndef LIBNAME
#error You should only #include this file inside a wrapped*.c file
#endif
#ifndef ADDED_FUNCTIONS
#define ADDED_FUNCTIONS() 
#endif

typedef void (*vFp_t)(void*);
typedef void* (*pFp_t)(void*);
typedef void* (*pFpp_t)(void*, void*);
typedef void (*vFppp_t)(void*, void*, void*);
typedef void* (*pFppp_t)(void*, void*, void*);
typedef void (*vFpppp_t)(void*, void*, void*, void*);
typedef int32_t (*iFppppi_t)(void*, void*, void*, void*, int32_t);
typedef void* (*pFpuupp_t)(void*, uint32_t, uint32_t, void*, void*);

#define SUPER() ADDED_FUNCTIONS() \
	GO(hb_draw_funcs_destroy, vFp_t) \
	GO(hb_font_funcs_destroy, vFp_t) \
	GO(hb_unicode_funcs_reference, pFp_t) \
	GO(hb_ft_face_create, pFpp_t) \
	GO(hb_ft_font_create, pFpp_t) \
	GO(hb_font_set_funcs_data, vFppp_t) \
	GO(hb_face_create_for_tables, pFppp_t) \
	GO(hb_buffer_set_message_func, vFpppp_t) \
	GO(hb_draw_funcs_set_close_path_func, vFpppp_t) \
	GO(hb_draw_funcs_set_cubic_to_func, vFpppp_t) \
	GO(hb_draw_funcs_set_line_to_func, vFpppp_t) \
	GO(hb_draw_funcs_set_move_to_func, vFpppp_t) \
	GO(hb_draw_funcs_set_quadratic_to_func, vFpppp_t) \
	GO(hb_font_funcs_set_font_h_extents_func, vFpppp_t) \
	GO(hb_font_funcs_set_font_v_extents_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_contour_point_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_extents_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_from_name_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_h_advance_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_h_advances_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_h_kerning_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_h_origin_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_name_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_shape_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_v_advance_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_v_advances_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_v_kerning_func, vFpppp_t) \
	GO(hb_font_funcs_set_glyph_v_origin_func, vFpppp_t) \
	GO(hb_font_funcs_set_nominal_glyph_func, vFpppp_t) \
	GO(hb_font_funcs_set_nominal_glyphs_func, vFpppp_t) \
	GO(hb_font_funcs_set_variation_glyph_func, vFpppp_t) \
	GO(hb_font_set_funcs, vFpppp_t) \
	GO(hb_unicode_funcs_set_combining_class_func, vFpppp_t) \
	GO(hb_unicode_funcs_set_compose_func, vFpppp_t) \
	GO(hb_unicode_funcs_set_decompose_compatibility_func, vFpppp_t) \
	GO(hb_unicode_funcs_set_decompose_func, vFpppp_t) \
	GO(hb_unicode_funcs_set_eastasian_width_func, vFpppp_t) \
	GO(hb_unicode_funcs_set_general_category_func, vFpppp_t) \
	GO(hb_unicode_funcs_set_mirroring_func, vFpppp_t) \
	GO(hb_unicode_funcs_set_script_func, vFpppp_t) \
	GO(hb_blob_set_user_data, iFppppi_t) \
	GO(hb_buffer_set_user_data, iFppppi_t) \
	GO(hb_face_set_user_data, iFppppi_t) \
	GO(hb_font_funcs_set_user_data, iFppppi_t) \
	GO(hb_font_set_user_data, iFppppi_t) \
	GO(hb_unicode_funcs_set_user_data, iFppppi_t) \
	GO(hb_blob_create, pFpuupp_t) \
	GO(hb_blob_create_or_fail, pFpuupp_t)

#endif // __wrappedlibharfbuzzTYPES_H_
