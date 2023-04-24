/*************************************************
 *
 * Module  :     shape.h
 *
 * Purpose :     Provide common services for shapes
 *
 * Functions: 
 *    lib_shape_point_dist         -- Euclidean distance between 2 points
 *    lib_shape_point2point        -- converts a point_struc to a shape
 *    lib_shape_coordinates2point  -- converts 2 coordinates to a shape-point.
 *    lib_shape_points2seg         -- converts 2 points to a seg
 *    lib_shape_points2line        -- converts 2 points to a line
 *    lib_shape_seg_len            -- length of a seg
 *    lib_shape_selected           -- tells whether a shape is selected
 *    lib_shape_ext_seg            -- change segment length ( and possibly direction )
 *    lib_shape_ext_curve          -- change curve length ( and possibly direction )
 *    lib_shape_grow_seg           -- change segment length Symmetricaly
 *    lib_shape_grow_curve         -- change curve length Symmetricaly
 *    lib_shape_line2line_sin      -- returns sin between two lines
 *    lib_shape_line2line_cos      -- returns cos between two lines
 *    lib_shape_list_limit         -- limit box for a list of shapes
 *    lib_shape_move               -- move shape 
 *    lib_shape_area               -- calculate shape area
 *    lib_shape2f                  -- convert shape into a feature. 
 *    lib_find_shape_on_other_edge -- Finds the shape over which the measurement
 *                                    is being calculated
 *    lib_shape_end_line_seg       -- get the segment at the end of line (diameter of circle
 *                                    when line is round)
 *    lib_shape_thermal_cut_sep    -- Cuts the second shape from the list in two.
 *                                    In use by pg.c and pgo.c
 *    lib_shape_move_from_shape    -- we can move seg from shape or from point	
 *
 * Usage :
 *    Copy the prototypes below
 * 
 * Written by:  Ben Michelson, Valor Ltd
 *
 **************************************************/

typedef enum { L_VERT, L_HOR, L_DIAG, L_POINT} seg_type_enum;

typedef enum 
{
    NEIGHBOR_ABOVE_DIST  = 1, 
    NEIGHBOR_BELOW_DIST	 = 2,
}pp_neig_dist_relation_enum;

typedef enum {
    SLOT_F_TYPE_PAD = 1,
    SLOT_F_TYPE_LINE,
} slot_f_type_enum;

typedef enum {
    SYM_TYPE_ROUND,
    SYM_TYPE_OVAL,
} sym_type_enum;

/*28/03/2007 IL: To suport link with static library and cpp code*/
#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#define EPS 100
/* ----------------------------------------------------------------
 *          lib_shape_points2vec     BL 13.03.03 
 *
 * Receives two points and constructs a point that represents
 * vector from first to second
 * (used by spacing_opt.c)
 */
ODB_EXPORT int lib_shape_points2vec(odb_point_struc ps, odb_point_struc pe,
				    ODB_P_SHAPE( vec ));

/* ----------------------------------------------------------------
 *          lib_shape_vec_sum     BL 13.03.03 
 *
 * Sum two vectors with multiplier coefficient
 * (used by spacing_opt.c)
 */
ODB_EXPORT int lib_shape_vec_sum(ODB_P_SHAPE( vec1 ), ODB_P_SHAPE( vec2 ), double mult,
				 ODB_P_SHAPE( sum ));

/* ----------------------------------------------------------------
 *          lib_shape_point_shift     BL 13.03.03 
 *
 * Shift point on vector direction by multiplier coefficient
 * Vector direction is normalized by length len
 * (used by spacing_opt.c)
 */
ODB_EXPORT int lib_shape_point_shift(ODB_P_SHAPE( pt ), ODB_P_SHAPE( vec ), double len, double mult,
				     ODB_P_SHAPE( new_pt ));

/* ----------------------------------------------------------------
 *          lib_shape_vec_scalar     BL 13.03.03 
 *
 * Calculate scalar production of two vectors
 * (used by spacing_opt.c)
 */
ODB_EXPORT int lib_shape_vec_scalar(ODB_P_SHAPE( vec1 ), 
				    ODB_P_SHAPE( vec2 ), double *sp_p);

/*
 *        lib_shape_point_dist
 *
 * Finds the distance between 2 points
 *
 */
ODB_EXPORT int lib_shape_point_dist(odb_point_struc p1, 
				odb_point_struc p2, 
				int *length_p);

/* 
  Find projection of point pt 
  on segment or line shape. The returned distance
  is the distance from the start point of
  the segment to the point on the segment
  which is closest to pt.
  */
ODB_EXPORT int lib_shape_project_point(odb_point_struc *pt,
				    ODB_P_SHAPE(shape), 
				    int *d_p );

/*
 *             lib_shape_project_point_vdist
 *
 * Find projection of point pt 
 * on segment or line shape. The returned distance
 * is the distance from the input point to the projection point
 *
 */
ODB_EXPORT int lib_shape_project_point_vdist(odb_point_struc *pt,
                                             ODB_P_SHAPE(shape),
                                             int *d_p);
   
/*
 *             lib_shape_point2point
 *
 * Receives a point_struc and constructs a shape from it
 *
 */
ODB_EXPORT int lib_shape_point2point(odb_point_struc p, ODB_P_SHAPE(point));

/*
 *          lib_shape_points2seg
 *
 * Receives two points and constructs a segment
 * shape from them.
 *
 */
ODB_EXPORT int lib_shape_points2seg(odb_point_struc ps,
				odb_point_struc pe, 
				ODB_P_SHAPE(seg));

/*
 *  lib_shape_points2line
 *
 *  Receives two points, a radius and a cap and
 *  constructs a line shape from them.
 *
 */
ODB_EXPORT int lib_shape_points2line(odb_point_struc ps, 
			 odb_point_struc  pe,
			 int r,
			 odb_cap_enum cap,
			 ODB_P_SHAPE(line));

/*
 *    lib_shape_seg_len
 *
 * Finds the length of a seg
 *
 */
ODB_EXPORT int lib_shape_seg_len(ODB_P_SHAPE(seg), int *length_p);

/*
 * lib_shape_curve_len - Finds the length of a curve
 */

ODB_EXPORT int lib_shape_curve_len(ODB_P_SHAPE(curve), int *length_p);

/*
 * lib_shape_edge_len - Finds the length of a edge
 */

ODB_EXPORT int lib_shape_edge_len( ODB_P_SHAPE(edge), int *length_p);

/*
 *          lib_shape_selected
 *
 * Returns whether the feature associated with a shape is selected.
 *
 */
ODB_EXPORT int lib_shape_selected(ODB_P_SHAPE(shape), boolean *selected_p);

/*
*          lib_shape_area_intersect_list
*
* Wintersact shape with list
*
*/
ODB_EXPORT int lib_shape_area_intersect_list(ODB_P_SHAPE(shape),
					    ODB_P_LIST (in_list),
					    ODB_P_LIST (out_list));
/*
 *          lib_shape_widen_line
 *
 * Widens a line without lengthening it
 *
 */
ODB_EXPORT int lib_shape_widen_line(ODB_P_SHAPE(line), int add);

/*
 *          lib_shape_make_line_without_caps
 *
 * Gets a round-cap line and returns a square-cap line that has the area
 * of the original line without the caps (shorter by R from each side)
 * If shape is not line, not round or not long enough, original line remains as is
 *
 */
ODB_EXPORT int lib_shape_make_line_without_caps(ODB_P_SHAPE(line));


/*
 *    lib_shape_ext_seg
 *
 *   Change segment's length to 'ABS(new_len)' and if 
 *   'new_len' is negative exchange the segment's
 *   end points (change its direction). The function
 *   changes the end point.
 *
 */
ODB_EXPORT int lib_shape_ext_seg(ODB_P_SHAPE(seg), int new_len);


/*
 *    lib_shape_ext_curve
 *
 *   Change curve's length to 'ABS(new_len)' and if 
 *   'new_len' is negative exchange the segment's
 *   end points (change its direction). The function
 *   changes the end point.
 *
 */
ODB_EXPORT int lib_shape_ext_curve(ODB_P_SHAPE(curve_shape), int new_len,boolean* is_ok);

/*
 *    lib_shape_ext_edge
 *
 *   Change segment/curve's length to 'ABS(new_len)' and if 
 *   'new_len' is negative exchange the segment's
 *   end points (change its direction). The function
 *   changes the end point.
 *
 */
ODB_EXPORT int lib_shape_ext_edge(ODB_P_SHAPE(edge_shape), int new_len, boolean* is_ok);

/*
 *    lib_shape_ext_seg_ps
 *
 *   Change segment's length to 'ABS(new_len)' and if 
 *   'new_len' is negative exchange the segment's
 *   start points (change its direction). The function
 *   changes the start point.
 *
 */
ODB_EXPORT int lib_shape_ext_seg_ps(ODB_P_SHAPE(seg), int new_len);


/*
 *    lib_shape_ext_curve_ps
 *
 *   Change curve's length to 'ABS(new_len)' and if 
 *   'new_len' is negative exchange the segment's
 *   start points (change its direction). The function
 *   changes the start point.
 *
 */
ODB_EXPORT int lib_shape_ext_curve_ps(ODB_P_SHAPE(curve_shape), int new_len,boolean* is_ok);

/*
 *    lib_shape_ext_edge_ps
 *
 *   Change segment/curve's length to 'ABS(new_len)' and if 
 *   'new_len' is negative exchange the segment's
 *   start points (change its direction). The function
 *   changes the start point.
 *
 */
ODB_EXPORT int lib_shape_ext_edge_ps(ODB_P_SHAPE(edge_shape), int new_len, boolean* is_ok);

/*
 *    lib_shape_change_edge_direction
 *
 *   Changes the direction of the given segment/curve's, keeping the same graphical representation.
 *   Changes between it ps and pe
 *
 */
ODB_EXPORT int lib_shape_change_edge_direction(ODB_P_SHAPE(edge_shape));

/* 
 *    lib_shape_ext_seg_to_shape
 *
 *    Extend a given segment until it touches the given shape
 */
ODB_EXPORT int lib_shape_ext_seg_to_shape(ODB_P_SHAPE	(seg), 
					  ODB_P_SHAPE	(shape), 
					  int		max_ext, 
					  boolean	extend_ps,
					  boolean	allow_shrink,
					  double	ext2max_ratio_prefer_shrink,
					  boolean	extend_touching,
					  boolean	*is_ok_p);


/*
 *    lib_shape_grow_seg
 *
 *   Change segment's length to 'ABS(new_len)'
 *   Segments grows/shrinks symmetrically to both ends
 *
 */
ODB_EXPORT int lib_shape_grow_seg(ODB_P_SHAPE(seg), int new_len);

/*
 *    lib_shape_grow_curve
 *
 *   Change curve's length to 'ABS(new_len)'
 *   Curves grows/shrinks symmetrically to both ends
 *
 */
ODB_EXPORT int lib_shape_grow_curve(ODB_P_SHAPE(curve), int new_len ,boolean *is_ok_p);

/*
 *    lib_shape_grow_edge
 *
 *   Change segment/curve's length to 'ABS(new_len)'
 *   Curves grows/shrinks symmetrically to both ends
 *
 */
ODB_EXPORT int lib_shape_grow_edge(ODB_P_SHAPE(edge), int new_len ,boolean *is_ok_p);



/*
 *          lib_shape_line2line_sin
 *
 * Returns sinus between l1 and l2. l1 and l2 are treated as vectors
 * represented by skeletons. if length of one or both of skeletons is 
 * 0 result is also 0. 
 *
 */
ODB_EXPORT int lib_shape_line2line_sin(ODB_P_SHAPE(l1),
				   ODB_P_SHAPE(l2),
				   double *fi_p);

/*
 *          lib_shape_line2line_cos
 *
 * Returns cosine between l1 and l2. l1 and l2 are treated as vectors
 * represented by skeletons. if length of one or both of skeletons is 
 * 0 result is also 0.
 *
 */
ODB_EXPORT int lib_shape_line2line_cos(ODB_P_SHAPE(l1),
				   ODB_P_SHAPE(l2),
				   double *fi_p);

/*
 *          lib_shape_seg_type
 *
 * Returns the type of the argument segment.
 * the type is L_VERT, L_HOR, L_DIAG or L_POINT
 *
 */
ODB_EXPORT int lib_shape_seg_type(ODB_P_SHAPE(s1), seg_type_enum *type_p);


/*
 *          lib_shape_create_tangent_seg_on_curve
 *
 *  This function calculates for a given curve a tangent segment
 *  on the touching point of a given line.
 *
 */
ODB_EXPORT int lib_shape_create_tangent_seg_on_curve(ODB_P_SHAPE(curve), 
						     ODB_P_SHAPE(touching_line), 
						     int	size_for_intersection,
						     int	final_size,
						     boolean	straighten_segment,
						     ODB_P_SHAPE(out_seg),
						     boolean*	is_ok_p);


/*
 *          lib_shape_list_limit
 *
 * Returns limit box for a list of shapes.
 *
 */

ODB_EXPORT int lib_shape_list_limit(ODB_P_LIST(slist), ODB_P_SHAPE(limit));

/*
 *          lib_shape_move
 *
 * Moves the shape 'sp' by 'dx' 'dy'
 *
 */
ODB_EXPORT int lib_shape_move(ODB_P_SHAPE(sp), int dx, int dy);

ODB_EXPORT int lib_shape_move_from_shape(ODB_P_SHAPE(sp),ODB_P_SHAPE(from) , int dist);

ODB_EXPORT int lib_shape_move_dir(ODB_P_SHAPE(sp), ODB_P_SHAPE(dir_seg) , int dist);


/*
 *          lib_shape2f
 *
 * Creates a feature from a shape
 *
 */
ODB_EXPORT int lib_shape2f(ODB_P_SHAPE(sp), ODB_P_F(f));

/*
 *          lib_shape2neighbor
 *
 * Creates a neighbor out of a shape and a relative shape
 */
ODB_EXPORT int lib_shape2neighbor(ODB_P_SHAPE(shape), ODB_P_SHAPE(searching_shape), ODB_P_NEIGHBOR(neig));


/*
 *          lib_shape_area
 *
 * Calculate shapes area.
 *
 */

/**************************************************************
 *             lib_find_shape_on_other_edge                   *
 * This function completes the ODB_SHAPE_COVER_LAYER          *
 * function as it allows to get the shape at the other        *
 * end of the measurement segment .                           *
 *                                                            *
 * Written by :                                               *
 *              Tal Daskal     on :  Feb 24, 1997             *     
 **************************************************************/
ODB_EXPORT int lib_find_shape_on_other_edge(ODB_P_SHAPE(shape1), ODB_P_LAYER(layer),
				ODB_P_SHAPE(dist_seg), int dist, ODB_P_SHAPE(shape2));


ODB_EXPORT int lib_shape_coordinates2point(int x, int y, ODB_P_SHAPE(point));

ODB_EXPORT int lib_shape_points_line2line(odb_point_struc ps, odb_point_struc pe,
			  ODB_P_SHAPE(line0), ODB_P_SHAPE(line1));
   
ODB_EXPORT  int lib_shape_coordinates2circle(int x, int y, int r,
					     ODB_P_SHAPE(circle));

ODB_EXPORT int lib_shape_point2square(odb_point_struc p, int r, ODB_P_SHAPE(square));

ODB_EXPORT int lib_shape_thermal_cut_sep(ODB_P_LIST(sep_list), ODB_P_F(thermal_f),
					 int *is_ok);
ODB_EXPORT int lib_shape_seg2distseg( _odb_seg_struc *seg, ODB_P_SHAPE(dist_seg) );
ODB_EXPORT int lib_shape_distseg2seg( ODB_P_SHAPE(dist_seg), _odb_seg_struc *seg );


ODB_EXPORT int lib_shape_measure_shaved_line( ODB_P_LAYER( ld ),  ODB_P_SHAPE( shaved_line ),
                                              ODB_P_SHAPE( cur_width_seg ), boolean* ok_p );
ODB_EXPORT int lib_shape_rotate_pt( odb_point_struc *pt, odb_point_struc *pol, odb_angle_enum  ang,
                                    odb_point_struc *newPt);
ODB_EXPORT int lib_shape_rotate_odb_seg(_odb_seg_struc *seg,
                                        odb_point_struc *pol,
                                        odb_angle_enum ang,
                                        _odb_seg_struc *seg_p);
ODB_EXPORT int lib_shape_rotate_seg( ODB_P_SHAPE( seg ), ODB_P_SHAPE( pol ), odb_angle_enum ang, ODB_P_SHAPE( seg_p ) );
ODB_EXPORT int lib_shape_rotate_pt_any_angle( odb_point_struc* orig_pt_p, odb_point_struc* anchor_pt_p, double angle, odb_point_struc* new_pt_p );
ODB_EXPORT int lib_shape_rotate_seg_any_angle( ODB_P_SHAPE( seg ), ODB_P_SHAPE( anchor_pt ), double angle, ODB_P_SHAPE( seg_p ) );
ODB_EXPORT int lib_shape_rotate_curve_any_angle( ODB_P_SHAPE( curve ), ODB_P_SHAPE( anchor_pt ), double angle, ODB_P_SHAPE( curve_p ) );
ODB_EXPORT int lib_shape_get_rotated_limit(ODB_P_LAYER(ld), ODB_P_SHAPE(shape),ODB_P_SHAPE(shape_limit),int* smd_type,int* success);
ODB_EXPORT int lib_shape_rotate_contr_any_angle( ODB_P_SHAPE( contr), ODB_P_SHAPE( anchor_pt ), double angle, ODB_P_SHAPE( contr_p ) );

ODB_EXPORT int lib_shape_size_arc( ODB_P_SHAPE( layer_shape ),ODB_P_LAYER( signal_layer ), int min_len, int max_width, double len2width_ratio, 
				   ODB_P_LIST( arc_list ), int *min_width, int *len_at_min_width, int *ind);
ODB_EXPORT int lib_shape_push_for_selection(ODB_P_LAYER(layer),ODB_P_SHAPE(shape));
ODB_EXPORT int lib_shape_push_for_selection_2_shapes(ODB_P_LAYER(firstlayer),ODB_P_SHAPE(firstshape),
						     ODB_P_LAYER(secondlayer),ODB_P_SHAPE(secondshape));
ODB_EXPORT int lib_shape_get_shapes(ODB_P_LAYER(sm_layer),ODB_P_SHAPE(shape),
				    ODB_P_LIST(sm_shapes_list),boolean* is_shape_in_sm_layer,
				    boolean* is_shape_cover_by_sm_layer);
/* Split shape (line, arc) into subshapes */
ODB_EXPORT int lib_shape_split_shape(ODB_P_SHAPE ( shape ),
				     int	min_length,
				     int	use_eps,
				     double	use_min_sin_value,
				     ODB_P_LIST  (split_shapes_list));
ODB_EXPORT int lib_shape_calc_break_pts(ODB_P_SHAPE ( shape ),
					int	min_length,
					int	use_eps,
					double	use_min_sin_value,
					ODB_P_LIST  (break_pt_list));
ODB_EXPORT int lib_shape_calc_break_line_pts(ODB_P_SHAPE ( line_shape),
					     int min_length,
					     ODB_P_LIST  (break_pt_list));
ODB_EXPORT int lib_shape_calc_break_curve_pts(ODB_P_SHAPE   (arc_shape),
					      int	    min_length,
					      int	    use_eps,
					      double	    use_min_sin_value,
					      ODB_P_LIST    (break_arc_pt_list));
ODB_EXPORT int lib_shape_get_arc_angle( ODB_P_SHAPE( arc_shape ), double* angle_p );
ODB_EXPORT int lib_shape_rotate_pt_any_angle_dir(ODB_P_SHAPE( in_pt_shape ),
						 ODB_P_SHAPE( pivot_pt_shape ),
						 double sina,
						 double cosa,
						 boolean cw,
						 ODB_P_SHAPE( out_pt_shape ));
ODB_EXPORT int lib_shape_get_mid_pt( ODB_P_SHAPE( shape ),
				    ODB_P_SHAPE ( mid_pt ) );
ODB_EXPORT int lib_shape_get_normal( ODB_P_SHAPE( shape ),
				    double* nx_p,
				    double* ny_p );
ODB_EXPORT int lib_shape_get_normal_to_seg( ODB_P_SHAPE( seg ),
					   double* nx_p,
					   double* ny_p );
ODB_EXPORT int lib_shape_get_normal_to_curve( ODB_P_SHAPE( curve ),
					     ODB_P_SHAPE ( pt ),
					     double* nx,
					     double* ny );
ODB_EXPORT int lib_shape_swap( ODB_P_SHAPE( shape ) );
ODB_EXPORT int lib_shape_offset( ODB_P_SHAPE( shape ),
				int dist,
				ODB_P_SHAPE( offset_shape ),
				boolean *ok_p );

typedef enum { NOT_COVERED, PARTIALLY_COVERED, FULLY_COVERED} covered_type_enum;
ODB_EXPORT int lib_shape_is_covered_by_edge(ODB_P_SHAPE( covered_shape ),
					    ODB_P_LIST( cover_list ),
					    double min_precentage,
                                            double max_precentage,
					    int clip_mode,
					    int clip_as_contour,
					    boolean consider_equal_size_as_embedded,
					    covered_type_enum* is_covered);

ODB_EXPORT int lib_shape_is_covered_by_area( ODB_P_SHAPE( covered_shape ),
					     ODB_P_LIST( cover_list ),
					     double min_precentage,
                                             double max_precentage,
					     boolean consider_equal_size_as_embedded,
					     covered_type_enum* is_covered);

ODB_EXPORT int lib_shape_valided_partial_embedded_pad(	ODB_P_SHAPE( pad_shape ), 
							ODB_P_LIST( close_shapes_lst ),
							boolean* is_partially_embedded_p );

#define EMBEDDED_IN_SURFACE_MARGIN 110 /*This value is a little bit more than SLR's EPS=100*/
ODB_EXPORT int lib_shape_trim_by_intersecting(ODB_P_SHAPE   (orig_shape),
					      ODB_P_LAYER   (layer),
					      int	    ignore_f_types,
					      ODB_P_LIST    (trimmed_list),
					      boolean*	    shape_was_trimmed_p);

/* Flighta Z. Kit 12005, get the width of rotated and special pad */
/* This funtion try to get small limit of Pad, similar with lib_shape_get_rotated_limit, but no need use ODB_SYMBOL_GET_SMD_PARAMS_ROT,
so construct pad also can get limits */
ODB_EXPORT int lib_shape_get_pad_small_limit(ODB_P_F(f_pad), ODB_P_LIST(limit_list));

ODB_EXPORT int lib_shape_get_small_limit(ODB_P_SHAPE(pad_shape), ODB_P_SHAPE(f_limits), ODB_P_LIST(limit_list));

ODB_EXPORT int lib_shape_intersect_furthest(ODB_P_SHAPE	(shape1), 
					    ODB_P_SHAPE	(shape2),
					    int*	num_intersection_p,
					    ODB_P_SHAPE	(intersect1),
					    ODB_P_SHAPE	(intersect2));

ODB_EXPORT int lib_shape_pierce_contour( ODB_P_SHAPE( seg ),
					ODB_P_SHAPE( cont ),
					ODB_P_LIST( pt_list ));

ODB_EXPORT int lib_shape_get_poly_by_pt( ODB_P_SHAPE( cont ),
					ODB_P_SHAPE( pt ),
					ODB_P_SHAPE( poly ),
					boolean *is_touch_p,
					boolean *is_island_p );

ODB_EXPORT int lib_shape_get_shape_center(ODB_P_SHAPE(shape),ODB_P_SHAPE(shape_center));

ODB_EXPORT int lib_shape_get_shape_raduis(ODB_P_SHAPE(shape),int* radius);

ODB_EXPORT int lib_shape_get_teardrop_and_entrace_line(ODB_P_SHAPE(pad_shape), ODB_P_LIST(near_shape_list), 
                                            ODB_P_LIST(tear_drop_list), ODB_P_LIST(entrace_line_list), 
                                            boolean *b_find_teardrop, boolean *b_found_entrace_line);

ODB_EXPORT int lib_shape_init_shape_as_circle(ODB_P_SHAPE(shape));

ODB_EXPORT int lib_shape_build_circle_by_center(ODB_P_SHAPE(return_shape),odb_point_struc circle_center,int circle_radius);

ODB_EXPORT int lib_shape_build_circle_by_shape(ODB_P_SHAPE(return_shape),ODB_P_SHAPE(shape));

ODB_EXPORT int lib_shape_build_circle_by_shape_and_raduis(ODB_P_SHAPE(return_shape),ODB_P_SHAPE(shape),int circle_radius);

ODB_EXPORT int lib_shape_add_extrem_break_point(ODB_P_LIST(edgesList));

ODB_EXPORT int lib_shape_debug_add_layer(ODB_P_LAYER(layer),odb_name name);

ODB_EXPORT int lib_shape_debug_add_layer_plus(ODB_P_LAYER(layer),odb_name name);

ODB_EXPORT int lib_shape_debug_add_list(ODB_P_LIST(segs_shape_list),odb_name name);

ODB_EXPORT int lib_shape_debug_add_list_plus(ODB_P_LIST(segs_shape_list),odb_name name);

ODB_EXPORT int lib_shape_debug_add_list_neig(ODB_P_LIST(segs_shape_list),odb_name name);

ODB_EXPORT int lib_shape_debug_add_list_neig_plus(ODB_P_LIST(segs_shape_list),odb_name name);

ODB_EXPORT int lib_shape_debug_add_shape_plus(ODB_P_SHAPE(shape),odb_name name);

ODB_EXPORT int lib_shape_debug_add_point_plus(ODB_P_SHAPE(shape),odb_name name);

ODB_EXPORT int lib_shape_debug_add_f_plus(ODB_P_F(feat),odb_name name);

ODB_EXPORT int lib_shape_debug_add_shape(ODB_P_SHAPE(shape),odb_name name,boolean with_open,ODB_P_LAYER(ld_out));

ODB_EXPORT int lib_shape_debug_add_f(ODB_P_F(feat),odb_name name,boolean with_open,ODB_P_LAYER(ld_out));

ODB_EXPORT int lib_shape_debug_add_list_f(ODB_P_LIST(segs_shape_list),odb_name name);

ODB_EXPORT int lib_shape_is_bga(ODB_P_SHAPE (shape));

ODB_EXPORT int lib_shape_is_smd(ODB_P_SHAPE (shape));

ODB_EXPORT int lib_shape_is_imp_line(ODB_P_SHAPE (shape));

ODB_EXPORT int lib_shape_is_pad(ODB_P_SHAPE (shape));

ODB_EXPORT int lib_shape_is_line(ODB_P_SHAPE (shape));

ODB_EXPORT int lib_shape_is_surface(ODB_P_SHAPE (shape));

ODB_EXPORT boolean lib_shape_point_on_the_left( ODB_P_SHAPE( seg ), ODB_P_SHAPE( point ) );

ODB_EXPORT int lib_shape_get_line(ODB_P_SHAPE(line_in), ODB_P_SHAPE(line_out), boolean *is_ok_p);
ODB_EXPORT int lib_shape_get_line_data(ODB_P_SHAPE(line),ODB_P_SHAPE(point_line_ps),ODB_P_SHAPE(point_line_pe),int *diameter_p, boolean *ok_p);
ODB_EXPORT int lib_shape_get_arc(ODB_P_SHAPE(arc_in), ODB_P_SHAPE(arc_out), boolean *is_ok_p);


ODB_EXPORT  int lib_shape_debug_get_add_f(ODB_P_LAYER(ld), ODB_P_F(f));

ODB_EXPORT  int lib_shape_debug_get_delete_f(ODB_P_LAYER(ld), int nf);

ODB_EXPORT  int lib_shape_near_layer(ODB_P_SHAPE(shape),ODB_P_LAYER(layer),int spacing,int ignore_net,ODB_P_LIST(near_list));

ODB_EXPORT  int lib_shape_near_layer_touch(ODB_P_SHAPE(shape),ODB_P_LAYER(layer),int spacing,int ignore_net,int* touch);

ODB_EXPORT  int lib_shape_neig_above_below_dist(ODB_P_NEIGHBOR(neig),int dist,pp_neig_dist_relation_enum relation,boolean also_equal);

ODB_EXPORT  int  lib_shape_get_neigbors(ODB_P_SHAPE(shape),ODB_P_LAYER(layer),int spacing,int ignore_net,ODB_P_LIST(*near_list));

ODB_EXPORT  int  lib_shape_diff_list_from_list_to_list(ODB_P_LIST(list),ODB_P_LIST(removed_list),ODB_P_LIST(diff_list),int tolerance);

ODB_EXPORT  int  lib_shape_inter_list_from_list_to_list(ODB_P_LIST(list),ODB_P_LIST(list1),ODB_P_LIST(inter_list));

ODB_EXPORT  int lib_shape_get_diff_list(ODB_P_SHAPE(movement_area),ODB_P_LIST(enlarge_near_list),ODB_P_LIST(out_list),int* count);

ODB_EXPORT  int lib_shape_get_diff_list_from_list(ODB_P_LIST(movement_area),ODB_P_LIST(enlarge_near_list),ODB_P_LIST(total_out_list),int* count);

ODB_EXPORT  int lib_shape_diff_list_from_list(ODB_P_LIST(list),ODB_P_LIST(removed_list),int tolerance);

ODB_EXPORT int lib_shape_enlarge_list(ODB_P_LIST(near_list),ODB_P_LIST(enlarge_near_list),int resize,boolean* is_ok);

ODB_EXPORT int lib_shape_get_shape_edge_ps(ODB_P_SHAPE(edge), odb_point_struc* ps);

ODB_EXPORT int lib_shape_get_shape_edge_pe(ODB_P_SHAPE(edge), odb_point_struc* pe);

ODB_EXPORT boolean lib_shape_is_points_eq(odb_point_struc p1, odb_point_struc p2);

ODB_EXPORT int lib_shape_is_pnt_edge_vertex(ODB_P_SHAPE(edge), odb_point_struc p, odb_point_struc* other_p, boolean* is_eq);

ODB_EXPORT int lib_shape_get_shape_edge_r(ODB_P_SHAPE(edge), int* r);

ODB_EXPORT int lib_shape_resize_list_to_list(ODB_P_LIST(list_in),int resize,ODB_P_LIST(list_out),boolean* is_ok);

ODB_EXPORT int lib_shape_resize_list(ODB_P_LIST(list_in),int resize,boolean* is_ok);

ODB_EXPORT int lib_shape_clear(ODB_P_SHAPE(shape));

ODB_EXPORT int lib_shape_cont_resize_by_edges(ODB_P_SHAPE(m_shape), 
                        int i_resize_value, 
                        int *o_ok);

ODB_EXPORT int lib_shape_cont_resize_by_edges_2list(ODB_P_SHAPE(i_shape), 
                                int        i_resize_value, 
                                ODB_P_LIST(o_resized_list), 
                                int       *o_ok);

ODB_EXPORT int lib_shape_check_for_pinhole_between_surface_and_patch(ODB_P_SHAPE  (surface),
						       ODB_P_SHAPE  (patch_line),
						       boolean*	    creates_pinhole_p);	
 
ODB_EXPORT int lib_shape_delete_temporary_attributes(ODB_P_LAYER(ld),char* string );

ODB_EXPORT int lib_shape_is_shape_touching_shape_center(ODB_P_SHAPE(touching_shape),
							 ODB_P_SHAPE(shape),/*this is the shape's center been touched by touching shape */
							 boolean* touches_shape_center);

ODB_EXPORT int lib_shape_is_small_arc(ODB_P_SHAPE(poletntial_small_arc),boolean* is_small_arc);

ODB_EXPORT int lib_shape_point_touch_seg(ODB_P_SHAPE(line),ODB_P_SHAPE(point), int tolerance, boolean* touch);

ODB_EXPORT int lib_shape_point_touch_virtual_seg(ODB_P_SHAPE(line),ODB_P_SHAPE(point),boolean* touch); 

ODB_EXPORT int lib_shape_is_point_on_line(ODB_P_SHAPE(line), ODB_P_SHAPE(point),int tolerance , boolean virtaul_line, boolean* touch);

ODB_EXPORT int lib_shape_get_connect_edge(ODB_P_LIST(edge_list), ODB_P_SHAPE(start_seg), ODB_P_LIST(connect_list));

ODB_EXPORT int lib_shape_copy_curve_to_curve(ODB_P_SHAPE(arc1),ODB_P_SHAPE(curve1),boolean* ok);

ODB_EXPORT int lib_shape_copy_curve_to_curve_reverse(ODB_P_SHAPE(arc1),ODB_P_SHAPE(curve1),boolean* ok);

ODB_EXPORT int lib_shape_curve_project_curve(ODB_P_SHAPE(curve1),ODB_P_SHAPE(curve2),boolean* is_project);

ODB_EXPORT int lib_shape_copy_seg_to_seg(ODB_P_SHAPE(line1),ODB_P_SHAPE(seg1),boolean* ok);

ODB_EXPORT int lib_shape_copy_seg_to_seg_reverse(ODB_P_SHAPE(line1),ODB_P_SHAPE(seg1),boolean* ok);

ODB_EXPORT int lib_shape_copy_trace_to_trace(ODB_P_SHAPE(line1),ODB_P_SHAPE(seg1),boolean* ok);

ODB_EXPORT int lib_shape_copy_trace_to_trace_reverse(ODB_P_SHAPE(line1),ODB_P_SHAPE(seg1),boolean* ok);

ODB_EXPORT int lib_shape_whether_rectangular_pad(ODB_P_SHAPE(shape),
    boolean* b_rect_pad, boolean* b_oblique,
    int* width, int* height);

ODB_EXPORT int lib_shape_whether_round_pad(ODB_P_SHAPE(shape), boolean* b_round);

ODB_EXPORT int lib_shape_union_seg_list(ODB_P_LIST(edge_shape_list), double min_cos_value);

ODB_EXPORT int lib_shape_union_seg_list_advance(ODB_P_LIST(edge_shape_list), double min_cos_value, int len_tol );

ODB_EXPORT double   lib_shape_get_abs_angl( double dX, double dY );

ODB_EXPORT int lib_shape_calc_break_curve_pts_dbl(ODB_P_SHAPE (arc_shape),
					          int          min_length,
					          int          use_eps,
					          double       use_min_sin_value,
					          ODB_P_LIST  (break_arc_pt_list));

ODB_EXPORT void lib_shape_set_flag_split_shape_curve( int flag_split_by_dbl);

ODB_EXPORT int lib_shape_merge_contour_shapes(ODB_P_LIST(edge_shape_list), 
                                              int curve_cen_tol, 
                                              ODB_P_SHAPE(pad_shape));

ODB_EXPORT int lib_shape_convert_oval(ODB_P_LAYER(layer), 
                           ODB_P_SHAPE(shape), 
                           slot_f_type_enum pp_slot_f_type, 
                           int convt_tol, 
                           ODB_P_F(slot_f), 
                           boolean *success); 
ODB_EXPORT int lib_shape_convert_oval_advanced(ODB_P_LAYER(layer),
			     ODB_P_SHAPE(shape),
			     slot_f_type_enum slot_f_type,
			     int convt_tol,
			     boolean v_convert_rect_to_slot,
			     ODB_P_F(slot_f),
			     boolean *success);
ODB_EXPORT int lib_shape_get_pad_skeleton(ODB_P_SHAPE(shape), 
                               ODB_P_SHAPE(skeleton_seg), 
                               int *width, 
                               int *height, 
                               boolean *success); 

ODB_EXPORT int lib_shape_get_shape_from_f_by_nf(ODB_P_LAYER(layer), 
                                   int nf, 
                                   ODB_P_SHAPE(shape), 
                                   boolean *success); 

ODB_EXPORT int lib_shape_create_poly(int (*arry)[2],
                                     int point_num,
                                     ODB_P_SHAPE(poly));

ODB_EXPORT int lib_shape_create_square(int pc_x,
                                       int pc_y,
                                       int width,
                                       ODB_P_SHAPE(square));

ODB_EXPORT int lib_shape_create_cricle(int pc_x,
                                       int pc_y,
                                       int r,
                                       ODB_P_SHAPE(circle));

ODB_EXPORT int lib_shape_create_arc(int ps_x,
                                    int ps_y,
                                    int pe_x,
                                    int pe_y,
                                    int pc_x,
                                    int pc_y,
                                    int width,
                                    int cw,
                                    ODB_P_SHAPE(arc));

ODB_EXPORT int lib_shape_create_line(int ps_x,
                                     int ps_y,
                                     int pe_x,
                                     int pe_y,
                                     int width,
                                     ODB_P_SHAPE(line));

ODB_EXPORT int lib_shape_get_round_edge(ODB_P_SHAPE(whole_shape),
                                        ODB_P_SHAPE(acute_shape),
                                        ODB_P_LAYER(layer),
                                        ODB_P_LIST(round_edge_list),
                                        int          smooth_radius,
                                        boolean      *b_get_round);

ODB_EXPORT int lib_shape_get_round_edge_tol(ODB_P_SHAPE(whole_shape),
                                            ODB_P_SHAPE(acute_shape),
                                            ODB_P_LAYER(layer),
                                            ODB_P_LIST(round_edge_list),
                                            int smooth_radius,
                                            int compare_radius_value,
                                            boolean *b_get_round);

ODB_EXPORT int lib_shape_union_curve_list(ODB_P_LIST(edge_shape_list), int tol_value);

ODB_EXPORT int lib_shape_clip_list_by_cont(ODB_P_LIST(in_list), ODB_P_SHAPE(clipper_shape), ODB_P_LIST(out_list));

ODB_EXPORT int lib_shape_is_shape_rectangle(ODB_P_SHAPE(shape), boolean *b_rectangle);
ODB_EXPORT int lib_shape_is_line_parallel_rect(ODB_P_SHAPE(line), ODB_P_SHAPE(rect), boolean *is_parallel_p);

ODB_EXPORT int lib_shape_get_surface_shape(ODB_P_SHAPE(pad_shape));
ODB_EXPORT int lib_shape_get_surface_shape_list(ODB_P_SHAPE(pad_shape), ODB_P_LIST(surfce_shape_list));
ODB_EXPORT int lib_shape_update_surface_info_from_shape_to_shape(ODB_P_SHAPE(shape), ODB_P_SHAPE(shape1));

ODB_EXPORT int lib_shape_get_pad_drill_type(ODB_P_SHAPE(pad_shape), ODB_P_SHAPE(hole), ODB_P_LIST(list_of_drill_layers),
					    int*	found_type_p,
					    int*	drill_type_p,
					    int*	via_type_p);
/*
 * Entry point for unit tests of this module
 */
ODB_EXPORT int lib_shape_unit_tests();

ODB_EXPORT int lib_shape_remove_not_touching_shapes(ODB_P_SHAPE(shape),ODB_P_LIST(near_list));





#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
