#include "accu3.h" 

int main()
{
	double batch_vol[NUM_VOLUME_TYPES];
	double ethanol_total_gv, delta_ethanol_gv, ethanol_gsv, ethanol_gv;
	double gasoline_gsv, sum_gas_gv;
	double sum_prd_gsv;
	double ref_dens_kgm3, avg_dens_kgm3;
	int gasoline_prd = 1;
	int i, prd;
	int c; 
	int ethanol_prd = 0;
	double sum_prds, sum_ghols, total_batch_vol, expected_batch_total, sum_pos_prds;
	int num_pos_prds, num_neg_prds;
	int run_unit_test = 1;
	double ProdVol[MAX_PRODUCTS][NUM_VOLUME_TYPES];
	double BlendVol[MAX_PRODUCTS][NUM_VOLUME_TYPES];

	expected_batch_total = 0;
	printf("TEST PRD1\tPRD2\tPRD3\tBV[1]\tBV[2]\t\tSUM_PRDS SUM_GHOLS\tACT_BATCH EXP_BATCH\n");

	for(c=0; c<11; c++) {
	
		if(c == 0) {
			ProdVol[0][GRS] = 5; ProdVol[1][GRS] = -2; ProdVol[2][GRS] = 5;
			expected_batch_total = 8.05;
		}
		else if (c == 1) {
			ProdVol[0][GRS] = 5; ProdVol[1][GRS] = 0; ProdVol[2][GRS] = 10;
			expected_batch_total = 15.05;
		}
		else if (c == 2) {
			ProdVol[0][GRS] = 5; ProdVol[1][GRS] = 10; ProdVol[2][GRS] = 0;
			expected_batch_total = 15.05;
		}
		else if (c == 3) {
			ProdVol[0][GRS] = 5; ProdVol[1][GRS] = 0; ProdVol[2][GRS] = 0;
			expected_batch_total = 5;
		}
		else if (c == 4) {
			ProdVol[0][GRS] = 5; ProdVol[1][GRS] = -5; ProdVol[2][GRS] = -5;
			expected_batch_total = -5;
		}
		else if (c == 5) {
			ProdVol[0][GRS] = 5; ProdVol[1][GRS] = 5; ProdVol[2][GRS] = -7;
			expected_batch_total = 3.05;
		}
		else if (c == 6) {
			ProdVol[0][GRS] = 5; ProdVol[1][GRS] = -7; ProdVol[2][GRS] = 5;
			expected_batch_total = 3.05;
		}
		else if (c == 7) {
			ProdVol[0][GRS] = 5; ProdVol[1][GRS] = 0; ProdVol[2][GRS] = -10;
			expected_batch_total = -5;
		}
		else if (c == 8) {
			ProdVol[0][GRS] = 5; ProdVol[1][GRS] = -10; ProdVol[2][GRS] = 0;
			expected_batch_total = -5;
		}
		else if (c == 9) {
			ProdVol[0][GRS] = 5; ProdVol[1][GRS] = 5; ProdVol[2][GRS] = -5;
			expected_batch_total = 5.05;
		}
		else if (c == 10) {
			ProdVol[0][GRS] = 5; ProdVol[1][GRS] = 5; ProdVol[2][GRS] = 5;
			expected_batch_total = 15.05;
		}


		//for (i=0, num_pos_prds=0, num_neg_prds=0, sum_pos_prds=0, sum_gas_gv=0; i<pDB.arm[arm].arm_product; i++)
		for (i=0, num_pos_prds=0, num_neg_prds=0, sum_pos_prds=0, sum_gas_gv=0; i<3; i++) {
			if (i != ethanol_prd) {
				if(ProdVol[i][GRS] > 0) {
					num_pos_prds++;
					sum_pos_prds += ProdVol[i][GRS];
				}
				if(ProdVol[i][GRS] < 0) {
					num_neg_prds++;
				}

				sum_gas_gv += ProdVol[i][GRS];
			}
		}

		//for (prd=0; prd<pDB.arm[arm].arm_product; prd++)
		for (prd=0; prd<3; prd++) {
			if(prd == ethanol_prd)
				continue;

			if(sum_gas_gv == 0)
			{
				if (num_neg_prds > 0)
				{
					if(num_pos_prds > 1)
					{
						if(ProdVol[prd][GRS] > 0) 
							ethanol_gv = ProdVol[ethanol_prd][GRS] * ProdVol[prd][GRS] / sum_pos_prds;
						else
							ethanol_gv = 0;
					}
					else if(num_pos_prds == 1)
					{
						if(ProdVol[prd][GRS] > 0) 
							ethanol_gv = ProdVol[ethanol_prd][GRS];
						else
							ethanol_gv = 0;
					}
				}
				else if ((num_neg_prds == 0 && num_pos_prds == 0))
				{
					if(prd == gasoline_prd)	
						ethanol_gv = ProdVol[ethanol_prd][GRS];
					else
						ethanol_gv = 0;
				}
			}

			else if (sum_gas_gv > 0)
			{
				if(num_neg_prds == 0)
				{
					//original divvy code here
					ethanol_gv = ProdVol[ethanol_prd][GRS] * ProdVol[prd][GRS] / sum_gas_gv;
				}
				else if (num_neg_prds > 0)
				{
					if(num_pos_prds > 1)
					{
						if(ProdVol[prd][GRS] > 0) 
							ethanol_gv = ProdVol[ethanol_prd][GRS] * ProdVol[prd][GRS] / sum_gas_gv;
						else
							ethanol_gv = 0;
					}
					else if(num_pos_prds == 1)
					{
						if(ProdVol[prd][GRS] > 0) 
							ethanol_gv = ProdVol[ethanol_prd][GRS];
						else
							ethanol_gv = 0;
					}
				}
			}
			else if(sum_gas_gv < 0)
			{
				if(num_pos_prds == 0)
					ethanol_gv = ProdVol[ethanol_prd][GRS] * ProdVol[prd][GRS] / sum_gas_gv;

				else if(num_pos_prds > 0)
				{
					if(num_pos_prds > 1)
					{
						if(ProdVol[prd][GRS] > 0) 
							ethanol_gv = ProdVol[ethanol_prd][GRS] * ProdVol[prd][GRS] / sum_gas_gv;
						else
							ethanol_gv = 0;
					}
					else if(num_pos_prds == 1)
					{
						if(ProdVol[prd][GRS] > 0) 
							ethanol_gv = ProdVol[ethanol_prd][GRS];
						else
							ethanol_gv = 0;
					}
				}
			}

			

			//ethanol_gsv = ethanol_gv * pAPI_ghol->last_eth_ctpl;
			ethanol_gsv = ethanol_gv * 1;
			//gasoline_gsv = ProdVol[prd][GRS] * ProdVol[prd].avg_ctpl;
			gasoline_gsv = ProdVol[prd][GRS] * 1;

			if(gasoline_gsv > 0)
				BlendVol[prd][GSV] = (ethanol_gsv + gasoline_gsv) * (1 + 0.005);
			else
				BlendVol[prd][GSV] = (ethanol_gsv + gasoline_gsv);
				
			BlendVol[prd][GST] = BlendVol[prd][GSV];
			BlendVol[prd][GRS] = ProdVol[prd][GRS] + ethanol_gv;

		} // end for loop

		// Event log stuff...
		//for (i=0, sum_prds=0, total_batch_vol=0; i<pDB.arm[arm].arm_product; i++)
		for (i=0, sum_prds=0, total_batch_vol=0; i<3; i++)
		{
			sum_prds += ProdVol[i][GRS];
			total_batch_vol += BlendVol[i][GSV];	
		}

		sum_ghols = BlendVol[1][GSV] + BlendVol[2][GSV];

		printf("(%d) [%7.2f %7.2f %7.2f]\t[%7.2f %7.2f]\t[%7.2f %7.2f]\t[%7.2f %7.2f]\n\n", c, ProdVol[0][GRS], ProdVol[1][GRS], ProdVol[2][GRS], BlendVol[1][GSV], BlendVol[2][GSV], sum_prds, sum_ghols, total_batch_vol, expected_batch_total);

	}
		
	return 0;
}
