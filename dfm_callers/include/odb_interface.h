#ifndef ODB_PUBLIC_OO 

#ifndef ODB_INTERFACE_H
#define ODB_INTERFACE_H

#include <odb.h>

/* 
 * The following should be in odbLIST.h (which is #included via odb.h)
 * but they are missing.
 */
#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern int odb__list_create(odb_list_type_enum type, ODB_P_LIST(*list));
extern int odb__list_clear(ODB_P_LIST(list));
extern int odb__list_destroy(ODB_P_LIST(list));
extern int odb__list_count(ODB_P_LIST(list), int* count);
extern int odb__list_remove(ODB_P_LIST(list), int serial);
extern int odb__list_get(ODB_P_LIST(list), int* serial, void* item, 
			 odb_list_type_enum type);
extern int odb__list_change(ODB_P_LIST(list),
                            int                serial,
                            void*              item,
                            odb_list_type_enum type);
extern int odb__list_add(ODB_P_LIST(list), void* item, 
			 odb_list_type_enum type);
extern int odb__list_first(ODB_P_LIST(list), void* item, 
			   odb_list_type_enum type);
extern int odb__list_last(ODB_P_LIST(list), void* item, 
			  odb_list_type_enum type);
extern int odb__list_copy_list(parameter_mode_enum mode, ODB_P_LIST(list0), 
			       ODB_P_LIST(*list1));
extern int odb__list_concatenate(parameter_mode_enum mode, 
				 ODB_P_LIST(list0), ODB_P_LIST(list1), 
				 ODB_P_LIST(*list2));
extern int odb__list_condense(ODB_P_LIST(list));
extern int odb__list_intersect(parameter_mode_enum mode,
			       parameter_mode_enum type,
			       int (*func)(void*, void*, void*, int*),
			       void*, ODB_P_LIST(list0), ODB_P_LIST(list1), 
			       ODB_P_LIST(*list2));
extern int odb__list_swap(ODB_P_LIST(list), int serial1, int serial2);
extern int odb__list_sort(parameter_mode_enum  mode,
			  parameter_order_enum order, 
			  ODB_P_LIST(list0), 
			  int (*func)(void* item, void* value, void* ),
			  void*, ODB_P_LIST(*list1));
extern int odb__list_register(int size, 
			      int (*init)(), 
			      int (*copy)(), 
			      int (*free)(), 
			      int* type_p);
extern int odb__list_create_2d(ODB_P_LIST(*listd_p));
extern int odb__list_build_2d (ODB_P_LIST(list));
extern int odb__list_minus_list(parameter_mode_enum  mode_type,
				parameter_order_enum order_type,
				int (*function_basic) (void *, void *, void *, int *),
				void *arg, 	 
				ODB_P_LIST(listd0),
				ODB_P_LIST(listd1),
				ODB_P_LIST(*listd2_p));


#if defined(__cplusplus) || defined(c_plusplus)
}
#endif


/* 
 * The following are just to make life easier by lessening the amount
 * of code associated with iterating over a list or layer. These are
 * not good for cases where the serial is needed at the end of the
 * loop.  
 */

     /* item_t is F, SHAPE, LAYER, INT, ... container_t is LIST or LAYER */
     /*25/03/2007 IL: renamed the index in roder to enable using foreach
       inside other foreach.*/
#define foreach(item_t, container_t, item, container)		\
{								\
  int _n_##item = 0;							\
  while(TRUE) {							\
    ODB_D_##item_t(item);					\
    ODB_##container_t##_GET_##item_t(container, _n_##item, item);	\
    if(_n_##item == ODB_L_LIST_END)					\
      break;

#define foreach_end				\
  }						\
}

#define foreach_f(f, features) foreach(F, LIST, f, features)  /* was missed BL 01.12.09 */

#define foreach_shape(shape, shapes) foreach(SHAPE, LIST, shape, shapes)

#define foreach_neighbor(neighbor, neighbors) foreach(NEIGHBOR, LIST, neighbor, neighbors)

#define foreach_layer(layer, layers) foreach(LAYER, LIST, layer, layers)

#define foreach_int(int_, ints)      foreach(INT, LIST, int_, ints)
#define ODB_D_INT(int_)              int int_ = 0

#define foreach_name(name, names)    foreach(NAME, LIST, name, names)
#define ODB_D_NAME(name)             odb_name name

#define foreach_layer_f(f, layer)    foreach(F, LAYER, f, layer)

/*
 * The following have not been used, and are therefore commented out until
 * needed. Test them then.
 *
#define foreach_double(double_, doubles) \
                                     foreach(DOUBLE, LIST, double_, doubles)
#define ODB_D_DOUBLE(double_)        double double_ = 0.0

#define foreach_layer_shape(shape, layer) \
                                     foreach(SHAPE, LAYER, shape, layer)
*/


/* 
 * According to the documentation of ODB_SETUP_GET_ERF_VAR*, the
 * value ODB_MAX_ERF_VAR should be defined.  
 * I have no definition, guessing 65 (ODB_L_LEN_NAME+1).
 */
#define ODB_MAX_ERF_VAR 65

/*
 * The same as ODB_SETUP_GET_ERF_VAR_NUMBER but for int not double.
 */
#define ODB_SETUP_GET_ERF_VAR_INT(_name) {	\
  odb_name s_##_name;				\
  int i_##_name;				\
  s_##_name[0] = '\0';				\
  ODB_SETUP_GET_ERF_VAR2(#_name,s_##_name);	\
  if (s_##_name[0] != '\0') {			\
    sscanf(s_##_name,"%d",&i_##_name);		\
    _name = i_##_name;				\
  }						\
}

/*14/03/2007 IL: This macro should ease the reading of ERF
  variables of type set*/
/*12/11/2007 IL: Enlarged size of __text_val to prevent error in some customer's ERF files*/
#define ODB_SETUP_GET_ERF_VAR_BOOLEAN(_name, _bool_val) {	    \
    char __text_val[25];					    \
    ODB_SETUP_GET_ERF_VAR(_name, __text_val, sizeof(__text_val));   \
    _bool_val = (__text_val[0] == 'y' || __text_val[0] == 'Y' ||    \
		 __text_val[0] == 't' || __text_val[0] == 'T' ||    \
		 __text_val[0] == '1' );			    \
}

/* 
 * In odb.h all of the types defind by the ODB_D_... macros are
 * defined as static! In order to write recursion one needs automatic
 * (stack) variables. In order to do this the following macros have
 * been written.
 */
#ifdef ODB_D_NOSTATIC

#define ODB_D_AUTO_LIST(l)  ODB_D_LIST(l)
#define ODB_D_AUTO_SHAPE(s) ODB_D_SHAPE(s)

#else

#define ODB_D_AUTO_LIST(d)  odb_obj_desc_struc d = ODB_L_DESC_NULL_VALUE

#define ODB_D_AUTO_SHAPE(shape) \
   odb_shape_struc _##shape = \
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
   odb_shape_struc *shape   = &_##shape 

#endif
#endif /* ODB_INTERFACE_H */

#endif /*ODB_PUBLIC_OO */
