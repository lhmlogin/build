/****************************************************
   
                 lib_attr.h

 Purpose : Provide services for report attributes

 Written by Ben Michelson, Valor
  
 Abbreviations:
    rm   - reliability margin
    typ  - typical
    cat  - category
    dra  - design registration allowance MAX((min - rm), 0)
    def  - definition
    attr - attribute

****************************************************/

#ifndef LIB_ATTR_H

/****************************************************

   The following structure contains the definition
   of all the attributes of a category

   the ``unsigned int'' fields receive boolean values
   
****************************************************/
   
typedef struct {
   char         *cat_name; /* Name of category */
   int           cat;      /* Number of category */
   int           rm;       /* Reliability margin, used only if dra == TRUE */
   unsigned int  count:1;  /* Output count            */
   unsigned int  dra  :1;  /* Output dra (design registration allowance) */
   unsigned int  min  :1;  /* Output minimum value    */
   unsigned int  typ  :1;  /* Output typical value    */
   unsigned int  max  :1;  /* Output maximum value    */
   int           spare:27; /* Not used                */
} lib_attr_def_struc;

typedef enum p_type
{
	p_round = 0,
	p_rect,
	p_oval,
	p_square,
	p_other,
}p_type;

typedef struct
{
	double size;
	int count;
	p_type type;
	char str[50]; /* if type = round , record r, if rect/oval record its H & W */
} lib_size_data_struct;
/****************************************************

   The following structure contains the results
   of the values of attributes computed for a
   specific category
   (returned by lib_attr_write())
   
****************************************************/
typedef struct {
   int count;
   int dra;
   int min;
   int typ;
   int max;
   int spare[9];
} lib_attr_struc;

/****************************************************
   
                lib_attr_write_dsize

Description:
   Add measurement attribute of type ``double''
   
Input:  layer - layer id of attribute, 
                ODB_L_LAYER_NULL if not of particular layer
        name  - name of attribute.
                Prefix of layer name added if ``layer'' is non-null.
        size  - size of attribute, in odb pixel units.
Output: none
****************************************************/
ODB_EXPORT int lib_attr_write_dsize(ODB_P_LAYER(layer), char *name, double size);

/****************************************************
                lib_attr_get_res_attr_name

Description:
   Forms attribute name as xxxxx_yyyyyzzzzz
   where: xxxxx - layer name
	  yyyyy - symbol name
	  zzzzz - name of attribute
   
Input:  layer_name - layer name, 
	sym_name   - symbol name or NULL
        name       - name of attribute.

Output: attr_name  - result attribute name
****************************************************/
ODB_EXPORT int lib_attr_get_res_attr_name (char *layer_name, char *sym_name, char *name, char *attr_name);


/****************************************************
   
                lib_attr_write_size

Description:
   Add measurement attribute of type ``int''
   
Input:  layer - layer id of attribute, 
                ODB_L_LAYER_NULL if not of particular layer
        name  - name of attribute.
                Prefix of layer name added if ``layer'' is non-null.
        size  - size of attribute, in odb pixel units.
Output: none
****************************************************/
ODB_EXPORT int lib_attr_write_size (ODB_P_LAYER(layer), char *name, int size);

/****************************************************
   
                lib_attr_write_count

Description:
   Add count attribute
   
Input:  layer - layer id of attribute, 
                ODB_L_LAYER_NULL if not of particular layer
        name  - name of attribute.
                Prefix of layer name added if ``layer'' is non-null.
        count - Number of items counted
Output: none
****************************************************/
ODB_EXPORT int lib_attr_write_count(ODB_P_LAYER(layer), char *name, int count);

/****************************************************

lib_attr_write_list

Description:
Add count attribute

Input:  layer - layer id of attribute, 
ODB_L_LAYER_NULL if not of particular layer
name  - name of attribute.
Prefix of layer name added if ``layer'' is non-null.
count - Number of items counted
Output: none
****************************************************/
ODB_EXPORT int lib_attr_write_list( ODB_P_LIST(layer_list), 
				    odb_name layer_list_name,
				    lib_attr_def_struc *attr_def,
				    lib_attr_struc     *attr_p);

/****************************************************
   
                     lib_attr_write

Description:
   Calculate & add an attributes of a specific category
   of results
   
Input:  layer     - layer id of attribute, 
                    ODB_L_LAYER_NULL if not of particular layer
        attr_def  - definition of attribute.
Output: 
        attr_p    - Values of attribute calculated
****************************************************/
ODB_EXPORT int lib_attr_write(ODB_P_LAYER(layer), 
			  lib_attr_def_struc *attr_def,
			  lib_attr_struc     *attr_p);


/****************************************************

lib_attr_write_one_cat_list

Description:
Calculate & add an attributes of a specific category
of results only one category

Input:  layer     - layer id of attribute, 
ODB_L_LAYER_NULL if not of particular layer
attr_def  - definition of attribute.
Output: 
attr_p    - Values of attribute calculated
****************************************************/
ODB_EXPORT int lib_attr_write_one_cat_list(ODB_P_LIST(layer_list),
					   odb_name layer_list_name, 
					   lib_attr_def_struc *attr_def,
					   lib_attr_struc     *attr_p);

/****************************************************

write_one_cat

Description:
Calculate & add an attributes of a specific category
of results only one category

Input:  layer     - layer id of attribute, 
ODB_L_LAYER_NULL if not of particular layer
attr_def  - definition of attribute.
Output: 
        attr_p    - Values of attribute calculated
****************************************************/
ODB_EXPORT int lib_attr_write_one_cat(ODB_P_LAYER(layer), lib_attr_def_struc *attr_def,
	lib_attr_struc     *attr_p, char* orig_cat_name, int orig_cat_num);

static int find_pad(ODB_P_LAYER(ld), ODB_P_SHAPE(limits), ODB_P_SHAPE(pad), boolean* get_pad);
static int check_pad_type(ODB_P_SHAPE(pad), p_type* type);
   
#define LIB_ATTR_H
#endif 
  
