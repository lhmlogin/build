/****************************************************
   
                 lib_utils.h

 Purpose : Provide general utilities (strings etc.)
  Written by Moshik, Valor
  
****************************************************/

#ifndef LIB_UTILS_H

//This is the definition of the Feature Properties used by all the DFMs.
//Each property to be used should be defined here!!!
//Keep logical order of the names, BUT NEVER CHANGE A NUMBER DEFINED (in case it is saved with the data)
//This is the range allocated for DFM usage.
//  DML_PROPERTY_DFMPE_START = 50000
//  DML_PROPERTY_DFMPE_END = 65530
typedef enum
{
    //First should start with 50000

    //SLR range: 50000 to 50250
    ODB_F_PROPERTY_SLR_ORIG_AR	= 50000,    //IL 14/02/2016 BUG65827 - use Feature Properties instead of "..slr_orig_ar"

    //Ranges for other new DFMs supported should be added here:

    //These are defined for unit testing - don't use numbers after these
    ODB_F_PROPERTY_TEST_INT	= 65527,    //for test purposes
    ODB_F_PROPERTY_TEST_DOUBLE	= 65528,    //for test purposes
    ODB_F_PROPERTY_TEST_BOOLEAN	= 65529,    //for test purposes
    ODB_F_PROPERTY_LAST		= 65530	    //THIS MUST BE LAST - don't add anything beyond it! 
} odb_f_properties_index_enum;

typedef struct{
    int *utils_use_array;
    int utils_use_array_size;
}lib_utils_global_struct;

#ifdef __cplusplus
extern "C" {
#endif

ODB_EXPORT int lib_utils_init_global_struct(lib_utils_global_struct* lib_utils_global_struct_p);
ODB_EXPORT int lib_utils_delete_global_struct(lib_utils_global_struct* lib_utils_global_struct_p);
ODB_EXPORT int lib_utils_str_match(char *name, char *pattern, boolean *match_p);
ODB_EXPORT int lib_utils_search_init(int use_array_num);
ODB_EXPORT int lib_utils_search_close(void);
ODB_EXPORT int lib_utils_set(int num);
ODB_EXPORT int lib_utils_is_same_layers(ODB_P_LAYER(ld1), ODB_P_LAYER(ld2), boolean* same);   
ODB_EXPORT int lib_utils_find(int num, int *found);
ODB_EXPORT int lib_utils_gen_search_init(int **use_array, int *use_array_size_p,
                                         int use_array_num);
ODB_EXPORT int lib_utils_gen_search_close(int *use_array);
ODB_EXPORT int lib_utils_gen_set(int *use_array, int use_array_size, int num);
ODB_EXPORT int lib_utils_gen_find(int *use_array, int use_array_size, int num,
                                  int *found_p);
ODB_EXPORT int lib_utils_copy_f_attr(int nf_src, ODB_P_LAYER( ld_src ),
                                     int nf_dst, ODB_P_LAYER( ld_dst ));
ODB_EXPORT int lib_utils_get_attrs_list(char *attrs_str, ODB_P_LIST(attrs_lst));
ODB_EXPORT int lib_utils_get_attrs_list_values(char *attrs_str, ODB_P_LIST(attrs_lst),ODB_P_LIST(attrs_values));
ODB_EXPORT int lib_utils_check_shape_attrs(ODB_P_SHAPE(shape), ODB_P_LIST(attrs_lst),
                                           boolean *found_p);
ODB_EXPORT int lib_utils_filter_shape_list_by_attrs_values(ODB_P_LIST(shape_list), 
				       ODB_P_LIST(attrs_lst),
				       ODB_P_LIST(attrs_values),
				       int units,
				       boolean *filtered); 
ODB_EXPORT int lib_utils_check_shape_attrs_values(ODB_P_SHAPE(shape), ODB_P_LIST(attrs_lst),ODB_P_LIST(attrs_values),
                                                  int units ,boolean *found_p);
ODB_EXPORT int lib_utils_check_f_attrs(ODB_P_F(f), ODB_P_LIST(attrs_lst), boolean *found_p);
ODB_EXPORT int lib_utils_check_nf_attrs(ODB_P_LAYER(ld), int nf, ODB_P_LIST(attrs_lst), boolean *found_p);
ODB_EXPORT int lib_utils_check_nf_attrs_values(ODB_P_LAYER(ld), int nf, ODB_P_LIST(attrs_lst),ODB_P_LIST(attrs_values),
					      int units,  boolean *found_p);
ODB_EXPORT int lib_utils_get_exclusion_areas_lst(ODB_P_LAYER(ld),
                                                 ODB_P_LIST(exclusion_areas_lst),
                                                 boolean *use_areas_to_exclusion_p);
ODB_EXPORT int lib_utils_get_layer_attrs_lst(ODB_P_LAYER(ld),
                                             ODB_P_LIST(global_attrs_lst),
                                             ODB_P_LIST(ld_attrs_lst));
ODB_EXPORT int lib_utils_get_layer_attrs_values_lst(ODB_P_LAYER(ld), 
						    ODB_P_LIST(global_attrs_lst),
						    ODB_P_LIST(global_attrs_values_lst),
						    ODB_P_LIST(ld_attrs_lst),
						    ODB_P_LIST(ld_attrs_values_lst)); 
ODB_EXPORT int lib_utils_mask_layer_summary(ODB_P_LAYER(ld));

ODB_EXPORT int lib_utils_create_tmp_layer( ODB_P_LAYER( *ld ) );
ODB_EXPORT int lib_utils_create_tmp_layer_preffix(odb_name layer_preffix, ODB_P_LAYER( *ld ) );

ODB_EXPORT int lib_utils_get_max_nf( ODB_P_LAYER( layer ), int* max_nf_p );
ODB_EXPORT int lib_utils_find_int_in_list( ODB_P_LIST( int_lst ), int int_to_check, boolean* found_p );

ODB_EXPORT int lib_utils_get_srl_max_nf( ODB_P_SRL( layer ), int* max_nf_p ); 

ODB_EXPORT int lib_utils_find_reference_sm_layers( ODB_P_LAYER( layer ), ODB_P_LIST(*sm_lyrs_lst), boolean* is );
ODB_EXPORT int lib_utils_get_drill_type(ODB_P_LAYER(ld),
					int nf,
					boolean check_layer_type,
					odb_drill_type_enum *drill_type_p,
					odb_via_type_enum   *via_type_p,
					boolean             *is_ok_p);
ODB_EXPORT int lib_utils_is_drill_layer(ODB_P_LAYER(ld),
					boolean *is_drill_p);

ODB_EXPORT int lib_utils_update_cont_list_by_profile(ODB_P_LAYER(sig_layer), ODB_P_LAYER(gold_mask_layer), ODB_P_LIST(shape_list));

ODB_EXPORT int lib_utils_check_is_deleted_nf(ODB_P_LAYER(ld), int nf, int* is_deleted_p);

ODB_EXPORT int lib_utils_are_layers_identical(ODB_P_LAYER(ld1), ODB_P_LAYER(ld2), boolean* are_identical_p);
ODB_EXPORT int lib_utils_are_shapes_identical(ODB_P_SHAPE(shape1), ODB_P_SHAPE(shape2), boolean* are_identical_p);

ODB_EXPORT boolean lib_utils_is_symbol_s(odb_name sym_name);


ODB_EXPORT int lib_utils_flatten_layers(ODB_P_LIST(layer_list), ODB_P_LIST(biggest_nf_list));
ODB_EXPORT int lib_utils_undo_flatten_layers(ODB_P_LIST(layer_list), ODB_P_LIST(biggest_nf_list));
ODB_EXPORT int lib_utils_get_array_pcbs(ODB_P_LAYER(ld), ODB_P_LIST(array_steps), ODB_P_LIST(pcb_steps));
ODB_EXPORT int lib_utils_create_srl_lists(ODB_P_LAYER(ld), ODB_P_LIST(arrays_name), ODB_P_LIST(pcbs_name),ODB_P_LIST(array_srl_lst), ODB_P_LIST(pcb_srl_lst));
ODB_EXPORT int lib_utils_flatten_componet_layers(ODB_P_LIST(componet_layer_list), ODB_P_LIST(*componet_replace_layer_list));
ODB_EXPORT int lib_utils_shape_list_near_layer(ODB_P_LIST(shape_list), ODB_P_LAYER(target_layer), int  search_dist, ODB_P_LIST(result_list));
ODB_EXPORT void lib_utils_trim(char *s);



#ifdef __cplusplus
}
#endif


#define LIB_UTILS_H
#endif 
  
