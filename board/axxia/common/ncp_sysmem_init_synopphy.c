/*
 *  Copyright (C) 2016 Intel (john.jacques@intel.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifdef __UBOOT__
#include <common.h>
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h" /* for macros and stuff mainly */
#include "ncp_sysmem_synopphy.h"
#else
#include <stdio.h>
#include "ncp.h"
#include "ncp_pvt.h"
#include "ncp_sysmem_ext.h"
#include "ncp_sysmem_lsiphy.h" /* for macros and stuff mainly */
#include "ncp_sysmem_synopphy.h"
#endif

ncp_st_t
ncp_sm_ddr4_phy_reg_dump(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode)
{
	ncp_st_t		ncpStatus = NCP_ST_SUCCESS;
	ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);
	ncp_uint32_t		numbytes = 0, bytecnt = 0, tmp = 0, period = 0, freq = 0, numranks = 0, numislands = 0;
	ncp_uint32_t		errorindicated = 0, vreferrorindicated = 0, bits = 0, field = 0, val = 0;

	ncp_phy_DX0GCR0_5600_t regDX0GCR0 = {0};
	ncp_phy_DX0GCR5_5600_t regDX0GCR5 = {0};
	ncp_phy_DX0GCR6_5600_t regDX0GCR6 = {0};
	ncp_phy_DCR_5600_t regDCR = {0};
	ncp_phy_PGCR2_5600_t regPGCR2 = {0};
	ncp_phy_PGCR3_5600_t regPGCR3 = {0};
	ncp_phy_PTR0_5600_t regPTR0 = {0};
	ncp_phy_PTR1_5600_t regPTR1 = {0};
	ncp_phy_PLLCR0_5600_t regPLLCR0 = {0};
	/*ncp_phy_PLLCR_5600_t regPLLCR = {0};*/
	ncp_phy_ZQCR_5600_t regZQCR = {0};
	ncp_phy_MR0_5600_t regMR0 = {0};
	ncp_phy_MR1_5600_t regMR1 = {0};
	ncp_phy_MR2_5600_t regMR2 = {0};
	/*ncp_phy_MR3_5600_t regMR3 = {0};*/
	ncp_phy_MR4_5600_t regMR4 = {0};
	ncp_phy_MR5_5600_t regMR5 = {0};
	ncp_phy_MR6_5600_t regMR6 = {0};
	ncp_phy_DTPR0_5600_t regDTPR0 = {0};
	ncp_phy_DTPR1_5600_t regDTPR1 = {0};
	ncp_phy_DTPR4_5600_t regDTPR4 = {0};
	ncp_phy_DTPR5_5600_t regDTPR5 = {0};
	ncp_phy_PTR3_5600_t regPTR3 = {0};
	ncp_phy_PTR4_5600_t regPTR4 = {0};
	ncp_phy_DXCCR_5600_t regDXCCR = {0};
	ncp_phy_DTCR0_5600_t regDTCR0 = {0};
	ncp_phy_DTCR1_5600_t regDTCR1 = {0};
	ncp_phy_VTCR0_5600_t regVTCR0 = {0};
	ncp_phy_ZQ0PR_5600_t regZQ0PR = {0};
	ncp_phy_DX0RSR0_5600_t regDX0RSR0 = {0};
	ncp_phy_DX0RSR1_5600_t regDX0RSR1 = {0};
	ncp_phy_DX0RSR2_5600_t regDX0RSR2 = {0};
	ncp_phy_DX0RSR3_5600_t regDX0RSR3 = {0};
	ncp_phy_DX0GSR3_5600_t regDX0GSR3 = {0};
	ncp_phy_DX0GSR2_5600_t regDX0GSR2 = {0};
	ncp_phy_RANKIDR_5600_t regRANKIDR = {0};
	ncp_phy_DX0MDLR0_5600_t regDX0MDLR0 = {0};
	ncp_phy_DX0MDLR1_5600_t regDX0MDLR1 = {0};
	ncp_phy_DX0GSR0_5600_t regDX0GSR0 = {0};
	ncp_phy_DX0LCDLR0_5600_t regDX0LCDLR0 = {0};
	ncp_phy_DX0LCDLR1_5600_t regDX0LCDLR1 = {0};
	ncp_phy_DX0LCDLR2_5600_t regDX0LCDLR2 = {0};
	ncp_phy_DX0LCDLR3_5600_t regDX0LCDLR3 = {0};
	ncp_phy_DX0LCDLR4_5600_t regDX0LCDLR4 = {0};
	ncp_phy_DX0GTR0_5600_t regDX0GTR0 = {0};

	for (bytecnt = 0; bytecnt < 9; bytecnt++)
	{
		/* DXnGCR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR0_5600 + (bytecnt * 0x100)), (ncp_uint32_t *)&regDX0GCR0);
		if (regDX0GCR0.dxen)
		{
			numbytes++;
		}
	}
	dbgprintf ("NUM BYTES calculated as %d\n", numbytes);

	/* DCR */
	ncr_read32(phyReg, NCP_PHY_DCR_5600, (ncp_uint32_t *)&regDCR);
	if (regDCR.ddrmd != 0x4)
	{
		dbgprintf ("ERROR: DCR[2:0] - Expect DDR4\n");
	}
	if (regDCR.ddr2t != 0x1)
	{
		dbgprintf ("ERROR: DCR[28] - Expect DDR2T\n");
	}
	if (regDCR.udimm != 0x1)
	{
		dbgprintf ("WARNING: DCR[29] - Expect Address Mirroring\n");
	}
	if (regDCR.ubg)
	{
		dbgprintf ("PHY is configured for x16 DRAM devices\n");
	}
	else
	{
		dbgprintf ("PHY is configured for x8 DRAM devices\n");
	}

	/* PGCR0-5 */
	ncr_read32(phyReg, NCP_PHY_PGCR2_5600, (ncp_uint32_t *)&regPGCR2);
	period = (7800 * 9 * 2 * 1000/regPGCR2.trefprd);
	freq = (1000000 / period);
	dbgprintf ("PGCR2 - Best Guess DDR Clock Frequency = %d MHz\n",freq);

	ncr_read32(phyReg, NCP_PHY_PGCR3_5600, (ncp_uint32_t *)&regPGCR3);
	if (regPGCR3.rdmode != 1)
	{
		dbgprintf ("ERROR: PGCR3 RDMODE should be -Static Read Response\n");
	}

	ncr_read32(phyReg, NCP_PHY_PGCR4_5600, &tmp);
	if (tmp != 0)
	{
		dbgprintf ("ERROR: Check PGCR4 value - 0x%x!\n", tmp);
	}

	/* PTR0-2 */
	ncr_read32(phyReg, NCP_PHY_PTR0_5600, (ncp_uint32_t *)&regPTR0);
	dbgprintf ("tPLLGS = %d ns clocks(min 4000 ns?)\n",(regPTR0.tpllgs * period)/1000);
	dbgprintf ("tPLLPD = %d ns clocks(min 1000 ns?)\n",(regPTR0.tpllpd * period)/1000);

	ncr_read32(phyReg, NCP_PHY_PTR1_5600, (ncp_uint32_t *)&regPTR1);
	dbgprintf ("tPLLRST = %d ns clocks(min 9000 ns?)\n",(regPTR1.tpllrst * period)/1000);
	dbgprintf ("tPLLLOCK = %d ns clocks(min 100000 ns?)\n",(regPTR1.tplllock * period)/1000);

	/* PLLCR0 */
	ncr_read32(phyReg, NCP_PHY_PLLCR0_5600, (ncp_uint32_t *)&regPLLCR0);
	if (((regPLLCR0.frqsel == 0) && (freq < 440)) || ((regPLLCR0.frqsel == 1) && ((freq < 225) || (freq > 490))))
	{
		dbgprintf ("ERROR: PLLCR0.FRQSEL is incorrect for frequency of %d MHz\n",freq);
	}

	/*ncr_read32(phyReg, NCP_PHY_PLLCR_5600, (ncp_uint32_t *)&regPLLCR);
	  if (((regPLLCR.frqsel == 0) && (freq < 440)) || ((regPLLCR.frqsel == 1) && ((freq < 225) || (freq > 490))))
	  {
	  dbgprintf ("ERROR: PLLCR.FRQSEL is incorrect for frequency of %d MHz\n",freq);
	  }*/

	/* ZQCR */
	ncr_read32(phyReg, NCP_PHY_ZQCR_5600, (ncp_uint32_t *)&regZQCR);
	if ((regZQCR.term_off != 0x0) || (regZQCR.zqpd != 0x0))
	{
		dbgprintf ("ZQCR[7:0] should be all 0\n");
	}
	if (regZQCR.pgwait != 0x7)
	{
		dbgprintf ("ERROR: ZQCR.PGWAIT should be 0x7, but got 0x%d\n",regZQCR.pgwait);
	}

	/* MR0-6 */
	ncr_read32(phyReg, NCP_PHY_MR0_5600, (ncp_uint32_t *)&regMR0);
	ncr_read32(phyReg, NCP_PHY_MR0_5600, &tmp);
	dbgprintf ("MR0 = 0x%x\n",tmp);
	dbgprintf ("    - Write Recover/RTP = %s\n", ((regMR0.wr == 0) ? "10/5" :
				(regMR0.wr == 1) ? "12/6" :
				(regMR0.wr == 2) ? "14/7" :
				(regMR0.wr == 3) ? "16/8" :
				(regMR0.wr == 4) ? "18/9" :
				(regMR0.wr == 5) ? "20/10" :
				(regMR0.wr == 6) ? "24/12" :
				"Err/Err"));
	dbgprintf ("    - CAS \t\t= %s\n", ((((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 0) ? "9" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 1) ? "10" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 2) ? "11" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 3) ? "12" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 4) ? "13" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 5) ? "14" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 6) ? "15" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 7) ? "16" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 8) ? "18" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 9) ? "20" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 10) ? "22" :
				(((regMR0.cl_6_4 * 2) + (regMR0.cl_2)) == 11) ? "24" :
				"ERROR"));

	ncr_read32(phyReg, NCP_PHY_MR1_5600, (ncp_uint32_t *)&regMR1);
	ncr_read32(phyReg, NCP_PHY_MR1_5600, &tmp);
	dbgprintf ("MR1 = 0x%x\n",tmp);
	dbgprintf ("    - RTT_NOM \t\t= %s\n", ((((tmp & 0x700) >> 8) == 0) ? "RTT_NOM disabled" :
				(((tmp & 0x700) >> 8) == 1) ? "RZQ/4 (60 ohm)" :
				(((tmp & 0x700) >> 8) == 2) ? "RZQ/2 (120 ohm)" :
				(((tmp & 0x700) >> 8) == 3) ? "RZQ/6 (40 ohm)" :
				(((tmp & 0x700) >> 8) == 4) ? "RZQ/1 (240 ohm)" :
				(((tmp & 0x700) >> 8) == 5) ? "RZQ/5 (48 ohm)" :
				(((tmp & 0x700) >> 8) == 6) ? "RZQ/3 (80 ohm)" :
				"RZQ/7 (38 ohm)"));
	dbgprintf ("    - AL \t\t= %d\n", regMR1.al);
	dbgprintf ("    - DRV Impedance\t= %s\n", ((((tmp & 0x6) >> 1) == 0) ? "RZQ/7 (34 ohm)" :
				(((tmp & 0x6) >> 1) == 1) ? "RZQ/5 (48 ohm)" :
				"ERROR"));

	ncr_read32(phyReg, NCP_PHY_MR2_5600, (ncp_uint32_t *)&regMR2);
	ncr_read32(phyReg, NCP_PHY_MR2_5600, &tmp);
	dbgprintf ("MR2 = 0x%x\n",tmp);
	dbgprintf ("    - Write CRC \t= %s\n", ((tmp & 0x1000) >> 12) ? "ENABLED" : "DISABLED"); /* per jedec */
	dbgprintf ("    - RTT_WR \t\t= %s\n", ((regMR2.rttwr == 0) ? "Dynamic ODT OFF" :
				(regMR2.rttwr == 1) ? "RZQ/2 (120 ohm)" :
				(regMR2.rttwr == 2) ? "RZQ/1 (240 ohm)" :
				"High-Z"));
	dbgprintf ("    - CWL \t\t= %s\n", ((regMR2.cwl == 0) ? "9  - 1600" :
				(regMR2.cwl == 1) ? "10 - 1866" :
				(regMR2.cwl == 2) ? "11 - 2133,1600" :
				(regMR2.cwl == 3) ? "12 - 2400,1866" :
				(regMR2.cwl == 4) ? "14 - 2133" :
				(regMR2.cwl == 5) ? "16 - 2400" :
				(regMR2.cwl == 6) ? "18 - ??" :
				"ERROR"));

	ncr_read32(phyReg, NCP_PHY_MR3_5600, &tmp);
	dbgprintf ("MR3 = 0x%x\n",tmp);

	ncr_read32(phyReg, NCP_PHY_MR4_5600, (ncp_uint32_t *)&regMR4);
	ncr_read32(phyReg, NCP_PHY_MR4_5600, &tmp);
	dbgprintf ("MR4 = 0x%x\n",tmp);
	dbgprintf ("    - Wr/Rd Preamble \t= %d/%d\n", regMR4.wrp, regMR4.rdp);
	dbgprintf ("    - CS to CMD/ADDR latency = %d\n", (regMR4.cs2cmdl == 0) ? 0/*"DISABLED"*/ : (regMR4.cs2cmdl+2));

	ncr_read32(phyReg, NCP_PHY_MR5_5600, (ncp_uint32_t *)&regMR5);
	ncr_read32(phyReg, NCP_PHY_MR5_5600, &tmp);
	dbgprintf ("MR5 = 0x%x\n",tmp);
	dbgprintf ("    - Wr/Rd DBI \t= %d/%d\n", regMR5.wdbi, regMR5.rdbi);
	dbgprintf ("    - CA Parity Latency = %s\n", ((regMR5.capm == 0) ? "DISABLED" :
				(regMR5.capm == 1) ? "4 - 1600,1866,2133" :
				(regMR5.capm == 2) ? "5 - 2400" :
				"ERROR"));

	ncr_read32(phyReg, NCP_PHY_MR6_5600, (ncp_uint32_t *)&regMR6);
	ncr_read32(phyReg, NCP_PHY_MR6_5600, &tmp);
	dbgprintf ("MR6 = 0x%x\n",tmp);
	dbgprintf ("    - tCCD_L \t\t= %s\n", ((regMR6.tccdl == 0) ? "4 - <= 1333" :
				(regMR6.tccdl == 1) ? "5 - <= 1866" :
				(regMR6.tccdl == 2) ? "6 - <= 2400" :
				"ERROR"));
	dbgprintf ("    - VREF Trained value = 0x%X\n",(tmp & 0x7f)); /* from jedec */

	/* DTPR0-6 */
	ncr_read32(phyReg, NCP_PHY_DTPR0_5600, (ncp_uint32_t *)&regDTPR0);
	ncr_read32(phyReg, NCP_PHY_DTPR1_5600, (ncp_uint32_t *)&regDTPR1);
	ncr_read32(phyReg, NCP_PHY_DTPR4_5600, (ncp_uint32_t *)&regDTPR4);
	ncr_read32(phyReg, NCP_PHY_DTPR5_5600, (ncp_uint32_t *)&regDTPR5);

	dbgprintf ("tRC  \t= %d\t",  regDTPR5.trc);
	dbgprintf ("tRRD \t= %d\n",  regDTPR0.trrd);

	dbgprintf ("tRP  \t= %d\t",  regDTPR0.trp);
	dbgprintf ("tWTR \t= %d\t",  regDTPR5.twtr);
	dbgprintf ("tRAS \t= %d\n",  regDTPR0.tras);

	dbgprintf ("tRTP \t= %d\t",  regDTPR0.trtp);
	dbgprintf ("tFAW \t= %d\t",  regDTPR1.tfaw);
	dbgprintf ("tRCD \t= %d\n",  regDTPR5.trcd);

	dbgprintf ("tRFC \t= %d\t",  regDTPR4.trfc);
	dbgprintf ("tMRD \t= %d\t",  regDTPR1.tmrd);
	dbgprintf ("tMOD \t= %d\t",  regDTPR1.tmod);
	dbgprintf ("tWLMRD \t= %d\t",regDTPR1.twlmrd);
	dbgprintf ("tWLO \t= %d\n",  regDTPR4.twlo);

	/* PTR3-4 */
	ncr_read32(phyReg, NCP_PHY_PTR3_5600, (ncp_uint32_t *)&regPTR3);
	ncr_read32(phyReg, NCP_PHY_PTR4_5600, (ncp_uint32_t *)&regPTR4);

	dbgprintf ("tDINIT0 = %d ns (min 500000 ns?)\n",((regPTR3.tdinit0) * period)/1000);
	dbgprintf ("tDINIT1 = %d clocks (tRFC + 5 ?)\n",regPTR3.tdinit1);
	dbgprintf ("tDINIT2 = %d ns (min 200000 ns?)\n",((regPTR4.tdinit2) * period)/1000);

	/* DXCCR */
	ncr_read32(phyReg, NCP_PHY_DXCCR_5600, (ncp_uint32_t *)&regDXCCR);
	ncr_read32(phyReg, NCP_PHY_DXCCR_5600, &tmp);

	dbgprintf ("DXCCR register = 0x%x\n", tmp);
	dbgprintf ("MSBDQ = %d\n",regDXCCR.msbudq);

	/* DTCR0-1 */
	ncr_read32(phyReg, NCP_PHY_DTCR0_5600, (ncp_uint32_t *)&regDTCR0);
	ncr_read32(phyReg, NCP_PHY_DTCR1_5600, (ncp_uint32_t *)&regDTCR1);

	if (regDTCR0.dtmpr == 0) {
		dbgprintf ("ERROR: DQS Gate Training does NOT use MPR. Not Recommended for DDR4\n");
	}
	if (regDTCR0.dtcmpd == 0) {
		dbgprintf ("NOTE: DQS Gate Training does NOT use data comparison.\n");
	}

	if (regDTCR1.ranken == 3)  
	{
		numranks = 2;
	}
	else if (regDTCR1.ranken == 7)  
	{
		numranks = 3;
	}
	else if (regDTCR1.ranken == 15) 
	{
		numranks = 4;
	}
	dbgprintf ("NUMBER of RANKS configured = %d\n", numranks);

	/* VTCR0-1 */
	ncr_read32(phyReg, NCP_PHY_VTCR0_5600, (ncp_uint32_t *)&regVTCR0);
	dbgprintf ("tVREF = %d ns (min 150 ns?)\n",((1 << (regVTCR0.tvref + 4)) * period)/1000);

	dbgprintf ("\n************** ODT and Impedance config - Assuming RZQ=240ohm ******************\n");
	dbgprintf ("\t\t\t");
	numislands = 4;
	for (bytecnt = 0; bytecnt < numislands; bytecnt++) 
	{
		dbgprintf ("Island %d \t", bytecnt);
	}
	dbgprintf ("\n");

	/* ZQnPR */
	dbgprintf ("Output Impedance\t");
	for (bytecnt = 0; bytecnt < numislands; bytecnt++) 
	{
		ncr_read32(phyReg, (NCP_PHY_ZQ0PR_5600 + (0x10 * bytecnt)), (ncp_uint32_t *)&regZQ0PR);
		dbgprintf (" %s \t", (((regZQ0PR.zqdiv & 0xF) == 1 ) ? "240 ohm" :
					((regZQ0PR.zqdiv & 0xF) == 3 ) ? "120 ohm" :
					((regZQ0PR.zqdiv & 0xF) == 5 ) ? "80 ohm" :
					((regZQ0PR.zqdiv & 0xF) == 7 ) ? "60 ohm" :
					((regZQ0PR.zqdiv & 0xF) == 9 ) ? "48 ohm" :
					((regZQ0PR.zqdiv & 0xF) == 11 ) ? "40 ohm" :
					((regZQ0PR.zqdiv & 0xF) == 13 ) ? "34 ohm" :
					"UNKNOWN"));
	} 
	dbgprintf ("\n");
	dbgprintf ("ODT settings\t\t");
	for (bytecnt = 0; bytecnt < numislands; bytecnt++) 
	{
		ncr_read32(phyReg, (NCP_PHY_ZQ0PR_5600 + (0x10 * bytecnt)), (ncp_uint32_t *)&regZQ0PR);
		dbgprintf (" %s \t", ((((regZQ0PR.zqdiv & 0xF0) >> 4) == 1 ) ? "240 ohm" :
					(((regZQ0PR.zqdiv & 0xF0) >> 4) == 3 ) ? "120 ohm" :
					(((regZQ0PR.zqdiv & 0xF0) >> 4) == 5 ) ? "80 ohm" :
					(((regZQ0PR.zqdiv & 0xF0) >> 4) == 7 ) ? "60 ohm" :
					(((regZQ0PR.zqdiv & 0xF0) >> 4) == 9 ) ? "48 ohm" :
					(((regZQ0PR.zqdiv & 0xF0) >> 4) == 11 ) ? "40 ohm" :
					(((regZQ0PR.zqdiv & 0xF0) >> 4) == 13 ) ? "34 ohm" :
					"UNKNOWN"));
	}
	dbgprintf ("\n");

	/* Data Training Results */
	dbgprintf ("\n***********************************************************\n");
	dbgprintf (" ** DDR Training typically occurs in the following order **\n");
	dbgprintf ("***********************************************************\n");
	dbgprintf (" *  1) PHY INIT \t\t-> PHY PLLs are initialized, and delay lines are calibrated\n");
	dbgprintf (" *  2) Write Leveling \t\t-> DQS at DRAM each is aligned to the Clock at each DRAM\n");
	dbgprintf (" *  3) Gate Training \t\t-> The timing for expecting a DQS from DRAM during a read is determined\n");
	dbgprintf (" *  4) Write Latency Adjust \t-> The correct write latency is determined after write leveling\n");
	dbgprintf (" *  5) Static Read Training \t-> Minimum amount of time to leave read data in read FIFOs is determined\n");
	dbgprintf (" *  6) Read bit de-skew \t-> Each bit in a data lane is adjusted for timing to optimize reads\n");
	dbgprintf (" *  7) Write bit de-skew \t-> Each bit in a data lane is adjusted for timing to optimize writes\n");
	dbgprintf (" *  8) Read eye training \t-> Read DQS is adjusted to optimally place DQS edge in center of data eye\n");
	dbgprintf (" *  9) Write eye training \t-> Write DQS is adjusted to optimally place DQS edge in center of data eye\n");
	dbgprintf (" * 10) VREF training \t\t-> Adjust VREF settings in DRAM and in PHY for optimal placement\n");

	dbgprintf ("\n**************** Training Errors *******************\n");
	dbgprintf ("***** All Values in Binary with Error per rank *****\n");
	dbgprintf ("\t\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		dbgprintf ("Byte %d \t", bytecnt);
	}
	dbgprintf ("\n");
	errorindicated = 0;
	vreferrorindicated = 0;

	dbgprintf ("Gate Train Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnRSR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0RSR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0RSR0);
		errorindicated += regDX0RSR0.qsgerr;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0RSR0.qsgerr & 0x8) ? 1 : 0),
				((regDX0RSR0.qsgerr & 0x4) ? 1 : 0),
				((regDX0RSR0.qsgerr & 0x2) ? 1 : 0),
				((regDX0RSR0.qsgerr & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("Read Leveling Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnRSR1 */
		ncr_read32(phyReg, (NCP_PHY_DX0RSR1_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0RSR1);
		errorindicated += regDX0RSR1.rdlvlerr;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0RSR1.rdlvlerr & 0x8) ? 1 : 0),
				((regDX0RSR1.rdlvlerr & 0x4) ? 1 : 0),
				((regDX0RSR1.rdlvlerr & 0x2) ? 1 : 0),
				((regDX0RSR1.rdlvlerr & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("WriteLatencyDQ Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnRSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0RSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0RSR2);
		errorindicated += regDX0RSR2.wlawn;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0RSR2.wlawn & 0x8) ? 1 : 0),
				((regDX0RSR2.wlawn & 0x4) ? 1 : 0),
				((regDX0RSR2.wlawn & 0x2) ? 1 : 0),
				((regDX0RSR2.wlawn & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("Write Latency Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnRSR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0RSR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0RSR3);
		errorindicated += regDX0RSR3.wlaerr;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0RSR3.wlaerr & 0x8) ? 1 : 0),
				((regDX0RSR3.wlaerr & 0x4) ? 1 : 0),
				((regDX0RSR3.wlaerr & 0x2) ? 1 : 0),
				((regDX0RSR3.wlaerr & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("Host VREF Error\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 	
	{
		/* DXnGSR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR3);
		errorindicated += regDX0GSR3.hverr;
		vreferrorindicated += regDX0GSR3.hverr;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0GSR3.hverr & 0x8) ? 1 : 0),
				((regDX0GSR3.hverr & 0x4) ? 1 : 0),
				((regDX0GSR3.hverr & 0x2) ? 1 : 0),
				((regDX0GSR3.hverr & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("Host VREF Warning\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR3);
		errorindicated += regDX0GSR3.hvwrn;
		vreferrorindicated += regDX0GSR3.hvwrn;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0GSR3.hvwrn & 0x8) ? 1 : 0),
				((regDX0GSR3.hvwrn & 0x4) ? 1 : 0),
				((regDX0GSR3.hvwrn & 0x2) ? 1 : 0),
				((regDX0GSR3.hvwrn & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("DRAM VREF Error\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR3);
		errorindicated += regDX0GSR3.dverr;
		vreferrorindicated += regDX0GSR3.dverr;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0GSR3.dverr & 0x8) ? 1 : 0),
				((regDX0GSR3.dverr & 0x4) ? 1 : 0),
				((regDX0GSR3.dverr & 0x2) ? 1 : 0),
				((regDX0GSR3.dverr & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("DRAM VREF Warning\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR3);
		errorindicated += regDX0GSR3.dvwrn;
		vreferrorindicated += regDX0GSR3.dvwrn;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0GSR3.dvwrn & 0x8) ? 1 : 0),
				((regDX0GSR3.dvwrn & 0x4) ? 1 : 0),
				((regDX0GSR3.dvwrn & 0x2) ? 1 : 0),
				((regDX0GSR3.dvwrn & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	if (vreferrorindicated) 
	{
		dbgprintf ("VREF Debug Code\t");
		for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
		{
			/* DXnGSR3 */
			ncr_read32(phyReg, (NCP_PHY_DX0GSR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR3);
			errorindicated += regDX0GSR3.estat;
			vreferrorindicated += regDX0GSR3.estat;
			dbgprintf (" %d%d%d%d \t", 
					((regDX0GSR3.estat & 0x8) ? 1 : 0),
					((regDX0GSR3.estat & 0x4) ? 1 : 0),
					((regDX0GSR3.estat & 0x2) ? 1 : 0),
					((regDX0GSR3.estat & 0x1) ? 1 : 0));
		}
		dbgprintf ("\n");
	}

	dbgprintf ("\n**************** Training Errors *******************\n");
	dbgprintf ("******** All Values in Binary. NOT per rank *********\n");
	dbgprintf ("\t\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		dbgprintf ("Byte %d \t", bytecnt);
	}
	dbgprintf ("\n");

	dbgprintf ("Read bit deskew Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.rderr;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0GSR2.rderr & 0x8) ? 1 : 0),
				((regDX0GSR2.rderr & 0x4) ? 1 : 0),
				((regDX0GSR2.rderr & 0x2) ? 1 : 0),
				((regDX0GSR2.rderr & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("Read bit deskew Warn\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.rdwn;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0GSR2.rdwn & 0x8) ? 1 : 0),
				((regDX0GSR2.rdwn & 0x4) ? 1 : 0),
				((regDX0GSR2.rdwn & 0x2) ? 1 : 0),
				((regDX0GSR2.rdwn & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("Write bit deskew Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.wderr;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0GSR2.wderr & 0x8) ? 1 : 0),
				((regDX0GSR2.wderr & 0x4) ? 1 : 0),
				((regDX0GSR2.wderr & 0x2) ? 1 : 0),
				((regDX0GSR2.wderr & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("Write bit deskew Warn\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.wdwn;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0GSR2.wdwn & 0x8) ? 1 : 0),
				((regDX0GSR2.wdwn & 0x4) ? 1 : 0),
				((regDX0GSR2.wdwn & 0x2) ? 1 : 0),
				((regDX0GSR2.wdwn & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("Read eye Center Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.reerr;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0GSR2.reerr & 0x8) ? 1 : 0),
				((regDX0GSR2.reerr & 0x4) ? 1 : 0),
				((regDX0GSR2.reerr & 0x2) ? 1 : 0),
				((regDX0GSR2.reerr & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("Read eye Center Warn\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.rewn;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0GSR2.rewn & 0x8) ? 1 : 0),
				((regDX0GSR2.rewn & 0x4) ? 1 : 0),
				((regDX0GSR2.rewn & 0x2) ? 1 : 0),
				((regDX0GSR2.rewn & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("Write eye Center Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.weerr;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0GSR2.weerr & 0x8) ? 1 : 0),
				((regDX0GSR2.weerr & 0x4) ? 1 : 0),
				((regDX0GSR2.weerr & 0x2) ? 1 : 0),
				((regDX0GSR2.weerr & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("Write eye Center Warn\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.wewn;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0GSR2.wewn & 0x8) ? 1 : 0),
				((regDX0GSR2.wewn & 0x4) ? 1 : 0),
				((regDX0GSR2.wewn & 0x2) ? 1 : 0),
				((regDX0GSR2.wewn & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	dbgprintf ("Static Read Error\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR2);
		errorindicated += regDX0GSR2.srderr;
		dbgprintf (" %d%d%d%d \t", 
				((regDX0GSR2.srderr & 0x8) ? 1 : 0),
				((regDX0GSR2.srderr & 0x4) ? 1 : 0),
				((regDX0GSR2.srderr & 0x2) ? 1 : 0),
				((regDX0GSR2.srderr & 0x1) ? 1 : 0));
	}
	dbgprintf ("\n");

	if (errorindicated) {
		dbgprintf ("\nERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n");
		dbgprintf ("ERROR: See above for a training error indicated\n");
		dbgprintf ("ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR\n");
	}

	ncr_read32(phyReg, NCP_PHY_RANKIDR_5600, (ncp_uint32_t *)&regRANKIDR);

	dbgprintf ("\n***********************************************************\n");
	dbgprintf ("************ All Results are based on Rank #%d *************\n", regRANKIDR.rankrid);
	dbgprintf ("***********************************************************\n");

	dbgprintf ("\n**************** Period Measurement Results *******************\n");
	dbgprintf ("\t\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		dbgprintf ("Byte %d \t", bytecnt);
	}
	dbgprintf ("\n");

	dbgprintf ("Master Delay Initial\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnMDLR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0MDLR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0MDLR0);
		dbgprintf (" 0x%X \t",regDX0MDLR0.iprd);
	}
	dbgprintf ("\n");

	dbgprintf ("Master Delay Target\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnMDLR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0MDLR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0MDLR0);
		dbgprintf (" 0x%X \t",regDX0MDLR0.tprd);
	}
	dbgprintf ("\n");

	dbgprintf ("Master Delay Selected\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnMDLR1 */
		ncr_read32(phyReg, (NCP_PHY_DX0MDLR1_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0MDLR1);
		dbgprintf (" 0x%X \t",regDX0MDLR1.mdld);
	}
	dbgprintf ("\n");

	dbgprintf ("Write Level Period\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR0);
		dbgprintf (" 0x%X \t",regDX0GSR0.wlprd);
	}
	dbgprintf ("\n");

	dbgprintf ("Read Level Period\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGSR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0GSR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GSR0);
		dbgprintf (" 0x%X \t",regDX0GSR0.gdqsprd);
	}
	dbgprintf ("\n");

	dbgprintf ("\n**************** LCDL Training Results *******************\n");
	dbgprintf ("\t\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		dbgprintf ("Byte %d \t", bytecnt);
	}
	dbgprintf ("\n");

	dbgprintf ("Write DQS Delay\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnLCDLR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0LCDLR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0LCDLR0);
		dbgprintf (" 0x%X \t",regDX0LCDLR0.wld);
	}
	dbgprintf ("\n");

	dbgprintf ("Write Adjust\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGTR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0GTR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GTR0);
		dbgprintf (" %s \t",((regDX0GTR0.wlsl == 0) ? "-1" :
					(regDX0GTR0.wlsl == 1) ? "-0.5" :
					(regDX0GTR0.wlsl == 2) ? "+-0" :
					(regDX0GTR0.wlsl == 3) ? "+0.5" :
					(regDX0GTR0.wlsl == 4) ? "+1" :
					(regDX0GTR0.wlsl == 5) ? "+1.5" :
					(regDX0GTR0.wlsl == 6) ? "+2" :
					(regDX0GTR0.wlsl == 7) ? "+2.5" :
					(regDX0GTR0.wlsl == 8) ? "+3" :
					(regDX0GTR0.wlsl == 9) ? "+3.5" :
					"ERROR"));
	}
	dbgprintf ("\n");

	dbgprintf ("Write Data Delay\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnLCDLR1 */
		ncr_read32(phyReg, (NCP_PHY_DX0LCDLR1_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0LCDLR1);
		dbgprintf (" 0x%X \t",regDX0LCDLR1.wdqd);
	}
	dbgprintf ("\n");

	dbgprintf ("DQS Gate Delay\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnLCDLR2 */
		ncr_read32(phyReg, (NCP_PHY_DX0LCDLR2_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0LCDLR2);
		dbgprintf (" 0x%X \t",regDX0LCDLR2.dqsgd);
	}
	dbgprintf ("\n");

	dbgprintf ("DQS Gate Adjust\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnGTR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0GTR0_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0GTR0);
		if (regDX0GTR0.dgsl == 0) 
		{
			dbgprintf (" +-0 \t");
		}
		else 
		{
			dbgprintf (" +%.1f \t",((double)regDX0GTR0.dgsl/2));
		}		      
	}
	dbgprintf ("\n");

	dbgprintf ("Read DQS Delay\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnLCDLR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0LCDLR3_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0LCDLR3);
		dbgprintf (" 0x%X \t",regDX0LCDLR3.rdqsd);
	}
	dbgprintf ("\n");

	dbgprintf ("Read DQSN Delay\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		/* DXnLCDLR4 */
		ncr_read32(phyReg, (NCP_PHY_DX0LCDLR4_5600 + (0x100 * bytecnt)), (ncp_uint32_t *)&regDX0LCDLR4);
		dbgprintf (" 0x%X \t",regDX0LCDLR4.rdqsnd);
	}
	dbgprintf ("\n");

	dbgprintf ("\n**************** Other Training Results *******************\n");
	dbgprintf ("\t\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		dbgprintf ("Byte %d \t", bytecnt);
	}
	dbgprintf ("\n");

	dbgprintf ("Static Read Delay\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++)
	{
		/* DXnGCR0 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR0_5600 + (bytecnt * 0x100)), (ncp_uint32_t *)&regDX0GCR0);
		dbgprintf (" 0x%X \t",regDX0GCR0.rddly);
	}
	dbgprintf ("\n");

	/* VREF training */
	dbgprintf ("Host VREF rank0\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++)
	{
		/* DXnGCR5 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR5_5600 + (bytecnt * 0x100)), (ncp_uint32_t *)&regDX0GCR5);
		dbgprintf (" 0x%X \t",regDX0GCR5.dxrefiselr0);
	}
	dbgprintf ("\n");

	dbgprintf ("Host VREF rank1\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++)
	{
		/* DXnGCR5 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR5_5600 + (bytecnt * 0x100)), (ncp_uint32_t *)&regDX0GCR5);
		dbgprintf (" 0x%X \t",regDX0GCR5.dxrefiselr1);
	}
	dbgprintf ("\n");

	dbgprintf ("DRAM VREF rank0\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++)
	{
		/* DXnGCR6 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR6_5600 + (bytecnt * 0x100)), (ncp_uint32_t *)&regDX0GCR6);
		dbgprintf (" 0x%X \t",regDX0GCR6.dxdqvrefr0);
	}
	dbgprintf ("\n");

	dbgprintf ("DRAM VREF rank1\t\t");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++)
	{
		/* DXnGCR6 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR6_5600 + (bytecnt * 0x100)), (ncp_uint32_t *)&regDX0GCR6);
		dbgprintf (" 0x%X \t",regDX0GCR6.dxdqvrefr1);
	}
	dbgprintf ("\n");

	dbgprintf ("\n**************** Read Data bit deskew Results *******************\n");
	dbgprintf ("         D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |\n");
	dbgprintf ("         Q  |  Q  |  Q  |  Q  |  Q  |  Q  |  Q  |  Q  |  M  |  Q  |  Q  |\n");
	dbgprintf ("         0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |     |  S  |  SN |\n");
	dbgprintf ("------------------------------------------------------------------\n");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		dbgprintf ("Byte %d ", bytecnt);
		dbgprintf ("  ");
		for (bits = 0; bits <= 10; bits++) 
		{
			field = bits % 4;
			/* DXnBDLR3-6 */
			ncr_read32(phyReg, (NCP_PHY_DX0BDLR3_5600 + (bytecnt * 0x100)), &tmp);
			switch (field)
			{
				case 0:
					val = (tmp & 0x3f);
					break;
				case 1:
					val = (tmp & 0x3f00) >> 8;
					break;
				case 2:
					val = (tmp & 0x3f0000) >> 16;
					break;
				case 3:
					val = (tmp & 0x3f000000) >> 24;
					break;
			}
			dbgprintf ("%d|  ", val);
		}
		dbgprintf ("\n");
	}
	dbgprintf ("\n");

	dbgprintf ("**************** Write Data bit deskew Results *******************\n");
	dbgprintf ("         D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |  D  |  O  |\n");
	dbgprintf ("         Q  |  Q  |  Q  |  Q  |  Q  |  Q  |  Q  |  Q  |  M  |  Q  |  E  |\n");
	dbgprintf ("         0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |     |  S  |     |\n");
	dbgprintf ("------------------------------------------------------------------\n");
	for (bytecnt = 0; bytecnt < numbytes; bytecnt++) 
	{
		dbgprintf ("Byte %d ", bytecnt);
		dbgprintf ("  ");
		for (bits = 0; bits <= 10; bits++) 
		{
			field = bits % 4;
			/* DXnBDLR0-2 */
			ncr_read32(phyReg, (NCP_PHY_DX0BDLR0_5600 + (bytecnt * 0x100)), &tmp);
			switch (field)
			{
				case 0:
					val = (tmp & 0x3f);
					break;
				case 1:
					val = (tmp & 0x3f00) >> 8;
					break;
				case 2:
					val = (tmp & 0x3f0000) >> 16;
					break;
				case 3:
					val = (tmp & 0x3f000000) >> 24;
					break;
			}
			dbgprintf ("%d|  ", val);
		}
		dbgprintf ("\n");
	}
	dbgprintf ("\n");

	/* Trained Registers
#ACLCDLR0
#ACMDLR0
#ACMDLR1
#DXnGTR0
#DXnGTR1
#DXnGTR2
#DXnGTR3
#DXnGSR0
#DXnGSR1
#DXnGSR2
#DXnGSR3
#DXnGSR4
#DXnGSR5
	 */

	NCP_RETURN_LABEL
		return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_phy_training_error_check(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode)
{
	ncp_st_t		ncpStatus = NCP_ST_SUCCESS;
	ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);

	ncp_phy_PGSR0_5600_t regPGSR0 = {0};

	/* Checking Gate Training Error */
	ncr_read32(phyReg, NCP_PHY_PGSR0_5600, (ncp_uint32_t *)&regPGSR0);

	/* ncpStatus = return <appropriate return code TBD> */

	if (regPGSR0.verr)
	{
		errprintf("VREF Training Error\n");
	}

	if (regPGSR0.zcerr)
	{
		errprintf("Impedance Calibration Error\n");
	}

	if (regPGSR0.wlerr)
	{
		errprintf("Write Leveling Error\n");
	}

	if (regPGSR0.qsgerr)
	{
		errprintf("DQS Gate Training Error\n");
	}

	if (regPGSR0.wlaerr)
	{
		errprintf("Write Leveling Adjustment Error\n");
	}

	if (regPGSR0.rderr)
	{
		errprintf("Read Bit Deskew Error\n");
	}

	if (regPGSR0.wderr)
	{
		errprintf("Write Bit Deskew Error\n");
	}

	if (regPGSR0.reerr)
	{
		errprintf("Read Eye Training Error\n");
	}

	if (regPGSR0.weerr)
	{
		errprintf("Write Eye Training Error\n");
	}

	if (regPGSR0.caerr)
	{
		errprintf("CA Training Error\n");
	}

	if (regPGSR0.cawrn)
	{
		errprintf("CA Training Warning\n");
	}

	if (regPGSR0.srderr)
	{
		errprintf("Static Read Error\n");
	}

	NCP_RETURN_LABEL
		return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_phy_training(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode,
		ncp_sm_parms_t *parms)
{
	ncp_st_t		ncpStatus = NCP_ST_SUCCESS;
	ncp_region_id_t 	ctlReg  = NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_DENALI);
	ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);

	ncp_phy_DTCR0_5600_t regDTCR0 = {0};
	ncp_phy_DTCR1_5600_t regDTCR1 = {0};
	ncp_phy_DTAR0_5600_t regDTAR0 = {0};
	ncp_phy_PIR_5600_t regPIR = {0};
	ncp_phy_PGCR0_5600_t regPGCR0 = {0};
	ncp_phy_PGCR3_5600_t regPGCR3 = {0};
	ncp_phy_PGCR1_5600_t regPGCR1 = {0};
	ncp_phy_BISTAR1_5600_t regBISTAR1 = {0};

	ncp_denali_DENALI_CTL_125_5600_t reg125 = {0};
	ncp_denali_DENALI_CTL_368_5600_t reg368 = {0};
	ncp_denali_DENALI_CTL_370_5600_t reg370 = {0};

	/* Started Data Training */
	/*************************/

	/* DTCR0 */
	ncr_read32(phyReg, NCP_PHY_DTCR0_5600, (ncp_uint32_t *)&regDTCR0);
	regDTCR0.dtrptn = 0x7; /* Data Training Repeat Number */
	regDTCR0.dtmpr = (parms->dram_class == NCP_SM_DDR4_MODE) ? 0x0 : 0x1; /* Data Training using MPR */
	regDTCR0.dtcmpd = 0x1; /* DQS Gate training compare data */
	regDTCR0.rfshent = 0x9; /* Assuming PHY refresh enabled during training */
	regDTCR0.dtwbddm = 0x1; /* Data training write bit deskew data mask */
	regDTCR0.dtbdc = 0x1; /* Data training bit deskew centering enables */
	regDTCR0.dtdrs = 0x0; /* DTDRS Data training debug rank select */
	regDTCR0.dtdbs = 0x0; /* DTDBS Data training debug byte select */
	/* RDBI deskewing is not performed */
	if (parms->dbi_rd_en)
	{
		regDTCR0.dtrdbitr = 0x2;
	}
	else
	{
		regDTCR0.dtrdbitr = 0x0;
	}
	regDTCR0.dtden = 0x0; /* DTDEN Data training debug enable */
	regDTCR0.dtdstp = 0x0; /* DTDSTP Data training debug step */
	regDTCR0.dtexd = 0x0; /* DTEXD Data training extended write DQ */
	regDTCR0.dtexg = 0x0; /* DTEXG Data training early/extended gate */
	regDTCR0.rfshdt = 0x9; /* Assuming PHY refresh enabled during training */
	ncr_write32(phyReg, NCP_PHY_DTCR0_5600, *((ncp_uint32_t *)&regDTCR0));

	/* DTCR1 */
	ncr_read32(phyReg, NCP_PHY_DTCR1_5600, (ncp_uint32_t *)&regDTCR1);
	regDTCR1.ranken = parms->topology; /* Each bit will enable each rank */
	regDTCR1.dtrank = 0x0;
	ncr_write32(phyReg, NCP_PHY_DTCR1_5600, *((ncp_uint32_t *)&regDTCR1));

	/* DTAR0 */
	ncr_read32(phyReg, NCP_PHY_DTAR0_5600, (ncp_uint32_t *)&regDTAR0);
	regDTAR0.mprloc = 0x1;
	ncr_write32(phyReg, NCP_PHY_DTAR0_5600, *((ncp_uint32_t *)&regDTAR0));

	/* PIR */
	ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
	regPIR.init = 1; 
	/* Actual init involves selection among the following steps:
	 * ZCAL: impedance calibration
	 * CA: CA training
	 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
	 * DCAL: digital delay line calibration
	 * PHYRST: reset the AC and DATX8
	 * DRAMRST: reset, wait 200us
	 * DRAMINIT: executes DRAM init sequence
	 * WL: write leveling
	 * QSGATE: read dqs gate training
	 * WLADJ: write leveling adjust
	 * RDDSKW: read data bit deskew
	 * WRDSKW: write data bit deskew
	 * RDEYE: read data eye training
	 * WREYE: write data eye training
	 *
	 *
	 * <specials are>
	 * SRD: static read training
	 * VREF: vref training
	 * CTLDINIT: controller performs DRAM init
	 * RDIMMINIT: rdimm init
	 */
	regPIR.zcal = 0; 
	regPIR.ca = 0; 
	regPIR.pllinit = 0; 
	regPIR.dcal = 0; 
	regPIR.phyrst = 0; 
	regPIR.dramrst = 0; 
	regPIR.draminit = 0; 
	regPIR.wl = 1; 
	regPIR.qsgate = 1; 
	regPIR.wladj = 1; 
	regPIR.rddskw = 0; 
	regPIR.wrdskw = 0; 
	regPIR.rdeye = 0; 
	regPIR.wreye = 0; 
	regPIR.srd = 0; 
	regPIR.vref = 0; 
	regPIR.ctldinit = 1; 
	regPIR.rdimminit = 0; 
	ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

	/* Check the General Status register */

	/* poll for idone(bit 0) */
	ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x1,  0x1,  1000000,  10000));

	if (ncpStatus == NCP_ST_POLL_TIMEOUT)
	{
		errprintf("POLL timeout while waiting for training to complete\n");
	}

	/* Checking Gate Training Error's */
	NCP_CALL(ncp_sm_ddr4_phy_training_error_check(dev, smNode));

	/* Perform Static Read Data Training */
	/*************************************/

	/* PGCR0 */
	ncr_read32(phyReg, NCP_PHY_PGCR0_5600, (ncp_uint32_t *)&regPGCR0);
	/* PHY FIFO Reset: 0 resets AC and DATX8 FIFO's without resetting PUB logic.
	 * write 1 to de-assert the reset later */
	regPGCR0.phyfrst = 0x0; 
	ncr_write32(phyReg, NCP_PHY_PGCR0_5600, *((ncp_uint32_t *)&regPGCR0));

	/* PGCR3 */
	ncr_read32(phyReg, NCP_PHY_PGCR3_5600, (ncp_uint32_t *)&regPGCR3);
	regPGCR3.rdmode = 0x1;  /* Static read response */
	ncr_write32(phyReg, NCP_PHY_PGCR3_5600, *((ncp_uint32_t *)&regPGCR3));

	/* PGCR0 */
	ncr_read32(phyReg, NCP_PHY_PGCR0_5600, (ncp_uint32_t *)&regPGCR0);
	/* PHY FIFO Reset: 0 resets AC and DATX8 FIFO's without resetting PUB logic.
	 * write 1 to de-assert the reset later */
	regPGCR0.phyfrst = 0x1; 
	ncr_write32(phyReg, NCP_PHY_PGCR0_5600, *((ncp_uint32_t *)&regPGCR0));

	/* Start SRD trainings */

	/* PIR */
	ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
	regPIR.init = 1; 
	/* Actual init involves selection among the following steps:
	 * ZCAL: impedance calibration
	 * CA: CA training
	 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
	 * DCAL: digital delay line calibration
	 * PHYRST: reset the AC and DATX8
	 * DRAMRST: reset, wait 200us
	 * DRAMINIT: executes DRAM init sequence
	 * WL: write leveling
	 * QSGATE: read dqs gate training
	 * WLADJ: write leveling adjust
	 * RDDSKW: read data bit deskew
	 * WRDSKW: write data bit deskew
	 * RDEYE: read data eye training
	 * WREYE: write data eye training
	 *
	 *
	 * <specials are>
	 * SRD: static read training
	 * VREF: vref training
	 * CTLDINIT: controller performs DRAM init
	 * RDIMMINIT: rdimm init
	 */
	regPIR.zcal = 0; 
	regPIR.ca = 0; 
	regPIR.pllinit = 0; 
	regPIR.dcal = 0; 
	regPIR.phyrst = 0; 
	regPIR.dramrst = 0; 
	regPIR.draminit = 0; 
	regPIR.wl = 0; 
	regPIR.qsgate = 0; 
	regPIR.wladj = 0; 
	regPIR.rddskw = 1; 
	regPIR.wrdskw = 1; 
	regPIR.rdeye = 1; 
	regPIR.wreye = 1; 
	regPIR.srd = 1; 
	regPIR.vref = 0; 
	regPIR.ctldinit = 1; 
	regPIR.rdimminit = 0; 
	ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

	/* Check the General Status register */

	/* poll for idone(bit 0) */
	ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x1,  0x1,  1000000,  10000));

	if (ncpStatus == NCP_ST_POLL_TIMEOUT)
	{
		errprintf("POLL timeout while SRD training\n");
	}

	/* Checking Gate Training Error's */
	NCP_CALL(ncp_sm_ddr4_phy_training_error_check(dev, smNode));

	/* VREF Training */
	/*****************/

	if (!parms->vref_en)
	{
		return ncpStatus;
	}

	/* DTCR1 */
	ncr_read32(phyReg, NCP_PHY_DTCR1_5600, (ncp_uint32_t *)&regDTCR1);
	regDTCR1.ranken = parms->topology; /* Each bit will enable each rank */
	ncr_write32(phyReg, NCP_PHY_DTCR1_5600, *((ncp_uint32_t *)&regDTCR1));

	/* BISTAR1 */
	ncr_read32(phyReg, NCP_PHY_BISTAR1_5600, (ncp_uint32_t *)&regBISTAR1);
	regBISTAR1.bmrank = 0x1; /* BIST Maximum rank */
	ncr_write32(phyReg, NCP_PHY_BISTAR1_5600, *((ncp_uint32_t *)&regBISTAR1));

	/* PIR */
	ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
	regPIR.init = 1; 
	/* Actual init involves selection among the following steps:
	 * ZCAL: impedance calibration
	 * CA: CA training
	 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
	 * DCAL: digital delay line calibration
	 * PHYRST: reset the AC and DATX8
	 * DRAMRST: reset, wait 200us
	 * DRAMINIT: executes DRAM init sequence
	 * WL: write leveling
	 * QSGATE: read dqs gate training
	 * WLADJ: write leveling adjust
	 * RDDSKW: read data bit deskew
	 * WRDSKW: write data bit deskew
	 * RDEYE: read data eye training
	 * WREYE: write data eye training
	 *
	 *
	 * <specials are>
	 * SRD: static read training
	 * VREF: vref training
	 * CTLDINIT: controller performs DRAM init
	 * RDIMMINIT: rdimm init
	 */
	regPIR.zcal = 0; 
	regPIR.ca = 0; 
	regPIR.pllinit = 0; 
	regPIR.dcal = 0; 
	regPIR.phyrst = 0; 
	regPIR.dramrst = 0; 
	regPIR.draminit = 0; 
	regPIR.wl = 0; 
	regPIR.qsgate = 0; 
	regPIR.wladj = 0; 
	regPIR.rddskw = 0; 
	regPIR.wrdskw = 0; 
	regPIR.rdeye = 0; 
	regPIR.wreye = 0; 
	regPIR.srd = 0; 
	regPIR.vref = 1; 
	regPIR.ctldinit = 0; 
	regPIR.rdimminit = 0; 
	ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

	/* Check the General Status register */

	/* poll for idone(bit 0) */
	ncpStatus = (ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x1,  0x1,  1000000,  10000));

	if (ncpStatus == NCP_ST_POLL_TIMEOUT)
	{
		errprintf("POLL timeout while VREF training\n");
	}

	/* Checking Gate Training Error's */
	NCP_CALL(ncp_sm_ddr4_phy_training_error_check(dev, smNode));

	/* PGCR1 */
	ncr_read32(phyReg, NCP_PHY_PGCR1_5600, (ncp_uint32_t *)&regPGCR1);
	/* Enables if set the PUB to control the interface to the PHY and SDRAM.
	 * In this mode the DFI commands from the controller are ignored. The bit must
	 * be set to 0 after the system determines it is convenient to pass control of the DFI
	 * bus to the controller. When set to 0 the DFI interface has control of the PHY and SDRAM
	 * interface except when trigerring pub operations such as BIST, DCU or data training.
	 */
	regPGCR1.pubmode = 0x0;
	ncr_write32(phyReg, NCP_PHY_PGCR1_5600, *((ncp_uint32_t *)&regPGCR1));

	/* DENALI_CTL_125 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_125_5600, (ncp_uint32_t *)&reg125);
	/* enable an automatic controller initiated update after every refresh */
	reg125.ctrlupd_req_per_aref_en = 0x1;
	ncr_write32(ctlReg, NCP_DENALI_CTL_125_5600, *((ncp_uint32_t *)&reg125));

	/* clear 17th and 30th bit of interrupt before clearing the mask, else interrupt gets set. */
	/* DENALI_CTL_368 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_368_5600, (ncp_uint32_t *)&reg368);
	reg368.int_ack = 0x40020000;  /* clears associated bit in int_status */
	ncr_write32(ctlReg, NCP_DENALI_CTL_368_5600, *((ncp_uint32_t *)&reg368));

	/* int_mask */
	/* DENALI_CTL_370 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_370_5600, (ncp_uint32_t *)&reg370);
	reg370.int_mask = 0x0;
	ncr_write32(ctlReg, NCP_DENALI_CTL_370_5600, *((ncp_uint32_t *)&reg370));

	NCP_RETURN_LABEL
		return ncpStatus;
}

ncp_st_t
ncp_sm_ddr4_phy_init(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smNode,
		ncp_sm_parms_t *parms,
		ncp_common_timing_parameters_t *ctm)
{
	ncp_st_t		ncpStatus = NCP_ST_SUCCESS;
	ncp_region_id_t 	ctlReg  = NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_DENALI);
	ncp_region_id_t 	phyReg 	= NCP_REGION_ID(smNode, NCP_SYSMEM_TGT_PHY);
	unsigned int		i = 0;
	unsigned int		tmp = 0;


	ncp_phy_PTR3_5600_t regPTR3 = {0};
	ncp_phy_PTR4_5600_t regPTR4 = {0};
	ncp_phy_DTPR0_5600_t regDTPR0 = {0};
	ncp_phy_DTPR1_5600_t regDTPR1 = {0};
	ncp_phy_DTPR2_5600_t regDTPR2 = {0};
	ncp_phy_DTPR3_5600_t regDTPR3 = {0};
	ncp_phy_DTPR4_5600_t regDTPR4 = {0};
	ncp_phy_DTPR5_5600_t regDTPR5 = {0};
	ncp_phy_DX8GCR0_5600_t regDX8GCR0 = {0};
	ncp_phy_RDIMMGCR0_5600_t regRDIMMGCR0 = {0};
	ncp_phy_RDIMMCR0_5600_t regRDIMMCR0 = {0};
	ncp_phy_RDIMMCR1_5600_t regRDIMMCR1 = {0};
	ncp_phy_RDIMMCR2_5600_t regRDIMMCR2 = {0};
	ncp_phy_RDIMMCR3_5600_t regRDIMMCR3 = {0};
	ncp_phy_RDIMMCR4_5600_t regRDIMMCR4 = {0};
	ncp_phy_DX0GCR1_5600_t regDX0GCR1 = {0};
	ncp_phy_DX0GCR3_5600_t regDX0GCR3 = {0};
	ncp_phy_DCR_5600_t regDCR = {0};
	ncp_phy_PGCR2_5600_t regPGCR2 = {0};
	ncp_phy_PIR_5600_t regPIR = {0};
	ncp_phy_PGCR1_5600_t regPGCR1 = {0};

	ncp_denali_DENALI_CTL_00_5600_t reg00 = {0};
	ncp_denali_DENALI_CTL_368_5600_t reg368 = {0};
	ncp_denali_DENALI_CTL_369_5600_t reg369 = {0};


	/* PTR3 */
	ncr_read32(phyReg, NCP_PHY_PTR3_5600, (ncp_uint32_t *)&regPTR3);
	/* dram init time in cke, use 500us per dwc pub */
	regPTR3.tdinit0 = ncp_ps_to_clk(parms->tck_ps, 500000000);
	regPTR3.tdinit1 = Max(5, (ctm->tRFC + ncp_ps_to_clk(parms->tck_ps, 10000)));
	ncr_write32(phyReg, NCP_PHY_PTR3_5600, *((ncp_uint32_t *)&regPTR3));

	/* PTR4 */
	ncr_read32(phyReg, NCP_PHY_PTR4_5600, (ncp_uint32_t *)&regPTR4);
	/* 200us on power up */
	regPTR4.tdinit2 = ncp_ps_to_clk(parms->tck_ps, 200000000);
	/* time from ZQ init to first command */
	regPTR4.tdinit3 = ctm->tZQinit;
	ncr_write32(phyReg, NCP_PHY_PTR4_5600, *((ncp_uint32_t *)&regPTR4));

	/* DTPR0 */
	ncr_read32(phyReg, NCP_PHY_DTPR0_5600, (ncp_uint32_t *)&regDTPR0);
	regDTPR0.trtp = ctm->tRTP;
	regDTPR0.trp = ctm->tRP;
	regDTPR0.tras = ctm->tRAS;
	regDTPR0.trrd = ctm->tRRD_S;
	ncr_write32(phyReg, NCP_PHY_DTPR0_5600, *((ncp_uint32_t *)&regDTPR0));

	/* DTPR1 */
	ncr_read32(phyReg, NCP_PHY_DTPR1_5600, (ncp_uint32_t *)&regDTPR1);
	regDTPR1.tmrd = ctm->tMRD;
	regDTPR1.tmod = ctm->tMOD;
	regDTPR1.tfaw = ctm->tFAW;
	/*regDTPR1.twlmrd = default */
	ncr_write32(phyReg, NCP_PHY_DTPR1_5600, *((ncp_uint32_t *)&regDTPR1));

	/* DTPR2 */
	ncr_read32(phyReg, NCP_PHY_DTPR2_5600, (ncp_uint32_t *)&regDTPR2);
	regDTPR2.txs = ctm->tXS;
	regDTPR2.tcke = ctm->tCKE;
	/*regDTPR2.trtodt = default */
	/*regDTPR2.trtw = default */
	ncr_write32(phyReg, NCP_PHY_DTPR2_5600, *((ncp_uint32_t *)&regDTPR2));

	/* DTPR3 */
	ncr_read32(phyReg, NCP_PHY_DTPR3_5600, (ncp_uint32_t *)&regDTPR3);
	/*regDTPR3.tdqsck = default */
	/*regDTPR3.tdqsckmax = default */
	/*regDTPR3.tdllk = default */
	regDTPR3.tccd = ctm->tCCD_L;
	/*regDTPR3.tofdx = default */ /* ODT turn-off delay extension */
	ncr_write32(phyReg, NCP_PHY_DTPR3_5600, *((ncp_uint32_t *)&regDTPR3));

	/* DTPR4 */
	ncr_read32(phyReg, NCP_PHY_DTPR4_5600, (ncp_uint32_t *)&regDTPR4);
	/*regDTPR4.txp = default */
	/*regDTPR4.twlo = default */
	regDTPR4.trfc = ctm->tRFC;
	ncr_write32(phyReg, NCP_PHY_DTPR4_5600, *((ncp_uint32_t *)&regDTPR4));

	/* DTPR5 */
	ncr_read32(phyReg, NCP_PHY_DTPR5_5600, (ncp_uint32_t *)&regDTPR5);
	regDTPR5.twtr = ctm->tWTR_L;
	regDTPR5.trcd = ctm->tRCD;
	regDTPR5.trc = ctm->tRC;
	ncr_write32(phyReg, NCP_PHY_DTPR5_5600, *((ncp_uint32_t *)&regDTPR5));

	if (parms->enableECC == FALSE)
	{
		/* DX8GCR0 */
		ncr_read32(phyReg, NCP_PHY_DX8GCR0_5600, (ncp_uint32_t *)&regDX8GCR0);
		regDX8GCR0.dxen = 0;
		ncr_write32(phyReg, NCP_PHY_DX8GCR0_5600, *((ncp_uint32_t *)&regDX8GCR0));
	}

	/* Initializing the ddr4 phy */

	/* Deal with RDIMM stuff */
	if (parms->rdimm_misc & 0x1)
	{
		/* RDIMMGCR0 */
		ncr_read32(phyReg, NCP_PHY_RDIMMGCR0_5600, (ncp_uint32_t *)&regRDIMMGCR0);
		regRDIMMGCR0.rdimm = 1;
		ncr_write32(phyReg, NCP_PHY_RDIMMGCR0_5600, *((ncp_uint32_t *)&regRDIMMGCR0));

		/* RDIMMCR0 */
		ncr_read32(phyReg, NCP_PHY_RDIMMCR0_5600, (ncp_uint32_t *)&regRDIMMCR0);
		regRDIMMCR0.rc0 = parms->rdimm_ctl_0_0 & 0xf; 
		regRDIMMCR0.rc1 = (parms->rdimm_ctl_0_0 & 0xf0) >> 4;
		regRDIMMCR0.rc2 = (parms->rdimm_ctl_0_0 & 0xf00) >> 8;
		regRDIMMCR0.rc3 = (parms->rdimm_ctl_0_0 & 0xf000) >> 12;
		regRDIMMCR0.rc4 = (parms->rdimm_ctl_0_0 & 0xf0000) >> 16;
		regRDIMMCR0.rc5 = (parms->rdimm_ctl_0_0 & 0xf00000) >> 20;
		regRDIMMCR0.rc6 = (parms->rdimm_ctl_0_0 & 0xf000000) >> 24;
		regRDIMMCR0.rc7 = (parms->rdimm_ctl_0_0 & 0xf0000000) >> 28;
		ncr_write32(phyReg, NCP_PHY_RDIMMCR0_5600, *((ncp_uint32_t *)&regRDIMMCR0));

		/* RDIMMCR1 */
		ncr_read32(phyReg, NCP_PHY_RDIMMCR1_5600, (ncp_uint32_t *)&regRDIMMCR1);
		regRDIMMCR1.rc8 = parms->rdimm_ctl_0_1 & 0xf; 
		regRDIMMCR1.rc9 = (parms->rdimm_ctl_0_1 & 0xf0) >> 4;
		regRDIMMCR1.rc10 = (parms->rdimm_ctl_0_1 & 0xf00) >> 8;
		regRDIMMCR1.rc11 = (parms->rdimm_ctl_0_1 & 0xf000) >> 12;
		regRDIMMCR1.rc12 = (parms->rdimm_ctl_0_1 & 0xf0000) >> 16;
		regRDIMMCR1.rc13 = (parms->rdimm_ctl_0_1 & 0xf00000) >> 20;
		regRDIMMCR1.rc14 = (parms->rdimm_ctl_0_1 & 0xf000000) >> 24;
		regRDIMMCR1.rc15 = (parms->rdimm_ctl_0_1 & 0xf0000000) >> 28;
		ncr_write32(phyReg, NCP_PHY_RDIMMCR1_5600, *((ncp_uint32_t *)&regRDIMMCR1));

		/* RDIMMCR2 */
		ncr_read32(phyReg, NCP_PHY_RDIMMCR2_5600, (ncp_uint32_t *)&regRDIMMCR2);
		regRDIMMCR2.rc1x = parms->rdimm_ctl_0_2 & 0xff; 
		regRDIMMCR2.rc2x = (parms->rdimm_ctl_0_2 & 0xff00) >> 8;
		regRDIMMCR2.rc3x = (parms->rdimm_ctl_0_2 & 0xff0000) >> 16;
		regRDIMMCR2.rc4x = (parms->rdimm_ctl_0_2 & 0xff000000) >> 24;
		ncr_write32(phyReg, NCP_PHY_RDIMMCR2_5600, *((ncp_uint32_t *)&regRDIMMCR2));

		/* RDIMMCR3 */
		ncr_read32(phyReg, NCP_PHY_RDIMMCR3_5600, (ncp_uint32_t *)&regRDIMMCR3);
		regRDIMMCR3.rc5x = parms->rdimm_ctl_0_3 & 0xff; 
		regRDIMMCR3.rc6x = (parms->rdimm_ctl_0_3 & 0xff00) >> 8;
		regRDIMMCR3.rc7x = (parms->rdimm_ctl_0_3 & 0xff0000) >> 16;
		regRDIMMCR3.rc8x = (parms->rdimm_ctl_0_3 & 0xff000000) >> 24;
		ncr_write32(phyReg, NCP_PHY_RDIMMCR3_5600, *((ncp_uint32_t *)&regRDIMMCR3));

		/* RDIMMCR4 */
		ncr_read32(phyReg, NCP_PHY_RDIMMCR4_5600, (ncp_uint32_t *)&regRDIMMCR4);
		regRDIMMCR4.rc9x = parms->rdimm_ctl_0_4 & 0xff; 
		regRDIMMCR4.rcax = (parms->rdimm_ctl_0_4 & 0xff00) >> 8;
		regRDIMMCR4.rcbx = (parms->rdimm_ctl_0_4 & 0xff0000) >> 16;
		regRDIMMCR4.rcxx = (parms->rdimm_ctl_0_4 & 0xff000000) >> 24;
		ncr_write32(phyReg, NCP_PHY_RDIMMCR4_5600, *((ncp_uint32_t *)&regRDIMMCR4));
	}

	/* Power Down OFF in PHY */

	for (i = 0; i < 9; i++)
	{
		/* DX0GCR1 .. DX8GCR1 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR1_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR1);
		regDX0GCR1.dxpddmode = 0x0000;
		regDX0GCR1.dxpdrmode = 0xaaaa;
		ncr_write32(phyReg, (NCP_PHY_DX0GCR1_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR1));
	}

	for (i = 0; i < 9; i++)
	{
		/* DX0GCR3 .. DX8GCR3 */
		ncr_read32(phyReg, (NCP_PHY_DX0GCR3_5600 + (0x100 * i)), (ncp_uint32_t *)&regDX0GCR3);
		regDX0GCR3.dspdrmode = 0x2;
		/* default for others ?? */
		ncr_write32(phyReg, (NCP_PHY_DX0GCR3_5600 + (0x100 * i)), *((ncp_uint32_t *)&regDX0GCR3));
	}

	/* PHY DCR Register */

	ncr_read32(phyReg, NCP_PHY_DCR_5600, (ncp_uint32_t *)&regDCR);
	regDCR.ddrmd = (parms->dram_class == NCP_SM_DDR4_MODE) ? 0x4 : 0x3;
	regDCR.ddr8bnk = 0x1; /* SDRAM uses 8 banks or less */
	regDCR.pdq = 0x0; /* which if the 0..7 DQ pins is primary for MPR */
	regDCR.mprdq = 0x1; /* both primary and other DQ pins all drive same data from MPR */

	/* This is for read data on all byte lanes during read DQS gate training */
	if (parms->primary_bus_width == 2)
	{
		/* half-datapath feature */
		regDCR.bytemask = 0xf; 
	}
	else
	{
		regDCR.bytemask = 0xff; 
	}

	/* No simultaneous Rank Access on same clock cycle allowed */
	regDCR.nosra = 0x1; 

	/* 2T timing should be used by PUB generated sdram transactions */
	regDCR.ddr2t = 0x1; 

	/* UDIMM address mirroring */
	/* PUB will rescramble bank and address when sending MR cmds to second rank */
	regDCR.udimm = parms->address_mirroring; 

	ncr_write32(phyReg, NCP_PHY_DCR_5600, *((ncp_uint32_t *)&regDCR));

	/* PHY PGCR2 Register */

	ncr_read32(phyReg, NCP_PHY_PGCR2_5600, (ncp_uint32_t *)&regPGCR2);
	/* ctm->tREFI will account for clock period.
	 * assuming 9 refresh per refresh interval
	 * use 400 clock safety margin per PUB
	 */
	regPGCR2.trefprd = (9 * ctm->tREFI) - 400;
	ncr_write32(phyReg, NCP_PHY_PGCR2_5600, *((ncp_uint32_t *)&regPGCR2));

	/* PHY MR0 Register */
	tmp = ctm->mr0;
	ncr_write32(phyReg, NCP_PHY_MR0_5600, tmp);

	/* PHY MR1 Register */
	tmp = ctm->mr1;
	ncr_write32(phyReg, NCP_PHY_MR1_5600, tmp);

	/* PHY MR2 Register */
	tmp = ctm->mr2;
	ncr_write32(phyReg, NCP_PHY_MR2_5600, tmp);

	/* PHY MR3 Register */
	tmp = ctm->mr3;
	ncr_write32(phyReg, NCP_PHY_MR3_5600, tmp);

	/* PHY MR4 Register */
	tmp = ctm->mr4;
	ncr_write32(phyReg, NCP_PHY_MR4_5600, tmp);

	/* PHY MR5 Register */
	tmp = ctm->mr5;
	ncr_write32(phyReg, NCP_PHY_MR5_5600, tmp);

	/* PHY MR6 Register */
	tmp = ctm->mr6;
	ncr_write32(phyReg, NCP_PHY_MR6_5600, tmp);

	/* PLL init and Impedance Calibration */

	ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
	/* Init trigger for DDR system init including PHY init, DRAM init, and PHY training */
	regPIR.init = 1; 
	/* Actual init involves selection among the following steps:
	 * ZCAL: impedance calibration
	 * CA: CA training
	 * PLLINIT: pll init (pll power, reset, gear shift, wait for lock)
	 * DCAL: digital delay line calibration
	 * PHYRST: reset the AC and DATX8
	 * DRAMRST: reset, wait 200us
	 * DRAMINIT: executes DRAM init sequence
	 * WL: write leveling
	 * QSGATE: read dqs gate training
	 * WLADJ: write leveling adjust
	 * RDDSKW: read data bit deskew
	 * WRDSKW: write data bit deskew
	 * RDEYE: read data eye training
	 * WREYE: write data eye training
	 *
	 *
	 * <specials are>
	 * SRD: static read training
	 * VREF: vref training
	 * CTLDINIT: controller performs DRAM init
	 * RDIMMINIT: rdimm init
	 */
	regPIR.zcal = 1; 
	regPIR.ca = 0; 
	regPIR.pllinit = 1; 
	regPIR.dcal = 1; 
	regPIR.phyrst = 1; 
	regPIR.dramrst = 0; 
	regPIR.draminit = 0; 
	regPIR.wl = 0; 
	regPIR.qsgate = 0; 
	regPIR.wladj = 0; 
	regPIR.rddskw = 0; 
	regPIR.wrdskw = 0; 
	regPIR.rdeye = 0; 
	regPIR.wreye = 0; 
	regPIR.srd = 0; 
	regPIR.vref = 0; 
	regPIR.ctldinit = 0; 
	regPIR.rdimminit = 0; 
	ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

	/* Check the General Status register */

	/* poll for idone(bit 0), pldone(1), dcdone(2), zcdone(3), didone(4) */
	ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x1f,  0x1f,  1000000,  10000);

	/* PHY Init done!!! */

	/* Clear all interrupts */
	/* DENALI_CTL_368 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_368_5600, (ncp_uint32_t *)&reg368);
	reg368.int_ack = 0xffffffff;  /* clears associated bit in int_status */
	ncr_write32(ctlReg, NCP_DENALI_CTL_368_5600, *((ncp_uint32_t *)&reg368));

	/* DENALI_CTL_369 */
	ncr_read32(ctlReg, NCP_DENALI_CTL_369_5600, (ncp_uint32_t *)&reg369);
	reg369.int_ack = 0x3; /* clears associated bit in int_status */
	ncr_write32(ctlReg, NCP_DENALI_CTL_369_5600, *((ncp_uint32_t *)&reg369));

#if 1 	/* Check if this is needed ?? MC is already init'd by this point
	 * should DRAM init be done by PHY-side or should PHY be told Controller will do DRAM init ?? */

	/* PGCR1 */
	ncr_read32(phyReg, NCP_PHY_PGCR1_5600, (ncp_uint32_t *)&regPGCR1);
	/* Enables if set the PUB to control the interface to the PHY and SDRAM.
	 * In this mode the DFI commands from the controller are ignored. The bit must
	 * be set to 0 after the system determines it is convenient to pass control of the DFI
	 * bus to the controller. When set to 0 the DFI interface has control of the PHY and SDRAM
	 * interface except when trigerring pub operations such as BIST, DCU or data training.
	 */
	regPGCR1.pubmode = 0x1;
	ncr_write32(phyReg, NCP_PHY_PGCR1_5600, *((ncp_uint32_t *)&regPGCR1));

	/* SDRAM Initialization by PHY !!! */

	ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
	regPIR.init = 1; 
	regPIR.zcal = 0; 
	regPIR.ca = 0; 
	regPIR.pllinit = 0; 
	regPIR.dcal = 0; 
	regPIR.phyrst = 0; 
	regPIR.dramrst = 1; 
	regPIR.draminit = 1; 
	regPIR.wl = 0; 
	regPIR.qsgate = 0; 
	regPIR.wladj = 0; 
	regPIR.rddskw = 0; 
	regPIR.wrdskw = 0; 
	regPIR.rdeye = 0; 
	regPIR.wreye = 0; 
	regPIR.srd = 0; 
	regPIR.vref = 0; 
	regPIR.ctldinit = 0; 
	regPIR.rdimminit = 0; 
	ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

	/* Check the General Status register */

	/* poll for idone(bit 0), didone(4) */
	ncr_poll(phyReg, NCP_PHY_PGSR0_5600,  0x11,  0x11,  1000000,  10000);

	/* SDRAM Initialization by PHY done !!! */

	/* start MC init operation */
	ncr_read32(ctlReg, NCP_DENALI_CTL_00_5600, (ncp_uint32_t *)&reg00);
	reg00.start = 0x1;
	ncr_write32(ctlReg, NCP_DENALI_CTL_00_5600, *((ncp_uint32_t *)&reg00));

	/* poll for memory init operation bit-8 */
	ncr_poll(ctlReg, NCP_DENALI_CTL_366_5600,  0x0100,  0x0100,  1000000,  10000);
#else
	ncr_read32(phyReg, NCP_PHY_PIR_5600, (ncp_uint32_t *)&regPIR);
	regPIR.init = 1; 
	regPIR.zcal = 0; 
	regPIR.ca = 0; 
	regPIR.pllinit = 0; 
	regPIR.dcal = 0; 
	regPIR.phyrst = 0; 
	regPIR.dramrst = 0; 
	regPIR.draminit = 0; 
	regPIR.wl = 0; 
	regPIR.qsgate = 0; 
	regPIR.wladj = 0; 
	regPIR.rddskw = 0; 
	regPIR.wrdskw = 0; 
	regPIR.rdeye = 0; 
	regPIR.wreye = 0; 
	regPIR.srd = 0; 
	regPIR.vref = 0; 
	regPIR.ctldinit = 1; 
	regPIR.rdimminit = 0; 
	ncr_write32(phyReg, NCP_PHY_PIR_5600, *((ncp_uint32_t *)&regPIR));

	/* start MC init operation */
	ncr_read32(ctlReg, NCP_DENALI_CTL_00_5600, (ncp_uint32_t *)&reg00);
	reg00.start = 0x1;
	ncr_write32(ctlReg, NCP_DENALI_CTL_00_5600, *((ncp_uint32_t *)&reg00));

	/* poll for memory init operation bit-8 */
	ncr_poll(ctlReg, NCP_DENALI_CTL_366_5600,  0x0100,  0x0100,  1000000,  10000);

	/* PGCR1 */
	ncr_read32(phyReg, NCP_PHY_PGCR1_5600, (ncp_uint32_t *)&regPGCR1);
	/* Enables if set the PUB to control the interface to the PHY and SDRAM.
	 * In this mode the DFI commands from the controller are ignored. The bit must
	 * be set to 0 after the system determines it is convenient to pass control of the DFI
	 * bus to the controller. When set to 0 the DFI interface has control of the PHY and SDRAM
	 * interface except when trigerring pub operations such as BIST, DCU or data training.
	 */
	regPGCR1.pubmode = 0x1;
	ncr_write32(phyReg, NCP_PHY_PGCR1_5600, *((ncp_uint32_t *)&regPGCR1));
#endif

	NCP_RETURN_LABEL
		return ncpStatus;
}

ncp_st_t
ncp_sysmem_init_synopphy(
		ncp_dev_hdl_t   dev,
		ncp_uint32_t    smId,
		ncp_sm_parms_t *parms)
{
	ncp_st_t	ncpStatus = NCP_ST_SUCCESS;
	ncp_common_timing_parameters_t	ctm = {0};
	ncp_uint32_t smNode = 0;

#ifndef __UBOOT__
	/* cmem setup
	 * XLF has 1 CMEM, X9 has 2 CMEM's
	 * If smId == 4 && chip == XLF, then setup CMEM-0
	 * If smId == 2 && chip == X9, then setup CMEM-0
	 * If smId == 3 && chip == X9, then setup CMEM-1
	 */

	if (((parms->version == NCP_CHIP_ACPXLF) && (smId == 4)) ||
			((parms->version == NCP_CHIP_ACP56xx) && (smId == 2)) ||
			((parms->version == NCP_CHIP_ACP56xx) && (smId == 3)))
	{
#if 1
		/* until CMEM setup is implemented */
		NCP_CALL(ncp_treemem_init_synopphy(dev, smId, parms));
#endif
		return ncpStatus;
	}
#endif

	switch (smId) {
		case 0:
			smNode  = 0x22;	/* X9/XLF */
			break;
		case 1:
			smNode  = 0xf;	/* X9/XLF */
			break;
		case 2:
			smNode  = 0x23;	/* XLF */
			break;
		case 3:
			smNode  = 0x24;	/* XLF */
			break;
		default:
			NCP_CALL(NCP_ST_ERROR);
	}

	/* ctm is populated so it can be commonly used during mc,phy setup */
	NCP_CALL(ncp_sm_common_setup_56xx(dev, smNode, parms, &ctm)); 

	/* Initialize the system memory controller... */
	NCP_CALL(ncp_sm_denali_2041_init_56xx(dev, smNode, parms, &ctm)); 

	NCP_CALL(ncp_sm_ddr4_phy_init(dev, smNode, parms, &ctm)); 

	/* Now go through training */
	NCP_CALL(ncp_sm_ddr4_phy_training(dev, smNode, parms));

ncp_return:
#ifdef NCP_SM_PHY_REG_DUMP
	if ((NCP_ST_SUCCESS != ncpStatus) && (NCP_ST_ERROR != ncpStatus))
	{
		/* Dump contents of synop phy regs */
		NCP_CALL(ncp_sm_ddr4_phy_reg_dump(dev, smNode));
	}
#endif
	return ncpStatus;
}