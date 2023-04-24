/***************************************************************
 *
 *                       odbLIST.h
 *
 * This file contains declarations for using the odb_list
 * on various types of objects.
 *
 * The file is divided into several parts.
 * In the first part are the declarations which apply
 * to lists of all kinds of objects.
 *
 * The rest of the file contains functions that are 
 * specific to one type of object.
 *
 * This file was generated by the command:
 * awk -f odbLIST_make.awk > odbLIST.h
 *
 * The relevant files: odb_list.c, 
 *                     odb_list.t - should be changed respectively
 *
 ***************************************************************/
#ifndef ODB_PUBLIC_OO

/******************* General Declarations **********************/

#define ODB_STATUS_REPORT(action) if (odb_status != 0) { \
   odb__lib_write_err(#action, __FILE__, __LINE__, odb_status); \
   ODB_RETURN_ERR; \
} 

#define ODB_LIST_CREATE(list_type, list) { \
   odb_status = odb__list_create(list_type, &(list)); \
   ODB_STATUS_REPORT(ODB_LIST_CREATE); \
}
        
#define ODB_LIST_CREATE_2D(list) { \
   odb_status = odb__list_create_2d(&(list)); \
   ODB_STATUS_REPORT(ODB_LIST_CREATE_2D); \
}
   
#define ODB_LIST_CLEAR(list) { \
   odb_status = odb__list_clear(list); \
   ODB_STATUS_REPORT(ODB_LIST_CLEAR); \
}

#define ODB_LIST_DESTROY(list) { \
   odb_status = odb__list_destroy(list); \
   ODB_STATUS_REPORT(ODB_LIST_DESTROY); \
}

#define ODB_LIST_ADD_GENERIC(list, type, item) {        \
   odb_status = odb__list_add(list, (void*)item, type); \
   ODB_STATUS_REPORT(ODB_LIST_ADD_GENERIC);             \
}

#define ODB_LIST_COUNT(list, count) { \
   odb_status = odb__list_count(list, &(count)); \
   ODB_STATUS_REPORT(ODB_LIST_COUNT); \
}

#define ODB_LIST_REMOVE(list, serial) { \
   odb_status = odb__list_remove(list, serial); \
   ODB_STATUS_REPORT(ODB_LIST_REMOVE); \
}
   
#define ODB_LIST_GET_GENERIC(list, type, serial, item) {                \
   odb_status = odb__list_get(list, &(serial), (void*)item, type);      \
   ODB_STATUS_REPORT(ODB_LIST_GET_GENERIC);                             \
}
   
#define ODB_LIST_CHANGE_GENERIC(list, type, serial, item) {                     \
   odb_status = odb__list_change(list, serial, (void*)item, type);              \
   ODB_STATUS_REPORT(ODB_LIST_CHANGE_GENERIC);                                  \
}

#define ODB_LIST_BUILD_2D(list) { \
   odb_status = odb__list_build_2d(list); \
   ODB_STATUS_REPORT(ODB_LIST_BUILD_2D); \
}
        
#define ODB_LIST_COPY(_mode_type, list0, list1_p) {                 \
   odb_status = odb__list_copy_list(_mode_type, list0, &(list1_p)); \
   ODB_STATUS_REPORT(ODB_LIST_COPY);                                \
}

#define ODB_LIST_FIRST_GENERIC( list, type, item ) {              \
   odb_status = odb__list_first( list, (void*)item, type ); \
   ODB_STATUS_REPORT(ODB_LIST_FIRST_GENERIC);                   \
}

#define ODB_LIST_LAST_GENERIC(list, type, item) {              \
   odb_status = odb__list_last(list, (void*)item, type);  \
   ODB_STATUS_REPORT(ODB_LIST_LAST_GENERIC);                    \
}

#define ODB_LIST_CONCATENATE(order_mode,  list0, list1, list2_p) { \
   odb_status = odb__list_concatenate(order_mode, list0, list1, &(list2_p) ); \
   ODB_STATUS_REPORT(ODB_LIST_CONCATENATE); \
}

#define ODB_LIST_CONDENSE(list) { \
   odb_status = odb__list_condense(list); \
   ODB_STATUS_REPORT(ODB_LIST_CONDENSE); \
}

#define ODB_LIST_REVERSE(_mode_type, list0, list1_p) { \
   odb_status = odb__list_reverse(_mode_type, list0,  &(list1_p) ); \
   ODB_STATUS_REPORT(ODB_LIST_REVERSE); \
}

#define ODB_LIST_MINUS(order_mode, order_type,                    \
                       function_basic, arg,                       \
                       list0, list1, list2_p) {                   \
   odb_status = odb__list_minus_list(order_mode, order_type,      \
      (int (*) (void *, void *, void *, int *))(*function_basic), \
      arg, list0, list1, &(list2_p));                             \
   ODB_STATUS_REPORT(ODB_LIST_MINUS);                             \
}

#define ODB_LIST_INTERSECT(order_mode, order_type,                            \
                       function_basic, arg,                                   \
                       list0, list1, list2_p) {                               \
   odb_status = odb__list_intersect(order_mode, order_type,                   \
      (int (*) (void *, void *, void *, int *))(*function_basic),             \
      arg, list0, list1, &(list2_p) );                                        \
   ODB_STATUS_REPORT(ODB_LIST_INTERSECT);                                     \
}
        
#define ODB_LIST_SWAP(list, serial1, serial2) {         \
   odb_status = odb__list_swap(list, serial1, serial2); \
   ODB_STATUS_REPORT(ODB_LIST_SWAP);                    \
}
        
#define ODB_LIST_SORT(order_mode, order_type,                              \
                      list0, function_basic,                               \
                      list2_p) {                                           \
   odb_status = odb__list_sort(order_mode, order_type, list0,              \
                (int (*) (void *, void *, void *))(*function_basic), NULL, \
                &(list2_p) );                                              \
   ODB_STATUS_REPORT(ODB_LIST_SORT);                                       \
}

#define ODB_LIST_REGISTER( _size, _init, _copy, _free, _type ) {                \
   odb_status = odb__list_register( _size, _init, _copy, _free, &_type );       \
   ODB_STATUS_REPORT( ODB_LIST_REGISTER );                                      \
}

#define ODB_LIST_UNREGISTER( _type ) {          \
   odb_status = odb__list_unregister( _type );  \
   ODB_STATUS_REPORT( ODB_LIST_UNREGISTER );    \
}

/**************** SHAPE Declarations ******************/

#define ODB_LIST_ADD_SHAPE(list, item) { \
   odb_shape_struc *_temp = item; \
   odb_status = odb__list_add(list, _temp, ODB_L_LIST_TYPE_SHAPE); \
   ODB_STATUS_REPORT(ODB_LIST_ADD_SHAPE); \
}

#define ODB_LIST_GET_SHAPE(list, serial, item) { \
   odb_shape_struc *_temp = item; \
   odb_status = odb__list_get(list, &(serial), _temp, ODB_L_LIST_TYPE_SHAPE); \
   ODB_STATUS_REPORT(ODB_LIST_GET_SHAPE); \
}

#define ODB_LIST_CHANGE_SHAPE(list, serial, item) { \
   odb_shape_struc *_temp = item; \
   odb_status = odb__list_change(list, serial, _temp, ODB_L_LIST_TYPE_SHAPE); \
   ODB_STATUS_REPORT(ODB_LIST_CHANGE_SHAPE); \
}

#define ODB_LIST_FIRST_SHAPE(list,  item) { \
   odb_shape_struc *_temp = item; \
   odb_status = odb__list_first(list, _temp, ODB_L_LIST_TYPE_SHAPE); \
   ODB_STATUS_REPORT(ODB_LIST_FIRST_SHAPE); \
}

#define ODB_LIST_LAST_SHAPE(list,  item) { \
   odb_shape_struc *_temp = item; \
   odb_status = odb__list_last(list, _temp, ODB_L_LIST_TYPE_SHAPE); \
   ODB_STATUS_REPORT(ODB_LIST_LAST_SHAPE); \
}

#define ODB_LIST_COPY_SHAPE(_mode_type, item, _list_p) { \
   odb_shape_struc *_temp = item;                                    \
   odb_status = odb__list_copy_scalar(_mode_type,              \
       ODB_L_LIST_TYPE_SHAPE, _temp, &(_list_p)  );            \
   ODB_STATUS_REPORT(ODB_LIST_COPY_SHAPE);               \
}

/**************** F Declarations ******************/

#define ODB_LIST_ADD_F(list, item) { \
   odb_f_struc *_temp = item; \
   odb_status = odb__list_add(list, _temp, ODB_L_LIST_TYPE_F); \
   ODB_STATUS_REPORT(ODB_LIST_ADD_F); \
}

#define ODB_LIST_GET_F(list, serial, item) { \
   odb_f_struc *_temp = item; \
   odb_status = odb__list_get(list, &(serial), _temp, ODB_L_LIST_TYPE_F); \
   ODB_STATUS_REPORT(ODB_LIST_GET_F); \
}

#define ODB_LIST_CHANGE_F(list, serial, item) { \
   odb_f_struc *_temp = item; \
   odb_status = odb__list_change(list, serial, _temp, ODB_L_LIST_TYPE_F); \
   ODB_STATUS_REPORT(ODB_LIST_CHANGE_F); \
}

#define ODB_LIST_FIRST_F(list,  item) { \
   odb_f_struc *_temp = item; \
   odb_status = odb__list_first(list, _temp, ODB_L_LIST_TYPE_F); \
   ODB_STATUS_REPORT(ODB_LIST_FIRST_F); \
}

#define ODB_LIST_LAST_F(list,  item) { \
   odb_f_struc *_temp = item; \
   odb_status = odb__list_last(list, _temp, ODB_L_LIST_TYPE_F); \
   ODB_STATUS_REPORT(ODB_LIST_LAST_F); \
}

#define ODB_LIST_COPY_F(_mode_type, item, _list_p) { \
   odb_f_struc *_temp = item;                                    \
   odb_status = odb__list_copy_scalar(_mode_type,              \
       ODB_L_LIST_TYPE_F, _temp, &(_list_p)  );            \
   ODB_STATUS_REPORT(ODB_LIST_COPY_F);               \
}

/**************** NAME Declarations ******************/

#define ODB_LIST_ADD_NAME(list, item) { \
   void *_temp = item; \
   odb_status = odb__list_add(list, _temp, ODB_L_LIST_TYPE_NAME); \
   ODB_STATUS_REPORT(ODB_LIST_ADD_NAME); \
}

#define ODB_LIST_GET_NAME(list, serial, item) { \
   void *_temp = item; \
   odb_status = odb__list_get(list, &(serial), _temp, ODB_L_LIST_TYPE_NAME); \
   ODB_STATUS_REPORT(ODB_LIST_GET_NAME); \
}

#define ODB_LIST_CHANGE_NAME(list, serial, item) { \
   void *_temp = item; \
   odb_status = odb__list_change(list, serial, _temp, ODB_L_LIST_TYPE_NAME); \
   ODB_STATUS_REPORT(ODB_LIST_CHANGE_NAME); \
}

#define ODB_LIST_FIRST_NAME(list,  item) { \
   void *_temp = item; \
   odb_status = odb__list_first(list, _temp, ODB_L_LIST_TYPE_NAME); \
   ODB_STATUS_REPORT(ODB_LIST_FIRST_NAME); \
}

#define ODB_LIST_LAST_NAME(list,  item) { \
   void *_temp = item; \
   odb_status = odb__list_last(list, _temp, ODB_L_LIST_TYPE_NAME); \
   ODB_STATUS_REPORT(ODB_LIST_LAST_NAME); \
}

#define ODB_LIST_COPY_NAME(_mode_type, item, _list_p) { \
   void *_temp = item;                                    \
   odb_status = odb__list_copy_scalar(_mode_type,              \
       ODB_L_LIST_TYPE_NAME, _temp, &(_list_p)  );            \
   ODB_STATUS_REPORT(ODB_LIST_COPY_NAME);               \
}

/**************** INT Declarations ******************/

#define ODB_LIST_ADD_INT(list, item) { \
   int _temp = item; \
   odb_status = odb__list_add(list, &_temp, ODB_L_LIST_TYPE_INT); \
   ODB_STATUS_REPORT(ODB_LIST_ADD_INT); \
}

#define ODB_LIST_GET_INT(list, serial, item) { \
   int *_temp = &item; \
   odb_status = odb__list_get(list, &(serial), _temp, ODB_L_LIST_TYPE_INT); \
   ODB_STATUS_REPORT(ODB_LIST_GET_INT); \
}

#define ODB_LIST_CHANGE_INT(list, serial, item) { \
   int _temp = item; \
   odb_status = odb__list_change(list, serial, &_temp, ODB_L_LIST_TYPE_INT); \
   ODB_STATUS_REPORT(ODB_LIST_CHANGE_INT); \
}

#define ODB_LIST_FIRST_INT(list,  item) { \
   int *_temp = &item; \
   odb_status = odb__list_first(list, _temp, ODB_L_LIST_TYPE_INT); \
   ODB_STATUS_REPORT(ODB_LIST_FIRST_INT); \
}

#define ODB_LIST_LAST_INT(list,  item) { \
   int *_temp = &item; \
   odb_status = odb__list_last(list, _temp, ODB_L_LIST_TYPE_INT); \
   ODB_STATUS_REPORT(ODB_LIST_LAST_INT); \
}

#define ODB_LIST_COPY_INT(_mode_type, item, _list_p) { \
   int _temp = item;                                    \
   odb_status = odb__list_copy_scalar(_mode_type,              \
       ODB_L_LIST_TYPE_INT, &_temp, &(_list_p)  );            \
   ODB_STATUS_REPORT(ODB_LIST_COPY_INT);               \
}

/**************** DOUBLE Declarations ******************/

#define ODB_LIST_ADD_DOUBLE(list, item) { \
   double _temp = item; \
   odb_status = odb__list_add(list, &_temp, ODB_L_LIST_TYPE_DOUBLE); \
   ODB_STATUS_REPORT(ODB_LIST_ADD_DOUBLE); \
}

#define ODB_LIST_GET_DOUBLE(list, serial, item) { \
   double *_temp = &item; \
   odb_status = odb__list_get(list, &(serial), _temp, ODB_L_LIST_TYPE_DOUBLE); \
   ODB_STATUS_REPORT(ODB_LIST_GET_DOUBLE); \
}

#define ODB_LIST_CHANGE_DOUBLE(list, serial, item) { \
   double _temp = item; \
   odb_status = odb__list_change(list, serial, &_temp, ODB_L_LIST_TYPE_DOUBLE); \
   ODB_STATUS_REPORT(ODB_LIST_CHANGE_DOUBLE); \
}

#define ODB_LIST_FIRST_DOUBLE(list,  item) { \
   double *_temp = &item; \
   odb_status = odb__list_first(list, _temp, ODB_L_LIST_TYPE_DOUBLE); \
   ODB_STATUS_REPORT(ODB_LIST_FIRST_DOUBLE); \
}

#define ODB_LIST_LAST_DOUBLE(list,  item) { \
   double *_temp = &item; \
   odb_status = odb__list_last(list, _temp, ODB_L_LIST_TYPE_DOUBLE); \
   ODB_STATUS_REPORT(ODB_LIST_LAST_DOUBLE); \
}

#define ODB_LIST_COPY_DOUBLE(_mode_type, item, _list_p) { \
   double _temp = item;                                    \
   odb_status = odb__list_copy_scalar(_mode_type,              \
       ODB_L_LIST_TYPE_DOUBLE, &_temp, &(_list_p)  );            \
   ODB_STATUS_REPORT(ODB_LIST_COPY_DOUBLE);               \
}

/**************** LAYER Declarations ******************/

#define ODB_LIST_ADD_LAYER(list, item) { \
   odb_obj_desc_struc _temp = item; \
   odb_status = odb__list_add(list, &_temp, ODB_L_LIST_TYPE_LAYER); \
   ODB_STATUS_REPORT(ODB_LIST_ADD_LAYER); \
}

#define ODB_LIST_GET_LAYER(list, serial, item) { \
   odb_obj_desc_struc *_temp = &item; \
   odb_status = odb__list_get(list, &(serial), _temp, ODB_L_LIST_TYPE_LAYER); \
   ODB_STATUS_REPORT(ODB_LIST_GET_LAYER); \
}

#define ODB_LIST_CHANGE_LAYER(list, serial, item) { \
   odb_obj_desc_struc _temp = item; \
   odb_status = odb__list_change(list, serial, &_temp, ODB_L_LIST_TYPE_LAYER); \
   ODB_STATUS_REPORT(ODB_LIST_CHANGE_LAYER); \
}

#define ODB_LIST_FIRST_LAYER(list,  item) { \
   odb_obj_desc_struc *_temp = &item; \
   odb_status = odb__list_first(list, _temp, ODB_L_LIST_TYPE_LAYER); \
   ODB_STATUS_REPORT(ODB_LIST_FIRST_LAYER); \
}

#define ODB_LIST_LAST_LAYER(list,  item) { \
   odb_obj_desc_struc *_temp = &item; \
   odb_status = odb__list_last(list, _temp, ODB_L_LIST_TYPE_LAYER); \
   ODB_STATUS_REPORT(ODB_LIST_LAST_LAYER); \
}

#define ODB_LIST_COPY_LAYER(_mode_type, item, _list_p) { \
   odb_obj_desc_struc _temp = item;                                    \
   odb_status = odb__list_copy_scalar(_mode_type,              \
       ODB_L_LIST_TYPE_LAYER, &_temp, &(_list_p)  );            \
   ODB_STATUS_REPORT(ODB_LIST_COPY_LAYER);               \
}

/**************** NEIGHBOR Declarations ******************/

#define ODB_LIST_ADD_NEIGHBOR(list, item) { \
   odb_neighbor_struc *_temp = item; \
   odb_status = odb__list_add(list, _temp, ODB_L_LIST_TYPE_NEIGHBOR); \
   ODB_STATUS_REPORT(ODB_LIST_ADD_NEIGHBOR); \
}

#define ODB_LIST_GET_NEIGHBOR(list, serial, item) { \
   odb_neighbor_struc *_temp = item; \
   odb_status = odb__list_get(list, &(serial), _temp, ODB_L_LIST_TYPE_NEIGHBOR); \
   ODB_STATUS_REPORT(ODB_LIST_GET_NEIGHBOR); \
}

#define ODB_LIST_CHANGE_NEIGHBOR(list, serial, item) { \
   odb_neighbor_struc *_temp = item; \
   odb_status = odb__list_change(list, serial, _temp, ODB_L_LIST_TYPE_NEIGHBOR); \
   ODB_STATUS_REPORT(ODB_LIST_CHANGE_NEIGHBOR); \
}

#define ODB_LIST_FIRST_NEIGHBOR(list,  item) { \
   odb_neighbor_struc *_temp = item; \
   odb_status = odb__list_first(list, _temp, ODB_L_LIST_TYPE_NEIGHBOR); \
   ODB_STATUS_REPORT(ODB_LIST_FIRST_NEIGHBOR); \
}

#define ODB_LIST_LAST_NEIGHBOR(list,  item) { \
   odb_neighbor_struc *_temp = item; \
   odb_status = odb__list_last(list, _temp, ODB_L_LIST_TYPE_NEIGHBOR); \
   ODB_STATUS_REPORT(ODB_LIST_LAST_NEIGHBOR); \
}

#define ODB_LIST_COPY_NEIGHBOR(_mode_type, item, _list_p) { \
   odb_neighbor_struc *_temp = item;                                    \
   odb_status = odb__list_copy_scalar(_mode_type,              \
       ODB_L_LIST_TYPE_NEIGHBOR, _temp, &(_list_p)  );            \
   ODB_STATUS_REPORT(ODB_LIST_COPY_NEIGHBOR);               \
}

/**************** FUNC Declarations ******************/

#define ODB_LIST_ADD_FUNCTION(list, item) { \
    odb_obj_desc_struc _temp = item; \
    odb_status = odb__list_add(list, &_temp, ODB_L_LIST_TYPE_FUNCTION); \
    ODB_STATUS_REPORT(ODB_LIST_ADD_FUNCTION); \
   }

#define ODB_LIST_GET_FUNCTION(list, serial, item) { \
    odb_obj_desc_struc *_temp = &item; \
    odb_status = odb__list_get(list, &(serial), _temp, ODB_L_LIST_TYPE_FUNCTION); \
    ODB_STATUS_REPORT(ODB_LIST_GET_FUNCTION); \
   }

#define ODB_LIST_CHANGE_FUNCTION(list, serial, item) { \
    odb_obj_desc_struc _temp = item; \
    odb_status = odb__list_change(list, serial, &_temp, ODB_L_LIST_TYPE_FUNCTION); \
    ODB_STATUS_REPORT(ODB_LIST_CHANGE_FUNCTION); \
   }

#define ODB_LIST_FIRST_FUNCTION(list,  item) { \
    odb_obj_desc_struc *_temp = &item; \
    odb_status = odb__list_first(list, _temp, ODB_L_LIST_TYPE_FUNCTION); \
    ODB_STATUS_REPORT(ODB_LIST_FIRST_FUNCTION); \
   }

#define ODB_LIST_LAST_FUNCTION(list,  item) { \
    odb_obj_desc_struc *_temp = &item; \
    odb_status = odb__list_last(list, _temp, ODB_L_LIST_TYPE_FUNCTION); \
    ODB_STATUS_REPORT(ODB_LIST_LAST_FUNCTION); \
   }

#define ODB_LIST_COPY_FUNCTION(_mode_type, item, _list_p) {       \
    odb_obj_desc_struc _temp = item;                           \
    odb_status = odb__list_copy_scalar(_mode_type,             \
    ODB_L_LIST_TYPE_FUNCTION, &_temp, &(_list_p)  );           \
    ODB_STATUS_REPORT(ODB_LIST_COPY_FUNCTION);                    \
   }


#endif /*ODB_PUBLIC_OO*/

