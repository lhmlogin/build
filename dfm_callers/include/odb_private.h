/***********************************************************
*
*  Module: odb_private.h
*
*  Description:
*
*  This module contains literals, macros and structures which are required
*  by any program which calls the Genesis odb library and are private and internally used by FLS DFMS.
*
*  Author:		Ronny C.
*
*  (c) Copyright 2009 - Frontline Computerized Systems Ltd.
*
*
* Naming conventions:
*
*    ODB_L*  -- literals
*    ODB_D*  -- variable declarations
*    ODB_M*  -- macros
*    ODB_P*  -- function parameter declarations
***********************************************************/


#ifndef ODB_PUBLIC_OO

#ifndef ODB_PRIVATE_DEF
#define ODB_PRIVATE_DEF

/* IL 14 Jan 2013: For unit tests support:
In the following section, I am duplicating the definitions of ODB_EXPORT and ODB_EXP.
The reason is that they are defined originally in odb.h and this file is always included
before including odb.h .
This will cause the original odb.h definition to complain or if we use ifndef in odb.h,
we may fail in the future in case we update this one and not the original.
To avoid this risk I prefer to do a duplication of the definition and run the risk of
updating the original one and not this one - the lesser risk.*/
#if !defined(ODB_INTERNAL_LIBRARY)

#ifdef WINDOWS_NT
#define ODB_INTERNAL_EXPORT          __declspec(dllexport)
#else
#define ODB_INTERNAL_EXPORT          __attribute__ ((visibility("default")))
#endif
#define ODB_PRIVATE_EXP(name, param) ODB_INTERNAL_EXPORT int name param; int name param

#define _ODB_TEST(id)       ODB_PRIVATE_EXP(id ## _test, (void))

#endif /* ODB_INTERNAL_LIBRARY */


typedef enum {
	INCAM_APPLICATION_TYPE,
	INSIGHT_APPLICATION_TYPE,
	TOUCHCAM_APPLICATION_TYPE,
	INCAM_STANDARD_APPLICATION_TYPE,
} odb_app_type_enum;


typedef enum {
	ODB_TEST_MODEL_TYPE_NONE = 0,
	ODB_TEST_MODEL_TYPE_SE,
	ODB_TEST_MODEL_TYPE_DF,
}odb_imp_test_model_enum;

typedef enum {
	ODB_COPLANAR_NONE = 0, /* Keep first */
	ODB_COPLANAR_WAVEGUIDE,
	ODB_COPLANAR_DUMMY     /* Keep last */
}odb_imp_coplanar_enum;

typedef enum {
	DRILL_DIRECTION_TOP2BOTTOM = 0,
	DRILL_DIRECTION_BOTTOM2TOP = 1,
	DRILL_DIRECTION_ANY = 2,
} odb_drill_direction_type;

typedef enum {
	ODB_LYR_ORIENTATION_NOT_DEFINED = 0,
	ODB_LYR_ORIENTATION_UPWARDS = 1,
	ODB_LYR_ORIENTATION_DOWNWARDS = 2,
	ODB_LYR_ORIENTATION_BOTH = 3, /*Only SM layer exposing 2 copper layers, one above it and one below it, will get this value*/
} odb_layer_orientation_type;


typedef enum {
	ODB_F_PROPERTY_TYPE_BOL = 0,
	ODB_F_PROPERTY_TYPE_INT,
	ODB_F_PROPERTY_TYPE_DOUBLE
} odb_f_property_type;

#define ODB_LEN_NAME 128

typedef struct odb_imp_struc {
	int			    serial;
	odb_imp_test_model_enum tm_type;
	odb_imp_coplanar_enum   coplanar_type;
	char		    test_lyr[ODB_LEN_NAME + 1];
	char		    ref_lyr1[ODB_LEN_NAME + 1];    /* top ref layer (relative to gns matrix) can be empty */
	char		    ref_lyr2[ODB_LEN_NAME + 1];    /* bot ref layer (relative to gns matrix) can be empty */

	int			    lw_art;	/* Real line widths */
	int			    lw_orig;	/* Doc line widths, used only for text composition */
	int			    lw_req;	/* the required line width defined by the planer */

							/* Space between the two lines of a differential model */
	int			    spc_art;
	int			    spc_orig;
	int			    spc_req;
	int			    coplanar_dist;
	double		    imp_val;	/* impedance value defined by the user (in ohms)*/
} odb_imp_struc;

#define ODB_EXT_ACT_TYPE     ODB_ACT_EDT_IMP_LIST			= 1070, \
			     ODB_ACT_EDT_IMP_DATA			= 1071, \
			     ODB_ACT_F_SET_IMP				= 1160, \
			     ODB_ACT_F_RESET_IMP			= 1161, \
			     ODB_ACT_F_IMP_ID				= 1162, \
			     ODB_ACT_F_IMP_ORIG_WIDTH			= 1163, \
			     ODB_ACT_SHAPE_SWITCH_DIST_INFRA		= 1164, \
			     ODB_ACT_RES_CALC_LIST			= 1370, \
			     ODB_ACT_RES_TYPICAL_SIZE_LIST		= 1395, \
			     ODB_ACT_RES_CALC_RANGE_LIST		= 1444, \
			     ODB_ACT_LAYER_GET_ACTIVE_AREA		= 1500, \
			     ODB_ACT_LAYER_GET_VISIBLE_AREA		= 1501, \
			     ODB_ACT_SHAPE_CHANGE_POLY_CORNER_RADIUS	= 1502, \
 		             ODB_ACT_LAYER_FILL_FROM_PATH		= 1503, \
 			     ODB_ACT_F_CHANGE_LIST			= 1504, \
			     ODB_ACT_LAYER_DRILL_DIRECTION		= 1505, \
			     ODB_ACT_FIX_REPLACE_NF			= 1506, \
			     ODB_ACT_F_ADD_LIST				= 1507, \
			     ODB_ACT_F_DELETE_LIST			= 1508, \
			     ODB_ACT_LAYER_STOP_SHAPE_LIST_UPDATE 	= 1509, \
			     ODB_ACT_LAYER_RESUME_SHAPE_LIST_UPDATE 	= 1510, \
			     ODB_ACT_LAYER_IS_EXPOSED			= 1511, \
			     ODB_ACT_LAYER_GET_EXPOSED_AREA_SHAPES	= 1512, \
			     ODB_ACT_LAYER_GET_ORIENTATION		= 1513, \
			     ODB_ACT_LAYER_GET_ATTACHED_LAYERS		= 1514, \
			     ODB_ACT_SHAPE_DIST_TO_CONT                 = 1515, \
			     ODB_ACT_SHAPE_DIST_TO_CONT2		= 1516, \
			     ODB_ACT_F_PROPERTY_SET                     = 1517, \
			     ODB_ACT_F_PROPERTY_GET                     = 1518, \
			     ODB_ACT_F_PROPERTY_DEL                     = 1519, \
			     ODB_ACT_F_PROPERTY_COPY_ALL                = 1520, \
			     ODB_ACT_UTILS_INDEX_SEARCH_SPECIAL         = 1521, \
			     ODB_ACT_SHAPE_DIST_DIST                    = 1522, \
			     ODB_ACT_F_BREAK_TO_F_LIST			= 1523, \
			     ODB_ACT_F_CONVERT_TO_SEMI_STANDART         = 1524   

#define ODB_STEP_GET_IMP_LIST( _imp_list ) {\
    ODB_PARAMS_INIT( ODB_ACT_EDT_IMP_LIST );              \
    ODB_PARAM_SET_OBJP( _imp_list );                       \
    ODB_CALL;  }

#define ODB_STEP_GET_IMP_DATA( _imp_id, _imp_data ) {\
    ODB_PARAMS_INIT( ODB_ACT_EDT_IMP_DATA );       \
    ODB_PARAM_SET_I (_imp_id);                     \
    ODB_PARAM_SET_VOID(_imp_data);                 \
    ODB_CALL;  }

#define ODB_F_SET_IMP(_ld,_nf,_imp_id, _polyline_id,_thresholdSetting)                \
{ ODB_PARAMS_INIT(ODB_ACT_F_SET_IMP);         \
    ODB_PARAM_SET_OBJ(_ld);		     \
    ODB_PARAM_SET_I(_nf);                    \
    ODB_PARAM_SET_I(_imp_id);                \
    ODB_PARAM_SET_I(_polyline_id);           \
    ODB_PARAM_SET_I(_thresholdSetting);      \
    ODB_CALL; }

#define ODB_F_RESET_IMP(_ld,_nf,_keep_orig)     \
{ ODB_PARAMS_INIT(ODB_ACT_F_RESET_IMP);         \
    ODB_PARAM_SET_OBJ(_ld);		        \
    ODB_PARAM_SET_I(_nf);                       \
    ODB_PARAM_SET_I(_keep_orig);                \
    ODB_CALL; }

#define ODB_F_GET_IMP_ID(_ld,_nf,_imp_id)                \
{ ODB_PARAMS_INIT(ODB_ACT_F_IMP_ID);         \
    ODB_PARAM_SET_OBJ(_ld);		        \
    ODB_PARAM_SET_I(_nf);                       \
    ODB_PARAM_SET_IP(_imp_id);                \
    ODB_CALL; }

#define ODB_F_GET_IMP_ORIG_WIDTH(_ld,_nf,_orig_width)                \
{ ODB_PARAMS_INIT(ODB_ACT_F_IMP_ORIG_WIDTH);         \
    ODB_PARAM_SET_OBJ(_ld);		        \
    ODB_PARAM_SET_I(_nf);                       \
    ODB_PARAM_SET_IP(_orig_width);                \
    ODB_CALL; }

#define ODB_SHAPE_SWITCH_DIST_INFRA( _flag ) {		    \
    ODB_PARAMS_INIT(ODB_ACT_SHAPE_SWITCH_DIST_INFRA);	    \
    ODB_PARAM_SET_I(_flag);				    \
    ODB_CALL;						    \
}

#define ODB_RES_CALC_LIST(_ld_lst,_cat_num, _calc, _result) \
{ ODB_PARAMS_INIT(ODB_ACT_RES_CALC_LIST);          \
    ODB_PARAM_SET_OBJ(_ld_lst);                     \
    ODB_PARAM_SET_I (_cat_num);                 \
    ODB_PARAM_SET_I (_calc);                    \
    ODB_PARAM_SET_IP(_result);                  \
    ODB_CALL; }


#define ODB_RES_TYPICAL_SIZE_LIST(_ld_lst,_cat_num, _resolution, _size) \
{ ODB_PARAMS_INIT(ODB_ACT_RES_TYPICAL_SIZE_LIST);   \
    ODB_PARAM_SET_OBJ(_ld_lst);                      \
    ODB_PARAM_SET_I (_cat_num);                  \
    ODB_PARAM_SET_I (_resolution);               \
    ODB_PARAM_SET_IP(_size);                     \
    ODB_CALL; }


#define ODB_RES_CALC_RANGE_LIST(_ld_lst,_cat_num, _calc_type, _low_limit, _high_limit, _result) \
{ ODB_PARAMS_INIT( ODB_ACT_RES_CALC_RANGE_LIST ); \
    ODB_PARAM_SET_OBJ(_ld_lst);                     \
    ODB_PARAM_SET_I (_cat_num);                 \
    ODB_PARAM_SET_I (_calc_type );              \
    ODB_PARAM_SET_I (_low_limit);               \
    ODB_PARAM_SET_I (_high_limit);              \
    ODB_PARAM_SET_IP(_result);                  \
    ODB_CALL; }


#define ODB_LAYER_GET_ACTIVE_AREA(_shape, _num_shapes)	\
 {  ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_ACTIVE_AREA);	\
    ODB_PARAM_SET_SHAPE (_shape);			\
    ODB_PARAM_SET_IP    (_num_shapes);			\
    ODB_CALL; }

#define ODB_LAYER_GET_VISIBLE_AREA(_shape, _num_shapes)	\
 {  ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_VISIBLE_AREA);	\
    ODB_PARAM_SET_SHAPE (_shape);			\
    ODB_PARAM_SET_IP    (_num_shapes);			\
    ODB_CALL; }

#define ODB_SHAPE_CHANGE_POLY_CORNER_RADIUS(_shape, _point_index, _radius, _is_ok)	\
 {  ODB_PARAMS_INIT(ODB_ACT_SHAPE_CHANGE_POLY_CORNER_RADIUS);	\
    ODB_PARAM_SET_SHAPE(_shape);			\
    ODB_PARAM_SET_I(_point_index);			\
    ODB_PARAM_SET_I(_radius);			\
    ODB_PARAM_SET_IP(_is_ok);			\
    ODB_CALL; }


#define ODB_LAYER_FILL_FROM_PATH(_ld,_path)		\
 {  ODB_PARAMS_INIT(ODB_ACT_LAYER_FILL_FROM_PATH);	\
    ODB_PARAM_SET_OBJ(_ld);				\
    ODB_PARAM_SET_S  (_path);				\
    ODB_CALL; }

#define ODB_F_CHANGE_LIST(_ld,_list)		\
 {  ODB_PARAMS_INIT(ODB_ACT_F_CHANGE_LIST);	\
    ODB_PARAM_SET_OBJ(_ld);			\
    ODB_PARAM_SET_OBJ(_list);			\
    ODB_CALL; }

#define ODB_F_ADD_LIST(_ld,_list)		\
 {  ODB_PARAMS_INIT(ODB_ACT_F_ADD_LIST);	\
     ODB_PARAM_SET_OBJ(_ld);			\
     ODB_PARAM_SET_OBJ(_list);			\
     ODB_CALL; }

#define ODB_F_DELETE_LIST(_ld,_list)		\
 {  ODB_PARAMS_INIT(ODB_ACT_F_DELETE_LIST);	\
     ODB_PARAM_SET_OBJ(_ld);			\
     ODB_PARAM_SET_OBJ(_list);			\
     ODB_CALL; }

#define ODB_LAYER_DRILL_DIRECTION(_ld,_direction)	\
 {  ODB_PARAMS_INIT(ODB_ACT_LAYER_DRILL_DIRECTION);	\
    ODB_PARAM_SET_OBJ(_ld);				\
    ODB_PARAM_SET_IP(_direction);			\
    ODB_CALL; }

#define ODB_LAYER_STOP_SHAPE_LIST_UPDATE(_ld)	\
 {  ODB_PARAMS_INIT(ODB_ACT_LAYER_STOP_SHAPE_LIST_UPDATE)\
    ODB_PARAM_SET_OBJ(_ld);				\
    ODB_CALL; }

#define ODB_LAYER_RESUME_SHAPE_LIST_UPDATE(_ld)	\
 {  ODB_PARAMS_INIT(ODB_ACT_LAYER_RESUME_SHAPE_LIST_UPDATE)\
    ODB_PARAM_SET_OBJ(_ld);				\
    ODB_CALL; }

#define ODB_FIX_REPLACE_NF(_ld, _meas_id, _old_nf, _new_nf)	\
 {  ODB_PARAMS_INIT(ODB_ACT_FIX_REPLACE_NF);			\
    ODB_PARAM_SET_OBJ(_ld);					\
    ODB_PARAM_SET_I(_meas_id);					\
    ODB_PARAM_SET_I(_old_nf);					\
    ODB_PARAM_SET_I(_new_nf);					\
    ODB_CALL; }

#define ODB_LAYER_IS_EXPOSED(_ld, _is_exposed)			\
 {  ODB_PARAMS_INIT(ODB_ACT_LAYER_IS_EXPOSED);			\
    ODB_PARAM_SET_OBJ(_ld);					\
    ODB_PARAM_SET_IP(_is_exposed);				\
    ODB_CALL; }

#define ODB_LAYER_GET_EXPOSED_AREA_SHAPES(_ld, _exposed_shapes)	\
 {  ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_EXPOSED_AREA_SHAPES);	\
    ODB_PARAM_SET_OBJ(_ld);					\
    ODB_PARAM_SET_OBJP(_exposed_shapes);			\
    ODB_CALL; }

#define ODB_LAYER_GET_ORIENTATION(_ld, _orientation)		\
 {  ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_ORIENTATION);		\
    ODB_PARAM_SET_OBJ(_ld);					\
    ODB_PARAM_SET_IP(_orientation);				\
    ODB_CALL; }

#define ODB_LAYER_GET_ATTACHED_LAYERS(_ld, _attached_layers)	\
 {  ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_ATTACHED_LAYERS);		\
    ODB_PARAM_SET_OBJ(_ld);					\
    ODB_PARAM_SET_OBJP(_attached_layers);			\
    ODB_CALL; }

#define ODB_SHAPE_DIST_TO_CONT(_shape1, _shape2, _max_dist, _edge_list, _seg_list, _dist_list, _rel) \
{  ODB_PARAMS_INIT(ODB_ACT_SHAPE_DIST_TO_CONT);         \
    ODB_PARAM_SET_SHAPE (_shape1);                      \
    ODB_PARAM_SET_SHAPE (_shape2);                      \
    ODB_PARAM_SET_I  (_max_dist);                       \
    ODB_PARAM_SET_OBJP(_edge_list);                     \
    ODB_PARAM_SET_OBJP(_seg_list);                      \
    ODB_PARAM_SET_OBJP(_dist_list);                     \
    ODB_PARAM_SET_RELP (_rel);                          \
    ODB_CALL; }

#define ODB_SHAPE_DIST_TO_CONT2(_shape1, _shape2, _max_dist, _seg, _dist, _rel) \
{ ODB_PARAMS_INIT(ODB_ACT_SHAPE_DIST_TO_CONT2);     \
    ODB_PARAM_SET_SHAPE (_shape1);              \
    ODB_PARAM_SET_SHAPE (_shape2);              \
    ODB_PARAM_SET_I  (_max_dist);               \
    ODB_PARAM_SET_SHAPE (_seg);                 \
    ODB_PARAM_SET_IP (_dist);                   \
    ODB_PARAM_SET_RELP (_rel);                  \
    ODB_CALL; }


#define ODB_F_PROPERTY_SET(_ld, _nf, _property_index, _property_type, _val, _save) \
    {ODB_PARAMS_INIT(ODB_ACT_F_PROPERTY_SET); \
	ODB_PARAM_SET_OBJ  (_ld);   \
	ODB_PARAM_SET_I    (_nf);   \
	ODB_PARAM_SET_I    (_property_index);   \
	ODB_PARAM_SET_I    (_property_type);   \
	ODB_PARAM_SET_VOID (_val); \
	ODB_PARAM_SET_I    (_save); \
	ODB_CALL;}

#define ODB_F_PROPERTY_GET(_ld, _nf, _property_index, _val, _exists) \
    {ODB_PARAMS_INIT(ODB_ACT_F_PROPERTY_GET); \
    ODB_PARAM_SET_OBJ  (_ld);   \
    ODB_PARAM_SET_I    (_nf);   \
    ODB_PARAM_SET_I    (_property_index); ODB_PARAM_SET_VOID (_val); ODB_PARAM_SET_IP (_exists); ODB_CALL;}


#define ODB_F_PROPERTY_DEL(_ld, _nf, _property_index) \
     { ODB_PARAMS_INIT(ODB_ACT_F_PROPERTY_DEL); \
     ODB_PARAM_SET_OBJ  (_ld);   \
     ODB_PARAM_SET_I    (_nf);   \
     ODB_PARAM_SET_I    (_property_index); ODB_CALL; }

#define ODB_F_PROPERTY_COPY_ALL(_ld_src, _nf_src, _ld_dst, _nf_dst) \
     { ODB_PARAMS_INIT(ODB_ACT_F_PROPERTY_COPY_ALL); \
     ODB_PARAM_SET_OBJ  (_ld_src);   \
     ODB_PARAM_SET_I    (_nf_src);   \
     ODB_PARAM_SET_OBJ  (_ld_dst);   \
     ODB_PARAM_SET_I    (_nf_dst);   \
     ODB_CALL; }

#define ODB_UTILS_INDEX_SEARCH_SPECIAL(_index, _shape, _ind_list) \
    { ODB_PARAMS_INIT(ODB_ACT_UTILS_INDEX_SEARCH_SPECIAL);       \
      ODB_PARAM_SET_I(_index);                                    \
      ODB_PARAM_SET_SHAPE(_shape);                                \
      ODB_PARAM_SET_VOID(_ind_list);                              \
      ODB_CALL; }

#endif

#define ODB_SHAPE_DIST_DIST(_shape1, _shape2, _dist) \
 {  ODB_PARAMS_INIT(ODB_ACT_SHAPE_DIST_DIST);   \
    ODB_PARAM_SET_SHAPE (_shape1);              \
    ODB_PARAM_SET_SHAPE (_shape2);              \
    ODB_PARAM_SET_IP (_dist);                   \
    ODB_CALL; }

#define ODB_F_BREAK_TO_F_LIST(_f, _f_list)	\
 {   ODB_PARAMS_INIT(ODB_ACT_F_BREAK_TO_F_LIST); \
     ODB_PARAM_SET_F (_f);			\
     ODB_PARAM_SET_OBJP( _f_list );              \
     ODB_CALL; }

#define ODB_F_CONVERT_TO_SEMI_STANDART(_f, _tol, _f_changed)	\
 {   ODB_PARAMS_INIT(ODB_ACT_F_CONVERT_TO_SEMI_STANDART); \
    ODB_PARAM_SET_F (_f);			\
     ODB_PARAM_SET_I(_tol);			\
    ODB_PARAM_SET_IP( _f_changed );              \
    ODB_CALL; }

#endif
