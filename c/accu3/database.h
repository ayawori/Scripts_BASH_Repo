#ifndef __DATABASE_H   /* must be first */
#define __DATABASE_H                                                                      
    
#include "sys_dir.h"
#include "mtr_prod.h"
#include "prd_dir.h"
#include "io_dir.h"
#include "sec_dir.h"
#include "comm_dir.h"
#include "add_def.h"
#include "algebool.h"
#include "alrm_dir.h"
#include "inj_dir.h"
#include "recp_dir.h"
#include "arm_dir.h"
#include "mtr_dir.h"
#include "prod_dir.h"
#include "comdrv.h"
#include "cardread.h"
#include "nedap.h"

#define MAX_BAYS                2
#define MAX_LOAD_ARMS           6
#define MAX_METERS              6
#define MAX_PRODUCTS            6
#define MAX_COMM_PORTS          4
#define MAX_SECURITY_LEVELS     5
#define MAX_RECIPES            50
#define MAX_USER_ALARMS        10
#define MAX_REVERSE_METERS	   MAX_METERS
#define MAX_PHYS_VIRT_METERS   (MAX_METERS * 2)

#define NUM_DIGITAL_INPUTS		43	/* total digital inputs */
#define NUM_DIGITAL_OUTPUTS		78	/* total digital outputs */
#define MAX_DIGITAL_INPUTS     NUM_DIGITAL_INPUTS 	/* 43 - total digital and bistate inputs */
#define MAX_DIGITAL_OUTPUTS    NUM_DIGITAL_OUTPUTS	/* 78 - total digital and bistate outputs */
#define MAX_DIGITAL_IO         (MAX_DIGITAL_INPUTS + MAX_DIGITAL_OUTPUTS)		/* 121 - total digital and bistate inputs and outputs */
#define FIRST_DIGITAL_INPUT	0
#define FIRST_BISTATE_INPUT 15
#define FIRST_DIGITAL_OUTPUT 43
#define FIRST_BISTATE_OUTPUT 73
#define MAX_BISTATE_IO			8
#define FIRST_AICB_OUTPUT	81

#define MAX_ANALOG_IO           6
#define MAX_ANALOG_INPUTS       6
#define MAX_ID_LENGTH           9     /* used for product & recipe name */
#define MAX_FACTORS             5
#define MAX_DISPLAY            (double)999999999.0
#define MAX_PRESET             (double)999999
#define MAX_UNLIMITED_PRESET   (double)9999999  /* Rev 11.08 - allow for bigger transactions */
#define MAX_BATCH_PER_TRAN     10
#define MAX_PERMISSIVES         2
#define MAX_SYS_PERMISSIVES     3
#define MAX_PROMPTS             5
#define MAX_PROMPT_LENGTH      28     /* used for prompts, permissives, user alarms */
#define MAX_TAG_ID_LENGTH		8	  /* use for Smith/Sening (Bluetooth) functionality*/
#define MAX_PULSE_OUT           5
#define MAX_PULSE_IN            12
#define MAX_VAPOR_PRES_PTS      3
#define MAX_DATE_LENGTH        15
#define TRANS_ALM_STR_SIZE	   11
#define BATCH_ALM_STR_SIZE	    8
#define ALPHA_DATE_SIZE        13     /* Dec 13, 1997 */
#define NUMERIC_DATE_SIZE       9     /* 12/13/97 */
#define TIME_SIZE              12     /* 10:15:01 PM */
#define DATE_TIME_SIZE         22     /* 12/13/97  10:15:01 PM */ 
#define MAX_LINE_LENGTH        30
#define MAX_HM_CLASS_LENGTH    30
#define MAX_AUDIT_TRAIL_ENTRY_LENGTH 72
#define MAX_SEQ_COMPS           6       /* number of components for sequential blender */
#define ALPHA_PROMPT_SIZE	   20
#define MAX_INJ_NON_VOLUME (double)1000000.0


#define MAX_CARD_DATA 48                /* max data from Smith Card Reader */
#define MAX_NEDAP_DATA 24            	/* max data from Nedap Reader */

#define ARCHIVED_USER_VARS    5		 // 10.15 - archive last 5 floats and bools with transaction
#define MAX_USER_TEXT         8      // 10.15 - user text entry definitions
#define USER_TEXT_LENGTH      32

#define FALSE                   0
#define TRUE                    (!FALSE)

#define db_not_updating 0
#define db_updating     1

typedef unsigned char byte;

enum alarm_state { ALARM_OFF, ALARM_ON, ALARM_ACK };

#define NO_OFFSET               0
#define NEW_PARAMETERS          0xff

#define ON_ENTRY                1         /* pDB.on_entry_flag set when store_parameter() */
#define NOT_ON_ENTRY            0         /*   is calling critical rtn - not backgnd crit task */

#define MAX_TRANS_NO			9999
#define MAX_BATCH_ALARMS        10
#define MAX_TRANS_ALARMS        20
#define MAX_RBM_PRODUCTS		4
#define	MAX_UNLOAD_DENSITY_SAMPLES	10

#define MAX_VALVE_CLOSE_DIAG_STORED 10	 //used for the valve closure diagnostic data

enum store_literals_types { start_store, next_store, last_store, kill_store, clear_store };
enum round_pts { whole, tenths, hundreths, thousandths, ten_thousands };

/*****************************************************************************/
/*********        PARAMETER DATABASE TABLE ENUMERATIONS               ********/
/*****************************************************************************/

enum TEXT_system_data
    {
        numeric_date,
        time,
        flow_rate_desc,
        trans_id_msg,
        vol_desc,
        mass_desc,
        user_alrm_1,
        user_alrm_2,
        user_alrm_3,
        user_alrm_4,
        user_alrm_5,
        user_alrm_6,
        user_alrm_7,
        user_alrm_8,
        user_alrm_9,
        user_alrm_10,
        inj_units,   
        inj_totals_units,
        sys_permissive_1_msg,
        sys_permissive_2_msg,
        sys_permissive_3_msg,
        mac_address,
		smtp_server,
		pop3_server,
		email_user_name,
		email_password,
		email_notify_dest,
		email_reply_to,
		network_printer,
		firmware_revision,
		max_arms,
        num_TEXT_system_data
    };

enum TEXT_prompt_data
    {
        prompt_msg_1,
        prompt_msg_2,
        prompt_msg_3,
        prompt_msg_4,
        prompt_msg_5,

        num_TEXT_prompt_data
    };

enum TEXT_arm_data
    {
        permissive_1_msg,
        permissive_2_msg,
        load_arm_id,
        report_print_time,
        ready_msg,
        tag_id,
        num_TEXT_arm_data
    };

enum TEXT_product_data
    {
        product_id,
        hm_class_1,
        hm_class_2,
        num_TEXT_product_data
    };

enum TEXT_recipe_data
{
    recipe_name,
    num_TEXT_recipe_data
};


enum TEXT_bay_data
{
		bay_id,
		rep_print_time_bay,
		bay_perm_1_msg,
		bay_perm_2_msg,
		num_TEXT_bay_data
};


enum TEXT_sys_run_data
    {
        card_A_data_1,
        card_A_data_2,
        card_A_data_3,
        card_B_data_1,
        card_B_data_2,
        card_B_data_3,
		
		nedap_A_data,
		nedap_B_data,

        num_TEXT_sys_run_data
    };

enum TEXT_tran_run_data
    {
        tran_alarm_1,
        tran_alarm_2,
        tran_alarm_3,
        tran_alarm_4,
        tran_alarm_5,
        tran_alarm_6,
        tran_alarm_7,
        tran_alarm_8,
        tran_alarm_9,
        tran_alarm_10,
        tran_alarm_11,
        tran_alarm_12,
        tran_alarm_13,
        tran_alarm_14,
        tran_alarm_15,
        tran_alarm_16,
        tran_alarm_17,
        tran_alarm_18,
        tran_alarm_19,
        tran_alarm_20,
		reserved_1,	   // old tran_end_time for backwards compatability
		card_info_1,
		card_info_2,
		card_info_3,
        tran_end_time,
		tran_start_time,
		alpha_pmpt_1,
		alpha_pmpt_2,
		alpha_pmpt_3,
		alpha_pmpt_4,
		alpha_pmpt_5,
		prove_time,
		card_field_1,
		card_field_2,
		card_field_3,
		card_hid_fac,
		card_hid_num,
		archived_user_text_1,
		archived_user_text_2,
		archived_user_text_3,
		archived_user_text_4,
		archived_user_text_5,
		archived_user_text_6,
		archived_user_text_7,
		archived_user_text_8,
        num_TEXT_tran_run_data
    };


enum TEXT_bay_run_data
    {
        btran_alarm_1,
        btran_alarm_2,
        btran_alarm_3,
        btran_alarm_4,
        btran_alarm_5,
        btran_alarm_6,
        btran_alarm_7,
        btran_alarm_8,
        btran_alarm_9,
        btran_alarm_10,
        btran_alarm_11,
        btran_alarm_12,
        btran_alarm_13,
        btran_alarm_14,
        btran_alarm_15,
        btran_alarm_16,
        btran_alarm_17,
        btran_alarm_18,
        btran_alarm_19,
        btran_alarm_20,
		breserved_1,
		bcard_info_1,
		bcard_info_2,
		bcard_info_3,
        btran_end_time,
		btran_start_time,
		balpha_pmpt_1,
		balpha_pmpt_2,
		balpha_pmpt_3,
		balpha_pmpt_4,
		balpha_pmpt_5,
		bcard_field_1,
		bcard_field_2,
		bcard_field_3,
		bcard_hid_fac,
		bcard_hid_num,
		barchived_user_text_1,
		barchived_user_text_2,
		barchived_user_text_3,
		barchived_user_text_4,
		barchived_user_text_5,
		barchived_user_text_6,
		barchived_user_text_7,
		barchived_user_text_8,
        num_TEXT_bay_run_data
    };


enum TEXT_batch_run_data
    {
        batch_alarm_1,
        batch_alarm_2,
        batch_alarm_3,
        batch_alarm_4,
        batch_alarm_5,
        batch_alarm_6,
        batch_alarm_7,
        batch_alarm_8,
        batch_alarm_9,
        batch_alarm_10,
        num_TEXT_batch_run_data
    };

enum TEXT_arm_commands
    {
		user_text_1,
		user_text_2,
		user_text_3,
		user_text_4,
		user_text_5,
		user_text_6,
		user_text_7,
		user_text_8,
        num_TEXT_arm_commands
    };




enum FP_system_data
    {
        pul_per_vol_1,
        pul_per_vol_2,
        pul_max_freq_1,
        pul_max_freq_2,
        batch_max_vol,
        batch_min_vol,
        auto_preset,
        auto_preset_inc,
        ref_temp,
        additive_stop_volume,
        conversion_factor,
        additive_clean_line_volume,
		inj_alarm_pulse_count,
		inj_error_count,
		pul_per_vol_3,
		pul_per_vol_4,
		pul_per_vol_5,
		pul_max_freq_3,
		pul_max_freq_4,
		pul_max_freq_5,
		nr_leak_alrm_limit,
		reverse_flow_alrm_limit,
		atmos_press,
        num_FP_system_data
    };

enum FP_arm_data
    {
        low_flow_start_rate,
        low_flow_start_vol,
        low_flow_start_percent,
        overrun_alrm_limit,
        arm_hi_flow_rate,
        arm_sec_hi_flow_rate,
        ratio_adjust_factor,
        blend_tol_pct,
        blend_tol_vol,
		arm_add_stop_amt,
		sec_hi_flow_preset,
		blend_correct_vol,
		valve_fault_amt,
        num_FP_arm_data
    };

enum FP_meter_data
    {
        mtr_overrun_alrm_limit,
        k_factor,
        dp_flow_rate_cutoff,
        smass1_a,
        smass1_b,
        sol1_dcf,              
        sol1_k0,
        sol1_k1,
        sol1_k2,
        sol1_k18,
        sol1_k19,
        sol1_k20a,
        sol1_k20b,
        sol1_k21a,
        sol1_k21b,              
        sol1_tcal,
        sol1_pcal,
        sar1_dcf,
        sar1_k,
        sar1_d0,
        sar1_t0,
        sar1_tcoef,
        sar1_tcal,
        sar1_pcoef,
        sar1_pcal,
        ugc1_dcf,
        ugc1_k0,
        ugc1_k1,
        ugc1_k2,
        ugc1_tc,
        ugc1_kt1,
        ugc1_kt2,
        ugc1_kt3,
        ugc1_pc,
        ugc1_kp1,
        ugc1_kp2,
        ugc1_kp3,
        od1_dcf,
        od1_a,
        od1_b,
        od1_c,
        flow_adj_tol,
        flow_adj_timer,
        ana_p,
        ana_i,
        ana_d,
        pid_intval,
		smass_mtr_ka,
		smass_mtr_kb,
		smass_mtr_kc,
        num_FP_meter_data
    };

enum FP_product_data
    {
        min_flow_rate,
        hi_flow_rate,
        sec_hi_flow_rate,
        flow_tol_percent,
        flow_tol_rate,
        first_trip_vol,
        sec_trip_vol,
        excess_hi_flow_rate,
        lo_flow_rate_alrm_limit,
        m1_mfac_1,
        m1_frate_1,
        m1_mfac_2,
        m1_frate_2,
        m1_mfac_3,
        m1_frate_3,
        m1_mfac_4,
        m1_frate_4,
        master_mtr_fac,
        lin_fac_dev,
        mfv_percent_temp,
        mfv_ref_temp,
        maint_temp,
        hi_temp_alrm_limit,
        lo_temp_alrm_limit,
        prd_dens,
        hi_dens_alrm_limit,
        lo_dens_alrm_limit,
        maint_press,
        press_coeff,
        hi_press_alrm_limit,
        lo_press_alrm_limit,
        diff_press,
        min_bp_flow_rate,
        bp_percent_reduce,
        bp_flow_recover_press,
        vapor_press_1,
        vp_temp_1,
        vapor_press_2,
        vp_temp_2,
        vapor_press_3,
        vp_temp_3,
        min_batch_vol,
		unload_delta_vol,
		unload_contam_dens,
		prd_stop_amt,
		prd_stop_alrm,
		ref_density_temp,
		ref_density_ctable,
		ethanol_a1,
		ethanol_a2,
		ethanol_a3,
		aromatic_dens,
		m1_mfac_5,
		m1_frate_5,
		ptb_k0e,
		eth_grade_bymass,
        num_FP_product_data
    };

enum FP_recipe_data
    {
        vol_1,
        vol_2,
        vol_3,
        vol_4,
        vol_5,
        vol_6,
        vol_7,
        vol_8,
        vol_9,
        vol_10,
        vol_11,
        vol_12,
        vol_13,
        vol_14,
        vol_15,
        vol_16,
        vol_17,
        vol_18,
        vol_19,
        vol_20,
        vol_21,
        vol_22,
        vol_23,
        vol_24,
        rate_1,
        rate_2,
        rate_3,
        rate_4,
        rate_5,
        rate_6,
        rate_7,
        rate_8,
        rate_9,
        rate_10,
        rate_11,
        rate_12,
        rate_13,
        rate_14,
        rate_15,
        rate_16,
        rate_17,
        rate_18,
        rate_19,
        rate_20,
        rate_21,
        rate_22,
        rate_23,
        rate_24,
        blend_pct1,
        blend_pct2,
        blend_pct3,
        blend_pct4,
        blend_pct5,
		blend_pct6,
        num_FP_recipe_data
    };

enum FP_analog_data
    {
        cal1_count_1,
        cal1_count_2,
        cal1_count_3,
        cal1_count_4,
        cal1_count_5,
        cal1_count_6,
        cal2_count_1,
        cal2_count_2,
        cal2_count_3,
        cal2_count_4,
        cal2_count_5,
        cal2_count_6,
        min_eng_value_1,
        min_eng_value_2,
        min_eng_value_3,
        min_eng_value_4,
        min_eng_value_5,
        min_eng_value_6,
        max_eng_value_1,
        max_eng_value_2,
        max_eng_value_3,
        max_eng_value_4,
        max_eng_value_5,
        max_eng_value_6,
        rtd_offset_1,
        rtd_offset_2,
		rtd_offset_3,
		rtd_offset_4,
		rtd_offset_5,
		rtd_offset_6,
        num_FP_analog_data
    };

enum FP_inj_data
{
	// Inj #1
    inj_k_factor1,     
    inj_meter_factor1, 
    inj_high_tol_1,
    inj_low_tol_1,

	// Inj #2
    inj_k_factor2,     
    inj_meter_factor2, 
    inj_high_tol_2,
    inj_low_tol_2,

	// Inj #3
    inj_k_factor3,     
    inj_meter_factor3, 
    inj_high_tol_3,
    inj_low_tol_3,

	// Inj #4
    inj_k_factor4,     
    inj_meter_factor4, 
    inj_high_tol_4,
    inj_low_tol_4,

	// Inj #5
    inj_k_factor5,     
    inj_meter_factor5, 
    inj_high_tol_5,
    inj_low_tol_5,

	// Inj #6
    inj_k_factor6,     
    inj_meter_factor6, 
    inj_high_tol_6,
    inj_low_tol_6,

	// Inj #7
    inj_k_factor7,     
    inj_meter_factor7, 
    inj_high_tol_7,
    inj_low_tol_7,

	// Inj #8
    inj_k_factor8,     
    inj_meter_factor8, 
    inj_high_tol_8,
    inj_low_tol_8,

	// Inj #9
    inj_k_factor9,     
    inj_meter_factor9, 
    inj_high_tol_9,
    inj_low_tol_9,

	// Inj #10
    inj_k_factor10,     
    inj_meter_factor10, 
    inj_high_tol_10,
    inj_low_tol_10,

	// Inj #11
    inj_k_factor11,     
    inj_meter_factor11, 
    inj_high_tol_11,
    inj_low_tol_11,

	// Inj #12
    inj_k_factor12,     
    inj_meter_factor12, 
    inj_high_tol_12,
    inj_low_tol_12,

	// Inj #13
    inj_k_factor13,     
    inj_meter_factor13, 
    inj_high_tol_13,
    inj_low_tol_13,

	// Inj #14
    inj_k_factor14,     
    inj_meter_factor14, 
    inj_high_tol_14,
    inj_low_tol_14,

	// Inj #15
    inj_k_factor15,     
    inj_meter_factor15, 
    inj_high_tol_15,
    inj_low_tol_15,

	// Inj #16
    inj_k_factor16,     
    inj_meter_factor16, 
    inj_high_tol_16,
    inj_low_tol_16,

	// Inj #17
    inj_k_factor17,     
    inj_meter_factor17, 
    inj_high_tol_17,
    inj_low_tol_17,

	// Inj #18
    inj_k_factor18,     
    inj_meter_factor18, 
    inj_high_tol_18,
    inj_low_tol_18,

	// Inj #19
    inj_k_factor19,     
    inj_meter_factor19, 
    inj_high_tol_19,
    inj_low_tol_19,

	// Inj #20
    inj_k_factor20,     
    inj_meter_factor20, 
    inj_high_tol_20,
    inj_low_tol_20,

	// Inj #21
    inj_k_factor21,     
    inj_meter_factor21, 
    inj_high_tol_21,
    inj_low_tol_21,

	// Inj #22
    inj_k_factor22,     
    inj_meter_factor22, 
    inj_high_tol_22,
    inj_low_tol_22,

	// Inj #23
    inj_k_factor23,     
    inj_meter_factor23, 
    inj_high_tol_23,
    inj_low_tol_23,

	// Inj #24
    inj_k_factor24,     
    inj_meter_factor24, 
    inj_high_tol_24,
    inj_low_tol_24,

    /*added rev 10.02*/
    // Inj #1
	inj_min_flow_1,
	inj_max_flow_1,
	inj_flow_tol_1,
	inj_sec_trip_1,

    // Inj #2
	inj_min_flow_2,
	inj_max_flow_2,
	inj_flow_tol_2,
	inj_sec_trip_2,

    // Inj #3
	inj_min_flow_3,
	inj_max_flow_3,
	inj_flow_tol_3,
	inj_sec_trip_3,
	
    // Inj #4
	inj_min_flow_4,
	inj_max_flow_4,
	inj_flow_tol_4,
	inj_sec_trip_4,
	
	inj_kp_1,
	inj_kp_2,
	inj_kp_3,
	inj_kp_4,

	inj_ki_1,
	inj_ki_2,
	inj_ki_3,
	inj_ki_4,

	inj_kd_1,
	inj_kd_2,
	inj_kd_3,
	inj_kd_4,

	inj_pid_intval_1,
	inj_pid_intval_2,
	inj_pid_intval_3,
	inj_pid_intval_4,

	inj_dens_1,
	inj_maint_temp_1,
	inj_high_temp_alarm_1,
	inj_low_temp_alarm_1,

	inj_dens_2,
	inj_maint_temp_2,
	inj_high_temp_alarm_2,
	inj_low_temp_alarm_2,

	inj_dens_3,
	inj_maint_temp_3,
	inj_high_temp_alarm_3,
	inj_low_temp_alarm_3,

	inj_dens_4,
	inj_maint_temp_4,
	inj_high_temp_alarm_4,
	inj_low_temp_alarm_4,

	inj_rate_cutoff_1,
	inj_rate_cutoff_2,
	inj_rate_cutoff_3,
	inj_rate_cutoff_4,
	num_FP_inj_data
};

enum FP_tran_run_data
    {
        tran_avg_mfac,
        tran_avg_temp,
        tran_avg_dens,
        tran_avg_pres,
        tran_avg_ctl,
        tran_avg_cpl,
        preset_vol,
        cur_frate,
		cur_frate_hr,
		cur_frate_min,
		dens_sample1,
		dens_sample2,
		dens_sample3,
		dens_sample4,
		dens_sample5,
		dens_sample6,
		dens_sample7,
		dens_sample8,
		dens_sample9,
		dens_sample10,
		prv_coeff,
		prv_avg_mfac,
		prv_old_mfac,
		prv_mfac_frate,
		entered_preset,
		alge_fp_96,
		alge_fp_97,
		alge_fp_98,
		alge_fp_99,
		alge_fp_100,
        num_FP_tran_run_data
     };


enum FP_batch_run_data
    {
        avg_frate,
        avg_mfac,
        avg_temp,
        avg_dens,
        avg_pres,
        avg_ctl,
        avg_cpl,
		percent_contam,
		last_den_sample,
		prv_ctsp,
		prv_ctlp,
		prv_ctlm,
		prv_iv,
		prv_mtr_iv,
		prv_temp,
		prv_mtr_temp,
		prv_new_mfac,
		prv_frate,
		prv_avg_dens,
        num_FP_batch_run_data
    };

enum FP_product_run_data
    {
        prd1_cur_frate,
		prd1_cur_frate_hr,
		prd1_cur_frate_min,
        prd1_cur_mfac,
        prd1_cur_temp,
        prd1_cur_dens,
        prd1_cur_pres,
        prd1_cur_vap_pres,
		prd1_blend_ratio,
		prd1_cur_ref_dens,
		prd1_instant_blend_ratio,
        num_FP_product_run_data
     };

enum FP_prd_batch_run_data
    {
        batch_p1_avg_frate,
        batch_p2_avg_frate,
        batch_p3_avg_frate,
        batch_p4_avg_frate,
        batch_p5_avg_frate,
        batch_p6_avg_frate,
        batch_p1_avg_mfac,
        batch_p2_avg_mfac,
        batch_p3_avg_mfac,
        batch_p4_avg_mfac,
        batch_p5_avg_mfac,
        batch_p6_avg_mfac,
        batch_p1_avg_temp,
        batch_p2_avg_temp,
        batch_p3_avg_temp,
        batch_p4_avg_temp,
        batch_p5_avg_temp,
        batch_p6_avg_temp,
        batch_p1_avg_dens,
        batch_p2_avg_dens,
        batch_p3_avg_dens,
        batch_p4_avg_dens,
        batch_p5_avg_dens,
        batch_p6_avg_dens,
        batch_p1_avg_pres,
        batch_p2_avg_pres,
        batch_p3_avg_pres,
        batch_p4_avg_pres,
        batch_p5_avg_pres,
        batch_p6_avg_pres,
        batch_p1_avg_ctl,
        batch_p2_avg_ctl,
        batch_p3_avg_ctl,
        batch_p4_avg_ctl,
        batch_p5_avg_ctl,
        batch_p6_avg_ctl,
        batch_p1_avg_cpl,
        batch_p2_avg_cpl,
        batch_p3_avg_cpl,
        batch_p4_avg_cpl,
        batch_p5_avg_cpl,
        batch_p6_avg_cpl,
        batch_p1_avg_ccf,
        batch_p2_avg_ccf,
        batch_p3_avg_ccf,
        batch_p4_avg_ccf,
        batch_p5_avg_ccf,
        batch_p6_avg_ccf,
        batch_p1_ref_den,
        batch_p2_ref_den,
        batch_p3_ref_den,
        batch_p4_ref_den,
        batch_p5_ref_den,
        batch_p6_ref_den,
        batch_p1_rel_den,
        batch_p2_rel_den,
        batch_p3_rel_den,
        batch_p4_rel_den,
        batch_p5_rel_den,
        batch_p6_rel_den,
        batch_p1_api_den,
        batch_p2_api_den,
        batch_p3_api_den,
        batch_p4_api_den,
        batch_p5_api_den,
        batch_p6_api_den,
        batch_p1_avg_vap_pres,
        batch_p2_avg_vap_pres,
        batch_p3_avg_vap_pres,
        batch_p4_avg_vap_pres,
        batch_p5_avg_vap_pres,
        batch_p6_avg_vap_pres,
        batch_p1_avg_ctpl,
        batch_p2_avg_ctpl,
        batch_p3_avg_ctpl,
        batch_p4_avg_ctpl,
        batch_p5_avg_ctpl,
        batch_p6_avg_ctpl,
		batch_p1_rd_at_dt,
		batch_p2_rd_at_dt,
		batch_p3_rd_at_dt,
		batch_p4_rd_at_dt,
		batch_p5_rd_at_dt,
		batch_p6_rd_at_dt,
		batch_p1_E_tab_rd_60,
		batch_p2_E_tab_rd_60,
		batch_p3_E_tab_rd_60,
		batch_p4_E_tab_rd_60,
		batch_p5_E_tab_rd_60,
		batch_p6_E_tab_rd_60,
		batch_p1_eth_grade_byvol,
		batch_p2_eth_grade_byvol,
		batch_p3_eth_grade_byvol,
		batch_p4_eth_grade_byvol,
		batch_p5_eth_grade_byvol,
		batch_p6_eth_grade_byvol,
		batch_p1_ME_read_dens,
		batch_p2_ME_read_dens,
		batch_p3_ME_read_dens,
		batch_p4_ME_read_dens,
		batch_p5_ME_read_dens,
		batch_p6_ME_read_dens,
		batch_p1_ME_20_dens,
		batch_p2_ME_20_dens,
		batch_p3_ME_20_dens,
		batch_p4_ME_20_dens,
		batch_p5_ME_20_dens,
		batch_p6_ME_20_dens,
        num_FP_prd_batch_run_data
    };


enum  FP_analog_run_data
    {
        count,
        ana_value,
        eng_value
    };

enum FP_recipe_run_data
	{
		min_rec_preset,
		p1_hi_flow,
		p1_sec_hi_flow,
		p1_low_flow,
		p2_hi_flow,
		p2_sec_hi_flow,
		p2_low_flow,
		p3_hi_flow,
		p3_sec_hi_flow,
		p3_low_flow,
		p4_hi_flow,
		p4_sec_hi_flow,
		p4_low_flow,
		p5_hi_flow,
		p5_sec_hi_flow,
		p5_low_flow,
		p6_hi_flow,
		p6_sec_hi_flow,
		p6_low_flow
	 };

enum FP_mtr_run_data
	{
	   cur_ana_val_percent,
	   TMD_sig,
	   TMD_dev,
	   TMD_blade_sig,
	   TMD_blade_dev,
	   TMD_rot_sig,
	   TMD_rot_dev,
	   TMD_cur,
	   recent_valve_close_tm,
	   recent_valve_close_amt,
	   recent_valve_close_fr,
	   num_FP_mtr_run_data
	};   	


enum FP_meter_commands
	{
	   TMC_sig,
	   TMC_dev,
	   TMC_blade_sig,
	   TMC_blade_dev,
	   TMC_rot_sig,
	   TMC_rot_dev,
	   num_FP_meter_commands
	};   	



enum FP_inj_run_data
    {
        live_vol_per_inj_1,
        live_vol_per_inj_2,
        live_vol_per_inj_3,
        live_vol_per_inj_4,
        live_vol_per_inj_5,
        live_vol_per_inj_6,
        live_vol_per_inj_7,
        live_vol_per_inj_8,
        live_vol_per_inj_9,
        live_vol_per_inj_10,
        live_vol_per_inj_11,
        live_vol_per_inj_12,
        live_vol_per_inj_13,
        live_vol_per_inj_14,
        live_vol_per_inj_15,
        live_vol_per_inj_16,
        live_vol_per_inj_17,
        live_vol_per_inj_18,
        live_vol_per_inj_19,
        live_vol_per_inj_20,
        live_vol_per_inj_21,
        live_vol_per_inj_22,
        live_vol_per_inj_23,
        live_vol_per_inj_24,
        live_vol_per_cycle_1,
        live_vol_per_cycle_2,
        live_vol_per_cycle_3,
        live_vol_per_cycle_4,
        live_vol_per_cycle_5,
        live_vol_per_cycle_6,
        live_vol_per_cycle_7,
        live_vol_per_cycle_8,
        live_vol_per_cycle_9,
        live_vol_per_cycle_10,
        live_vol_per_cycle_11,
        live_vol_per_cycle_12,
        live_vol_per_cycle_13,
        live_vol_per_cycle_14,
        live_vol_per_cycle_15,
        live_vol_per_cycle_16,
        live_vol_per_cycle_17,
        live_vol_per_cycle_18,
        live_vol_per_cycle_19,
        live_vol_per_cycle_20,
        live_vol_per_cycle_21,
        live_vol_per_cycle_22,
        live_vol_per_cycle_23,
        live_vol_per_cycle_24,
		fc_inj_cur_temp_1,
		fc_inj_cur_temp_2,
		fc_inj_cur_temp_3,
		fc_inj_cur_temp_4,
		fc_inj_avg_temp_1,
		fc_inj_avg_temp_2,
		fc_inj_avg_temp_3,
		fc_inj_avg_temp_4,
		fc_inj_avg_dens_1,
		fc_inj_avg_dens_2,
		fc_inj_avg_dens_3,
		fc_inj_avg_dens_4,
		fc_inj_avg_ctl_1,
		fc_inj_avg_ctl_2,
		fc_inj_avg_ctl_3,
		fc_inj_avg_ctl_4,
		num_FP_inj_run_data
    };

enum FP_algebool_data                         /* rev2 */
    {
        alge_fp_data,
        num_FP_algebool_data
    };


enum FP_analog_commands
    {
        set_eng_val_out,
        num_FP_analog_commands
    };


enum DP_tran_run_data
    {
        tran_cur_raw,
        tran_cur_grs,
        tran_cur_gst,
        tran_cur_gsv,
        tran_cur_mass,
        remain_vol,
        tran_cur_add1,
        tran_cur_add2,
        tran_cur_add3,
        tran_cur_add4,
        tran_cur_add5,
        tran_cur_add6,
        tran_cur_add7,
        tran_cur_add8,
        tran_cur_add9,
        tran_cur_add10,
        tran_cur_add11,
        tran_cur_add12,
        tran_cur_add13,
        tran_cur_add14,
        tran_cur_add15,
        tran_cur_add16,
        tran_cur_add17,
        tran_cur_add18,
        tran_cur_add19,
        tran_cur_add20,
        tran_cur_add21,
        tran_cur_add22,
        tran_cur_add23,
        tran_cur_add24,
		tran_vap_recover,
		tran_straight_vrs_net,
		tran_nrst_vap_recover,
		tran_nrst_start_vaprec,
        num_DP_tran_run_data
    };

enum DP_bay_run_data
    {
        btran_cur_raw,
        btran_cur_grs,
        btran_cur_gst,
        btran_cur_gsv,
        btran_cur_mass,
        btran_cur_add1,
        btran_cur_add2,
        btran_cur_add3,
        btran_cur_add4,
        btran_cur_add5,
        btran_cur_add6,
        btran_cur_add7,
        btran_cur_add8,
        btran_cur_add9,
        btran_cur_add10,
        btran_cur_add11,
        btran_cur_add12,
        btran_cur_add13,
        btran_cur_add14,
        btran_cur_add15,
        btran_cur_add16,
        btran_cur_add17,
        btran_cur_add18,
        btran_cur_add19,
        btran_cur_add20,
        btran_cur_add21,
        btran_cur_add22,
        btran_cur_add23,
        btran_cur_add24,
		btran_vap_recover,
		btran_straight_vrs_net,
        num_DP_bay_run_data
    };


enum DP_prd_run_data
    {
        prd_cur_raw,
        prd_cur_grs,
        prd_cur_gst,
        prd_cur_gsv,
        prd_cur_mass,
        prd_nonres_raw,
        prd_nonres_gross,
        prd_nonres_gst,
        prd_nonres_gsv,
        prd_nonres_mass,
		prd_blend_error,
		prd_nrst_start_raw,
        prd_nrst_start_gross,
        prd_nrst_start_gst,
        prd_nrst_start_gsv,
        prd_nrst_start_mass,
        num_DP_prd_run_data
    };

enum DP_batch_run_data
    {
        total_pulses,
        cur_raw,
        cur_grs,
        cur_gst,
        cur_gsv,
        cur_mass,
        cur_add1,
        cur_add2,
        cur_add3,
        cur_add4,
        cur_add5,
        cur_add6,
        cur_add7,
        cur_add8,
        cur_add9,
        cur_add10,
        cur_add11,
        cur_add12,
        cur_add13,
        cur_add14,
        cur_add15,
        cur_add16,
        cur_add17,
        cur_add18,
        cur_add19,
        cur_add20,
        cur_add21,
        cur_add22,
        cur_add23,
        cur_add24,
		fc_add_1_raw,
		fc_add_2_raw,
		fc_add_3_raw,
		fc_add_4_raw,
		fc_add_1_grs,
		fc_add_2_grs,
		fc_add_3_grs,
		fc_add_4_grs,
		fc_add_1_gst,
		fc_add_2_gst,
		fc_add_3_gst,
		fc_add_4_gst,
		fc_add_1_mass,
		fc_add_2_mass,
		fc_add_3_mass,
		fc_add_4_mass,
		cur_vap_recover,
		batch_straight_vrs_net,
		num_DP_batch_run_data
    };

enum DP_prd_batch_run_data
    {
        batch_p1_total_pulses,
        batch_p2_total_pulses,
        batch_p3_total_pulses,
        batch_p4_total_pulses,
        batch_p5_total_pulses,
        batch_p6_total_pulses,
        batch_p1_cur_raw,
        batch_p2_cur_raw,
        batch_p3_cur_raw,
        batch_p4_cur_raw,
        batch_p5_cur_raw,
        batch_p6_cur_raw,
        batch_p1_cur_grs,
        batch_p2_cur_grs,
        batch_p3_cur_grs,
        batch_p4_cur_grs,
        batch_p5_cur_grs,
        batch_p6_cur_grs,
        batch_p1_cur_gst,
        batch_p2_cur_gst,
        batch_p3_cur_gst,
        batch_p4_cur_gst,
        batch_p5_cur_gst,
        batch_p6_cur_gst,
        batch_p1_cur_gsv,
        batch_p2_cur_gsv,
        batch_p3_cur_gsv,
        batch_p4_cur_gsv,
        batch_p5_cur_gsv,
        batch_p6_cur_gsv,
        batch_p1_cur_mass,
        batch_p2_cur_mass,
        batch_p3_cur_mass,
        batch_p4_cur_mass,
        batch_p5_cur_mass,
        batch_p6_cur_mass
    };

enum DP_inj_run_data
    {
        additive_1_non_resetable_total,
        additive_2_non_resetable_total,
        additive_3_non_resetable_total,
        additive_4_non_resetable_total,
        additive_5_non_resetable_total,
        additive_6_non_resetable_total,
        additive_7_non_resetable_total,
        additive_8_non_resetable_total,
        additive_9_non_resetable_total,
        additive_10_non_resetable_total,
        additive_11_non_resetable_total,
        additive_12_non_resetable_total,
        additive_13_non_resetable_total,
        additive_14_non_resetable_total,
        additive_15_non_resetable_total,
        additive_16_non_resetable_total,
        additive_17_non_resetable_total,
        additive_18_non_resetable_total,
        additive_19_non_resetable_total,
        additive_20_non_resetable_total,
        additive_21_non_resetable_total,
        additive_22_non_resetable_total,
        additive_23_non_resetable_total,
        additive_24_non_resetable_total,
        additive_1_non_resetable_total_leak,
        additive_2_non_resetable_total_leak,
        additive_3_non_resetable_total_leak,
        additive_4_non_resetable_total_leak,
        additive_5_non_resetable_total_leak,
        additive_6_non_resetable_total_leak,
        additive_7_non_resetable_total_leak,
        additive_8_non_resetable_total_leak,
        additive_9_non_resetable_total_leak,
        additive_10_non_resetable_total_leak,
        additive_11_non_resetable_total_leak,
        additive_12_non_resetable_total_leak,
        additive_13_non_resetable_total_leak,
        additive_14_non_resetable_total_leak,
        additive_15_non_resetable_total_leak,
        additive_16_non_resetable_total_leak,
        additive_17_non_resetable_total_leak,
        additive_18_non_resetable_total_leak,
        additive_19_non_resetable_total_leak,
        additive_20_non_resetable_total_leak,
        additive_21_non_resetable_total_leak,
        additive_22_non_resetable_total_leak,
        additive_23_non_resetable_total_leak,
        additive_24_non_resetable_total_leak,
		num_DP_inj_run_data
    };


enum DP_recipe_run_data
	{
	  rec_nonres_raw,
	  rec_nonres_gross,
	  rec_nonres_gst,
	  rec_nonres_gsv,
	  rec_nonres_mass,
	  num_DP_recipe_run_data	
	};


enum UN_CH_system_data
    {
        pulse_mode_type,
        xmit_integrity,
        pul_func_1,
        pul_func_2,
        pul_unit_1,
        pul_unit_2,
        flow_rate_units,
        dyn_disp_timeout,
        auto_reset_timer,
        dec_comma_sel,
        start_key_disable,
        def_trans_lits,
        batch_per_tran,
        vol_units,
        mass_units,
        trans_term,
        auto_prv_sel,
        prv_mode,
        blank_downcounter,
        preset_vol_type,
        delivery_vol_type,
        display_resolution,
        temp_units,
        dens_units,
        press_units,
        clr_able_alrm,
        com_lnk_prog,
        modbus_endian,
        start_option,      
        vol_used,
        stop_option,       
        max_feedback_errors,              
        num_physical_arms,
        arm_1_config,
        arm_1_product,
        arm_2_config,
        arm_2_product,
        num_inj_used,
        recipes_per_tran,
        comm_addr1,
        comm_addr2,
        comm_addr3,
        comm_addr4,
        powerfail_alarm,
        arm_3_config,
        arm_3_product,
        arm_4_config,
        arm_4_product,
        zoom_reset_timer,
        pul_mtr_1,
        pul_mtr_2,
        arm_5_config, 
        arm_5_product,
        arm_6_config,
        arm_6_product,
        stop_key_action,
        comm_addr5,
        comm_addr6,
        sys_status_display,
        sys_permissive_1_type,
        sys_permissive_1_start,
        sys_permissive_2_type,
        sys_permissive_2_start,
        sys_permissive_3_type,
        sys_permissive_3_start,
		RBM_prod_map_arm1,
		RBM_prod_map_arm2,
		RBM_prod_map_arm3,
		RBM_prod_map_arm4,
		RBM_prod_map_arm5,
		RBM_prod_map_arm6,
		comm_timeout_action,
		inhibit_auto_focus,
		pulse_in_type,
		prover_output_mtr,
		card_validation,
		card_timeout,
		piston_stop_action,
		trans_start,
		del_vol_disp,
		flow_add_totals,
		card_config,
		inj_pulse_mode_type,
		inj_error_reset,
		inj_error_amt,
		num_ratio_prds_1,
		num_ratio_prds_2,
		num_ratio_prds_3,
		num_ratio_prds_4,
		num_ratio_prds_5,
		num_ratio_prds_6,
		rev_vol_batch,
		rev_vol_nr,
		pul_func_3,
		pul_func_4,
		pul_func_5,
		pul_unit_3,
		pul_unit_4,
		pul_unit_5,
		pul_mtr_3,
		pul_mtr_4,
		pul_mtr_5,
		dens_prompt,
		ethernet_control,
		user_text_saved,
		stop_key_disable,
		bluetooth_master,
		add_stop_action,
		update_the_leakage,
		card_authorize,
		print_standby,
		auto_reprint,
		solenoid_count_clear,
		auto_tear_off,
//		nedap_config,
		vehicle_id_tag,
		da_alarms_function,
		num_UN_CH_system_data
    };


enum UN_CH_bay_data
	{
		rep_sel_bay,
		rep_res_bay,
		rep_pages_bay,
		rep_hm_bay,
		bay_perm_1_type,
		bay_perm_1_start,
		bay_perm_2_type,
		bay_perm_2_start,
		num_UN_CH_bay_data
	};



enum UN_CH_prompt_data
    {
        prompts_in_use,
        prompt_timeout,
        input_type_1,
        length_1,
        input_type_2,
        length_2,
        input_type_3,
        length_3,
        input_type_4,
        length_4,
        input_type_5,
        length_5,
		prompt_mode,
		prompt_valid,
        num_UN_CH_prompt_data
    };

enum UN_CH_arm_data
    {
        permissive_1_type,
        permissive_1_start,
        permissive_2_type,
        permissive_2_start,
        low_flow_start_cond,
        arm_zero_flow_timer,
        valve_delay_on,
        pump_delay_off,
        valve_fault_timeout,
        report_sel,
        clean_product,
        clean_alarm_limit,
        ratio_time,
        bv_pos,
        blend_correction,
        rep_vol_res,
		rpt_pages,
		rpt_hm_class,
	   	bay_assignment,
		clean_line_blend,
		add_start,
		unlimited_preset,
		trans_reset_start_hr,
		blend_error_reset,
		virtual_swing_arm,
        ratio_blend_alg,
        ratio_prd_min_flow,
		first_sec_hf_sel,
        num_UN_CH_arm_data
    };

enum UN_CH_meter_data
    {
        valve_type,
        mtr_zero_flow_timer,
        dp_error_reset,
        sol1_units,
        sar1_units,
        ugc1_units,
        od1_units,
        dens_in_type,
		turbine_mtr_blades,
		turbine_mtr_alarm_tol,
		pulse_sec_alrm_vol,
		share_temp,
		share_dens,
		share_pres,
		mass_mtr_type,
		mass_mtr_mult,
		mass_mtr_lfc,
		mass_mtr_tube,
		mass_mtr_model,
		pulse_period_sample_count,
		hybrid_mtr_plumb,
		num_UN_CH_meter_data
    };

enum UN_CH_product_data
    {
        sec_trip_auto_adjust,
        mfv_select,
        api_table,
        min_bp_flow_rate_timer,
        bp_flow_recover_timer,
        vp_calc_method,
        bv_delay_open,
        bv_delay_close,
		calc_cur_ref_dens,
		aromatic_prd,
        num_UN_CH_product_data
    };

enum UN_CH_recipe_data
{
    recipe_used,
    hm_class_prod,
    blend_comp1,
    blend_comp2,
    blend_comp3,
    blend_comp4,
    blend_comp5,
	blend_comp6,
    inj_prod1,                              
    inj_prod2,                              
    inj_prod3,                              
    inj_prod4,                              
    inj_prod5,                              
    inj_prod6,                              
    inj_prod7,                              
    inj_prod8,                              
    inj_prod9,                              
    inj_prod10,                             
    inj_prod11,                             
    inj_prod12,                             
    inj_prod13,                             
    inj_prod14,                             
    inj_prod15,                             
    inj_prod16,                             
    inj_prod17,                             
    inj_prod18,                             
    inj_prod19,                             
    inj_prod20,                             
    inj_prod21,                             
    inj_prod22,                             
    inj_prod23,                             
    inj_prod24,                             
    clean_deduct_prod,
	rec_clean_line_prd,
	ratio_seq_mode,
    num_UN_CH_recipe_data
};

enum UN_CH_digital_data
    {
        dig_func_in_1,
        dig_func_in_2,
        dig_func_in_3,
        dig_func_in_4,
        dig_func_in_5,
        dig_func_in_6,
        dig_func_in_7,
        dig_func_in_8,
        dig_func_in_9,
        dig_func_in_10,
        dig_func_in_11,
		dig_func_in_12,
		dig_func_in_13,
		dig_func_in_14,
		dig_func_in_15,
		bio_func_in_1,
		bio_func_in_2,
		bio_func_in_3,
		bio_func_in_4,
		bio_func_in_5,
		bio_func_in_6,
		bio_func_in_7,
		bio_func_in_8,
        dig_func_in_24,
        dig_func_in_25,
        dig_func_in_26,
        dig_func_in_27,
        dig_func_in_28,
        dig_func_in_29,
        dig_func_in_30,
        dig_func_in_31,
        dig_func_in_32,
        dig_func_in_33,
        dig_func_in_34,
		dig_func_in_35,
		dig_func_in_36,
		dig_func_in_37,
		dig_func_in_38,
        dig_func_in_39,
        dig_func_in_40,
        dig_func_in_41,
        dig_func_in_42,
        dig_func_in_43,

        dig_func_out_1,
        dig_func_out_2,
        dig_func_out_3,
        dig_func_out_4,
        dig_func_out_5,
        dig_func_out_6,
        dig_func_out_7,
        dig_func_out_8,
        dig_func_out_9,
        dig_func_out_10,
        dig_func_out_11,
        dig_func_out_12,
        dig_func_out_13,
        dig_func_out_14,
        dig_func_out_15,
        dig_func_out_16,
        dig_func_out_17,
        dig_func_out_18,
        dig_func_out_19,
        dig_func_out_20,
        dig_func_out_21,
        dig_func_out_22,
        dig_func_out_23,
        dig_func_out_24,
        dig_func_out_25,
        dig_func_out_26,
        dig_func_out_27,
        dig_func_out_28,
        dig_func_out_29,
        dig_func_out_30,
		bio_func_out_1,
		bio_func_out_2,
		bio_func_out_3,
		bio_func_out_4,
		bio_func_out_5,
		bio_func_out_6,
		bio_func_out_7,
		bio_func_out_8,
        dig_func_out_39,
        dig_func_out_40,
        dig_func_out_41,
        dig_func_out_42,
        dig_func_out_43,
        dig_func_out_44,
        dig_func_out_45,
        dig_func_out_46,
        dig_func_out_47,
        dig_func_out_48,
        dig_func_out_49,
        dig_func_out_50,
        dig_func_out_51,
        dig_func_out_52,
        dig_func_out_53,
        dig_func_out_54,
        dig_func_out_55,
        dig_func_out_56,
        dig_func_out_57,
        dig_func_out_58,
        dig_func_out_59,
        dig_func_out_60,
        dig_func_out_61,
        dig_func_out_62,
        dig_func_out_63,
        dig_func_out_64,
        dig_func_out_65,
        dig_func_out_66,
        dig_func_out_67,
        dig_func_out_68,
        dig_func_out_69,
        dig_func_out_70,
        dig_func_out_71,
        dig_func_out_72,
        dig_func_out_73,
        dig_func_out_74,
        dig_func_out_75,
        dig_func_out_76,
        dig_func_out_77,
        dig_func_out_78,

        dig_in_1_arm,
        dig_in_2_arm,
        dig_in_3_arm,
        dig_in_4_arm,
        dig_in_5_arm,
        dig_in_6_arm,
        dig_in_7_arm,
        dig_in_8_arm,
        dig_in_9_arm,
        dig_in_10_arm,
        dig_in_11_arm,
        dig_in_12_arm,
        dig_in_13_arm,
        dig_in_14_arm,
        dig_in_15_arm,
		bio_in_1_arm,
		bio_in_2_arm,
		bio_in_3_arm,
		bio_in_4_arm,
		bio_in_5_arm,
		bio_in_6_arm,
		bio_in_7_arm,
		bio_in_8_arm,
        dig_in_24_arm,
        dig_in_25_arm,
        dig_in_26_arm,
        dig_in_27_arm,
        dig_in_28_arm,
        dig_in_29_arm,
        dig_in_30_arm,
        dig_in_31_arm,
        dig_in_32_arm,
        dig_in_33_arm,
        dig_in_34_arm,
        dig_in_35_arm,
        dig_in_36_arm,
        dig_in_37_arm,
        dig_in_38_arm,
        dig_in_39_arm,
        dig_in_40_arm,
        dig_in_41_arm,
        dig_in_42_arm,
        dig_in_43_arm,
		
        dig_out_1_arm,
        dig_out_2_arm,
        dig_out_3_arm,
        dig_out_4_arm,
        dig_out_5_arm,
        dig_out_6_arm,
        dig_out_7_arm,
        dig_out_8_arm,
        dig_out_9_arm,
        dig_out_10_arm,
        dig_out_11_arm,
        dig_out_12_arm,
        dig_out_13_arm,
        dig_out_14_arm,
        dig_out_15_arm,
        dig_out_16_arm,
        dig_out_17_arm,
        dig_out_18_arm,
        dig_out_19_arm,
        dig_out_20_arm,
        dig_out_21_arm,
        dig_out_22_arm,
        dig_out_23_arm,
        dig_out_24_arm,
        dig_out_25_arm,
        dig_out_26_arm,
        dig_out_27_arm,
        dig_out_28_arm,
        dig_out_29_arm,
        dig_out_30_arm,
		bio_out_1_arm,
		bio_out_2_arm,
		bio_out_3_arm,
		bio_out_4_arm,
		bio_out_5_arm,
		bio_out_6_arm,
		bio_out_7_arm,
		bio_out_8_arm,
        dig_out_39_arm,
        dig_out_40_arm,
        dig_out_41_arm,
        dig_out_42_arm,
        dig_out_43_arm,
        dig_out_44_arm,
        dig_out_45_arm,
        dig_out_46_arm,
        dig_out_47_arm,
        dig_out_48_arm,
        dig_out_49_arm,
        dig_out_50_arm,
        dig_out_51_arm,
        dig_out_52_arm,
        dig_out_53_arm,
        dig_out_54_arm,
        dig_out_55_arm,
        dig_out_56_arm,
        dig_out_57_arm,
        dig_out_58_arm,
        dig_out_59_arm,
        dig_out_60_arm,
        dig_out_61_arm,
        dig_out_62_arm,
        dig_out_63_arm,
        dig_out_64_arm,
        dig_out_65_arm,
        dig_out_66_arm,
        dig_out_67_arm,
        dig_out_68_arm,
        dig_out_69_arm,
        dig_out_70_arm,
        dig_out_71_arm,
        dig_out_72_arm,
        dig_out_73_arm,
        dig_out_74_arm,
        dig_out_75_arm,
        dig_out_76_arm,
        dig_out_77_arm,
        dig_out_78_arm,
		num_UN_CH_digital_data

};		
enum UN_CH_digital_data_2
{
        dig_in_1_mtr,
        dig_in_2_mtr,
        dig_in_3_mtr,
        dig_in_4_mtr,
        dig_in_5_mtr,
        dig_in_6_mtr,
        dig_in_7_mtr,
        dig_in_8_mtr,
        dig_in_9_mtr,
        dig_in_10_mtr,
        dig_in_11_mtr,
        dig_in_12_mtr,
        dig_in_13_mtr,
        dig_in_14_mtr,
        dig_in_15_mtr,
		bio_in_1_mtr,
		bio_in_2_mtr,
		bio_in_3_mtr,
		bio_in_4_mtr,
		bio_in_5_mtr,
		bio_in_6_mtr,
		bio_in_7_mtr,
		bio_in_8_mtr,
        dig_in_24_mtr,
        dig_in_25_mtr,
        dig_in_26_mtr,
        dig_in_27_mtr,
        dig_in_28_mtr,
        dig_in_29_mtr,
        dig_in_30_mtr,
        dig_in_31_mtr,
        dig_in_32_mtr,
        dig_in_33_mtr,
        dig_in_34_mtr,
        dig_in_35_mtr,
        dig_in_36_mtr,
        dig_in_37_mtr,
        dig_in_38_mtr,
        dig_in_39_mtr,
        dig_in_40_mtr,
        dig_in_41_mtr,
        dig_in_42_mtr,
        dig_in_43_mtr,
		
        dig_out_1_mtr,
        dig_out_2_mtr,
        dig_out_3_mtr,
        dig_out_4_mtr,
        dig_out_5_mtr,
        dig_out_6_mtr,
        dig_out_7_mtr,
        dig_out_8_mtr,
        dig_out_9_mtr,
        dig_out_10_mtr,
        dig_out_11_mtr,
        dig_out_12_mtr,
        dig_out_13_mtr,
        dig_out_14_mtr,
        dig_out_15_mtr,
        dig_out_16_mtr,
        dig_out_17_mtr,
        dig_out_18_mtr,
        dig_out_19_mtr,
        dig_out_20_mtr,
        dig_out_21_mtr,
        dig_out_22_mtr,
        dig_out_23_mtr,
        dig_out_24_mtr,
        dig_out_25_mtr,
        dig_out_26_mtr,
        dig_out_27_mtr,
        dig_out_28_mtr,
        dig_out_29_mtr,
        dig_out_30_mtr,
		bio_out_1_mtr,
		bio_out_2_mtr,
		bio_out_3_mtr,
		bio_out_4_mtr,
		bio_out_5_mtr,
		bio_out_6_mtr,
		bio_out_7_mtr,
		bio_out_8_mtr,
        dig_out_39_mtr,
        dig_out_40_mtr,
        dig_out_41_mtr,
        dig_out_42_mtr,
        dig_out_43_mtr,
        dig_out_44_mtr,
        dig_out_45_mtr,
        dig_out_46_mtr,
        dig_out_47_mtr,
        dig_out_48_mtr,
        dig_out_49_mtr,
        dig_out_50_mtr,
        dig_out_51_mtr,
        dig_out_52_mtr,
        dig_out_53_mtr,
        dig_out_54_mtr,
        dig_out_55_mtr,
        dig_out_56_mtr,
        dig_out_57_mtr,
        dig_out_58_mtr,
        dig_out_59_mtr,
        dig_out_60_mtr,
        dig_out_61_mtr,
        dig_out_62_mtr,
        dig_out_63_mtr,
        dig_out_64_mtr,
        dig_out_65_mtr,
        dig_out_66_mtr,
        dig_out_67_mtr,
        dig_out_68_mtr,
        dig_out_69_mtr,
        dig_out_70_mtr,
        dig_out_71_mtr,
        dig_out_72_mtr,
        dig_out_73_mtr,
        dig_out_74_mtr,
        dig_out_75_mtr,
        dig_out_76_mtr,
        dig_out_77_mtr,
        dig_out_78_mtr,
		
        dig_in_1_prd,
        dig_in_2_prd,
        dig_in_3_prd,
        dig_in_4_prd,
        dig_in_5_prd,
        dig_in_6_prd,
        dig_in_7_prd,
        dig_in_8_prd,
        dig_in_9_prd,
        dig_in_10_prd,
        dig_in_11_prd,
        dig_in_12_prd,
        dig_in_13_prd,
        dig_in_14_prd,
        dig_in_15_prd,
		bio_in_1_prd,
		bio_in_2_prd,
		bio_in_3_prd,
		bio_in_4_prd,
		bio_in_5_prd,
		bio_in_6_prd,
		bio_in_7_prd,
		bio_in_8_prd,
        dig_in_24_prd,
        dig_in_25_prd,
        dig_in_26_prd,
        dig_in_27_prd,
        dig_in_28_prd,
        dig_in_29_prd,
        dig_in_30_prd,
        dig_in_31_prd,
        dig_in_32_prd,
        dig_in_33_prd,
        dig_in_34_prd,
        dig_in_35_prd,
        dig_in_36_prd,
        dig_in_37_prd,
        dig_in_38_prd,
        dig_in_39_prd,
        dig_in_40_prd,
        dig_in_41_prd,
        dig_in_42_prd,
        dig_in_43_prd,
		
        dig_out_1_prd,
        dig_out_2_prd,
        dig_out_3_prd,
        dig_out_4_prd,
        dig_out_5_prd,
        dig_out_6_prd,
        dig_out_7_prd,
        dig_out_8_prd,
        dig_out_9_prd,
        dig_out_10_prd,
        dig_out_11_prd,
        dig_out_12_prd,
        dig_out_13_prd,
        dig_out_14_prd,
        dig_out_15_prd,
        dig_out_16_prd,
        dig_out_17_prd,
        dig_out_18_prd,
        dig_out_19_prd,
        dig_out_20_prd,
        dig_out_21_prd,
        dig_out_22_prd,
        dig_out_23_prd,
        dig_out_24_prd,
        dig_out_25_prd,
        dig_out_26_prd,
        dig_out_27_prd,
        dig_out_28_prd,
        dig_out_29_prd,
        dig_out_30_prd,
		bio_out_1_prd,
		bio_out_2_prd,
		bio_out_3_prd,
		bio_out_4_prd,
		bio_out_5_prd,
		bio_out_6_prd,
		bio_out_7_prd,
		bio_out_8_prd,
        dig_out_39_prd,
        dig_out_40_prd,
        dig_out_41_prd,
        dig_out_42_prd,
        dig_out_43_prd,
        dig_out_44_prd,
        dig_out_45_prd,
        dig_out_46_prd,
        dig_out_47_prd,
        dig_out_48_prd,
        dig_out_49_prd,
        dig_out_50_prd,
        dig_out_51_prd,
        dig_out_52_prd,
        dig_out_53_prd,
        dig_out_54_prd,
        dig_out_55_prd,
        dig_out_56_prd,
        dig_out_57_prd,
        dig_out_58_prd,
        dig_out_59_prd,
        dig_out_60_prd,
        dig_out_61_prd,
        dig_out_62_prd,
        dig_out_63_prd,
        dig_out_64_prd,
        dig_out_65_prd,
        dig_out_66_prd,
        dig_out_67_prd,
        dig_out_68_prd,
        dig_out_69_prd,
        dig_out_70_prd,
        dig_out_71_prd,
        dig_out_72_prd,
        dig_out_73_prd,
        dig_out_74_prd,
        dig_out_75_prd,
        dig_out_76_prd,
        dig_out_77_prd,
        dig_out_78_prd,
		num_UN_CH_digital_data_2
    };


enum UN_CH_analog_data
    {
        analog_type_1,
        analog_type_2,
        analog_type_3,
        analog_type_4,
        analog_type_5,
        analog_type_6,
        analog_function_1,
        analog_function_2,
        analog_function_3,
        analog_function_4,
        analog_function_5,
        analog_function_6,
        analog_arm_1,
        analog_arm_2,
        analog_arm_3,
        analog_arm_4,
        analog_arm_5,
        analog_arm_6,
        analog_mtr_1,
        analog_mtr_2,
        analog_mtr_3,
        analog_mtr_4,
        analog_mtr_5,
        analog_mtr_6,

        num_UN_CH_analog_data
    };

enum UN_CH_pulse_in_data
    {
        pulse_func_1,
        pulse_func_2,
        pulse_func_3,
        pulse_func_4,
        pulse_func_5,
        pulse_func_6,
        pulse_func_7,
        pulse_func_8,
        pulse_func_9,
        pulse_func_10,
        pulse_func_11,
        pulse_func_12,
        pulse_arm_3,
        pulse_arm_4,
        pulse_arm_5,
        pulse_arm_6,
        pulse_arm_7,
        pulse_arm_8,
        pulse_arm_9,
        pulse_arm_10,
        pulse_arm_11,
        pulse_arm_12,
        pulse_mtr_3,
        pulse_mtr_4,
        pulse_mtr_5,
        pulse_mtr_6,
        pulse_mtr_7,
        pulse_mtr_8,
        pulse_mtr_9,
        pulse_mtr_10,
        pulse_mtr_11,
        pulse_mtr_12,
        num_UN_CH_pulse_in_data
    };

enum UN_CH_comm_data
    {
        protocol_1,
        protocol_2,
        protocol_3,
        protocol_4,
        baud_rate_1,
        baud_rate_2,
        baud_rate_3,
        baud_rate_4,
        data_parity_1,
        data_parity_2,
        data_parity_3,
        data_parity_4,
        control_1,
        control_2,
        control_3,
        control_4,     
        num_UN_CH_comm_data
    };

enum UN_CH_alarm_config
    {
        add_comm_config,
        back_pressure_config,
        comms_error_config,
        dens_xducer_fail_config,
        add_feedback_config,
        high_dens_config,
        high_flow_config,
        high_pres_config,
        high_temp_config,
        low_additive_config,
        low_dens_config,
        low_flow_config,
        low_pres_config,
        low_temp_config,
        excess_add_pulses_config,
        no_add_pulses_config,
        sys_overrun_config,
        xmitter_integ_config,
        pres_xducer_fail_config,
        pulse_security_config,
        add_freq_config,
        shared_printer_config,      
        temp_xducer_fail_config,
        valve_fault_config,
        add_unauth_fail_config,
        sys_zero_flow_config,
        general_additive_alarm_config,
        overrev_injector_config,
        additive_clean_line_config,
        command_refused_config,
        ticket_alarm_config,    
        civacon_alarm_config,
        clean_line_alarm_config,
        block_valve_alarm_config,
        blend_high_alarm_config,
        blend_low_alarm_config,
        product_overrun_alarm_config,
        product_zero_flow_alarm_config,
        unauthorized_flow_alarm_config, 
        PTB_printer_failure_config,
        turbine_mtr_alarm_config,
        auto_detect_failed_config,
        inj_powerfail_alarm_config,
        inj_diagnostic_alarm_config,
        aicb_autodetect_config,
        aicb_comm_failed_config,
        mmi_comm_failed_config,
        mmi_excess_active_arms_config, 
        storage_full_alarm_config,
		de_head_alarm_config,
		mass_meter_comm_config,
		mass_meter_drive_config,
		mass_meter_tube_config,
		add_high_temp_config,
		add_low_temp_config,
		add_temp_probe_config,
		card_removed_config,
		add_pulse_sec_config,
		add_xmit_integ_config,
		prd_stop_config,
		add_comm_totals_config,
		comflash_alarm_config,
		network_printer_alarm_config,
		fa_sening_alarm_config,
		dig_sol_counts_config,
		promass_alarm_config,
		predict_overrun_config,
		nr_leakage_config,
		reverse_flow_config,
		report_storage_full_config,
        last_alarm_config       /* must always be last */
    };
    
enum UN_CH_user_alarm_config
    {            
        user_alarm1_config,
        user_alarm2_config,
        user_alarm3_config,
        user_alarm4_config,
        user_alarm5_config,
        user_alarm6_config,
        user_alarm7_config,
        user_alarm8_config,
        user_alarm9_config,
        user_alarm10_config,    

        last_user_alarm_config  /* must always be last */
    };

enum UN_CH_system_run_data
	{
		civicon_overfill,
		civicon_ground,  
		civicon_bypassed,
		civicon_sensor1, 
		civicon_sensor2, 
		civicon_sensor3, 
		civicon_sensor4,
		bse_online,
		display2_online,
		time_type,
		num_load_arms,
		num_UN_CH_system_run_data
	};

enum UN_CH_tran_run_data
    {
      rom_version_major,
      batch_status,
      pump_status,
      swing_arm_position,
      rom_version_minor,
	  unload_product,
	  prv_prd,
	  prv_mfac_no,
	  prv_trip_no,
	  prv_mfac_stored,
	  bool_data_96,
	  bool_data_97,
	  bool_data_98,
	  bool_data_99,
	  bool_data_100,
      num_UN_CH_tran_run_data
    };

enum UN_CH_batch_run_data
    {
        prd_no,
        recipe_no,
        hm_class_prd,
        run_batch_no,
		prv_trip_accepted,
		load_arm,
        num_UN_CH_batch_run_data
    };

enum UN_CH_inj_data
    {
        type_1, 
        type_2, 
        type_3, 
        type_4, 
        type_5, 
        type_6, 
        type_7, 
        type_8, 
        type_9, 
        type_10,
        type_11,
        type_12,
        type_13,
        type_14,
        type_15,
        type_16,
        type_17,
        type_18,
        type_19,
        type_20,
        type_21,
        type_22,
        type_23,
        type_24,

        inj_arm_1,  
        inj_arm_2,  
        inj_arm_3,  
        inj_arm_4,  
        inj_arm_5,  
        inj_arm_6,  
        inj_arm_7,  
        inj_arm_8,  
        inj_arm_9,  
        inj_arm_10,
        inj_arm_11,
        inj_arm_12,
        inj_arm_13,
        inj_arm_14,
        inj_arm_15,
        inj_arm_16,
        inj_arm_17,
        inj_arm_18,
        inj_arm_19,
        inj_arm_20,
        inj_arm_21,
        inj_arm_22,
        inj_arm_23,
        inj_arm_24,

        plumbing_1,
        plumbing_2,
        plumbing_3,
        plumbing_4,
        plumbing_5,
        plumbing_6,
        plumbing_7,
        plumbing_8,
        plumbing_9,
        plumbing_10,
        plumbing_11,
        plumbing_12,
        plumbing_13,
        plumbing_14,
        plumbing_15,
        plumbing_16,
        plumbing_17,
        plumbing_18,
        plumbing_19,
        plumbing_20,
        plumbing_21,
        plumbing_22,
        plumbing_23,
        plumbing_24,


        max_inj_tol_errors_1,
        max_inj_tol_errors_2,
        max_inj_tol_errors_3,
        max_inj_tol_errors_4,
        max_inj_tol_errors_5,
        max_inj_tol_errors_6,
        max_inj_tol_errors_7,
        max_inj_tol_errors_8,
        max_inj_tol_errors_9,
        max_inj_tol_errors_10,
        max_inj_tol_errors_11,
        max_inj_tol_errors_12,
        max_inj_tol_errors_13,
        max_inj_tol_errors_14,
        max_inj_tol_errors_15,
        max_inj_tol_errors_16,
        max_inj_tol_errors_17,
        max_inj_tol_errors_18,
        max_inj_tol_errors_19,
        max_inj_tol_errors_20,
        max_inj_tol_errors_21,
        max_inj_tol_errors_22,
        max_inj_tol_errors_23,
        max_inj_tol_errors_24,

		inj_1_valve_type,
		inj_2_valve_type,
		inj_3_valve_type,
		inj_4_valve_type,

		inj_1_api_table,
		inj_2_api_table,
		inj_3_api_table,
		inj_4_api_table,

		inj_1_share_temp,
		inj_2_share_temp,
		inj_3_share_temp,
		inj_4_share_temp,

		inj_1_flow_timeout,
		inj_2_flow_timeout,
		inj_3_flow_timeout,
		inj_4_flow_timeout,

        num_UN_CH_inj_data
    };

enum UN_CH_inj_run_data
    {
        on_off_1,
        on_off_2,
        on_off_3,
        on_off_4,
        on_off_5,
        on_off_6,
        on_off_7,
        on_off_8,
        on_off_9,
        on_off_10,
        on_off_11,
        on_off_12,
        on_off_13,
        on_off_14,
        on_off_15,
        on_off_16,
        on_off_17,
        on_off_18,
        on_off_19,
        on_off_20,
        on_off_21,
        on_off_22,
        on_off_23,
        on_off_24,
        num_UN_CH_inj_run_data
    };

enum UN_CH_mtr_run_data
	{
		cur_dig_valve_status,
		tmd_state,
		tmd_status,
		num_UN_CH_mtr_run_data
	};



enum UN_CH_meter_commands
	{
		tmd_command,
		num_UN_CH_meter_commands
	};


enum UN_CH_algebool_data                      /* rev2 */
    {
        bool_data,
        num_UN_CH_algebool_data
    };



enum UN_CH_system_commands
    {
        set_user_alarm,
        card_reader_cmd,
        num_UN_CH_system_commands
    };



enum UN_IN_security_data
    {
        passcode_1,
        passcode_2,
        passcode_3,
        passcode_4,
        passcode_5,
        sec1_in_acc_lev,
        sec2_in_acc_lev,
		diag_sec_level,
        num_UN_IN_security_data
    };



enum UN_IN_arm_data
    {
		start_stop_delay,
		report_intval,
		clean_volume,
		valve_close_delay,
		trans_reset_time,
		blend_tol_timeout,
		blend_alarm_min_vol,
		blend_correct_time,
		min_close_time,
		num_UN_IN_arm_data
     };



enum UN_IN_meter_data
    {
        dp_error_count,
		smass_mtr_dcf,
		ramp_down_tol_Q1,
		ramp_down_tol_Q2,
        num_UN_IN_meter_data
    };


enum UN_IN_comm_data
    {
        timeout_1,
        timeout_2,
        timeout_3,
        timeout_4,
        ether_timeout,
        num_UN_IN_comm_data
    };



enum UN_IN_sys_run_data
	{
		current_year,
		current_month,
		current_day,
		current_wday,
		current_sec,
		current_min,
		current_hour,
		num_UN_IN_sys_run_data
	};


enum UN_IN_tran_run_data
    {
      trans_no,
      total_batches,
	  start_year,
	  start_month,
	  start_day,
	  start_wday,
	  start_sec,
	  start_min,
	  start_hour,
	  end_year,
	  end_month,
	  end_day,
	  end_wday,
	  end_sec,
	  end_min,
	  end_hour,
      num_UN_IN_tran_run_data
    };


enum UN_IN_bay_data
	{
		rep_int_bay,
		num_UN_IN_bay_data
	};



enum UN_IN_bay_run_data
    {
      btrans_no,
      btotal_batches,
	  bstart_year,
	  bstart_month,
	  bstart_day,
	  bstart_wday,
	  bstart_sec,
	  bstart_min,
	  bstart_hour,
	  bend_year,
	  bend_month,
	  bend_day,
	  bend_wday,
	  bend_sec,
	  bend_min,
	  bend_hour,
      num_UN_IN_bay_run_data
    };


enum UN_IN_inj_data
{
    inj_address_1, 
    inj_address_2, 
    inj_address_3, 
    inj_address_4, 
    inj_address_5, 
    inj_address_6, 
    inj_address_7, 
    inj_address_8, 
    inj_address_9, 
    inj_address_10,
    inj_address_11,
    inj_address_12,
    inj_address_13,
    inj_address_14,
    inj_address_15,
    inj_address_16,
    inj_address_17,
    inj_address_18,
    inj_address_19,
    inj_address_20,
    inj_address_21,
    inj_address_22,
    inj_address_23,
    inj_address_24,
    num_UN_IN_inj_data
};


enum UN_IN_inj_run_data
{   
    number_of_inj_1,  
    number_of_inj_2,  
    number_of_inj_3,  
    number_of_inj_4,  
    number_of_inj_5,  
    number_of_inj_6,  
    number_of_inj_7,  
    number_of_inj_8,  
    number_of_inj_9,  
    number_of_inj_10, 
    number_of_inj_11, 
    number_of_inj_12, 
    number_of_inj_13, 
    number_of_inj_14, 
    number_of_inj_15, 
    number_of_inj_16, 
    number_of_inj_17, 
    number_of_inj_18, 
    number_of_inj_19, 
    number_of_inj_20, 
    number_of_inj_21, 
    number_of_inj_22, 
    number_of_inj_23, 
    number_of_inj_24, 
    feedback_error_1, 
    feedback_error_2, 
    feedback_error_3, 
    feedback_error_4, 
    feedback_error_5, 
    feedback_error_6, 
    feedback_error_7, 
    feedback_error_8, 
    feedback_error_9, 
    feedback_error_10,
    feedback_error_11,
    feedback_error_12,
    feedback_error_13,
    feedback_error_14,
    feedback_error_15,
    feedback_error_16,
    feedback_error_17,
    feedback_error_18,
    feedback_error_19,
    feedback_error_20,
    feedback_error_21,
    feedback_error_22,
    feedback_error_23,
    feedback_error_24,
    num_UN_IN_inj_run_data
};                    


enum UN_IN_system_commands
    {
        timer1_reset,
        timer2_reset,
        timer3_reset,
        timer4_reset,
        timer5_reset,
        timer6_reset,
        timer7_reset,
        timer8_reset,
        timer9_reset,
        timer10_reset,
        timer11_reset,
        timer12_reset,
        timer13_reset,
        timer14_reset,
        timer15_reset,
        timer16_reset,
        num_UN_IN_system_commands
    };


enum UN_IN_arm_commands                   /* rev 10.00    */
    {
        print_to_printer,
        num_UN_IN_arm_commands
    };



enum UN_IN_algebool_data                      /* rev2 */
    {
        timer1,
        timer2,
        timer3,
        timer4,
        timer5,
        timer6,
        timer7,
        timer8,
        timer9,
        timer10,
        timer11,
        timer12,
        timer13,
        timer14,
        timer15,
        timer16,
        num_UN_IN_algebool_data
    };


enum UN_LG_batch_run_data
    {
      additive_mask,
      num_UN_LG_batch_run_data
    };

enum UN_LG_tran_run_data
    {
        rom_crc,
        pmpt_1_rsp,
        pmpt_2_rsp,
        pmpt_3_rsp,
        pmpt_4_rsp,
        pmpt_5_rsp,
		current_pmpt_1,
		current_pmpt_2,
		current_pmpt_3,
		current_pmpt_4,
		current_pmpt_5,
		trans_seq_no,
        num_UN_LG_tran_run_data
    };


enum UN_LG_bay_run_data
	{
		bpmpt_1_rsp,
		bpmpt_2_rsp,
		bpmpt_3_rsp,
		bpmpt_4_rsp,
		bpmpt_5_rsp,
		bcurrent_pmpt_1,
		bcurrent_pmpt_2,
		bcurrent_pmpt_3,
		bcurrent_pmpt_4,
		bcurrent_pmpt_5,
		btrans_seq_no,
		num_UN_LG_bay_run_data
	};



enum UN_LG_system_data
	{
		trans_id,
		inj_alarm_pulse_time,
		add_stop_disable,
		ip_addr,
		netmask,
		gateway,
		eth_mac_addr_1,
		eth_mac_addr_2,
		dns_server,
		dig_sol_alrm_counts,
		num_UN_LG_system_data
	};



enum UN_LG_prd_run_data
    {
        prd_leak_pulses,
        num_UN_LG_prd_run_data
    };

enum UN_LG_meter_data
    {
        mass_mtr_seq,
        num_UN_LG_meter_data
    };

enum UN_LG_inj_run_data
	{
		inj1_up_sol_ons,
		inj2_up_sol_ons,
		inj3_up_sol_ons,
		inj4_up_sol_ons,
		inj1_down_sol_ons,
		inj2_down_sol_ons,
		inj3_down_sol_ons,
		inj4_down_sol_ons,
		num_UN_LG_inj_run_data
	};

enum UN_LG_meter_run_data
	{
		mtr_up_sol_ons,
		mtr_down_sol_ons,
		num_UN_LG_meter_run_data
	};


enum BOOL_system_run_data
    {
        in_program_mode,
        checking_entries,
        prg_value_changed,
        power_fail_occurred,
        print_in_progress,
        in_standby,
        card_A_status,
        card_A_valid,
        card_B_status,
        card_B_valid,
        printer_standby,
		new_nedap_data,
		nedap_comms_failed,
        num_BOOL_system_run_data
    };

enum BOOL_tran_run_data
    {
        accuload_authorized,
        accuload_released,
        transaction_in_progress,
        batch_done,
        transaction_done,
        keypad_data_pending,
        delayed_prompt_in_effect,
        display_msg_timed_out,
        alarm_condition,
        stop_delay_in_effect,
        injectors_authorized,
        proving_in_progress,
        product_flowing,
        permissive_not_met,
        standby_lock_in_effect,
        storage_full,
        batch_presetting,
        printer_standby_rpts_locked,
        printer_standby_rpts_storage_full,
        valve_diagnostic_new_data,
        num_BOOL_tran_run_data
    };

enum BOOL_bay_run_data
    {
        btransaction_in_progress,
        btransaction_done,
        bstandby_lock_in_effect,
        bstorage_full,
        bprinter_standby_rpts_locked,
        bprinter_standby_rpts_storage_full,
        num_BOOL_bay_run_data
    };


enum BOOL_digital_run_data
    {
        state,
        num_BOOL_digital_run_data
    };

enum BOOL_system_alarms
    {
        rom_bad,
        ram_bad,
        flash_error,
        powerup_ram_corrupt,
        powerup_flash_corrupt,
        watchdog_error,
        sys_prog_error,
        eaai_failure,
        bse_failure,
        passcodes_reset,
        powerfail,
        comms_error,
        civacon_alarm,
        shared_printer,
        PTB_printer_failure,
        user_alarm1,
        user_alarm2,
        user_alarm3,
        user_alarm4,
        user_alarm5,
        user_alarm6,
        user_alarm7,
        user_alarm8,
        user_alarm9,
        user_alarm10,
        addPak1_powerfail,
        addPak2_powerfail,
        addPak1_diagnostic,
        addPak2_diagnostic,
        aicb1_autodetect,
        aicb2_autodetect,
        aicb1_comm_failed,
        aicb2_comm_failed,
        display_failure,
        mmi_comm_failed,
        mmi_excess_active_arms,
		data_retention,
		comflash_alarm,
		network_printer_alarm,
        fa_sening_alarm,
		factory_diag_alarm,
        last_system_alarm   /* must always be last  */
    };  
    
enum BOOL_arm_alarms
    {          
        arm_prog_error,
        sys_zero_flow,
        sys_overrun,
        ticket_alarm,
        prd_clean_line,
        additive_clean_line,
        arm_rec_prog_error,
        storage_full_alarm,
		de_head_alarm,
		card_removed_alarm,
		report_storage_full,
        last_arm_alarm   /* must always be last */
    };

enum BOOL_meter_alarms
    {
        mtr_prog_error,
        xmit_integ,
        pulse_security,
        valve_fault,
        temp_xducer_fail,
        pres_xducer_fail,
        dens_xducer_fail,
        turbine_mtr_alarm,
		mass_meter_comm,
		mass_meter_overdrive,
		mass_meter_tube,
		prd_mtr_dig_sol_counts,
		promass_alarm,
		predict_overrun,
		nr_leakage,
		rev_flow_leakage,
        last_meter_alarm  /* must always be last */
    };


enum BOOL_product_alarms
    {
        prd_prog_error,
        back_pressure,
        high_dens,
        high_flow,
        high_pres,
        high_temp,
        low_dens,
        low_flow,
        low_pres,
        low_temp,
        prd_zero_flow,
        prd_overrun,
        block_valve,
        blend_high,
        blend_low,
		prd_stop,
        last_product_alarm   /* must always be last */
    };            



enum BOOL_injector_alarms                                                       
    {                            
        add_feedback_error,          
        additive_comm,           
        low_additive,            
        additive_pulse_excess,   
        additive_no_pulses,
        additive_freq,
        unauthorize_failed,
        general_additive_alarm,
        overrev_injector,
        command_refused,
		auto_detect_failed,
		add_high_temp,
		add_low_temp,
		add_temp_probe,
		add_pulse_sec,
		add_xmit_integ,
		add_comm_totals,
		inj_mtr_dig_sol_counts,
        last_injector_alarm     /* must always be last */
    };            


enum BOOL_recipe_alarms                                                       
    {                            
        rcp_prog_error,          

        last_recipe_alarm     /* must always be last */
    };            


enum BOOL_digital_commands
    {
        dig_out_cmd,
        num_BOOL_digital_commands
    };



/**************************************************************************
*******           PROGRAM CODES - (pDB struct)                     ********
**************************************************************************/
struct s_product_parameters
    {
        char            product_id[MAX_ID_LENGTH + 1];
        char            hm_class_1[MAX_HM_CLASS_LENGTH + 1];
        char            hm_class_2[MAX_HM_CLASS_LENGTH + 1];

        float           min_flow_rate;
        float           hi_flow_rate;
        float           sec_hi_flow_rate;
        float           flow_tol_percent;
        float           flow_tol_rate;
        float           first_trip_vol;
        float           sec_trip_vol;
        unsigned char   sec_trip_auto_adjust;
        float           excess_hi_flow_rate;
        float           lo_flow_rate_alrm_limit;

        float           mfac[MAX_FACTORS];
        float           frate[MAX_FACTORS];
        float           master_mtr_fac;
        float           lin_fac_dev;
        float           mfv_percent_temp;       /*meter factor variation with temperature*/
        float           mfv_ref_temp;           /*meter factor variation reference temperature*/
        unsigned char   mfv_select;             /*meter factor variation select*/
        

        float           maint_temp;
        float           hi_temp_alrm_limit;
        float           lo_temp_alrm_limit;
        unsigned char   api_table;
        float           prd_dens;
        float           hi_dens_alrm_limit;
        float           lo_dens_alrm_limit;
		float			unload_delta_vol;
		float			unload_contam_dens;

        float           maint_press;
        float           press_coeff;
        float           hi_press_alrm_limit;
        float           lo_press_alrm_limit;
        float           diff_press;
        float           min_bp_flow_rate;
        unsigned char   min_bp_flow_rate_timer;
        float           bp_percent_reduce;
        float           bp_flow_recover_press;
        unsigned char   bp_flow_recover_timer;
        unsigned char   vp_calc_method;
        float           vapor_press[MAX_VAPOR_PRES_PTS];
        float           vp_temp[MAX_VAPOR_PRES_PTS];

        unsigned char   bv_delay_open;
        unsigned char   bv_delay_close;
		unsigned char	calc_cur_ref_dens;
	
        float           min_batch_vol;
		float 			prd_stop_amt;
		float 			prd_stop_alarm;
		
		float			ref_density_temp;
		float			ref_density_ctable;
		float			ethanol_a1;
		float			ethanol_a2;
		float			ethanol_a3;
		float			aromatic_dens;
		unsigned char   aromatic_prd;
		float			ptb_k0e;
		float			eth_grade_bymass;

        /* these variable are set up in inta routines dependant on other
        pDB variables - do not add to database.c tables or add enums for them */
        unsigned char   api_table_type;
		API_GROUP	    api_grp;
        double          prd_dens_in_dens_units;
        float           prs_slope[MAX_VAPOR_PRES_PTS];
        unsigned char   vap_flg;

    };


struct s_smass_params

    {
        float           smass_a;
        float           smass_b;
    };

struct s_solartron_params
    {
        float           sol_dcf;
        float           sol_k0;
        float           sol_k1;
        float           sol_k2;
        float           sol_k18;
        float           sol_k19;
        float           sol_k20a;
        float           sol_k20b;
        float           sol_k21a;
        float           sol_k21b;
        float           sol_tcal;
        float           sol_pcal;
        unsigned char   sol_units;
    };


struct s_sarasota_params
    {
        float           sar_dcf;
        float           sar_k;
        float           sar_d0;
        float           sar_t0;
        float           sar_tcoef;
        float           sar_pcoef;
        float           sar_tcal;
        float           sar_pcal;
        unsigned char   sar_units;
    };

struct s_ugc_params
    {
        float           ugc_dcf;
        float           ugc_k0;
        float           ugc_k1;
        float           ugc_k2;
        float           ugc_tc;
        float           ugc_kt1;
        float           ugc_kt2;
        float           ugc_kt3;
        float           ugc_pc;
        float           ugc_kp1;
        float           ugc_kp2;
        float           ugc_kp3;
        unsigned char   ugc_units;
    };

struct s_other_dens_params
    {
        float           od_dcf;
        float           od_a;
        float           od_b;
        float           od_c;
        unsigned char   od_units;
    };

struct s_meter_parameters
    {
        unsigned char   valve_type;
        unsigned char   mtr_zero_flow_timer;
        float           overrun_alrm_limit;
        float           k_factor;
        float           dp_flow_rate_cutoff;
        unsigned char   dp_error_reset;
        unsigned int    dp_error_count;
		unsigned char   pulse_sec_alrm_vol;
		
		unsigned char	turbine_mtr_blades;
		unsigned char	turbine_mtr_alarm_tol;
		
        float           ana_p;
        float           ana_i;
        float           ana_d;
        float           pid_intval;
		float			smass_mtr_ka;
		float			smass_mtr_kb;
		float			smass_mtr_kc;
		unsigned int	smass_mtr_dcf;
        unsigned char   dens_in_type;

		unsigned char   share_temp;
		unsigned char   share_dens;
		unsigned char   share_pres;
		unsigned char   mass_mtr_type;
		unsigned char   mass_mtr_mult;
		unsigned char   mass_mtr_lfc;
		unsigned char   mass_mtr_tube;
		unsigned char   mass_mtr_model;
		unsigned long	mass_mtr_seq;
		unsigned char 	pulse_period_sample_count;
		unsigned char 	smass_menu_dummy;
		unsigned char 	solar_menu_dummy;
		unsigned char 	sara_menu_dummy;
		unsigned char 	ugc_menu_dummy;
		unsigned char 	other_menu_dummy;
		unsigned char 	mass_comm_menu_dummy;
		
        float           flow_adj_tol;
        float           flow_adj_timer;

        struct s_smass_params       smass[1];
        struct s_solartron_params   solar[1];
        struct s_sarasota_params    saras[1];
        struct s_ugc_params         ugc[1];
        struct s_other_dens_params  other_den[1];

		unsigned char	hybrid_mtr_plumb;
		unsigned int 	ramp_down_tol_Q1;
		unsigned int 	ramp_down_tol_Q2;
    };



/* this is needed in the pDB to save the data storing profile so datalog knows where to find */
/* the transaction and batch information in the flash record */
struct data_log_profile 
	{
		unsigned int		num_batches;
		unsigned int		num_products;
		unsigned long int	inj_in_use;  /* bit map of the injectors in use for the arm */
		unsigned int		record_size;
		unsigned int		header_size;
		unsigned int		trailer_size;
		unsigned int		batch_size;
		unsigned int		header_offset;
		unsigned int		trailer_offset;
		unsigned int		batch_offset[MAX_BATCH_PER_TRAN];
	};


struct s_load_arm
    {

      	unsigned char   arm_config;   
      	unsigned char   arm_product;
		unsigned char	num_ratio_prds;	    /* hybrid blender */

        char            load_arm_id[MAX_PROMPT_LENGTH+1];
		char			ready_msg[MAX_PROMPT_LENGTH+1];

        char            permissive_msg[MAX_PERMISSIVES][MAX_PROMPT_LENGTH+1];
        unsigned char   permissive_type[MAX_PERMISSIVES];
        unsigned char   permissive_start[MAX_PERMISSIVES];

        unsigned char   low_flow_start_cond;
        float           low_flow_start_rate;
        float           low_flow_start_percent;
        float           low_flow_start_vol;
        float           hi_flow_rate;
        float           sec_hi_flow_rate;
		float			sec_hi_flow_preset;         /* Rev 10.08 */


        float           blend_tol_pct;
        float           blend_tol_vol;
		float			blend_correct_vol;  /* blend correction volume (unlimited preset) */
        unsigned char   blend_correction;
		unsigned char   clean_line_blend;
		unsigned char	add_start;
		unsigned char	unlimited_preset;
		unsigned char   blend_error_reset;
		unsigned char   virtual_swing_arm;	 	
		unsigned char	trans_reset_start_hr;
		unsigned int    trans_reset_time;
		unsigned int	blend_alarm_min_vol;
        unsigned char   ratio_blend_algorithm;  /* Rev 11.09 - use ratio adjust factor or timed algorithm */
        unsigned char   ratio_prd_min_flow;
		unsigned char   first_sec_hf_sel;

        unsigned char   pump_delay_off;
        unsigned char   valve_delay_on;
        unsigned int    start_stop_delay;
        unsigned int    clean_volume;
        unsigned char   valve_fault_timeout;
        unsigned char   arm_zero_flow_timer;
        unsigned char   clean_product;
        unsigned char   clean_alarm_limit;
        unsigned char   ratio_time;
        unsigned char   bv_pos;
	   	unsigned char	bay_assign;				

        float           ratio_adjust_factor;
        float           overrun_alrm_limit;

		unsigned int	blend_tol_timeout;				/* blend tolerance alarm time (unlimited preset) */
		unsigned int	blend_correct_time;				/* blend correction time (unlimited preset) */
        unsigned int    min_close_time;
		
        unsigned char   report_sel;
        char            report_print_time[9];
        unsigned int    report_intval;
        unsigned char   rep_vol_resolution;
		unsigned char	rpt_pages;
		unsigned char	rpt_hm_class;

        struct          s_meter_parameters mtr[MAX_METERS];
        struct          s_product_parameters prd[MAX_PRODUCTS];

        unsigned long recipe_mask_A;
        unsigned long recipe_mask_B;

		struct 			data_log_profile transaction_log_profile;
		float			arm_add_stop_amt;
		unsigned int	valve_close_delay;
		float 			valve_fault_amount;

		char tagID[MAX_TAG_ID_LENGTH+1];
    };


// Note: the program params for the bay are in the system tables
//       this structure exists for the transaction archival routines
//       which expect the profiles to be array-based
struct s_bay
	{
		struct data_log_profile  transaction_log_profile;
		int             max_products;          // sum of products of all arms available to bay
		char   			bay_id[MAX_PROMPT_LENGTH+1];
		unsigned char   report_sel_bay;
		char            report_print_time_bay[9];
		unsigned int    report_intval_bay;
		unsigned char   rep_vol_resolution_bay;
		unsigned char   rpt_pages_bay;
		unsigned char   rpt_hm_class_bay;

        char            perm_msg[MAX_PERMISSIVES][MAX_PROMPT_LENGTH+1];
        unsigned char   perm_type[MAX_PERMISSIVES];
        unsigned char   perm_start[MAX_PERMISSIVES];
	};


struct s_recipe_params
    {
        unsigned char   recipe_used;
        unsigned char   hm_class_prod;                  /*use HM class from this product*/
        unsigned char   clean_deduct_prod;              /*deduct clean line from this product*/
        unsigned char   blend_comp[MAX_SEQ_COMPS];      /*sequential blend components*/
        float           blend_pct[MAX_SEQ_COMPS];       /*blend percentages*/
        float           rcp_corr_factor;                /*recipe correction factor*/

        char            recipe_name[MAX_ID_LENGTH+1];
        float           volume[MAX_INJECTORS];
        float           rate[MAX_INJECTORS];
		unsigned char	clean_line_prd;
        unsigned char   inj_prods[MAX_INJECTORS];       /*bit-map: products using injectors */
		unsigned char	ratio_seq_mode;			   
	};


/******** Boolean and Algebraic structures **************************************/
struct s_boolean
    {
        unsigned char equation[MAX_BOOLEAN+MAX_ALGEBRAIC];
    };

struct s_user                                            
    {
        unsigned char bool_vars[MAX_USER_VARS];
        double alge_dp_vars[MAX_USER_VARS];
        float alge_fp_vars[MAX_USER_VARS];
        unsigned int timer[MAX_TIMERS];
        unsigned int resettimer[MAX_TIMERS];
    };



struct s_digital_parameters
    {
        unsigned char   function;
        unsigned char   arm;
        unsigned char   mtr;
        unsigned char   prd;
        
        unsigned char   polarity;
        unsigned char   delay_on;
        unsigned char   delay_off;

        char            id[MAX_ID_LENGTH + 1];
    };


struct s_analog_parameters
    {
        unsigned char   function;
        unsigned char   arm;
        unsigned char   mtr;
        unsigned char   prd;
        unsigned char   trans_type;

        float           cal1_count;
        float           cal2_count;

        float           rtd_offset;
        float           min_eng_value;
        float           max_eng_value;
        float           min_eng_ma;
        float           max_eng_ma;
    };

struct s_pulse_in_parameters
    {
        unsigned char   pulse_func;
        unsigned char   pulse_arm;
        unsigned char   pulse_mtr;
    };



struct s_security_level
    {
        int             passcode;
        char            security_id[MAX_ID_LENGTH + 1];
        byte            sec_io;
    };


/* security level settings for each program mode parameter */
/*   all tables containing program mode parameters should be included here!!! */
struct s_pc_security_level
    {
        unsigned char   TEXT_system_data[num_TEXT_system_data];
        unsigned char   TEXT_prompt_data[num_TEXT_prompt_data];
        unsigned char   TEXT_arm_data[num_TEXT_arm_data];
        unsigned char   TEXT_product_data[num_TEXT_product_data];
        unsigned char   TEXT_recipe_data[num_TEXT_recipe_data];
        unsigned char   TEXT_bay_data[num_TEXT_bay_data];
        unsigned char   FP_analog_data[num_FP_analog_data];
        unsigned char   FP_system_data[num_FP_system_data];
        unsigned char   FP_inj_data [num_FP_inj_data];
        unsigned char   FP_arm_data[num_FP_arm_data];
        unsigned char   FP_meter_data[num_FP_meter_data];
        unsigned char   FP_product_data[num_FP_product_data];
        unsigned char   FP_recipe_data[num_FP_recipe_data];
        unsigned char   UN_CH_pulse_in_data[num_UN_CH_pulse_in_data];
        unsigned char   UN_CH_digital_data[num_UN_CH_digital_data];
        unsigned char   UN_CH_digital_data_2[num_UN_CH_digital_data_2];
        unsigned char   UN_CH_analog_data[num_UN_CH_analog_data];
        unsigned char   UN_CH_system_data[num_UN_CH_system_data];
        unsigned char   UN_CH_prompt_data[num_UN_CH_prompt_data];
        unsigned char   UN_CH_alarm_config[last_alarm_config];
        unsigned char   UN_CH_user_alarm_config[last_user_alarm_config];
        unsigned char   UN_CH_comm_data[num_UN_CH_comm_data];
        unsigned char   UN_CH_inj_data[num_UN_CH_inj_data];
        unsigned char   UN_CH_arm_data[num_UN_CH_arm_data];
        unsigned char   UN_CH_meter_data[num_UN_CH_meter_data];
        unsigned char   UN_CH_product_data[num_UN_CH_product_data];
        unsigned char   UN_CH_recipe_data[num_UN_CH_recipe_data];
        unsigned char   UN_CH_bay_data[num_UN_CH_bay_data];
        unsigned char   UN_IN_security_data[num_UN_IN_security_data];
        unsigned char   UN_IN_comm_data[num_UN_IN_comm_data];
        unsigned char   UN_IN_inj_data[num_UN_IN_inj_data];
        unsigned char   UN_IN_arm_data[num_UN_IN_arm_data];
        unsigned char   UN_IN_meter_data[num_UN_IN_meter_data];
        unsigned char   UN_IN_bay_data[num_UN_IN_bay_data];
        unsigned char   UN_LG_system_data[num_UN_LG_system_data];
        unsigned char   UN_LG_meter_data[num_UN_LG_meter_data];
    };


/******** Additive Injector Parameters **************************************/
struct s_injector
    {
        unsigned int      inj_address;          /* for SAI only. */
        float             inj_k_factor;         /* for Metered Inj */
        float             inj_meter_factor;     /* for Metered Inj */
        float             inj_high_tol;         /* for Metered Inj */
        float             inj_low_tol;          /* for Metered Inj */
                
        unsigned char     max_inj_tol_errors;   /* for Metered Inj */
        unsigned char     type;                 /* for all! */
        unsigned char     plumbing;             /* for all! */
        unsigned char     arm;                  /* for all! */  
    	unsigned char	  up_or_down;			/*one for all!*/
    };

struct s_flow_cntrl_inj	 /* for flow control inj */
	{
		unsigned char	  inj_valve_type;
		float			  inj_kp;
		float			  inj_ki;
		float			  inj_kd;
		float			  inj_pid_intval;							
		float			  inj_min_flow;			/* for flow control inj */
		float			  inj_max_flow;			/* for flow control inj */
		float			  inj_flow_tol;			/* for flow control inj */
		float			  inj_sec_trip;			/* for flow control inj */		 		
		float			  inj_dens;				/* for flow control inj */
		unsigned char	  inj_api_table;		/* for flow control inj */
		unsigned char	  inj_share_temp;		/* for flow control inj */
		float			  inj_maint_temp;		/* for flow control inj */
		float			  inj_high_temp_alarm;	/* for flow control inj */
		float			  inj_low_temp_alarm;	/* for flow control inj */
       	/*following are not in database.c*/
        unsigned char     inj_api_table_type;
		API_GROUP	  	  inj_api_grp;
        double            inj_dens_in_dens_units;
		double 			  inj_api_to_kgm3;
		float			  inj_rate_cutoff;		
		unsigned char	  inj_flow_timeout;
	};	



/* Actual structure for Additive Injector Parameters */
struct s_add_inj /* add_inj */
    {
        float             			additive_stop_volume;     /* in Preset volume type*/
        float             			conversion_factor;
        float             			additive_clean_line_volume;   /* in Preset volume type*/
		float						alarm_pulse_count;
		unsigned long				alarm_pulse_time;
		unsigned long				add_stop_disable;	// rev 10.14 bit map to disable use of additive stop option 
        unsigned char       		option;              
        unsigned char     			stop;                
        unsigned char     			vol_used;
        unsigned char     			max_feedback_errors; 
        char              			inj_units[4];
        char              			totals_units[4];         
        struct s_injector 			inj[MAX_INJECTORS];
		struct s_flow_cntrl_inj 	fc_inj[MAX_DUMB_INJECTORS];
        unsigned char     			piston_stop_action;
        unsigned char				flow_add_totals;
		unsigned char				inj_pulse_mode_type;
		unsigned char				inj_error_reset;
		unsigned char				inj_error_amt;
		float						inj_error_count;

          
 };

struct s_prompt_parameters
    {
        char            msg[MAX_PROMPT_LENGTH + 1];
        unsigned char   input_type;
        unsigned char   length;

    };

struct s_comm_parameters
    {
        unsigned int    timeout;

        unsigned char   protocol;
        unsigned char   baud_rate;
        unsigned char   data_parity;
        unsigned char   control;
    };


/* programmable parameters template */
struct s_parameters
    {
		unsigned char   RomVersionMajor;	/* !!!! KEEP THESE TWO ITEMS FIRST !!!! */
		unsigned char	RomVersionMinor;	/* !!!! KEEP THESE TWO ITEMS FIRST !!!!	*/

        unsigned char   pulse_mode_type;
        unsigned char   xmit_integrity;
        unsigned char   vol_units;
        unsigned char   temp_units;
        unsigned char   dens_units;
        unsigned char   mass_units;
        unsigned char   press_units;
        unsigned char   flow_rate_units;
        unsigned char   preset_vol_type;
        unsigned char   delivery_vol_type;
        unsigned char   dec_comma_sel;
        unsigned char   start_key_disable;
        unsigned char   def_trans_lits;
        unsigned char   a3_mode_type;
        unsigned char   api_rounding;
        unsigned char   display_resolution;
        unsigned char   blank_downcounter;
        unsigned char   prompts_in_use;
		unsigned char	prompt_mode;
		unsigned char	prompt_valid;
        unsigned char   batch_per_tran;
        unsigned char   recipes_per_tran;
        unsigned char   powerfail_alarm_disable;
        unsigned char   trans_term;
		unsigned char   trans_start;
		unsigned char   del_vol_disp;
        unsigned char   auto_prv_sel;
        unsigned char   prv_mode;
        unsigned char   prompt_timeout;
        unsigned char   comm_address[MAX_LOAD_ARMS];
        unsigned char   stop_key_action;
        unsigned char   sys_status_display;
		unsigned char	RBM_arm_prod[MAX_LOAD_ARMS];
		unsigned char	comm_timeout_action;
		unsigned char   inhibit_auto_focus;
		unsigned char	pulse_in_type;
		unsigned char	prover_out_mtr;
		unsigned char	rev_vol_batch;
		unsigned char	rev_vol_nr;
		unsigned char   dens_prompt;

		struct s_prompt_parameters  prompt[MAX_PROMPTS];
		unsigned char	card_validation;
		unsigned char	card_timeout;
		unsigned char	card_config;
		unsigned char   card_authorize;
		unsigned char   print_standby;
		unsigned char   auto_reprint;
		unsigned char	auto_tear_off;
		unsigned char	nedap_config;
		unsigned char	vehicle_id_tag;		
		unsigned char   da_alarms_function;

		unsigned char   solenoid_count_clear;

        float           batch_max_vol;
        float           batch_min_vol;
        float           auto_preset;
        float           auto_preset_inc;

        unsigned long   trans_id;

        unsigned long   ip_address;
        unsigned long   gateway;
        unsigned long   netmask;
        unsigned long   dns_server;

        char   SMTP_server[MAX_PROMPT_LENGTH+1];
        char   POP3_server[MAX_PROMPT_LENGTH+1];
        char   email_user_name[MAX_PROMPT_LENGTH+1];
        char   email_password[MAX_PROMPT_LENGTH+1];
        char   email_notify_dest[MAX_PROMPT_LENGTH+1];
        char   email_reply_to[MAX_PROMPT_LENGTH+1];
        char   network_printer[MAX_PROMPT_LENGTH+1];

        char            vol_desc[5];
        char            mass_desc[5];
        char            flow_rate_desc[4];
        char            trans_id_msg[MAX_PROMPT_LENGTH+1];
        char            user_alarm[MAX_USER_ALARMS][21];

        float           ref_temp;
        float           mcf;

        char            sys_permissive_msg[MAX_SYS_PERMISSIVES][MAX_PROMPT_LENGTH+1];
        unsigned char   sys_permissive_type[MAX_SYS_PERMISSIVES];
        unsigned char   sys_permissive_start[MAX_SYS_PERMISSIVES];


        struct s_comm_parameters        comm[MAX_COMM_PORTS];
        struct s_digital_parameters     dig[MAX_DIGITAL_IO];
        struct s_analog_parameters      ana[MAX_ANALOG_IO];
        struct s_pulse_in_parameters    pul_in[MAX_PULSE_IN];
        struct s_security_level         sec_level[MAX_SECURITY_LEVELS];
        struct s_add_inj                add_inj;
        struct s_recipe_params          recipe[MAX_RECIPES];
        
        struct          s_boolean boolean;                                  
        struct          s_pc_security_level sec;

        unsigned int    prg_mode;
        unsigned char   on_entry_flag;
        
        unsigned char   alarm_config[last_alarm_config];
        unsigned char   user_alarm_config[last_user_alarm_config];

        unsigned char   pul_func[MAX_PULSE_OUT];
        unsigned char   pul_mtr[MAX_PULSE_OUT];
        unsigned char   pul_unit[MAX_PULSE_OUT];
        float           pul_per_vol[MAX_PULSE_OUT];
        float           pul_max_freq[MAX_PULSE_OUT];

		unsigned char   recipe_select_1[MAX_LOAD_ARMS];
		unsigned char   recipe_select_2[MAX_LOAD_ARMS];
		unsigned char   recipe_select_3[MAX_LOAD_ARMS];
        unsigned char   dyn_disp_timeout;
        unsigned char   auto_reset_timer;
        unsigned char   zoom_reset_timer;
        unsigned char   com_lnk_prog;
        unsigned char   modbus_endian;
        unsigned char   ethernet_control;
        unsigned int    ethernet_timeout;
        unsigned int    sec1_in_acc_lev;
        unsigned int    sec2_in_acc_lev;
		unsigned int	diag_sec_level;
		unsigned char   user_text_saved;

        unsigned char   clr_able_alrm;
        unsigned char   civacon_used;
        
        unsigned char   num_load_arms;
		unsigned char   num_physical_arms;
        unsigned char   num_inj_used;

	   	unsigned char	stop_key_disable;	     /* for unlimited preset only */
		unsigned char   bluetooth_master;
		unsigned char	add_stop_action;
                               
        /*system io points*/             
        unsigned char   gen_purp_in_io_pt;
        unsigned char   gen_purp_out_io_pt;
        unsigned char   security1_io_pt;
        unsigned char   security2_io_pt;
        unsigned char   top_sec_level;
        unsigned char   set_sec_level;
        unsigned char   alarm_1_io_pt;
        unsigned char   alarm_2_io_pt;
        unsigned char   remote_stop_io_pt;
        unsigned char   sys_permissive1_io_pt;
        unsigned char   sys_permissive2_io_pt;
        unsigned char   sys_permissive3_io_pt;
		unsigned char	mtr_inj_remote_prove_io_pt;/*common to all meter injectors*/
		
		/*bay io points*/
		unsigned char	bay_perm1_io_pt[MAX_BAYS];
		unsigned char	bay_perm2_io_pt[MAX_BAYS];

        /*arm io points*/   
        unsigned char   permissive1_io_pt[MAX_LOAD_ARMS];
        unsigned char   permissive2_io_pt[MAX_LOAD_ARMS];
        unsigned char   first_sec_flow_io_pt[MAX_LOAD_ARMS];
        unsigned char   remote_start_io_pt[MAX_LOAD_ARMS];
        unsigned char   remote_stop_arm_io_pt[MAX_LOAD_ARMS];
        unsigned char   xaction_reset_io_pt[MAX_LOAD_ARMS];
        unsigned char   ticket_tray_io_pt[MAX_LOAD_ARMS];
        unsigned char   flow_out_io_pt[MAX_LOAD_ARMS];
        unsigned char   stop_relay_io_pt[MAX_LOAD_ARMS];
        unsigned char   swingarm_A_detect_io_pt[MAX_LOAD_ARMS];
        unsigned char   swingarm_B_detect_io_pt[MAX_LOAD_ARMS];
		unsigned char	de_head_stop_flow_io_pt[MAX_LOAD_ARMS];
		unsigned char	de_head_low_flow_io_pt[MAX_LOAD_ARMS];
		unsigned char	de_head_high_flow_io_pt[MAX_LOAD_ARMS];
		unsigned char	inj_upstream_sol_io_pt[MAX_DUMB_INJECTORS];
		unsigned char	inj_downstream_sol_io_pt[MAX_DUMB_INJECTORS];
		unsigned char   virtual_arm_map[MAX_LOAD_ARMS];
		unsigned char   vapor_line_valve[MAX_LOAD_ARMS];
		    
        /*meter io points*/ 
        unsigned char   pump_io_pt[MAX_LOAD_ARMS][MAX_METERS];
        unsigned char   upstream_io_pt[MAX_LOAD_ARMS][MAX_METERS];
        unsigned char   downstream_io_pt[MAX_LOAD_ARMS][MAX_METERS];
        unsigned char   temp_in_io_pt[MAX_LOAD_ARMS][MAX_METERS];
        unsigned char   dens_in_io_pt[MAX_LOAD_ARMS][MAX_METERS];
        unsigned char   pres_in_io_pt[MAX_LOAD_ARMS][MAX_METERS];
        unsigned char   ana_val_io_pt[MAX_LOAD_ARMS][MAX_METERS];
		unsigned char	inj_ana_val_io_pt[MAX_DUMB_INJECTORS];
		unsigned char	inj_temp_in_io_pt[MAX_DUMB_INJECTORS];/*flow control injectors only*/

        /*inj io points*/
        unsigned char   piston_fb_io_pt[MAX_FEEDBACK_INJECTORS];    
        unsigned char   add_pump_io_pt[MAX_INJECTORS];  
        unsigned char   piston_inj_io_pt[MAX_PISTON_INJECTORS]; 
        unsigned char   meter_inj_io_pt[MAX_DUMB_INJECTORS];
        unsigned char	share_add_sol_io_pt[MAX_INJECTORS];
        unsigned char	share_add_flush_io_pt[MAX_DUMB_INJECTORS];
        /*product io points*/
        unsigned char   block_valve_io_pt[MAX_LOAD_ARMS][MAX_PRODUCTS];
        unsigned char   block_valve_fb_io_pt[MAX_LOAD_ARMS][MAX_PRODUCTS];  

        struct s_load_arm               arm[MAX_LOAD_ARMS];

        struct s_bay                    bay[MAX_BAYS];

		//system volume accuracy
		unsigned char 	update_leakage;
		//system flow control
		unsigned long	digital_sol_alarm_counts;
		float 			leakage_alarm_limit;
		float 			reverse_flow_limit;
		float			atmos_press;

    };

/**************************************************************************
******           DYNAMIC RUN-TIME VARIABLES - (rDB. struct)        ********
**************************************************************************/

/*****  individual product data for batch ******/
struct s_product_batch_data
{
	double   cur_[NUM_VOLUME_TYPES];
	double   total_pulses;
	float    avg_frate;
	float    avg_mfac;
	float    avg_temp;
	float    avg_dens;
	float    avg_pres;
	float    avg_vap_pres;
	float    avg_ctpl;
	float    avg_ctl;
	float    avg_cpl;
	float    avg_ccf;
	float    ref_den;
	float    rel_den;
	float    api_den;
	float    ref_dens_at_dens_temp;   // 11.05 ref density at reference density's temperature
	float 	 E_table_rel_den_60;      // 11.07 rel dens @60F used in CPL calculation for E tables
	float    eth_grade_byvol;		  // 11.22 ethanol grade by % volume
	float    eth_dens_ME_read;
	float    eth_dens_ME_20;

	double   ref_dens_60_kgm3;
	double   ref_dens_kgm3;
	double   avg_dens_kgm3;

};


/*****  batch values for transaction *****/
struct  s_batch_run_data
{
	unsigned char batch_no;			   /* if bays, this indicates bay batch #.  (1 based) */
	unsigned char prd_no;
	unsigned char recipe_no;           /* recipe selected (1 based) */
	unsigned char hm_class_prod;
	unsigned long additive_mask;
	unsigned char load_arm;            /* identifies which arm this batch was delivered on (used for bays) */
	unsigned char compartment_no;		// 11.00 - truck compartment attached to batch

	double cur_[NUM_VOLUME_TYPES];
	double total_pulses;
	float  avg_frate;
	float  avg_mfac;
	float  avg_temp;
	float  avg_dens;           
	float  avg_pres;
	float  avg_ctl;
	float  avg_cpl;
	float  percent_contam;   /*unloading arm only*/
	float  last_den_sample;  /*unloading arm only*/

	double  gasohol_pct_ethanol;  // API Chapter 11.3.4 gasohol blends
	double  gasohol_ref_dens;
	double  gasohol_excess_vol;	 // volume expansion due to blending ethanol and gasoline
	double  ref_dens;

	double additive_total[MAX_INJECTORS];  /* Total amount of additive per injector in this batch. */
	double fc_additive[MAX_DUMB_INJECTORS][NUM_VOLUME_TYPES]; /*flow rate injectors only*/
    double vapor_recover;
	double straight_vrs_net;//liquid product - vapor recovered in mass units for a STRAIGHT_WITH_VRS load arm
       
	unsigned char   batch_dens_good;       /* density available on every product delivered during batch */

	float   prv_ctsp;   /* this block of data is the prove values for last prove run */
	float   prv_ctlp;
	float   prv_ctlm;
	float   prv_iv;
	float   prv_mtr_iv;
	float   prv_temp;
	float   prv_mtr_temp;
	float   prv_new_mfac;
	float   prv_frate;
	float   prv_avg_dens;

	unsigned char  prv_trip_accepted;
	char           rpt_alarm_log[MAX_BATCH_ALARMS][BATCH_ALM_STR_SIZE];  /* ex. P2:HF (prd 2 high flow) */
	unsigned char  num_alarms;                          /*     - for injectors, IN:GA05 (blah blah ...)*/
	                                                    /*                           ^^            */
	                                                    /*         Injector offset:  ||            */
	struct s_product_batch_data prd[MAX_PRODUCTS];

		/* 	This variable will contain an lrc calculated on the batch just before it is stored 
			in flash.  It is position dependent!!!! If you add a variable after the lrc, it will NOT
			contribute to the lrc, and thus no error detection will be on it.  Also, once this is 
			calculated for a batch, don't write to this batch again.  Besides having already been archived,
			if there is a powerfail durring the transaction, the lrc on this batch will flag it as 
			corrupt, and bad things will happen. - mb - 9/3/99*/
	unsigned char lrc;
};



struct s_alarm_log
{
	unsigned char type;             /* SYSTEM_ALARM, PRODUCT_ALARM etc. */
	unsigned char index;            /* database enum for alarm */
	unsigned char offset;           /* i.e. product index */
	unsigned char batch_no;         /* batch # when alarm occured */
	struct data_base *dbtbl_ptr;    /* ptr to this alarm in database table */
};

struct s_product_run_data
{ /* double          nonres_[NUM_VOLUME_TYPES]; */ /* in tran_ftr*/
	double          cur_[NUM_VOLUME_TYPES];
	float           cur_frate;
	float           cur_frate_hr;
	float           cur_frate_min;
	float           cur_mfac;
	float           cur_temp;
	float           cur_dens;
	float           cur_pres;
	float           vap_pres;
	float           blend_ratio;
	float			instant_blend_ratio;
	double			blend_vol_error;
	float			cur_ref_dens;
	float    		brazil_d154c;
	float    		brazil_d420c;
	float    		brazil_d4tc;
	double          sum_frate_avg;   /* delta grs vol * current value */
	double          sum_mfac_avg;
	double          sum_temp_avg;
	double          sum_dens_avg;
	double          sum_pres_avg;
	double          sum_grs;         /* sum delta grs vol */
	double          sum_raw;         /* sum delta raw vol */
	double          prd_raw_mass;    /*used when pulse input type is mass */
	double          total_downstream_injection_to_add; /*not in database.c*/
	double 			prd_without_fc_add[NUM_VOLUME_TYPES];/*not in database.c*/
	double			fc_add_to_prd[NUM_VOLUME_TYPES];/*not in database.c*/
	unsigned long   leakage_pulses;
};


struct s_meter_run_data
{
	float         cur_ana_val_percent;	 /*analog valve percentage, 4ma or 1V = 0%.. 20ma or 5 V = 100%*/
	unsigned char cur_dig_valve_status;  /*open,lock,close*/

	unsigned char TMDState;   /*turbine meter diagnostic state,  Disabled, Enabled, Learning, or ALARM */
	unsigned char TMDStatus;  /*turbine meter diagnostic status, Meter OK, Learn Failed, Bent Blade or Bad Bearing*/
	unsigned char TMDCommand; /*turbine meter diagnostic command, Learn, Disable, Enable or View-Edit*/
   
   	float TMDSig;
	float TMDDev;
	float TMDBladeSig;
	float TMDBladeDev;
	float TMDRotSig;
	float TMDRotDev;
	float TMDCurValue;

	float TMCSig;
	float TMCDev;
	float TMCBladeSig;
	float TMCBladeDev;
	float TMCRotSig;
	float TMCRotDev;
	float MassMeterTemp;
	float MassMeterDens;
	unsigned long UpSolenoidCounts;
	unsigned long DownSolenoidCounts; 

	float latest_valve_close_time;
	float latest_valve_close_amt;
	float latest_valve_close_flow_rate;
};

/* 	These two structures were ported from datalog.h and integreted into the 
	database in the arm area. - mb 8/19/99 */
/* this data is saved at the start of a transaction */
struct s_trans_header
{
	unsigned long   prompt_response[MAX_PROMPTS];
	unsigned int    trans_no;
	char            alpha_prompt[MAX_PROMPTS][ALPHA_PROMPT_SIZE+1];
	char            tran_start_time[DATE_TIME_SIZE];
	char            card_info[MAX_CARD_DATA];
	char            card_field_1[MAX_CARD_FIELD_1];
	char            card_field_2[MAX_CARD_FIELD_2];
	char            card_field_3[MAX_CARD_FIELD_3];
	char			card_hid_fac[MAX_CARD_HID_FAC];
	char			card_hid_num[MAX_CARD_HID_NUM];
};


/* this data is saved at the end of a transaction */
struct s_trans_trailer
{
	unsigned int   total_batches;

	double         nonres_[MAX_PRODUCTS][NUM_VOLUME_TYPES];
	double		   start_nonres_[MAX_PRODUCTS][NUM_VOLUME_TYPES];
	double         cur_[NUM_VOLUME_TYPES];
	double 		   nonres_vapor_recover;
	double 		   start_nonres_vapor_recover;		
	double         additive_total[MAX_INJECTORS];   /* Total amount of additive per injector in this transaction */
	double         vapor_recover;                   /* Transaction vapor recovery, mass units */
	double 		   straight_vrs_net;	//liquid product - vapor recovered in mass units for a STRAIGHT_WITH_VRS load arm

	float          avg_mfac;
	float          avg_temp;
	float          avg_dens;
	float          avg_pres;
	float          avg_ctl;
	float          avg_cpl;
	unsigned char  tran_dens_good;   /* density available on every product delivered during transaction */
	char           tran_end_time[DATE_TIME_SIZE];
	unsigned long  tran_end_time_ticks;   /* needed for smi comms; not in db tables... */
	char           rpt_alarm_log[MAX_TRANS_ALARMS][TRANS_ALM_STR_SIZE];  /* ex. P2:HF:10 (prd 2 high flow batch 10) */
	unsigned char  num_alarms;            /*  - for injectors, IN:AI12:10 (blah blah ...)*/

	char 		   user_text[MAX_USER_TEXT][USER_TEXT_LENGTH+1]; // 10.15 - archive host text for reports
    unsigned char  bool_vars[ARCHIVED_USER_VARS];		   		 // 10.15 archive last 5 user bools
    float          alge_fp_vars[ARCHIVED_USER_VARS];	         // 10.15 archive last 5 user floats
};



/*****  transaction values for load arm *****/
struct s_load_arm_run_data
{
/*#$-CAUTION!!!  -  this area must remain identical to s_bay_run_data for archiving-$#*/
	struct s_trans_header   tran_hdr;
	struct s_trans_trailer  tran_ftr;
	struct s_batch_run_data    batch[MAX_BATCH_PER_TRAN];
/*#$-END CAUTION  -  identical to s_bay_run_data-$#*/


	unsigned int  batch_no;
	float         cur_frate;
	float         cur_frate_hr;
	float         cur_frate_min;


	struct s_product_run_data  prd[MAX_PRODUCTS];
	struct s_meter_run_data	   mtr[MAX_METERS];	

	/* active alarms for this arm */
	unsigned char   arm_alarm[last_arm_alarm];
	unsigned char   mtr_alarm[MAX_METERS][last_meter_alarm];
	unsigned char   prd_alarm[MAX_PRODUCTS][last_product_alarm];

	unsigned char   seq_prd;       /* current seq prd # being delivered */
	unsigned char   seq_comp;      /* current seq comp # being delivered */
	float seq_preset[NUM_COMPS+1]; /* preset for each component of recipe, including clean line */

	unsigned char   batch_status;
	unsigned char   pump_status;

	unsigned char   swing_arm_position;  /* JMP Feb 02 - dual MMI support */

	unsigned char unload_product;
	/* AccuLoad Status Flags - used by AII style communications */
	unsigned char   accuload_authorized;        /* transaction/batch authorized by AT,AU,SB commands */ 
	unsigned char   batch_presetting;
	unsigned char   accuload_released;          /* valve commanded open */
	unsigned char   transaction_in_progress;
	unsigned char   batch_done;
	unsigned char   transaction_done;
	unsigned char   keypad_data_pending;        /* driver input in response to WD message */
	unsigned char   delayed_prompt_in_effect;   /* wait for SET key before displaying WP,WQ messages */
	unsigned char   delayed_prompt_displayed;   /* delayed prompt is currently being displayed */
	unsigned char   display_msg_timed_out;      /* WD etc message has timed out (no driver input) */
	unsigned char   alarm_condition;            /* an alarm condition is present */
	unsigned char   start_stop_delay;           /* start after stop delay is in effect */
	unsigned char   valve_opening_delay;        /* valve delay to on is in effect */
	unsigned char   block_valve_delay;          /* waiting for block valves to be positioned */
	unsigned char   product_flowing;            /* product flow rate is not zero */
	unsigned char   permissive_not_met;         /* all permissives not currently met */
	unsigned char   injectors_authorized;       /* injectors have been selected by host */
	unsigned char   proving_in_progress;        
	unsigned char   trans_rpt_queued;           /* waiting on summary report before printing transaction report */
	unsigned char   trans_ended_remove_ticket;
	unsigned char   in_program_mode;            /* logged into program mode on this arm */
	unsigned char   focus_requested;            /* local action requires focus at MMI */

	double          auth_max_trans_vol;         /* max trans vol authorized by ST command */
	float           auth_max_batch_vol;         /* max batch vol authorized by SB command */
	unsigned long   recipe_mask_A;              /* recipes allocated by AB command */
	unsigned long   recipe_mask_B;
	unsigned char   cur_recipe;                 /* current recipe selected (0 based) updated when released */

	unsigned char   valve_diagnostic_new_data;  /* flag set when meter stopped by STOP key or permissive lost */

	float           preset_vol;
	float           entered_preset;             /* value entered at preset prompt */
	double          remain_vol;                 /* volume in preset type */
	double          tran_del_vol;               /* volume in delivery type */
	double          batch_del_vol;              /* volume in preset type */
	double          excess_batch_del_vol;       // API 11.3.4 expansion volume caused by blending products
	
	float           delta_pulses;
	unsigned long   leakage_pulses;

	float			gasohol_cur_temp;           // API 11.3.4 ethanol blending - temp, pres and dens from blended product (gasohol)
	float			gasohol_cur_pres;
	float			gasohol_cur_dens;

	struct s_alarm_log alarm_log[MAX_TRANS_ALARMS];

	float           prv_coeff;
	float           prv_new_mfac[MAX_BATCH_PER_TRAN]; /* new mfac for each trip */
	float           prv_avg_mfac;
	float           prv_old_mfac;
	float           prv_mfac_frate;
	float           prv_lf_start_vol;
	unsigned char   prv_prd;          /* prd being proved (0 based) */
	unsigned char   prv_mfac_no;      /* mfac # being proved (0 based) */
	unsigned char   prv_trip;         /* current prove trip # */ 
	unsigned char   prv_mfac_stored;  /* new mfac is stored */ 
	unsigned char   prove_enabled;    /* auto prove enabled and security is met */
	unsigned char   prv_trip_no;      /* # trips used in prove */
	char            prv_time[DATE_TIME_SIZE];	/* time last prove was finished */

	float           dens_sample[MAX_UNLOAD_DENSITY_SAMPLES];/*unloading arm*/
	float           sample_target_vol;
	double          sample_sum_avg;
	double          sample_delta_gross;
	unsigned char   dens_sample_index;

	unsigned char 	next_compartment_no;   // 11.00 - Truck interface connection info

	float         TMDFlowRate[MAX_METERS];  /*turbine meter diagnostic flow rate sent to eaai*/
	float         TMDFlowTol[MAX_METERS];   /*turbine meter diagnostic flow tolerance sent to eaai*/

	unsigned char RomVersionMajor; /* needed to access rom version by transaction; initialized on power up to const. */
	unsigned char RomVersionMinor; /* JMP: Rev 10.00 */
   
	unsigned char   calc_ctl23e_now;  	/* calc ctl for 23e now, don't wait for polling loop */
	unsigned char   calc_ctl_2004_now; 	/* calc ctl for 2004 odd table now, don't wait for polling loop */
	unsigned char   calc_ctl_ABNT_now;  /* calc ctl for ABNT tables now, don't wait for polling loop */
	float           calc_ctlspec_dens; 	/*    density to use for special request ctl 23e */
	float           calc_ctlspec_temp; 	/*    temperature to use for special request ctl 23e */
	unsigned char   standby_lock_in_effect; // TRUE if standby transactions are currently protected from deletion
	unsigned char   storage_full;           // TRUE if no pages can be freed without deleting standby transactions
	unsigned long   standby_first_seq_num;  // sequence no. of first protected transaction for arm
	unsigned long   standby_last_seq_num;   // sequence no. of last protected transaction for arm

	unsigned char	printer_standby_rpts_locked;		// Rev 11.12 there are transaction reports that have not been printed
	unsigned char	printer_standby_rpts_storage_full;  // Rev 11.12 can't deliver transaction without overwriting locked transaction
	unsigned long	printer_standby_first_seq_num;      // Rev 11.12 sequence # of oldest locked transaction

	double   batch_raw_mass;   //used when pulse input is mass
	double   trans_raw_mass;   //used when pulse input is mass

	int start_year;
	int start_month;
	int start_day;
	int start_wday;
	int start_hour;
	int start_min;
	int start_sec;

	int end_year;
	int end_month;
	int end_day;
	int end_wday;
	int end_hour;
	int end_min;
	int end_sec;

	unsigned int  print_to_printer;  // Rev 10.00 - for PP command via Modbus
	unsigned long prompt_response[MAX_PROMPTS];
	unsigned long trans_seq_no;      // Rev 10.15 latest seq # for easier modbus retrieval

	char user_text[USER_TEXT_LENGTH+1]; // 10.15 - allows host-defined text on reports
};



struct s_analog_data
    {
        float           count;
        float           ana_value;
        float           eng_value;
        float           cmd_value;   // rev 1 JMP: for use by init routine on Set GP ANIO Out cmd
    };

struct s_digital_data
    {
        unsigned char   state;
        unsigned char   dig_out_cmd;
    };



/***************************************************
*     Run Time Additive Injector Variables         *
***************************************************/
/*----- Run Time data for Specific Add Inj -------*/
struct run_injector
{
	unsigned char  arm;
	unsigned char  inj_enabled_arms; //bit map indicating which arm this injector is for, see "const byte InjArmCode[MAX_LOAD_ARMS]" 
	unsigned char  on_off;
	unsigned char  feedback_error;
	unsigned int   number_of_inj;
	float          vol_per_inj;
	float          vol_per_cycle;
	double         additive_total;
	double         non_resetable_total;
	double 		   non_resetable_total_with_leak;	

	// the remaining parameters are not in database.c
	double         start_non_resetable_total; /* This parameters are not in database.c !!! */    
	unsigned char  control_io_pt;             /* This parameters are not in database.c !!! */
	unsigned char  feedback_io_pt;            /* This parameters are not in database.c !!! */
	unsigned char  pump_io_pt;                /* This parameters are not in database.c !!! */

	double         target_vol_on;             /* This parameters are not in database.c !!! */
	double         target_vol_off;            /* This parameters are not in database.c !!! */
	unsigned int   no_injector_ons;           /* This parameters are not in database.c !!! */
	unsigned int   no_injector_offs;          /* This parameters are not in database.c !!! */

	unsigned char prds_used;                  /* This parameters are not in database.c !!! */

	unsigned char  type;                      /* This parameters are not in database.c !!! */
	unsigned char  port;                      /* This parameters are not in database.c !!! */
	unsigned char  pollInPrgmMode;            /* This parameters are not in database.c !!! */
	double         previous_add_total;        /* used for downstream injectors */
	float 		   additive_leak;			 /* This parameters are not in database.c !!! */
};


/*----- Run Time data for Add Inj in General -------*/
struct run_add_inj /* rDB.add_inj */
{
	struct run_injector inj[MAX_INJECTORS];
	unsigned char AicbBoardPort [2];
	float cur_ana_val_percent[MAX_DUMB_INJECTORS]; /*flow rate injectors only*/
	float cur_temp[MAX_DUMB_INJECTORS];			   /*flow rate injectors only*/
	float avg_temp[MAX_DUMB_INJECTORS];			   /*flow rate injectors only*/
	float avg_dens[MAX_DUMB_INJECTORS];			   /*flow rate injectors only*/
	float avg_ctl[MAX_DUMB_INJECTORS];			   /*flow rate injectors only*/
	double sum_amt[MAX_DUMB_INJECTORS];			   /*flow rate injectors only*/
	double sum_temp_avg[MAX_DUMB_INJECTORS];	   /*flow rate injectors only*/
	double last_inj_amt[MAX_DUMB_INJECTORS];	   /*flow rate injectors only*/
	double batch_raw_inj_mass[MAX_DUMB_INJECTORS]; /*flow rate injectors only*/
	unsigned long UpSolenoidCounts[MAX_DUMB_INJECTORS];/*flow rate injectors only*/
	unsigned long DownSolenoidCounts[MAX_DUMB_INJECTORS];/*flow rate injectors only*/
};

struct s_recipe_run_data
{
	 float MinRecipePreset;
	 float HiFlow[MAX_PRODUCTS];  
	 float SecHiFlow[MAX_PRODUCTS];
	 float LowFlow[MAX_PRODUCTS];
	 double nonres_[NUM_VOLUME_TYPES];
};	   


// New data structure exclusively for Add-Paks
struct s_addpack
{
	unsigned int  pulses;
	unsigned char pump_state;
	unsigned char solenoid_state;
	unsigned char version;
	unsigned char diag_auth_flag;
	unsigned char diag_deauth_flag;
	char          crc[9];
};

struct s_batch_location
{
	unsigned char	arm;
	unsigned char	batch;
};

/*structure for bay run data*/
struct s_bay_run_data
{
/*#$-CAUTION!!!  -  this area must remain identical to s_load_arm_run_data for archiving-$#*/
	struct s_trans_header   tran_hdr;
	struct s_trans_trailer  tran_ftr;
	struct s_batch_run_data batch[MAX_BATCH_PER_TRAN];
/*#$-END CAUTION  -  identical to s_load_arm_run_data -$#*/

	double          		nonres_[MAX_LOAD_ARMS][MAX_PRODUCTS][NUM_VOLUME_TYPES];
	
	struct s_batch_location batch_loc[MAX_BATCH_PER_TRAN];

	unsigned long   prelim_prompt_response[MAX_PROMPTS];
	unsigned long	trans_seq_no;

	unsigned char 	transaction_in_progress;
	unsigned char   transaction_done;
	unsigned char	trans_rpt_queued;
	unsigned int 	batch_no;

	double          tran_del_vol;               /* bay transaction volume in delivery type */
    
	unsigned char   standby_lock_in_effect; 	// TRUE if standby transactions are currently protected from deletion
	unsigned char   storage_full;           	// TRUE if no pages can be freed without deleting standby transactions
	unsigned long   standby_first_seq_num;  	// sequence no. of first protected transaction for arm
	unsigned long   standby_last_seq_num;   	// sequence no. of last protected transaction for arm
	struct s_alarm_log alarm_log[MAX_TRANS_ALARMS];

	unsigned char	printer_standby_rpts_locked;		// Rev 11.12 there are transaction reports that have not been printed
	unsigned char	printer_standby_rpts_storage_full;  // Rev 11.12 can't deliver transaction without overwriting locked transaction
	unsigned long	printer_standby_first_seq_num;      // Rev 11.12 sequence # of oldest locked transaction

	int 			start_year;
	int 			start_month;
	int 			start_day;
	int 			start_wday;
	int 			start_hour;
	int 			start_min;
	int 			start_sec;

	int 			end_year;
	int 			end_month;
	int 			end_day;
	int 			end_wday;
	int 			end_hour;
	int 			end_min;
	int 			end_sec;

};



/* dynamic run-time variables template */
struct s_DB
{
	/* AccuLoad Status Flags - used by AII style communications */
	unsigned char   in_program_mode;
	unsigned char   checking_entries;           /* checking criticals */
	unsigned char   prg_value_changed;          /* a change has been made to a parameter since this status reset by host */
	unsigned char   power_fail_occurred;        /* a power fail has occurred since this status last reset by host */
	unsigned char   prg_error_count;            /* # of program mode errors existing */
	unsigned char   sys_prog_error;             /* flags indicating program error exists */
	unsigned char   arm_prog_error[MAX_LOAD_ARMS];
	unsigned char   arm_rec_prog_error[MAX_LOAD_ARMS];
	unsigned char   mtr_prog_error[MAX_LOAD_ARMS][MAX_METERS];
	unsigned char   prd_prog_error[MAX_LOAD_ARMS][MAX_PRODUCTS];
	unsigned char   rcp_prog_error;
	unsigned char   in_standby;
	unsigned char   host_control;
	unsigned char   al2_host;
	unsigned char	printer_standby;			// Rev 11.12 printer is down - last transaction report failed to be printed
	unsigned char	nedap_comms_failed;			// Rev 11.21 Nedap Reader is down - past 30 secs, no response when polled

	unsigned char   in_prg_common_area;    		/* making changes to common area of program mode */
	unsigned char   factory_initialized;
	unsigned char   comm_test_in_progress;
	unsigned char   prog_code_chg;
	unsigned char   hi_sec_prog_code_chg;
	unsigned char   accu1_keypad;

	unsigned char   print_in_progress;
	unsigned char   printer_1_in_use;
	unsigned char   printer_2_in_use;
	unsigned char	printer_3_in_use;
	unsigned char   report_being_processed;
	unsigned char   processing_done_1;
	unsigned char   processing_done_2;
	unsigned char   processing_done_3;
	unsigned char	printing_current_trans_rpt;
	unsigned char   rpt_arm;
	unsigned char   printing_pending_rpts;
	unsigned char	aborting_printing_pending_rpts;
	unsigned int	rpt_trans_num;

	unsigned char   user_access_level;
	unsigned char   time_type;
	unsigned char   temp_time_type;

	unsigned char   card_status[2];
	unsigned char   card_valid[2];
	unsigned char   new_card_data[2];
	unsigned char   new_nedap_data;
	unsigned char   card_locked[2]; 
	unsigned char	nedap_locked[2];
	unsigned char   card_reader_cmd;
	char            firmware_revision[MAX_LINE_LENGTH+1];
	char            max_arms[MAX_LINE_LENGTH+1];
	char            card_data[2][MAX_CARD_DATA];
	unsigned long	nedap_data[2];
	char            card_pin[2][MAX_CARD_PIN];
	char			card_field_1[2][MAX_CARD_FIELD_1];
	char			card_field_2[2][MAX_CARD_FIELD_2];
	char			card_field_3[2][MAX_CARD_FIELD_3];
	char			card_hid_fac[2][MAX_CARD_HID_FAC];
	char			card_hid_num[2][MAX_CARD_HID_NUM];
	char			mmi_card_db_record[2][MAX_RECORD_SIZE];

	char            alpha_date[ALPHA_DATE_SIZE];
	char            numeric_date[NUMERIC_DATE_SIZE];
	char            time[TIME_SIZE];
	char            logo_time[MAX_LINE_LENGTH+1];
	char            MacAddress[MAX_LINE_LENGTH+1];

	int             cur_month;
	int             cur_day;
	int             cur_year;
	int             cur_wday;
	int             cur_hour;
	int             cur_min;
	int             cur_sec;

	unsigned char   set_user_alarm;
	unsigned char   sys_alarm[last_system_alarm];
	unsigned char   rcp_alarm[last_recipe_alarm];
	unsigned char   inj_alarm[MAX_INJECTORS][last_injector_alarm];


	struct s_load_arm_run_data  arm[MAX_LOAD_ARMS];
	struct s_digital_data       dig[MAX_DIGITAL_IO /*+ MAX_BISTATE_IO*/];
	struct s_analog_data        ana[MAX_ANALOG_IO];
	struct run_add_inj          add_inj;
	struct s_user               userdata;
	struct s_recipe_run_data    recipe[MAX_RECIPES];
	struct s_addpack            addpack[MAX_INJECTORS];
	struct s_bay_run_data       bay[MAX_BAYS];


	unsigned char civacon_permit;
	unsigned char civacon_ground;
	unsigned char civacon_bypassed;
	unsigned char civacon_sensor[4];

	/* indexes used for screens only */
	unsigned char   cur_batch;
	unsigned char   cur_mtr;
	unsigned char   cur_prd;
	unsigned char   cur_arm;
	unsigned char   cur_recipe;
	unsigned char   cur_ana_io;
	unsigned char   cur_dig_io;
	unsigned char   cur_pulse_io;
	unsigned char   cur_security;
	unsigned char   cur_comm_port;
	unsigned char   cur_prompt;
	unsigned char   cur_alarm;
	unsigned char   cur_alarm_action;
	unsigned char   cur_injector;
	unsigned char   cur_alg_eq;
	unsigned char   cur_plumbed;
	unsigned char   cur_prod_using;
	unsigned char   cur_val;

	unsigned char   BSE_online;
	unsigned char   Display2_online;
	unsigned char	firmware_upgrade_ok;

};




/***********************************************************************
*           data base table definitions
************************************************************************/

/*************  table of tables structure definition *************************/
#define read_only       0
#define read_write      1

typedef struct table_data_base_table
    {
        const struct data_base *data_base_ptrs;
        unsigned int                size;
        unsigned int                offset_used; 
        unsigned char               dir_type;
        unsigned char               data_type;   
    } DB_TABLE_STRUCT;

#define DB_TABLE_TYPE const DB_TABLE_STRUCT 

enum table_of_tables_indexes
    {
        PULSE_IN_DIR,	 /* 0x00 */
        DIGITAL_DIR,
        DIGITAL_DIR_2,
        ANALOG_DIR,
        SYSTEM_DIR,
        SECURITY_DIR,	 /* 0x05 */
        PROMPT_DIR,
        ALARM_DIR,
        USER_ALARM_DIR,
        COMM_PORT_DIR,
        INJ_DIR,		 /* 0x0A */
        LOAD_ARM_DIR,
        METER_DIR,
        PRODUCT_DIR,
        RECIPE_DIR,

        SYS_RUN_DATA,
        TRAN_RUN_DATA,	 /* 0x10 */
        BATCH_RUN_DATA,
        PRD_RUN_DATA,
        BATCH_PRD_RUN_DATA,
        INJ_RUN_DATA,
        DIG_RUN_DATA,	 /* 0x15 */
        ANA_RUN_DATA,
        RECIPE_RUN_DATA,
        METER_RUN_DATA,

        SYSTEM_ALARMS,
        LOAD_ARM_ALARMS, /* 0x1A */
        METER_ALARMS,
        PRODUCT_ALARMS,
        INJECTOR_ALARMS,

        SYSTEM_CMDS,
        DIGITAL_CMDS,
        ALGEBOOL_DATA,	 /* 0x20 */
        METER_CMDS,
        RECIPE_ALARMS,
        ANALOG_CMDS,
        ARM_CMDS,
        BAY_DIR,          /* 0x25 */
        BAY_RUN_DATA,
        NUMBER_TABLES
    };

enum db_table_types
    {
        pDB_DATA,
        rDB_DATA
    };

enum db_table_arm_offset
    {
        NO_ARM_OFFSET,
        ARM_OFFSET,
        BAY_OFFSET
    };

typedef const struct db_table_info
    {
        unsigned char               func_code;
        enum db_table_types         db_type;
        enum db_table_arm_offset    arm_offset_used;
        unsigned char               read_write_status;
    }DB_TABLE_INFO;

     
/************** enumerate data types used in data base table **********/
enum data_types
    {
        text_type,                /* TEXT strings */
        ch_type,                  /* CHAR types */
        in_type,                  /* INT types */
        lg_type,                  /* LONG types */
        fp_type,                  /* FLOAT types */
        dp_type,                  /* DOUBLE types */
        un_ch_type,               /* unsigned CHAR types */
        un_in_type,               /* unsigned INT types */
        ul_type,                  /* unsigned LONG types */
        bool_type,                /* BOOLEAN types */
        NUMBER_DATA_TYPES         /* this must be last */
    };

#define MAX_DT NUMBER_DATA_TYPES - 1
#define MAX_FC NUMBER_TABLES - 1

#define DP_PTR *(double *)
#define FP_PTR *(float *)
#define IN_PTR *(unsigned int *)
#define LG_PTR *(unsigned long *)
#define CH_PTR *(char *)
#define UN_CH_PTR *(unsigned char *)


/******************** error codes & store_parameter control ****************/

enum error_codes
    {
        NO_ENTRY,
        NO_ERROR,
        WARNING,
        CRITICAL,
        FATAL,
        LOCKED
    };

enum store_parameter_control
    {
        STORE_IF_NO_ERROR,
        FORCE_SAVE,
        FORCE_SAVE_NSC,
        NO_TRANS_IN_PROGRESS
    };


enum flash_mail_types
  {
    DATABASE_UPDATE,
    FLASH_MAIL,
    LOCAL_STORAGE_UPDATE,
    LOCAL_STORAGE_UPDATE_DONE,
    STORE_REPORT_DATA,
    STORE_REPORT_DATA_DONE,
    STORE_DISPLAY_DATA,
    GET_REPORT_DATA,
    GET_DISPLAY_DATA,
    GET_BATCH_DATA,
    GET_BATCH_REPORT_DATA,
    GET_COMM_BATCH_DATA,
    NO_REPORT_DATA,
    NO_DISPLAY_DATA,
    NO_BATCH_REPORT_DATA,
    NO_DATABASE_UPDATE,

    STORE_LITERAL_DATA,
    GET_COMM_REPORT_DATA,
    GET_COMM_DISPLAY_DATA,
    GET_LITERAL_DATA
  };


/*************************** conversion parameters ************************/

union cvt_parm
    {
        float           fp;
        double          dp;
        char            ch;
        int             in;
        long            lg;
        unsigned char   un_ch;
        char            text[MAX_LINE_LENGTH+1];
    };
union parm
    {
        void            *dummy;
        float           *fp;
        double          *dp;
        long            *lg;
        unsigned long   *un_lg;
        int             *in;
        char            *ch;
        unsigned char   *un_ch;
        char            *text;
    };



/* The ERROR_LIST structure and typedef is used to store the WARNING,
    CRITICAL, or FATAL function name and a pointer to the error message
    to be displayed should that function fail.

    Arrays of ERROR_LIST structures are associated with each pDB parameter.
*/

struct error_list_parm
    {
        int (*function)(void *enter_value, int arm, int index);
        char **message;
    };

typedef struct error_list_parm ERROR_LIST;

/* The PC_ERROR_TBL structure is used to identify the pDB parameter
    (*db_item and offset), the error message, and its severity. Each entry
    will be the result of a critical or fatal function which failed when
    checked. */

typedef struct error_tbl_struct
    {
        struct data_base *db_table;
        unsigned char offset_type;
		unsigned char arm_offset;
        unsigned char offset;
        char  *err_msg;
        unsigned char severity;
    } PC_ERROR_TBL;


/****************** data base table structure defination *****************/
struct data_base
    {
        union parm      adr;                /* pointer to the variable in RAM */
        const ERROR_LIST  *list_of_crits;    /* pointer to the list of criticals for this param */
        void            (*post_storage)(int,int); /* pointer to init function (done after data storage) */
        void             *(*screen_adr)(unsigned char event, unsigned char arm, unsigned char init); /* pointer to param change screen func */
        char            **descript_ptr;     /* pointer to param description */
        char            **help_msg_ptr;     /* pointer to help message */
        char            **select_list_ptr;  /* pointer to select list text entries, NULL if not an "enum" */
        unsigned char   *sec_ptr;           /* pointer to required security level to change this param */
        float           min_val;            /* minimum value allowed for this param */
        float           max_val;            /* maximum value, max string length, or # of select list items */
        unsigned char   data_type;          /* "4 byte code" data_type */
        unsigned char   func_code;          /* "4 byte code" function */
        unsigned char   sub_func_code;      /* "4 byte code" sub-function */
        char            format[10];         /* format string to use for sprintf for this param */
        unsigned char   format_arg1;        /* minimum field length for the format. */
        unsigned char   format_arg2;        /* precision of the format */
        unsigned int    major_index_size;   /* if offsets are allowed, this is the size in bytes from one struct to the next */
        unsigned int    offset_used;        /* maximum offset used for this entry */
        char            *accumate_ptr;      /* pointer to AccuMate literal */
    };

typedef struct data_base db_element;



/***********************  database.c prototypes ***************************/
typedef struct
    {
        void            *dest;
        void            *src;
        unsigned char   size;
    }xDB_DATA;

typedef struct s_smith_code
{
    unsigned char       data_type;
    unsigned char       func_code;
    unsigned char       sub_code;
}SMITH_CODE;

void            db_access           (char *dest, char *source, unsigned long size);
void            xdb_access          (xDB_DATA *data, unsigned char num_items);
unsigned char   store_parameter     (void *buffer_ptr,const struct data_base *db_ptr,int arm_offset,int db_index,unsigned char control);
unsigned char   binary_store_parameter(void *parm_to_store, const struct data_base *dbtbl_ptr,int arm_offset, int db_index, unsigned char control);
unsigned char   check_criticals     (const struct data_base *dbtbl_ptr,void *dataptr,int arm_offset,int db_index);
void            nop_rtn2            (int,int);
unsigned char   db_range_error      (const struct data_base *dbtbl_ptr, void *dataptr);
void            dbtbl_smith_code    (SMITH_CODE *smith_code ,const struct data_base *dbtbl_ptr);
void            log_parameter_change_event(const struct data_base *dbtbl_ptr, void *parm_to_store, int arm_offset, int db_index);



/*-------------------------------------------------------------------------------------------------------------**
** This routine fetches a pointer to a database record given the database "4 byte code" (less the offsets).    **
** In other words, obscure database table lookups are done here... please don't ask me to explain it,          **
** I more or less stole it from COMRAD...                                                                      **
**-------------------------------------------------------------------------------------------------------------*/
void
DATABASE_get_db_entry_ptr   (   unsigned char cdata_type,               /* type of data */
                                unsigned char cfunc_code,               /* function code */
                                unsigned char csub_func,                /* sub-function */
                                const struct data_base   **db_entry  /* pointer to the database entry */
                            );


/*------------------------------------------------------------------------------------------------------------**
** This routine fetches a pointer to the data given type, function, sub-function, and offset.                 **
** In other words, all the obscure database table lookups are done here... please don't ask me to explain it, **
** I more or less stole it from COMRAD...                                                                     **
** The function returns a true if a valid address was found; otherwise false and a NULL pointer are returned. **
**------------------------------------------------------------------------------------------------------------*/
unsigned int
DATABASE_get_data_ptr ( unsigned char cdata_type,    /* type of data */
                        unsigned char cfunc_code,    /* function code */
                        unsigned char csub_func,     /* sub-function */
                        unsigned char coffset,       /* offset (zero based) */
                        unsigned char arm_offset,    /* arm offset */
                        void          **data_ptr     /* returns pointer to the data */
                      );

/*--------------------------------------------------------------------------------------------------------------**
** Get the format string for a given parameter.  If left_justify is true, left field justification will result; **
** otherwise it will be right justified.  If leading_zeroes is true, leading zero's notation will be included.  **
** This function returns a null string in "format" if the operation failed.  The pointer "format" is returned.  **
**--------------------------------------------------------------------------------------------------------------*/
char *
DATABASE_get_format_string (const struct data_base  *db_entry,      /* pointer to DB entry */
                            unsigned char           left_justify,   /* set to true if left justification is desired */
							unsigned char           leading_zeroes, /* set to true if leading zeroes is desired */
                            char                    *format,        /* format string placed here */
							unsigned char			*arg1,			/* argument 1 number */
							unsigned char			*arg2			/* argumant 2 number */
                         );

/*-------------------------------------------------------------------------------------------------------------------------**
** Given a pointer to a database record, this routine returns the maximum allowable offset and size of the data structure. **
**-------------------------------------------------------------------------------------------------------------------------*/
void
DATABASE_get_struct_size_and_max_offset ( const struct data_base *db_entry, unsigned int *max_offset, unsigned int *major_index_size );

/*--------------------------------------------------------------------------------------------**
** This routine returns the address of the actual data given a pointer to the database entry. **
** It also returns the type of the data and the size in bytes.                                **
** This routine will return a NULL pointer if any invalid parameters are detected.            **
**--------------------------------------------------------------------------------------------*/
void
DATABASE_get_address (  const struct data_base      *db_entry,      /* pointer to DB entry            */
                        unsigned int                arm_offset,     /* arm offset */
                        unsigned int                offset,         /* offset of interest             */
                        unsigned char               use_edit_buf,   /* true to return a pDB_edit_buf pointer */
                        void                        **data,         /* data pointer */
                        enum data_types             *data_type,     /* returns the data type          */
                        unsigned int                *size           /* returns the data size in bytes */
                     );


/*--------------------------------------------------------------------------------------------------------------------**
** This function takes a pointer to a database entry and an offset and produces an ascii string representation        **
** of the data.  If left_justify is true, left field justification will result; otherwise it will be right justified. **
** If the database entry is a pDB entry and use_edit_buf is true, then the value in the pDB_edit_buf will be          **
** converted instead of the one in the pDB.                                                                           **
**--------------------------------------------------------------------------------------------------------------------*/
unsigned char 
DATABASE_get_data_string (  const struct data_base  *db_entry,      /* pointer to DB entry */
                            unsigned int            arm_offset,     /* arm offset */
                            unsigned int            offset,         /* parameter offset */
                            unsigned char           use_edit_buf,   /* true to convert a pDB_edit_buf value */
                            unsigned char           left_justify,   /* set to true if left justification is desired */
                            unsigned char           leading_zeroes, /* set to true if leading zeroes is desired */
                            char                    *string         /* ascii value placed here */
                         );             

/*------------------------------------------------------------------------------------------------------------------**
** This function is identical to the DATABASE_get_data_string() function, but returns the full significance of      **
** doubles and float data types.                                                                                    **
**                                                                                                                  **
**------------------------------------------------------------------------------------------------------------------*/
unsigned char 
DATABASE_get_full_data_string (  const struct data_base  *db_entry,      /* pointer to DB entry */
                            unsigned int            arm_offset,     /* arm offset */
                            unsigned int            offset,         /* parameter offset */
                            unsigned char           use_edit_buf,   /* true to convert a pDB_edit_buf value */
                            unsigned char           left_justify,   /* set to true if left justification is desired */
                            unsigned char           leading_zeroes, /* set to true if leading zeroes is desired */
                            char                    *string         /* ascii value placed here */
                         );             



// This function takes a pointer to a database entry and returns 
// the select list text for the current value of the parameter.  
// It returns NULL if no select list exists for the element.     
const char *
DATABASE_get_select_list_string (db_element  *db_entry,      /* pointer to DB entry */
                            unsigned int     arm_offset,     /* arm offset */
                            unsigned int     offset,         /* parameter offset */
                            unsigned char    use_edit_buf    /* true to convert a pDB_edit_buf value */
                         );





/*------------------------------------------------------------------------------------------------------------------**
** This function is identical to the DATABASE_get_data_string() function, but always returns a valid string.  If an **
** error occurs, a null string is returned.  Also, a pointer to the string passed into the function is returned     **
** rather than an error code.                                                                                       **
**------------------------------------------------------------------------------------------------------------------*/
char * 
DATABASE_alt_get_data_string (	const struct data_base  *db_entry,      /* pointer to DB entry */
                            	unsigned int            arm_offset,     /* arm offset */
                            	unsigned int            offset,         /* parameter offset */
                            	unsigned char           use_edit_buf,   /* true to convert a pDB_edit_buf value */
                            	unsigned char           left_justify,   /* set to true if left justification is desired */
                            	unsigned char           leading_zeroes, /* set to true if leading zeroes is desired */
                            	char                    *string         /* ascii value placed here */
						     );


/* reads the security setting for the specified table entry */
unsigned char 
read_parameter_security (   const struct data_base  *dbtbl_ptr,         /* pointer to the database item */
                            unsigned char           use_edit_buff,      /* index into the edit buffer rather than the pDB */
                            unsigned char           *security_level     /* security level to be set (0 based) */
                        );


/* sets the security setting for the specified table entry */
enum error_codes 
set_parameter_security  (   const struct data_base  *dbtbl_ptr,         /* pointer to the database item */
                            unsigned char           security_level,     /* security level to be set (0 based) */
                            unsigned char           control,            /* storage control */
                            unsigned char           arm                 /* Arm calling */
                        );


/*--------------------------------------------------------------------------------------**
** returns 1 if the given parameter is a program code, and 0 if it's not or is invalid. **
**--------------------------------------------------------------------------------------*/
unsigned char
DATABASE_is_program_parameter   (   enum data_types data_type,
                                    unsigned int    func,
                                    unsigned char   sub_func
                                );

/*------------------------------------------------------------------------------**
** returns true if transaction is not in progress or being started (presetting) **
**------------------------------------------------------------------------------*/
unsigned char 
is_arm_idle(unsigned char arm);

/*-----------------------------------------------------------------------------------**
** returns true if trying to write to a parameter that is currently in use by an arm **
** with a transaction in progress or about to be started (presetting).               **
**-----------------------------------------------------------------------------------*/
unsigned char 
is_parameter_locked(char *parm_to_store, const db_element *dbtbl_ptr, int arm, int db_index);


/* allow access to the database */
#pragma sep_on class pf_saved 
extern struct s_DB           rDB;            /* run (dynamic variables) data base */

// Rev 11.11 - original sec_ticks could go backwards when sync'ed to current date/time by RTC or by SD command.  This can cause problems if calculating elapsed
//    time.  As of this revision, sec_ticks is no longer sync'ed to date/time.  Use date_time_sec_ticks if the current date/time in sec ticks is needed. 
extern unsigned long sec_ticks;
#pragma sep_off


#pragma sep_on class noinit 
extern struct s_parameters   pDB;            /* run (parameter) data base */
extern struct s_parameters   pDB_edit_buf;   /* program mode copy of parameters */
extern unsigned int			 pDB_ram_crc;
#pragma sep_off


extern unsigned long date_time_sec_ticks; /* Rev 11.11 use this instead of sec_ticks if date/time in ticks is needed (sec_ticks is no longer sync'ed to date/time) */
extern unsigned long ten_ms_ticks;
extern unsigned long hun_ms_ticks;


/* allow access to the database entries */
#pragma sep_on
extern struct data_base DP_bay_run_data[];
extern struct data_base DP_tran_run_data[];
extern struct data_base DP_batch_run_data[];
extern struct data_base DP_algebool_data[];
extern struct data_base DP_inj_run_data[];
extern struct data_base DP_prd_run_data[];
extern struct data_base DP_prd_batch_run_data[];
extern struct data_base DP_recipe_run_data[];
extern struct data_base FP_system_data[];
extern struct data_base FP_meter_data[];
extern struct data_base FP_product_data[];
extern struct data_base FP_digital_data[];
extern struct data_base FP_analog_data[];
extern struct data_base FP_batch_run_data[]; 
extern struct data_base FP_prd_run_data[];
extern struct data_base FP_prd_batch_run_data[];
extern struct data_base FP_tran_run_data[];
extern struct data_base FP_analog_run_data[]; 
extern struct data_base FP_algebool_data[];
extern struct data_base FP_inj_data[];
extern struct data_base FP_inj_run_data[];
extern struct data_base FP_recipe_data[];
extern struct data_base FP_arm_data[];
extern struct data_base FP_prd_run_data[];
extern struct data_base FP_prd_batch_run_data[];
extern struct data_base FP_recipe_run_data[];
extern struct data_base FP_mtr_run_data[];
extern struct data_base FP_meter_commands[];
extern struct data_base FP_analog_commands[];
extern struct data_base UN_IN_meter_data[];
extern struct data_base UN_IN_comm_data[];
extern struct data_base UN_IN_tran_run_data[];
extern struct data_base UN_IN_bay_run_data[];
extern struct data_base UN_IN_system_commands[]; 
extern struct data_base UN_IN_algebool_data[];
extern struct data_base UN_IN_inj_data[];
extern struct data_base UN_IN_inj_run_data[];
extern struct data_base UN_IN_product_data[];
extern struct data_base UN_IN_security_data[];
extern struct data_base UN_IN_arm_data[];
extern struct data_base UN_IN_bay_data[]; 
extern struct data_base UN_CH_system_data[];
extern struct data_base UN_CH_meter_data[];
extern struct data_base UN_CH_product_data[];
extern struct data_base UN_CH_digital_data[];
extern struct data_base UN_CH_digital_data_2[];
extern struct data_base UN_CH_analog_data[];
extern struct data_base UN_CH_comm_data[];
extern struct data_base UN_CH_alarm_config[];
extern struct data_base UN_CH_user_alarm_config[];
extern struct data_base UN_CH_recipe_data[];
extern struct data_base UN_CH_batch_run_data[];
extern struct data_base UN_CH_sys_run_data[]; 
extern struct data_base UN_CH_tran_run_data[];
extern struct data_base UN_CH_bay_run_data[];
extern struct data_base UN_CH_algebool_data[];
extern struct data_base UN_CH_inj_data[];
extern struct data_base UN_CH_inj_run_data[];
extern struct data_base UN_CH_prompt_data[];
extern struct data_base UN_CH_pulse_in_data[];
extern struct data_base UN_CH_system_commands[];
extern struct data_base UN_CH_prompt_data[];
extern struct data_base UN_CH_arm_data[];
extern struct data_base UN_CH_meter_commands[];
extern struct data_base UN_CH_bay_data[];
extern struct data_base UN_LG_meter_data[];
extern struct data_base UN_LG_tran_run_data[];
extern struct data_base UN_LG_bay_run_data[];
extern struct data_base UN_LG_system_data[];
extern struct data_base UN_LG_prd_run_data[];
extern struct data_base UN_LG_inj_run_data[];
extern struct data_base UN_LG_meter_run_data[]; 
extern struct data_base LG_batch_run_data[];
extern struct data_base TEXT_system_data[];
extern struct data_base TEXT_product_data[];
extern struct data_base TEXT_digital_data[];
extern struct data_base TEXT_batch_run_data[];
extern struct data_base TEXT_tran_run_data[]; 
extern struct data_base TEXT_tran_run_data[];
extern struct data_base TEXT_bay_run_data[];
extern struct data_base TEXT_meter_data[];
extern struct data_base TEXT_recipe_data[];
extern struct data_base TEXT_prompt_data[];
extern struct data_base TEXT_arm_data[];
extern struct data_base TEXT_bay_data[];
extern struct data_base TEXT_arm_commands[];
extern struct data_base BOOL_digital_data[];
extern struct data_base BOOL_tran_run_data[];
extern struct data_base BOOL_bay_run_data[]; 
extern struct data_base BOOL_digital_run_data[]; 
extern struct data_base BOOL_system_commands[];
extern struct data_base BOOL_digital_commands[];
extern struct data_base BOOL_system_alarms[];
extern struct data_base BOOL_recipe_alarms[];
extern struct data_base BOOL_arm_alarms[];
extern struct data_base BOOL_meter_alarms[];
extern struct data_base BOOL_product_alarms[];
extern struct data_base BOOL_injector_alarms[];
extern struct data_base BOOL_arm_data[];
#pragma sep_off

extern DB_TABLE_TYPE * const DB_table[NUMBER_DATA_TYPES];
extern DB_TABLE_INFO DB_table_info[NUMBER_TABLES];




#endif /* __DATABASE_H must be last */

