#include <stdio.h>

#define MAX_LOAD_ARMS           6
#define MAX_DUMB_INJECTORS      4
#define MAX_BATCH_ALARMS        10
#define BATCH_ALM_STR_SIZE	    8
#define MAX_INJECTORS           24
#define MAX_PRODUCTS            6

enum volume_types {
		RAW,
		GRS,
		GST,
		GSV,
		MASS,
		NUM_VOLUME_TYPES};

typedef struct gasohol_avgs {
	double avg_temp;
	double avg_pres;
	double avg_dens;
	double ref_dens_kgm3;
	double last_gv;
	double sum_temp_avg;
	double sum_pres_avg;
	double sum_dens_avg;
}GASOHOL_AVG;

struct api_gasohol {
	int configured;		// arm is configured for ethanol blending
	int in_use;			// ethanol blending in use for current transaction (some recipes may not be using the ethanol product)
	int divy_up_ethanol;	// must divy up ethanol among multiple gasoline products.
	int all_seq;		// all products, including ethanol, are sequentially delivered
	int ethanol_prd;
	int gasoline_prd;
	int gas_prds[MAX_PRODUCTS];

	double last_ghol_ctpl;							  // last calculated gasohol CTPL for current gasoline product flowing
	double last_ghol_ctl;							  // last calculated gasohol CTL for current gasoline product flowing
	double last_eth_ctpl;							  // last calculated ethanol CTPL for current gasoline product flowing
	double last_bob_ctpl;							  // last calculated gasoline CTPL for current gasoline product flowing
	double last_bob_ctl;						      // last calculated gasoline CTL for current gasoline product flowing
	double excess_vol_frac[MAX_PRODUCTS];		  // fraction of blended gasohol volume due to expansion (for each gasoline product)

	double BlendVol[MAX_PRODUCTS][NUM_VOLUME_TYPES];  // gasohol volume measured/calculated while specific main sequential product is flowing
	double EthanolGV[MAX_PRODUCTS];                   // ethanol GV measured while specific main sequential product is flowing
	double last_ethanol_gv;
	double last_gasohol_gv;
	GASOHOL_AVG EthanolAvg[MAX_PRODUCTS];   // ethanol values while specific main sequential product is flowing
	GASOHOL_AVG BlendAvg[MAX_PRODUCTS];     // blend meter values while specific main sequential product is flowing
};

struct s_product_batch_data {
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

struct  s_batch_run_data {
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


