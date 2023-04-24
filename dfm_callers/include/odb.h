/***********************************************************
 *
 *  Module: odb.h
 *
 *  Description:
 *
 *  This module contains literals, macros and structures which are required
 *  by any program which calls the Genesis odb library.
 *
 *  Author:		Moshik Kovarsky
 *
 *  (c) Copyright 1994,1995 - Valor Computerized Systems Ltd.
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

#ifndef ODB_PUBLIC_DEF
#define ODB_PUBLIC_DEF

#define u_enum enum  /* HP has no working support of unsigned enum */

#include <stdio.h>
#include <math.h>
#include <string.h>
#ifdef SOLARIS_2
#include <values.h>
#endif
#ifndef WINDOWS_NT
#include <unistd.h> /*for intptr_t type*/
#endif

#ifndef M_PI_4
#   define M_PI_4   0.78539816339744830962
#endif
#ifndef M_PI_2
#   define M_PI_2   1.57079632679489661923
#endif
#ifndef M_PI
#   define M_PI     3.14159265358979323846
#endif
#ifndef M_PIx2
#   define M_PIx2   6.28318530717958647692
#endif
#ifndef M_SQRT1_2
#define	M_SQRT1_2	0.70710678118654752440
#endif
#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#endif
/*------------ GENERAL CONSTANTS ----------------------------- */

#define ODB_VERSION     80 /* Version number of genesis O.D.B. */

enum _odb_boolean
   { ODB_FALSE = 0,
     ODB_TRUE  = 1 };

#ifndef ODB_INTERNAL_LIBRARY
typedef u_enum _odb_boolean boolean;
/* 64 bit defines sizeof as long which leads to
   many redundant warnings */
#ifndef __cplusplus
#define sizeof (int)sizeof
#endif

/* Valor programs Internationalization support */
#define NLS_GENERAL    "GENERAL"
#define NLS_HEADER     "@$@#"

#define XXSTR(s) #s
#define XSTR(s)  XXSTR(s)

#ifdef NLS_GROUP
#define NLSD(x) (NLS_HEADER __FILE__ NLS_HEADER NLS_GROUP   NLS_HEADER XSTR(__LINE__) NLS_HEADER x)
#else
#define NLSD(x) (NLS_HEADER __FILE__ NLS_HEADER NLS_GENERAL NLS_HEADER XSTR(__LINE__) NLS_HEADER x)
#endif

#define NLST(x)  gen__nls_nlst_const((x))
#define NLSI(x)  NLST(NLSD(x))
#define NLSE(x)  x

#endif

#ifndef TRUE
#define TRUE ODB_TRUE
#endif

/* ANY Angle constants */
#define MIN_ANG_GRAD	0.0001
#define MIN_ANG_RAD	(MIN_ANG_GRAD*M_PI/180.)
#define M_PIx3_2	(M_PI+M_PI_2)

#ifndef FALSE
#define FALSE ODB_FALSE
#endif

#define ODB_L_LEN_NAME           64
typedef char odb_name[ODB_L_LEN_NAME+1];

#define ODB_L_LEN_LAYER_DEF     2047
typedef char odb_layer_def[ODB_L_LEN_LAYER_DEF+1];

typedef char odb_function_def[FILENAME_MAX];

typedef char odb_detch_setup_filename[FILENAME_MAX];

enum  _odb_units
   { ODB_UNITS_INCH,
     ODB_UNITS_MM };

typedef u_enum _odb_units odb_units_enum;

enum  _odb_match_std
   { ODB_L_MATCH_EXACTLY,
     ODB_L_MATCH,
     ODB_L_MATCH_NON };

typedef u_enum _odb_match_std odb_match_std_enum;

enum  _odb_compensate
   { ODB_L_COMPENSATE_NESTED      = 1,
     ODB_L_COMPENSATE_ADD_EXTRAS  = 2,
     ODB_L_COMPENSATE_DO_CHAINS   = 4,
     ODB_L_COMPENSATE_ALL         = 7};

typedef u_enum _odb_compensate odb_compensate_enum;

enum  _odb_cont_op_accuracy
   { ODB_L_CONT_OP_ACCURACY_NORMAL = 0,
     ODB_L_CONT_OP_ACCURACY_HIGH   = 1};

typedef u_enum _odb_cont_op_accuracy odb_cont_op_accuracy_enum;

enum _odb_clip_mode
{   ODB_L_CLIP_INSIDE              = 1,
    ODB_L_CLIP_OUTSIDE             = 2 };
typedef u_enum _odb_clip_mode odb_clip_mode_enum;

enum _odb_sliver_mode
   { ODB_L_SLIVER_FIND                 = 0,
     ODB_L_SLIVER_FILL_SURFACES        = 1,
     ODB_L_SLIVER_FILL_LINES           = 2 };

typedef u_enum _odb_sliver_mode odb_sliver_mode_enum;

enum _odb_cont_resize_mode
   { ODB_L_KEEP_CORNER                  = 0,
     ODB_L_CONTROL_CORNER               = 1,
     ODB_L_ROUND_CORNER                 = 2,
     ODB_L_ROUND_CORNER_NO_SIMPLIFY     = 3,
     ODB_L_KEEP_CORNER_NO_SIMPLIFY      = 4};

typedef u_enum _odb_cont_resize_mode odb_cont_resize_mode_enum;

enum _odb_cont_clean_mode
   { ODB_L_CLEAN_X_OR_Y                 = 0,
     ODB_L_CLEAN_X_AND_Y                = 1,
     ODB_L_CLEAN_AREA                   = 2 };

typedef u_enum _odb_cont_clean_mode odb_cont_clean_mode_enum;

enum _odb_func_interpolation_mode
   { ODB_L_STEPS                 = 0,
     ODB_L_LINEAR                = 1 };

enum _odb_layer_orientation_mode {
    ODB_L_LYR_ORIENTATION_NOT_DEFINED = 0,
    ODB_L_LYR_ORIENTATION_UPWARDS,
    ODB_L_LYR_ORIENTATION_DOWNWARDS,
    /* Only sm used to cover both top & bot copper layers can get the following type */
    ODB_L_LYR_ORIENTATION_BOTH 
};

typedef u_enum _odb_func_interpolation_mode odb_func_interpolation_mode_enum;

enum _odb_neighbor_search_mode
   {  ODB_L_SEARCH_ALL              = 0,
      ODB_L_SEARCH_AIR_GAP          = 1 };
typedef u_enum _odb_neighbor_search_mode odb_neighbor_search_mode_enum;

enum _odb_meas_fix_mode
   {  ODB_L_MEAS_FIX_NONE           = 0,
      ODB_L_MEAS_FIX_DONE           = 1,
      ODB_L_MEAS_FIX_NOT_DONE       = 2 };
typedef u_enum _odb_meas_fix_mode odb_meas_fix_mode_enum;

enum _odb_detch_method_enum
{
    ODB_L_DETCH_METHOD_NONE = 0,
    ODB_L_DETCH_METHOD_RESIZE = 1,
    ODB_L_DETCH_METHOD_LINE_BASED_PATCH    = 2,
    ODB_L_DETCH_METHOD_CONTOUR_BASED_PATCH = 3,
    ODB_L_DETCH_METHOD_RESIZE_UNIFORM = 4,
    ODB_L_DETCH_METHOD_SPLIT_AND_RESIZE = 5,
    ODB_L_DETCH_METHOD_SPECIAL = 6
};
typedef u_enum _odb_detch_method_enum odb_detch_method_enum;

#define PIXELS_MIL 10160 /* Pixels in one mil    */
#define PIXELS_MIC 400   /* Pixels in one micron */

#ifndef MAX
#define MAX(x,y)  ((x)>(y)?(x):(y))
#endif
#ifndef MIN
#define MIN(x,y)  ((x)<(y)?(x):(y))
#endif
#ifndef SGN
#define SGN(x) (x==0 ? 0 : (x > 0 ? 1 : -1))
#endif
#ifndef ABS
#define ABS(x)   ((x)>0 ? (x) : -(x))
#endif

#ifndef ODB_INTERNAL_LIBRARY
#define INT(x) ((x)>=0 ? (int)((x)+0.5) : (int)((x)-0.5))
#define DEG(x) (180.*(x)/M_PI)
#define RAD(x) (M_PI*(x)/180.)
#endif


#ifndef MAXINT
#   define MAXINT 0x7fffffff
#endif
#define MININT (-MAXINT)

#ifndef LENGTH
#define LENGTH(x) (sizeof((x))/sizeof(*(x)))
#endif
#define _LENGTH(x) (sizeof((x))/sizeof(*(x)))  /* For internal use */

#define I2P(x)   INT((x) * (PIXELS_MIL * 1000.))
#define P2I(x)   ((double)((x) / (PIXELS_MIL * 1000.)))
#define MIL2P(x) INT((x) * (PIXELS_MIL))
#define P2MIL(x) ((double) ((x) / (double)(PIXELS_MIL)))

#define MM2P(x)  INT((x) * (PIXELS_MIC * 1000.))
#define P2MM(x)  ((double)((x) / (PIXELS_MIC * 1000.)))
#define MIC2P(x) INT((x) * (PIXELS_MIC))
#define P2MIC(x) ((double) ((x) / (double)(PIXELS_MIC)))

#if !defined(SWAP)
#define SWAP(a,b,type) do { \
    type __tmp_##type; \
    __tmp_##type = a; \
    a = b; \
    b = __tmp_##type; } while(0)
#endif

/* -------------- Program Standard preambles ------------------ */

#define ODB_L_PARAM_STRING_LEN	255

#define ODB_L_LIST_END -1
#define ODB_L_IGNORE_NET       -2

typedef odb_layer_def  odb_param_layer;
typedef int       odb_param_int;
typedef double    odb_param_double;
typedef int       odb_param_p_inch;
typedef int       odb_param_p_mil;
typedef int       odb_param_opt;
typedef char      odb_param_string[ODB_L_PARAM_STRING_LEN+1];
typedef odb_function_def odb_param_function;

#define _ODB_PARAM_LAYER(name)  #name,name
#define _ODB_PARAM_INT(name)    #name,&name
#define _ODB_PARAM_DOUBLE(name) #name,&name
#define _ODB_PARAM_P_INCH(name) #name,&name
#define _ODB_PARAM_P_MIL(name)  #name,&name
#define _ODB_PARAM_RADIO(name)  #name,&name
#define _ODB_PARAM_SET(name)    #name,&name
#define _ODB_PARAM_MENU(name)   #name,&name
#define _ODB_PARAM_STRING(name) #name,name
#define _ODB_PARAM_FUNCTION(name) #name,name

#define ODB_M_PARAM_OPTION(_pval,_nopt) (_pval & (1 << (_nopt-1)))

typedef struct {
   char *name;
   void *addr;
} odb_prog_params;

typedef struct {
   char *name;
   char *title;
   char *description;
} odb_categories;

#ifndef ODB_INTERNAL_LIBRARY
#ifdef WINDOWS_NT
    #define ODB_EXPORT          __declspec(dllexport)
#else
    #define ODB_EXPORT          __attribute__ ((visibility("default")))
#endif

#define ODB_EXP(name, param) ODB_EXPORT int name param; int name param
#define _ODB_START(id)      ODB_EXP(id, (void))
#define _ODB_SUMMARY(id)    ODB_EXP(id ## _summary, (void))
#define _ODB_FLASH_EDIT(id) ODB_EXP(id ## _flash_edit, (void))
#define _ODB_CLEANUP(id)    ODB_EXP(id ## _cleanup, (int exec_action, int exec_status))
#define _ODB_RANGES(id)     ODB_EXP(id ## _ranges, (odb_categories** categories_p, int* categories_num_p))
#define _ODB_DYN_RANGES(id) ODB_EXP(id ## _dyn_ranges, (odb_categories** dyn_categories_p, int* dyn_categories_num_p))
#define _ODB_LOCAL( id )    ODB_EXP(id ## _odb_local, ( void ) )

#define ODB_RANGES(_id, _categories) _ODB_RANGES(_id)			  \
{ *categories_p = _categories; *categories_num_p = _LENGTH(_categories);  \
  return 0 /* ODB_L_OK */; }
#define ODB_DYN_RANGES(_id, _pseudo_categories) _ODB_DYN_RANGES(_id) 	\
{ *dyn_categories_p = _pseudo_categories; 				\
  *dyn_categories_num_p = _LENGTH(_pseudo_categories);			\
  return 0 /* ODB_L_OK */; }

#endif /* ODB_INTERNAL_LIBRARY */

#define ODB_L_OK       0          /* allow error handling */
#define ODB_L_STOPPED (-1)
#define ODB_L_ERR      1
#define ODB_RETURN_OK      return(ODB_L_OK);
#define ODB_RETURN_STOPPED return(ODB_L_STOPPED);
#define ODB_RETURN_ERR    \
   { odb__exec_error(ODB_L_ERR,__LINE__); return(ODB_L_ERR);}

#define ODB_ASSERT(x) if (!(x)) {  \
    printf("(" #x ") at %s %d\n",__FILE__,__LINE__); ODB_RETURN_ERR; \
}

#ifndef ODB_PRIVATE_DEF


//typedef void odb_imp_struc;
#define ODB_EXT_ACT_TYPE  

#endif



/* ------- SCRIPT ACTIVATION LITERALS ------------------------ */
typedef enum {
   ODB_L_SCR_RUN, ODB_L_SCR_DEBUG
} odb_script_run_mode_enum ;

/* ------- FEATURE FIELDS CONSTANTS -------------------------- */
/* BE doc*/
/* A feature has three defining characteristics:               */
/* Type - its type (a line, pad ...)                           */
/*        Each type has special sub-characteristics.           */
/* Sym  - Round, square or special                             */
/* Sym num - either a size or a handle of the special          */
/*           definiton.                                        */
/* These three fully define the feature shape                  */
/* In addition to these there are several modifier that affect */
/* the feature relation to where it is located -               */
/* Mirror - whether it is mirrored or not.                     */
/* Angle - its angle of rotation - (0, 90, 180, 270)           */
/* Polarity                                                    */
/* Selected - whether it is selected in editor.                */
/*     ???? - use/don't for selection                          */
/* BE doc*/

enum _odb_f_type
   { ODB_L_F_TYPE_LINE,
     ODB_L_F_TYPE_PAD,
     ODB_L_F_TYPE_SURFACE,
     ODB_L_F_TYPE_ARC,
     ODB_L_F_TYPE_TEXT,
     ODB_L_F_TYPE_NONE = 15};

typedef u_enum _odb_f_type odb_f_type_enum;

typedef intptr_t odb_sym_t; /* type big enough to contain both symbol size and symbol id */

enum _odb_f_sym
   { ODB_L_F_SYM_ROUND,
     ODB_L_F_SYM_SQUARE,
     ODB_L_F_SYM_SPECIAL,
     ODB_L_F_SYM_NONE = 7 };

typedef u_enum _odb_f_sym odb_f_sym_enum;

enum _odb_pol
   { ODB_L_POL_POS,
     ODB_L_POL_NEG };

typedef u_enum _odb_pol odb_pol_enum;

enum _odb_angle
   { ODB_L_ANGLE_0,
     ODB_L_ANGLE_90,
     ODB_L_ANGLE_180,
     ODB_L_ANGLE_270,
     ODB_L_ANGLE_ANY = 7 };

typedef u_enum _odb_angle odb_angle_enum;

enum _odb_mirror
   { ODB_L_MIRROR_R,
     ODB_L_MIRROR_W };

typedef u_enum _odb_mirror odb_mirror_enum;

enum _odb_cw_ccw
   { ODB_L_CW,
     ODB_L_CCW };

typedef u_enum _odb_cw_ccw odb_cw_ccw_enum;

enum _odb_text_str_bar
   { ODB_L_TEXT_STR,
     ODB_L_TEXT_BAR };

typedef u_enum _odb_text_str_bar odb_text_str_bar_enum;

enum _odb_text_ver
   { ODB_L_TEXT_VER0,
     ODB_L_TEXT_VER1 };

typedef u_enum _odb_text_ver odb_text_ver_enum;

enum _odb_bar_type
   { ODB_L_F_BAR_TYPE_U39,
     ODB_L_F_BAR_TYPE_NONE = 7};

typedef u_enum _odb_bar_type odb_bar_type_enum;

enum _odb_bar_asc
   { ODB_L_BAR_ASC,
     ODB_L_BAR_FASC };

typedef u_enum _odb_bar_asc odb_bar_asc_enum;

enum _odb_bar_cs
   { ODB_L_BAR_NCS,
     ODB_L_BAR_CS };

typedef u_enum _odb_bar_cs odb_bar_cs_enum;

enum _odb_bar_bg
   { ODB_L_BAR_NBG,
     ODB_L_BAR_BG };

typedef u_enum _odb_bar_bg odb_bar_bg_enum;

enum _odb_bar_astr
   { ODB_L_BAR_NASTR,
     ODB_L_BAR_ASTR };

typedef u_enum _odb_bar_astr odb_bar_astr_enum;

enum _odb_bar_astr_pos
   { ODB_L_BAR_ASTR_POS_TOP,
     ODB_L_BAR_ASTR_POS_BOT };

enum _odb_set_meas_type
{ ODB_SET_MEAS_ID_TYPE_NONE = 0,
  ODB_SET_MEAS_ID_TYPE_TEXT,
  ODB_SET_MEAS_ID_TYPE_SCALAR,
  ODB_SET_MEAS_ID_TYPE_SCALAR_US,
  ODB_SET_MEAS_ID_TYPE_SCALAR_SQR
};

typedef u_enum _odb_bar_astr_pos odb_bar_astr_pos_enum;

/* BE doc */
/* Literals documentation                                      */
/* ODB_L_DRILL_TYPE_PTH - Plated Through hole.                 */
/* ODB_L_DRILL_TYPE_NPTH - Non Plated Through hole.            */
/* ODB_L_DRILL_TYPE_VIA - Plated via hole.                     */
/*                                                             */
/* ODB_L_PAD_USAGE_TOEPRINT   - Pad used for toeprints         */
/* ODB_L_PAD_USAGE_VIA        - Pad used for via               */
/* ODB_L_PAD_USAGE_G_FIDUCIAL - Pad used for global fiducial   */
/* ODB_L_PAD_USAGE_L_FIDUCIAL - Pad used for local fiducial    */
/* ODB_L_PAD_USAGE_TOOLING_HOLE -                              */
/*                       - Pad(Drill) used for tooling hole    */
/*                                                             */
/* the following literals are used by ODB_RES_REPORT_HIST      */
/* to affect the x axis meaning for a histogram in the report  */
/* ODB_L_HIST_X_SHAPE - the histogram x axis will stand for    */
/*                      measurement shape dimensions.          */
/* ODB_L_HIST_X_F_NAME- the histogram x axis will stand for    */
/*                      measurement feature name.              */
/* ODB_L_HIST_X_F_SYM_PREFIX - the histogram x axis will stand */
/*                             for round, square, rect etc...  */
/* ODB_L_HIST_X_F_SYM_TYPE- the histogram x axis will stand for*/
/*                          r10, r20... s15, s30... rect20x30  */
/* ODB_L_HIST_X_F_TYPE - the histogram x axis will stand for   */
/*                       the measurement feature type (line etc*/
/*                                                             */
/* the following literals are used by ODB_RES_REPORT_HIST      */
/* to affect the Y axis meaning for a histogram in the report  */
/* Their names are self documenting.                           */
/* ODB_L_HIST_Y_COUNT                                          */
/* ODB_L_HIST_Y_AVG                                            */
/* ODB_L_HIST_Y_SUM  - identical to  ODB_L_HIST_Y_COUNT        */
/* ODB_L_HIST_Y_MIN                                            */
/* ODB_L_HIST_Y_MAX                                            */
/*                                                             */
/* The following literals direct which of the measurement      */
/* shapes the histogram will refer to:                         */
/* ODB_L_HIST_MEAS_NA - dont use                               */
/* ODB_L_HIST_MEAS_SHAPE - first (principal) shape.            */
/* ODB_L_HIST_MEAS_ST1 -  second (first auxiliary) shape.      */
/* ODB_L_HIST_MEAS_ST2 -  third (second auxiliary) shape.      */
/*                                                             */
/* The following literals define the shape of line caps        */
/* Note - a square-capped arc is not supported                 */
/* ODB_L_CAP_ROUND                                             */
/* ODB_L_CAP_SQUARE                                            */
/*                                                             */
/* odb_convexity_enum - is unused currently.                   */
/*                                                             */
/* The following literals define geometrical relations between */
/* shapes or between a shape and a list or layer - as returned */
/* by ODB_SHAPE_DIST, ODB_SHPAE_COVER_LAYER etc..              */
/* ODB_L_DISJOINT - the shapes are seperated                   */
/* ODB_L_1_IN_2 - the first shape is fully included in the 2nd */
/* ODB_L_2_IN_1 - the second shape is fully included in the 1st*/
/* ODB_L_INTERSECT - the shapes touch but neither includes the */
/*                   other one.                                */
/* ODB_L_EQUAL - the shapes are exactly alike.                 */
/*                                                             */
/* The following literals control the type of rect to create   */
/* in ODB_SYMBOL_BUILD_RECT:                                   */
/* ODB_L_RECT_TYPE_RECT - euclidean rectangle.                 */
/* ODB_L_RECT_TYPE_RECT_R - round cornered rectangle.          */
/* ODB_L_RECT_TYPE_RECT_C - chamfered rectangle.               */
/*                                                             */
/* The following literals are returned as the style of a       */
/* thermal pad by ODB_SYMBOL_GET_THERMAL_PARAM:                */
/* ODB_L_STYLE_NONE - only style for an outer square and inner */
/* round thermal.                                              */
/* ODB_L_STYLE_SQUARE                                          */
/* ODB_L_STYLE_ROUND                                           */
/* ODB_L_STYLE_ORTHOGONAL                                      */
/*                                                             */
/* Use for calling ODB_F_GET_TOUCHING and                      */
/*   ODB_SHAPE_GET_TOUCHING                                    */
/* ODB_L_TOUCH_MODE_NEG - the action returns all               */
/*                        negative shaves for a given positive */
/*                        feature or shape.                    */
/* ODB_L_TOUCH_MODE_POS_BY_NEG - the action returns all        */
/*                               positive features affected    */
/*                               by a given shave.             */
/*                                                             */
/* The following describe the attributes accessible by         */
/* ODB_LAYER_GET_ATTR and settable by ODB_LAYER_SET_ATTR       */
/* Note - only ODB_L_LAYER_SIDE cannot be set because it is    */
/* a derived value.                                            */
/* Note 2 - changing any of the matrix related attributes (up  */
/* to and including ODB_L_LAYER_POL affects the whole job - not*/
/* just the current step.                                      */
/* ODB_L_LAYER_ROW                                             */
/* ODB_L_LAYER_CONTEXT                                         */
/* ODB_L_LAYER_TYPE                                            */
/* ODB_L_LAYER_POL                                             */
/* ODB_L_LAYER_SIDE                                            */
/* ODB_L_LAYER_AFFECTED                                        */
/* ODB_L_LAYER_WORK                                            */
/*                                                             */
/* These are the possible matrix contexts for a layer:         */
/* ODB_L_LAYER_CONTEXT_BOARD                                   */
/* ODB_L_LAYER_CONTEXT_MISC                                    */
/* ODB_L_LAYER_CONTEXT_ANY                                     */
/*                                                             */
/* These are the possible values of the calc parameter of      */
/* ODB_RES_CALC:                                               */
/* ODB_L_RES_COUNT                                             */
/* ODB_L_RES_AVG                                               */
/* ODB_L_RES_SUM                                               */
/* ODB_L_RES_MIN                                               */
/* ODB_L_RES_MAX                                               */
/* ODB_L_RES_MEDIAN                                            */
/* ODB_L_RES_VARIANCE                                          */
/* ODB_L_RES_STD_DEV                                           */
/*                                                             */
/* Possible values for the type of a layer:                    */
/* ODB_L_LAYER_TYPE_SIG                                        */
/* ODB_L_LAYER_TYPE_PG                                         */
/* ODB_L_LAYER_TYPE_MIX                                        */
/* ODB_L_LAYER_TYPE_SM                                         */
/* ODB_L_LAYER_TYPE_SS                                         */
/* ODB_L_LAYER_TYPE_SP                                         */
/* ODB_L_LAYER_TYPE_DRL                                        */
/* ODB_L_LAYER_TYPE_ROUT                                       */
/* ODB_L_LAYER_TYPE_DOC                                        */
/* ODB_L_LAYER_TYPE_COMP                                       */
/* ODB_L_LAYER_TYPE_MASK                                       */
/*                                                             */
/* Possible values for the side of a layer:                    */
/* ODB_L_LAYER_SIDE_TOP                                        */
/* ODB_L_LAYER_SIDE_BOT                                        */
/* ODB_L_LAYER_SIDE_INN                                        */
/* ODB_L_LAYER_SIDE_NONE                                       */
/*                                                             */
/* Possible values for the type of a shape:                    */
/* ODB_L_SHAPE_TYPE_POINT                                      */
/* ODB_L_SHAPE_TYPE_SEG                                        */
/* ODB_L_SHAPE_TYPE_CURVE                                      */
/* ODB_L_SHAPE_TYPE_LINE                                       */
/* ODB_L_SHAPE_TYPE_CIRCLE                                     */
/* ODB_L_SHAPE_TYPE_SQUARE                                     */
/* ODB_L_SHAPE_TYPE_RECT                                       */
/* ODB_L_SHAPE_TYPE_ARC                                        */
/* ODB_L_SHAPE_TYPE_POLY - not in use poly is under cont.      */
/* ODB_L_SHAPE_TYPE_CONT                                       */
/*                                                             */
/* Possible values for the type of a subnet:                   */
/* ODB_L_SUBNET_TYPE_TOEPRINT                                  */
/* ODB_L_SUBNET_TYPE_VIA                                       */
/* ODB_L_SUBNET_TYPE_TRACE                                     */
/* ODB_L_SUBNET_TYPE_PLANE                                     */
/*                                                             */
/* these list types are currentaly available in ODB:           */
/* ODB_L_LIST_TYPE_SHAPE                                       */
/* ODB_L_LIST_TYPE_F                                           */
/* ODB_L_LIST_TYPE_NAME                                        */
/* ODB_L_LIST_TYPE_INT                                         */
/* ODB_L_LIST_TYPE_DOUBLE                                      */
/* ODB_L_LIST_TYPE_LAYER                                       */
/* ODB_L_LIST_TYPE_NEIGHBOR                                    */
/* ODB_SHAPE_AIR_GAP_LAYER and ODB_SHAPE_AIR_GAP_LIST return   */
/*                                                             */
/* these possible values as the air gap.                       */
/* ODB_L_NO_AIR_GAP                                            */
/* ODB_L_AIR_GAP                                               */
/*                                                             */
/* ODB_F_CONV_STD  returns these values as the match acheived: */
/* ODB_L_MATCH_EXACTLY - the feature exactly matches a standard*/
/* ODB_L_MATCH - a surface matches the returned standard within*/
/*               the given tolerance.                          */
/* ODB_L_MATCH_NON - there is no match to a standard.          */
/*                                                             */
/*  Layer's mask layer attribute: ODB_L_ACTION_MASK_LYR        */
/*  The following attribute set the mask type:                 */
/*  ODB_L_MASK_LAYER_USAGE. This attribute can get the follow  */
/*  two values:                                                */
/*  ODB_L_EXCLUSION_MASK_LAYER = 0                             */
/* ODB_L_INCLUSION_MASK_LAYER = 1                              */
/*                                                             */
/* BE doc */

enum _odb_drill_type {
    ODB_L_DRILL_TYPE_PTH,
    ODB_L_DRILL_TYPE_NPTH,
    ODB_L_DRILL_TYPE_VIA
};
typedef u_enum _odb_drill_type odb_drill_type_enum;

enum _odb_via_type {
    ODB_L_VIA_TYPE_DRILLED,
    ODB_L_VIA_TYPE_LASER,
    ODB_L_VIA_TYPE_PHOTO
};
typedef u_enum _odb_via_type odb_via_type_enum;

enum _odb_plated_type {
    ODB_L_PLATED_TYPE_STANDARD,
    ODB_L_PLATED_TYPE_PRESS_FIT
};
typedef u_enum _odb_plated_type odb_plated_type_enum;
        
enum _odb_direction {
    ODB_L_DIRECTION_L2R, ODB_L_DIRECTION_T2B,
    ODB_L_DIRECTION_R2L, ODB_L_DIRECTION_B2T
};
typedef u_enum _odb_direction odb_direction_enum;

enum _odb_viacap_side {
    ODB_L_VIACAP_TOP, ODB_L_VIACAP_BOTTOM,
    ODB_L_VIACAP_BOTH, ODB_L_VIACAP_NONE
};
typedef u_enum _odb_viacap_side odb_viacap_side_enum;

enum _odb_side {
    ODB_L_SIDE_NONE = 0,
    ODB_L_SIDE_UP = 1,
    ODB_L_SIDE_RIGHT = 2,
    ODB_L_SIDE_DOWN = 4,
    ODB_L_SIDE_LEFT = 8
};
typedef u_enum _odb_side odb_side_enum;

enum _odb_mount_type {
    ODB_L_MOUNT_OTHER, ODB_L_MOUNT_SMT, ODB_L_MOUNT_THMT
};
typedef u_enum _odb_mount_type odb_mount_type_enum;

enum _odb_pad_usage_type
   { ODB_L_PAD_USAGE_TOEPRINT,
     ODB_L_PAD_USAGE_VIA,
     ODB_L_PAD_USAGE_G_FIDUCIAL,
     ODB_L_PAD_USAGE_L_FIDUCIAL,
     ODB_L_PAD_USAGE_TOOLING_HOLE };

typedef u_enum _odb_pad_usage_type odb_pad_usage_type_enum;

enum _odb_hist_x
   { ODB_L_HIST_X_SHAPE,
     ODB_L_HIST_X_F_NAME,
     ODB_L_HIST_X_F_SYM_PREFIX,
     ODB_L_HIST_X_F_SYM_TYPE,
     ODB_L_HIST_X_F_TYPE };

typedef u_enum _odb_hist_x odb_hist_x_enum;

enum _odb_hist_y
   { ODB_L_HIST_Y_COUNT,
     ODB_L_HIST_Y_AVG,
     ODB_L_HIST_Y_SUM,
     ODB_L_HIST_Y_MIN,
     ODB_L_HIST_Y_MAX };

typedef u_enum _odb_hist_y odb_hist_y_enum;

enum _odb_hist_meas_num
   { ODB_L_HIST_MEAS_NA,
     ODB_L_HIST_MEAS_SHAPE,
     ODB_L_HIST_MEAS_ST1,
     ODB_L_HIST_MEAS_ST2};

typedef u_enum _odb_hist_meas_num odb_hist_meas_num_enum;

enum _odb_cap
   { ODB_L_CAP_ROUND,
     ODB_L_CAP_SQUARE };

typedef u_enum _odb_cap odb_cap_enum;

enum _odb_convexity
   { ODB_L_CONCAVE,
     ODB_L_CONVEX };

typedef u_enum _odb_convexity odb_convexity_enum;

enum _odb_rel
   { ODB_L_DISJOINT,
     ODB_L_1_IN_2,
     ODB_L_2_IN_1,
     ODB_L_INTERSECT,
     ODB_L_EQUAL };

typedef u_enum _odb_rel odb_rel_enum;

enum _odb_rect_type
   { ODB_L_RECT_TYPE_RECT,
     ODB_L_RECT_TYPE_RECT_R,
     ODB_L_RECT_TYPE_RECT_C };

typedef u_enum _odb_rect_type odb_rect_enum;

enum _odb_smd_type
   { ODB_L_SMD_TYPE_SQUARE,
     ODB_L_SMD_TYPE_OVAL,
     ODB_L_SMD_TYPE_RECT,
     ODB_L_SMD_TYPE_RECT_R,
     ODB_L_SMD_TYPE_RECT_C,
     ODB_L_SMD_TYPE_DIAMOND,
     ODB_L_SMD_TYPE_OCTAGON,
     ODB_L_SMD_TYPE_HEXAGON_L,
     ODB_L_SMD_TYPE_HEXAGON_S,
     ODB_L_SMD_TYPE_CROSS,
     ODB_L_SMD_TYPE_TSHAPE,
     ODB_L_SMD_TYPE_CROSS8 };

typedef u_enum _odb_smd_type odb_smd_enum;

enum _odb_corner_mask
   { ODB_L_SMD_CORNER_TR = 0x1,
     ODB_L_SMD_CORNER_TL = 0x2,
     ODB_L_SMD_CORNER_BL = 0x4,
     ODB_L_SMD_CORNER_BR = 0x8 };

typedef u_enum _odb_corner_mask odb_corner_enum;

enum _odb_rout_comp_side
   {
    ODB_L_COMP_NONE = 0,
    ODB_L_COMP_RIGHT = 1,
    ODB_L_COMP_LEFT = 2
   };
typedef u_enum _odb_rout_comp_side odb_rout_comp_side_enum; 

enum _odb_thermal_type
   { ODB_L_THERMAL_R,
     ODB_L_THERMAL_S,
     ODB_L_THERMAL_RC,
     ODB_L_THERMAL_SR,
     ODB_L_THERMAL_RS,
     ODB_L_THERMAL_RRC,
     ODB_L_THERMAL_O
 };

typedef u_enum _odb_thermal_type odb_thermal_enum;

enum _odb_donut_type
   { ODB_L_DONUT_R,
     ODB_L_DONUT_S,
     ODB_L_DONUT_RC,
     ODB_L_DONUT_RS,
     ODB_L_DONUT_SR,
     ODB_L_DONUT_RRC,
     ODB_L_DONUT_O
};

typedef u_enum _odb_donut_type odb_donut_enum;

enum _odb_style_type
   { ODB_L_STYLE_NONE,
     ODB_L_STYLE_SQUARE,
     ODB_L_STYLE_ROUND,
     ODB_L_STYLE_ORTHOGONAL};

typedef u_enum _odb_style_type odb_style_enum;

/* currently only get touching negatives is supported */
enum _odb_touch_mode_enum
   { ODB_L_TOUCH_MODE_NEG,
     ODB_L_TOUCH_MODE_POS_BY_NEG,
     ODB_L_TOUCH_MODE_NEG_FCL };

typedef u_enum _odb_touch_mode_enum odb_touch_mode_enum;

enum _odb_mask_layer_type
   {  ODB_L_EXCLUSION_MASK_LAYER = 0,
      ODB_L_INCLUSION_MASK_LAYER = 1 };
typedef u_enum _odb_mask_layer_type odb_mask_layer_type;

enum _odb_generated_net_point_type
{
    ODB_L_NET_POINT_DRAWN,
    ODB_L_NET_POINT_SPLIT,
    ODB_L_NET_POINT_GASKET,
    ODB_L_NET_POINT_OTHER
};
typedef u_enum _odb_generated_net_point_type odb_generated_net_point_enum;

enum _odb_local_mode_enum {
    ODB_L_LOCAL_FIX_BEST = 0,
    ODB_L_LOCAL_FIX_ALL_OPTIONS = 1
};
typedef u_enum _odb_local_mode_enum odb_local_mode_enum;

/*--------------------------------*/
#define ODB_L_ATTR_NAME_DONT_REPAIR  ".dont_repair"
#define ODB_L_ATTR_NAME_SMD          ".smd"
#define ODB_L_ATTR_NAME_BGA          ".bga"
#define ODB_L_ATTR_NAME_GOLD_PLATE   ".gold_plating"
#define ODB_L_ATTR_NAME_DRILL        ".drill"
#define ODB_L_ATTR_NAME_ROUT_PLATED  ".rout_plated"
#define ODB_L_ATTR_NAME_VIA_TYPE     ".via_type"
#define ODB_L_ATTR_NAME_PLATED_TYPE  ".plated_type"
#define ODB_L_ATTR_NAME_BIT          ".bit"
#define ODB_L_ATTR_NAME_N_ELECTRIC   ".n_electric"
#define ODB_L_ATTR_NAME_NOMENCLATURE ".nomenclature"
#define ODB_L_ATTR_NAME_TEAR_DROP    ".tear_drop"
#define ODB_L_ATTR_NAME_PATTERN_FILL ".pattern_fill"
#define ODB_L_ATTR_NAME_PAD_USAGE    ".pad_usage"
#define ODB_L_ATTR_NAME_TEST_POINT   ".test_point"
#define ODB_L_ATTR_NAME_TEST_REQ     ".test_req"
#define ODB_L_ATTR_NAME_AREA_NAME    ".area_name"
#define ODB_L_ATTR_NAME_SLIVER_FILL        ".sliver_fill"
#define ODB_L_ATTR_NAME_PATCH              ".patch"
#define ODB_L_ATTR_NAME_SURFACE_BOTTLENECK ".surface_bottleneck"
#define ODB_L_ATTR_NAME_SMOOTH             ".smooth"
#define ODB_L_ATTR_NAME_SHAVE              ".shave"
#define ODB_L_ATTR_NAME_DFM_ADDED_SHAVE    ".dfm_added_shave"
#define ODB_L_ATTR_NAME_DFM_ADDED_SMOOTHING ".dfm_added_smoothing"
#define ODB_L_ATTR_NAME_ADDED_CONNECTION   ".added_connection"
#define ODB_L_ATTR_NAME_MOUNT_HOLE   ".mount_hole"
#define ODB_L_ATTR_NAME_TOOLING_HOLE ".tooling_hole"
#define ODB_L_ATTR_NAME_IS_CAPPED    ".is_capped"
#define ODB_L_ATTR_NAME_STRING       ".string"
#define ODB_L_ATTR_NAME_SPACING_REQ  ".spacing_req"
#define ODB_L_ATTR_NAME_TIE          ".tie"
#define ODB_L_ATTR_NAME_TIE_PLANE    ".tie_plane"
#define ODB_L_ATTR_NAME_TIEDOWN      ".tiedown"
#define ODB_L_ATTR_NAME_HATCH        ".hatch"
#define ODB_L_ATTR_NAME_HATCH_BORDER ".hatch_border"
#define ODB_L_ATTR_NAME_ORIG_FEATURES ".orig_features" 
#define ODB_L_ATTR_NAME_ORIG_SURF    ".orig_surf"
#define ODB_L_ATTR_NAME_AVOID_SHAVE  ".avoid_shave"
#define ODB_L_ATTR_NAME_CLEAR_DONT_OPT       ".clear_dont_opt"
#define ODB_L_ATTR_NAME_SPLIT_CLEAR          ".split_clear"
#define ODB_L_ATTR_NAME_SPLIT_CLEAR_SHAVE    ".split_clear_shave"
#define ODB_L_ATTR_NAME_GENERATED_NET_POINT  ".generated_net_point"
#define ODB_L_ATTR_NAME_CANNED_TEXT	     ".canned_text"
#define ODB_L_ATTR_NAME_GOLD_FINGER	     ".gold_finger"

#define ODB_L_ATTR_NAME_ROUT_COMP    ".comp"
#define ODB_L_ATTR_NAME_ROUT_CHAIN   ".rout_chain"
#define ODB_L_ATTR_NAME_ROUT_FLAG    ".rout_flag"
#define ODB_L_ATTR_NAME_ROUT_FEED    ".feed"
#define ODB_L_ATTR_NAME_ROUT_SPEED   ".speed"
#define ODB_L_ATTR_NAME_ROUT_TYPE    ".rout_type"
#define ODB_L_ATTR_NAME_ROUT_TOOL    ".rout_tool"
#define ODB_L_ATTR_NAME_TOOLING_HOLES_SET    ".tooling_holes_set"
#define ODB_L_ATTR_NAME_ORIG_TOOLING_HOLES_SET ".orig_tooling_holes_set"

#define ODB_L_ATTR_NAME_COMP_TYPE            ".comp_type"
#define ODB_L_ATTR_NAME_CENTER_FIDUCIAL      ".center_fiducial"
#define ODB_L_ATTR_NAME_NUM_LOCAL_FIDUCIALS  ".num_local_fiducials"
#define ODB_L_ATTR_NAME_LOCAL_FIDUCIAL_DIST  ".local_fiducial_dist"
#define ODB_L_ATTR_NAME_COMP_HEIGHT          ".comp_height"
#define ODB_L_ATTR_NAME_COMP_HTOL_PLUS       ".comp_htol_plus"
#define ODB_L_ATTR_NAME_COMP_HTOL_MINUS      ".comp_htol_minus"
#define ODB_L_ATTR_NAME_COMP_WEIGHT          ".comp_weight"
#define ODB_L_ATTR_NAME_OTHERSIDE_KEEPOUT    ".otherside_keepout"
#define ODB_L_ATTR_NAME_COMP_IGN_SPACING     ".comp_ign_spacing"
#define ODB_L_ATTR_NAME_NO_TP_UNDER          ".no_tp_under"
#define ODB_L_ATTR_NAME_NO_TEXT_UNDER        ".no_text_under"
#define ODB_L_ATTR_NAME_NO_HOLE_UNDER        ".no_hole_under"
#define ODB_L_ATTR_NAME_NO_UNCAP_VIA_UNDER   ".no_uncap_via_under"
#define ODB_L_ATTR_NAME_THVPAD_REQUIRED      ".thvpad_required"
#define ODB_L_ATTR_NAME_LABEL_CLEARANCE      ".label_clearance"
#define ODB_L_ATTR_NAME_SRC_ORIENTATION      ".src_orientation"
#define ODB_L_ATTR_NAME_COMP_MOUNT_TYPE      ".comp_mount_type"
#define ODB_L_ATTR_NAME_GUARD_COMP           ".guard_comp"
#define ODB_L_ATTR_NAME_NEEDS_GUARDING       ".needs_guarding"
#define ODB_L_ATTR_NAME_IND_ORIENT_REQ       ".ind_orient_req"
#define ODB_L_ATTR_NAME_NO_FIDUCIAL_CHECK    ".no_fiducial_check"
#define ODB_L_ATTR_NAME_IS_SHADOWED          ".is_shadowed"

#define ODB_L_ATTR_NAME_ASSEMBLY_PROC_TOP    ".assembly_proc_top"
#define ODB_L_ATTR_NAME_ASSEMBLY_PROC_BOTTOM ".assembly_proc_bottom"
#define ODB_L_ATTR_NAME_FS_DIRECTION_TOP     ".fs_direction_top"
#define ODB_L_ATTR_NAME_FS_DIRECTION_BOTTOM  ".fs_direction_bottom"
#define ODB_L_ATTR_NAME_SMT_DIRECTION_TOP    ".smt_direction_top"
#define ODB_L_ATTR_NAME_SMT_DIRECTION_BOTTOM ".smt_direction_bottom"
#define ODB_L_ATTR_NAME_PRIMARY_SIDE	     ".primary_side"
#define ODB_L_ATTR_NAME_BOARD_THICKNESS	     ".board_thickness"
#define ODB_L_ATTR_NAME_ARRAY_WITH_ROTATION  ".array_with_rotation"
#define ODB_L_ATTR_NAME_VIACAP_LAYER         ".viacap_layer"
#define ODB_L_ATTR_NAME_STAGGERED_VIA_STACK  ".staggered_via"
#define ODB_L_ATTR_NAME_DEPTH                ".depth"
#define ODB_L_ATTR_NAME_DETCH_COMP           ".detch_comp"
#define ODB_L_ATTR_NAME_DETCH_SMOOTH         ".detch_smooth"
#define ODB_L_ATTR_NAME_DETCH_TAPERING       ".detch_tapering"
#define ODB_L_ATTR_NAME_DETCH_ORIG_TYPE      ".detch_orig_type"
#define ODB_L_ATTR_NAME_DETCH_ORIG_NF	     ".detch_orig_nf" 
#define ODB_L_ATTR_NAME_FORCE_GALV_ETCH      ".force_galv_etch"
#define ODB_L_ATTR_NAME_OSP_PAD              ".osp_pad"
#define ODB_L_ATTR_NAME_COPPER_THICKNESS     ".copper_thickness"
#define ODB_L_ATTR_NAME_COPPER_WEIGHT        ".copper_weight"

#define ODB_L_ATTR_NAME_CU_BASE              ".cu_base"
#define ODB_L_ATTR_NAME_TOEP_SPACE           ".toep_spacing_req"
#define ODB_L_ATTR_NAME_NFP                  ".nfp"
#define ODB_L_ATTR_NAME_NFL                  ".nfl"
#define ODB_L_ATTR_NAME_IGNORE_ACTION        ".ignore_action"
#define ODB_L_ATTR_NAME_ACTION_MASK_LYR      ".action_mask_layer"
#define ODB_L_ATTR_NAME_ACTION_MASK_LYR_USAGE ".action_mask_layer_type"
#define ODB_L_ATTR_NAME_ENLARGED_CLEARANCE   ".enlarged_clearance_size"
#define ODB_L_ATTR_NAME_FINGER		     ".finger"

/* special attributes for additional control in solder paste opt */
#define ODB_L_ATTR_NAME_SPO_SHAPE            ".spo_shape"
#define ODB_L_ATTR_NAME_SPO_MOVE_CENTER      ".spo_move_center"
#define ODB_L_ATTR_NAME_SPO_W_MODE           ".spo_w_mode"
#define ODB_L_ATTR_NAME_SPO_W_VAL            ".spo_w_val"
#define ODB_L_ATTR_NAME_SPO_W_FACT           ".spo_w_fact"
#define ODB_L_ATTR_NAME_SPO_H_MODE           ".spo_h_mode"
#define ODB_L_ATTR_NAME_SPO_H_VAL            ".spo_h_val"
#define ODB_L_ATTR_NAME_SPO_H_FACT           ".spo_h_fact"
#define ODB_L_ATTR_NAME_SPO_S_MODE           ".spo_s_mode"
#define ODB_L_ATTR_NAME_SPO_S_VAL            ".spo_s_val"
#define ODB_L_ATTR_NAME_SPO_S_FACT           ".spo_s_fact"

/* Define the related impedance line attribute */
#define ODB_L_ATTR_NAME_IMP_LINE     ".imp_line"
#define ODB_L_ATTR_NAME_IMP_LINE_CANDIDATE ".imp_line_candidate"
#define ODB_L_ATTR_NAME_IMP_CONSTRAINT_ID ".imp_constraint_id";
#define ODB_L_ATTR_NAME_IMP_POLYLINE_ID ".imp_polyline_id" 
#define ODB_L_ATTR_NAME_IMP_TYPE ".imp_type" 
#define ODB_L_ATTR_NAME_IMP_ORIG_LINE_WIDTH ".imp_orig_lw" 

#define ODB_L_ATTR_NAME_CRITICAL_TRACE       ".critical_trace"
#define ODB_L_ATTR_NAME_NON_CRITICAL_TRACE   ".non_critical_trace"
#define ODB_L_ATTR_NAME_NON_FUNCTIONAL_TRACE ".non_functional_trace"

#define ODB_L_ATTR_NAME_TEXT_FEATURE       ".text_feature"
#define ODB_L_ATTR_NAME_TEXT_BLOCK	   ".text_block"
#define ODB_L_ATTR_NAME_TEXT_SYM_IN_BLOCK  ".text_sym_in_block"
#define ODB_L_ATTR_NAME_FRAME_FEATURE	   ".frame_feature"
#define ODB_L_ATTR_NAME_FRAME_BLOCK	   ".frame_block"

/* Attributes related to special pad and feature classification */
#define ODB_L_ATTR_NAME_ORIG_SIZE_MM			".orig_size_mm"
#define ODB_L_ATTR_NAME_ORIG_SIZE_INCH			".orig_size_inch"
#define ODB_L_ATTR_NAME_VIA_PAD				".via_pad"
#define ODB_L_ATTR_NAME_VIA_TYPE_PAD			".via_type_pad"
#define ODB_L_ATTR_NAME_PTH_PAD				".pth_pad"
#define ODB_L_ATTR_NAME_NPTH_PAD			".npth_pad"
#define ODB_L_ATTR_NAME_COPPER_DEFINED			".copper_defined"
#define ODB_L_ATTR_NAME_SOLDER_DEFINED			".solder_defined"
#define ODB_L_ATTR_NAME_PARTIAL_SOLDER_DEFINED		".partial_solder_defined"
#define ODB_L_ATTR_NAME_EMBEDDED			".embedded"
#define ODB_L_ATTR_NAME_PARTIAILLY_EMBEDDED		".partially_embedded"
#define ODB_L_ATTR_NAME_COVERED				".covered"
#define ODB_L_ATTR_NAME_PARTIAILLY_COVERED		".partially_covered"
#define ODB_L_ATTR_NAME_SIDE_PROXIMITY			".side_proximity"
#define ODB_L_ATTR_NAME_ICT_TEST_POINT			".ict_test_point"
#define ODB_L_ATTR_NAME_ICT_TEST_POINT_ON_THICK_TRACE	".ict_test_point_on_thick_trace"
#define ODB_L_ATTR_NAME_BACKDRILLED_PAD			".backdrilled_pad"



/* For the definition of internal attributes (..) */
/* Only ODB_L_ATTR_TYPE_INT is supported   BL 20.04.07 */
enum _odb_attr_type
{ ODB_L_ATTR_TYPE_BOL,
  ODB_L_ATTR_TYPE_TXT,
  ODB_L_ATTR_TYPE_OPT,
  ODB_L_ATTR_TYPE_INT,
  ODB_L_ATTR_TYPE_FLT };

/*--------------------------------*/

enum _odb_layer_attr
   { ODB_L_LAYER_ROW,
     ODB_L_LAYER_CONTEXT,
     ODB_L_LAYER_TYPE,
     ODB_L_LAYER_POL,
     ODB_L_LAYER_SIDE,
     ODB_L_LAYER_AFFECTED,
     ODB_L_LAYER_WORK };

typedef u_enum _odb_layer_attr odb_layer_attr_enum;

/*--------------------------------*/

enum _odb_layer_context
   { ODB_L_LAYER_CONTEXT_BOARD = 1,
     ODB_L_LAYER_CONTEXT_MISC  = 2,
     ODB_L_LAYER_CONTEXT_ANY   = 3 };

typedef u_enum _odb_layer_context odb_layer_context_enum;

/*--------------------------------*/

enum _odb_res_calc_enum        /* used by ODB_RES_CALC */
   { ODB_L_RES_COUNT,
     ODB_L_RES_AVG,
     ODB_L_RES_SUM,
     ODB_L_RES_MIN,
     ODB_L_RES_MAX,
     ODB_L_RES_MEDIAN,
     ODB_L_RES_VARIANCE,
     ODB_L_RES_STD_DEV };

typedef u_enum _odb_res_calc_enum odb_res_calc_enum;

/*--------------------------------*/

enum _odb_layer_type {           /* Values may be ``or'ed''  */
   ODB_L_LAYER_TYPE_SIG  =    1,     /* to form later type masks */
   ODB_L_LAYER_TYPE_PG   =    2,
   ODB_L_LAYER_TYPE_MIX  =    4,
   ODB_L_LAYER_TYPE_SM   =    8,
   ODB_L_LAYER_TYPE_SS   =   16,
   ODB_L_LAYER_TYPE_SP   =   32,
   ODB_L_LAYER_TYPE_DRL  =   64,
   ODB_L_LAYER_TYPE_ROUT =  128,
   ODB_L_LAYER_TYPE_DOC  =  256,
   ODB_L_LAYER_TYPE_COMP =  512,
   ODB_L_LAYER_TYPE_MASK = 1024,
   ODB_L_LAYER_COND_PASTE= 2048,
   ODB_L_LAYER_DIELECTRIC= 4096,
};

typedef u_enum _odb_layer_type odb_layer_type_enum;

/*List of basic layer types names*/
#define ODB_L_LAYER_TYPE_NAME_SIG   "signal"
#define ODB_L_LAYER_TYPE_NAME_PG    "power_ground"
#define ODB_L_LAYER_TYPE_NAME_MIX   "mixed"
#define ODB_L_LAYER_TYPE_NAME_SM    "solder_mask"
#define ODB_L_LAYER_TYPE_NAME_SS    "silk_screen"
#define ODB_L_LAYER_TYPE_NAME_SP    "solder_paste"
#define ODB_L_LAYER_TYPE_NAME_DRL   "drill"
#define ODB_L_LAYER_TYPE_NAME_ROUT  "rout"
#define ODB_L_LAYER_TYPE_NAME_DOC   "document"
#define ODB_L_LAYER_TYPE_NAME_COMP  "components"
#define ODB_L_LAYER_TYPE_NAME_MASK  "mask"

/*List of extended layer types names*/
#define ODB_L_LAYER_TYPE_NAME_CARB	"carbon_mask"
#define ODB_L_LAYER_TYPE_NAME_DRL_MAP	"drill_map"
#define ODB_L_LAYER_TYPE_NAME_GOLD	"gold_mask"
#define ODB_L_LAYER_TYPE_NAME_PEEL	"peelable_mask"
#define ODB_L_LAYER_TYPE_NAME_OSP	"osp_mask"
#define ODB_L_LAYER_TYPE_NAME_SIT	"sit_mask"
#define ODB_L_LAYER_TYPE_NAME_SHLD	"shielding"
#define ODB_L_LAYER_TYPE_NAME_VCAPS	"via_caps"
#define ODB_L_LAYER_TYPE_NAME_VPLUGS	"via_plugs"

/*--------------------------------*/

enum _odb_layer_affected
   { ODB_L_LAYER_AFFECTED_OFF,
     ODB_L_LAYER_AFFECTED_ON };	

typedef u_enum _odb_layer_affected odb_layer_affected_enum;

/*--------------------------------*/

enum _odb_layer_work { ODB_L_LAYER_WORK_OFF,
                       ODB_L_LAYER_WORK_ON };	

typedef u_enum _odb_layer_work odb_layer_work_enum;

/*--------------------------------*/

enum _odb_layer_side
   { ODB_L_LAYER_SIDE_TOP  = 1,
     ODB_L_LAYER_SIDE_BOT  = 2,
     ODB_L_LAYER_SIDE_INN  = 4,
     ODB_L_LAYER_SIDE_NONE = 8 };

typedef u_enum _odb_layer_side odb_layer_side_enum;

/*--------------------------------*/

enum _odb_shape_type
   { ODB_L_SHAPE_TYPE_NONE   =   0,
     ODB_L_SHAPE_TYPE_POINT  =   1,
     ODB_L_SHAPE_TYPE_SEG    =   2,
     ODB_L_SHAPE_TYPE_CURVE  =   4,
     ODB_L_SHAPE_TYPE_LINE   =   8,
     ODB_L_SHAPE_TYPE_CIRCLE =  16,
     ODB_L_SHAPE_TYPE_SQUARE =  32,
     ODB_L_SHAPE_TYPE_RECT   =  64,
     ODB_L_SHAPE_TYPE_ARC    = 128,
     ODB_L_SHAPE_TYPE_POLY   = 256,
     ODB_L_SHAPE_TYPE_CONT   = 512 };

typedef u_enum _odb_shape_type odb_shape_type_enum;

/*--------------------------------*/

enum _odb_cont_type
   { ODB_CONT_TYPE_HDR,
     ODB_CONT_TYPE_POLY,
     ODB_CONT_TYPE_LIM,
     ODB_CONT_TYPE_SEG,
     ODB_CONT_TYPE_CURVE,
     ODB_CONT_TYPE_DEL };

typedef u_enum _odb_cont_type odb_cont_type_enum;

/*--------------------------------*/

enum _odb_subnet_type
{ ODB_L_SUBNET_TYPE_TOEPRINT,
  ODB_L_SUBNET_TYPE_VIA,
  ODB_L_SUBNET_TYPE_TRACE,
  ODB_L_SUBNET_TYPE_PLANE };

typedef u_enum _odb_subnet_type odb_subnet_type_enum;

/*--------------------------------*/

enum _odb_list_type
{ ODB_L_LIST_TYPE_SHAPE,
  ODB_L_LIST_TYPE_F,
  ODB_L_LIST_TYPE_NAME,
  ODB_L_LIST_TYPE_INT,
  ODB_L_LIST_TYPE_DOUBLE,
  ODB_L_LIST_TYPE_LAYER,
  ODB_L_LIST_TYPE_NEIGHBOR,
  ODB_L_LIST_TYPE_FUNCTION };

typedef u_enum _odb_list_type odb_list_type_enum;

#define ODB_L_LIST_NUMBER_TYPES  8

/*----------- INDICATOR RETURN VALUES -----------*/

enum _odb_calc_size           /* returned by ODB_SHAPE_SIZE_* */
   { ODB_L_CALC_SIZE_OK,
     ODB_L_CALC_SIZE_NA };

/*---------------- FUNCTION FLAGS ---------------*/

typedef u_enum _odb_calc_size odb_calc_size;

enum _odb_alarm             /* passed to ODB_RES_ADD_MEAS*    */
   { ODB_L_NO_ALARM,
     ODB_L_ALARM };

typedef u_enum _odb_alarm odb_alarm_enum;

enum _odb_subst_mode        /* passed to ODB_LAYER_SUBSTITUTE  */
   { ODB_L_SUBST_MANUAL,
     ODB_L_SUBST_AUTO,
     ODB_L_SUBST_MANUAL_IN_SELECTED,  /* Reference substitution ;
					 only for selected features */
     ODB_L_SUBST_AUTO_IN_SELECTED  }; /* Automatic substitution ;
					 only for selected features */
typedef u_enum _odb_subst_mode odb_subst_mode_enum;

enum _odb_subst_rot         /* passed to ODB_LAYER_SUBSTITUTE  */
   { ODB_L_SUBST_ROT_ONE,
     ODB_L_SUBST_ROT_ALL,
     ODB_L_SUBST_ROT_NON_90};
typedef u_enum _odb_subst_rot odb_subst_rot_enum;

enum _odb_subst_conn        /* passed to ODB_LAYER_SUBSTITUTE  */
   { ODB_L_SUBST_CONNECTED,
     ODB_L_SUBST_NON_CONNECTED };
typedef u_enum _odb_subst_conn odb_subst_conn_enum;

enum _odb_subst_flags       /* passed to ODB_LAYER_SUBSTITUTE  */
   { ODB_L_SUBST_FLAGS_NONE = 0,    /* Values may be ``or'ed''  */
     ODB_L_SUBST_FLAGS_NO_CONSTRUCT     =  ( 1 << 0 ),
     ODB_L_SUBST_FLAGS_NO_TYPE_ROUND    =  ( 1 << 1 ),
     ODB_L_SUBST_FLAGS_NO_TYPE_SQUARE   =  ( 1 << 2 ),
     ODB_L_SUBST_FLAGS_NO_TYPE_RECT     =  ( 1 << 3 ),
     ODB_L_SUBST_FLAGS_NO_TYPE_RECT_R   =  ( 1 << 4 ),
     ODB_L_SUBST_FLAGS_NO_TYPE_RECT_C   =  ( 1 << 5 ),
     ODB_L_SUBST_FALGS_NO_TYPE_OVAL     =  ( 1 << 6 ),
     ODB_L_SUBST_FLAGS_NO_TYPE_DIAMOND  =  ( 1 << 7 ),
     ODB_L_SUBST_FLAGS_NO_TYPE_OCTAGON  =  ( 1 << 8 ),
     ODB_L_SUBST_FLAGS_NO_TYPE_DONUT_R  =  ( 1 << 9 ),
     ODB_L_SUBST_FLAGS_NO_TYPE_DONUT_S  =  ( 1 << 10),
     ODB_L_SUBST_FLAGS_NO_TYPE_HEXAGON_L=  ( 1 << 11),
     ODB_L_SUBST_FLAGS_NO_TYPE_HEXAGON_S=  ( 1 << 12),
     ODB_L_SUBST_FLAGS_NO_TYPE_BFR      =  ( 1 << 13),
     ODB_L_SUBST_FLAGS_NO_TYPE_BFS      =  ( 1 << 14),
     ODB_L_SUBST_FLAGS_NO_TYPE_TRIANGLE =  ( 1 << 15),
     ODB_L_SUBST_FLAGS_NO_TYPE_OVAL_H   =  ( 1 << 16),
     ODB_L_SUBST_FLAGS_NO_TYPE_THERMAL_R=  ( 1 << 17),
     ODB_L_SUBST_FLAGS_NO_TYPE_THERMAL_S=  ( 1 << 18),
     ODB_L_SUBST_FLAGS_NO_TYPE_THERMAL_SR= ( 1 << 19),
     ODB_L_SUBST_FLAGS_NO_TYPE_THERMAL_RC= ( 1 << 20),
     ODB_L_SUBST_FLAGS_NO_TYPE_ELLIPSE  =  ( 1 << 21),
     ODB_L_SUBST_FLAGS_NO_TYPE_MORIE    =  ( 1 << 22)
   };
typedef u_enum _odb_subst_flags  odb_subst_flags_enum;

enum _odb_air_gap
   { ODB_L_NO_AIR_GAP,
     ODB_L_AIR_GAP };
typedef u_enum _odb_air_gap odb_air_gap_enum;

#define ODB_L_FC_CP_NO        0
#define ODB_L_FC_CP_YES       1
#define ODB_L_FC_CP_UPDATE    2

/*----------- OBJECT DESCRIPTOR STRUCTURE -----------*/

typedef	struct {         /* used for layer & list */
   int descriptor;
   int run_number;
} odb_obj_desc_struc;

/*---------------- FEATURE STRUCTURES ---------------*/

typedef struct {
   int x;
   int y;
} odb_point_struc;

typedef struct {
   odb_point_struc ps;
   odb_point_struc pe;
} _odb_f_line_struc;

typedef struct {
   odb_point_struc pc;
} _odb_f_pad_struc;

typedef struct {
   void *cont;
} _odb_f_surface_struc;

typedef struct {
   odb_point_struc ps;
   odb_point_struc pe;
   odb_point_struc pc;
} _odb_f_arc_struc;

typedef struct {
   odb_point_struc pos;
   char           *str;
   void*          fntid;
   union {
      struct {
	 int   xsize, ysize;
	 int   xspace;
	 float w_factor;
      } string;
      struct {
	 int width;
	 int height;
	 unsigned int type     :3; /* odb_bar_type_enum     */
	 unsigned int fasc     :1; /* odb_bar_asc_enum      */
	 unsigned int cs       :1; /* odb_bar_cs_enum       */
	 unsigned int bg       :1; /* odb_bar_bg_enum       */
	 unsigned int astr     :1; /* odb_bar_astr_enum     */
	 unsigned int astr_pos :1; /* odb_bar_astr_pos_enum */
	 unsigned int spare    :24;
      } bar;
   } u;
} _odb_f_text_struc;

typedef struct {
   int                magic;
   int                nf;
   union {
      odb_sym_t       sym;
      intptr_t        lyrid;
   } usym; 
   odb_obj_desc_struc ld;
   union {
      _odb_f_line_struc    line;
      _odb_f_pad_struc     pad;
      _odb_f_surface_struc surface;
      _odb_f_arc_struc     arc;
      _odb_f_text_struc    text;
   } f;
   double rotation;   /* rotation in radians (valid when angle = ODB_L_ANGLE_ANY ) */
   struct {
      unsigned int type     :4; /* odb_f_type_enum */
      unsigned int sym_type :3; /* odb_f_sym_enum */
      unsigned int polarity :1; /* odb_pol_enum */
      unsigned int angle    :3; /* odb_angle_enum. angle_idx: 0-0, 1-90, 2-180, 3-270, 7 - any angle rotation  */
      unsigned int mirror   :1; /* odb_mirror_enum */
      unsigned int cw       :1; /* odb_cw_ccw_enum */
      unsigned int spare1   :1;
      unsigned int select   :1; /* boolean */
      unsigned int drill    :1; /* boolean */
      unsigned int attr     :1; /* boolean */
      unsigned int bar      :1; /* odb_text_str_bar_enum */
      unsigned int dcode    :13;
      unsigned int text_ver :1; /* odb_text_ver_enum */
   } flags;
} odb_f_struc;

/*--------------- SHAPE STRUCTURES ----------------*/

typedef struct {
   odb_point_struc min;
   odb_point_struc max;
} odb_limits_struc;

typedef struct {
   odb_point_struc ps, pe;              /* Start & End points   */
} _odb_seg_struc;

typedef struct {
   odb_point_struc ps, pe;              /* Start & End points   */
   odb_point_struc pc;                  /* Center of circle */
   struct {
      unsigned int cw        : 1;       /* odb_cw_ccw_enum */
      unsigned int convexity : 1;       /* odb_convexity_enum */
      unsigned int spare     : 30;
   } flags;
} _odb_curve_struc;

typedef struct {
   _odb_seg_struc  seg;                 /* segment (skeleton)   */
   struct {
      unsigned int cap        :  1;     /* odb_cap_enum     */
      unsigned int r          : 31;     /* Radius (Half width)  */
   } w;
} _odb_line_struc;

typedef struct {
   odb_point_struc  pc;      	/* Center              */
   int		    r;          /* Radius              */
} _odb_circle_struc;

typedef struct {
   odb_point_struc  pc;      	/* Center              */
   int		    r;     	/* Radius (Half width) */
} _odb_square_struc;

typedef struct {
   odb_point_struc  pll;      	/* Lower left corner   */
   int		   w, h;    	/* Width & Height      */
} _odb_rect_struc;

typedef struct {
   _odb_curve_struc  c;  	/* skeleton            */
   struct {
     unsigned int   cap : 1;   /* odb_cap_enum     */
     unsigned int   r   :31;   /* Radius (Half width) */
   } w;
} _odb_arc_struc;

typedef struct {
   int  xff;
   int  yff;
   odb_limits_struc limits;    /* bounding limits of the contour/polygon */
} _odb_cont_lim_struc;

typedef struct {
   void              *cont;    /* For internal use */
   odb_obj_desc_struc obj;     /* For internal use */
} _odb_cont;

typedef struct {
   odb_shape_type_enum type;
   union {
       odb_point_struc	point;
      _odb_seg_struc	seg;
      _odb_curve_struc	curve;
      _odb_line_struc	line;
      _odb_circle_struc	circle;
      _odb_square_struc	square;
      _odb_rect_struc	rect;
      _odb_arc_struc	arc;
      _odb_cont         cont;
   } s;
} odb_mat_shape_struc;

typedef struct {
   int                 magic;
   odb_obj_desc_struc  ld;
   void*	       fcd;
   int                 nfc;
   int                 net;
   enum _odb_boolean   single;
   int                 nf;
   odb_f_type_enum     f_type;
   odb_f_sym_enum      f_sym_type;
   odb_sym_t           f_sym;
   odb_mat_shape_struc mshape;
} odb_shape_struc;


/* bi_tree structure for sorting and retrieval */
typedef struct {
   int key;      /* the field for sorting key */
   int l;  /* left-points (-1 for null) to the vertices with smaller key */
   int r;  /* right-points (-1 for null) to the vertices with greater key */
   int info;     /* information */
   int count;    /* how many times the key is repeated */
}  odb_btree_element_struct;

typedef struct {
    odb_shape_struc   shape;
    _odb_seg_struc    dist_seg;
    int               dist;
    int               rel;
} odb_neighbor_struc;

/*--------------- COMPONENT STRUCTURES ----------------*/

/* super structure */
typedef struct {
   int magic;
   int n_elem;              /* number of the elements in the array below */
   int n_alloc;             /* number of allocated elements. */
   odb_btree_element_struct *element;
}  odb_btree_struct;


typedef struct {
   int			magic;
   odb_obj_desc_struc	ld;
   int			ncomp ;
   odb_name		name ;
   odb_name		part_name ;
   odb_name		pkg_name ;
   odb_point_struc	position ;
   double		rotation ;
   int			height ;
   int			pitch ;
   boolean		mirror ;
   int			num_toeprints ;
   int			spare[20];
} odb_comp_struc ;

/*----------------- PARAMETERS STRUCTURES -------------------- */

/* Type of parameters passed to the ODB library from a program */

enum _odb_ptype
   { ODB_PTYPE_S = 100,
     ODB_PTYPE_I,
     ODB_PTYPE_SYM,
     ODB_PTYPE_D,
     ODB_PTYPE_SP,
     ODB_PTYPE_IP,
     ODB_PTYPE_SYM_P,
     ODB_PTYPE_DP,
     ODB_PTYPE_SHAPE_P,
     ODB_PTYPE_F_P,
     ODB_PTYPE_CATEGORIES_P,
     ODB_PTYPE_PROG_PARAMS_P,
     ODB_PTYPE_REL_P,
     ODB_PTYPE_CAP,
     ODB_PTYPE_OBJ,
     ODB_PTYPE_OBJ_P,
     ODB_PTYPE_VOID_P,
     ODB_PTYPE_COMP_P
};

typedef u_enum _odb_ptype odb_ptype_enum;

#define ODB_MAX_PARAMS 32

typedef struct {
   odb_ptype_enum         type;
   union {
      char               *s;
      int                 i;
      odb_sym_t	          sym;
      double              d;
      char              **sp;
      int      	         *ip;
      odb_sym_t		 *sym_p;
      double	         *dp;
      odb_shape_struc    *shape_p;
      odb_f_struc        *f_p;
      odb_rel_enum       *rel_p;
      odb_cap_enum        cap;
      odb_categories     *categories_p;
      odb_prog_params    *prog_params_p;
      odb_obj_desc_struc  obj;
      odb_obj_desc_struc *obj_p;
      void               *void_p;
      odb_comp_struc     *comp_p;
   } v;
} odb_param_struc;


/*---------ODB CALLS PREPARATION MACROS ---------*/

#define ODB_NUM_PARAMS odb_params.num_params

#define ODB_PARAMS_INIT(_action)     \
 { odb_params.action     = _action;  \
   odb_params.asc_action = #_action; \
   odb_params.env.fname  = __FILE__; \
   odb_params.env.line   = __LINE__; \
   odb_params.num_params = 0; }

#define ODB_PARAM_SET_S(_pvalue)                          \
 { odb_params.params[ODB_NUM_PARAMS].type = ODB_PTYPE_S;  \
   odb_params.params[ODB_NUM_PARAMS].v.s  = _pvalue;      \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_I(_pvalue)                          \
 { odb_params.params[ODB_NUM_PARAMS].type = ODB_PTYPE_I;  \
   odb_params.params[ODB_NUM_PARAMS].v.i  = _pvalue;      \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_SYM(_pvalue)                         \
{ odb_params.params[ODB_NUM_PARAMS].type = ODB_PTYPE_SYM;  \
    odb_params.params[ODB_NUM_PARAMS].v.sym  = _pvalue;    \
    ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_D(_pvalue)                          \
 { odb_params.params[ODB_NUM_PARAMS].type = ODB_PTYPE_D;  \
   odb_params.params[ODB_NUM_PARAMS].v.d  = _pvalue;      \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_SP(_pvalue)                          \
 { odb_params.params[ODB_NUM_PARAMS].type = ODB_PTYPE_SP;  \
   odb_params.params[ODB_NUM_PARAMS].v.sp = &(_pvalue);    \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_IP(_pvalue)                          \
 { odb_params.params[ODB_NUM_PARAMS].type = ODB_PTYPE_IP;  \
   odb_params.params[ODB_NUM_PARAMS].v.ip = &(_pvalue);    \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_SYM_P(_pvalue)                         \
{ odb_params.params[ODB_NUM_PARAMS].type = ODB_PTYPE_SYM_P;  \
    odb_params.params[ODB_NUM_PARAMS].v.sym_p = &(_pvalue);  \
    ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_DP(_pvalue)                          \
 { odb_params.params[ODB_NUM_PARAMS].type = ODB_PTYPE_DP;  \
   odb_params.params[ODB_NUM_PARAMS].v.dp = &(_pvalue);    \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_SHAPE(_pvalue)                                \
 { odb_params.params[ODB_NUM_PARAMS].type      = ODB_PTYPE_SHAPE_P; \
   odb_params.params[ODB_NUM_PARAMS].v.shape_p = _pvalue;           \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_F(_pvalue)                            \
 { odb_params.params[ODB_NUM_PARAMS].type  = ODB_PTYPE_F_P; \
   odb_params.params[ODB_NUM_PARAMS].v.f_p = _pvalue;       \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_COMP(_pvalue)                         \
 { odb_params.params[ODB_NUM_PARAMS].type  = ODB_PTYPE_COMP_P; \
   odb_params.params[ODB_NUM_PARAMS].v.comp_p = _pvalue;       \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_RELP(_pvalue)                         \
 { odb_params.params[ODB_NUM_PARAMS].type   = ODB_PTYPE_REL_P; \
   odb_params.params[ODB_NUM_PARAMS].v.rel_p= &(_pvalue);   \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_CAP(_pvalue)                          \
 { odb_params.params[ODB_NUM_PARAMS].type   = ODB_PTYPE_CAP;\
   odb_params.params[ODB_NUM_PARAMS].v.cap  = _pvalue;      \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_CATEGORIES(_pvalue)                   \
 { odb_params.params[ODB_NUM_PARAMS].type = ODB_PTYPE_CATEGORIES_P; \
   odb_params.params[ODB_NUM_PARAMS].v.categories_p = _pvalue;      \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_PROG_PARAMS(_pvalue)                  \
 { odb_params.params[ODB_NUM_PARAMS].type = ODB_PTYPE_PROG_PARAMS_P;\
   odb_params.params[ODB_NUM_PARAMS].v.prog_params_p = _pvalue;     \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_OBJ(_pvalue)                          \
 { odb_params.params[ODB_NUM_PARAMS].type = ODB_PTYPE_OBJ;  \
   odb_params.params[ODB_NUM_PARAMS].v.obj  = _pvalue;      \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_OBJP(_pvalue)                         \
 { odb_params.params[ODB_NUM_PARAMS].type = ODB_PTYPE_OBJ_P;\
   odb_params.params[ODB_NUM_PARAMS].v.obj_p  = &(_pvalue); \
   ODB_NUM_PARAMS++; }

#define ODB_PARAM_SET_VOID(_pvalue)                         \
 { odb_params.params[ODB_NUM_PARAMS].type   = ODB_PTYPE_VOID_P;     \
   odb_params.params[ODB_NUM_PARAMS].v.void_p = (void *)&(_pvalue); \
   ODB_NUM_PARAMS++; }

#define ODB_CALL                              \
 { odb_status = odb__call_do(&odb_params);    \
   if (odb_status == ODB_L_STOPPED ||         \
      (odb_status != 0 && !odb_ignore_one_status)){ \
      odb__exec_error(odb_status, __LINE__);  \
      return(odb_status); } \
   odb_ignore_one_status = FALSE ; }

#define ODB_CALL_IGNORE_ONE_STATUS()          \
{ odb_ignore_one_status = TRUE; }

#define ODB_CALL_GET_STATUS(_odb_status_new)  \
{ _odb_status_new = odb_status; }


/* ------------------------------------------------------- */

enum _odb_act {                         /* Routines of the odb library      */

   ODB_ACT_EDT_ADD_ATTR              = 5,   /* Add new internal feature attribute BL 20.04.07 */
   ODB_ACT_EDT_CLOSE_LIC             = 7,
   ODB_ACT_EDT_COMMAND               = 10,
   ODB_ACT_EDT_GET_JOB_STEP_NAME     = 12,
   ODB_ACT_EDT_GET_MIN_BRUSH         = 13,
   ODB_ACT_EDT_GET_STEP_ATTR         = 14,
   ODB_ACT_EDT_MESSAGE               = 15,
   ODB_ACT_EDT_GET_JOB_ATTR          = 16,
   ODB_ACT_EDT_OPEN_LIC              = 22,
   ODB_ACT_EDT_PROGRESS_FRAME_CLOSE  = 25,
   ODB_ACT_EDT_PROGRESS_FRAME_OPEN   = 30,
   ODB_ACT_EDT_PROGRESS_STEP_ADVANCE = 35,
   ODB_ACT_EDT_PROGRESS_STEP_CLOSE   = 40,
   ODB_ACT_EDT_PROGRESS_STEP_OPEN    = 45,
   ODB_ACT_EDT_PROGRESS_STEP_RESET   = 50,
   ODB_ACT_EDT_PROGRESS_TITLE        = 55,
   ODB_ACT_EDT_REFRESH               = 20,
   ODB_ACT_EDT_RUN_LIMITS            = 57,
   ODB_ACT_EDT_SCRIPT                = 60,
   ODB_ACT_EDT_RUN_IN_PROFILE        = 65,   /* JH */

   ODB_ACT_F_ADD                = 105,
   ODB_ACT_F_AREA               = 107,
   ODB_ACT_F_CHANGE             = 110,
   ODB_ACT_F_CONV_STD           = 160,
   ODB_ACT_F_COPY               = 115,
   ODB_ACT_F_DELETE             = 120,
   ODB_ACT_F_IS_DELETED         = 121,    /* BL 21.12.06 */
   ODB_ACT_F_IS_MULTIPOLAR      = 122,    /* MIC 12.04.10 */
   ODB_ACT_F_DELETE_ATTR        = 125,
   ODB_ACT_F_GET_ATTR_LIST      = 128,
   ODB_ACT_F_GET_ATTR           = 130,
   ODB_ACT_F_GET_ATTR_STR       = 131,
   ODB_ACT_F_GET_SYM_NAME       = 135,
   ODB_ACT_F_GET_SYM_RES        = 137,
   ODB_ACT_F_GET_LIMITS         = 140,
   ODB_ACT_F_GET_TOUCHING       = 141,
   ODB_ACT_F_NF_TO_SHAPE_LIST   = 142,
   ODB_ACT_F_IS_STANDARD        = 143,
   ODB_ACT_F_IS_ROTATED         = 144,
   ODB_ACT_F_RESIZE             = 145,
   ODB_ACT_F_RESIZE_VERIFY      = 146,
   ODB_ACT_F_RESIZE_BY_XY       = 148,
   ODB_ACT_F_RESIZE_FACTOR      = 149,
   ODB_ACT_F_SURROUND           = 147,
   ODB_ACT_F_SET_ATTR           = 150,
   ODB_ACT_F_SET_SYM_RES        = 152,
   ODB_ACT_F_TO_SHAPE_LIST      = 155,
   ODB_ACT_F_LINE_ENLARGE       = 156,
   ODB_ACT_F_LINE_MOVE          = 157,
   ODB_ACT_F_LINE_SMOOTH        = 158,
   ODB_ACT_F_LINE_CLIP          = 159,
   ODB_ACT_F_VALIDATE           = 165,
   ODB_ACT_F_DRAWN_TO_CONT      = 166,
   ODB_ACT_F_SET_FONT		= 167,   
   ODB_ACT_F_TAPER              = 168,
   ODB_ACT_F_SURFACE_COUNT_ISLANDS = 1680,

   ODB_ACT_EDA_ALL_INFO         = 170,
   ODB_ACT_EDA_CLASSIFY_COMP_SEG= 172,
   ODB_ACT_EDA_COMP_DELETE_ATTR = 175,
   ODB_ACT_EDA_COMP_GET         = 180,
   ODB_ACT_EDA_COMP_GET_ATTR    = 182,
   ODB_ACT_EDA_COMP_GET_TYPE    = 183,
   ODB_ACT_EDA_COMP_SET_ATTR    = 186,
   ODB_ACT_EDA_COMP_GET_PADS    = 188,
   ODB_ACT_EDA_F_FIND           = 190,
   ODB_ACT_EDA_FID_GET          = 192,
   ODB_ACT_EDA_LYR_GET		= 193,
   ODB_ACT_EDA_NET_GET		= 194,
   ODB_ACT_EDA_SUBNET_GET	= 196,
   ODB_ACT_EDA_TOEP_SIDE        = 197,
   ODB_ACT_EDA_TOEP_GET	        = 198,
   ODB_ACT_EDA_TOEP_SHAPE_GET	= 199,

   /*ODB_ACT_LAYER_DESTRUCT_GROUPS = 201,   TBD: Separate destructor for layer groups object */
   ODB_ACT_LAYER_CLEAR          = 202,
   ODB_ACT_LAYER_DELETE_ALL     = 203,
   ODB_ACT_LAYER_DETECT_PADS	= 204,
   ODB_ACT_LAYER_CLOSE          = 205,
   ODB_ACT_LAYER_CONTOURIZE     = 207,  /* Note: The integer values of the  */
   ODB_ACT_LAYER_CONTOURIZE_FILTER = 208,
   ODB_ACT_LAYER_COPY           = 210,  /*       literals must always       */
   ODB_ACT_LAYER_COPY_TEMP      = 211,
   ODB_ACT_LAYER_COPY_KEEP_SELECTED = 212,
   ODB_ACT_LAYER_COPPER_AREA    = 215,  /*       remain the same to allow   */
   ODB_ACT_LAYER_COUNT_F        = 220,  /*       compatibility between      */
   ODB_ACT_LAYER_COUNT_NET      = 222,  /*       versions.                  */
   ODB_ACT_LAYER_COUNT_TRUE_NET = 1223,
   ODB_ACT_LAYER_COUNT_SHAPE    = 225,  /*       Any routines added must be */
   ODB_ACT_LAYER_CREATE         = 230,  /*       placed at the end of a set */
   ODB_ACT_LAYER_CREATE_TEMP    = 231,  /*       or in a new set.           */
   ODB_ACT_LAYER_DELETE         = 235,  /*       The alpahbetical order has */
   ODB_ACT_LAYER_DRILL_TERM     = 237,  /*                                  */
   ODB_ACT_LAYER_DRILL_THROUGH  = 238,  /*       to be kept to facilitate   */
   ODB_ACT_LAYER_DRILLS         = 240,  /*       easy searching (note the   */
   ODB_ACT_LAYER_FATR_EXISTS    = 242,
   ODB_ACT_LAYER_F_CONTOURIZE   = 243,
   ODB_ACT_LAYER_EXISTS         = 245,  /*       gaps between adjacent      */
   ODB_ACT_LAYER_GET_USER_ATTR  = 247,/*       literals)                  */
   ODB_ACT_LAYER_GET_ATTR       = 250,
   ODB_ACT_LAYER_GET_BOARD_NET_BY_NET = 251,
   ODB_ACT_LAYER_GET_DATUM      = 252,
   ODB_ACT_LAYER_GET_PROFILE    = 255,
   ODB_ACT_LAYER_GET_PROFILE_AND_HOLES = 257, /*get the outline profile and the holes in it*/
   ODB_ACT_LAYER_GET_NET        = 260,  /* Get shapes according to net */
   ODB_ACT_LAYER_GET_NET_ALL    = 261,  /* Get shapes according to net including contact points */
   ODB_ACT_LAYER_GET_NET_FILTER = 262,  /* Get shapes according to net, using filters. */
   ODB_ACT_LAYER_GET_NET_CONTOUR = 263, /* Get layer net contour */
   ODB_ACT_LAYER_GET_SHAPE      = 265,
   ODB_ACT_LAYER_GET_SHAPE_BY_NFC = 267,/* get a specific shape */
   ODB_ACT_LAYER_GET_SHAPE_FILTER = 268,/* Get layer's shapes, use filter to skip unwanted shapes.*/
   ODB_ACT_LAYER_GET_F          = 270,
   ODB_ACT_LAYER_GET_F_AREA     = 271,
   ODB_ACT_LAYER_GET_F_BY_NF    = 272,
   ODB_ACT_LAYER_GET_F_EXT      = 273,
   ODB_ACT_LAYER_GET_F_FILTER   = 274,
   ODB_ACT_LAYER_GET_LNAME      = 275,
   ODB_ACT_LAYER_GET_F_SYM_NUM_BY_NF=276,
   ODB_ACT_LAYER_GET_F_TYPE_BY_NF=277,
   ODB_ACT_LAYER_GET_NETS_BY_NF	= 278,
   ODB_ACT_LAYER_GET_NET_BY_POINT= 279,
   ODB_ACT_LAYER_GET_WORK_LNAME = 280,
   ODB_ACT_LAYER_HATCH          = 283,
   ODB_ACT_LAYER_IS_SELECTED_NF = 284,
   ODB_ACT_LAYER_LIMITS         = 285,
   ODB_ACT_LAYER_NAME_TO_LIST   = 290,
   ODB_ACT_LAYER_NAME_TO_LIST_POS = 291,
   ODB_ACT_LAYER_OPEN           = 295,
   ODB_ACT_LAYER_OPEN_POS       = 296,
   ODB_ACT_LAYER_PROFILE        = 300,
   ODB_ACT_LAYER_SELECT_NF      = 303,
   ODB_ACT_LAYER_RENAME         = 305,
   ODB_ACT_LAYER_SELECT_CLEAR   = 308,
   ODB_ACT_LAYER_SET_ATTR       = 310,
   ODB_ACT_LAYER_CONNECT        = 311,
   ODB_ACT_LAYER_WAS_OPENED_POS = 312,

   ODB_ACT_LAYER_SUBPROFILES    = 313,
   ODB_ACT_LAYER_OPTIMIZE_POLARITY = 314,
   ODB_ACT_LAYER_SUBSTITUTE     = 315,
   ODB_ACT_LAYER_SUBSTITUTE_CAT = 316,  /* return list of different categories */
   ODB_ACT_LAYER_SUBSTITUTE_CAT2 = 317,
   ODB_ACT_LAYER_SUBSTITUTE_TRACES= 318,
   ODB_ACT_LAYER_LAYER_SUBPROFILES = 319, 
   ODB_ACT_LAYER_SYNC           = 320,

   ODB_ACT_LAYER_QUICK_NEXT_DEL = 325,
   ODB_ACT_LAYER_UNDO           = 332,
   ODB_ACT_LAYER_APPEND_LAYER   = 333, 
   ODB_ACT_LAYER_UNDO_FETCH     = 334,  /* fetch the undo data into a command
					   string*/
   ODB_ACT_LAYER_UNDO_GET_F     = 336,  /* fetch the undo data into a feature
					   list */
   ODB_ACT_LAYER_GET_EXPOSED_AREA_LAYERS = 337, /* get exposed coppers layers + sm layers (bottom & top ) */

   ODB_ACT_LAYER_UNDO_MARK      = 338,  /* create an undo level for a layer */
   ODB_ACT_LAYER_PHYS_COUNT_F	= 339,
    
   ODB_ACT_LAYER_UNDO_RESET     = 340,  /* reset the given undo level */
   ODB_ACT_LAYER_UNMERGE	= 341,
   ODB_ACT_LAYER_DELETE_SHAPE_LIST= 342,/* delete shapelist           */
   ODB_ACT_LAYER_SET_SPAN         = 343,  
   ODB_ACT_LAYER_COMPENSATE       = 344,  /* compensate rout layer      */
   ODB_ACT_LAYER_GET_TYPE_NAME    = 345,  /* return the type name of a layer  */
   ODB_ACT_LAYER_SET_TYPE_BY_NAME = 346,  /* set layer type according to name */
   ODB_ACT_LAYER_VERIFY_TOOLING_HOLES_SET = 321,
   ODB_ACT_LAYER_GET_MASK_LAYER   = 347,
   ODB_ACT_LAYER_SET_MASK_LAYER   = 348,
   ODB_ACT_LAYER_FILTER_DRAWN	  = 349,
   ODB_ACT_LAYER_FILTER_CROSSHATCH  = 351, 
   ODB_ACT_LAYER_GET_STEP_RIGID_FLEX_AREAS = 1200,
   ODB_ACT_LAYER_GET_RIGID_FLEX_AREAS = 1201,
   ODB_ACT_LAYER_GET_LAYER_PROFILE = 1202,
   ODB_ACT_LAYER_CREATE_SHAPE_LIST = 1203,  /* create shape list BL 29.07.11 */
   ODB_ACT_LAYER_ORIENTATION    = 1798,

   ODB_ACT_RES_ADD_ATTR         = 350,
   ODB_ACT_RES_ADD_CATEGORIES   = 355,
   ODB_ACT_RES_ADD_MEAS         = 360,
   ODB_ACT_RES_ADD_MEAS_FIX     = 362,
   ODB_ACT_RES_ADD_MEAS_F       = 365,
   ODB_ACT_RES_ADD_MEAS_F_FIX   = 367,
   ODB_ACT_RES_ADD_ONE_CATEGORY	= 368,
   ODB_ACT_RES_CALC             = 370,
   ODB_ACT_RES_CATEGORY_EXISTS  = 371,
   ODB_ACT_RES_CLASSIFY_LOCATION= 372,
   ODB_ACT_RES_CLASSIFY_BY_PROC = 373,
   ODB_ACT_RES_GET_ATTR         = 375,
   ODB_ACT_RES_GET_CATEGORIES   = 377,
   ODB_ACT_RES_GET_CATEGORY_TITLE = 378,
   ODB_ACT_RES_GET_CATEGORY_NAME  = 379,
   ODB_ACT_RES_GET_LAYER        = 380,
   ODB_ACT_RES_GET_MEAS         = 385,
   ODB_ACT_RES_GET_MEAS_SIZE    = 390,
   ODB_ACT_RES_GET_MEAS_ID_TEXT = 392,
   ODB_ACT_RES_MEAS_SORT	= 393,
   ODB_ACT_RES_TYPICAL_SIZE     = 395,
   ODB_ACT_RES_REPORT_ACTION    = 400,
   ODB_ACT_RES_REPORT_ALARMS    = 405,
   ODB_ACT_RES_REPORT_HDR       = 410,
   ODB_ACT_RES_REPORT_HIST      = 415,
   ODB_ACT_RES_REPORT_TAG       = 420,
   ODB_ACT_RES_REPORT_TEXT      = 425,
   ODB_ACT_RES_SET_DISP_LYRS    = 430,
   ODB_ACT_RES_SET_MEAS_SCALAR  = 432,
   ODB_ACT_RES_SET_MEAS_SCALAR_SQR = 434,
   ODB_ACT_RES_SORT_CATEGORIES    = 435,
   ODB_ACT_RES_SET_MEAS_ID_SCALAR = 437,
   ODB_ACT_RES_SET_MEAS_ID_TEXT   = 438,
   ODB_ACT_RES_GET_RANGE          = 440,
   ODB_ACT_RES_SET_CATEGORY_LIMITS_SENSITIVE = 442,
   ODB_ACT_RES_CALC_RANGE         = 444,
   ODB_ACT_RES_UPDATE_MEAS        = 445,
   ODB_ACT_RES_UPDATE_MEAS_TEXT   = 1350,
   ODB_ACT_RES_GET_MEAS_SPACING   = 446,
   ODB_ACT_RES_GET_MEAS_ADDED     = 428,
   ODB_ACT_RES_SET_MEAS_DELETED   = 447,
   ODB_ACT_RES_SET_SUB_CATEGORY   = 448,
   ODB_ACT_RES_GET_SUB_CATEGORIES = 449,
   ODB_ACT_RES_GET_NUM_MEAS       = 426,
   ODB_ACT_RES_UNDO_MEAS_FIXES    = 427,

   ODB_ACT_SETUP_GET_ERF_UNITS    = 450,
   ODB_ACT_SETUP_GET_ERF_VAR      = 455,
   ODB_ACT_SETUP_CHECK_ERF_VAR    = 457,
   ODB_ACT_SETUP_GET_ERF_VAR_MIL  = 460, /* Unused.  Here for completeness */
   ODB_ACT_SETUP_GET_PARAMS       = 465,
   ODB_ACT_SETUP_GET_PARAM_OPTION = 470,
   ODB_ACT_SETUP_SET_MODIFY       = 475,
   ODB_ACT_SETUP_SET_VERSION      = 480,

   ODB_ACT_SHAPE_DEBUG_WRITE_XML  = 501,
   ODB_ACT_SHAPE_AIR_GAP_LAYER  = 505,
   ODB_ACT_SHAPE_AIR_GAP_LIST   = 510,
   ODB_ACT_SHAPE_AREA_INTER     = 515,
   ODB_ACT_SHAPE_AREA_INTER_TOL = 516,
   ODB_ACT_SHAPE_AREA_DIFF      = 520,
   ODB_ACT_SHAPE_AREA_DIFF_TOL  = 521,
   ODB_ACT_SHAPE_AREA_RECT_COVER= 522,
   ODB_ACT_SHAPE_CLIP           = 523,
   ODB_ACT_SHAPE_AREA_UNION     = 525,
   ODB_ACT_SHAPE_AREA_UNION_TOL = 527,
   ODB_ACT_SHAPE_CONTOUR        = 528,
   ODB_ACT_SHAPE_BOTTLENECK     = 529,
   ODB_ACT_SHAPE_CENTER         = 530,
   ODB_ACT_SHAPE_MIDPT          = 532,
   ODB_ACT_SHAPE_CENTER_LIST    = 535,
   ODB_ACT_SHAPE_CLEAN_SURFACE  = 536,
   ODB_ACT_SHAPE_CLOSE_TRI      = 537,
   ODB_ACT_SHAPE_CLEAN_SIP      = 538,
   ODB_ACT_SHAPE_COPPER_AREA    = 540,
   ODB_ACT_SHAPE_CALC_AREA      = 541,
   ODB_ACT_SHAPE_COUNT_CONT_NREC = 542,
   ODB_ACT_SHAPE_COVER_LAYER    = 545,
   ODB_ACT_SHAPE_COVER_LIST     = 550,
   ODB_ACT_SHAPE_COVER_LIST_MAX = 551,
   ODB_ACT_SHAPE_SEG_COVER_LIST = 552,
   ODB_ACT_SHAPE_DIST           = 555,
   ODB_ACT_SHAPE_DIST_MAX       = 556,
   ODB_ACT_SHAPE_DIST_TO_FC_MAX = 557,
   ODB_ACT_SHAPE_DIST_LAYER     = 560,
   ODB_ACT_SHAPE_DIST_LIST      = 565,
   ODB_ACT_SHAPE_DIST_NET       = 567,
   ODB_ACT_SHAPE_END_SHAPE      = 570,
   ODB_ACT_SHAPE_ENCLOSED_RECT  = 571,
   ODB_ACT_SHAPE_LINE_END_SEG   = 572,
   ODB_ACT_SHAPE_EXPAND         = 575,
   ODB_ACT_SHAPE_EXT_POINT      = 580,           /* extrapolate */
   ODB_ACT_SHAPE_FILL           = 585,
   ODB_ACT_SHAPE_GET_HOLES      = 590,
   ODB_ACT_SHAPE_GET_ISLAND     = 595,
   ODB_ACT_SHAPE_GET_CONT_EDGES = 596,
   ODB_ACT_SHAPE_GET_NEIGHBORS        = 598,
   ODB_ACT_SHAPE_GET_NEIGHBORS_FILTER = 597,
   ODB_ACT_SHAPE_GET_NEIGHBORS_SR     = 599,
   ODB_ACT_SHAPE_INTERSECT      = 600,
   ODB_ACT_SHAPE_INTERSECT_VIRT = 601,
   ODB_ACT_SHAPE_LEFT_SLIVER    = 605,
   ODB_ACT_SHAPE_LIMITS         = 610,
   ODB_ACT_SHAPE_LIMITS_LIST    = 615,
   ODB_ACT_SHAPE_LIST_NEAR_LAYER= 620,
   ODB_ACT_SHAPE_LIST2CHULL     = 622,
   ODB_ACT_SHAPE_LIST2CONT      = 623,
   ODB_ACT_SHAPE_MOVE_CONT      = 624,
   ODB_ACT_SHAPE_MOVE_SEG       = 625,
   ODB_ACT_SHAPE_NEAR_LAYER     = 630,
   ODB_ACT_SHAPE_NEAR_LAYER_REF = 631,
   ODB_ACT_SHAPE_NEAR_LAYER2    = 632,
   ODB_ACT_SHAPE_NEAR_LAYER_COARSE  = 633,
   ODB_ACT_SHAPE_NEAR_LIST      = 635,
   ODB_ACT_SHAPE_NEAR_LIST_COARSE   = 636,
   ODB_ACT_SHAPE_NEAR_OUTLINE_LAYER = 637,
   ODB_ACT_SHAPE_GET_TOUCHING   = 638,
   ODB_ACT_SHAPE_POINTS_TO_SEG  = 639,
   ODB_ACT_SHAPE_PAR_DIST       = 640,
   ODB_ACT_SHAPE_POLYS2CONT     = 641,
   ODB_ACT_SHAPE_RESIZE         = 642,
   ODB_ACT_SHAPE_RESIZE_IDENTICAL   = 643,
   ODB_ACT_SHAPE_SIN            = 644,
   ODB_ACT_SHAPE_SIZE_LINE      = 645,
   ODB_ACT_SHAPE_SIZE_LINE_LIST = 647,
   ODB_ACT_SHAPE_SIZE_PAD       = 650,
   ODB_ACT_SHAPE_SMOOTH_LIST    = 652,
   ODB_ACT_SHAPE_SIMPLIFY_AND_SMOOTH_LIST = 1653,
   ODB_ACT_SHAPE_SKELETON       = 655,
   ODB_ACT_SHAPE_SLIVER         = 657,
   ODB_ACT_SHAPE_SORT_RECTS     = 660,
   ODB_ACT_SHAPE_SORT_RECTS_2   = 662,
   ODB_ACT_SHAPE_SORT_RECTS_3   = 663,
   ODB_ACT_SHAPE_TANGENT        = 665,
   ODB_ACT_SHAPE_CREATE_TANGENT_CURVE = 1666,
   ODB_ACT_SHAPE_CREATE_TANGENT_CIRCLE = 1667,
   ODB_ACT_SHAPE_TAPER          = 667,
   ODB_ACT_SHAPE_TOUCH          = 670,
   ODB_ACT_SHAPE_TOUCH_LAYER    = 671,
   ODB_ACT_SHAPE_TOUCH_LIST     = 672,
   ODB_ACT_SHAPE_TRY_PAD        = 675,
   ODB_ACT_SHAPE_RESIZE_CONT    = 680,
   ODB_ACT_SHAPE_RESIZE_CONT_2LIST   = 685,
   ODB_ACT_SHAPE_IS_CONVEX           = 690,
   ODB_ACT_SHAPE_BREAK_ARC           = 695,
   ODB_ACT_SHAPE_GAPS_LIST           = 696,
   ODB_ACT_SHAPE_EQUAL_SHAPES        = 697,
   ODB_ACT_SHAPE_GAPS_LIST_INTERSECT = 698,
   ODB_ACT_SHAPE_LINE_TRANSFORM      = 699,
   ODB_ACT_SHAPE_CALC_TANGENT_SHAPES = 1300,
   ODB_ACT_SHAPE_GET_CONT_ENCLOSE_CIRCLE = 1301,
   ODB_ACT_SYMBOL_BUILD_RECT    = 700,
   ODB_ACT_SYMBOL_BUILD_SMD     = 702,
   ODB_ACT_SYMBOL_BUILD_SMD_ROT = 703,
   ODB_ACT_SYMBOL_BUILD_THERMAL = 704,
   ODB_ACT_SYMBOL_CREATE        = 705,
   ODB_ACT_SYMBOL_BUILD_DONUT   = 707,
   ODB_ACT_SYMBOL_BUILD_NEW_THERMAL = 708,
   ODB_ACT_SYMBOL_BUILD_NEW_DONUT   = 709,
   ODB_ACT_SYMBOL_F_ADD         = 710,
   ODB_ACT_SYMBOL_GET           = 715,
   ODB_ACT_SYMBOL_GET_NAME      = 720,
   ODB_ACT_SYMBOL_GET_NAME_2  = 721,
   ODB_ACT_SYMBOL_CHANGE_SHAPE  = 723,
   ODB_ACT_SYMBOL_CHANGE_SHAPE_2  = 724,
   ODB_ACT_SYMBOL_GET_RECT_SIZES= 725,
   ODB_ACT_SYMBOL_GET_W_H       = 726,
   ODB_ACT_SYMBOL_GET_SMD_PARAMS= 727,
   ODB_ACT_SYMBOL_GET_SMD_PARAMS_ROT = 728,
   ODB_ACT_SYMBOL_GET_W_H_2       = 729, 
   ODB_ACT_SYMBOL_GET_THERMAL_PARAM = 730,
   ODB_ACT_SYMBOL_GET_NEW_THERMAL_PARAM = 731,
   ODB_ACT_SYMBOL_GET_DONUT_PARAMS  = 733,
   ODB_ACT_SYMBOL_GET_NEW_DONUT_PARAMS  = 734,
   ODB_ACT_SYMBOL_FILL          = 735,
   ODB_ACT_SYMBOL_GET_CROSS_TSHAPE_PARAMS = 736,
   ODB_ACT_SYMBOL_BUILD_CROSS_TSHAPE = 737,
   ODB_ACT_SYMBOL_VALIDATE      = 740,

   ODB_ACT_UTILS_BELL           = 750,
   ODB_ACT_UTILS_CMP_W          = 752,
   ODB_ACT_UTILS_UNITS          = 755,
   ODB_ACT_UTILS_INDEX_CREATE   = 760,
   ODB_ACT_UTILS_INDEX_DESTROY  = 761,
   ODB_ACT_UTILS_INDEX_INSERT   = 762,
   ODB_ACT_UTILS_INDEX_REMOVE   = 763,
   ODB_ACT_UTILS_INDEX_UPDATE   = 764,
   ODB_ACT_UTILS_INDEX_SEARCH   = 765,
   ODB_ACT_UTILS_SORT_TCREATE   = 770,
   ODB_ACT_UTILS_SORT_TDESTROY  = 773,
   ODB_ACT_UTILS_SORT_TADD      = 776,
   ODB_ACT_UTILS_SORT_TFIND     = 779,
   ODB_ACT_UTILS_GET_RESOURCE   = 780,
   ODB_ACT_UTILS_GET_CONT_OP_ACCURACY = 785,
   ODB_ACT_UTILS_SET_CONT_OP_ACCURACY = 790,
   ODB_ACT_UTILS_GET_CFG        = 795,
   ODB_ACT_UTILS_IS_FLEX        = 797,

   ODB_ACT_SRL_GET_SR_LAYER     = 800,
   ODB_ACT_SRL_GET_SR_INFO      = 805,
   ODB_ACT_SRL_GET_PCB_COUNT    = 806,
   ODB_ACT_SRL_CONTOURIZE       = 810,
   ODB_ACT_SRL_GET_F            = 815,
   ODB_ACT_SRL_GET_F_ATTR       = 820,
   ODB_ACT_SRL_GET_SHAPE        = 825,
   ODB_ACT_SRL_GET_BOARD_NET_BY_NET = 830,
   ODB_ACT_SRL_COUNT_NET        = 835,
   ODB_ACT_SRL_COUNT_F          = 836,
   ODB_ACT_SRL_COUNT_SHAPE      = 837,
   ODB_ACT_SRL_GET_NET          = 840,
   ODB_ACT_SRL_GET_PROFILE      = 845,
   ODB_ACT_SRL_GET_RIGID_FLEX_AREAS	= 846,
   ODB_ACT_SRL_GET_STEP_RIGID_FLEX_AREAS= 847,

   ODB_ACT_FIX_RESET            = 850,
   ODB_ACT_FIX_MARK             = 851,
   ODB_ACT_FIX_UNMARK           = 852,
   ODB_ACT_FIX_RESET_MARK       = 853,
   ODB_ACT_FIX_UNDO_TO_MARK		= 856,
   ODB_ACT_FIX_PUSH_SPACING		= 854,
   ODB_ACT_FIX_PUSH_ADD         = 855,
   ODB_ACT_FIX_PUSH_DELETE      = 860,
   ODB_ACT_FIX_PUSH_RESIZE      = 865,
   ODB_ACT_FIX_PUSH_MOVE        = 870,
   ODB_ACT_FIX_PUSH_MOVE_S      = 871,
   ODB_ACT_FIX_PUSH_MOVE_E      = 872,
   ODB_ACT_FIX_PUSH_SYMBOL      = 875,
   ODB_ACT_FIX_PUSH_SET_ATTR    = 880,
   ODB_ACT_FIX_PUSH_DELETE_ATTR = 885,
   ODB_ACT_FIX_PUSH_CHANGE_FEATURE = 886,
   ODB_ACT_FIX_INIT_ALL_OPTIONS = 887,
   ODB_ACT_FIX_CLOSE_ALL_OPTIONS = 889,
   ODB_ACT_FIX_ADD_ONE_OPTION   = 890,
   ODB_ACT_FIX_REPEAT_OPTION    = 892,
   

   ODB_ACT_FIX_GET_LOCAL_LAYER	    = 895,
   ODB_ACT_FIX_GET_LOCAL_SHAPE	    = 896,
   ODB_ACT_FIX_GET_LOCAL_MODE	    = 897,
   ODB_ACT_FIX_GET_LOCAL_CATEGORY   = 898,
   ODB_ACT_FIX_GET_LOCAL_SCALAR	    = 899,
   ODB_ACT_FIX_GET_LOCAL_FEATURES   = 900,
   ODB_ACT_FIX_GET_LOCAL_DEP_SHAPES = 901,    

   ODB_ACT_FUNC_LOAD            = 910,
   ODB_ACT_FUNC_LOAD_LIST       = 911,
   ODB_ACT_FUNC_EVAL            = 920,
   ODB_ACT_FUNC_GET_FACTOR      = 925,
   ODB_ACT_FUNC_GET_DOMAIN      = 930,
   ODB_ACT_FUNC_GET_NEIGHBOR    = 931,
   ODB_ACT_FUNC_CREATE          = 935,
   ODB_ACT_FUNC_SET_UNITS       = 940,
   ODB_ACT_FUNC_GET_INTERPOLATION = 1944,
   ODB_ACT_FUNC_SET_INTERPOLATION = 945,
   ODB_ACT_FUNC_ADD_POINT       = 950,
   ODB_ACT_FUNC_SAVE            = 955,
   ODB_ACT_FUNC_GET_FIRST_POINT = 960,

   ODB_ACT_DETCHSETUP_LOAD      = 970,

   ODB_EXT_ACT_TYPE 
};

/*These numbers are occupied - don't use these numbers:
    1070
    1071
    1160
    1161
    1162
    1163
    1164
    1370
    1395
    1444
    1500
    1501
    1502
    1503
    1503
    1504
    1505
    1506
    1507
    1508
    1509
    1510
    1511
    1512
    1513
    1514
    1515
    1516
    1517
    1518
    1519
    1520
    1521
    1522
    1523
    1524
    1525
    1526
*/

typedef u_enum _odb_act odb_act_enum;

typedef struct {
   odb_act_enum	action;
   char        *asc_action;
   struct {
      void     *run_data;
      int       edt_num;
      char     *fname;
      int	line;
   } env;
   int num_params;
   odb_param_struc params[ODB_MAX_PARAMS];
} odb_params_struc;

#ifndef ODB_INTERNAL_LIBRARY

static odb_params_struc odb_params;
static int		odb_status=0;
static boolean          odb_ignore_one_status=FALSE ;
#define STATUS_CHECK \
   { if (status != ODB_L_OK) { \
      fprintf(stderr,"ODB program error at file %s line %d\n",__FILE__,__LINE__); \
      return(status); }}

static odb_f_struc     *ODB_L_F_NULL     = NULL;
static odb_shape_struc *ODB_L_SHAPE_NULL = NULL;
static odb_shape_struc *ODB_L_COMP_NULL  = NULL;

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void *gen__mem_malloc(int size, int mode, char *file, int line);
extern void *gen__mem_calloc(int nelem, int size, int mode, char *file, int line);
extern void gen__mem_free(void *p, int mode, char *file, int line);
extern void *gen__mem_realloc(void *p, int size, int mode, char *file, int line);
#ifdef NLS_GROUP
extern char *gen__nls_nlst(char *str);
extern const char *gen__nls_nlst_const(const char *str);
#endif
extern int odb__call_do(odb_params_struc *_odb_params);
extern void odb__exec_error(int odb_status, int line);
extern void odb__lib_write_err(char *asc_action, char *fname, int   line, int   status_code);
extern int odb__lib_shape_copy(odb_shape_struc *to, odb_shape_struc *from);
extern int odb__lib_shape_clone(odb_shape_struc *to, odb_shape_struc *from);
extern int odb__lib_cont_clone(void *to, void *from);
extern int odb__lib_shape_free(odb_shape_struc *shape);
extern int odb__lib_f_free( odb_f_struc *f );

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif//c++

#endif

#define ODB_L_DESC_NULL_VALUE {-1, -1}
#define ODB_M_IS_DESC_NULL(obj) \
   ((obj).descriptor < 0 && (obj).run_number < 0)

static odb_obj_desc_struc ODB_L_DESC_NULL = ODB_L_DESC_NULL_VALUE;

#define ODB_L_LAYER_NULL ODB_L_DESC_NULL
#define ODB_L_LIST_NULL  ODB_L_DESC_NULL
#define ODB_L_SRL_NULL ODB_L_DESC_NULL

#define ODB_L_NULL_NF  (-1)
#define ODB_L_NULL_NET (-1)
#define ODB_L_NULL_NFC (-1)
#define ODB_L_NULL_FCD NULL
#define ODB_L_NULL_SUBNET (-1)
#define ODB_L_NULL_COMP   (-1)

/* Null-descriptor of gen_2d edge index in odb_cont BL 10.06.10 BUG34320
   Consistent with gen_2d null-descriptor in gen_2d.h : GEN_2D_NULL_ID -1
*/
#define ODB_L_GEN_2D_NULL_ID NULL

/*---------ODB CALLS MACROS ---------*/
#define ODB_EDT_ADD_ATTR(_name, _type)    \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_ADD_ATTR); \
   ODB_PARAM_SET_S (_name);               \
   ODB_PARAM_SET_I (_type);               \
   ODB_CALL; }

#define ODB_EDT_CLOSE_LIC(_license)            \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_CLOSE_LIC);     \
   ODB_PARAM_SET_S (_license);                 \
   ODB_CALL; }

#define ODB_EDT_COMMAND(_command,_response)    \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_COMMAND);       \
   ODB_PARAM_SET_S (_command);                 \
   ODB_PARAM_SET_SP (_response);               \
   ODB_CALL; }

#define ODB_EDT_GET_JOB_ATTR(_name, _data, _exists)\
 { ODB_PARAMS_INIT(ODB_ACT_EDT_GET_JOB_ATTR);    \
   ODB_PARAM_SET_S (_name);                   \
   ODB_PARAM_SET_VOID(_data);                 \
   ODB_PARAM_SET_I (sizeof(_data));           \
   ODB_PARAM_SET_IP(_exists);                 \
   ODB_CALL; }

#define ODB_EDT_GET_JOB_STEP_NAME(_step, _job) \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_GET_JOB_STEP_NAME);  \
   ODB_PARAM_SET_S (_step);                    \
   ODB_PARAM_SET_S (_job);                     \
   ODB_CALL; }

#define ODB_EDT_GET_MIN_BRUSH(_min_brush) \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_GET_MIN_BRUSH); \
   ODB_PARAM_SET_IP (_min_brush);              \
   ODB_CALL; }

#define ODB_EDT_GET_STEP_ATTR(_name, _data, _exists)\
 { ODB_PARAMS_INIT(ODB_ACT_EDT_GET_STEP_ATTR);    \
   ODB_PARAM_SET_S (_name);                   \
   ODB_PARAM_SET_VOID(_data);                 \
   ODB_PARAM_SET_I (sizeof(_data));           \
   ODB_PARAM_SET_IP(_exists);                 \
   ODB_CALL; }

#define ODB_EDT_MESSAGE(_message)              \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_MESSAGE);       \
   ODB_PARAM_SET_S (_message);                 \
   ODB_CALL; }

#define ODB_EDT_OPEN_LIC(_license, _success)   \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_OPEN_LIC);      \
   ODB_PARAM_SET_S (_license);                 \
   ODB_PARAM_SET_IP(_success);                 \
   ODB_CALL; }

#define ODB_EDT_PROGRESS_FRAME_CLOSE(_name,_stop)    \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_PROGRESS_FRAME_CLOSE);\
   ODB_PARAM_SET_S (_name);                          \
   ODB_PARAM_SET_IP(_stop);                          \
   ODB_CALL; }

#define ODB_EDT_PROGRESS_FRAME_OPEN(_name,_size,_stop)\
 { ODB_PARAMS_INIT(ODB_ACT_EDT_PROGRESS_FRAME_OPEN);  \
   ODB_PARAM_SET_S (_name);                    \
   ODB_PARAM_SET_D (_size);                    \
   ODB_PARAM_SET_IP(_stop);                    \
   ODB_CALL; }

#define ODB_EDT_PROGRESS_STEP_ADVANCE(_name,_step_size,_stop) \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_PROGRESS_STEP_ADVANCE);        \
   ODB_PARAM_SET_S (_name);                    \
   ODB_PARAM_SET_D (_step_size);               \
   ODB_PARAM_SET_IP(_stop);                    \
   ODB_CALL; }

#define ODB_EDT_PROGRESS_STEP_CLOSE(_name,_stop)       \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_PROGRESS_STEP_CLOSE);   \
   ODB_PARAM_SET_S (_name);                    \
   ODB_PARAM_SET_IP(_stop);                    \
   ODB_CALL; }

#define ODB_EDT_PROGRESS_STEP_OPEN(_name,_step_size,_stop) \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_PROGRESS_STEP_OPEN);        \
   ODB_PARAM_SET_S (_name);                    \
   ODB_PARAM_SET_D (_step_size);               \
   ODB_PARAM_SET_IP(_stop);                    \
   ODB_CALL; }

#define ODB_EDT_PROGRESS_STEP_RESET(_name,_stop)     \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_PROGRESS_STEP_RESET); \
   ODB_PARAM_SET_S (_name);                    \
   ODB_PARAM_SET_IP(_stop);                    \
   ODB_CALL; }

#define ODB_EDT_PROGRESS_TITLE(_title)         \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_PROGRESS_TITLE);\
   ODB_PARAM_SET_S (_title);                   \
   ODB_CALL; }

#define ODB_EDT_REFRESH                       \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_REFRESH);      \
   ODB_CALL; }

#define ODB_EDT_RUN_LIMITS(_limits, _exists)  \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_RUN_LIMITS);   \
   ODB_PARAM_SET_SHAPE (_limits);             \
   ODB_PARAM_SET_IP    (_exists);             \
   ODB_CALL; }

#define ODB_EDT_SCRIPT(_name,_params,_debug)  \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_SCRIPT);       \
   ODB_PARAM_SET_S (_name);                   \
   ODB_PARAM_SET_S (_params);                 \
   ODB_PARAM_SET_I (_debug);                  \
   ODB_CALL; }

/* JH */
#define ODB_EDT_RUN_IN_PROFILE(_exists)           \
 { ODB_PARAMS_INIT(ODB_ACT_EDT_RUN_IN_PROFILE);   \
   ODB_PARAM_SET_IP(_exists);                     \
   ODB_CALL; }

#define ODB_F_ADD(_ld,_f)                     \
 { ODB_PARAMS_INIT(ODB_ACT_F_ADD);            \
   ODB_PARAM_SET_OBJ(_ld);                    \
   ODB_PARAM_SET_F(_f);                       \
   ODB_CALL; }

#define ODB_F_AREA(_f, _out_list)	     \
 { ODB_PARAMS_INIT(ODB_ACT_F_AREA);  	     \
   ODB_PARAM_SET_F(_f);                	     \
   ODB_PARAM_SET_OBJP  (_out_list);          \
   ODB_CALL; }

#define ODB_F_CHANGE(_ld,_f)                  \
 { ODB_PARAMS_INIT(ODB_ACT_F_CHANGE);         \
   ODB_PARAM_SET_OBJ(_ld);                    \
   ODB_PARAM_SET_F(_f);                       \
   ODB_CALL; }

#define ODB_F_COPY(_source_f, _dest_f)        \
 { ODB_PARAMS_INIT(ODB_ACT_F_COPY);           \
   ODB_PARAM_SET_F(_source_f);                \
   ODB_PARAM_SET_F(_dest_f);                  \
   ODB_CALL; }

#define ODB_F_DELETE(_ld,_nf)                 \
 { ODB_PARAMS_INIT(ODB_ACT_F_DELETE);         \
   ODB_PARAM_SET_OBJ(_ld);                    \
   ODB_PARAM_SET_I(_nf);                      \
   ODB_CALL; }

#define ODB_F_IS_DELETED(_ld,_nf, _deleted)   \
 { ODB_PARAMS_INIT(ODB_ACT_F_IS_DELETED);     \
   ODB_PARAM_SET_OBJ(_ld);                    \
   ODB_PARAM_SET_I(_nf);                      \
   ODB_PARAM_SET_IP(_deleted);                \
   ODB_CALL; }

#define ODB_F_IS_MULTIPOLAR(_ld,_nf, _multipolar)   \
 { ODB_PARAMS_INIT(ODB_ACT_F_IS_MULTIPOLAR);        \
 ODB_PARAM_SET_OBJ(_ld);                            \
 ODB_PARAM_SET_I(_nf);                              \
 ODB_PARAM_SET_IP(_multipolar);                     \
 ODB_CALL; }


#define ODB_F_DELETE_ATTR(_ld, _nf, _name)    \
 { ODB_PARAMS_INIT(ODB_ACT_F_DELETE_ATTR);    \
   ODB_PARAM_SET_OBJ  (_ld);                  \
   ODB_PARAM_SET_I    (_nf);                  \
   ODB_PARAM_SET_S    (_name);                \
   ODB_CALL; }

#define ODB_F_GET_ATTR_LIST(_ld, _nf, _list) \
 { ODB_PARAMS_INIT(ODB_ACT_F_GET_ATTR_LIST);    \
   ODB_PARAM_SET_OBJ  (_ld);                  \
   ODB_PARAM_SET_I    (_nf);                  \
   ODB_PARAM_SET_OBJP (_list);                \
   ODB_CALL; }

#define ODB_F_GET_ATTR(_ld, _nf, _name, _data, _exists)\
 { ODB_PARAMS_INIT(ODB_ACT_F_GET_ATTR);       \
   ODB_PARAM_SET_OBJ(_ld);                    \
   ODB_PARAM_SET_I (_nf);                     \
   ODB_PARAM_SET_S (_name);                   \
   ODB_PARAM_SET_VOID(_data);                 \
   ODB_PARAM_SET_I (sizeof(_data));           \
   ODB_PARAM_SET_IP(_exists);                 \
   ODB_CALL; }

#define ODB_F_GET_ATTR_STR(_ld, _nf, _units,_name, _data, _exists)\
 { ODB_PARAMS_INIT(ODB_ACT_F_GET_ATTR_STR);       \
   ODB_PARAM_SET_OBJ(_ld);                    \
   ODB_PARAM_SET_I (_nf);                     \
   ODB_PARAM_SET_I (_units);                  \
   ODB_PARAM_SET_S (_name);                   \
   ODB_PARAM_SET_S(_data);                    \
   ODB_PARAM_SET_IP(_exists);                 \
   ODB_CALL; }

#define ODB_F_GET_LIMITS(_f,_rect)            \
 { ODB_PARAMS_INIT(ODB_ACT_F_GET_LIMITS);     \
   ODB_PARAM_SET_F     (_f);                  \
   ODB_PARAM_SET_SHAPE (_rect);               \
   ODB_CALL; }

#define ODB_F_GET_TOUCHING(_ld, _nf, _mode, _tch_list)\
 { ODB_PARAMS_INIT(ODB_ACT_F_GET_TOUCHING);   \
   ODB_PARAM_SET_OBJ(_ld);                    \
   ODB_PARAM_SET_I (_nf);                     \
   ODB_PARAM_SET_I (_mode);                   \
   ODB_PARAM_SET_OBJP (_tch_list);            \
   ODB_CALL; }

#define ODB_F_GET_SYM_NAME(_f,_units,_sym_name)\
 { ODB_PARAMS_INIT(ODB_ACT_F_GET_SYM_NAME);   \
   ODB_PARAM_SET_F (_f);                      \
   ODB_PARAM_SET_I (_units);                  \
   ODB_PARAM_SET_S (_sym_name);               \
   ODB_CALL; }

#define ODB_F_GET_SYM_RES(_sym_res)\
 { ODB_PARAMS_INIT(ODB_ACT_F_GET_SYM_RES);    \
   ODB_PARAM_SET_IP (_sym_res);               \
   ODB_CALL; }

#define ODB_F_IS_STANDARD(_f, _is_standard)   \
 { ODB_PARAMS_INIT(ODB_ACT_F_IS_STANDARD);    \
   ODB_PARAM_SET_F (_f);                      \
   ODB_PARAM_SET_IP (_is_standard);           \
   ODB_CALL; }

#define ODB_F_IS_ROTATED(_f, _rot, _is_rotated, _rotated_symbol) \
 { ODB_PARAMS_INIT(ODB_ACT_F_IS_ROTATED);     \
   ODB_PARAM_SET_F (_f);                      \
   ODB_PARAM_SET_ID (_rot);                   \
   ODB_PARAM_SET_IP (_is_rotated);            \
   ODB_PARAM_SET_IP (_rotated_symbol);        \
   ODB_CALL; }

#define ODB_F_NF_TO_SHAPE_LIST(_nf, _ld, _shape_list)   \
 { ODB_PARAMS_INIT(ODB_ACT_F_NF_TO_SHAPE_LIST);\
   ODB_PARAM_SET_I    (_nf);                  \
   ODB_PARAM_SET_OBJ  (_ld);                  \
   ODB_PARAM_SET_OBJP (_shape_list);          \
   ODB_CALL; }

#define ODB_F_RESIZE(_f,_size)                \
 { ODB_PARAMS_INIT(ODB_ACT_F_RESIZE);         \
   ODB_PARAM_SET_F(_f);                       \
   ODB_PARAM_SET_I(_size);                    \
   ODB_CALL; }

#define ODB_F_RESIZE_VERIFY(_f,_size,_ok_p)   \
 { ODB_PARAMS_INIT(ODB_ACT_F_RESIZE_VERIFY);  \
   ODB_PARAM_SET_F(_f);                       \
   ODB_PARAM_SET_I(_size);                    \
   ODB_PARAM_SET_IP (_ok_p);                  \
   ODB_CALL; }

#define ODB_F_RESIZE_BY_XY(_f, _x, _y, _ok)  \
 { ODB_PARAMS_INIT(ODB_ACT_F_RESIZE_BY_XY);  \
   ODB_PARAM_SET_F(_f);                      \
   ODB_PARAM_SET_I(_x);                      \
   ODB_PARAM_SET_I(_y);                      \
   ODB_PARAM_SET_IP(_ok);                    \
   ODB_CALL; }

#define ODB_F_RESIZE_FACTOR(_f, _factor)     \
 { ODB_PARAMS_INIT(ODB_ACT_F_RESIZE_FACTOR); \
   ODB_PARAM_SET_F(_f);                      \
   ODB_PARAM_SET_D(_factor);                 \
   ODB_CALL; }

#define ODB_F_SURROUND(_f,_size)              \
 { ODB_PARAMS_INIT(ODB_ACT_F_SURROUND);       \
   ODB_PARAM_SET_F(_f);                       \
   ODB_PARAM_SET_I(_size);                    \
   ODB_CALL; }

#define ODB_F_SET_ATTR(_ld, _nf,_name,_data)  \
 { ODB_PARAMS_INIT(ODB_ACT_F_SET_ATTR);       \
   ODB_PARAM_SET_OBJ  (_ld);                  \
   ODB_PARAM_SET_I    (_nf);                  \
   ODB_PARAM_SET_S    (_name);                \
   ODB_PARAM_SET_VOID (_data);                \
   ODB_CALL; }

#define ODB_F_SET_SYM_RES(_sym_res)           \
 { ODB_PARAMS_INIT(ODB_ACT_F_SET_SYM_RES);    \
   ODB_PARAM_SET_I    (_sym_res);             \
   ODB_CALL; }

#define ODB_F_TO_SHAPE_LIST(_f, _shape_list)  \
 { ODB_PARAMS_INIT(ODB_ACT_F_TO_SHAPE_LIST);  \
   ODB_PARAM_SET_F(_f);                       \
   ODB_PARAM_SET_OBJP(_shape_list);           \
   ODB_CALL; }

#define ODB_F_CONV_STD(_f, _tol,_match, _flag)\
 { ODB_PARAMS_INIT(ODB_ACT_F_CONV_STD);       \
   ODB_PARAM_SET_F (_f);                      \
   ODB_PARAM_SET_I (_tol);                    \
   ODB_PARAM_SET_F (_match);                  \
   ODB_PARAM_SET_IP(_flag);                   \
   ODB_CALL; }

#define ODB_F_VALIDATE(_f, _size, _mode, _fold, _edge_len, _types , _shapes, _values)  \
 { ODB_PARAMS_INIT(ODB_ACT_F_VALIDATE);       \
   ODB_PARAM_SET_F (_f);                      \
   ODB_PARAM_SET_I (_size);                   \
   ODB_PARAM_SET_I (_mode);                   \
   ODB_PARAM_SET_I (_fold);                   \
   ODB_PARAM_SET_I (_edge_len);               \
   ODB_PARAM_SET_OBJP(_types);                \
   ODB_PARAM_SET_OBJP(_shapes);               \
   ODB_PARAM_SET_OBJP(_values);               \
   ODB_CALL; }

#define ODB_F_DRAWN_TO_CONT(_ld, _nf_list, _usage_list, _tolerance, _clean_holes, _hole_size, _cont_shape) \
 { ODB_PARAMS_INIT(ODB_ACT_F_DRAWN_TO_CONT);	    \
   ODB_PARAM_SET_OBJ   (_ld);			    \
   ODB_PARAM_SET_OBJ   (_nf_list);		    \
   ODB_PARAM_SET_OBJ   (_usage_list);               \
   ODB_PARAM_SET_I     (_tolerance);		    \
   ODB_PARAM_SET_I     (_clean_holes);		    \
   ODB_PARAM_SET_I     (_hole_size);		    \
   ODB_PARAM_SET_SHAPE (_cont_shape);               \
   ODB_CALL; }

#define ODB_F_SURFACE_COUNT_ISLANDS(_f, _num_islands, _num_holes) \
 { ODB_PARAMS_INIT(ODB_ACT_F_SURFACE_COUNT_ISLANDS);           \
   ODB_PARAM_SET_F(_f);		                               \
   ODB_PARAM_SET_IP(_num_islands);                             \
   ODB_PARAM_SET_IP(_num_holes);                               \
   ODB_CALL; }

#define ODB_F_SET_FONT( _f, _font_name )    \
 { ODB_PARAMS_INIT(ODB_ACT_F_SET_FONT );    \
   ODB_PARAM_SET_F( _f );		    \
   ODB_PARAM_SET_S( _font_name );           \
   ODB_CALL; }

#define ODB_F_LINE_ENLARGE( _ld, _f, _enlarge,         \
                            _enlarge_start, _enlarge_end, \
                            _f_res_ld, _f_res_stat_ld, \
                            _shrinked_to_zero )        \
 { ODB_PARAMS_INIT( ODB_ACT_F_LINE_ENLARGE );          \
   ODB_PARAM_SET_OBJ(_ld);                             \
   ODB_PARAM_SET_F( _f );                              \
   ODB_PARAM_SET_I (_enlarge);                         \
   ODB_PARAM_SET_I (_enlarge_start);                   \
   ODB_PARAM_SET_I (_enlarge_end);                     \
   ODB_PARAM_SET_OBJP(_f_res_ld);                      \
   ODB_PARAM_SET_OBJP(_f_res_stat_ld);                 \
   ODB_PARAM_SET_IP(_shrinked_to_zero);                \
   ODB_CALL; }

#define ODB_F_LINE_MOVE( _ld, _f, _dx, _dy,            \
                         _f_res_ld, _f_res_stat_ld,    \
                         _shrinked_to_zero )           \
 { ODB_PARAMS_INIT( ODB_ACT_F_LINE_MOVE );             \
   ODB_PARAM_SET_OBJ(_ld);                             \
   ODB_PARAM_SET_F( _f );                              \
   ODB_PARAM_SET_I (_dx);                              \
   ODB_PARAM_SET_I (_dy);                              \
   ODB_PARAM_SET_OBJP(_f_res_ld);                      \
   ODB_PARAM_SET_OBJP(_f_res_stat_ld);                 \
   ODB_PARAM_SET_IP(_shrinked_to_zero);                \
   ODB_CALL; }
  
#define ODB_F_LINE_SMOOTH( _ld, _f,                    \
                           _f_res_ld, _f_res_stat_ld ) \
 { ODB_PARAMS_INIT( ODB_ACT_F_LINE_SMOOTH );           \
   ODB_PARAM_SET_OBJ(_ld);                             \
   ODB_PARAM_SET_F( _f );                              \
   ODB_PARAM_SET_OBJP(_f_res_ld);                      \
   ODB_PARAM_SET_OBJP(_f_res_stat_ld);                 \
   ODB_CALL; }

#define ODB_F_LINE_CLIP( _ld, _f, _clipper_f,        \
    _clip_as_contour,           \
    _f_res_ld, _clipped )       \
 { ODB_PARAMS_INIT( ODB_ACT_F_LINE_CLIP );           \
 ODB_PARAM_SET_OBJ(_ld);                             \
 ODB_PARAM_SET_F( _f );                              \
 ODB_PARAM_SET_F( _clipper_f );                      \
 ODB_PARAM_SET_I( _clip_as_contour );                \
 ODB_PARAM_SET_OBJP(_f_res_ld);                      \
 ODB_PARAM_SET_IP(_clipped);                         \
 ODB_CALL; }

#define ODB_F_TAPER( _f, _from_end, _bigger_size,    \
                     _f_res_ld )                     \
 { ODB_PARAMS_INIT( ODB_ACT_F_TAPER );               \
   ODB_PARAM_SET_F( _f );                            \
   ODB_PARAM_SET_I( _from_end )                      \
   ODB_PARAM_SET_I( _bigger_size )                   \
   ODB_PARAM_SET_OBJP(_f_res_ld);                    \
   ODB_CALL; }


#define ODB_EDA_ALL_INFO(_num_nets, _num_pkgs, \
                         _num_comps1, _num_comps2, _num_fgroups)    \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_ALL_INFO);     \
   ODB_PARAM_SET_IP   (_num_nets);            \
   ODB_PARAM_SET_IP   (_num_pkgs);            \
   ODB_PARAM_SET_IP   (_num_comps1);          \
   ODB_PARAM_SET_IP   (_num_comps2);          \
   ODB_PARAM_SET_IP   (_num_fgroups);         \
   ODB_CALL; }

#define ODB_EDA_CLASSIFY_COMP_SEG(_seg, _comp_ld1, _comp_ld2, \
                                  _nc1, _nc2, _class_name)    \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_CLASSIFY_COMP_SEG);    \
   ODB_PARAM_SET_SHAPE (_seg);                  \
   ODB_PARAM_SET_OBJ   (_comp_ld1);             \
   ODB_PARAM_SET_OBJ   (_comp_ld2);             \
   ODB_PARAM_SET_I     (_nc1);                  \
   ODB_PARAM_SET_I     (_nc2);                  \
   ODB_PARAM_SET_S     (_class_name);           \
   ODB_PARAM_SET_I     (sizeof(_class_name));   \
   ODB_CALL; }

#define ODB_EDA_COMP_DELETE_ATTR(_ld, _nc, _name)    \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_COMP_DELETE_ATTR);    \
   ODB_PARAM_SET_OBJ  (_ld);                  \
   ODB_PARAM_SET_I    (_nc);                  \
   ODB_PARAM_SET_S    (_name);                \
   ODB_CALL; }

#define ODB_EDA_COMP_GET(_ld, _nc, _comp)     \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_COMP_GET);     \
   ODB_PARAM_SET_OBJ  (_ld);                  \
   ODB_PARAM_SET_I    (_nc);                  \
   ODB_PARAM_SET_COMP (_comp);                \
   ODB_CALL; }

#define ODB_EDA_COMP_GET_ATTR(_ld, _nc, _name, _data, _exists)\
 { ODB_PARAMS_INIT(ODB_ACT_EDA_COMP_GET_ATTR);    \
   ODB_PARAM_SET_OBJ(_ld);                    \
   ODB_PARAM_SET_I (_nc);                     \
   ODB_PARAM_SET_S (_name);                   \
   ODB_PARAM_SET_VOID(_data);                 \
   ODB_PARAM_SET_I (sizeof(_data));           \
   ODB_PARAM_SET_IP(_exists);                 \
   ODB_CALL; }

#define ODB_EDA_COMP_GET_TYPE( _ld, _nc, _type, _exists )\
 { ODB_PARAMS_INIT(ODB_ACT_EDA_COMP_GET_TYPE);  \
   ODB_PARAM_SET_OBJ(_ld);                      \
   ODB_PARAM_SET_I (_nc);                       \
   ODB_PARAM_SET_IP(_type);                     \
   ODB_PARAM_SET_IP(_exists);                   \
   ODB_CALL; }

#define ODB_EDA_COMP_SET_ATTR(_ld, _nc,_name,_data)  \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_COMP_SET_ATTR);       \
   ODB_PARAM_SET_OBJ  (_ld);                  \
   ODB_PARAM_SET_I    (_nc);                  \
   ODB_PARAM_SET_S    (_name);                \
   ODB_PARAM_SET_VOID (_data);                \
   ODB_CALL; }

#define ODB_EDA_COMP_GET_PADS(_comp, _pad_ld, _nf_list) \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_COMP_GET_PADS); \
   ODB_PARAM_SET_COMP(_comp);    \
   ODB_PARAM_SET_OBJ (_pad_ld);  \
   ODB_PARAM_SET_OBJP(_nf_list); \
   ODB_CALL; }

#define ODB_EDA_F_FIND(_ld, _nf,  \
               _net_num,_subnet_num, _comp_num, _comp_side)  \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_F_FIND);       \
   ODB_PARAM_SET_OBJ  (_ld);                  \
   ODB_PARAM_SET_I    (_nf);                  \
   ODB_PARAM_SET_IP   (_net_num);             \
   ODB_PARAM_SET_IP   (_subnet_num);          \
   ODB_PARAM_SET_IP   (_comp_num);            \
   ODB_PARAM_SET_IP   (_comp_side);           \
   ODB_CALL; }

#define ODB_EDA_FID_GET(_net_num, _subnet_num, _fid_num, _ld,_nf_p)  \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_FID_GET);      \
   ODB_PARAM_SET_I    (_net_num);             \
   ODB_PARAM_SET_I    (_subnet_num);          \
   ODB_PARAM_SET_I    (_fid_num);             \
   ODB_PARAM_SET_OBJ  (_ld);                  \
   ODB_PARAM_SET_IP   (_nf_p);                \
   ODB_CALL; }

#define ODB_EDA_LYR_GET(_side, _ld)  \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_LYR_GET);  \
   ODB_PARAM_SET_I    (_side);            \
   ODB_PARAM_SET_OBJP (_ld);              \
   ODB_CALL; }

#define ODB_EDA_NET_GET(_net_num, _name, _num_subnets)  \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_NET_GET);      \
   ODB_PARAM_SET_I    (_net_num);             \
   ODB_PARAM_SET_S    (_name);                \
   ODB_PARAM_SET_IP   (_num_subnets);         \
   ODB_CALL; }

#define ODB_EDA_SUBNET_GET(_net_num, _subnet_num, _type, _num_fids)  \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_SUBNET_GET);      \
   ODB_PARAM_SET_I    (_net_num);             \
   ODB_PARAM_SET_I    (_subnet_num);          \
   ODB_PARAM_SET_IP   (_type);                \
   ODB_PARAM_SET_IP   (_num_fids);            \
   ODB_CALL; }

#define ODB_EDA_TOEP_GET(_ld, _comp_num, _toep_num,  \
                         _toep_name, _net_num, _subnet_num)  \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_TOEP_GET);      \
   ODB_PARAM_SET_OBJ  (_ld);                  \
   ODB_PARAM_SET_I    (_comp_num);            \
   ODB_PARAM_SET_I    (_toep_num);            \
   ODB_PARAM_SET_S    (_toep_name);           \
   ODB_PARAM_SET_IP   (_net_num);             \
   ODB_PARAM_SET_IP   (_subnet_num);          \
   ODB_CALL; }

#define ODB_EDA_TOEP_SHAPE_GET(_ld, _comp_num, _toep_num, _toep_shape) \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_TOEP_SHAPE_GET);      \
   ODB_PARAM_SET_OBJ  (_ld);                  \
   ODB_PARAM_SET_I    (_comp_num);            \
   ODB_PARAM_SET_I    (_toep_num);            \
   ODB_PARAM_SET_SHAPE(_toep_shape);          \
   ODB_CALL; }

#define ODB_EDA_TOEP_SIDE(_comp, _toep_num, _toep_side) \
 { ODB_PARAMS_INIT(ODB_ACT_EDA_TOEP_SIDE); \
   ODB_PARAM_SET_COMP(_comp);              \
   ODB_PARAM_SET_I   (_toep_num);          \
   ODB_PARAM_SET_IP  (_toep_side);         \
   ODB_CALL; }

#define ODB_LAYER_ADD_GROUP(_ld, _f_types, _attrs_lst)  \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_ADD_GROUP); \
   ODB_PARAM_SET_OBJ (_ld);                  \
   ODB_PARAM_SET_I (_f_types);               \
   ODB_PARAM_SET_S (_attrs_lst);             \
   ODB_CALL; }
/*
#define ODB_LAYER_DESTRUCT_GROUPS()             \
{ ODB_PARAMS_INIT(ODB_ACT_LAYER_DESTRUCT_GROUPS); \
ODB_CALL; }
*/
#define ODB_LAYER_CLEAR(_name)                \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_CLEAR);      \
   ODB_PARAM_SET_S(_name);                    \
   ODB_CALL; }

#define ODB_LAYER_DELETE_ALL(_ld)             \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_DELETE_ALL); \
   ODB_PARAM_SET_OBJ(_ld);                    \
   ODB_CALL; }

#define ODB_LAYER_DETECT_PADS(_ld, _smld, _drld, _tol, _minw, _maxw, _minl, _maxl,  _mind, _maxd, _err_perim, _overlap_value, _resld)  \
 {  ODB_PARAMS_INIT(ODB_ACT_LAYER_DETECT_PADS);						    \
 ODB_PARAM_SET_OBJ(_ld);								    \
 ODB_PARAM_SET_OBJ(_smld);								    \
 ODB_PARAM_SET_OBJ(_drld);								    \
 ODB_PARAM_SET_I  (_tol);								    \
 ODB_PARAM_SET_I  (_minw);								    \
 ODB_PARAM_SET_I  (_maxw);								    \
 ODB_PARAM_SET_I  (_minl);								    \
 ODB_PARAM_SET_I  (_maxl);								    \
 ODB_PARAM_SET_I  (_mind);								    \
 ODB_PARAM_SET_I  (_maxd);								    \
 ODB_PARAM_SET_D  (_err_perim);								    \
 ODB_PARAM_SET_I  (_overlap_value);							    \
 ODB_PARAM_SET_OBJ(_resld);								    \
 ODB_CALL; }

#define ODB_LAYER_CLOSE(_ld)                  \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_CLOSE);      \
   ODB_PARAM_SET_OBJP(_ld);                   \
   ODB_CALL; }

#define ODB_LAYER_COPPER_AREA(_ld,_rect,_dflag,_thick,_res, _area)  \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_COPPER_AREA);\
   ODB_PARAM_SET_OBJ  (_ld);                  \
   ODB_PARAM_SET_SHAPE(_rect);                \
   ODB_PARAM_SET_I    (_dflag);               \
   ODB_PARAM_SET_I    (_thick);               \
   ODB_PARAM_SET_I    (_res);                 \
   ODB_PARAM_SET_DP   (_area);                \
   ODB_CALL; }

#define ODB_LAYER_COPY(_name,_new_name)       \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_COPY);       \
   ODB_PARAM_SET_S(_name);                    \
   ODB_PARAM_SET_S(_new_name);                \
   ODB_CALL; }

#define ODB_LAYER_COPY_TEMP(_name, _ld) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_COPY_TEMP);      \
   ODB_PARAM_SET_S(_name);                        \
   ODB_PARAM_SET_OBJP(_ld);                       \
   ODB_CALL; }

#define ODB_LAYER_COPY_KEEP_SELECTED(_name,_new_name)       \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_COPY_KEEP_SELECTED);       \
 ODB_PARAM_SET_S(_name);                                         \
 ODB_PARAM_SET_S(_new_name);                                     \
 ODB_CALL; }

#define ODB_LAYER_COUNT_F(_ld, _count)        \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_COUNT_F);    \
   ODB_PARAM_SET_OBJ(_ld);                    \
   ODB_PARAM_SET_IP (_count);                 \
   ODB_CALL; }

#define ODB_LAYER_COUNT_NET(_ld, _count)      \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_COUNT_NET);  \
   ODB_PARAM_SET_OBJ(_ld);                    \
   ODB_PARAM_SET_IP (_count);                 \
   ODB_CALL; }

#define ODB_LAYER_COUNT_TRUE_NET(_ld, _count) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_COUNT_TRUE_NET);  \
   ODB_PARAM_SET_OBJ (_ld);                   \
   ODB_PARAM_SET_IP  (_count);                \
   ODB_CALL; }

#define ODB_LAYER_COUNT_SHAPE(_ld, _count)    \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_COUNT_SHAPE);\
   ODB_PARAM_SET_OBJ(_ld);                    \
   ODB_PARAM_SET_IP (_count);                 \
   ODB_CALL; }

#define ODB_LAYER_CREATE(_name,_del_after,_ld) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_CREATE);      \
   ODB_PARAM_SET_S(_name);                     \
   ODB_PARAM_SET_I(_del_after);                \
   ODB_PARAM_SET_OBJP(_ld);                    \
   ODB_CALL; }

#define ODB_LAYER_CREATE_TEMP(_name,_ld) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_CREATE_TEMP); \
   ODB_PARAM_SET_S(_name);                     \
   ODB_PARAM_SET_OBJP(_ld);                    \
   ODB_CALL; }

#define ODB_LAYER_DELETE(_name)                \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_DELETE);      \
   ODB_PARAM_SET_S(_name);                     \
   ODB_CALL; }

#define ODB_LAYER_DRILL_THROUGH(_ld,_type_mask,_side_mask,_lld) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_DRILL_THROUGH);           \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I(_type_mask);                \
   ODB_PARAM_SET_I(_side_mask);                \
   ODB_PARAM_SET_OBJP(_lld);                   \
   ODB_CALL; }

#define ODB_LAYER_DRILL_TERM(_dld,_tld,_bld)    \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_DRILL_TERM);   \
   ODB_PARAM_SET_OBJ(_dld);                     \
   ODB_PARAM_SET_OBJP(_tld);                    \
   ODB_PARAM_SET_OBJP(_bld);                    \
   ODB_CALL; }

#define ODB_LAYER_DRILLS(_ld,_drill_mask, _lld)\
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_DRILLS);      \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I(_drill_mask);               \
   ODB_PARAM_SET_OBJP(_lld);                   \
   ODB_CALL; }

#define ODB_LAYER_EXISTS(_name,_exists)        \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_EXISTS);      \
   ODB_PARAM_SET_S(_name);                     \
   ODB_PARAM_SET_IP(_exists);                  \
   ODB_CALL; }

#define ODB_LAYER_FATR_EXISTS(_ld, _attr_name, _exists)        \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_FATR_EXISTS);       \
   ODB_PARAM_SET_OBJ(_ld);                           \
   ODB_PARAM_SET_S(_attr_name);                           \
   ODB_PARAM_SET_IP(_exists);                        \
   ODB_CALL; }

#define ODB_LAYER_F_CONTOURIZE(_ld, _in_lst, _tol, _f )	    \
{							    \
    ODB_PARAMS_INIT(ODB_ACT_LAYER_F_CONTOURIZE);	    \
    ODB_PARAM_SET_OBJ(_ld);				    \
    ODB_PARAM_SET_OBJ(_in_lst);				    \
    ODB_PARAM_SET_I(_tol);				    \
    ODB_PARAM_SET_F(_f);				    \
    ODB_CALL;						    \
}

#define ODB_LAYER_GET_ATTR(_ld,_attr,_value)   \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_ATTR);    \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I(_attr);                     \
   ODB_PARAM_SET_IP(_value);                   \
   ODB_CALL; }

#define ODB_LAYER_GET_BOARD_NET_BY_NET(_ld, _fcnet, _board_net_p) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_BOARD_NET_BY_NET);           \
   ODB_PARAM_SET_OBJ   (_ld);                                     \
   ODB_PARAM_SET_I     (_fcnet);                                  \
   ODB_PARAM_SET_IP    (_board_net_p);                            \
   ODB_CALL;}

#define ODB_LAYER_GET_DATUM(_ld,_point)        \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_DATUM);   \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_SHAPE(_point);                \
   ODB_CALL; }

#define ODB_LAYER_GET_PROFILE(_shape, _num_shapes)     \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_PROFILE); \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_IP    (_num_shapes);          \
   ODB_CALL; }

#define ODB_LAYER_GET_PROFILE_AND_HOLES(_outer_profile, _num_outer_profiles, _holes_list)     \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_PROFILE_AND_HOLES); \
 ODB_PARAM_SET_SHAPE(_outer_profile);          \
 ODB_PARAM_SET_IP   (_num_outer_profiles);     \
 ODB_PARAM_SET_OBJP (_holes_list);             \
 ODB_CALL; }

#define ODB_LAYER_GET_F(_ld, _serial, _f)      \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_F);       \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_IP (_serial);                 \
   ODB_PARAM_SET_F (_f);                       \
   ODB_CALL; }

#define ODB_LAYER_GET_F_AREA(_ld, _area, _intersect, _flist) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_F_AREA);  \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_SHAPE (_area);                \
   ODB_PARAM_SET_I  (_intersect);              \
   ODB_PARAM_SET_OBJP(_flist);                 \
   ODB_CALL; }

#define ODB_LAYER_GET_F_BY_NF(_ld, _nf, _f)    \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_F_BY_NF); \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I (_nf);                      \
   ODB_PARAM_SET_F (_f);                       \
   ODB_CALL; }

#define ODB_LAYER_GET_F_SYM_NUM_BY_NF( _ld, _nf, _f_sym_num )	\
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_F_SYM_NUM_BY_NF);	\
 ODB_PARAM_SET_OBJ(_ld);				\
 ODB_PARAM_SET_I (_nf);				        \
 ODB_PARAM_SET_SYM_P (_f_sym_num);		        \
 ODB_CALL; }

#define ODB_LAYER_GET_F_TYPE_BY_NF( _ld, _nf, _f_type, _f_sym_type )	\
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_F_TYPE_BY_NF);	\
   ODB_PARAM_SET_OBJ(_ld);				\
   ODB_PARAM_SET_I (_nf);				\
   ODB_PARAM_SET_IP (_f_type);				\
   ODB_PARAM_SET_IP (_f_sym_type);			\
   ODB_CALL; }

#define ODB_LAYER_GET_NETS_BY_NF( _ld, _nf, _net )	\
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_NETS_BY_NF);	\
 ODB_PARAM_SET_OBJ(_ld);				\
 ODB_PARAM_SET_I (_nf);					\
 ODB_PARAM_SET_OBJP (_net);				\
 ODB_CALL; }

#define ODB_LAYER_GET_NET_BY_POINT( _ld, _pt, _net )	\
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_NET_BY_POINT);	\
 ODB_PARAM_SET_OBJ(_ld);				\
 ODB_PARAM_SET_SHAPE (_pt);				\
 ODB_PARAM_SET_IP (_net);				\
 ODB_CALL; }

#define ODB_LAYER_GET_F_EXT(_ld, _serial, _f)  \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_F_EXT);   \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_IP (_serial);                 \
   ODB_PARAM_SET_F (_f);                       \
   ODB_CALL; }

#define ODB_LAYER_GET_F_FILTER(_ld, _serial, _attrs_lst, _areas_lst, _exclude,  _f)      \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_F_FILTER);       \
   ODB_PARAM_SET_OBJ (_ld);                    \
   ODB_PARAM_SET_IP  (_serial);                \
   ODB_PARAM_SET_OBJ (_attrs_lst);             \
   ODB_PARAM_SET_OBJ (_areas_lst);             \
   ODB_PARAM_SET_I   (_exclude);               \
   ODB_PARAM_SET_F (_f);                       \
   ODB_CALL; }

#define ODB_LAYER_GET_LNAME(_ld, _lname)       \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_LNAME);   \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_S  (_lname);                  \
   ODB_CALL; }

#define ODB_LAYER_GET_NET(_ld, _net_id, _shape_list) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_NET);     \
   ODB_PARAM_SET_OBJ (_ld);                    \
   ODB_PARAM_SET_I  (_net_id);                 \
   ODB_PARAM_SET_OBJP (_shape_list);           \
   ODB_CALL; }

#define ODB_LAYER_GET_NET_ALL(_ld, _net_id, _shape_list) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_NET_ALL); \
   ODB_PARAM_SET_OBJ (_ld);                    \
   ODB_PARAM_SET_I  (_net_id);                 \
   ODB_PARAM_SET_OBJP (_shape_list);           \
   ODB_CALL; }

#define ODB_LAYER_GET_NET_FILTER(_ld, _net_id, _attrs_lst, _areas_lst, _exclude, _shape_list) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_NET_FILTER);     \
   ODB_PARAM_SET_OBJ (_ld);                           \
   ODB_PARAM_SET_I  (_net_id);                        \
   ODB_PARAM_SET_OBJ (_attrs_lst);                    \
   ODB_PARAM_SET_OBJ (_areas_lst);                    \
   ODB_PARAM_SET_I   (_exclude);                      \
   ODB_PARAM_SET_OBJP (_shape_list);                  \
   ODB_CALL; }

#define ODB_LAYER_GET_NET_CONTOUR(_ld, _net_id, _shape_cont) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_NET_CONTOUR);           \
   ODB_PARAM_SET_OBJ (_ld);                                  \
   ODB_PARAM_SET_I  (_net_id);                               \
   ODB_PARAM_SET_SHAPE (_shape_cont);                        \
   ODB_CALL; }

#define ODB_LAYER_GET_SHAPE(_ld, _serial, _shape) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_SHAPE);   \
   ODB_PARAM_SET_OBJ (_ld);                    \
   ODB_PARAM_SET_IP (_serial);                 \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_CALL; }

#define ODB_LAYER_GET_SHAPE_BY_NFC(_ld, _serial, _shape)\
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_SHAPE_BY_NFC);   	\
   ODB_PARAM_SET_OBJ (_ld);                   		\
   ODB_PARAM_SET_I (_serial);                 		\
   ODB_PARAM_SET_SHAPE (_shape);               		\
   ODB_CALL; }
#define ODB_LAYER_GET_SHAPE_FILTER(_ld, _serial, _attrs_lst, _areas_lst, _exclude, _shape) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_SHAPE_FILTER);   \
   ODB_PARAM_SET_OBJ (_ld);                    \
   ODB_PARAM_SET_IP (_serial);                 \
   ODB_PARAM_SET_OBJ (_attrs_lst);             \
   ODB_PARAM_SET_OBJ (_areas_lst);             \
   ODB_PARAM_SET_I   (_exclude);               \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_CALL; }

#define ODB_LAYER_GET_WORK_LNAME(_lname)       \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_WORK_LNAME);\
   ODB_PARAM_SET_S (_lname);                   \
   ODB_CALL; }

#define ODB_LAYER_ORIENTATION(_ld,_orientation)	\
 {  ODB_PARAMS_INIT(ODB_ACT_LAYER_ORIENTATION);	\
 ODB_PARAM_SET_OBJ(_ld);				\
 ODB_PARAM_SET_IP(_orientation);			\
 ODB_CALL; }

#define ODB_LAYER_HATCH(_ld, _min_line, _max_line, _min_pat_lines,                  \
                        _cross_only, _allow_overlap, _tol, _bld, _pld)              \
{ ODB_PARAMS_INIT(ODB_ACT_LAYER_HATCH);                                             \
  ODB_PARAM_SET_OBJ (_ld);                                                          \
  ODB_PARAM_SET_I (_min_line);                                                      \
  ODB_PARAM_SET_I (_max_line);                                                      \
  ODB_PARAM_SET_I (_min_pat_lines);                                                 \
  ODB_PARAM_SET_I (_cross_only);                                                    \
  ODB_PARAM_SET_I (_allow_overlap);                                                 \
  ODB_PARAM_SET_I (_tol);                                                           \
  ODB_PARAM_SET_OBJP (_bld);                                                        \
  ODB_PARAM_SET_OBJP (_pld);                                                        \
  ODB_CALL ; }

#define ODB_LAYER_LIMITS(_ld,_rect)            \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_LIMITS);      \
   ODB_PARAM_SET_OBJ     (_ld);                \
   ODB_PARAM_SET_SHAPE (_rect);                \
   ODB_CALL; }

#define ODB_LAYER_NAME_TO_LIST(_name,_lld)     \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_NAME_TO_LIST);\
   ODB_PARAM_SET_S(_name);                     \
   ODB_PARAM_SET_OBJP(_lld);                   \
   ODB_CALL; }

#define ODB_LAYER_NAME_TO_LIST_POS(_name,_lld) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_NAME_TO_LIST_POS);\
   ODB_PARAM_SET_S(_name);                     \
   ODB_PARAM_SET_OBJP(_lld);                   \
   ODB_CALL; }

#define ODB_LAYER_OPEN(_name,_ld)              \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_OPEN);        \
   ODB_PARAM_SET_S(_name);                     \
   ODB_PARAM_SET_OBJP(_ld);                    \
   ODB_CALL; }

#define ODB_LAYER_OPEN_POS(_name,_ld)          \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_OPEN_POS);    \
   ODB_PARAM_SET_S(_name);                     \
   ODB_PARAM_SET_OBJP(_ld);                    \
   ODB_CALL; }

#define ODB_LAYER_PROFILE(_pld)                \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_PROFILE);     \
   ODB_PARAM_SET_OBJP(_pld);                   \
   ODB_CALL; }

#define ODB_LAYER_QUICK_NEXT_DEL(_ld)            \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_QUICK_NEXT_DEL);\
   ODB_PARAM_SET_OBJ(_ld);                       \
   ODB_CALL; }

#define ODB_LAYER_SELECT_NF(_ld,_nf,_select)    \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_SELECT_NF);    \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I(_nf);                       \
   ODB_PARAM_SET_I(_select);                   \
   ODB_CALL; }

#define ODB_LAYER_IS_SELECTED_NF(_ld,_nf,_is_selected)    \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_IS_SELECTED_NF);\
 ODB_PARAM_SET_OBJ(_ld);                         \
 ODB_PARAM_SET_I(_nf);                           \
 ODB_PARAM_SET_IP(_is_selected);                 \
 ODB_CALL; }

#define ODB_LAYER_RENAME(_name,_new_name)      \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_RENAME);      \
   ODB_PARAM_SET_S(_name);                     \
   ODB_PARAM_SET_S(_new_name);                 \
   ODB_CALL; }

#define ODB_LAYER_SELECT_CLEAR(_ld)      \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_SELECT_CLEAR);      \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_CALL; }

#define ODB_LAYER_SET_ATTR(_ld,_attr,_value)   \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_SET_ATTR);    \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I(_attr);                     \
   ODB_PARAM_SET_I(_value);                    \
   ODB_CALL; }

#define ODB_LAYER_CONNECT(_ld,_top,_bot)       \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_CONNECT);     \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_IP(_top);                     \
   ODB_PARAM_SET_IP(_bot);                     \
   ODB_CALL; }

#define ODB_LAYER_SUBPROFILES(_ld)             \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_SUBPROFILES); \
   ODB_PARAM_SET_OBJP(_ld);                     \
   ODB_CALL; }

#define ODB_LAYER_SUBSTITUTE(_ld,_ref_sm_ld,_tol,_max_smd,_min_smd,_mode,   \
                             _rot_mode,_conn_mode,_flags,_spare2,_ild)  \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_SUBSTITUTE);  \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_OBJ(_ref_sm_ld);              \
   ODB_PARAM_SET_I (_tol);                     \
   ODB_PARAM_SET_I (_max_smd);                 \
   ODB_PARAM_SET_I (_min_smd);                 \
   ODB_PARAM_SET_I (_mode);                    \
   ODB_PARAM_SET_I (_rot_mode);                \
   ODB_PARAM_SET_I (_conn_mode);               \
   ODB_PARAM_SET_I (_flags);                   \
   ODB_PARAM_SET_I (_spare2);                  \
   ODB_PARAM_SET_OBJP(_ild);                   \
   ODB_CALL; }

#define ODB_LAYER_SUBSTITUTE_CAT(_ld,_ref_sm_ld,_tol,_max_smd,_min_smd,      \
                                 _sm_margin,_drill_margin,_mode,             \
                                 _rot_mode,_conn_mode,                       \
                                 _flags,_spare2,_ild, _cat)                  \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_SUBSTITUTE_CAT);  \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_OBJ(_ref_sm_ld);              \
   ODB_PARAM_SET_I (_tol);                     \
   ODB_PARAM_SET_I (_max_smd);                 \
   ODB_PARAM_SET_I (_min_smd);                 \
   ODB_PARAM_SET_I (_sm_margin);               \
   ODB_PARAM_SET_I (_drill_margin);            \
   ODB_PARAM_SET_I (_mode);                    \
   ODB_PARAM_SET_I (_rot_mode);                \
   ODB_PARAM_SET_I (_conn_mode);               \
   ODB_PARAM_SET_I (_flags);                   \
   ODB_PARAM_SET_I (_spare2);                  \
   ODB_PARAM_SET_OBJP(_ild);                   \
   ODB_PARAM_SET_OBJP(_cat);                   \
   ODB_CALL; }

#define ODB_LAYER_SUBSTITUTE_CAT2( _ld,_ref_sm_ld,_tol,_max_smd,_min_smd,   \
                                 _sm_margin,_drill_margin,_mode,            \
                                 _rot_mode,_conn_mode,                      \
                                 _flags,_ild, _cat, _list_type )            \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_SUBSTITUTE_CAT2);  \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_OBJ(_ref_sm_ld);              \
   ODB_PARAM_SET_I (_tol);                     \
   ODB_PARAM_SET_I (_max_smd);                 \
   ODB_PARAM_SET_I (_min_smd);                 \
   ODB_PARAM_SET_I (_sm_margin);               \
   ODB_PARAM_SET_I (_drill_margin);            \
   ODB_PARAM_SET_I (_mode);                    \
   ODB_PARAM_SET_I (_rot_mode);                \
   ODB_PARAM_SET_I (_conn_mode);               \
   ODB_PARAM_SET_I (_flags);                   \
   ODB_PARAM_SET_OBJP(_ild);                   \
   ODB_PARAM_SET_OBJP(_cat);                   \
   ODB_PARAM_SET_I(_list_type);                   \
   ODB_CALL; }

#define ODB_LAYER_SYNC(_ld)                    \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_SYNC);        \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_CALL; }

#define ODB_LAYER_UNDO(_ld, _undo_id)            \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_UNDO);          \
   ODB_PARAM_SET_OBJ(_ld);                       \
   ODB_PARAM_SET_I (_undo_id);                   \
   ODB_CALL; }

#define ODB_LAYER_UNDO_FETCH(_ld, _comm_str_p)   \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_UNDO_FETCH);    \
   ODB_PARAM_SET_OBJ(_ld);                       \
   ODB_PARAM_SET_SP (_comm_str_p);               \
   ODB_CALL; }

#define ODB_LAYER_UNDO_GET_F(_ld, _flist)        \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_UNDO_GET_F);    \
   ODB_PARAM_SET_OBJ(_ld);                       \
   ODB_PARAM_SET_OBJP(_flist);                   \
   ODB_CALL; }

/* note that only the top level can be undone/reset
   so the undo_id used by the undo functions is used
   for verification of sychronous operation of
   MARK/RESET and MARK/UNDO pairs */
#define ODB_LAYER_UNDO_MARK(_ld, _undo_id_p)     \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_UNDO_MARK);     \
   ODB_PARAM_SET_OBJ(_ld);                       \
   ODB_PARAM_SET_IP (_undo_id_p);                \
   ODB_CALL; }

#define ODB_LAYER_UNDO_RESET(_ld, _undo_id)      \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_UNDO_RESET);    \
   ODB_PARAM_SET_OBJ(_ld);                       \
   ODB_PARAM_SET_I (_undo_id);                   \
   ODB_CALL; }

#define ODB_LAYER_DELETE_SHAPE_LIST( _ld )          \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_DELETE_SHAPE_LIST);\
   ODB_PARAM_SET_OBJ(_ld);                          \
   ODB_CALL; }

#define ODB_LAYER_CREATE_SHAPE_LIST( _ld, _split_complex_conts, _fc_cp_mode )  \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_CREATE_SHAPE_LIST);              \
   ODB_PARAM_SET_OBJ(_ld);                                        \
   ODB_PARAM_SET_I  (_split_complex_conts);                       \
   ODB_PARAM_SET_I  (_fc_cp_mode);                                \
   ODB_CALL; }

#define ODB_LAYER_COMPENSATE( _s_ld, _d_ld, _mode) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_COMPENSATE);	    \
   ODB_PARAM_SET_OBJ(_s_ld);                        \
   ODB_PARAM_SET_OBJ(_d_ld);                        \
   ODB_PARAM_SET_I  (_mode);                        \
   ODB_CALL; }

#define ODB_LAYER_GET_USER_ATTR(_ld, _name, _value) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_USER_ATTR);    \
   ODB_PARAM_SET_OBJ(_ld);                          \
   ODB_PARAM_SET_S(_name);                          \
   ODB_PARAM_SET_S(_value);                         \
   ODB_CALL; }

#define ODB_LAYER_GET_TYPE_NAME(_ld, _name)         \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_TYPE_NAME);    \
   ODB_PARAM_SET_OBJ(_ld);                          \
   ODB_PARAM_SET_S(_name);                          \
   ODB_CALL; }

#define ODB_LAYER_GET_RIGID_FLEX_AREAS(_ld, _flex_lst, _rigid_lst)  \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_RIGID_FLEX_AREAS);		    \
 ODB_PARAM_SET_OBJ(_ld);					    \
 ODB_PARAM_SET_OBJP(_flex_lst);					    \
 ODB_PARAM_SET_OBJP(_rigid_lst);				    \
 ODB_CALL; }

#define ODB_LAYER_GET_STEP_RIGID_FLEX_AREAS(_flex_lst, _rigid_lst)  \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_STEP_RIGID_FLEX_AREAS);	    \
 ODB_PARAM_SET_OBJP(_flex_lst);					    \
 ODB_PARAM_SET_OBJP(_rigid_lst);				    \
 ODB_CALL; }


#define ODB_LAYER_GET_LAYER_PROFILE( _ld, _get_step_profile, _cont_lst, _found)  \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_LAYER_PROFILE);		    \
 ODB_PARAM_SET_OBJ(_ld);                                            \
 ODB_PARAM_SET_I( _get_step_profile );                              \
 ODB_PARAM_SET_OBJP(_cont_lst);					    \
 ODB_PARAM_SET_IP(_found);      				    \
 ODB_CALL; }

#define ODB_LAYER_LAYER_SUBPROFILES(_ld, _sub_prof_lst ) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_LAYER_SUBPROFILES); \
   ODB_PARAM_SET_OBJ(_ld);                           \
   ODB_PARAM_SET_OBJP(_sub_prof_lst);                \
   ODB_CALL; }

#define ODB_LAYER_SET_TYPE_BY_NAME(_ld, _name)      \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_SET_TYPE_BY_NAME); \
   ODB_PARAM_SET_OBJ(_ld);                          \
   ODB_PARAM_SET_S(_name);                          \
   ODB_CALL; }

#define ODB_LAYER_VERIFY_TOOLING_HOLES_SET( _ld, _set_lst, _holes_lst, _size_tol, _loc_tol,\
                                           _report_shape, _report_cat, _similarity_transform ) \
{  ODB_PARAMS_INIT( ODB_ACT_LAYER_VERIFY_TOOLING_HOLES_SET ); \
   ODB_PARAM_SET_OBJ(_ld);                          \
   ODB_PARAM_SET_OBJ(_set_lst);                     \
   ODB_PARAM_SET_OBJ(_holes_lst);                   \
   ODB_PARAM_SET_I(_size_tol);                      \
   ODB_PARAM_SET_I(_loc_tol);                       \
   ODB_PARAM_SET_SHAPE(_report_shape);              \
   ODB_PARAM_SET_IP(_report_cat);                   \
   ODB_PARAM_SET_IP(_similarity_transform);         \
   ODB_CALL; }


#define ODB_LAYER_SET_SPAN( _ld, _top_ld, _bottom_ld ) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_SET_SPAN);            \
   ODB_PARAM_SET_OBJ(_ld);                             \
   ODB_PARAM_SET_OBJ(_top_ld);                         \
   ODB_PARAM_SET_OBJ(_bottom_ld);                      \
   ODB_CALL; }

#define ODB_LAYER_WAS_OPENED_POS(_ld, _value)     \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_WAS_OPENED_POS); \
   ODB_PARAM_SET_OBJ(_ld);                        \
   ODB_PARAM_SET_IP(_value);                      \
   ODB_CALL; }

#define ODB_LAYER_CONTOURIZE(_ld, _tol, _excl_texts, _repl_hatch, _max_net_size, _work_on_selected, _sld, _skiped_nets_lst) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_CONTOURIZE);                   \
   ODB_PARAM_SET_OBJ (_ld);                                     \
   ODB_PARAM_SET_I  (_tol);                                     \
   ODB_PARAM_SET_I  (_excl_texts);                              \
   ODB_PARAM_SET_I  (_repl_hatch);                              \
   ODB_PARAM_SET_I  (_max_net_size);                            \
   ODB_PARAM_SET_I  (_work_on_selected);                        \
   ODB_PARAM_SET_OBJP (_sld);                                   \
   ODB_PARAM_SET_OBJP (_skiped_nets_lst);                       \
   ODB_CALL; }
#define ODB_LAYER_CONTOURIZE_FILTER(_ld, _tol, _excl_texts, _repl_hatch, _max_net_size, _work_on_selected,\
                                    _attrs_lst, _areas_lst, _exclude, _sld, _skiped_nets_lst ) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_CONTOURIZE_FILTER);                   \
   ODB_PARAM_SET_OBJ (_ld);                                     \
   ODB_PARAM_SET_I  (_tol);                                     \
   ODB_PARAM_SET_I  (_excl_texts);                              \
   ODB_PARAM_SET_I  (_repl_hatch);                              \
   ODB_PARAM_SET_I  (_max_net_size);                            \
   ODB_PARAM_SET_I  (_work_on_selected);                        \
   ODB_PARAM_SET_OBJ (_attrs_lst);                              \
   ODB_PARAM_SET_OBJ (_areas_lst);                              \
   ODB_PARAM_SET_I   (_exclude);                                \
   ODB_PARAM_SET_OBJP (_sld);                                   \
   ODB_PARAM_SET_OBJP (_skiped_nets_lst);                       \
   ODB_CALL; }

#define ODB_LAYER_GET_MASK_LAYER( _ld, _exclude ) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_MASK_LAYER );   \
   ODB_PARAM_SET_OBJP ( _ld   );		      \
   ODB_PARAM_SET_IP( _exclude );		      \
   ODB_CALL; }

#define ODB_LAYER_SET_MASK_LAYER( _ld, _exclude ) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_SET_MASK_LAYER );  \
   ODB_PARAM_SET_OBJ ( _ld   );			      \
   ODB_PARAM_SET_I( _exclude );		              \
   ODB_CALL; }

#define ODB_LAYER_FILTER_DRAWN( _ld, _mode, _net_sz,	\
				_min_line_sz,		\
				_max_line_sz,		\
				_apply_statistical_fltr,\
				_cross_hole_size,	\
				_ls_us, _d_lst_lst )	\
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_FILTER_DRAWN);		\
   ODB_PARAM_SET_OBJ  ( _ld   );			\
   ODB_PARAM_SET_I    ( _mode );			\
   ODB_PARAM_SET_I    ( _net_sz );			\
   ODB_PARAM_SET_I    ( _min_line_sz );			\
   ODB_PARAM_SET_I    ( _max_line_sz );			\
   ODB_PARAM_SET_I    ( _apply_statistical_fltr );	\
   ODB_PARAM_SET_I    ( _cross_hole_size );		\
   ODB_PARAM_SET_OBJP ( _ls_us );			\
   ODB_PARAM_SET_OBJP ( _d_lst_lst );			\
   ODB_CALL; }

#define ODB_LAYER_FILTER_CROSSHATCH(	_ld,			\
					_mode,			\
					_net_sz,		\
					_connect_tol,		\
					_angle_tol,		\
					_pitch_tol,		\
					_min_line_sz,		\
					_max_line_sz,		\
					_single_size_crosshatch,\
					_p_lst_lst,		\
					_o_lst_lst )		\
{ ODB_PARAMS_INIT(ODB_ACT_LAYER_FILTER_CROSSHATCH);		\
    ODB_PARAM_SET_OBJ  ( _ld   );				\
    ODB_PARAM_SET_I    ( _mode );				\
    ODB_PARAM_SET_I    ( _net_sz );				\
    ODB_PARAM_SET_I    ( _connect_tol );			\
    ODB_PARAM_SET_D    ( _angle_tol );				\
    ODB_PARAM_SET_I    ( _pitch_tol );				\
    ODB_PARAM_SET_I    ( _min_line_sz );			\
    ODB_PARAM_SET_I    ( _max_line_sz );			\
    ODB_PARAM_SET_I    ( _single_size_crosshatch );		\
    ODB_PARAM_SET_OBJP ( _p_lst_lst );				\
    ODB_PARAM_SET_OBJP ( _o_lst_lst );				\
    ODB_CALL; }

#define ODB_LAYER_PHYS_COUNT_F( _ld, _count )	\
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_PHYS_COUNT_F);	\
   ODB_PARAM_SET_OBJ(_ld);			\
   ODB_PARAM_SET_IP (_count);			\
   ODB_CALL; }

#define ODB_LAYER_UNMERGE( _ld, _ld_p )		\
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_UNMERGE);	\
   ODB_PARAM_SET_OBJ ( _ld   );			\
   ODB_PARAM_SET_OBJP ( _ld_p );		\
   ODB_CALL; }

#define ODB_LAYER_APPEND_LAYER( _ld_id, _lyr_id, _pol )	    \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_APPEND_LAYER);		    \
 ODB_PARAM_SET_OBJ  ( _ld_id   );			    \
 ODB_PARAM_SET_OBJ  ( _lyr_id );			    \
 ODB_PARAM_SET_I    ( _pol );				    \
 ODB_CALL; }

#define ODB_RES_ADD_ATTR(_name, _value)        \
 { ODB_PARAMS_INIT(ODB_ACT_RES_ADD_ATTR);      \
   ODB_PARAM_SET_S (_name);                    \
   ODB_PARAM_SET_S (_value);                   \
   ODB_CALL; }

#define ODB_LAYER_GET_EXPOSED_LYRS(_ld, _bot_cu_lyrs_lst, _bot_sm_lst, _top_cu_lyrs_lst, _top_sm_lst) \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_GET_EXPOSED_AREA_LAYERS); \
   ODB_PARAM_SET_OBJ(_ld);                        \
   ODB_PARAM_SET_OBJP (_bot_cu_lyrs_lst);         \
   ODB_PARAM_SET_OBJP (_bot_sm_lst);		  \
   ODB_PARAM_SET_OBJP (_top_cu_lyrs_lst);	  \
   ODB_PARAM_SET_OBJP (_top_sm_lst);		  \
   ODB_CALL; }

#define ODB_LAYER_OPTIMIZE_POLARITY(_ld, _ld_p)	    \
 { ODB_PARAMS_INIT(ODB_ACT_LAYER_OPTIMIZE_POLARITY);\
 ODB_PARAM_SET_OBJ  (_ld);			    \
 ODB_PARAM_SET_OBJP (_ld_p);			    \
 ODB_CALL; }

#define ODB_LAYER_SUBSTITUTE_TRACES( _ld, _tol, _line_width_min, _line_width_max, _pad_width_min, _pad_width_max, _pad_length_min, _pad_length_max, _line_tol, _arc_tol, _conn_tol )\
{       ODB_PARAMS_INIT(ODB_ACT_LAYER_SUBSTITUTE_TRACES);   \
        ODB_PARAM_SET_OBJ	(_ld);                      \
        ODB_PARAM_SET_I		(_tol);                     \
        ODB_PARAM_SET_I		(_line_width_min);          \
        ODB_PARAM_SET_I		(_line_width_max);          \
        ODB_PARAM_SET_I		(_pad_width_min);           \
        ODB_PARAM_SET_I		(_pad_width_max);           \
        ODB_PARAM_SET_I		(_pad_length_min);          \
        ODB_PARAM_SET_I		(_pad_length_max);          \
        ODB_PARAM_SET_I		(_line_tol);                \
        ODB_PARAM_SET_I		(_arc_tol);                 \
        ODB_PARAM_SET_I		(_conn_tol);                \
        ODB_CALL; }

#define ODB_RES_ADD_CATEGORIES(_categories)    \
 { ODB_PARAMS_INIT(ODB_ACT_RES_ADD_CATEGORIES);\
   ODB_PARAM_SET_CATEGORIES (_categories);     \
   ODB_PARAM_SET_I (_LENGTH(_categories));         \
   ODB_CALL; }

#define ODB_RES_ADD_ONE_CATEGORY(_cat,_cat_num)    \
 { ODB_PARAMS_INIT(ODB_ACT_RES_ADD_ONE_CATEGORY);\
   ODB_PARAM_SET_CATEGORIES (_cat);     \
   ODB_PARAM_SET_IP (_cat_num);         \
   ODB_CALL; }

#define ODB_RES_CATEGORY_EXISTS(_cat,_exists)    \
 { ODB_PARAMS_INIT(ODB_ACT_RES_CATEGORY_EXISTS);\
   ODB_PARAM_SET_CATEGORIES (_cat);     \
   ODB_PARAM_SET_IP (_exists);         \
   ODB_CALL; }

#define ODB_RES_SORT_CATEGORIES(_sort_order, _num)  \
 { ODB_PARAMS_INIT(ODB_ACT_RES_SORT_CATEGORIES);    \
   ODB_PARAM_SET_IP (_sort_order);                  \
   ODB_PARAM_SET_I  (_num);                         \
   ODB_CALL; }

#define ODB_RES_ADD_MEAS(_ld,_num_cat,_shape1,_shape2,_shape3,_alarm) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_ADD_MEAS);      \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I (_num_cat);                 \
   ODB_PARAM_SET_SHAPE (_shape1);              \
   ODB_PARAM_SET_SHAPE (_shape2);              \
   ODB_PARAM_SET_SHAPE (_shape3);              \
   ODB_PARAM_SET_I (_alarm);                   \
   ODB_CALL; }

#define ODB_RES_ADD_MEAS_FIX(_ld,_num_cat,_shape1,_shape2,_shape3,_alarm,_fixmode, _enable_fix) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_ADD_MEAS_FIX);  \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I (_num_cat);                 \
   ODB_PARAM_SET_SHAPE (_shape1);              \
   ODB_PARAM_SET_SHAPE (_shape2);              \
   ODB_PARAM_SET_SHAPE (_shape3);              \
   ODB_PARAM_SET_I (_alarm);                   \
   ODB_PARAM_SET_I (_fixmode);                 \
   ODB_PARAM_SET_I (_enable_fix);                 \
   ODB_CALL; }

#define ODB_RES_ADD_MEAS_F(_ld,_num_cat,_shape1,_f1,_f2,_alarm) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_ADD_MEAS_F);    \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I (_num_cat);                 \
   ODB_PARAM_SET_SHAPE (_shape1);              \
   ODB_PARAM_SET_F (_f1);                      \
   ODB_PARAM_SET_F (_f2);                      \
   ODB_PARAM_SET_I (_alarm);                   \
   ODB_CALL; }

#define ODB_RES_ADD_MEAS_F_FIX(_ld,_num_cat,_shape1,_f1,_f2,_alarm,_fixmode, _enable_fix) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_ADD_MEAS_F_FIX);\
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I (_num_cat);                 \
   ODB_PARAM_SET_SHAPE (_shape1);              \
   ODB_PARAM_SET_F (_f1);                      \
   ODB_PARAM_SET_F (_f2);                      \
   ODB_PARAM_SET_I (_alarm);                   \
   ODB_PARAM_SET_I (_fixmode);                 \
   ODB_PARAM_SET_I (_enable_fix);                 \
   ODB_CALL; }

#define ODB_RES_CALC(_ld,_cat_num, _calc, _result) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_CALC);          \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I (_cat_num);                 \
   ODB_PARAM_SET_I (_calc);                    \
   ODB_PARAM_SET_IP(_result);                  \
   ODB_CALL; }

#define ODB_RES_CLASSIFY_LOCATION(_shape,_lname, _attr_name, _area_name) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_CLASSIFY_LOCATION); \
   ODB_PARAM_SET_SHAPE(_shape);                \
   ODB_PARAM_SET_S (_lname);                   \
   ODB_PARAM_SET_S (_attr_name);               \
   ODB_PARAM_SET_S (_area_name);               \
   ODB_PARAM_SET_I (sizeof(_area_name));       \
   ODB_CALL; }

#define ODB_RES_CLASSIFY_BY_PROC(_shape, _lname, \
				 _side, _attr_name, _area_name) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_CLASSIFY_BY_PROC); \
   ODB_PARAM_SET_SHAPE(_shape);                \
   ODB_PARAM_SET_S (_lname);                   \
   ODB_PARAM_SET_I (_side);                    \
   ODB_PARAM_SET_S (_attr_name);               \
   ODB_PARAM_SET_S (_area_name);               \
   ODB_PARAM_SET_I (sizeof(_area_name));       \
   ODB_CALL; }

#define ODB_RES_GET_ATTR(_name, _value)        \
 { ODB_PARAMS_INIT(ODB_ACT_RES_GET_ATTR);      \
   ODB_PARAM_SET_S (_name);                    \
   ODB_PARAM_SET_S (_value);                   \
   ODB_CALL; }

#define ODB_RES_GET_CATEGORIES(_lld)    	\
 { ODB_PARAMS_INIT(ODB_ACT_RES_GET_CATEGORIES); \
   ODB_PARAM_SET_OBJP(_lld);  			\
   ODB_CALL; }

#define ODB_RES_GET_CATEGORY_TITLE(_cat_num, _name)  \
 { ODB_PARAMS_INIT(ODB_ACT_RES_GET_CATEGORY_TITLE);\
   ODB_PARAM_SET_I (_cat_num);                 \
   ODB_PARAM_SET_S(_name);                     \
   ODB_CALL; }

#define ODB_RES_GET_CATEGORY_NAME(_cat_num, _name)  \
    { ODB_PARAMS_INIT(ODB_ACT_RES_GET_CATEGORY_NAME);\
      ODB_PARAM_SET_I (_cat_num);                 \
      ODB_PARAM_SET_S(_name);                     \
      ODB_CALL; }

#define ODB_RES_GET_LAYER(_serial, _ld)        \
   { ODB_PARAMS_INIT(ODB_ACT_RES_GET_LAYER);   \
     ODB_PARAM_SET_IP  (_serial);              \
     ODB_PARAM_SET_OBJP(_ld);                  \
     ODB_CALL; }

#define ODB_RES_GET_MEAS(_ld, _cat_num, _serial, _shape) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_GET_MEAS);      \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I (_cat_num);                 \
   ODB_PARAM_SET_IP(_serial);                  \
   ODB_PARAM_SET_SHAPE(_shape);                \
   ODB_CALL; }

#define ODB_RES_GET_MEAS_SIZE(_ld,_cat_num, _serial, _size) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_GET_MEAS_SIZE); \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I (_cat_num);                 \
   ODB_PARAM_SET_IP(_serial);                  \
   ODB_PARAM_SET_DP(_size);                    \
   ODB_CALL; } 

#define ODB_RES_GET_MEAS_ID_TEXT( _ld, _cat_num, _serial, _id_num, _str ) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_GET_MEAS_ID_TEXT ); \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I (_cat_num);                 \
   ODB_PARAM_SET_IP(_serial);                  \
   ODB_PARAM_SET_I (_id_num);                 \
   ODB_PARAM_SET_S( _str);                    \
   ODB_CALL; }
   
#define ODB_RES_MEAS_SORT( _ld )               \
 { ODB_PARAMS_INIT(ODB_ACT_RES_MEAS_SORT );    \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_CALL; }

#define ODB_RES_REPORT_ACTION(_name,_ld,_line) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_REPORT_ACTION); \
   ODB_PARAM_SET_S (_name);                    \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_S (_line);                    \
   ODB_CALL; }

#define ODB_RES_REPORT_ALARMS(_ld, _cat_num)   \
 { ODB_PARAMS_INIT(ODB_ACT_RES_REPORT_ALARMS); \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I (_cat_num);                 \
   ODB_CALL; }

#define ODB_RES_REPORT_HDR(_line)              \
 { ODB_PARAMS_INIT(ODB_ACT_RES_REPORT_HDR);    \
   ODB_PARAM_SET_S (_line);                    \
   ODB_CALL; }

#define ODB_RES_REPORT_HIST(_ld,_cat_num,_x_num,_y_num,_x,_y) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_REPORT_HIST);   \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I (_cat_num);                 \
   ODB_PARAM_SET_I (_x_num);                   \
   ODB_PARAM_SET_I (_y_num);                   \
   ODB_PARAM_SET_I (_x);                       \
   ODB_PARAM_SET_I (_y);                       \
   ODB_CALL; }

#define ODB_RES_REPORT_TAG(_ld, _shape, _line) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_REPORT_TAG);    \
   ODB_PARAM_SET_OBJ (_ld);                    \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_S (_line);                    \
   ODB_CALL; }

#define ODB_RES_REPORT_TEXT(_line)              \
 { ODB_PARAMS_INIT(ODB_ACT_RES_REPORT_TEXT);    \
   ODB_PARAM_SET_S (_line);                     \
   ODB_CALL; }

#define ODB_RES_SET_DISP_LYRS(                  \
    _ld, _disp_ld1, _disp_ld2, _disp_ld3, _disp_ld4) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_SET_DISP_LYRS);  \
   ODB_PARAM_SET_OBJ(_ld);                      \
   ODB_PARAM_SET_OBJ(_disp_ld1);                \
   ODB_PARAM_SET_OBJ(_disp_ld2);                \
   ODB_PARAM_SET_OBJ(_disp_ld3);                \
   ODB_PARAM_SET_OBJ(_disp_ld4);                \
   ODB_CALL; }

#define ODB_RES_GET_RANGE(_cat_num,_range_values)  \
 { ODB_PARAMS_INIT(ODB_ACT_RES_GET_RANGE);         \
   ODB_PARAM_SET_I (_cat_num);                     \
   ODB_PARAM_SET_OBJP (_range_values);             \
   ODB_CALL; }

#define ODB_RES_SET_MEAS_SCALAR(_dvalue,_units_sensitive)  \
 { ODB_PARAMS_INIT(ODB_ACT_RES_SET_MEAS_SCALAR);  \
   ODB_PARAM_SET_D (_dvalue);                     \
   ODB_PARAM_SET_I (_units_sensitive);            \
   ODB_CALL; }

#define ODB_RES_SET_MEAS_SCALAR_SQR(_dvalue,_units_sensitive)  \
 { ODB_PARAMS_INIT(ODB_ACT_RES_SET_MEAS_SCALAR_SQR);  \
   ODB_PARAM_SET_D (_dvalue);                     \
   ODB_PARAM_SET_I (_units_sensitive);            \
   ODB_CALL; }

#define ODB_RES_SET_MEAS_ID_SCALAR(_id_num,_dval,_us,_sqr)  \
 { ODB_PARAMS_INIT(ODB_ACT_RES_SET_MEAS_ID_SCALAR);  \
   ODB_PARAM_SET_I (_id_num);                     \
   ODB_PARAM_SET_D (_dval);                      \
   ODB_PARAM_SET_I (_us);                       \
   ODB_PARAM_SET_I (_sqr);                     \
   ODB_CALL; }

#define ODB_RES_SET_MEAS_ID_TEXT(_id_num,_str)  \
 { ODB_PARAMS_INIT(ODB_ACT_RES_SET_MEAS_ID_TEXT);  \
   ODB_PARAM_SET_I (_id_num);                     \
   ODB_PARAM_SET_S (_str);                       \
   ODB_CALL; }

#define ODB_RES_SET_SUB_CATEGORY(_basic_cat_num,_prefix,_suffix)  \
 { ODB_PARAMS_INIT(ODB_ACT_RES_SET_SUB_CATEGORY);  \
   ODB_PARAM_SET_I (_basic_cat_num);     \
   ODB_PARAM_SET_S (_prefix);            \
   ODB_PARAM_SET_S (_suffix);            \
   ODB_CALL; }

#define ODB_RES_GET_SUB_CATEGORIES(_cat_num, _lld)    	\
 { ODB_PARAMS_INIT(ODB_ACT_RES_GET_SUB_CATEGORIES); \
   ODB_PARAM_SET_I (_cat_num);                 \
   ODB_PARAM_SET_OBJP(_lld);  			\
   ODB_CALL; }

#define ODB_RES_TYPICAL_SIZE(_ld,_cat_num, _resolution, _size) \
 { ODB_PARAMS_INIT(ODB_ACT_RES_TYPICAL_SIZE);   \
   ODB_PARAM_SET_OBJ(_ld);                      \
   ODB_PARAM_SET_I (_cat_num);                  \
   ODB_PARAM_SET_I (_resolution);               \
   ODB_PARAM_SET_IP(_size);                     \
   ODB_CALL; }

#define ODB_RES_SET_CAT_LIMITS_SENSITIVE( _cat_num, _sensitive ) \
 { ODB_PARAMS_INIT( ODB_ACT_RES_SET_CATEGORY_LIMITS_SENSITIVE );      \
   ODB_PARAM_SET_I ( _cat_num );                                      \
   ODB_PARAM_SET_I ( _sensitive );                                    \
   ODB_CALL; }

#define ODB_RES_CALC_RANGE(_ld,_cat_num, _calc_type, _low_limit, _high_limit, _result) \
 { ODB_PARAMS_INIT( ODB_ACT_RES_CALC_RANGE ); \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I (_cat_num);                 \
   ODB_PARAM_SET_I (_calc_type );              \
   ODB_PARAM_SET_I (_low_limit);               \
   ODB_PARAM_SET_I (_high_limit);              \
   ODB_PARAM_SET_IP(_result);                  \
   ODB_CALL; }

#define ODB_RES_UPDATE_MEAS(_ld, _index, _cat_num, _shape ) \
 { ODB_PARAMS_INIT( ODB_ACT_RES_UPDATE_MEAS ); \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I (_index);                   \
   ODB_PARAM_SET_I (_cat_num);                 \
   ODB_PARAM_SET_SHAPE(_shape);                \
   ODB_CALL; }

#define ODB_RES_UPDATE_MEAS_TEXT(_ld, _index, _text_index, _text ) \
 { ODB_PARAMS_INIT( ODB_ACT_RES_UPDATE_MEAS_TEXT ); \
   ODB_PARAM_SET_OBJ(_ld);			    \
   ODB_PARAM_SET_I (_index);			    \
   ODB_PARAM_SET_I (_text_index);		    \
   ODB_PARAM_SET_S (_text);			    \
   ODB_CALL; }

#define ODB_RES_SET_MEAS_DELETED(_ld, _index )      \
 { ODB_PARAMS_INIT( ODB_ACT_RES_SET_MEAS_DELETED ); \
   ODB_PARAM_SET_OBJ (_ld);                         \
   ODB_PARAM_SET_I   (_index);                      \
   ODB_CALL; }

#define ODB_RES_GET_NUM_MEAS(_ld, _num )        \
 { ODB_PARAMS_INIT( ODB_ACT_RES_GET_NUM_MEAS ); \
   ODB_PARAM_SET_OBJ (_ld);                     \
   ODB_PARAM_SET_IP  (_num);                    \
   ODB_CALL; }

#define ODB_RES_GET_MEAS_SPACING(_ld, _index, _ld1, _nf1, _ld2, _nf2, _spacing ) \
 { ODB_PARAMS_INIT( ODB_ACT_RES_GET_MEAS_SPACING ); \
   ODB_PARAM_SET_OBJ (_ld);                      \
   ODB_PARAM_SET_I   (_index);                   \
   ODB_PARAM_SET_OBJP( _ld1 );	                 \
   ODB_PARAM_SET_IP  ( _nf1 );                   \
   ODB_PARAM_SET_OBJP( _ld2 );	                 \
   ODB_PARAM_SET_IP  ( _nf2 );                   \
   ODB_PARAM_SET_IP  ( _spacing );               \
   ODB_CALL; }

#define ODB_RES_GET_MEAS_ADDED(_ld, _index, _added_nfs ) \
 { ODB_PARAMS_INIT( ODB_ACT_RES_GET_MEAS_ADDED ); \
   ODB_PARAM_SET_OBJ (_ld);                       \
   ODB_PARAM_SET_I   (_index);                    \
   ODB_PARAM_SET_OBJP( _added_nfs );              \
   ODB_CALL; }

#define ODB_RES_UNDO_MEAS_FIXES(_ld, _index )      \
 { ODB_PARAMS_INIT( ODB_ACT_RES_UNDO_MEAS_FIXES ); \
 ODB_PARAM_SET_OBJ (_ld);                          \
 ODB_PARAM_SET_I   (_index);                       \
 ODB_CALL; }

#define ODB_SETUP_GET_ERF_UNITS(_units) \
 { ODB_PARAMS_INIT(ODB_ACT_SETUP_GET_ERF_UNITS);  \
   ODB_PARAM_SET_IP (_units);                     \
   ODB_CALL; }

#define ODB_SETUP_GET_ERF_VAR(_var_name,_value,_len) \
 { char _temp_value[FILENAME_MAX];  \
   int len = MIN( _len, FILENAME_MAX );\
   ODB_PARAMS_INIT(ODB_ACT_SETUP_GET_ERF_VAR);  \
   ODB_PARAM_SET_S (_var_name);                 \
   ODB_PARAM_SET_S (_temp_value);               \
   ODB_PARAM_SET_I (len);                      \
   ODB_CALL;                                    \
   _value[0] = '\0';			    \
   if(_temp_value[0] != '\0') {			\
   strncpy(_value,_temp_value,len-1);		\
   _value[len-1] = '\0' ;			\
   }}

#define ODB_SETUP_GET_ERF_VAR2(_var_name,_value) \
		ODB_SETUP_GET_ERF_VAR(_var_name,_value,sizeof(_value)-1)

#define ODB_SETUP_GET_ERF_VAR1(_var_name) \
		ODB_SETUP_GET_ERF_VAR2(#_var_name,_var_name)

#define ODB_SETUP_CHECK_ERF_VAR(_var_name,_value,_len,_ok) \
 { odb_name _temp_value;                          \
   ODB_PARAMS_INIT(ODB_ACT_SETUP_CHECK_ERF_VAR);  \
   ODB_PARAM_SET_S (_var_name);                   \
   ODB_PARAM_SET_S (_temp_value);                 \
   ODB_PARAM_SET_I (_len);                        \
   ODB_CALL;                                      \
   _ok = ODB_FALSE;                               \
   if(_temp_value[0] != '\0') {                   \
       strncpy(_value,_temp_value,_len-1);        \
       _value[_len-1] = '\0' ;                    \
       _ok = ODB_TRUE;                            \
   }}

#define ODB_SETUP_GET_ERF_VAR_NUMBER(_name)	\
   { odb_name s_##_name;			\
     double d_##_name;				\
     s_##_name[0] = '\0';			\
     ODB_SETUP_GET_ERF_VAR2(#_name,s_##_name);	\
     if (s_##_name[0] != '\0') {		\
        sscanf(s_##_name,"%lf",&d_##_name);	\
         _name = d_##_name;			\
     }}

#define ODB_SETUP_GET_ERF_VAR_PIXELS(_name)      \
   { odb_name s_##_name;                         \
     double d_##_name;                           \
     int u_##_name ;                  \
     s_##_name[0] = '\0' ;                       \
     ODB_SETUP_GET_ERF_VAR                       \
         (#_name, s_##_name,sizeof(s_##_name)-1); \
     ODB_SETUP_GET_ERF_UNITS(u_##_name);         \
     if(s_##_name[0] != '\0'){ \
        sscanf(s_##_name,"%lf",&d_##_name);  \
        if(u_##_name == ODB_UNITS_INCH){     \
         _name = MIL2P(d_##_name) ;          \
        } else {                             \
         _name = MIC2P(d_##_name) ;          \
     }}}

#define ODB_SETUP_GET_PARAMS(_params)          \
{                                              \
   ODB_SETUP_SET_VERSION(ODB_VERSION)          \
   ODB_PARAMS_INIT(ODB_ACT_SETUP_GET_PARAMS);  \
   ODB_PARAM_SET_PROG_PARAMS (_params);        \
   ODB_PARAM_SET_I (_LENGTH(_params));         \
   ODB_CALL; }

#define ODB_SETUP_GET_PARAM_OPTION(_pname,_option,_value) \
 { ODB_PARAMS_INIT(ODB_ACT_SETUP_GET_PARAM_OPTION);       \
   ODB_PARAM_SET_S (_pname);                   \
   ODB_PARAM_SET_S (_option);                  \
   ODB_PARAM_SET_IP (_value);                  \
   ODB_CALL; }

#define ODB_SETUP_SET_MODIFY(_set_value)          \
 { ODB_PARAMS_INIT(ODB_ACT_SETUP_SET_MODIFY);  \
   ODB_PARAM_SET_I (_set_value);             \
   ODB_CALL; }

#define ODB_SETUP_SET_VERSION(_set_value)      \
 { ODB_PARAMS_INIT(ODB_ACT_SETUP_SET_VERSION); \
   ODB_PARAM_SET_I (_set_value);               \
   ODB_CALL; }

#define ODB_SHAPE_DEBUG_WRITE_XML(_shape, _filename, _label) \
{  ODB_PARAMS_INIT(ODB_ACT_SHAPE_DEBUG_WRITE_XML);   \
   ODB_PARAM_SET_SHAPE (_shape);                     \
   ODB_PARAM_SET_S (_filename);                      \
   ODB_PARAM_SET_S (_label);                         \
   ODB_CALL; }

#define ODB_SHAPE_AIR_GAP_LAYER(_seg, _layer, _air_gap) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_AIR_GAP_LAYER);        \
   ODB_PARAM_SET_SHAPE (_seg);                 \
   ODB_PARAM_SET_OBJ   (_layer);               \
   ODB_PARAM_SET_IP    (_air_gap);             \
   ODB_CALL; }

#define ODB_SHAPE_AIR_GAP_LIST(_seg, _shape_list, _air_gap) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_AIR_GAP_LIST);\
   ODB_PARAM_SET_SHAPE (_seg);                 \
   ODB_PARAM_SET_OBJ   (_shape_list);          \
   ODB_PARAM_SET_IP    (_air_gap);             \
   ODB_CALL; }

#define ODB_SHAPE_AREA_DIFF(_in_list, _out_list) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_AREA_DIFF);     \
   ODB_PARAM_SET_OBJ   (_in_list);               \
   ODB_PARAM_SET_OBJP  (_out_list);              \
   ODB_CALL; }
   
#define ODB_SHAPE_CLIP(_cliped_list,_mask_shape,_mode,_clip_as_contour,_out_list) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_CLIP);    \
   ODB_PARAM_SET_OBJ   (_cliped_list);     \
   ODB_PARAM_SET_SHAPE (_mask_shape);      \
   ODB_PARAM_SET_I     (_mode);            \
   ODB_PARAM_SET_I     (_clip_as_contour);            \
   ODB_PARAM_SET_OBJP  (_out_list);        \
   ODB_CALL; }

#define ODB_SHAPE_AREA_DIFF_TOL(_in_list, _tol, _out_list) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_AREA_DIFF_TOL); \
 ODB_PARAM_SET_OBJ   (_in_list);               \
 ODB_PARAM_SET_I     (_tol);                   \
 ODB_PARAM_SET_OBJP  (_out_list);              \
 ODB_CALL; }

#define ODB_SHAPE_AREA_INTER(_in_list, _out_list)\
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_AREA_INTER);    \
   ODB_PARAM_SET_OBJ   (_in_list);               \
   ODB_PARAM_SET_OBJP  (_out_list);              \
   ODB_CALL; }

#define ODB_SHAPE_AREA_INTER_TOL(_in_list, _tol, _out_list)\
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_AREA_INTER_TOL);\
 ODB_PARAM_SET_OBJ   (_in_list);               \
 ODB_PARAM_SET_I     (_tol);                   \
 ODB_PARAM_SET_OBJP  (_out_list);              \
 ODB_CALL; }

#define ODB_SHAPE_AREA_UNION(_in_list, _out_list)\
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_AREA_UNION);    \
   ODB_PARAM_SET_OBJ   (_in_list);               \
   ODB_PARAM_SET_OBJP  (_out_list);              \
   ODB_CALL; }

#define ODB_SHAPE_AREA_UNION_TOL(_in_list, _tol, _out_list)\
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_AREA_UNION_TOL); \
   ODB_PARAM_SET_OBJ   (_in_list);                \
   ODB_PARAM_SET_I     (_tol);                    \
   ODB_PARAM_SET_OBJP  (_out_list);               \
   ODB_CALL; }

#define ODB_SHAPE_CONTOUR(_shape, _contour)      \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_CONTOUR);       \
   ODB_PARAM_SET_SHAPE (_shape);                 \
   ODB_PARAM_SET_SHAPE (_contour);               \
   ODB_CALL; }

#define ODB_SHAPE_BOTTLENECK(_in_list, _dist, _dist2peri,\
                             _check_aa, _max_aa,        \
                             _out_list, _out_val_list ) \
{                                                       \
    ODB_PARAMS_INIT(ODB_ACT_SHAPE_BOTTLENECK);          \
    ODB_PARAM_SET_OBJ(_in_list);                        \
    ODB_PARAM_SET_I(_dist);                             \
    ODB_PARAM_SET_D(_dist2peri);                        \
    ODB_PARAM_SET_I(_check_aa );                        \
    ODB_PARAM_SET_D(_max_aa );                          \
    ODB_PARAM_SET_OBJP(_out_list);                      \
    ODB_PARAM_SET_OBJP(_out_val_list);                  \
    ODB_CALL; }

#define ODB_SHAPE_BREAK_ARC(_shape,_tol,_list)  \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_BREAK_ARC);    \
   ODB_PARAM_SET_SHAPE(_shape);                 \
   ODB_PARAM_SET_I(_tol);                       \
   ODB_PARAM_SET_OBJP(_list);                   \
   ODB_CALL; }

#define ODB_SHAPE_CENTER(_shape, _center)      \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_CENTER);      \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_SHAPE (_center);              \
   ODB_CALL; }

#define ODB_SHAPE_MIDPT(_shape, _midpt)        \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_MIDPT);       \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_SHAPE (_midpt);               \
   ODB_CALL; }

#define ODB_SHAPE_CENTER_LIST(_slist, _center)  \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_CENTER_LIST); \
   ODB_PARAM_SET_OBJ   (_slist);               \
   ODB_PARAM_SET_SHAPE (_center);              \
   ODB_CALL; }

#define ODB_SHAPE_CLEAN_SURFACE(_contour, _smooth_tol, _clean_holes_size, \
    _clean_holes_mode, _fold_length)               \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_CLEAN_SURFACE);   \
   ODB_PARAM_SET_SHAPE (_contour);                 \
   ODB_PARAM_SET_I     (_smooth_tol);              \
   ODB_PARAM_SET_I     (_clean_holes_size);        \
   ODB_PARAM_SET_I     (_clean_holes_mode);        \
   ODB_PARAM_SET_I     (_fold_length);             \
   ODB_CALL; }

#define ODB_SHAPE_CLOSE_TRI(_shape1, _shape2, _shape_o, _length, _ok_p)  \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_CLOSE_TRI);   \
   ODB_PARAM_SET_SHAPE (_shape1);              \
   ODB_PARAM_SET_SHAPE (_shape2);              \
   ODB_PARAM_SET_SHAPE (_shape_o);             \
   ODB_PARAM_SET_I     (_length);              \
   ODB_PARAM_SET_IP    (_ok_p);                \
   ODB_CALL; }

#define ODB_SHAPE_CLEAN_SIP(_contour, _out_list)   \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_CLEAN_SIP);       \
   ODB_PARAM_SET_SHAPE (_contour);                 \
   ODB_PARAM_SET_OBJP  (_out_list);                \
   ODB_CALL; }

#define ODB_SHAPE_COPPER_AREA(_shape,_res, _area)\
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_COPPER_AREA); \
   ODB_PARAM_SET_SHAPE    (_shape);            \
   ODB_PARAM_SET_I      (_res);                \
   ODB_PARAM_SET_DP     (_area);               \
   ODB_CALL; }

#define ODB_SHAPE_CALC_AREA(_shape, _area)   \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_CALC_AREA); \
   ODB_PARAM_SET_SHAPE    (_shape);          \
   ODB_PARAM_SET_DP     (_area);             \
   ODB_CALL; }

#define ODB_SHAPE_COUNT_CONT_NREC(_shape, _count) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_COUNT_CONT_NREC);  \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_IP  (_count);                 \
   ODB_CALL; }

#define ODB_SHAPE_COVER_LAYER(_shape, _ld, _max_search, _seg, _dist, _rel) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_COVER_LAYER); \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_OBJ(_ld);                     \
   ODB_PARAM_SET_I  (_max_search);             \
   ODB_PARAM_SET_SHAPE (_seg);                 \
   ODB_PARAM_SET_IP (_dist);                   \
   ODB_PARAM_SET_RELP (_rel);                  \
   ODB_CALL; }

#define ODB_SHAPE_COVER_LIST(_shape, _slist, _seg, _dist, _rel) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_COVER_LIST);  \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_OBJ  (_slist);                \
   ODB_PARAM_SET_SHAPE (_seg);                 \
   ODB_PARAM_SET_IP (_dist);                   \
   ODB_PARAM_SET_RELP (_rel);                  \
   ODB_CALL; }

#define ODB_SHAPE_COVER_LIST_MAX(_shape, _slist, _max_search, _seg, _dist, _rel) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_COVER_LIST_MAX);  \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_OBJ  (_slist);                \
   ODB_PARAM_SET_I  (_max_search);             \
   ODB_PARAM_SET_SHAPE (_seg);                 \
   ODB_PARAM_SET_IP (_dist);                   \
   ODB_PARAM_SET_RELP (_rel);                  \
   ODB_CALL; }

#define ODB_SHAPE_SEG_COVER_LIST(_shape, _slist, _rel) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_SEG_COVER_LIST);  \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_OBJ  (_slist);                \
   ODB_PARAM_SET_RELP (_rel);                  \
   ODB_CALL; }

#define ODB_SHAPE_DIST_MAX(_shape1, _shape2, _max_dist, _seg, _dist, _rel) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_DIST_MAX);    \
   ODB_PARAM_SET_SHAPE (_shape1);              \
   ODB_PARAM_SET_SHAPE (_shape2);              \
   ODB_PARAM_SET_I  (_max_dist);               \
   ODB_PARAM_SET_SHAPE (_seg);                 \
   ODB_PARAM_SET_IP (_dist);                   \
   ODB_PARAM_SET_RELP (_rel);                  \
   ODB_CALL; }

#define ODB_SHAPE_DIST_TO_FC_MAX(_shape, _shape_fc, _max_dist, _seg, _dist, _rel) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_DIST_TO_FC_MAX);    \
   ODB_PARAM_SET_SHAPE (_shape);              \
   ODB_PARAM_SET_SHAPE (_shape_fc);              \
   ODB_PARAM_SET_I  (_max_dist);               \
   ODB_PARAM_SET_SHAPE (_seg);                 \
   ODB_PARAM_SET_IP (_dist);                   \
   ODB_PARAM_SET_RELP (_rel);                  \
   ODB_CALL; }

#define ODB_SHAPE_DIST(_shape1, _shape2, _seg, _dist, _rel) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_DIST);        \
   ODB_PARAM_SET_SHAPE (_shape1);              \
   ODB_PARAM_SET_SHAPE (_shape2);              \
   ODB_PARAM_SET_SHAPE (_seg);                 \
   ODB_PARAM_SET_IP (_dist);                   \
   ODB_PARAM_SET_RELP (_rel);                  \
   ODB_CALL; }

#define ODB_SHAPE_DIST_LAYER(_shape, _ld, _max_search, _seg, _dist, _rel) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_DIST_LAYER);  \
   ODB_PARAM_SET_SHAPE(_shape);                \
   ODB_PARAM_SET_OBJ  (_ld);                   \
   ODB_PARAM_SET_I    (_max_search);           \
   ODB_PARAM_SET_SHAPE(_seg);                  \
   ODB_PARAM_SET_IP   (_dist);                 \
   ODB_PARAM_SET_RELP (_rel);                  \
   ODB_CALL; }

#define ODB_SHAPE_DIST_LIST(_shape, _slist, _seg, _dist, _rel) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_DIST_LIST);   \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_OBJ   (_slist);               \
   ODB_PARAM_SET_SHAPE (_seg);                 \
   ODB_PARAM_SET_IP    (_dist);                \
   ODB_PARAM_SET_RELP  (_rel);                 \
   ODB_CALL; }

#define ODB_SHAPE_DIST_NET(_shape, _ld, _net, _seg, _dist, _rel) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_DIST_NET);        \
   ODB_PARAM_SET_SHAPE (_shape);                   \
   ODB_PARAM_SET_OBJ (_ld);                        \
   ODB_PARAM_SET_I (_net);                         \
   ODB_PARAM_SET_SHAPE (_seg);                     \
   ODB_PARAM_SET_IP    (_dist);                    \
   ODB_PARAM_SET_RELP  (_rel);                     \
   ODB_CALL; }

#define ODB_SHAPE_END_SHAPE(_shape, _end_num, _out_shape) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_END_SHAPE);   \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_I  (_end_num);                \
   ODB_PARAM_SET_SHAPE (_out_shape);           \
   ODB_CALL; }

#define ODB_SHAPE_ENCLOSED_RECT(_cont_shape, _rect_shape, _ok ) \
{  ODB_PARAMS_INIT(ODB_ACT_SHAPE_ENCLOSED_RECT);                \
   ODB_PARAM_SET_SHAPE(_cont_shape);                            \
   ODB_PARAM_SET_SHAPE(_rect_shape);                            \
   ODB_PARAM_SET_IP(_ok);                                       \
   ODB_CALL; }

#define ODB_SHAPE_LINE_END_SEG(_line, _end_num, _seg, _is_ok) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_LINE_END_SEG); \
   ODB_PARAM_SET_SHAPE(_line);                  \
   ODB_PARAM_SET_I    (_end_num);               \
   ODB_PARAM_SET_SHAPE(_seg);                   \
   ODB_PARAM_SET_IP   (_is_ok);                 \
   ODB_CALL; }


#define ODB_SHAPE_EXPAND(_in_shape, _r, _cap, _out_shape) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_EXPAND);      \
   ODB_PARAM_SET_SHAPE (_in_shape);            \
   ODB_PARAM_SET_I (_r);                       \
   ODB_PARAM_SET_CAP (_cap);                   \
   ODB_PARAM_SET_SHAPE (_out_shape);           \
   ODB_CALL; }

#define ODB_SHAPE_EXT_POINT(_point1, _point2, _dist, _out_point) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_EXT_POINT);   \
   ODB_PARAM_SET_SHAPE (_point1);              \
   ODB_PARAM_SET_SHAPE (_point2);              \
   ODB_PARAM_SET_I     (_dist);                \
   ODB_PARAM_SET_SHAPE (_out_point);           \
   ODB_CALL; }

#define ODB_SHAPE_FILL(_shape1, _min_brush, _overlap, _accuracy, \
   _shape_list, _ok_p) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_FILL);        \
   ODB_PARAM_SET_SHAPE (_shape1);              \
   ODB_PARAM_SET_I     (_min_brush);           \
   ODB_PARAM_SET_I     (_overlap);             \
   ODB_PARAM_SET_I     (_accuracy);            \
   ODB_PARAM_SET_OBJP  (_shape_list);          \
   ODB_PARAM_SET_IP    (_ok_p);                \
   ODB_CALL; }

#define ODB_SHAPE_GET_HOLES(_shape, _shape_list)\
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_GET_HOLES);   \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_OBJP (_shape_list);           \
   ODB_CALL; }

#define ODB_SHAPE_GET_ISLAND(_shape, _shape_p) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_GET_ISLAND);  \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_SHAPE (_shape_p);             \
   ODB_CALL; }

#define ODB_SHAPE_GET_CONT_EDGES(_shape, _sld) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_GET_CONT_EDGES);  \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_OBJP  (_sld);                 \
   ODB_CALL; }

#define ODB_SHAPE_GET_NEIGHBORS(_shape, _ld, _dist, _net, _consider_board_net, _same_layer, _search_mode, _out_slist) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_GET_NEIGHBORS);   \
   ODB_PARAM_SET_SHAPE (_shape);                \
   ODB_PARAM_SET_OBJ(_ld);                      \
   ODB_PARAM_SET_I (_dist);                     \
   ODB_PARAM_SET_I (_net);                      \
   ODB_PARAM_SET_I (_consider_board_net);       \
   ODB_PARAM_SET_I (_same_layer);               \
   ODB_PARAM_SET_I (_search_mode);              \
   ODB_PARAM_SET_OBJP(_out_slist);              \
   ODB_CALL; }

#define ODB_SHAPE_GET_NEIGHBORS_FILTER(_shape, _ld, _dist, _net, _consider_board_net, _same_layer, _f_type, _include_attr, _from_nf, _to_nf, _skip_equal_rel_check, _search_mode, _out_slist) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_GET_NEIGHBORS_FILTER);   \
   ODB_PARAM_SET_SHAPE (_shape);                \
   ODB_PARAM_SET_OBJ(_ld);                      \
   ODB_PARAM_SET_I (_dist);                     \
   ODB_PARAM_SET_I (_net);                      \
   ODB_PARAM_SET_I (_consider_board_net);       \
   ODB_PARAM_SET_I (_same_layer);               \
   ODB_PARAM_SET_I (_f_type);			\
   ODB_PARAM_SET_S (_include_attr);             \
   ODB_PARAM_SET_I (_from_nf);                  \
   ODB_PARAM_SET_I (_to_nf);                    \
   ODB_PARAM_SET_I (_skip_equal_rel_check);     \
   ODB_PARAM_SET_I (_search_mode);              \
   ODB_PARAM_SET_OBJP(_out_slist);              \
   ODB_CALL; }

#define ODB_SHAPE_GET_NEIGHBORS_SR(_shape, _layer_sr, _dist, _ignore_img, _net, _consider_board_net, _same_layer, _search_mode, _out_slist) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_GET_NEIGHBORS_SR); \
   ODB_PARAM_SET_SHAPE (_shape);		    \
   ODB_PARAM_SET_OBJ(_layer_sr);		    \
   ODB_PARAM_SET_I (_dist);			    \
   ODB_PARAM_SET_I (_ignore_img);		    \
   ODB_PARAM_SET_I (_net);			    \
   ODB_PARAM_SET_I (_consider_board_net);	    \
   ODB_PARAM_SET_I (_same_layer);		    \
   ODB_PARAM_SET_I (_search_mode);		    \
   ODB_PARAM_SET_OBJP(_out_slist);		    \
   ODB_CALL; }


#define ODB_SHAPE_INTERSECT(_shape1, _shape2, _points_sld) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_INTERSECT);    \
   ODB_PARAM_SET_SHAPE (_shape1);               \
   ODB_PARAM_SET_SHAPE (_shape2);               \
   ODB_PARAM_SET_OBJP  (_points_sld);           \
   ODB_CALL; }

#define ODB_SHAPE_INTERSECT_VIRT(_shape1, _shape2, _points_sld, _virt1, _virt2, _ok) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_INTERSECT_VIRT);    \
 ODB_PARAM_SET_SHAPE (_shape1);                      \
 ODB_PARAM_SET_SHAPE (_shape2);                      \
 ODB_PARAM_SET_OBJP  (_points_sld);                  \
 ODB_PARAM_SET_IP  (_virt1);                         \
 ODB_PARAM_SET_IP  (_virt2);                         \
 ODB_PARAM_SET_IP  (_ok);                            \
 ODB_CALL; }

#define ODB_SHAPE_LEFT_SLIVER(_shape, _layer, _min_len, _max_width, _sliver_list) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_LEFT_SLIVER);  \
   ODB_PARAM_SET_SHAPE (_shape);                \
   ODB_PARAM_SET_OBJ(_layer);                   \
   ODB_PARAM_SET_I (_min_len);                  \
   ODB_PARAM_SET_I (_max_width);                \
   ODB_PARAM_SET_OBJP ( _sliver_list);          \
   ODB_CALL; }

#define ODB_SHAPE_LIMITS(_shape, _limits)       \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_LIMITS);       \
   ODB_PARAM_SET_SHAPE (_shape);                \
   ODB_PARAM_SET_SHAPE (_limits);               \
   ODB_CALL; }

#define ODB_SHAPE_LIMITS_LIST(_slist, _limits)  \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_LIMITS_LIST);  \
   ODB_PARAM_SET_OBJ   (_slist);                \
   ODB_PARAM_SET_SHAPE (_limits);               \
   ODB_CALL; }

#define ODB_SHAPE_TRY_PAD(_shape, _tol, _out_f) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_TRY_PAD); \
   ODB_PARAM_SET_SHAPE(_shape);                \
   ODB_PARAM_SET_I    (_tol);                  \
   ODB_PARAM_SET_F    (_out_f);                \
   ODB_CALL; }

#define ODB_SHAPE_AREA_RECT_COVER(_shape, _rect, _length, _cor) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_AREA_RECT_COVER);              \
   ODB_PARAM_SET_SHAPE(_shape);                                 \
   ODB_PARAM_SET_SHAPE(_rect);                                  \
   ODB_PARAM_SET_IP   (_length);                                \
   ODB_PARAM_SET_DP   (_cor);                                   \
   ODB_CALL; }

#define ODB_SHAPE_LIST_NEAR_LAYER(_in_slist, _ld, _dist, _out_slist) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_LIST_NEAR_LAYER); \
   ODB_PARAM_SET_OBJ(_in_slist);                \
   ODB_PARAM_SET_OBJ(_ld);                      \
   ODB_PARAM_SET_I (_dist);                     \
   ODB_PARAM_SET_OBJP(_out_slist);              \
   ODB_CALL; }

#define ODB_SHAPE_MOVE_CONT(_shape, _dx, _dy)   \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_MOVE_CONT);     \
   ODB_PARAM_SET_SHAPE(_shape);                 \
   ODB_PARAM_SET_I    (_dx);                    \
   ODB_PARAM_SET_I    (_dy);                    \
   ODB_CALL; }

#define ODB_SHAPE_MOVE_SEG(_seg, _point, _dist, _out_seg) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_MOVE_SEG);     \
   ODB_PARAM_SET_SHAPE (_seg);                  \
   ODB_PARAM_SET_SHAPE (_point);                \
   ODB_PARAM_SET_I     (_dist);                 \
   ODB_PARAM_SET_SHAPE (_out_seg);              \
   ODB_CALL; }

#define ODB_SHAPE_NEAR_LAYER(_shape, _ld, _dist, _net, _out_slist) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_NEAR_LAYER);   \
   ODB_PARAM_SET_SHAPE (_shape);                \
   ODB_PARAM_SET_OBJ(_ld);                      \
   ODB_PARAM_SET_I (_dist);                     \
   ODB_PARAM_SET_I (_net);                      \
   ODB_PARAM_SET_OBJP(_out_slist);              \
   ODB_CALL; }

#define ODB_SHAPE_NEAR_LAYER_REF(_shape, _ld, _dist, _net, _ref_nf, _out_slist) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_NEAR_LAYER_REF);   \
   ODB_PARAM_SET_SHAPE (_shape);                \
   ODB_PARAM_SET_OBJ(_ld);                      \
   ODB_PARAM_SET_I (_dist);                     \
   ODB_PARAM_SET_I (_net);                      \
   ODB_PARAM_SET_I (_ref_nf);                   \
   ODB_PARAM_SET_OBJP(_out_slist);              \
   ODB_CALL; }

#define ODB_SHAPE_NEAR_LAYER2(_shape, _ld, _dist, _net, _out_slist) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_NEAR_LAYER);   \
   ODB_PARAM_SET_SHAPE (_shape);                \
   ODB_PARAM_SET_OBJ(_ld);                      \
   ODB_PARAM_SET_I (_dist);                     \
   ODB_PARAM_SET_I (_net);                      \
   ODB_PARAM_SET_OBJP(_out_slist);              \
   ODB_CALL; }

#define ODB_SHAPE_NEAR_LAYER_COARSE(_shape, _ld, _dist, _net, _out_slist) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_NEAR_LAYER_COARSE);   \
   ODB_PARAM_SET_SHAPE (_shape);                \
   ODB_PARAM_SET_OBJ(_ld);                      \
   ODB_PARAM_SET_I (_dist);                     \
   ODB_PARAM_SET_I (_net);                      \
   ODB_PARAM_SET_OBJP(_out_slist);              \
   ODB_CALL; }

#define ODB_SHAPE_NEAR_LIST(_shape, _in_slist, _dist, _out_slist) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_NEAR_LIST);   \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_OBJ   (_in_slist);            \
   ODB_PARAM_SET_I     (_dist);                \
   ODB_PARAM_SET_OBJP  (_out_slist);           \
   ODB_CALL; }

#define ODB_SHAPE_NEAR_LIST_COARSE(_shape, _in_slist, _dist, _out_slist) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_NEAR_LIST_COARSE);   \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_OBJ   (_in_slist);            \
   ODB_PARAM_SET_I     (_dist);                \
   ODB_PARAM_SET_OBJP  (_out_slist);           \
   ODB_CALL; }

#define ODB_SHAPE_NEAR_OUTLINE_LAYER(_shape, _ld, _dist, _net, \
				     _out_slist) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_NEAR_OUTLINE_LAYER);   \
   ODB_PARAM_SET_SHAPE (_shape);                \
   ODB_PARAM_SET_OBJ(_ld);                      \
   ODB_PARAM_SET_I (_dist);                     \
   ODB_PARAM_SET_I (_net);                      \
   ODB_PARAM_SET_OBJP(_out_slist);              \
   ODB_CALL; }

#define ODB_SHAPE_GET_TOUCHING(_shape, _ld, _mode, _tch_list) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_GET_TOUCHING); \
   ODB_PARAM_SET_SHAPE (_shape);                \
   ODB_PARAM_SET_OBJ(_ld);                      \
   ODB_PARAM_SET_I (_mode);                     \
   ODB_PARAM_SET_OBJP(_tch_list);               \
   ODB_CALL; }

#define ODB_SHAPE_PAR_DIST(_seg, _dist, _point, _new_line) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_PAR_DIST);    \
   ODB_PARAM_SET_SHAPE (_seg);                 \
   ODB_PARAM_SET_I (_dist);                    \
   ODB_PARAM_SET_SHAPE (_point);               \
   ODB_PARAM_SET_SHAPE (_new_line);            \
   ODB_CALL; }

#define ODB_SHAPE_POINTS_TO_SEG(_points_list, _axis_seg, _keep_min_seg, _seg) \
{   ODB_PARAMS_INIT(ODB_ACT_SHAPE_POINTS_TO_SEG);		\
    ODB_PARAM_SET_OBJ   (_points_list);				\
    ODB_PARAM_SET_SHAPE (_axis_seg);				\
    ODB_PARAM_SET_I	(_keep_min_seg);			\
    ODB_PARAM_SET_SHAPE (_seg);					\
    ODB_CALL; }

#define ODB_SHAPE_POLYS2CONT(_list1, _list2)    \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_POLYS2CONT);   \
   ODB_PARAM_SET_OBJ   (_list1);                \
   ODB_PARAM_SET_OBJP  (_list2);                \
   ODB_CALL; }


#define ODB_SHAPE_RESIZE(_shape, _enlarge, ok_p) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_RESIZE);        \
   ODB_PARAM_SET_SHAPE (_shape);                 \
   ODB_PARAM_SET_I (_enlarge);                   \
   ODB_PARAM_SET_IP (ok_p);                      \
   ODB_CALL; }

#define ODB_SHAPE_RESIZE_CONT(_shape, _enlarge, _mode, ok_p)    \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_RESIZE_CONT);                  \
   ODB_PARAM_SET_SHAPE (_shape);                                \
   ODB_PARAM_SET_I (_enlarge);                                  \
   ODB_PARAM_SET_I (_mode);                                     \
   ODB_PARAM_SET_IP (ok_p);                                     \
   ODB_CALL; }

#define ODB_SHAPE_RESIZE_CONT_2LIST(_shape, _enlarge, _mode, _out_list, ok_p) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_RESIZE_CONT_2LIST);            \
   ODB_PARAM_SET_SHAPE (_shape);                                \
   ODB_PARAM_SET_I (_enlarge);                                  \
   ODB_PARAM_SET_I (_mode);                                     \
   ODB_PARAM_SET_OBJP (_out_list);                              \
   ODB_PARAM_SET_IP (ok_p);                                     \
   ODB_CALL; }

#define ODB_SHAPE_RESIZE_IDENTICAL(_shape, _enlarge, ok_p) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_RESIZE_IDENTICAL);        \
   ODB_PARAM_SET_SHAPE (_shape);                           \
   ODB_PARAM_SET_I (_enlarge);                             \
   ODB_PARAM_SET_IP (ok_p);                                \
   ODB_CALL; }

#define ODB_SHAPE_IS_CONVEX(_shape, _is_convex_p, ok_p) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_IS_CONVEX);            \
   ODB_PARAM_SET_SHAPE (_shape);                        \
   ODB_PARAM_SET_IP    (_is_convex_p);                  \
   ODB_PARAM_SET_IP    (ok_p);                          \
   ODB_CALL; }

#define ODB_SHAPE_SIN(_shape1, _shape2, sin_p, cos_p, ok_p) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_SIN);            \
   ODB_PARAM_SET_SHAPE (_shape1);                 \
   ODB_PARAM_SET_SHAPE (_shape2);                 \
   ODB_PARAM_SET_DP (sin_p);                      \
   ODB_PARAM_SET_DP (cos_p);                      \
   ODB_PARAM_SET_IP (ok_p);                       \
   ODB_CALL; }

#define ODB_SHAPE_SIZE_LINE(_shape, _ld, _min_len, _max_width, \
                            _len2width_ratio, _line_list, _min_width, \
                            _len_at_min_width, _ind) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_SIZE_LINE);   \
   ODB_PARAM_SET_SHAPE(_shape);                \
   ODB_PARAM_SET_OBJ  (_ld);                   \
   ODB_PARAM_SET_I    (_min_len);              \
   ODB_PARAM_SET_I    (_max_width);            \
   ODB_PARAM_SET_D    (_len2width_ratio);      \
   ODB_PARAM_SET_OBJP (_line_list);            \
   ODB_PARAM_SET_IP   (_min_width);            \
   ODB_PARAM_SET_IP   (_len_at_min_width);     \
   ODB_PARAM_SET_IP   (_ind);                  \
   ODB_CALL; }

#define ODB_SHAPE_SIZE_LINE_LIST(_shape, _lsd, _min_len, _max_width, \
                                 _len2width_ratio, _line_list, _min_width, \
                                 _len_at_min_width, _ind) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_SIZE_LINE_LIST);   \
   ODB_PARAM_SET_SHAPE(_shape);                \
   ODB_PARAM_SET_OBJ  (_lsd);                   \
   ODB_PARAM_SET_I    (_min_len);              \
   ODB_PARAM_SET_I    (_max_width);            \
   ODB_PARAM_SET_D    (_len2width_ratio);      \
   ODB_PARAM_SET_OBJP (_line_list);            \
   ODB_PARAM_SET_IP   (_min_width);            \
   ODB_PARAM_SET_IP   (_len_at_min_width);     \
   ODB_PARAM_SET_IP   (_ind);                  \
   ODB_CALL; }

#define ODB_SHAPE_SIZE_PAD(_shape, _rect, _ind)\
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_SIZE_PAD);    \
   ODB_PARAM_SET_SHAPE(_shape);                \
   ODB_PARAM_SET_SHAPE(_rect);                 \
   ODB_PARAM_SET_IP   (_ind);                  \
   ODB_CALL; }

#define ODB_SHAPE_SMOOTH_LIST(_in_list, _tol, _out_list, _success) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_SMOOTH_LIST);                     \
   ODB_PARAM_SET_OBJ               (_in_list);                     \
   ODB_PARAM_SET_I                     (_tol);                     \
   ODB_PARAM_SET_OBJP             (_out_list);                     \
   ODB_PARAM_SET_IP                (_success);                     \
   ODB_CALL; }

#define ODB_SHAPE_SIMPLIFY_AND_SMOOTH_LIST(_in_list,               \
                                           _tsx, _tsy, _ts_valid,  \
                                           _tex, _tey, _te_valid,  \
                                           _tol, _out_list)        \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_SIMPLIFY_AND_SMOOTH_LIST);        \
   ODB_PARAM_SET_OBJ               (_in_list);                     \
   ODB_PARAM_SET_D                     (_tsx);                     \
   ODB_PARAM_SET_D                     (_tsy);                     \
   ODB_PARAM_SET_I                (_ts_valid);                     \
   ODB_PARAM_SET_D                     (_tex);                     \
   ODB_PARAM_SET_D                     (_tey);                     \
   ODB_PARAM_SET_I                (_te_valid);                     \
   ODB_PARAM_SET_I                     (_tol);                     \
   ODB_PARAM_SET_OBJP             (_out_list);                     \
   ODB_CALL; }

#define ODB_SHAPE_SLIVER(_in_list, _dist,                               \
                         _dist2peri, _mode, _diff_net_mode,             \
			 _min_len, _max_len, _overlap,                  \
                         _check_aa, _max_aa, _check_by_limits,          \
			 _report_all_slivers, _out_list, _out_val_list, \
			 _out_local_list, _out_local_val_list )         \
{                                                                       \
    ODB_PARAMS_INIT(ODB_ACT_SHAPE_SLIVER);                              \
    ODB_PARAM_SET_OBJ(_in_list);                                        \
    ODB_PARAM_SET_I(_dist);                                             \
    ODB_PARAM_SET_D(_dist2peri);                                        \
    ODB_PARAM_SET_I(_mode);                                             \
    ODB_PARAM_SET_I(_diff_net_mode);                                    \
    ODB_PARAM_SET_I(_min_len);                                          \
    ODB_PARAM_SET_I(_max_len);                                          \
    ODB_PARAM_SET_I(_overlap);                                          \
    ODB_PARAM_SET_I(_check_aa );                                        \
    ODB_PARAM_SET_D(_max_aa );                                          \
    ODB_PARAM_SET_I(_check_by_limits );                                 \
    ODB_PARAM_SET_I(_report_all_slivers );                              \
    ODB_PARAM_SET_OBJP(_out_list);                                      \
    ODB_PARAM_SET_OBJP(_out_val_list);                                  \
    ODB_PARAM_SET_OBJP(_out_local_list);                                \
    ODB_PARAM_SET_OBJP(_out_local_val_list);                            \
    ODB_CALL; }

#define ODB_SHAPE_SORT_RECTS(_sld, _max_smd, _pitch_sld, _packages_sld) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_SORT_RECTS);  \
   ODB_PARAM_SET_OBJ(_sld);                    \
   ODB_PARAM_SET_I  (_max_smd);                \
   ODB_PARAM_SET_OBJP (_pitch_sld);            \
   ODB_PARAM_SET_OBJP (_packages_sld);         \
   ODB_CALL; }

#define ODB_SHAPE_SORT_RECTS_2(_sld, _max_smd, _pitch_sld, _packages_sld, _rows_sld) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_SORT_RECTS_2);  \
   ODB_PARAM_SET_OBJ(_sld);                    \
   ODB_PARAM_SET_I  (_max_smd);                \
   ODB_PARAM_SET_OBJP (_pitch_sld);            \
   ODB_PARAM_SET_OBJP (_packages_sld);         \
   ODB_PARAM_SET_OBJP (_rows_sld);         \
   ODB_CALL; }
#define ODB_SHAPE_SORT_RECTS_3(_sld, _max_smd, _pitch_tol, _search, _pitch_sld, _packages_sld, _rows_sld) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_SORT_RECTS_3);  \
   ODB_PARAM_SET_OBJ(_sld);                    \
   ODB_PARAM_SET_I  (_max_smd);                \
   ODB_PARAM_SET_I  (_pitch_tol);                \
   ODB_PARAM_SET_I  (_search);                \
   ODB_PARAM_SET_OBJP (_pitch_sld);            \
   ODB_PARAM_SET_OBJP (_packages_sld);         \
   ODB_PARAM_SET_OBJP (_rows_sld);         \
   ODB_CALL; }

#define ODB_SHAPE_SKELETON(_in_shape, _out_shape)\
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_SKELETON);      \
   ODB_PARAM_SET_SHAPE (_in_shape);              \
   ODB_PARAM_SET_SHAPE (_out_shape);             \
   ODB_CALL; }

#define ODB_SHAPE_TANGENT(_point1, _point2, _out_point1, _out_point2) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_TANGENT);       \
   ODB_PARAM_SET_SHAPE (_point1);                \
   ODB_PARAM_SET_SHAPE (_point2);                \
   ODB_PARAM_SET_SHAPE (_out_point1);            \
   ODB_PARAM_SET_SHAPE (_out_point2);            \
   ODB_CALL; }

#define ODB_SHAPE_CALC_TANGENT_SHAPES(_shape1, _shape2, _type, _tangent_shapes_list)	\
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_CALC_TANGENT_SHAPES);				\
 ODB_PARAM_SET_SHAPE (_shape1);							\
 ODB_PARAM_SET_SHAPE (_shape2);							\
 ODB_PARAM_SET_I(_type);							\
 ODB_PARAM_SET_OBJP (_tangent_shapes_list);					\
 ODB_CALL; }

#define ODB_SHAPE_GET_CONT_ENCLOSE_CIRCLE(_shape1, _shape2 , _step_size , _is_ok)	\
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_GET_CONT_ENCLOSE_CIRCLE);				\
 ODB_PARAM_SET_SHAPE (_shape1);							\
 ODB_PARAM_SET_SHAPE (_shape2);							\
 ODB_PARAM_SET_I(_step_size);							\
 ODB_PARAM_SET_IP (_is_ok);					\
 ODB_CALL; }


#define ODB_SHAPE_CREATE_TANGENT_CURVE(_point1, _tangent1_x, _tangent1_y, _point2, _curve_shape, _ok) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_CREATE_TANGENT_CURVE);       \
   ODB_PARAM_SET_SHAPE (_point1);                \
   ODB_PARAM_SET_D(_tangent1_x);                 \
   ODB_PARAM_SET_D(_tangent1_y);                 \
   ODB_PARAM_SET_SHAPE (_point2);                \
   ODB_PARAM_SET_SHAPE (_curve_shape);           \
   ODB_PARAM_SET_IP (_ok);                       \
   ODB_CALL; }

#define ODB_SHAPE_CREATE_TANGENT_CIRCLE(_shape1, _point_on_shape1, _shape2, _max_search, _inner, _circle, _point_on_shape2, _ok) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_CREATE_TANGENT_CIRCLE);  \
   ODB_PARAM_SET_SHAPE (_shape1);                         \
   ODB_PARAM_SET_SHAPE(_point_on_shape1);                 \
   ODB_PARAM_SET_SHAPE(_shape2);                          \
   ODB_PARAM_SET_I(_max_search);                          \
   ODB_PARAM_SET_I(_inner);                               \
   ODB_PARAM_SET_SHAPE (_circle);                         \
   ODB_PARAM_SET_SHAPE (_point_on_shape2);                \
   ODB_PARAM_SET_IP (_ok);                                \
   ODB_CALL; }

#define ODB_SHAPE_TAPER( _shape, _from_end, _bigger_size, _sides,   \
    _shape_res_ld )                                \
 { ODB_PARAMS_INIT( ODB_ACT_SHAPE_TAPER );         \
   ODB_PARAM_SET_SHAPE( _shape );                  \
   ODB_PARAM_SET_I( _from_end )                    \
   ODB_PARAM_SET_I( _bigger_size )                 \
   ODB_PARAM_SET_I( _sides )                       \
   ODB_PARAM_SET_OBJP(_shape_res_ld);              \
   ODB_CALL; }

#define ODB_SHAPE_TOUCH(_shape1, _shape2, _touch) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_TOUCH);       \
   ODB_PARAM_SET_SHAPE (_shape1);              \
   ODB_PARAM_SET_SHAPE (_shape2);              \
   ODB_PARAM_SET_IP (_touch);                  \
   ODB_CALL; }

#define ODB_SHAPE_TOUCH_LIST(_shape, _in_list, _touch) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_TOUCH_LIST);  \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_OBJ   (_in_list);             \
   ODB_PARAM_SET_IP    (_touch);               \
   ODB_CALL; }

#define ODB_SHAPE_TOUCH_LAYER(_shape, _layer, _touch) \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_TOUCH_LAYER); \
   ODB_PARAM_SET_SHAPE (_shape);               \
   ODB_PARAM_SET_OBJ   (_layer);               \
   ODB_PARAM_SET_IP    (_touch);               \
   ODB_CALL; }

#define ODB_SHAPE_LIST2CHULL(_list, _shape)    \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_LIST2CHULL);  \
   ODB_PARAM_SET_OBJ   (_list);              \
   ODB_PARAM_SET_SHAPE (_shape);             \
   ODB_CALL; }

#define ODB_SHAPE_LIST2CONT(_list1, _list2)    \
 { ODB_PARAMS_INIT(ODB_ACT_SHAPE_LIST2CONT);   \
   ODB_PARAM_SET_OBJ   (_list1);              \
   ODB_PARAM_SET_OBJP  (_list2);             \
   ODB_CALL; }

#define ODB_SHAPE_GAPS_LIST(_shape1, _shape2, _max_dist, _seg_list, _dist_list, _rel) \
{  ODB_PARAMS_INIT(ODB_ACT_SHAPE_GAPS_LIST);     \
   ODB_PARAM_SET_SHAPE (_shape1);                \
   ODB_PARAM_SET_SHAPE (_shape2);                \
   ODB_PARAM_SET_I  (_max_dist);                 \
   ODB_PARAM_SET_OBJP(_seg_list);                \
   ODB_PARAM_SET_OBJP(_dist_list);               \
   ODB_PARAM_SET_RELP (_rel);                    \
   ODB_CALL; }

#define ODB_SHAPE_GAPS_LIST_INTERSECT(_shape1, _shape2, _max_dist, _seg_list, _dist_list, _rel) \
{  ODB_PARAMS_INIT(ODB_ACT_SHAPE_GAPS_LIST_INTERSECT); \
   ODB_PARAM_SET_SHAPE (_shape1);                      \
   ODB_PARAM_SET_SHAPE (_shape2);                      \
   ODB_PARAM_SET_I  (_max_dist);                       \
   ODB_PARAM_SET_OBJP(_seg_list);                      \
   ODB_PARAM_SET_OBJP(_dist_list);                     \
   ODB_PARAM_SET_RELP (_rel);                          \
   ODB_CALL; }

#define ODB_SHAPE_EQUAL_SHAPES(_shape1, _shape2, _equal) \
{  ODB_PARAMS_INIT(ODB_ACT_SHAPE_EQUAL_SHAPES);  \
   ODB_PARAM_SET_SHAPE(_shape1);                \
   ODB_PARAM_SET_SHAPE(_shape2);                \
   ODB_PARAM_SET_IP(_equal);                 \
   ODB_CALL;  }

#define ODB_SHAPE_LINE_TRANSFORM(_shape, _neighbor_shape, _enlarge,                       \
                                 _transformed_shape, _shrunk_to_zero,                     \
                                 _transformed_neighbor_shape, _neighbor_shrunk_to_zero,   \
                                 _act_enlarge)                                            \
{  ODB_PARAMS_INIT(ODB_ACT_SHAPE_LINE_TRANSFORM);      \
   ODB_PARAM_SET_SHAPE (_shape);                       \
   ODB_PARAM_SET_SHAPE (_neighbor_shape);              \
   ODB_PARAM_SET_I  (_enlarge);                        \
   ODB_PARAM_SET_SHAPE (_transformed_shape);           \
   ODB_PARAM_SET_IP  (_shrunk_to_zero);                \
   ODB_PARAM_SET_SHAPE (_transformed_neighbor_shape);  \
   ODB_PARAM_SET_IP  (_neighbor_shrunk_to_zero);       \
   ODB_PARAM_SET_IP  (_act_enlarge);                   \
   ODB_CALL; }

#define ODB_SYMBOL_CREATE(_name, _sym_num)       \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_CREATE);       \
   ODB_PARAM_SET_S (_name);                      \
   ODB_PARAM_SET_SYM_P(_sym_num);              \
   ODB_CALL; }

#define ODB_SYMBOL_GET(_name, _sym_num, _exists) \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_GET);          \
   ODB_PARAM_SET_S (_name);                      \
   ODB_PARAM_SET_SYM_P(_sym_num);              \
   ODB_PARAM_SET_IP(_exists);                    \
   ODB_CALL; }

#define ODB_SYMBOL_F_ADD(_sym_num, _f)           \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_F_ADD);        \
   ODB_PARAM_SET_SYM(_sym_num);               \
   ODB_PARAM_SET_F(_f);                          \
   ODB_CALL; }

#define ODB_SYMBOL_GET_NAME(_sym_num, _name)     \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_GET_NAME);     \
   ODB_PARAM_SET_SYM (_sym_num);              \
   ODB_PARAM_SET_S (_name);                      \
   ODB_CALL; }

#define ODB_SYMBOL_GET_NAME_NEW(_sym_num, _sym_type, _name) \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_GET_NAME_NEW);    \
   ODB_PARAM_SET_SYM (_sym_num);		    \
   ODB_PARAM_SET_I (_sym_type);			    \
   ODB_PARAM_SET_S (_name);			    \
   ODB_CALL; }

#define ODB_SYMBOL_CHANGE_SHAPE(_old_sym_num, _new_sym_name, _new_sym_num, _sym_type) \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_CHANGE_SHAPE); \
   ODB_PARAM_SET_SYM (_old_sym_num);  \
   ODB_PARAM_SET_S (_new_sym_name);	 \
   ODB_PARAM_SET_SYM_P(_new_sym_num);  \
   ODB_PARAM_SET_IP(_sym_type);		 \
   ODB_CALL; }

#define ODB_SYMBOL_CHANGE_SHAPE_2(_old_sym_num, _old_sym_type, _new_sym_name, _new_sym_num, _sym_type) \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_CHANGE_SHAPE_2); \
   ODB_PARAM_SET_SYM (_old_sym_num);  \
   ODB_PARAM_SET_I (_old_sym_type);	 \
   ODB_PARAM_SET_S (_new_sym_name);	 \
   ODB_PARAM_SET_SYM_P(_new_sym_num);  \
   ODB_PARAM_SET_IP(_sym_type);		 \
   ODB_CALL; }

#define ODB_SYMBOL_GET_RECT_SIZES(_sym_num, _sym_type, _w, _h, _r, _ok)\
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_GET_RECT_SIZES);                     \
   ODB_PARAM_SET_SYM (_sym_num);                                    \
   ODB_PARAM_SET_I (_sym_type);                                        \
   ODB_PARAM_SET_IP(_w);                                               \
   ODB_PARAM_SET_IP(_h);                                               \
   ODB_PARAM_SET_IP(_r);                                               \
   ODB_PARAM_SET_IP(_ok);                                              \
   ODB_CALL; }

#define ODB_SYMBOL_GET_W_H(_sym_num, _w, _h, _ok) \
 { ODB_PARAMS_INIT (ODB_ACT_SYMBOL_GET_W_H);      \
   ODB_PARAM_SET_SYM (_sym_num);               \
   ODB_PARAM_SET_IP(_w);                          \
   ODB_PARAM_SET_IP(_h);                          \
   ODB_PARAM_SET_IP(_ok);                         \
   ODB_CALL; }

#define ODB_SYMBOL_GET_W_H_2(_sym_num, _sym_type, _w, _h, _ok) \
 { ODB_PARAMS_INIT (ODB_ACT_SYMBOL_GET_W_H_2);  \
   ODB_PARAM_SET_SYM (_sym_num);               \
   ODB_PARAM_SET_I (_sym_type);                   \
   ODB_PARAM_SET_IP(_w);                          \
   ODB_PARAM_SET_IP(_h);                          \
   ODB_PARAM_SET_IP(_ok);                         \
   ODB_CALL; }

#define ODB_SYMBOL_GET_SMD_PARAMS(_sym_num, _sym_type, _w,             \
                                  _h, _r, _corner, _type, _ok)         \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_GET_SMD_PARAMS);                     \
   ODB_PARAM_SET_SYM (_sym_num);                                    \
   ODB_PARAM_SET_I (_sym_type);                                        \
   ODB_PARAM_SET_IP(_w);                                               \
   ODB_PARAM_SET_IP(_h);                                               \
   ODB_PARAM_SET_IP(_r);                                               \
   ODB_PARAM_SET_IP(_corner);                                          \
   ODB_PARAM_SET_IP(_type);                                            \
   ODB_PARAM_SET_IP(_ok);                                              \
   ODB_CALL; }

#define ODB_SYMBOL_GET_SMD_PARAMS_ROT(_sym_num, _sym_type, _w,         \
                                  _h, _r, _corner, _type, _rot, _ok)   \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_GET_SMD_PARAMS_ROT);                 \
   ODB_PARAM_SET_SYM (_sym_num);                                    \
   ODB_PARAM_SET_I (_sym_type);                                        \
   ODB_PARAM_SET_IP(_w);                                               \
   ODB_PARAM_SET_IP(_h);                                               \
   ODB_PARAM_SET_IP(_r);                                               \
   ODB_PARAM_SET_IP(_corner);                                          \
   ODB_PARAM_SET_IP(_type);                                            \
   ODB_PARAM_SET_DP(_rot);                                             \
   ODB_PARAM_SET_IP(_ok);                                              \
   ODB_CALL; }

#define ODB_SYMBOL_GET_CROSS_TSHAPE_PARAMS(_sym_num, _sym_type,         \
                                           _hor_length, _hor_width,     \
                                           _ver_length, _ver_width,     \
					   _hor_point, _ver_point,      \
					   _r, _style, _type, _ok)      \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_GET_CROSS_TSHAPE_PARAMS);	        \
 ODB_PARAM_SET_SYM (_sym_num);					        \
 ODB_PARAM_SET_I (_sym_type);					        \
 ODB_PARAM_SET_IP(_hor_length);					        \
 ODB_PARAM_SET_IP(_hor_width);					        \
 ODB_PARAM_SET_IP(_ver_length);						\
 ODB_PARAM_SET_IP(_ver_width);						\
 ODB_PARAM_SET_IP(_hor_point);						\
 ODB_PARAM_SET_IP(_ver_point);						\
 ODB_PARAM_SET_IP(_r);							\
 ODB_PARAM_SET_IP(_style);						\
 ODB_PARAM_SET_IP(_type);						\
 ODB_PARAM_SET_IP(_ok);							\
 ODB_CALL; }


#define ODB_SYMBOL_GET_THERMAL_PARAM(_sym_num, _sym_type, _pcx, _pcy,  \
                                     _in_shape, _out_shape, _gap, _act_gap, \
                                     _n_spoke, _style, _angle, _ok)    \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_GET_THERMAL_PARAM);                  \
   ODB_PARAM_SET_SYM (_sym_num);                                    \
   ODB_PARAM_SET_I (_sym_type);                                        \
   ODB_PARAM_SET_I (_pcx);                                             \
   ODB_PARAM_SET_I (_pcy);                                             \
   ODB_PARAM_SET_SHAPE (_in_shape);                                    \
   ODB_PARAM_SET_SHAPE (_out_shape);                                   \
   ODB_PARAM_SET_IP(_gap);                                             \
   ODB_PARAM_SET_IP(_act_gap);                                         \
   ODB_PARAM_SET_IP(_n_spoke);                                         \
   ODB_PARAM_SET_IP(_style);                                           \
   ODB_PARAM_SET_IP(_angle);                                           \
   ODB_PARAM_SET_IP(_ok);                                              \
   ODB_CALL; }

#define ODB_SYMBOL_GET_NEW_THERMAL_PARAM(_sym_num, _sym_type, _pcx, _pcy,  \
                                         _in_shape, _out_shape, _gap, _act_gap, \
                                         _n_spoke, _style, _angle, _thermal_type, \
					 _outer_width, _outer_height, _air_gap, \
					 _corners, _corner_radius, _ok)    \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_GET_NEW_THERMAL_PARAM);                  \
   ODB_PARAM_SET_SYM (_sym_num);                                    \
   ODB_PARAM_SET_I (_sym_type);                                        \
   ODB_PARAM_SET_I (_pcx);                                             \
   ODB_PARAM_SET_I (_pcy);                                             \
   ODB_PARAM_SET_SHAPE (_in_shape);                                    \
   ODB_PARAM_SET_SHAPE (_out_shape);                                   \
   ODB_PARAM_SET_IP(_gap);                                             \
   ODB_PARAM_SET_IP(_act_gap);                                         \
   ODB_PARAM_SET_IP(_n_spoke);                                         \
   ODB_PARAM_SET_IP(_style);                                           \
   ODB_PARAM_SET_IP(_angle);                                           \
   ODB_PARAM_SET_IP(_thermal_type);                                    \
   ODB_PARAM_SET_IP(_outer_width);                                     \
   ODB_PARAM_SET_IP(_outer_height);                                    \
   ODB_PARAM_SET_IP(_air_gap);                                         \
   ODB_PARAM_SET_IP(_corners);                                         \
   ODB_PARAM_SET_IP(_corner_radius);                                   \
   ODB_PARAM_SET_IP(_ok);                                              \
   ODB_CALL; }

#define ODB_SYMBOL_GET_DONUT_PARAMS(_sym_num, _sym_type,                \
				    _cap_type, _i_size, _o_size, _is_ok) \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_GET_DONUT_PARAMS); \
   ODB_PARAM_SET_SYM (_sym_num);                  \
   ODB_PARAM_SET_I (_sym_type);                      \
   ODB_PARAM_SET_IP(_cap_type);                      \
   ODB_PARAM_SET_IP(_i_size);                        \
   ODB_PARAM_SET_IP(_o_size);                        \
   ODB_PARAM_SET_IP(_is_ok);                         \
   ODB_CALL; }

#define ODB_SYMBOL_GET_NEW_DONUT_PARAMS(_sym_num, _sym_type, _pcx, _pcy,         \
					_inner_shape, _outer_shape, _donut_type, \
					_outer_width, _outer_height, _air_gap,   \
					_corners, _corner_radius, _is_ok) \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_GET_NEW_DONUT_PARAMS); \
   ODB_PARAM_SET_SYM (_sym_num);                  \
   ODB_PARAM_SET_I (_sym_type);                      \
   ODB_PARAM_SET_I (_pcx);	                     \
   ODB_PARAM_SET_I (_pcy);			     \
   ODB_PARAM_SET_SHAPE (_inner_shape);               \
   ODB_PARAM_SET_SHAPE (_outer_shape);               \
   ODB_PARAM_SET_IP(_donut_type);                    \
   ODB_PARAM_SET_IP(_outer_width);                   \
   ODB_PARAM_SET_IP(_outer_height);                  \
   ODB_PARAM_SET_IP(_air_gap);                       \
   ODB_PARAM_SET_IP(_corners);                       \
   ODB_PARAM_SET_IP(_corner_radius);                 \
   ODB_PARAM_SET_IP(_is_ok);                         \
   ODB_CALL; }

#define ODB_SYMBOL_FILL(_sym_num,				       \
			_sym_type,				       \
			_min_brush,				       \
			_max_brush, 				       \
			_fld,					       \
			_ok_p)			   		       \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_FILL);    	                       \
   ODB_PARAM_SET_SYM (_sym_num);            	                       \
   ODB_PARAM_SET_I (_sym_type);                                        \
   ODB_PARAM_SET_I (_min_brush);                                       \
   ODB_PARAM_SET_I (_max_brush);                                       \
   ODB_PARAM_SET_OBJP(_fld);                                           \
   ODB_PARAM_SET_IP(_ok_p);                                            \
   ODB_CALL; }

#define ODB_SYMBOL_VALIDATE(_sym_num,				       \
			    _sym_type,				       \
                            _size ,                                    \
                            _mode ,                                    \
                            _fold ,                                    \
                            _edge_len ,                                \
                            _types ,                                   \
                            _shapes ,                                  \
			    _values)                                   \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_VALIDATE);  	                       \
   ODB_PARAM_SET_SYM (_sym_num);            	                       \
   ODB_PARAM_SET_I (_sym_type);                                        \
   ODB_PARAM_SET_I (_size);                                            \
   ODB_PARAM_SET_I (_mode);                                            \
   ODB_PARAM_SET_I (_fold);                                            \
   ODB_PARAM_SET_I (_edge_len);                                        \
   ODB_PARAM_SET_OBJP(_types);                                         \
   ODB_PARAM_SET_OBJP(_shapes);                                        \
   ODB_PARAM_SET_OBJP(_values);                                        \
   ODB_CALL; }

#define ODB_SYMBOL_BUILD_RECT(_rect_type, _w, _h, _r, _ok, _sym_num)   \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_BUILD_RECT);                     \
   ODB_PARAM_SET_I (_rect_type);                                       \
   ODB_PARAM_SET_I (_w);                                               \
   ODB_PARAM_SET_I (_h);                                               \
   ODB_PARAM_SET_I (_r);                                               \
   ODB_PARAM_SET_IP(_ok);                                              \
   ODB_PARAM_SET_SYM_P(_sym_num);                                    \
   ODB_CALL; }

#define ODB_SYMBOL_BUILD_CROSS_TSHAPE(	_smd_type, _hor_length, _ver_length,\
					_hor_width, _ver_width,             \
					_hor_point, _ver_point,             \
					_r, _style,                         \
					_rot, _ok, _sym_num)		    \
{ ODB_PARAMS_INIT(ODB_ACT_SYMBOL_BUILD_CROSS_TSHAPE);                       \
 ODB_PARAM_SET_I (_smd_type);						    \
 ODB_PARAM_SET_I (_hor_length);                                             \
 ODB_PARAM_SET_I (_ver_length);                                             \
 ODB_PARAM_SET_I (_hor_width);                                              \
 ODB_PARAM_SET_I (_ver_width);                                              \
 ODB_PARAM_SET_I (_hor_point);                                              \
 ODB_PARAM_SET_I (_ver_point);                                              \
 ODB_PARAM_SET_I (_r);							    \
 ODB_PARAM_SET_I (_style);						    \
 ODB_PARAM_SET_D (_rot);						    \
 ODB_PARAM_SET_IP(_ok);							    \
 ODB_PARAM_SET_SYM_P(_sym_num);						    \
 ODB_CALL; }


#define ODB_SYMBOL_BUILD_SMD(_smd_type, _w, _h, _r, _corner, _ok, _sym_num)\
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_BUILD_SMD);                          \
   ODB_PARAM_SET_I (_smd_type);                                       \
   ODB_PARAM_SET_I (_w);                                               \
   ODB_PARAM_SET_I (_h);                                               \
   ODB_PARAM_SET_I (_r);                                               \
   ODB_PARAM_SET_I (_corner);                                          \
   ODB_PARAM_SET_IP(_ok);                                              \
   ODB_PARAM_SET_SYM_P(_sym_num);                                    \
   ODB_CALL; }

#define ODB_SYMBOL_BUILD_SMD_ROT(_smd_type, _w, _h, _r, _corner,        \
 				 _rot,_ok, _sym_num)                    \
 { ODB_PARAMS_INIT(ODB_ACT_SYMBOL_BUILD_SMD_ROT);                       \
   ODB_PARAM_SET_I (_smd_type);                                         \
   ODB_PARAM_SET_I (_w);                                                \
   ODB_PARAM_SET_I (_h);                                                \
   ODB_PARAM_SET_I (_r);                                                \
   ODB_PARAM_SET_I (_corner);                                           \
   ODB_PARAM_SET_D (_rot);                                              \
   ODB_PARAM_SET_IP(_ok);                                               \
   ODB_PARAM_SET_SYM_P(_sym_num);                                     \
   ODB_CALL; }

#define ODB_SYMBOL_BUILD_THERMAL(_thermal_type, _osize, _isize, _angle,             \
				 _num_sproks, _spoke_gap, _style, _is_ok, _sym_num) \
 { ODB_PARAMS_INIT (ODB_ACT_SYMBOL_BUILD_THERMAL);                                  \
   ODB_PARAM_SET_I (_thermal_type); \
   ODB_PARAM_SET_I (_osize);        \
   ODB_PARAM_SET_I (_isize);        \
   ODB_PARAM_SET_I (_angle);        \
   ODB_PARAM_SET_I (_num_sproks);   \
   ODB_PARAM_SET_I (_spoke_gap);    \
   ODB_PARAM_SET_I (_style);        \
   ODB_PARAM_SET_IP(_is_ok);        \
   ODB_PARAM_SET_SYM_P(_sym_num); \
   ODB_CALL; }

#define ODB_SYMBOL_BUILD_NEW_THERMAL(_thermal_type, _osize, _isize, _angle,             \
				     _num_sproks, _spoke_gap, _style, _corners, _corner_radius,\
				     _air_gap, _is_ok, _sym_num) \
 { ODB_PARAMS_INIT (ODB_ACT_SYMBOL_BUILD_NEW_THERMAL);                                  \
   ODB_PARAM_SET_I (_thermal_type); \
   ODB_PARAM_SET_I (_osize);        \
   ODB_PARAM_SET_I (_isize);        \
   ODB_PARAM_SET_I (_angle);        \
   ODB_PARAM_SET_I (_num_sproks);   \
   ODB_PARAM_SET_I (_spoke_gap);    \
   ODB_PARAM_SET_I (_style);        \
   ODB_PARAM_SET_I (_corners);      \
   ODB_PARAM_SET_I (_corner_radius); \
   ODB_PARAM_SET_I (_air_gap);      \
   ODB_PARAM_SET_IP(_is_ok);        \
   ODB_PARAM_SET_SYM_P(_sym_num); \
   ODB_CALL; }

#define ODB_SYMBOL_BUILD_DONUT(_cap_type, _i_size, _o_size, _is_ok, _sym_num) \
 { ODB_PARAMS_INIT (ODB_ACT_SYMBOL_BUILD_DONUT); \
   ODB_PARAM_SET_I (_cap_type);     \
   ODB_PARAM_SET_I (_i_size);       \
   ODB_PARAM_SET_I (_o_size);       \
   ODB_PARAM_SET_IP(_is_ok);        \
   ODB_PARAM_SET_SYM_P(_sym_num); \
   ODB_CALL; }

#define ODB_SYMBOL_BUILD_NEW_DONUT(_cap_type, _i_size, _o_size, _corners, _corner_radius, _air_gap, _is_ok, _sym_num) \
 { ODB_PARAMS_INIT (ODB_ACT_SYMBOL_BUILD_NEW_DONUT); \
   ODB_PARAM_SET_I (_cap_type);     \
   ODB_PARAM_SET_I (_i_size);       \
   ODB_PARAM_SET_I (_o_size);       \
   ODB_PARAM_SET_I (_corners);      \
   ODB_PARAM_SET_I (_corner_radius); \
   ODB_PARAM_SET_I (_air_gap);      \
   ODB_PARAM_SET_IP(_is_ok);        \
   ODB_PARAM_SET_SYM_P(_sym_num); \
   ODB_CALL; }

#define ODB_UTILS_BELL(_num)                     \
 { ODB_PARAMS_INIT(ODB_ACT_UTILS_BELL);          \
   ODB_PARAM_SET_I(_num); 	                 \
   ODB_CALL; }

#define ODB_UTILS_CMP_W(_name, _pattern, _match) \
 { ODB_PARAMS_INIT(ODB_ACT_UTILS_CMP_W);        \
   ODB_PARAM_SET_S (_name);                     \
   ODB_PARAM_SET_S (_pattern);                  \
   ODB_PARAM_SET_IP(_match);                    \
   ODB_CALL; }

#define ODB_UTILS_UNITS(_units)                  \
 { ODB_PARAMS_INIT(ODB_ACT_UTILS_UNITS);         \
   ODB_PARAM_SET_IP(_units); 	                 \
   ODB_CALL; }

#define ODB_UTILS_INDEX_CREATE(_index)               \
    { ODB_PARAMS_INIT(ODB_ACT_UTILS_INDEX_CREATE);   \
      ODB_PARAM_SET_IP(_index);                      \
      ODB_CALL; }

#define ODB_UTILS_INDEX_DESTROY(_index)              \
    { ODB_PARAMS_INIT(ODB_ACT_UTILS_INDEX_DESTROY);  \
      ODB_PARAM_SET_I(_index);                       \
      ODB_CALL; }

#define ODB_UTILS_INDEX_INSERT(_index, _shape, _id)  \
    { ODB_PARAMS_INIT(ODB_ACT_UTILS_INDEX_INSERT);   \
      ODB_PARAM_SET_I(_index);                       \
      ODB_PARAM_SET_SHAPE(_shape);                   \
      ODB_PARAM_SET_I(_id);                          \
      ODB_CALL; }
     
#define ODB_UTILS_INDEX_REMOVE(_index, _shape, _id)  \
    { ODB_PARAMS_INIT(ODB_ACT_UTILS_INDEX_REMOVE);   \
      ODB_PARAM_SET_I(_index);                       \
      ODB_PARAM_SET_SHAPE(_shape);                   \
      ODB_PARAM_SET_I(_id);                          \
      ODB_CALL; }

#define ODB_UTILS_INDEX_UPDATE(_index, _shape, _id, _new_shape)   \
    { ODB_PARAMS_INIT(ODB_ACT_UTILS_INDEX_UPDATE);                \
      ODB_PARAM_SET_I(_index);                                    \
      ODB_PARAM_SET_SHAPE(_shape);                                \
      ODB_PARAM_SET_I(_id);                                       \
      ODB_PARAM_SET_SHAPE(_new_shape);                            \
      ODB_CALL; }

#define ODB_UTILS_INDEX_SEARCH(_index, _shape, _ind_list)   \
    { ODB_PARAMS_INIT(ODB_ACT_UTILS_INDEX_SEARCH);              \
      ODB_PARAM_SET_I(_index);                                  \
      ODB_PARAM_SET_SHAPE(_shape);                              \
      ODB_PARAM_SET_OBJP(_ind_list);                            \
      ODB_CALL; }

#define ODB_UTILS_SORT_TCREATE(_name, _size, _sensitive, _td) \
 { ODB_PARAMS_INIT(ODB_ACT_UTILS_SORT_TCREATE); \
   ODB_PARAM_SET_S (_name);                     \
   ODB_PARAM_SET_I (_size);                     \
   ODB_PARAM_SET_I (_sensitive);                \
   ODB_PARAM_SET_IP(_td);                       \
   ODB_CALL; }

#define ODB_UTILS_SORT_TDESTROY(_td) \
 { ODB_PARAMS_INIT(ODB_ACT_UTILS_SORT_TDESTROY); \
   ODB_PARAM_SET_I (_td);                        \
   ODB_CALL; }

#define ODB_UTILS_SORT_TADD(_td, _str, _value) \
 { ODB_PARAMS_INIT(ODB_ACT_UTILS_SORT_TADD); \
   ODB_PARAM_SET_I (_td);                        \
   ODB_PARAM_SET_S (_str);                       \
   ODB_PARAM_SET_I (_value);                     \
   ODB_CALL; }

#define ODB_UTILS_SORT_TFIND(_td, _str, _value, _found) \
 { ODB_PARAMS_INIT(ODB_ACT_UTILS_SORT_TFIND); \
   ODB_PARAM_SET_I (_td);                        \
   ODB_PARAM_SET_S (_str);                       \
   ODB_PARAM_SET_IP(_value);                     \
   ODB_PARAM_SET_IP(_found);                     \
   ODB_CALL; }

#define ODB_UTILS_GET_RESOURCE(_name, _value) {	\
  ODB_PARAMS_INIT(ODB_ACT_UTILS_GET_RESOURCE);	\
  ODB_PARAM_SET_S(_name);			\
  ODB_PARAM_SET_S(_value);			\
  ODB_PARAM_SET_I(sizeof(_value));		\
  ODB_CALL;					\
}

#define ODB_UTILS_GET_CFG(_name, _value, _exists) {	\
  ODB_PARAMS_INIT(ODB_ACT_UTILS_GET_CFG);	\
  ODB_PARAM_SET_S(_name);			\
  ODB_PARAM_SET_VOID(_value);			\
  ODB_PARAM_SET_IP(_exists);                    \
  ODB_CALL;					\
}

#define ODB_UTILS_GET_CONT_OP_ACCURACY(_acc) {	        \
  ODB_PARAMS_INIT(ODB_ACT_UTILS_GET_CONT_OP_ACCURACY);  \
  ODB_PARAM_SET_IP(_acc);			        \
  ODB_CALL;					        \
}

#define ODB_UTILS_SET_CONT_OP_ACCURACY(_acc) {	        \
  ODB_PARAMS_INIT(ODB_ACT_UTILS_SET_CONT_OP_ACCURACY);  \
  ODB_PARAM_SET_I(_acc);			        \
  ODB_CALL;					        \
}

#define ODB_UTILS_IS_FLEX(_is_flex)           \
 { ODB_PARAMS_INIT(ODB_ACT_UTILS_IS_FLEX);    \
 ODB_PARAM_SET_IP(_is_flex);                  \
 ODB_CALL; }


#define ODB_STEP_GET_PCB_COUNT( _layer_sr, _pcb_count ) {\
    ODB_PARAMS_INIT( ODB_ACT_SRL_GET_PCB_COUNT );          \
    ODB_PARAM_SET_OBJ( _layer_sr );                       \
    ODB_PARAM_SET_IP( _pcb_count );                      \
    ODB_CALL;  }

#define ODB_STEP_GET_SR_DATA( _steps_name, _step_has_sr ) {\
    ODB_PARAMS_INIT( ODB_ACT_SRL_GET_SR_INFO );              \
    ODB_PARAM_SET_OBJP( _steps_name );                       \
    ODB_PARAM_SET_OBJP( _step_has_sr );                      \
    ODB_CALL;  }


#define ODB_STEP_GET_SR_LAYER( _step_name, _layer_name, _open_ops, _layer_sr ) {\
    ODB_PARAMS_INIT( ODB_ACT_SRL_GET_SR_LAYER );                                  \
    ODB_PARAM_SET_S( _step_name );                                                \
    ODB_PARAM_SET_S( _layer_name );                                               \
    ODB_PARAM_SET_I( _open_ops );                                                 \
    ODB_PARAM_SET_OBJP( _layer_sr );                                              \
    ODB_CALL;  }

#define ODB_LAYER_SR_GET_SHAPE( _layer_sr, _index, _single_iteration, _shape )  { \
    ODB_PARAMS_INIT( ODB_ACT_SRL_GET_SHAPE );                    \
    ODB_PARAM_SET_OBJ( _layer_sr );                              \
    ODB_PARAM_SET_IP( _index );                                  \
    ODB_PARAM_SET_I  (_single_iteration);                        \
    ODB_PARAM_SET_SHAPE( _shape );                               \
    ODB_CALL;  }

#define ODB_LAYER_SR_GET_F( _layer_sr, _index, _single_iteration, _f )  { \
    ODB_PARAMS_INIT( ODB_ACT_SRL_GET_F );                \
    ODB_PARAM_SET_OBJ( _layer_sr );                      \
    ODB_PARAM_SET_IP( _index );                          \
    ODB_PARAM_SET_I  (_single_iteration);                \
    ODB_PARAM_SET_F( _f );                               \
    ODB_CALL;  }

#define ODB_LAYER_SR_GET_F_ATTR( _layer_sr, _nf, _name, _data, _exists )  { \
    ODB_PARAMS_INIT( ODB_ACT_SRL_GET_F_ATTR ); \
    ODB_PARAM_SET_OBJ( _layer_sr );            \
    ODB_PARAM_SET_I( _nf );                    \
    ODB_PARAM_SET_S (_name);                   \
    ODB_PARAM_SET_VOID(_data);                 \
    ODB_PARAM_SET_I (sizeof(_data));           \
    ODB_PARAM_SET_IP(_exists);                 \
    ODB_CALL;  }

#define ODB_LAYER_SR_CONTOURIZE( _layer_ld, _tol, _excl_texts, _repl_hatch, _max_net_size, \
    _work_on_selected, _single_iteration, _sld, _skiped_nets_lst) \
 { ODB_PARAMS_INIT(ODB_ACT_SRL_CONTOURIZE);                            \
 ODB_PARAM_SET_OBJ ( _layer_ld );                                    \
 ODB_PARAM_SET_I  (_tol);                                            \
 ODB_PARAM_SET_I  (_excl_texts);                                     \
 ODB_PARAM_SET_I  (_repl_hatch);                                     \
 ODB_PARAM_SET_I  (_max_net_size);                                   \
 ODB_PARAM_SET_I  (_work_on_selected);                               \
 ODB_PARAM_SET_I  (_single_iteration);                               \
 ODB_PARAM_SET_OBJP (_sld);                                          \
 ODB_PARAM_SET_OBJP (_skiped_nets_lst);                              \
 ODB_CALL; }

#define ODB_LAYER_SR_GET_BOARD_NET_BY_NET( _layer_sr, _net, _board_net )  { \
    ODB_PARAMS_INIT( ODB_ACT_SRL_GET_BOARD_NET_BY_NET );                     \
    ODB_PARAM_SET_OBJ ( _layer_sr );                                         \
    ODB_PARAM_SET_I ( _net );                                                \
    ODB_PARAM_SET_IP ( _board_net );                                         \
    ODB_CALL; }

#define ODB_LAYER_SR_GET_NET( _layer_sr, _step_index, _net, _net_shapes ) {\
    ODB_PARAMS_INIT( ODB_ACT_SRL_GET_NET );                                 \
    ODB_PARAM_SET_OBJ ( _layer_sr );                                        \
    ODB_PARAM_SET_IP ( _step_index );                                       \
    ODB_PARAM_SET_I ( _net );                                               \
    ODB_PARAM_SET_OBJP ( _net_shapes );                                     \
    ODB_CALL; }

#define ODB_LAYER_SR_COUNT_NET( _layer_sr, _nets_num ) { \
    ODB_PARAMS_INIT( ODB_ACT_SRL_COUNT_NET );             \
    ODB_PARAM_SET_OBJ ( _layer_sr );                      \
    ODB_PARAM_SET_IP ( _nets_num );                       \
    ODB_CALL; }  

#define ODB_LAYER_SR_COUNT_F( _layer_sr, _features_num ) { \
   ODB_PARAMS_INIT( ODB_ACT_SRL_COUNT_F );             \
   ODB_PARAM_SET_OBJ ( _layer_sr );                      \
   ODB_PARAM_SET_IP ( _features_num );                       \
   ODB_CALL; }  

#define ODB_LAYER_SR_COUNT_SHAPE( _layer_sr, _shapes_num ) { \
   ODB_PARAMS_INIT( ODB_ACT_SRL_COUNT_SHAPE );             \
   ODB_PARAM_SET_OBJ ( _layer_sr );                      \
   ODB_PARAM_SET_IP ( _shapes_num );                       \
   ODB_CALL; }  

#define ODB_LAYER_SR_GET_PROFILE(_layer_sr, _index, _profile)  { \
    ODB_PARAMS_INIT(ODB_ACT_SRL_GET_PROFILE);                    \
    ODB_PARAM_SET_OBJ(_layer_sr);                                \
    ODB_PARAM_SET_IP(_index);                                    \
    ODB_PARAM_SET_SHAPE(_profile);                               \
    ODB_CALL; }

#define ODB_LAYER_SR_GET_RIGID_FLEX_AREAS( _layer_sr, _single_iteration, _flex_lst, _rigid_lst ) {\
    ODB_PARAMS_INIT( ODB_ACT_SRL_GET_RIGID_FLEX_AREAS );                   \
    ODB_PARAM_SET_OBJ ( _layer_sr );                                       \
    ODB_PARAM_SET_I  (_single_iteration);				   \
    ODB_PARAM_SET_OBJP(_flex_lst);					   \
    ODB_PARAM_SET_OBJP(_rigid_lst);				           \
    ODB_CALL; }

#define ODB_LAYER_SR_GET_STEP_RIGID_FLEX_AREAS( _layer_sr, _single_iteration, _flex_lst, _rigid_lst ) {\
    ODB_PARAMS_INIT( ODB_ACT_SRL_GET_STEP_RIGID_FLEX_AREAS );              \
    ODB_PARAM_SET_OBJ ( _layer_sr );                                       \
    ODB_PARAM_SET_I  (_single_iteration);				   \
    ODB_PARAM_SET_OBJP(_flex_lst);					   \
    ODB_PARAM_SET_OBJP(_rigid_lst);				           \
    ODB_CALL; }


#define ODB_FIX_RESET {                                 \
    ODB_PARAMS_INIT(ODB_ACT_FIX_RESET);                 \
    ODB_CALL; }

#define ODB_FIX_MARK {                                 \
    ODB_PARAMS_INIT(ODB_ACT_FIX_MARK);                 \
    ODB_CALL; }

#define ODB_FIX_UNMARK {                                 \
    ODB_PARAMS_INIT(ODB_ACT_FIX_UNMARK);                 \
    ODB_CALL; }

#define ODB_FIX_RESET_MARK {                                 \
    ODB_PARAMS_INIT(ODB_ACT_FIX_RESET_MARK);                 \
    ODB_CALL; }

#define ODB_FIX_UNDO_TO_MARK {                               \
    ODB_PARAMS_INIT(ODB_ACT_FIX_UNDO_TO_MARK);                 \
    ODB_CALL; }

#define ODB_FIX_PUSH_ADD(_ld,_nf) {             \
    ODB_PARAMS_INIT(ODB_ACT_FIX_PUSH_ADD);      \
    ODB_PARAM_SET_OBJ(_ld);                     \
    ODB_PARAM_SET_I(_nf);                       \
    ODB_CALL; }

#define ODB_FIX_PUSH_DELETE(_ld,_nf) {          \
    ODB_PARAMS_INIT(ODB_ACT_FIX_PUSH_DELETE);   \
    ODB_PARAM_SET_OBJ(_ld);                     \
    ODB_PARAM_SET_I(_nf);                       \
    ODB_CALL; }


#define ODB_FIX_PUSH_RESIZE(_ld,_nf,_size) {    \
    ODB_PARAMS_INIT(ODB_ACT_FIX_PUSH_RESIZE);   \
    ODB_PARAM_SET_OBJ(_ld);                     \
    ODB_PARAM_SET_I(_nf);                       \
    ODB_PARAM_SET_I(_size);                     \
    ODB_CALL; }

#define ODB_FIX_PUSH_MOVE(_ld,_nf,_dx,_dy) {    \
    ODB_PARAMS_INIT(ODB_ACT_FIX_PUSH_MOVE);     \
    ODB_PARAM_SET_OBJ(_ld);                     \
    ODB_PARAM_SET_I(_nf);                       \
    ODB_PARAM_SET_I(_dx);                       \
    ODB_PARAM_SET_I(_dy);                       \
    ODB_CALL; }

#define ODB_FIX_PUSH_MOVE_S(_ld,_nf,_dx,_dy) {  \
    ODB_PARAMS_INIT(ODB_ACT_FIX_PUSH_MOVE_S);   \
    ODB_PARAM_SET_OBJ(_ld);                     \
    ODB_PARAM_SET_I(_nf);                       \
    ODB_PARAM_SET_I(_dx);                       \
    ODB_PARAM_SET_I(_dy);                       \
    ODB_CALL; }

#define ODB_FIX_PUSH_MOVE_E(_ld,_nf,_dx,_dy) {  \
    ODB_PARAMS_INIT(ODB_ACT_FIX_PUSH_MOVE_E);   \
    ODB_PARAM_SET_OBJ(_ld);                     \
    ODB_PARAM_SET_I(_nf);                       \
    ODB_PARAM_SET_I(_dx);                       \
    ODB_PARAM_SET_I(_dy);                       \
    ODB_CALL; }

#define ODB_FIX_PUSH_SYMBOL(_ld,_nf,_num,_type) {  \
    ODB_PARAMS_INIT(ODB_ACT_FIX_PUSH_SYMBOL);   \
    ODB_PARAM_SET_OBJ(_ld);                     \
    ODB_PARAM_SET_I(_nf);                       \
    ODB_PARAM_SET_SYM(_num);                 \
    ODB_PARAM_SET_I(_type);                     \
    ODB_CALL; }

#define ODB_FIX_PUSH_SET_ATTR(_ld,_nf,_name,_data) {    \
    ODB_PARAMS_INIT(ODB_ACT_FIX_PUSH_SET_ATTR);         \
    ODB_PARAM_SET_OBJ(_ld);                             \
    ODB_PARAM_SET_I(_nf);                               \
    ODB_PARAM_SET_S(_name);                             \
    ODB_PARAM_SET_VOID(_data);                          \
    ODB_CALL; }

#define ODB_FIX_PUSH_DELETE_ATTR(_ld,_nf,_name) {       \
    ODB_PARAMS_INIT(ODB_ACT_FIX_PUSH_DELETE_ATTR);      \
    ODB_PARAM_SET_OBJ(_ld);                             \
    ODB_PARAM_SET_I(_nf);                               \
    ODB_PARAM_SET_S(_name);                             \
    ODB_CALL; }

#define ODB_FIX_PUSH_CHANGE_FEATURE( _ld, _nf, _f ) {   \
    ODB_PARAMS_INIT(ODB_ACT_FIX_PUSH_CHANGE_FEATURE);   \
    ODB_PARAM_SET_OBJ( _ld );				\
    ODB_PARAM_SET_I( _nf );				\
    ODB_PARAM_SET_F( _f );				\
    ODB_CALL; }

#define ODB_FIX_PUSH_SPACING( _ld1, _nf1, _ld2, _nf2, _spacing ) {	\
    ODB_PARAMS_INIT(ODB_ACT_FIX_PUSH_SPACING);		\
    ODB_PARAM_SET_OBJ( _ld1 );				\
    ODB_PARAM_SET_I( _nf1 );				\
    ODB_PARAM_SET_OBJ( _ld2 );				\
    ODB_PARAM_SET_I( _nf2 );				\
    ODB_PARAM_SET_I( _spacing );			\
    ODB_CALL; }

#define ODB_FIX_INIT_ALL_OPTIONS {                  \
    ODB_PARAMS_INIT(ODB_ACT_FIX_INIT_ALL_OPTIONS);  \
    ODB_CALL; }

#define ODB_FIX_CLOSE_ALL_OPTIONS {                 \
    ODB_PARAMS_INIT(ODB_ACT_FIX_CLOSE_ALL_OPTIONS); \
    ODB_CALL; }

#define ODB_FIX_REPEAT_OPTION  {                 \
    ODB_PARAMS_INIT(ODB_ACT_FIX_REPEAT_OPTION);  \
    ODB_CALL; }

#define ODB_FIX_ADD_ONE_OPTION( _shape, _option_size )  {                 \
    ODB_PARAMS_INIT(ODB_ACT_FIX_ADD_ONE_OPTION);  \
    ODB_PARAM_SET_SHAPE( _shape );		  \
    ODB_PARAM_SET_I( _option_size );             \
    ODB_CALL; }

#define ODB_FIX_GET_LOCAL_LAYER( _ld )  {	    \
    ODB_PARAMS_INIT(ODB_ACT_FIX_GET_LOCAL_LAYER);   \
    ODB_PARAM_SET_OBJP(_ld);			    \
    ODB_CALL;}

#define ODB_FIX_GET_LOCAL_SHAPE( _shape )  {	    \
    ODB_PARAMS_INIT(ODB_ACT_FIX_GET_LOCAL_SHAPE);   \
    ODB_PARAM_SET_SHAPE (_shape);		    \
    ODB_CALL;}

#define ODB_FIX_GET_LOCAL_MODE( _local_mode_p ){    \
    ODB_PARAMS_INIT(ODB_ACT_FIX_GET_LOCAL_MODE);    \
    ODB_PARAM_SET_IP(_local_mode_p);		    \
    ODB_CALL;}

#define ODB_FIX_GET_LOCAL_CATEGORY( _catid_p ){	    \
    ODB_PARAMS_INIT(ODB_ACT_FIX_GET_LOCAL_CATEGORY);\
    ODB_PARAM_SET_IP(_catid_p);			    \
    ODB_CALL;}

#define ODB_FIX_GET_LOCAL_SCALAR( _scalar_p ){	    \
    ODB_PARAMS_INIT(ODB_ACT_FIX_GET_LOCAL_SCALAR);  \
    ODB_PARAM_SET_DP(_scalar_p);		    \
    ODB_CALL;}

#define ODB_FIX_GET_LOCAL_FEATURES( _list , _skip_non_trans){	    \
    ODB_PARAMS_INIT(ODB_ACT_FIX_GET_LOCAL_FEATURES);\
    ODB_PARAM_SET_OBJP( _list );		    \
	ODB_PARAM_SET_I(_skip_non_trans);       \
    ODB_CALL;}

#define ODB_FIX_GET_LOCAL_DEP_SHAPES( _list ){	      \
    ODB_PARAMS_INIT(ODB_ACT_FIX_GET_LOCAL_DEP_SHAPES);\
    ODB_PARAM_SET_OBJP( _list );		      \
    ODB_CALL;}

#define ODB_FUNC_LOAD(_func_name,_func_desc) {     \
  ODB_PARAMS_INIT(ODB_ACT_FUNC_LOAD);                   \
  ODB_PARAM_SET_S(_func_name);			        \
  ODB_PARAM_SET_OBJP(_func_desc);		        \
  ODB_CALL;					        \
}

#define ODB_FUNC_LOAD_LIST(_func_name,_func_desc_list) {     \
    ODB_PARAMS_INIT(ODB_ACT_FUNC_LOAD_LIST);                 \
    ODB_PARAM_SET_S(_func_name);			     \
    ODB_PARAM_SET_OBJP(_func_desc_list);	             \
    ODB_CALL;					             \
}

#define ODB_FUNC_EVAL(_func_desc,_xval,_yval) {    \
  ODB_PARAMS_INIT(ODB_ACT_FUNC_EVAL);  \
  ODB_PARAM_SET_OBJ(_func_desc);			\
  ODB_PARAM_SET_I  (_xval);  \
  ODB_PARAM_SET_IP (_yval);  \
  ODB_CALL;					        \
}

#define ODB_FUNC_GET_FACTOR(_func_desc,_factor) {   \
    ODB_PARAMS_INIT(ODB_ACT_FUNC_GET_FACTOR);           \
    ODB_PARAM_SET_OBJ(_func_desc);			\
    ODB_PARAM_SET_IP (_factor);                         \
    ODB_CALL;					        \
}

#define ODB_FUNC_GET_DOMAIN(_func_desc,_xmin,_xmax) {    \
  ODB_PARAMS_INIT(ODB_ACT_FUNC_GET_DOMAIN);  \
  ODB_PARAM_SET_OBJ(_func_desc);			\
  ODB_PARAM_SET_IP  (_xmin);  \
  ODB_PARAM_SET_IP (_xmax);  \
  ODB_CALL;					        \
}

#define ODB_FUNC_GET_NEIGHBOR(_func_desc,_str) {     \
    ODB_PARAMS_INIT(ODB_ACT_FUNC_GET_NEIGHBOR);      \
    ODB_PARAM_SET_OBJ(_func_desc);		     \
    ODB_PARAM_SET_SP(_str);                          \
    ODB_CALL;				             \
}

#define ODB_FUNC_GET_FIRST_POINT(_func_desc,_xfirst,_yfirst) {    \
    ODB_PARAMS_INIT(ODB_ACT_FUNC_GET_FIRST_POINT);  \
    ODB_PARAM_SET_OBJ(_func_desc);			\
    ODB_PARAM_SET_IP  (_xfirst);  \
    ODB_PARAM_SET_IP (_yfirst);  \
    ODB_CALL;					        \
}

#define ODB_FUNC_CREATE(_func_desc) {                   \
  ODB_PARAMS_INIT(ODB_ACT_FUNC_CREATE);                 \
  ODB_PARAM_SET_OBJP(_func_desc);		        \
  ODB_CALL;					        \
}

#define ODB_FUNC_SET_UNITS(_func_desc,_u) {             \
  ODB_PARAMS_INIT(ODB_ACT_FUNC_SET_UNITS);              \
  ODB_PARAM_SET_OBJ(_func_desc);		        \
  ODB_PARAM_SET_I(_u);                                  \
  ODB_CALL;					        \
}

#define ODB_FUNC_GET_INTERPOLATION(_func_desc,_i) {     \
    ODB_PARAMS_INIT(ODB_ACT_FUNC_GET_INTERPOLATION);    \
    ODB_PARAM_SET_OBJ(_func_desc);		        \
    ODB_PARAM_SET_IP(_i);                               \
    ODB_CALL;					        \
}

#define ODB_FUNC_SET_INTERPOLATION(_func_desc,_i) {     \
  ODB_PARAMS_INIT(ODB_ACT_FUNC_SET_INTERPOLATION);      \
  ODB_PARAM_SET_OBJ(_func_desc);		        \
  ODB_PARAM_SET_I(_i);                                  \
  ODB_CALL;					        \
}

#define ODB_FUNC_ADD_POINT(_func_desc,_x,_y) {          \
  ODB_PARAMS_INIT(ODB_ACT_FUNC_ADD_POINT);              \
  ODB_PARAM_SET_OBJ(_func_desc);		        \
  ODB_PARAM_SET_I(_x);                                  \
  ODB_PARAM_SET_I(_y);                                  \
  ODB_CALL;					        \
}

#define ODB_FUNC_SAVE(_func_desc,_name) {               \
  ODB_PARAMS_INIT(ODB_ACT_FUNC_SAVE);                   \
  ODB_PARAM_SET_OBJ(_func_desc);		        \
  ODB_PARAM_SET_S(_name);                               \
  ODB_CALL;					        \
}

#define ODB_DETCHSETUP_LOAD(_detchsetup_file_name,_detchsetup) {     \
    ODB_PARAMS_INIT(ODB_ACT_DETCHSETUP_LOAD);                        \
    ODB_PARAM_SET_S(_detchsetup_file_name);   	                     \
    ODB_PARAM_SET_VOID(_detchsetup); 		                     \
    ODB_CALL;					                     \
}

#define ODB_MALLOC(size)  \
   ((void *) gen__mem_malloc((size),1,__FILE__,__LINE__))
#define ODB_CALLOC(nelem,size) \
   ((void *) gen__mem_calloc((nelem),(size),1,__FILE__,__LINE__))
#define ODB_FREE(p) \
   gen__mem_free((p),1,__FILE__,__LINE__)
#define ODB_REALLOC(p,size) \
   ((void *) gen__mem_realloc((p),(size),1,__FILE__,__LINE__))
#define ODB_COND_FREE(p) {if((p)!= NULL){ODB_FREE((p)); p=NULL;}}

/* 0 == GEN_MEM_FAST_MODE */
#define ODB_FMALLOC(size)  \
    ((void *) gen__mem_malloc((size),0,__FILE__,__LINE__))
#define ODB_FFREE(p) \
    gen__mem_free((p),0,__FILE__,__LINE__)

/* ------- OBJECT DEFINITION MACROS ---------------------- */

/* In V2.0, all definition of shapes and features were converted
 * to static to prvenet accumulation of memory.
 * To aboid this change, one has to add -DODB_D_NOSTATIC
 * to Makefiles of ODB programs
 */


#ifdef ODB_D_NOSTATIC
#define _ODB_D_STATIC   /* None */
#else
#define _ODB_D_STATIC static
#endif

#define ODB_MAGIC_F	12345678
#define ODB_MAGIC_SHAPE	18273645
#define ODB_MAGIC_COMP	21436587

#define ODB_D_LAYER(d) _ODB_D_STATIC odb_obj_desc_struc d = ODB_L_DESC_NULL_VALUE
#define ODB_D_LIST(d)  _ODB_D_STATIC odb_obj_desc_struc d = ODB_L_DESC_NULL_VALUE
#define ODB_D_FUNC(d)  _ODB_D_STATIC odb_obj_desc_struc d = ODB_L_DESC_NULL_VALUE
#define ODB_D_SRL(d)   _ODB_D_STATIC odb_obj_desc_struc d = ODB_L_DESC_NULL_VALUE
#define ODB_D_DETCH_SETUP(d)  _ODB_D_STATIC odb_obj_desc_struc d = ODB_L_DESC_NULL_VALUE

#define ODB_S_LAYER(d) odb_obj_desc_struc d
#define ODB_S_LIST(d)  odb_obj_desc_struc d
#define ODB_S_FUNC(d)  odb_obj_desc_struc d
#define ODB_S_SRL(d)   odb_obj_desc_struc d

#define ODB_D_F(f) \
   _ODB_D_STATIC odb_f_struc _##f = \
   { ODB_MAGIC_F,              \
     ODB_L_NULL_NF,            \
     { 0 },                    \
     ODB_L_DESC_NULL_VALUE, }; \
   _ODB_D_STATIC odb_f_struc *f   = &_##f

#define ODB_D_COMP(comp) \
   _ODB_D_STATIC odb_comp_struc _##comp = \
   { ODB_MAGIC_COMP,              \
     ODB_L_DESC_NULL_VALUE,    \
     ODB_L_NULL_NF,            \
     0  }; \
   _ODB_D_STATIC odb_comp_struc *comp   = &_##comp

#define ODB_D_SHAPE(shape) \
   _ODB_D_STATIC odb_shape_struc _##shape = \
   { ODB_MAGIC_SHAPE ,  \
     ODB_L_DESC_NULL_VALUE, \
     ODB_L_NULL_FCD,    \
     ODB_L_NULL_NFC,    \
     ODB_L_NULL_NET,    \
     TRUE,              \
     ODB_L_NULL_NF,     \
     ODB_L_F_TYPE_NONE, \
     ODB_L_F_SYM_NONE,  \
     0 }; \
   _ODB_D_STATIC odb_shape_struc *shape   = &_##shape

#define ODB_D_NEIGHBOR(neighbor) \
   _ODB_D_STATIC odb_neighbor_struc _##neighbor = \
   { ODB_MAGIC_SHAPE ,  \
     ODB_L_DESC_NULL_VALUE, \
     ODB_L_NULL_FCD,    \
     ODB_L_NULL_NFC,    \
     ODB_L_NULL_NET,    \
     TRUE,              \
     ODB_L_NULL_NF,     \
     ODB_L_F_TYPE_NONE, \
     ODB_L_F_SYM_NONE,  \
     0 }; \
   _ODB_D_STATIC odb_neighbor_struc *neighbor   = &_##neighbor

#define ODB_P_LAYER(d)	   odb_obj_desc_struc d
#define ODB_P_LIST(d)      odb_obj_desc_struc d
#define ODB_P_FUNC(d)      odb_obj_desc_struc d
#define ODB_P_SRL(d)       odb_obj_desc_struc d
#define ODB_P_F(f)         odb_f_struc *f
#define ODB_P_SHAPE(shape) odb_shape_struc *shape
#define ODB_P_COMP(comp)   odb_comp_struc *comp
#define ODB_P_NEIGHBOR(neighbor) odb_neighbor_struc *neighbor


/* ------- FEATURE FIELDS MACROS -------------------------- */

#define ODB_M_F_NF(_f)		(_f)->nf
#define ODB_M_F_LD(_f)		(_f)->ld
#define ODB_M_F_ROTATION(_f)    (_f)->rotation
#define ODB_M_F_TYPE(_f)	(_f)->flags.type
#define ODB_M_F_SYM_TYPE(_f)	(_f)->flags.sym_type
#define ODB_M_F_POLARITY(_f)	(_f)->flags.polarity
#define ODB_M_F_ANGLE(_f)	(_f)->flags.angle
#define ODB_M_F_MIRROR(_f)	(_f)->flags.mirror
#define ODB_M_F_CW(_f)   	(_f)->flags.cw
#define ODB_M_F_SELECT(_f)	(_f)->flags.select
#define ODB_M_F_DRILL(_f)	(_f)->flags.drill
#define ODB_M_F_ATTR(_f)  	(_f)->flags.attr
#define ODB_M_F_DCODE(_f)  	(_f)->flags.dcode
#define ODB_M_F_BAR(_f)  	(_f)->flags.bar
#define ODB_M_F_TEXT_VER(_f)    (_f)->flags.text_ver

#define ODB_M_F_SYM_NUM(_f)	(_f)->usym.sym

#define ODB_M_F_LINE_PS(_f)  	(_f)->f.line.ps
#define ODB_M_F_LINE_PE(_f)  	(_f)->f.line.pe

#define ODB_M_F_PAD_POS(_f)  	(_f)->f.pad.pc
#define ODB_M_F_CONT_SURFACE(_f) (_f)->f.surface.cont

#define ODB_M_F_ARC_PS(_f)  	(_f)->f.arc.ps
#define ODB_M_F_ARC_PE(_f)  	(_f)->f.arc.pe
#define ODB_M_F_ARC_PC(_f)  	(_f)->f.arc.pc
#define ODB_M_F_ARC_CW(_f)   	(_f)->flags.cw

#define ODB_M_F_TEXT_POS(_f)      (_f)->f.text.pos
#define ODB_M_F_TEXT_STR(_f)      (_f)->f.text.str
#define ODB_M_F_TEXT_FNTID(_f)    (_f)->f.text.fntid

#define ODB_M_F_TEXT_XSIZE(_f)    (_f)->f.text.u.string.xsize
#define ODB_M_F_TEXT_YSIZE(_f)    (_f)->f.text.u.string.ysize
#define ODB_M_F_TEXT_XSPACE(_f)   (_f)->f.text.u.string.xspace
#define ODB_M_F_TEXT_W_FACTOR(_f) (_f)->f.text.u.string.w_factor

#define ODB_M_F_BAR_TYPE(_f)      (_f)->f.text.u.bar.type
#define ODB_M_F_BAR_FASC(_f)      (_f)->f.text.u.bar.fasc
#define ODB_M_F_BAR_CS(_f)        (_f)->f.text.u.bar.cs
#define ODB_M_F_BAR_BG(_f)        (_f)->f.text.u.bar.bg
#define ODB_M_F_BAR_ASTR(_f)      (_f)->f.text.u.bar.astr
#define ODB_M_F_BAR_ASTR_POS(_f)  (_f)->f.text.u.bar.astr_pos
#define ODB_M_F_BAR_WIDTH(_f)     (_f)->f.text.u.bar.width
#define ODB_M_F_BAR_HEIGHT(_f)    (_f)->f.text.u.bar.height

#define ODB_M_F_COPY(_dest_f, _source_f) \
   ODB_F_COPY(_source_f, _dest_f)

#define ODB_M_F_TO_1_SHAPE(f, shape, success) \
   { ODB_D_LIST(_shape_list); \
     int _shape_list_size; \
     int _first = 0; \
     ODB_F_TO_SHAPE_LIST(f, _shape_list); \
     ODB_LIST_COUNT(_shape_list, _shape_list_size); \
     if (_shape_list_size != 1) { \
	success = FALSE; \
     } else { \
	success = TRUE; \
	ODB_LIST_GET_SHAPE(_shape_list, _first, shape); \
     } \
     /*ODB_LIST_DESTROY(_shape_list);*/ }

#define ODB_M_F_NF_TO_1_SHAPE(nf, layer, shape, success) \
   { ODB_D_LIST(_shape_list); \
     int _shape_list_size; \
     int _first = 0; \
     ODB_F_NF_TO_SHAPE_LIST(nf, layer, _shape_list); \
     ODB_LIST_COUNT(_shape_list, _shape_list_size); \
     if (_shape_list_size != 1) { \
	success = FALSE; \
     } else { \
	success = TRUE; \
	ODB_LIST_GET_SHAPE(_shape_list, _first, shape); \
        if (ODB_M_SHAPE_SINGLE(shape) == FALSE) { \
           success = FALSE; \
        } \
     } \
     /*ODB_LIST_DESTROY(_shape_list);*/ }

#define ODB_M_F_FREE( _f ) \
  {  int status = odb__lib_f_free( _f ); \
STATUS_CHECK;       } \
/* ---------- Feature any angle Macros -----------------------*/

#define ODB_M_ROTATION_2_ANGLE_ENUM( _rr, _i )  {                             \
        double __r2 = _rr;                                                    \
        while ( __r2 <= -MIN_ANG_RAD )         { __r2 += M_PIx2; }            \
        while ( __r2 >= (M_PIx2+MIN_ANG_RAD) ) { __r2 -= M_PIx2; }            \
        if( __r2 < MIN_ANG_RAD || __r2 > (M_PIx2 - MIN_ANG_RAD) ) { _i = 0; } \
        else if( ABS( __r2 - M_PI_2  ) < MIN_ANG_RAD )	          { _i = 1; } \
        else if( ABS( __r2 - M_PI    ) < MIN_ANG_RAD )            { _i = 2; } \
        else if( ABS( __r2 - M_PIx3_2) < MIN_ANG_RAD )	          { _i = 3; } \
        else   {  _i = ODB_L_ANGLE_ANY; } }

#define ODB_M_F_GET_ROTATION_GRAD( _f, _g )  do { \
        if ( ODB_M_F_ANGLE( _f ) != ODB_L_ANGLE_ANY )  { (_g) = ODB_M_F_ANGLE( _f ) * 90; } \
        else { (_g) =  DEG( ODB_M_F_ROTATION( _f ) ); } } while ( 0 )
#define ODB_M_F_GET_ROTATION( _f, _r)  do {   \
        double __g;                           \
        ODB_M_F_GET_ROTATION_GRAD( _f, __g ); \
        _r = RAD( __g ); } while ( 0 )

#define ODB_M_F_SET_ROTATION( _r, _f ) do {                        \
        odb_angle_enum _angle;                                     \
        double         __r1 = _r;                                  \
        while ( __r1 <= -MIN_ANG_RAD         ) { __r1 += M_PIx2; } \
        while ( __r1 >= (M_PIx2+MIN_ANG_RAD) ) { __r1 -= M_PIx2; } \
        ODB_M_ROTATION_2_ANGLE_ENUM( __r1, _angle );               \
        ODB_M_F_ROTATION( _f ) = __r1;                             \
        ODB_M_F_ANGLE( _f )    = _angle;		           \
	ODB_M_F_ANGLE( _f )    = ODB_L_ANGLE_ANY; } while ( 0 )

#define ODB_M_F_SET_ROTATION_GRAD( _g, _f ) { ODB_M_F_SET_ROTATION( RAD( _g ), _f ); }

/* -------- Shape fields MACROS ------------------------------ */
#define ODB_M_SHAPE_TYPE(shape)	(shape)->mshape.type

#define ODB_M_IS_SHAPE_POINT(shape) \
   (ODB_M_SHAPE_TYPE(shape) == ODB_L_SHAPE_TYPE_POINT)
#define ODB_M_IS_SHAPE_SEG(shape) \
   (ODB_M_SHAPE_TYPE(shape) == ODB_L_SHAPE_TYPE_SEG)
#define ODB_M_IS_SHAPE_CURVE(shape) \
   (ODB_M_SHAPE_TYPE(shape) == ODB_L_SHAPE_TYPE_CURVE)
#define ODB_M_IS_SHAPE_CIRCLE(shape) \
   (ODB_M_SHAPE_TYPE(shape) == ODB_L_SHAPE_TYPE_CIRCLE)
#define ODB_M_IS_SHAPE_SQUARE(shape) \
   (ODB_M_SHAPE_TYPE(shape) == ODB_L_SHAPE_TYPE_SQUARE)
#define ODB_M_IS_SHAPE_RECT(shape) \
   (ODB_M_SHAPE_TYPE(shape) == ODB_L_SHAPE_TYPE_RECT)
#define ODB_M_IS_SHAPE_LINE(shape) \
   (ODB_M_SHAPE_TYPE(shape) == ODB_L_SHAPE_TYPE_LINE)
#define ODB_M_IS_SHAPE_ARC(shape) \
   (ODB_M_SHAPE_TYPE(shape) == ODB_L_SHAPE_TYPE_ARC)
#define ODB_M_IS_SHAPE_CONT(shape) \
   (ODB_M_SHAPE_TYPE(shape) == ODB_L_SHAPE_TYPE_CONT)

#define ODB_M_SHAPE_POINT(shape)      (shape)->mshape.s.point

#define ODB_M_SHAPE_SEG_PS(shape)     (shape)->mshape.s.seg.ps
#define ODB_M_SHAPE_SEG_PE(shape)     (shape)->mshape.s.seg.pe

#define ODB_M_SHAPE_CURVE_PS(shape)   (shape)->mshape.s.curve.ps
#define ODB_M_SHAPE_CURVE_PE(shape)   (shape)->mshape.s.curve.pe
#define ODB_M_SHAPE_CURVE_PC(shape)   (shape)->mshape.s.curve.pc
#define ODB_M_SHAPE_CURVE_CW(shape)   (shape)->mshape.s.curve.flags.cw

#define ODB_M_SHAPE_CIRCLE_PC(shape)  (shape)->mshape.s.circle.pc
#define ODB_M_SHAPE_CIRCLE_R(shape)   (shape)->mshape.s.circle.r

#define ODB_M_SHAPE_SQUARE_PC(shape)  (shape)->mshape.s.square.pc
#define ODB_M_SHAPE_SQUARE_R(shape)   (shape)->mshape.s.square.r

#define ODB_M_SHAPE_RECT_PLL(shape)   (shape)->mshape.s.rect.pll
#define ODB_M_SHAPE_RECT_W(shape)     (shape)->mshape.s.rect.w
#define ODB_M_SHAPE_RECT_H(shape)     (shape)->mshape.s.rect.h

#define ODB_M_SHAPE_LINE_PS(shape)    (shape)->mshape.s.line.seg.ps
#define ODB_M_SHAPE_LINE_PE(shape)    (shape)->mshape.s.line.seg.pe
#define ODB_M_SHAPE_LINE_CAP(shape)   (shape)->mshape.s.line.w.cap
#define ODB_M_SHAPE_LINE_R(shape)     (shape)->mshape.s.line.w.r

#define ODB_M_SHAPE_ARC_PS(shape)     (shape)->mshape.s.arc.c.ps
#define ODB_M_SHAPE_ARC_PE(shape)     (shape)->mshape.s.arc.c.pe
#define ODB_M_SHAPE_ARC_PC(shape)     (shape)->mshape.s.arc.c.pc
#define ODB_M_SHAPE_ARC_CW(shape)     (shape)->mshape.s.arc.c.flags.cw
#define ODB_M_SHAPE_ARC_R(shape)      (shape)->mshape.s.arc.w.r
#define ODB_M_SHAPE_ARC_CAP(shape)    (shape)->mshape.s.arc.w.cap

#define ODB_M_SHAPE_CONT(shape)	      (shape)->mshape.s.cont.cont
#define ODB_M_SHAPE_CONTD(shape)      (shape)->mshape.s.cont.obj

#define ODB_M_SHAPE_LD(shape)         (shape)->ld
#define ODB_M_SHAPE_NFC(shape)	      (shape)->nfc
#define ODB_M_SHAPE_NET(shape)	      (shape)->net
#define ODB_M_SHAPE_SINGLE(shape)     (shape)->single
#define ODB_M_SHAPE_NF(shape)         (shape)->nf
#define ODB_M_SHAPE_NCOMP(shape)      (shape)->nf  /* comp num shares the same */
                                                   /* loc as feature num */
#define ODB_M_SHAPE_F_TYPE(shape)     (shape)->f_type
#define ODB_M_SHAPE_F_SYM_TYPE(shape) (shape)->f_sym_type
#define ODB_M_SHAPE_F_SYM(shape)      (shape)->f_sym

#define ODB_M_SHAPE_COPY(dest,source) \
   { if((dest)->magic == ODB_MAGIC_SHAPE && (source)->magic == ODB_MAGIC_SHAPE){ \
       int status = odb__lib_shape_copy(dest,source);  \
       STATUS_CHECK ; \
   } else { ODB_RETURN_ERR; }}

#define ODB_M_SHAPE_CLONE(dest,source) \
   { if((dest)->magic == ODB_MAGIC_SHAPE && (source)->magic == ODB_MAGIC_SHAPE){ \
       int status = odb__lib_shape_clone(dest,source);  \
       STATUS_CHECK ; \
   } else { ODB_RETURN_ERR; }}

#define ODB_M_CONT_CLONE(dest,source) \
   { int status = odb__lib_cont_clone(dest,source);  \
   STATUS_CHECK ;} 

#define ODB_M_SHAPE_FREE(s1) \
   { if((s1)->magic == ODB_MAGIC_SHAPE ){ \
       int status = odb__lib_shape_free(s1);  \
       STATUS_CHECK ; \
   } else { ODB_RETURN_ERR; }}

/*---------------- Neighbor Fields Macros -------------------------- */
#define ODB_M_NEIGHBOR_SHAPE(neighbor)     &((neighbor)->shape)
#define ODB_M_NEIGHBOR_DIST_SEG(neighbor)   ((neighbor)->dist_seg)
#define ODB_M_NEIGHBOR_DIST(neighbor)         (neighbor)->dist
#define ODB_M_NEIGHBOR_REL(neighbor)          (neighbor)->rel

#define ODB_M_NEIGHBOR_COPY(__dest, __source) \
    { ODB_M_SHAPE_COPY(ODB_M_NEIGHBOR_SHAPE(__dest), ODB_M_NEIGHBOR_SHAPE(__source));	\
      ODB_M_NEIGHBOR_DIST_SEG(__dest)	= ODB_M_NEIGHBOR_DIST_SEG(__source);		\
      ODB_M_NEIGHBOR_DIST(__dest)	= ODB_M_NEIGHBOR_DIST(__source);		\
      ODB_M_NEIGHBOR_REL(__dest)	= ODB_M_NEIGHBOR_REL(__source); }

/*---------------- Contour macros:  By no means comprehensive ----------------*/

#define ODB_M_SHAPE_CONT_TYPE(shape)      (shape)->s.cont[0].flags.type
#define ODB_M_SHAPE_CONT_IS_INH(shape)    (shape)->s.cont[0].hdr.flags.is_inh

#define ODB_M_SHAPE_POLY_NEDGE(shape)     (shape)->s.cont[0].poly.nedge
#define ODB_M_SHAPE_POLY_IS_ISLAND(shape) (shape)->s.cont[0].poly.flags.is_island

/* ------- COMPONENT FIELDS MACROS -------------------------- */

#define ODB_M_COMP_NCOMP(_comp)		(_comp)->ncomp
#define ODB_M_COMP_LD(_comp)		(_comp)->ld
#define ODB_M_COMP_NAME(_comp)		(_comp)->name
#define ODB_M_COMP_PART_NAME(_comp)	(_comp)->part_name
#define ODB_M_COMP_PKG_NAME(_comp)	(_comp)->pkg_name
#define ODB_M_COMP_X(_comp)		(_comp)->position.x
#define ODB_M_COMP_Y(_comp)		(_comp)->position.y
#define ODB_M_COMP_ROTATION(_comp)	(_comp)->rotation
#define ODB_M_COMP_HEIGHT(_comp)	(_comp)->height
#define ODB_M_COMP_PITCH(_comp)		(_comp)->pitch
#define ODB_M_COMP_MIRROR(_comp)	(_comp)->mirror
#define ODB_M_COMP_NUM_TOEPRINTS(_comp)	(_comp)->num_toeprints

/*------------ Miscellaneous Macros: For your macro enjoyment ----------------*/

#define ODB_M_OBJ_DESCRIPTOR(_d) (_d).descriptor
#define ODB_M_OBJ_RUN_NUMBER(_d) (_d).run_number

#define ODB_M_OBJ_P_INIT(_d) ODB_M_SET_LD(_d, ODB_L_DESC_NULL);;
#define ODB_M_OBJ_P_FREE(_d) 
#define ODB_M_SHAPE_CONTRUCTOR(_d) { \
    (_d)->magic = ODB_MAGIC_SHAPE; \
    (_d)->ld.descriptor = -1; \
    (_d)->ld.run_number = -1; \
    (_d)->fcd = ODB_L_NULL_FCD;\
    (_d)->nfc = ODB_L_NULL_NFC;\
    (_d)->net = ODB_L_NULL_NET;\
    (_d)->single = TRUE;\
    (_d)->nf = ODB_L_NULL_NF;\
    (_d)->f_type = ODB_L_F_TYPE_NONE;\
    (_d)->f_sym_type = ODB_L_F_SYM_NONE;\
    (_d)->f_sym = 0;\
    memset(&(_d)->mshape, 0, sizeof(odb_mat_shape_struc)); \
}
#define ODB_M_SHAPE_P_INIT(_d) (_d) = (odb_shape_struc*)ODB_MALLOC(sizeof(odb_shape_struc)); ODB_M_SHAPE_CONTRUCTOR(_d);
#define ODB_M_SHAPE_P_FREE(_d)

#define ODB_M_OBJ_EQ(_o1, _o2) (ODB_M_OBJ_DESCRIPTOR(_o1) == ODB_M_OBJ_DESCRIPTOR(_o2) && \
			        ODB_M_OBJ_RUN_NUMBER(_o1) == ODB_M_OBJ_RUN_NUMBER(_o2))

#define ODB_M_SET_LD(_dst_ld, _src_ld) { (_dst_ld) = (_src_ld); }

#define ODB_M_POINT_EQ(_s1, _s2)	\
       (ODB_M_IS_SHAPE_POINT(_s1) && ODB_M_IS_SHAPE_POINT(_s2) &&	\
	(ODB_M_SHAPE_POINT(_s1).x == ODB_M_SHAPE_POINT(_s2).x) &&	\
	(ODB_M_SHAPE_POINT(_s1).y == ODB_M_SHAPE_POINT(_s2).y))

#define ODB_M_POINT_COPY(_p_dest, _p_source) \
   {_p_dest.x = _p_source.x;   _p_dest.y = _p_source.y;}

#define ODB_M_POINT_CREATE(_x, _y, _p_dest) \
   {_p_dest.x = x;   _p_dest.y = y;}

/* make string */
#define ODB_M_GENERAL_MKSTR(s)      # s

/* --------------------------------------------------------------------------- */

/* how to order the compound elements such as shape, layer etc. according some field,
   size or what */
typedef enum {
   ODB_L_LIST_ORDER_DEFAULT=0,
   ODB_L_LIST_ORDER_NF ,           /* according the NF- value */
   ODB_L_LIST_ORDER_ID ,           /* for layers */
   ODB_L_LIST_ORDER_NOT_DISJOINT,  /* for shapes, when two shapes are not disjoint
				     treated as equal*/
   ODB_L_LIST_ORDER_DISJOINT,      /* disjoint shapes are treated as equal */
   ODB_L_LIST_ORDER_ASCENDING,     /* inceasing values */
   ODB_L_LIST_ORDER_DESCENDING,    /* decreasing values */
   ODB_L_LIST_ORDER_MIN=2,           /* minimum computing */
   ODB_L_LIST_ORDER_MAX=0            /* maximum computing */
} parameter_order_enum;


/* What sub-set of elements of the same oder to consider in
   the operation that gives a sub-list af the two input lists.

   ODB_L_LIST_MODE_DEFAULT -
   ODB_L_LIST_MODE_REMOVE - a given number of elements should be removed
   ODB_L_LIST_MODE_LEAVE - a given number of elements should be leaved
                           i.e. un-removed.
   ODB_L_LIST_MODE_EVERY -
      The list-element is treated as the whole set of elements
      having the same order-number i.e.,
      the operation is performed on every element with the same order.
      The default mode is treated as the ODB_L_LIST_MODE_EVERY
      When Minus the lists: A = { 1 2 3 2} - B {2} = {1 3}
      the {2 2} is removed.
   ODB_L_LIST_MODE_EXACT - When Minus the lists:
      A = { 1 2 3 2} - B {2} = {1 3 2}
      only one element from A is removed {2} and not {2 2}

   ODB_L_LIST_MODE_SORT_BUBBLE    - bubble sort.

   ODB_L_LIST_MODE_SERIAL         - the MAP command outputs the corresponding
                                    serial numbers of the mapped list.
   ODB_L_LIST_MODE_NO_SERIAL      - the MAP command doesn't output
                                    the serial-numbers	
   ODB_L_LIST_MODE_FILTER         - to be used for filtration
   ODB_L_LIST_MODE_FILTER_MATCH   - the return value ODB_L_LIST_NO_MATCH causes
                                    the value not be included,
   ODB_L_LIST_MODE_FILTER_NOMATCH - the return value ODB_L_LIST_NO_MATCH causes
                                    the value be included.
   ODB_L_LIST_MODE_NOSCALAR       - LIST
   ODB_L_LIST_MODE_SCALAR         - INT, DOUBLE, LAYER etc.
   ODB_L_LIST_MODE_BEFORE         - Insert before the designated shape
   ODB_L_LIST_MODE_AFTER          - after it
   */

typedef enum {
   ODB_L_LIST_MODE_DEFAULT=0,
   ODB_L_LIST_MODE_LEAVE=2,
   ODB_L_LIST_MODE_REMOVE=0,
   ODB_L_LIST_MODE_EVERY=4,
   ODB_L_LIST_MODE_EXACT=0,
   ODB_L_LIST_MODE_SORT_BUBBLE=8,
   ODB_L_LIST_MODE_SORT_Q = 256,
   ODB_L_LIST_MODE_SERIAL=16,
   ODB_L_LIST_MODE_NO_SERIAL=0,
   ODB_L_LIST_MODE_FILTER_NOMATCH=32,  /* in functions such as 'eq' */
   ODB_L_LIST_MODE_FILTER_MATCH=0,
   ODB_L_LIST_MODE_NOSCALAR=64,        /* LIST */
   ODB_L_LIST_MODE_SCALAR=0,           /* INT, DOUBLE, LAYER etc. */
   ODB_L_LIST_MODE_BEFORE=128,
   ODB_L_LIST_MODE_AFTER,
} parameter_mode_enum;


/* all the elements should be removed */
#define ODB_L_LIST_NUMBER_ALL  MAXINT
#define ODB_L_LIST_NUMBER_ONE  1

/* The following numbers should be not changed */
#define  ODB_L_LIST_ARGS_0     0     /* number of extra arguments is 0 */
#define  ODB_L_LIST_ARGS_1     1     /* number of extra arguments is 1 */

/* literals for list_map directives */
typedef enum {
   /* The user mapping function has no return value for filtering */
   ODB_L_LIST_MAP_OUTPUT_VALUE=1
} parameter_map_enum;

#define  ODB_L_LIST_NO_MATCH        1     /* There was no matching */
#define  ODB_L_LIST_MAP_ARGUMENTS   1     /* number of the extra arguments in the internal/user function */

#ifndef ODB_INTERNAL_LIBRARY
#include <odbLIST.h> /* Macros for invoking list functions */
#endif

#endif

#endif /*ODB_PUBLIC_OO*/

