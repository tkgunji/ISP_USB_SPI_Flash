/*-----------------------------------------------------------*/
/* MDDR Initialization values                                */
/*-----------------------------------------------------------*/

#define MDDR_DDRC_DYN_SOFT_RESET_CR 0x4
#define MDDR_DDRC_RESERVED0 0x0
#define MDDR_DDRC_DYN_REFRESH_1_CR 0x1188
#define MDDR_DDRC_DYN_REFRESH_2_CR 0x290
#define MDDR_DDRC_DYN_POWERDOWN_CR 0x2
#define MDDR_DDRC_DYN_DEBUG_CR 0x0
#define MDDR_DDRC_MODE_CR 0x0
#define MDDR_DDRC_ADDR_MAP_BANK_CR 0x0
#define MDDR_DDRC_ECC_DATA_MASK_CR 0x0
#define MDDR_DDRC_ADDR_MAP_COL_1_CR 0x0
#define MDDR_DDRC_ADDR_MAP_COL_2_CR 0x0
#define MDDR_DDRC_ADDR_MAP_COL_3_CR 0x0
#define MDDR_DDRC_ADDR_MAP_ROW_1_CR 0x0
#define MDDR_DDRC_ADDR_MAP_ROW_2_CR 0x0
#define MDDR_DDRC_INIT_1_CR 0x1
#define MDDR_DDRC_CKE_RSTN_CYCLES_CR1 0x0
#define MDDR_DDRC_CKE_RSTN_CYCLES_CR2 0x0
#define MDDR_DDRC_INIT_MR_CR 0x95A
#define MDDR_DDRC_INIT_EMR_CR 0x402
#define MDDR_DDRC_INIT_EMR2_CR 0x0
#define MDDR_DDRC_INIT_EMR3_CR 0x0
#define MDDR_DDRC_DRAM_BANK_TIMING_PARAM_CR 0x0
#define MDDR_DDRC_DRAM_RD_WR_LATENCY_CR 0x0
#define MDDR_DDRC_DRAM_RD_WR_PRE_CR 0x0
#define MDDR_DDRC_DRAM_MR_TIMING_PARAM_CR 0x0
#define MDDR_DDRC_DRAM_RAS_TIMING_CR 0x0
#define MDDR_DDRC_DRAM_RD_WR_TRNARND_TIME_CR 0x0
#define MDDR_DDRC_DRAM_T_PD_CR 0x0
#define MDDR_DDRC_DRAM_BANK_ACT_TIMING_CR 0x0
#define MDDR_DDRC_ODT_PARAM_1_CR 0x0
#define MDDR_DDRC_ODT_PARAM_2_CR 0x0
#define MDDR_DDRC_DEBUG_CR 0x0
#define MDDR_DDRC_MODE_REG_RD_WR_CR 0x0
#define MDDR_DDRC_MODE_REG_DATA_CR 0x0
#define MDDR_DDRC_PWR_SAVE_1_CR 0x40C
#define MDDR_DDRC_PWR_SAVE_2_CR 0x0
#define MDDR_DDRC_ZQ_LONG_TIME_CR 0x0
#define MDDR_DDRC_ZQ_SHORT_TIME_CR 0x0
#define MDDR_DDRC_ZQ_SHORT_INT_REFRESH_MARGIN_CR1 0x2
#define MDDR_DDRC_ZQ_SHORT_INT_REFRESH_MARGIN_CR2 0x0
#define MDDR_DDRC_PERF_PARAM_1_CR 0x83
#define MDDR_DDRC_HPR_QUEUE_PARAM_CR1 0x0
#define MDDR_DDRC_HPR_QUEUE_PARAM_CR2 0x0
#define MDDR_DDRC_LPR_QUEUE_PARAM_CR1 0x0
#define MDDR_DDRC_LPR_QUEUE_PARAM_CR2 0x0
#define MDDR_DDRC_WR_QUEUE_PARAM_CR 0x0
#define MDDR_DDRC_PERF_PARAM_2_CR 0x0
#define MDDR_DDRC_PERF_PARAM_3_CR 0x0
#define MDDR_DDRC_DFI_RDDATA_EN_CR 0x0
#define MDDR_DDRC_DFI_MIN_CTRLUPD_TIMING_CR 0x3
#define MDDR_DDRC_DFI_MAX_CTRLUPD_TIMING_CR 0x40
#define MDDR_DDRC_DFI_WR_LVL_CONTROL_CR1 0x0
#define MDDR_DDRC_DFI_WR_LVL_CONTROL_CR2 0x0
#define MDDR_DDRC_DFI_RD_LVL_CONTROL_CR1 0x0
#define MDDR_DDRC_DFI_RD_LVL_CONTROL_CR2 0x0
#define MDDR_DDRC_DFI_CTRLUPD_TIME_INTERVAL_CR 0x1016
#define MDDR_DDRC_DYN_SOFT_RESET_ALIAS_CR 0x4
#define MDDR_DDRC_AXI_FABRIC_PRI_ID_CR 0x0
#define MDDR_DDRC_SR 0x0
#define MDDR_DDRC_SINGLE_ERR_CNT_SR 0x0
#define MDDR_DDRC_DOUBLE_ERR_CNT_SR 0x0
#define MDDR_DDRC_LUE_SYNDROME_SR1 0x0
#define MDDR_DDRC_LUE_SYNDROME_SR2 0x0
#define MDDR_DDRC_LUE_SYNDROME_SR3 0x0
#define MDDR_DDRC_LUE_SYNDROME_SR4 0x0
#define MDDR_DDRC_LUE_SYNDROME_SR5 0x0
#define MDDR_DDRC_LUE_ADDRESS_SR1 0x0
#define MDDR_DDRC_LUE_ADDRESS_SR2 0x0
#define MDDR_DDRC_LCE_SYNDROME_SR1 0x0
#define MDDR_DDRC_LCE_SYNDROME_SR2 0x0
#define MDDR_DDRC_LCE_SYNDROME_SR3 0x0
#define MDDR_DDRC_LCE_SYNDROME_SR4 0x0
#define MDDR_DDRC_LCE_SYNDROME_SR5 0x0
#define MDDR_DDRC_LCE_ADDRESS_SR1 0x0
#define MDDR_DDRC_LCE_ADDRESS_SR2 0x0
#define MDDR_DDRC_LCB_NUMBER_SR 0x0
#define MDDR_DDRC_LCB_MASK_SR1 0x0
#define MDDR_DDRC_LCB_MASK_SR2 0x0
#define MDDR_DDRC_LCB_MASK_SR3 0x0
#define MDDR_DDRC_LCB_MASK_SR4 0x0
#define MDDR_DDRC_ECC_INT_SR 0x0
#define MDDR_DDRC_ECC_INT_CLR_REG 0x0
#define MDDR_DDRC_ECC_OUTPUT_DATA_SR 0x0
#define MDDR_PHY_DYN_BIST_TEST_CR 0x0
#define MDDR_PHY_DYN_BIST_TEST_ERRCLR_CR1 0x0
#define MDDR_PHY_DYN_BIST_TEST_ERRCLR_CR2 0x0
#define MDDR_PHY_DYN_BIST_TEST_ERRCLR_CR3 0x0
#define MDDR_PHY_BIST_TEST_SHIFT_PATTERN_CR1 0x0
#define MDDR_PHY_BIST_TEST_SHIFT_PATTERN_CR2 0x0
#define MDDR_PHY_BIST_TEST_SHIFT_PATTERN_CR3 0x0
#define MDDR_PHY_LOOPBACK_TEST_CR 0x0
#define MDDR_PHY_BOARD_LOOPBACK_CR 0x0
#define MDDR_PHY_CTRL_SLAVE_RATIO_CR 0x0
#define MDDR_PHY_CTRL_SLAVE_FORCE_CR 0x0
#define MDDR_PHY_CTRL_SLAVE_DELAY_CR 0x0
#define MDDR_PHY_DATA_SLICE_IN_USE_CR 0x0
#define MDDR_PHY_LVL_NUM_OF_DQ0_CR 0x0
#define MDDR_PHY_DQ_OFFSET_CR1 0x240
#define MDDR_PHY_DQ_OFFSET_CR2 0x4081
#define MDDR_PHY_DQ_OFFSET_CR3 0x0
#define MDDR_PHY_DIS_CALIB_RST_CR 0x0
#define MDDR_PHY_DLL_LOCK_DIFF_CR 0x0
#define MDDR_PHY_FIFO_WE_IN_DELAY_CR1 0x0
#define MDDR_PHY_FIFO_WE_IN_DELAY_CR2 0x0
#define MDDR_PHY_FIFO_WE_IN_DELAY_CR3 0x0
#define MDDR_PHY_FIFO_WE_IN_FORCE_CR 0x0
#define MDDR_PHY_FIFO_WE_SLAVE_RATIO_CR1 0x0
#define MDDR_PHY_FIFO_WE_SLAVE_RATIO_CR2 0x0
#define MDDR_PHY_FIFO_WE_SLAVE_RATIO_CR3 0x0
#define MDDR_PHY_FIFO_WE_SLAVE_RATIO_CR4 0x0
#define MDDR_PHY_GATELVL_INIT_MODE_CR 0x0
#define MDDR_PHY_GATELVL_INIT_RATIO_CR1 0x0
#define MDDR_PHY_GATELVL_INIT_RATIO_CR2 0x0
#define MDDR_PHY_GATELVL_INIT_RATIO_CR3 0x0
#define MDDR_PHY_GATELVL_INIT_RATIO_CR4 0x0
#define MDDR_PHY_LOCAL_ODT_CR 0x0
#define MDDR_PHY_INVERT_CLKOUT_CR 0x0
#define MDDR_PHY_RD_DQS_SLAVE_DELAY_CR1 0x0
#define MDDR_PHY_RD_DQS_SLAVE_DELAY_CR2 0x0
#define MDDR_PHY_RD_DQS_SLAVE_DELAY_CR3 0x0
#define MDDR_PHY_RD_DQS_SLAVE_FORCE_CR 0x0
#define MDDR_PHY_RD_DQS_SLAVE_RATIO_CR1 0x40
#define MDDR_PHY_RD_DQS_SLAVE_RATIO_CR2 0x401
#define MDDR_PHY_RD_DQS_SLAVE_RATIO_CR3 0x4010
#define MDDR_PHY_RD_DQS_SLAVE_RATIO_CR4 0x0
#define MDDR_PHY_WR_DQS_SLAVE_DELAY_CR1 0x0
#define MDDR_PHY_WR_DQS_SLAVE_DELAY_CR2 0x0
#define MDDR_PHY_WR_DQS_SLAVE_DELAY_CR3 0x0
#define MDDR_PHY_WR_DQS_SLAVE_FORCE_CR 0x0
#define MDDR_PHY_WR_DQS_SLAVE_RATIO_CR1 0x0
#define MDDR_PHY_WR_DQS_SLAVE_RATIO_CR2 0x0
#define MDDR_PHY_WR_DQS_SLAVE_RATIO_CR3 0x0
#define MDDR_PHY_WR_DQS_SLAVE_RATIO_CR4 0x0
#define MDDR_PHY_WR_DATA_SLAVE_DELAY_CR1 0x0
#define MDDR_PHY_WR_DATA_SLAVE_DELAY_CR2 0x0
#define MDDR_PHY_WR_DATA_SLAVE_DELAY_CR3 0x0
#define MDDR_PHY_WR_DATA_SLAVE_FORCE_CR 0x0
#define MDDR_PHY_WR_DATA_SLAVE_RATIO_CR1 0x40
#define MDDR_PHY_WR_DATA_SLAVE_RATIO_CR2 0x401
#define MDDR_PHY_WR_DATA_SLAVE_RATIO_CR3 0x401
#define MDDR_PHY_WR_DATA_SLAVE_RATIO_CR4 0x0
#define MDDR_PHY_WRLVL_INIT_MODE_CR 0x0
#define MDDR_PHY_WRLVL_INIT_RATIO_CR1 0x0
#define MDDR_PHY_WRLVL_INIT_RATIO_CR2 0x0
#define MDDR_PHY_WRLVL_INIT_RATIO_CR3 0x0
#define MDDR_PHY_WRLVL_INIT_RATIO_CR4 0x0
#define MDDR_PHY_WR_RD_RL_CR 0x0
#define MDDR_PHY_RDC_FIFO_RST_ERR_CNT_CLR_CR 0x0
#define MDDR_PHY_RDC_WE_TO_RE_DELAY_CR 0x0
#define MDDR_PHY_USE_FIXED_RE_CR 0x0
#define MDDR_PHY_USE_RANK0_DELAYS_CR 0x0
#define MDDR_PHY_USE_LVL_TRNG_LEVEL_CR 0x0
#define MDDR_PHY_DYN_CONFIG_CR 0x0
#define MDDR_PHY_RD_WR_GATE_LVL_CR 0x0
#define MDDR_PHY_DYN_RESET_CR 0x0
#define MDDR_PHY_LEVELLING_FAILURE_SR 0x0
#define MDDR_PHY_BIST_ERROR_SR1 0x0
#define MDDR_PHY_BIST_ERROR_SR2 0x0
#define MDDR_PHY_BIST_ERROR_SR3 0x0
#define MDDR_PHY_WRLVL_DQS_RATIO_SR1 0x0
#define MDDR_PHY_WRLVL_DQS_RATIO_SR2 0x0
#define MDDR_PHY_WRLVL_DQS_RATIO_SR3 0x0
#define MDDR_PHY_WRLVL_DQS_RATIO_SR4 0x0
#define MDDR_PHY_WRLVL_DQ_RATIO_SR1 0x0
#define MDDR_PHY_WRLVL_DQ_RATIO_SR2 0x0
#define MDDR_PHY_WRLVL_DQ_RATIO_SR3 0x0
#define MDDR_PHY_WRLVL_DQ_RATIO_SR4 0x0
#define MDDR_PHY_RDLVL_DQS_RATIO_SR1 0x0
#define MDDR_PHY_RDLVL_DQS_RATIO_SR2 0x0
#define MDDR_PHY_RDLVL_DQS_RATIO_SR3 0x0
#define MDDR_PHY_RDLVL_DQS_RATIO_SR4 0x0
#define MDDR_PHY_FIFO_SR1 0x0
#define MDDR_PHY_FIFO_SR2 0x0
#define MDDR_PHY_FIFO_SR3 0x0
#define MDDR_PHY_FIFO_SR4 0x0
#define MDDR_PHY_MASTER_DLL_SR 0x0
#define MDDR_PHY_DLL_SLAVE_VALUE_SR1 0x0
#define MDDR_PHY_DLL_SLAVE_VALUE_SR2 0x0
#define MDDR_PHY_STATUS_OF_IN_DELAY_VAL_SR1 0x0
#define MDDR_PHY_STATUS_OF_IN_DELAY_VAL_SR2 0x0
#define MDDR_PHY_STATUS_OF_OUT_DELAY_VAL_SR1 0x0
#define MDDR_PHY_STATUS_OF_OUT_DELAY_VAL_SR2 0x0
#define MDDR_PHY_DLL_LOCK_AND_SLAVE_VAL_SR 0x0
#define MDDR_PHY_CTRL_OUTPUT_FILTER_SR 0x0
#define MDDR_PHY_CTRL_OF_OUTPUT_DELAY_SR 0x0
#define MDDR_PHY_RD_DQS_SLAVE_DLL_VAL_SR1 0x0
#define MDDR_PHY_RD_DQS_SLAVE_DLL_VAL_SR2 0x0
#define MDDR_PHY_RD_DQS_SLAVE_DLL_VAL_SR3 0x0
#define MDDR_PHY_WR_DATA_SLAVE_DLL_VAL_SR1 0x0
#define MDDR_PHY_WR_DATA_SLAVE_DLL_VAL_SR2 0x0
#define MDDR_PHY_WR_DATA_SLAVE_DLL_VAL_SR3 0x0
#define MDDR_PHY_FIFO_WE_SLAVE_DLL_VAL_SR1 0x0
#define MDDR_PHY_FIFO_WE_SLAVE_DLL_VAL_SR2 0x0
#define MDDR_PHY_FIFO_WE_SLAVE_DLL_VAL_SR3 0x0
#define MDDR_PHY_WR_DQS_SLAVE_DLL_VAL_SR1 0x0
#define MDDR_PHY_WR_DQS_SLAVE_DLL_VAL_SR2 0x0
#define MDDR_PHY_WR_DQS_SLAVE_DLL_VAL_SR3 0x0
#define MDDR_PHY_CTRL_SLAVE_DLL_VAL_SR 0x0
#define MDDR_DDR_FIC_NB_ADDR_CR 0x0
#define MDDR_DDR_FIC_NBRWB_SIZE_CR 0x0
#define MDDR_DDR_FIC_WB_TIMEOUT_CR 0x0
#define MDDR_DDR_FIC_HPD_SW_RW_EN_CR 0x0
#define MDDR_DDR_FIC_HPD_SW_RW_INVAL_CR 0x0
#define MDDR_DDR_FIC_SW_WR_ERCLR_CR 0x0
#define MDDR_DDR_FIC_ERR_INT_ENABLE_CR 0x0
#define MDDR_DDR_FIC_NUM_AHB_MASTERS_CR 0x0
#define MDDR_DDR_FIC_HPB_ERR_ADDR_SR1 0x0
#define MDDR_DDR_FIC_HPB_ERR_ADDR_SR2 0x0
#define MDDR_DDR_FIC_SW_ERR_ADDR_SR1 0x0
#define MDDR_DDR_FIC_SW_ERR_ADDR_SR2 0x0
#define MDDR_DDR_FIC_HPD_SW_WRB_EMPTY_SR 0x0
#define MDDR_DDR_FIC_SW_HPB_LOCKOUT_SR 0x0
#define MDDR_DDR_FIC_SW_HPD_WERR_SR 0x0
#define MDDR_DDR_FIC_LOCK_TIMEOUTVAL_CR1 0x0
#define MDDR_DDR_FIC_LOCK_TIMEOUTVAL_CR2 0x0
#define MDDR_DDR_FIC_LOCK_TIMEOUT_EN_CR 0x0
#define MDDR_DDR_FIC_RDWR_ERR_SR 0x0

