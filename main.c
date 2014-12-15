/*******************************************************************************
 * (c) Copyright 2008-2013 Microsemi SoC Products Group.  All rights reserved.
 *
 * This example project demonstrates communications with an external flash
 * device.
 *
 * Please refer to the file README.txt for further details about this example.
 *
 * SVN $Revision: 5510 $
 * SVN $Date: 2013-03-29 18:29:47 +0000 (Fri, 29 Mar 2013) $
 */
#include <stdio.h>
//#include "drivers/mss_pdma/mss_pdma.h"
#include "drivers/mss_spi/mss_spi.h"
#include "drivers/at25df641/at25df641.h"
#include "drivers/mss_uart/mss_uart.h"
#include "drivers/mss_sys_services/mss_sys_services.h"
#include "system_m2sxxx.h"


#define BUFFER_A_SIZE  256
#define NB_NIBBLES_IN_INT   8
#define NOTIFY 100*256
/* Manufactuer and device IDs for Atmel AT25DF641 SPI Flash. */
//#define FLASH_MANUFACTURER_ID   (uint8_t)0x01
//#define FLASH_DEVICE_ID         (uint8_t)0x20
#define FLASH_MANUFACTURER_ID   (uint8_t)0xef
#define FLASH_DEVICE_ID         (uint8_t)0x40
#define SPI_DATA_ADDR           0x200000       /// spi data for the firmware 
#define UBOOT_DATA_ADDRESS      0x100000          /// u-boot.bin
#define UBOOT_DATA_SIZE         91212             /// size of u-boot.bin
#define VERSION_ID_ADDR         381           ///version number addr in *.spi 


/// spi addr for the RCU2
/// 0-10000 for u-boot environment
/// 10000 - 400000 for linux
/// 410000 - 400000 for linux

#define SPI_WRITE_ADDR_BASE    0x700000
#define ISP_RESULT_ADDR        0x0
#define VERSION_NEW_ADDR       0x2
#define VERSION_SPI_ADDR       0x4
#define VERSION_OLD_ADDR       0x6

#define CMD_DUMP_DATA           0x31u  
#define CMD_UBOOT_UP           0x32u  
#define CMD_AUTHENTICATE          0x33u
#define CMD_PROGRAM               0x34u
#define CMD_VERIFY                0x35u
#define CMD_RESET                  0x36u
#define IDLE                  0x37u

/* Application Interrupt and Reset Controller */
typedef struct
{
  volatile uint32_t AIRCR_Bits;
} AIRCR_TypeDef;

#define AIRCR_BASE 0xE000ED0C
#define AIRCR                  ((AIRCR_TypeDef *) AIRCR_BASE)
#define SYSRESETREQ_MASK ( (uint32_t)0x1u << 2u)

/*
 * Static global variables
 */
static uint8_t g_flash_wr_buf[BUFFER_A_SIZE];
static uint8_t g_flash_rd_buf[BUFFER_A_SIZE];
static uint8_t g_result[1];

mss_uart_instance_t * const gp_my_uart = &g_mss_uart1;
uint8_t action_code = IDLE;


/* ISP globals */
static long g_src_image_target_address = 0;
/*static long g_src_image_size = 0; Not need, as size is read from SPI header */
static uint32_t g_error_flag = 1;
volatile uint8_t g_isp_operation_busy = 1;

/* Function prototypes */
uint32_t page_read_handler(uint8_t const ** pp_next_page);
void isp_completion_handler(uint32_t value);
static uint32_t read_page_from_flash(uint8_t * g_buffer, uint32_t length);
static void sys_services_event_handler(uint8_t opcode, uint8_t response);
void delay(int n);
static void display_hex_values(const uint8_t * in_buffer, uint32_t byte_length);

/* Function prototype for booting the u-boot */
void copy_spi_image(uint32_t address, uint32_t size);
void spi_flash_bootloader(void);
uint32_t MDDR_status=0;



uint32_t int_to_hex_int(uint32_t value,
                        uint8_t * p_result,
                        uint32_t result_size);
static void display_command(void);
void action_menu(void);
void press_any_key(void);
void dump_spi_image(uint32_t address, uint32_t size);

static uint32_t val_initial_mssddr_facc1_cr = 0U;
static uint32_t val_initial_mssddr_facc2_cr = 0U;



/*==============================================================================
  Messages displayed over the UART.
 */
const uint8_t g_greeting_msg[] =
"\r\n\r\n\
**********************************************************************\r\n\
***************** SmartFusion2 MSS SPI Flash example *****************\r\n\
**********************************************************************\r\n\
This example project demonstrates the use of the SmartFusion2 MSS SPI\r\n\
block.It reads and writes the content of an external SPI flash device\r\n\
---------------------------------------------------------------------\r\n";
/***************************************************************************//**
 * main function.
 */
int main()
{
    volatile uint32_t errors = 0;
    uint32_t address = 0;
    uint16_t loop_count;
    uint8_t i;
    uint8_t manufacturer_id = 0;
    uint8_t device_id = 0;
    uint32_t DELAY_LOAD_VALUE=5000000;
    uint32_t time=DELAY_LOAD_VALUE;
    uint32_t abort = 0;
    uint8_t status = 0;
    uint8_t design_version_mss[2];
    uint8_t design_version_mss_new[2];
    uint8_t design_version_spi[2];
    uint8_t do_programming = 0;
    uint8_t manual_boot = 0;



    g_result[0] = 0;

    SystemInit(); //including DDR Configurations


    /* Disable Watchdog */
    SYSREG->WDOG_CR = 0x00000000;
    MSS_UART_init(gp_my_uart,
                       MSS_UART_115200_BAUD,
                       MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
    MSS_UART_polled_tx_string(gp_my_uart, g_greeting_msg);

    /*--------------------------------------------------------------------------
     * Initialize the write and read Buffers
    */
    for(loop_count = 0; loop_count <(BUFFER_A_SIZE); loop_count++)
    {
        g_flash_wr_buf[loop_count] = loop_count;
        g_flash_rd_buf[loop_count] = 0x00;
    }

    uint32_t clock_setting[2];
    clock_setting[0] = SYSREG->MSSDDR_FACC1_CR;
    clock_setting[1] = 0x0;
    MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r reading MSSDDR_FACC1_CR register ... \n\r ");
    display_hex_values(clock_setting, sizeof(clock_setting));
    MSS_UART_polled_tx_string(gp_my_uart,
			      (const uint8_t*)"\r\n");


    /*--------------------------------------------------------------------------
     * select auto-boot or manual boot 
     * auto-boot: bootloader --> (ISP --> reset if version number is different) --> uboot
     * manual-boot: selectable of each sequence (ISP(1), reset(2), u-boot(3))
    */

    MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r Waiting for uart interrupt to do manual boot... \n\r ");
    MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r (please wait 10 secs in case of auto-boot...\n\r ");
    for(i=0;i<10;i++){
      time = DELAY_LOAD_VALUE;
      MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)".");
      while(abort==0 && time>0){
	if((g_mss_uart1.hw_reg->LSR & 0x1) !=0){
	  abort = 1;
	  break;
	}
	--time;
      }
    }

    if(abort==0){
      MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r autoboot is selected \n\r ");
      manual_boot = 0;
    }else if(abort==1){
      MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r manual boot is selected \n\r ");
      manual_boot = 1;
    }

    /*--------------------------------------------------------------------------
     * Flash Driver Initialization
    */
    FLASH_init(4);
    FLASH_global_unprotect();
    FLASH_erase_4k_block(SPI_WRITE_ADDR_BASE);
    /*--------------------------------------------------------------------------
     * Check SPI Flash part manufacturer and device ID.
    */
    FLASH_read_device_id(&manufacturer_id, &device_id);
    if ((manufacturer_id != FLASH_MANUFACTURER_ID) || (device_id != FLASH_DEVICE_ID)){
      ++errors;
      MSS_UART_polled_tx_string(gp_my_uart, (uint8_t *) "\r\n Wrong SPI Flash device ID \r\n");
    }else{
      MSS_UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n Correct SPI Flash device IDs \r\n");
    }


    /*----------------------------------------------------------------------------
     * design version from firmware 
     */
    MSS_SYS_init(sys_services_event_handler);
    status = MSS_SYS_get_design_version(design_version_mss);
    if(MSS_SYS_SUCCESS == status){
      MSS_UART_polled_tx_string(gp_my_uart,
				(const uint8_t*)"Design version (install in the fabric) : ");
      display_hex_values(design_version_mss, sizeof(design_version_mss));
      MSS_UART_polled_tx_string(gp_my_uart,
				(const uint8_t*)"\r\n");
    }else{
      MSS_UART_polled_tx_string(gp_my_uart,
				(const uint8_t*)"Service get design version failed.\r\n");
      if(MSS_SYS_MEM_ACCESS_ERROR == status){
	MSS_UART_polled_tx_string(gp_my_uart,
				  (const uint8_t*)"Error - MSS memory access error \r\n.");
      }
    }

    /*----------------------------------------------------------------------------
     * design version from spi flash 
    */
    FLASH_read(SPI_DATA_ADDR + VERSION_ID_ADDR -1, design_version_spi, 2);
    MSS_UART_polled_tx_string(gp_my_uart,
			      (const uint8_t*)"Design version (install in the SPI Flash) : ");
    display_hex_values(design_version_spi, sizeof(design_version_spi));
    MSS_UART_polled_tx_string(gp_my_uart,
			      (const uint8_t*)"\r\n");


    /*----------------------------------------------------------------------------
     * write this information in the SPI Flash
     */
    FLASH_program(SPI_WRITE_ADDR_BASE+VERSION_OLD_ADDR, design_version_mss, sizeof(design_version_mss));
    FLASH_program(SPI_WRITE_ADDR_BASE+VERSION_SPI_ADDR, design_version_spi, sizeof(design_version_spi));
    
    /*----------------------------------------------------------------------------
     * judge whether the programming will be executed or not....
    */
    if(design_version_mss[0]==design_version_spi[0]){
      MSS_UART_polled_tx_string(gp_my_uart,
    					  (const uint8_t*)"Version match!! No programming.");
      do_programming = 0;
    }else{
      do_programming = 1;
    }

    if(manual_boot==0){
      if(do_programming==1){

	/* TEST */
	MSS_SYS_init(sys_services_event_handler);
	MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r Authenticate... \n\r ");
	g_isp_operation_busy = 1;
	g_src_image_target_address = SPI_DATA_ADDR;
	MSS_SYS_start_isp(MSS_SYS_PROG_AUTHENTICATE,page_read_handler,isp_completion_handler);
	while(g_isp_operation_busy){;}
	if(g_error_flag == MSS_SYS_SUCCESS){
	  MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r ISP Authentication completed successfully \n\r ");
	  MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r Continuing with ISP Programming... \n\r ");
	  MSS_SYS_init(sys_services_event_handler);

	  /*
	   * Do programming
	   */
	  g_isp_operation_busy = 1;
	  g_src_image_target_address = SPI_DATA_ADDR;
	  MSS_SYS_start_isp(MSS_SYS_PROG_PROGRAM,page_read_handler,isp_completion_handler);
	  while(g_isp_operation_busy){;}
	  if(g_error_flag == MSS_SYS_SUCCESS){
	    MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r ISP programming completed successfully \n\r ");	    
	    MSS_SYS_init(sys_services_event_handler);
	    /*
	     * Do Verify 
	     */
	    g_isp_operation_busy = 1;
	    g_src_image_target_address = SPI_DATA_ADDR;
	    MSS_SYS_start_isp(MSS_SYS_PROG_VERIFY,page_read_handler,isp_completion_handler);	  
	    while(g_isp_operation_busy){;}
	    if(g_error_flag == MSS_SYS_SUCCESS){
	      MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r ISP verifyng completed successfully \n\r ");
	      
	      
	      MSS_SYS_init(sys_services_event_handler);

	      status = MSS_SYS_get_design_version(design_version_mss_new);
	      if(MSS_SYS_SUCCESS == status){
		MSS_UART_polled_tx_string(gp_my_uart,
					  (const uint8_t*)"Design version Newly install in the fabric : ");
		display_hex_values(design_version_mss_new, sizeof(design_version_mss_new));
		MSS_UART_polled_tx_string(gp_my_uart,
					  (const uint8_t*)"\r\n");
	      }else{
		MSS_UART_polled_tx_string(gp_my_uart,
					  (const uint8_t*)"Service get design version failed.\r\n");
		if(MSS_SYS_MEM_ACCESS_ERROR == status){
		  MSS_UART_polled_tx_string(gp_my_uart,
					    (const uint8_t*)"Error - MSS memory access error \r\n.");
		}
	      }
	      	      
	      ///// Flash write the programming results 
	      FLASH_program(SPI_WRITE_ADDR_BASE+VERSION_NEW_ADDR,design_version_mss_new,sizeof(design_version_mss_new)); 
	      clock_setting[1] = SYSREG->MSSDDR_FACC1_CR;
	      MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r reading MSSDDR_FACC1_CR register ... \n\r ");
	      display_hex_values(clock_setting, sizeof(clock_setting));
	      MSS_UART_polled_tx_string(gp_my_uart,
					(const uint8_t*)"\r\n");

	      MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r write original value in MSSDDR_FACC1_CR ... \n\r ");
	      delay(DELAY_LOAD_VALUE);
	      SYSREG->MSSDDR_FACC1_CR = clock_setting[0];
	      delay(DELAY_LOAD_VALUE);
	      clock_setting[1] = SYSREG->MSSDDR_FACC1_CR;
	      
	      MSS_UART_init(gp_my_uart,
			    MSS_UART_115200_BAUD,
			    MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
	      MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r reading MSSDDR_FACC1_CR register again... \n\r ");
	      display_hex_values(clock_setting, sizeof(clock_setting));
	      MSS_UART_polled_tx_string(gp_my_uart,
					(const uint8_t*)"\r\n");

	      FLASH_init(4);
	      FLASH_global_unprotect();
	      
	      /*
	       * Do reset 
	       */
	      //delay(DELAY_LOAD_VALUE);
	      //AIRCR->AIRCR_Bits = 0x05FA0004u;
	    }else{
	      uint8_t value_text[50];
	      uint32_t textsize;
	      textsize = int_to_hex_int(g_error_flag, value_text, 2);
	      MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r ISP verifyng failed with error: ");
	      MSS_UART_polled_tx(gp_my_uart, value_text, textsize);
	      MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)"\n\r");
	      
	      /// do reset 
	      delay(DELAY_LOAD_VALUE);
	      AIRCR->AIRCR_Bits = 0x05FA0004u;
	    }
	  }else{
	    uint8_t value_text[50];
	    uint32_t textsize;
	    textsize = int_to_hex_int(g_error_flag, value_text, 2);
	    MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r ISP Programming failed with error: ");
	    MSS_UART_polled_tx(gp_my_uart, value_text, textsize);
	    MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)"\n\r");
	    /// do reset 
	    delay(DELAY_LOAD_VALUE);
	    AIRCR->AIRCR_Bits = 0x05FA0004u;
	  }
	}else{
	  uint8_t value_text[50];
	  uint32_t textsize;
	  textsize = int_to_hex_int(g_error_flag, value_text, 2);
	  MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r ISP Authentication failed with error: ");
	  MSS_UART_polled_tx(gp_my_uart, value_text, textsize);
	  MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)"\n\r");
	  /// do reset 
	  delay(DELAY_LOAD_VALUE);
	  AIRCR->AIRCR_Bits = 0x05FA0004u;
	}
      }else{ //no programming. do verify???
	
      }	
      ///next step is to boot the u-boot
      spi_flash_bootloader();
    }else if(manual_boot == 1){
      while(1){
	action_menu();
	MSS_SYS_init(sys_services_event_handler);
	
	switch (action_code){
	case CMD_DUMP_DATA:
	  MSS_UART_disable_irq(gp_my_uart, MSS_UART_RBF_IRQ );
	  dump_spi_image(SPI_DATA_ADDR, 100);
	  press_any_key();
	  break;
	case CMD_UBOOT_UP:
	  MSS_UART_disable_irq(gp_my_uart, MSS_UART_RBF_IRQ );
	  spi_flash_bootloader();
	  press_any_key();
	  break;
	case CMD_AUTHENTICATE:
	  MSS_UART_polled_tx_string( gp_my_uart, (const uint8_t *)"\r\nPerforming authentication.  Please wait...\r\n");
	  delay(DELAY_LOAD_VALUE);
	  g_isp_operation_busy = 1;
	  g_src_image_target_address = SPI_DATA_ADDR;
	  MSS_SYS_start_isp(MSS_SYS_PROG_AUTHENTICATE, page_read_handler, isp_completion_handler);
	  while(g_isp_operation_busy) {;}
	  press_any_key();
	  break;
	case CMD_PROGRAM:
	  MSS_UART_polled_tx_string( gp_my_uart, (const uint8_t *)"\r\nPerforming programming.  Please wait...\r\n");
	  delay(DELAY_LOAD_VALUE);
	  g_isp_operation_busy = 1;
	  g_src_image_target_address = SPI_DATA_ADDR;
	  MSS_SYS_start_isp(MSS_SYS_PROG_PROGRAM, page_read_handler, isp_completion_handler);
	  while(g_isp_operation_busy) {;}
	  delay(DELAY_LOAD_VALUE);
	  press_any_key();
	  break;
	case CMD_VERIFY:
	  MSS_UART_polled_tx_string( gp_my_uart, (const uint8_t *)"\r\nPerforming verification.  Please wait...\r\n");
	  delay(DELAY_LOAD_VALUE);
	  g_isp_operation_busy = 1;
	  g_src_image_target_address = SPI_DATA_ADDR;
	  MSS_SYS_start_isp(MSS_SYS_PROG_VERIFY, page_read_handler, isp_completion_handler);
	  while(g_isp_operation_busy) {;}



	  MSS_SYS_init(sys_services_event_handler);
	  status = MSS_SYS_get_design_version(design_version_mss_new);
	  if(MSS_SYS_SUCCESS == status){
	    MSS_UART_polled_tx_string(gp_my_uart,
				      (const uint8_t*)"Design version Newly install in the fabric : ");
	    display_hex_values(design_version_mss_new, sizeof(design_version_mss_new));
	    MSS_UART_polled_tx_string(gp_my_uart,
				      (const uint8_t*)"\r\n");
	  }else{
	    MSS_UART_polled_tx_string(gp_my_uart,
				      (const uint8_t*)"Service get design version failed.\r\n");
	    if(MSS_SYS_MEM_ACCESS_ERROR == status){
	      MSS_UART_polled_tx_string(gp_my_uart,
					(const uint8_t*)"Error - MSS memory access error \r\n.");
	    }
	  }
          FLASH_program(SPI_WRITE_ADDR_BASE+VERSION_NEW_ADDR,design_version_mss_new, sizeof(design_version_mss_new));

	  clock_setting[1] = SYSREG->MSSDDR_FACC1_CR;
	  MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r reading MSSDDR_FACC1_CR register ... \n\r ");
	  display_hex_values(clock_setting, sizeof(clock_setting));
	  MSS_UART_polled_tx_string(gp_my_uart,
				    (const uint8_t*)"\r\n");
	  
	  MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r write original value in MSSDDR_FACC1_CR ... \n\r ");
	  delay(DELAY_LOAD_VALUE);
	  SYSREG->MSSDDR_FACC1_CR = clock_setting[0];
	  delay(DELAY_LOAD_VALUE);
	  clock_setting[1] = SYSREG->MSSDDR_FACC1_CR;
	  
	  MSS_UART_init(gp_my_uart,
			MSS_UART_115200_BAUD,
			MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
	  MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r reading MSSDDR_FACC1_CR register again ... \n\r ");
	  display_hex_values(clock_setting, sizeof(clock_setting));
	  MSS_UART_polled_tx_string(gp_my_uart,
				    (const uint8_t*)"\r\n");
	  
	  FLASH_init(4);
	  FLASH_global_unprotect();

	  press_any_key();
	  break;
	case CMD_RESET:
	  delay(DELAY_LOAD_VALUE);
	  AIRCR->AIRCR_Bits = 0x05FA0004u;
	case IDLE:
	  break;
	default:
	  MSS_UART_polled_tx_string( gp_my_uart, (const uint8_t *)"\r\nError: Invalid action. ");
	  press_any_key();
	}
      }
    }

    while(1){
      ;
    }
    return 0;
}


void isp_completion_handler(uint32_t value)
{
  uint8_t value_text[50];
  uint32_t text_size;

  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"\r\nExit status = ");
  text_size = int_to_hex_int(value, value_text, 8);
  MSS_UART_polled_tx (gp_my_uart, value_text, text_size);

  g_error_flag = value;
  g_isp_operation_busy = 0;
  
}

static uint32_t read_page_from_flash(uint8_t * g_buffer, uint32_t length)
{
  uint32_t num_bytes;
  num_bytes = length;
	
  FLASH_read(g_src_image_target_address-1, g_buffer, num_bytes);

  //////////////////////
  if(g_src_image_target_address==SPI_DATA_ADDR){
    MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"Firmware bitstream (first 128 words)\r\n");
    display_hex_values(g_buffer, 128);
    MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"\r\n");
  }


  if(g_src_image_target_address%(NOTIFY) == 0)
    MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)".");
  g_src_image_target_address += num_bytes;
  
  return num_bytes;
  
}

/* function called by COMM_BLK for input data bit stream*/
uint32_t page_read_handler
(
 uint8_t const ** pp_next_page
)
{
  uint32_t length;
  
  length = read_page_from_flash(g_flash_rd_buf, BUFFER_A_SIZE);
  *pp_next_page = g_flash_rd_buf;
  
  return length;
}


/*------------------------------------------------------------------------------
  Converts Integer to Hex
 */
uint32_t int_to_hex_int
(
 uint32_t value,
 uint8_t * p_result,
 uint32_t result_size
 )
{
  int nibble_idx, nb_nibbles;
  unsigned char conv_array[NB_NIBBLES_IN_INT];
  unsigned int uvalue;
  nibble_idx = 0;
  uvalue = (unsigned int)value;
  
    do {
      int nibble = uvalue & 0x0F;
      if (nibble < 10)
	{
	  conv_array[nibble_idx] = nibble + '0';
	}
      else
	{
	  conv_array[nibble_idx] = nibble  - 10 + 'A';
	}
      uvalue = (uvalue >> 4);
      nibble_idx++;
    } while ((nibble_idx < NB_NIBBLES_IN_INT) && (uvalue > 0));
    
    nb_nibbles = nibble_idx;
    for (nibble_idx = 0; (nibble_idx < nb_nibbles) && (nibble_idx < result_size) ;nibble_idx++ )
      {
        p_result[nibble_idx] = conv_array[nb_nibbles - nibble_idx - 1];
      }
    return nibble_idx;
}

/*
 * System Services event handler
 * */
static void sys_services_event_handler(uint8_t opcode, uint8_t response)
{
   // volatile uint32_t inc;
  uint8_t manufacturer_id = 0;
  uint8_t device_id = 0;
  uint32_t DELAY_LOAD_VALUE=5000000;
  if(FLASH_FREEZE_SHUTDOWN_OPCODE == opcode)
    {
      /* Delay */
      delay(DELAY_LOAD_VALUE);
      
      
      /* Re-initialize the UART. */
      MSS_UART_init(gp_my_uart,
		    MSS_UART_115200_BAUD,
		    MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
      MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r Entered Flash*Freeze, UART and Flash drivers are re-initialized \n\r ");

      /* Re-init flash driver */
      FLASH_init(5);
      FLASH_global_unprotect();
      FLASH_read_device_id(&manufacturer_id, &device_id);
      if ((manufacturer_id != FLASH_MANUFACTURER_ID) || (device_id != FLASH_DEVICE_ID)){
	MSS_UART_polled_tx_string(gp_my_uart, (uint8_t *) "\r\n Wrong SPI Flash device ID \r\n");
      }else{
	MSS_UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n Correct SPI Flash device IDs \r\n");
      }

      
    }
  else if(FLASH_FREEZE_EXIT_OPCODE == opcode)
   {
      
      /* Delay */
      delay(DELAY_LOAD_VALUE);

      /* Re-initialize the UART. */
      MSS_UART_init(gp_my_uart,
		    MSS_UART_115200_BAUD,
		    MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
      MSS_UART_polled_tx_string(gp_my_uart, (uint8_t*)" \n\r Exit Flash*Freeze, UART driver is re-initialized \n\r ");
      
      /* Re-init flash driver */
      FLASH_init(4);
      FLASH_global_unprotect();
      FLASH_read_device_id(&manufacturer_id, &device_id);
      if ((manufacturer_id != FLASH_MANUFACTURER_ID) || (device_id != FLASH_DEVICE_ID)){
	MSS_UART_polled_tx_string(gp_my_uart, (uint8_t *) "\r\n Wrong SPI Flash device ID \r\n");
      }else{
	MSS_UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n Correct SPI Flash device IDs \r\n");
      }
    }

}


/*============================================================
* Delay function
*/
void delay(int n)
{
  while(n>0) {
    n--;
  }
}

static void display_hex_values(const uint8_t * in_buffer,  uint32_t byte_length){

  uint8_t display_buffer[128];
  uint32_t inc;

  if(byte_length > 16u){
    MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"\r\n" );
  }

  for(inc = 0; inc < byte_length; ++inc){
    if((inc > 1u) &&(0u == (inc % 16u))){
      MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"\r\n" );
    }
    snprintf((char *)display_buffer, sizeof(display_buffer), "%02x ", in_buffer[inc]);
    MSS_UART_polled_tx_string(gp_my_uart, display_buffer);
  }
}

/*============================================================
* Copy the SPI Image for u-boot
*/
void copy_spi_image(uint32_t Address, uint32_t Size){
  uint8_t img_buffer[1024];
  uint32_t srcAddr = Address;
  uint32_t size = Size;
  unsigned int jj =0;
  unsigned long length = 0;
  unsigned int ii =0;

  unsigned char *destAddr = (unsigned char *)0xA0000000;



  while(size > 0){

    if(size >=1024){
      length = 1024;
    }else{
      length = size;
    }

    FLASH_read(srcAddr+jj-1, img_buffer, length);

    for(ii=0; ii<length; ii++){
      *destAddr++ = img_buffer[ii];
    }
    
    if(size == UBOOT_DATA_SIZE){
      MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)" data of u-boot.bin from SPI Flash (first 128 words)\r\n" );
      display_hex_values(img_buffer, 128); // sizeof(img_buffer));      
      MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"\r\n" );
      MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"\r\n" );
      MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)" data of u-boot.bin from DDR (first 128 words)\r\n" );
      display_hex_values(destAddr-length, 128); 
      MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"\r\n" );    
    }
    jj += length;
    size -= length;
  }
  
  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t *)"copy_spi_image done \n\r ");


}

/*============================================================
* U-boot bootloader from SPI Flash 
*/
void spi_flash_bootloader(){

  uint32_t DELAY_LOAD_VALUE=5000000;
  SystemInit();
  delay(DELAY_LOAD_VALUE);
  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t *)"SystemInit Re-done \n\r ");

  /* First copy the u-boot.bin in DDR */
  copy_spi_image(UBOOT_DATA_ADDRESS, UBOOT_DATA_SIZE);
  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t *)"copy the SPI data to DDR done\n\r ");

  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t *)"trying to booting the u-boot by remapping DDR space to 0x00000000 \n\r ");
  delay(DELAY_LOAD_VALUE);
  

  MSS_UART_disable_irq(gp_my_uart, MSS_UART_RBF_IRQ );
  int * address = (int *)0x00000004;  //pointer to reset handler of application 
  __set_MSP(*(int*)0xA0000000); //set the stack pointer to that of the application
  *(volatile uint32_t *)(0x40038008) = 0x1;  //Remapping DDR address space to 0x00000000 
  ((void (*)())(*address))(); // pointer recast as function pointer and the dereferenced/called 

  while(1){ };  //This instruction never executed
}

/*============================================================
* display for command 
*/
static void display_command(void){
  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"\r\nEnter desired action to perform in the below mentioned sequence:\n\r");
  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"1. dump the data from SPI \n\r");
  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"2. execute spi_flash_bootloader \n\r");
  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"3. authentication of firmware \n\r");
  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"4. programming of firmware \n\r");
  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"5. verify the firmware\n\r");
  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"6. RESET \n\r");
  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"7. IDLE \n\r");
  MSS_UART_polled_tx_string(gp_my_uart,(const uint8_t*)"Enter valid selection [1-6]: \n\r");
}


/*============================================================
* display for action menu (manual boot)
*/
void action_menu(void){
  uint8_t rx_data = 0;
  uint8_t rx_size = 0;

  display_command();

  MSS_UART_polled_tx_string( gp_my_uart, (const uint8_t *)"\r\n Wait for command...");
  do{
    rx_size = MSS_UART_get_rx(gp_my_uart, &rx_data,1);
  }while(rx_size ==0 );

  if (((rx_data < '1') || (rx_data > '7' )) && rx_size != 0){
    MSS_UART_polled_tx_string( gp_my_uart, (const uint8_t *)"\r\nInvalid action.  Please try again...");
  }else if(rx_size != 0){
    action_code = rx_data;
  }else{
  }
  return ;
}
  
/*============================================================
* press any key
*/
void press_any_key(void){
  uint8_t rx_size = 0;
  uint8_t rx_data = 0;
  
  MSS_UART_polled_tx_string(gp_my_uart, (const uint8_t *)"\r\nPress any key to continue...");
  do {
    rx_size = MSS_UART_get_rx(gp_my_uart, &rx_data,1);
  } while(rx_size == 0);

  //MSS_UART_polled_tx_string(gp_my_uart, (const uint8_t *)"\r\n---------------------------------------------- \r\n" );
  //display_command();

  return;
}

/*============================================================
* dump the SPI data
*/
void dump_spi_image(uint32_t Address, uint32_t Size){
  uint8_t img_buffer[256];
  uint32_t srcAddr = Address;
  uint32_t size = Size;

  unsigned int jj =0;
  unsigned long length = 0;
  while(size > 0){

    if(size >=256){
      length = 256;
    }else{
      length = size;
    }
    FLASH_read(srcAddr +jj-1, img_buffer, length);
    display_hex_values(img_buffer, length); // sizeof(img_buffer));  
    jj += length;
    size -= length;
  }
}
