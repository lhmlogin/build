#!/bin/csh
COM imp_cnsts_change,imp_id=1,ilr_dfm_use=yes
COM chklist_cupd,chklist=frontline_imp_test_points_creator,nact=1,params=((pp_tp_min_width=0)(pp_tp_min_length=6)(pp_tp_max_width=75)(pp_imp_min_len=0.1)(pp_imp_min_coverage=90)(pp_tp_good_pair_num=1)(pp_pgtp_max_search_dist=40)(pp_pgtp_min_width=6)(pp_allow_middle_pad=allow_middle_pad)(pp_imp_min_avail_percent=10.000000)(pp_imp_has_best_len=)(pp_imp_best_len=4)(pp_tp_need_middle=)(pp_tp_need_shortest=)(pp_all_need_len_cov=all_need_len_cov)(ignore_attrs=.gold_finger)),mode=regular
COM chklist_run,chklist=frontline_imp_test_points_creator,nact=1
COM chklist_single,show=yes,action=frontline_imp_test_points_creator
COM info,out_file=D:/tmp/check_result.txt,write_mode=replace,args=-t check -e $JOB/pcb/frontline_imp_test_points_creator -d MEAS -o action=1
