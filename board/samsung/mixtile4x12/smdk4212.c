/*
 * (C) Copyright 2011 Samsung Electronics Co. Ltd
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
 
#include <common.h>
#include <asm/arch/cpu.h>
#include <asm/arch/gpio.h>

unsigned int OmPin;

DECLARE_GLOBAL_DATA_PTR;
extern int nr_dram_banks;
unsigned int second_boot_info = 0xffffffff;
unsigned int boot_charge = 0;

/* ------------------------------------------------------------------------- */
#define SMC9115_Tacs	(0x0)	// 0clk		address set-up
#define SMC9115_Tcos	(0x4)	// 4clk		chip selection set-up
#define SMC9115_Tacc	(0xe)	// 14clk	access cycle
#define SMC9115_Tcoh	(0x1)	// 1clk		chip selection hold
#define SMC9115_Tah	(0x4)	// 4clk		address holding time
#define SMC9115_Tacp	(0x6)	// 6clk		page mode access cycle
#define SMC9115_PMC	(0x0)	// normal(1data)page mode configuration

#define SROM_DATA16_WIDTH(x)	(1<<((x*4)+0))
#define SROM_WAIT_ENABLE(x)	(1<<((x*4)+1))
#define SROM_BYTE_ENABLE(x)	(1<<((x*4)+2))

//Apollo +
#define REBOOT_MODE_PREFIX	0x12345670
#define REBOOT_MODE_NONE	0
#define REBOOT_MODE_DOWNLOAD	1
#define REBOOT_MODE_UPLOAD	2
#define REBOOT_MODE_CHARGING	3
#define REBOOT_MODE_RECOVERY	4
#define REBOOT_MODE_ARM11_FOTA	5

#define REBOOT_SET_PREFIX	0xabc00000
#define REBOOT_SET_DEBUG	0x000d0000
#define REBOOT_SET_SWSEL	0x000e0000
#define REBOOT_SET_SUD		0x000f0000

struct recovery_message {
    char command[32];
    char status[32];
    char recovery[1024];
};

void mdelay10(int count)
{
  int i;
  for(i=0; i<count; i++)
    udelay(10000);    
}

void mixtile4x12_gpio_init()
{
  GPIO_Init();
  
  //power off motor --- GPM3_5
  GPIO_SetFunctionEach(eGPIO_M3, eGPIO_5, 1);
  GPIO_SetDataEach(eGPIO_M3, eGPIO_5, 0);

  //power off wifi --- GPM4_5
  GPIO_SetFunctionEach(eGPIO_M4, eGPIO_5, 1);
  GPIO_SetDataEach(eGPIO_M4, eGPIO_5, 0);

  //power off camera --- GPM1_4
  GPIO_SetFunctionEach(eGPIO_M1, eGPIO_4, 1);
  GPIO_SetDataEach(eGPIO_M1, eGPIO_4, 0);

  //power off flash_LED --- GPD0_2
  GPIO_SetFunctionEach(eGPIO_D0, eGPIO_2, 1);
  GPIO_SetDataEach(eGPIO_D0, eGPIO_2, 0);

  //power off TP --- GPM4_2
  GPIO_SetFunctionEach(eGPIO_M4, eGPIO_2, 1);
  GPIO_SetDataEach(eGPIO_M4, eGPIO_2, 0);

  //power off GPS --- GPM4_0
  GPIO_SetFunctionEach(eGPIO_M4, eGPIO_0, 1);
  GPIO_SetDataEach(eGPIO_M4, eGPIO_0, 0);

  //power off LCD_PWR --- GPX2_4
  GPIO_SetFunctionEach(eGPIO_X2, eGPIO_4, 1);
  GPIO_SetDataEach(eGPIO_X2, eGPIO_4, 0);

  //power off LVDS --- GPM3_3
  GPIO_SetFunctionEach(eGPIO_M3, eGPIO_3, 1);
  GPIO_SetDataEach(eGPIO_M3, eGPIO_3, 0);

  //power off LCD_BACK_LED --- GPM3_2
  GPIO_SetFunctionEach(eGPIO_M3, eGPIO_2, 1);
  GPIO_SetDataEach(eGPIO_M3, eGPIO_2, 0);

  //power off 3G --- GPM3_0
  GPIO_SetFunctionEach(eGPIO_M3, eGPIO_0, 1);
  GPIO_SetDataEach(eGPIO_M3, eGPIO_0, 0);

  //power off USB_HUB --- GPM3_7
  GPIO_SetFunctionEach(eGPIO_M3, eGPIO_7, 1);
  GPIO_SetDataEach(eGPIO_M3, eGPIO_7, 0);

  //power off USB_HOST_5V --- GPX3_4
  GPIO_SetFunctionEach(eGPIO_X3, eGPIO_4, 1);
  GPIO_SetDataEach(eGPIO_X3, eGPIO_4, 0);

  //power off OTG_5V --- GPM3_4
  GPIO_SetFunctionEach(eGPIO_M3, eGPIO_4, 1);
  GPIO_SetDataEach(eGPIO_M3, eGPIO_4, 0);

  //power off DM9000 --- GPX3_5
  GPIO_SetFunctionEach(eGPIO_X3, eGPIO_5, 1);
  GPIO_SetDataEach(eGPIO_X3, eGPIO_5, 0);

  // USB OTG ID --- GPX0_0
  GPIO_SetFunctionEach(eGPIO_X0, eGPIO_0, 0);
  GPIO_SetPullUpDownEach(eGPIO_X0, eGPIO_0, 3);

/////////////////////////////////////////////////////////////////////////////////// 
  // VOLUME+_KEY --- GPX2_1
  GPIO_SetFunctionEach(eGPIO_X2, eGPIO_1, 0);
  GPIO_SetPullUpDownEach(eGPIO_X2, eGPIO_1, 3);

  // VOLUME-_KEY --- GPX2_2
  GPIO_SetFunctionEach(eGPIO_X2, eGPIO_2, 0);
  GPIO_SetPullUpDownEach(eGPIO_X2, eGPIO_2, 3);

  // HOME_KEY --- GPX1_2
  GPIO_SetFunctionEach(eGPIO_X1, eGPIO_2, 0);
  GPIO_SetPullUpDownEach(eGPIO_X1, eGPIO_2, 3);
 
  // MENU_KEY --- GPX1_4
  GPIO_SetFunctionEach(eGPIO_X1, eGPIO_4, 0);
  GPIO_SetPullUpDownEach(eGPIO_X1, eGPIO_4, 3);

  // BACK_KEY --- GPX1_5
  GPIO_SetFunctionEach(eGPIO_X1, eGPIO_5, 0);
  GPIO_SetPullUpDownEach(eGPIO_X1, eGPIO_5, 3);

  // RESUME_KEY --- GPX2_5 (HTPC)
  GPIO_SetFunctionEach(eGPIO_X2, eGPIO_5, 0);
  GPIO_SetPullUpDownEach(eGPIO_X2, eGPIO_5, 3);
/////////////////////////////////////////////////////////////////////////////////// 
  //hs-mmc 接口上拉
  GPIO_SetPullUpDownEach(eGPIO_K0, eGPIO_3, 3);
  GPIO_SetPullUpDownEach(eGPIO_K0, eGPIO_4, 3);
  GPIO_SetPullUpDownEach(eGPIO_K0, eGPIO_5, 3);
  GPIO_SetPullUpDownEach(eGPIO_K0, eGPIO_6, 3);

  GPIO_SetPullUpDownEach(eGPIO_K1, eGPIO_3, 3);
  GPIO_SetPullUpDownEach(eGPIO_K1, eGPIO_4, 3);
  GPIO_SetPullUpDownEach(eGPIO_K1, eGPIO_5, 3);
  GPIO_SetPullUpDownEach(eGPIO_K1, eGPIO_6, 3);

  GPIO_SetPullUpDownEach(eGPIO_K2, eGPIO_3, 3);
  GPIO_SetPullUpDownEach(eGPIO_K2, eGPIO_4, 3);
  GPIO_SetPullUpDownEach(eGPIO_K2, eGPIO_5, 3);
  GPIO_SetPullUpDownEach(eGPIO_K2, eGPIO_6, 3);

  GPIO_SetPullUpDownEach(eGPIO_K3, eGPIO_3, 3);
  GPIO_SetPullUpDownEach(eGPIO_K3, eGPIO_5, 3);
  GPIO_SetPullUpDownEach(eGPIO_K3, eGPIO_5, 3);
  GPIO_SetPullUpDownEach(eGPIO_K3, eGPIO_6, 3);
}

//检测是否为软重启
int check_reboot()
{
  if(RST_STAT_REG & (0x1<<29))
    return 1;
  else
    return 0;
}

int check_reboot_reason()
{
  switch(INF_REG2_REG)
  {
    default:
    case REBOOT_MODE_PREFIX | REBOOT_MODE_NONE:
      return 0;
    case REBOOT_MODE_PREFIX | REBOOT_MODE_RECOVERY:
      return 1;
    case REBOOT_MODE_PREFIX | REBOOT_MODE_ARM11_FOTA:
      return 2;
    case REBOOT_MODE_PREFIX | REBOOT_MODE_DOWNLOAD:
      return 3;
    case REBOOT_MODE_PREFIX | REBOOT_MODE_UPLOAD:
      return 4;
    case REBOOT_MODE_PREFIX | REBOOT_MODE_CHARGING:
      return 5;
  }
}

void wait_power_key()
{
  unsigned int check_time = 0;
  
  mixtile4x12_gpio_init();

  // Powerkey_INT --- GPX0_1
  GPIO_SetFunctionEach(eGPIO_X0, eGPIO_1, 0);
  GPIO_SetPullUpDownEach(eGPIO_X0, eGPIO_1, 3);

  if(check_reboot())
  {
    char reboot_cmd[24];
    
    switch(check_reboot_reason())
    {
      default:
      case 0:
        strcpy(reboot_cmd, "null");
        break;
      case 1:
        strcpy(reboot_cmd, "recovery");
        break;
      case 2:
        strcpy(reboot_cmd, "fota");
        break;
      case 3:
        strcpy(reboot_cmd, "download");
        break;
      case 4:
        strcpy(reboot_cmd, "upload");
        break;
      case 5:
        strcpy(reboot_cmd, "chargeing");
        PS_HOLD_CONTROL_REG = (check_time & (~(0x100)));
        break;
    }
  	printf("\nsoft reset: %s!\n", reboot_cmd);
  	return;
  }

  check_time = 0;
  while(!GPIO_GetDataEach(eGPIO_X0, eGPIO_1))
  {
    mdelay10(10);
    if(check_time >= CHECK_KEY_TIME)
      break;
    check_time++;
  }

  if(check_time < CHECK_KEY_TIME)
  {
    //检测是否为充电启动
    int i;
    for(i=0; i<10; i++)
       mdelay10(500);

    if((check_charge() == 1) || (check_time==0))
    {
     	PS_HOLD_CONTROL_REG = (check_time & (~(0x100)));
     	boot_charge = 1;
      return;
    }

  	check_time = PS_HOLD_CONTROL_REG;
  	printf("\nboot key press too short! PS_HOLD = 0x%08x\n", check_time);
    while(1)
    {
      mdelay10(500);
     	PS_HOLD_CONTROL_REG = (check_time & (~(0x100)));
    }
  }
}

int check_power_key()
{
  int ret = 0;
  GPIO_SetFunctionEach(eGPIO_X0, eGPIO_1, 0);
  GPIO_SetPullUpDownEach(eGPIO_X0, eGPIO_1, 3);
  if(GPIO_GetDataEach(eGPIO_X0, eGPIO_1))
    ret = 0;
  else
    ret = 1;
//  printf("%s %d\n", __func__, ret);
  return ret;
}

int check_valumeup_key()
{
  int ret = 0;
  GPIO_SetFunctionEach(eGPIO_X2, eGPIO_1, 0);
  GPIO_SetPullUpDownEach(eGPIO_X2, eGPIO_1, 3);
  if(GPIO_GetDataEach(eGPIO_X2, eGPIO_1))
    ret = 0;
  else
    ret = 1;
//  printf("%s %d\n", __func__, ret);
  return ret;
}

int check_valumedown_key()
{
  int ret = 0;
  GPIO_SetFunctionEach(eGPIO_X2, eGPIO_2, 0);
  GPIO_SetPullUpDownEach(eGPIO_X2, eGPIO_2, 3);
  if(GPIO_GetDataEach(eGPIO_X2, eGPIO_2))
    ret = 0;
  else
    ret = 1;
//  printf("%s %d\n", __func__, ret);
  return ret;
}

int check_resume_key()
{
  int ret = 0;
  GPIO_SetFunctionEach(eGPIO_X1, eGPIO_5, 0);
  GPIO_SetPullUpDownEach(eGPIO_X1, eGPIO_5, 3);
  if(GPIO_GetDataEach(eGPIO_X1, eGPIO_5))
    ret = 0;
  else
    ret = 1;
//  printf("%s %d\n", __func__, ret);
  return ret;
}

int check_charge()
{
  int ret = 0;
  int stat1, stat2;
  GPIO_SetFunctionEach(eGPIO_X3, eGPIO_0, 0);
  GPIO_SetPullUpDownEach(eGPIO_X3, eGPIO_0, 3);
  GPIO_SetFunctionEach(eGPIO_X3, eGPIO_1, 0);
  GPIO_SetPullUpDownEach(eGPIO_X3, eGPIO_1, 3);
  mdelay10(10);
  stat1 = GPIO_GetDataEach(eGPIO_X3, eGPIO_0);
  stat2 = GPIO_GetDataEach(eGPIO_X3, eGPIO_1);

  if((stat1==1) || ((stat1==0) && (stat2==1)))
    ret = 1;

  printf("%s %d %d %d\n", __func__, stat1, stat2, ret);
//开发板
#ifdef COFIG_DEVBOARD
  return 0;
#else
  return ret;
#endif
}
//Apollo -

/*
 * Miscellaneous platform dependent initialisations
 */
static void smc9115_pre_init(void)
{
        unsigned int cs1;
	/* gpio configuration */
	writel(0x00220020, 0x11000000 + 0x120);
	writel(0x00002222, 0x11000000 + 0x140);

	/* 16 Bit bus width */
	writel(0x22222222, 0x11000000 + 0x180);
	writel(0x0000FFFF, 0x11000000 + 0x188);
	writel(0x22222222, 0x11000000 + 0x1C0);
	writel(0x0000FFFF, 0x11000000 + 0x1C8);
	writel(0x22222222, 0x11000000 + 0x1E0);
	writel(0x0000FFFF, 0x11000000 + 0x1E8);

//	/* SROM BANK1 */
//        cs1 = SROM_BW_REG & ~(0xF<<4);
//	cs1 |= ((1 << 0) |
//		(0 << 2) |
//		(1 << 3)) << 4;                
//
//        SROM_BW_REG = cs1;

//	/* set timing for nCS1 suitable for ethernet chip */
//	SROM_BC1_REG = ( (0x1 << 0) |
//		     (0x9 << 4) |
//		     (0xc << 8) |
//		     (0x1 << 12) |
//		     (0x6 << 16) |
//		     (0x1 << 24) |
//		     (0x1 << 28) );
}

int board_init(void)
{
	char bl1_version[9] = {0};
#ifdef ENABLE_PMIC
	u8 read_id;
	u8 read_vol_arm;
	u8 read_vol_int;
	u8 read_vol_g3d;
	u8 read_vol_mif;
	u8 buck1_ctrl;
	u8 buck2_ctrl;
	u8 buck3_ctrl;
	u8 buck4_ctrl;
	u8 ldo14_ctrl;

	IIC0_ERead(0xcc, 0, &read_id);
	if (read_id == 0x77) {
		IIC0_ERead(0xcc, 0x19, &read_vol_arm);
		IIC0_ERead(0xcc, 0x22, &read_vol_int);
		IIC0_ERead(0xcc, 0x2B, &read_vol_g3d);
		//IIC0_ERead(0xcc, 0x2D, &read_vol_mif);
		IIC0_ERead(0xcc, 0x18, &buck1_ctrl);
		IIC0_ERead(0xcc, 0x21, &buck2_ctrl);
		IIC0_ERead(0xcc, 0x2A, &buck3_ctrl);
		//IIC0_ERead(0xcc, 0x2C, &buck4_ctrl);
		IIC0_ERead(0xcc, 0x48, &ldo14_ctrl);

		printf("vol_arm: %X\n", read_vol_arm);
		printf("vol_int: %X\n", read_vol_int);
		printf("vol_g3d: %X\n", read_vol_g3d);
		printf("buck1_ctrl: %X\n", buck1_ctrl);
		printf("buck2_ctrl: %X\n", buck2_ctrl);
		printf("buck3_ctrl: %X\n", buck3_ctrl);
		printf("ldo14_ctrl: %X\n", ldo14_ctrl);
	} else if ((0 <= read_id) && (read_id <= 0x5)) {
		IIC0_ERead(0xcc, 0x33, &read_vol_mif);
		IIC0_ERead(0xcc, 0x35, &read_vol_arm);
		IIC0_ERead(0xcc, 0x3E, &read_vol_int);
		IIC0_ERead(0xcc, 0x47, &read_vol_g3d);
		printf("vol_mif: %X\n", read_vol_mif);
		printf("vol_arm: %X\n", read_vol_arm);
		printf("vol_int: %X\n", read_vol_int);
		printf("vol_g3d: %X\n", read_vol_g3d);
	} else {
		IIC0_ERead(0x12, 0x14, &read_vol_arm);
		IIC0_ERead(0x12, 0x1E, &read_vol_int);
		IIC0_ERead(0x12, 0x28, &read_vol_g3d);
		IIC0_ERead(0x12, 0x11, &read_vol_mif);
		IIC0_ERead(0x12, 0x10, &buck1_ctrl);
		IIC0_ERead(0x12, 0x12, &buck2_ctrl);
		IIC0_ERead(0x12, 0x1C, &buck3_ctrl);
		IIC0_ERead(0x12, 0x26, &buck4_ctrl);

		printf("vol_arm: %X\n", read_vol_arm);
		printf("vol_int: %X\n", read_vol_int);
		printf("vol_g3d: %X\n", read_vol_g3d);
		printf("vol_mif: %X\n", read_vol_mif);
		printf("buck1_ctrl: %X\n", buck1_ctrl);
		printf("buck2_ctrl: %X\n", buck2_ctrl);
		printf("buck3_ctrl: %X\n", buck3_ctrl);
		printf("buck4_ctrl: %X\n", buck4_ctrl);
	}
#endif /* ENABLE_PMIC */

	/* display BL1 version */
#ifdef CONFIG_TRUSTZONE
	printf("TrustZone Enabled BSP\n");
	strncpy(&bl1_version[0], (char *)0x0204f810, 8);
#else
	strncpy(&bl1_version[0], (char *)0x020233c8, 8);
#endif
	printf("BL1 version: %s\n", &bl1_version[0]);

	/* check half synchronizer for asynchronous bridge */
	if(*(unsigned int *)(0x10010350) == 0x1)
		printf("Using half synchronizer for asynchronous bridge\n");
//fighter++	
//#ifdef CONFIG_SMC911X
//	smc9115_pre_init();
//#endif
	smc9115_pre_init();
//fighter++

#ifdef CONFIG_SMDKC220
	gd->bd->bi_arch_number = MACH_TYPE_C220;
#else
	if(((PRO_ID & 0x300) >> 8) == 2)
		gd->bd->bi_arch_number = MACH_TYPE_C210;
	else
		gd->bd->bi_arch_number = MACH_TYPE_V310;
#endif

	gd->bd->bi_boot_params = (PHYS_SDRAM_1+0x100);

   	OmPin = INF_REG3_REG;
	printf("OM_STAT=0x%08x\n", *((unsigned int *)(0x10020000)));
	printf("Checking Boot Mode ...");
	if(OmPin == BOOT_ONENAND) {
		printf(" OneNand\n");
	} else if (OmPin == BOOT_NAND) {
		printf(" NAND\n");
	} else if (OmPin == BOOT_MMCSD) {
		printf(" SDMMC\n");
	} else if (OmPin == BOOT_EMMC) {
		printf(" EMMC4.3\n");
	} else if (OmPin == BOOT_EMMC_4_4) {
		printf(" EMMC4.41\n");
	}

	return 0;
}

int dram_init(void)
{
	//gd->ram_size = get_ram_size((long *)PHYS_SDRAM_1, PHYS_SDRAM_1_SIZE);
	
	return 0;
}

void dram_init_banksize(void)
{
		nr_dram_banks = CONFIG_NR_DRAM_BANKS;
	  if(CONFIG_NR_DRAM_BANKS == 4)
	  {
  		gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
  		gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
  		gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
  		gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
  		gd->bd->bi_dram[2].start = PHYS_SDRAM_3;
  		gd->bd->bi_dram[2].size = PHYS_SDRAM_3_SIZE;
  		gd->bd->bi_dram[3].start = PHYS_SDRAM_4;
  		gd->bd->bi_dram[3].size = PHYS_SDRAM_4_SIZE;
	  }
	  else
	  {
  		gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
  		gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
  		gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
  		gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
  		gd->bd->bi_dram[2].start = PHYS_SDRAM_3;
  		gd->bd->bi_dram[2].size = PHYS_SDRAM_3_SIZE;
  		gd->bd->bi_dram[3].start = PHYS_SDRAM_4;
  		gd->bd->bi_dram[3].size = PHYS_SDRAM_4_SIZE;
  		gd->bd->bi_dram[4].start = PHYS_SDRAM_5;
  		gd->bd->bi_dram[4].size = PHYS_SDRAM_5_SIZE;
  		gd->bd->bi_dram[5].start = PHYS_SDRAM_6;
  		gd->bd->bi_dram[5].size = PHYS_SDRAM_6_SIZE;
  		gd->bd->bi_dram[6].start = PHYS_SDRAM_7;
  		gd->bd->bi_dram[6].size = PHYS_SDRAM_7_SIZE;
  		gd->bd->bi_dram[7].start = PHYS_SDRAM_8;
  		gd->bd->bi_dram[7].size = PHYS_SDRAM_8_SIZE;
  	}

#ifdef CONFIG_TRUSTZONE
	gd->bd->bi_dram[nr_dram_banks - 1].size -= CONFIG_TRUSTZONE_RESERVED_DRAM;
#endif
}

int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_SMC911X
	rc = smc911x_initialize(0, CONFIG_SMC911X_BASE);
#endif
	return rc;
}

#ifdef CONFIG_DISPLAY_BOARDINFO
int checkboard(void)
{
	printf("Board:\tSMDKV310\n");
	
	return 0;

}
#endif

void write_recovery_msg(int type)
{
};

void reboot_recovery(int type)
{
}

int board_late_init (void)
{
//#ifdef CONFIG_UPDATE_SOLUTION
//	GPIO_Init();
//	GPIO_SetFunctionEach(eGPIO_X0, eGPIO_0, 0);
//	GPIO_SetPullUpDownEach(eGPIO_X0, eGPIO_0, 0);
//
//	udelay(10);
//	if (GPIO_GetDataEach(eGPIO_X0, eGPIO_0) == EINT0_pressed || second_boot_info == 1){
//		setenv ("bootcmd", CONFIG_BOOTCOMMAND2);
//	}
//#endif
//
//#ifdef CONFIG_CPU_EXYNOS4X12
//	if(INF_REG4_REG == 0xf)
//		setenv ("bootcmd", CONFIG_BOOTCOMMAND3);
//#endif
	char cmd[128];
	unsigned char buf[512];
 	GPIO_Init();
	//读取 Logo 文件
	memset(cmd, 0xFF, 128);
	sprintf(cmd, "mmc read 0 %x %d 1", &buf, LOGO_PART_START/MOVI_BLKSIZE);
//	printf("%s\n", cmd);
	run_command(cmd, 0);
	if((buf[0]==0x00) && (buf[1]==0x02))
	{
		int read_num;
		read_num = LOGO_PIC_HEIGHT*LOGO_PIC_WIDTH*4/512 + 1;
		sprintf(cmd, "mmc read 0 %x %d %d", LOGO_BUF_ADDRESS, LOGO_PART_START/MOVI_BLKSIZE+1, read_num);
//		printf("%s\n", cmd);
		run_command(cmd, 0);
	}
#ifdef	CONFIG_AUTO_SDFUSE /* 首次通过TF卡烧写系统 */
	{
		struct mmc *mmc;
		mmc = find_mmc_device(0);
 		mmc_init(mmc);
 		if(!strcmp(mmc->name, "S5P_MSHC4"))
 		{
	 		run_command("mmc erase boot 0 0 0", 0);
			run_command("mmc erase user 0 0 0", 0);
			run_command("sdfuse flashall", 0);
   		mmc_init(mmc);
   		printf("fdisk -c 0\n");
			run_command("fdisk -c 0", 0);
 		}
		do_reset (NULL, 0, 0, NULL);
	}
#endif /* CONFIG_AUTO_SDFUSE */

	return 0;
}

int board_mmc_init(bd_t *bis)
{
#ifdef CONFIG_S3C_HSMMC
	setup_hsmmc_clock();
	setup_hsmmc_cfg_gpio();
	if (OmPin == BOOT_EMMC_4_4 || OmPin == BOOT_EMMC) {
#ifdef CONFIG_S5PC210
		smdk_s5p_mshc_init();
#endif
		smdk_s3c_hsmmc_init();
	} else {
		smdk_s3c_hsmmc_init();
#ifdef CONFIG_S5PC210
		smdk_s5p_mshc_init();
#endif
	}
#endif
	return 0;
}

#ifdef CONFIG_ENABLE_MMU
ulong virt_to_phy_s5pv310(ulong addr)
{
	if ((0xc0000000 <= addr) && (addr < 0xe0000000))
		return (addr - 0xc0000000 + 0x40000000);

	return addr;
}
#endif

