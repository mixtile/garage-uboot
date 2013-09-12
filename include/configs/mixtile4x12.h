/*
 * (C) Copyright 2009 Samsung Electronics
 * Minkyu Kang <mk7.kang@samsung.com>
 * HeungJun Kim <riverful.kim@samsung.com>
 * Inki Dae <inki.dae@samsung.com>
 *
 * Configuation settings for the SAMSUNG SMDKC100 board.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_ARMV7		1	/* This is an ARM V7 CPU core */
#define CONFIG_SAMSUNG		1	/* in a SAMSUNG core */
#define CONFIG_S5P		1	/* which is in a S5P Family */
#define CONFIG_CPU_EXYNOS4X12	1	/* which is in a Exynos4X12 */
#define CONFIG_S5PC210		1	/* which is in a S5PC210 */
#define CONFIG_S5PC220		1	/* which is in a S5PC220 */
#define CONFIG_SMDKC210		1
#define CONFIG_SMDKC220		1
#define CONFIG_EXYNOS4212	1
#define CONFIG_EXYNOS4412	1
#define CONFIG_EXYNOS4412_EVT1	1
//#define CONFIG_EXYNOS4412_EVT2	1

#define CONFIG_DEVBOARD          /* ������ */

#define BOOT_MMC  0             /*�� mmc0 ����*/
#define HSMMC0_SPEED 50000000     /* mmc0 clock����ٶ�*/
#define MMC2_SPEED 25000000     /* mmc2 clock����ٶ�*/

#define CONFIG_TRUSTZONE
#define CONFIG_TRUSTZONE_RESERVED_DRAM	0x100000
#ifdef CONFIG_TRUSTZONE
#define CONFIG_BL1_MONITOR
#define CONFIG_BOOTLOADER_MONITOR        1
#define CONFIG_PHY_IRAM_BASE            (0x02020000)
#define CONFIG_PHY_IRAM_NS_BASE         (CONFIG_PHY_IRAM_BASE + 0x2F000)
#endif

#define CONFIG_SECURE_BL1_ONLY
//#define CONFIG_SECURE_TZSW_ONLY
//#define CONFIG_SECURE_BOOT
#ifdef CONFIG_SECURE_BOOT
#define CONFIG_S5PC210S
#define CONFIG_SECURE_ROOTFS
#define CONFIG_SECURE_KERNEL_BASE	0x40008000
#define CONFIG_SECURE_KERNEL_SIZE	0x400000
#define CONFIG_SECURE_ROOTFS_BASE	0x41000000
#define CONFIG_SECURE_ROOTFS_SIZE	0x100000
#endif

//#define CONFIG_UPDATE_SOLUTION	1

//#include <asm/arch/cpu.h>		/* get chip and board defs */
#ifdef CONFIG_EXYNOS4412
  /* APLL : 800MHz */
  //#define CONFIG_CLK_ARM_800_APLL_800
  /* APLL : 1GHz */
  //#define CONFIG_CLK_ARM_1000_APLL_1000
  /* APLL : 1.1GHz */
  //#define CONFIG_CLK_ARM_1200_APLL_1100
  /* APLL : 1.2GHz */
  #define CONFIG_CLK_ARM_1200_APLL_1200
  /* APLL : 1.3GHz */
  //#define CONFIG_CLK_ARM_1200_APLL_1300
  /* APLL : 1.4GHz */
  //#define CONFIG_CLK_ARM_1200_APLL_1400
  /* APLL : 1.5GHz */
  //#define CONFIG_CLK_ARM_1500_APLL_1500
#else
  /* APLL : 1GHz */
  #define CONFIG_CLK_ARM_1000
  /* APLL : 1.5GHz */
  //#define CONFIG_CLK_ARM_1500
  /* APLL : 1.2GHz */
  //#define CONFIG_CLK_ARM_1200
  /* APLL : 8GHz */
  //#define CONFIG_CLK_ARM_800
  /* APLL : 4GHz */
  //#define CONFIG_CLK_ARM_400
  /* APLL : 2GHz */
  //#define CONFIG_CLK_ARM_200
#endif /* CONFIG_EXYNOS4412 */

#ifdef CONFIG_EXYNOS4412_EVT2
/* bus clock: 220Mhz, DMC clock 440Mhz */
#define CONFIG_CLK_BUS_DMC_220_440
#else
/* bus clock: 100Mhz, DMC clock 200Mhz */
//#define CONFIG_CLK_BUS_DMC_100_200
/* bus clock: 165Mhz, DMC clock 330Mhz */
//#define CONFIG_CLK_BUS_DMC_165_330
/* bus clock: 200Mhz, DMC clock 400Mhz */
#define CONFIG_CLK_BUS_DMC_200_400
/* bus clock: 220Mhz, DMC clock 440Mhz */
//#define CONFIG_CLK_BUS_DMC_220_440
#endif

/* IV_SIZE: 128 byte, 2 port(1 Gbyte), open page, trrd: 4 */
#define CONFIG_EVT0_PERFORMANCE
/* IV_SIZE: 512 Mbyte, 1 port(512 Mbyte), open page, trrd: 4 */
//#define CONFIG_EVT0_STABLE
/* IV_SIZE: 128 byte, 2 port(1 Gbyte), close page, trrd: 0xA */
//#define CONFIG_EVT0_RECOMMEND

/* (Memory Interleaving Size = 1 << IV_SIZE) */
#ifdef CONFIG_EVT0_STABLE
#define CONFIG_IV_SIZE 0x1D
#else
#define CONFIG_IV_SIZE 0x7
#endif

/* Notice for MSHC[Using of MMC CH4] */
/*
 * If you want MSHC at MMC CH4.
 */

#define CONFIG_L2_OFF

//#define CONFIG_ARCH_CPU_INIT

#define CONFIG_DISPLAY_CPUINFO
//#define CONFIG_DISPLAY_BOARDINFO
#define BOARD_LATE_INIT

/* input clock of PLL: SMDKV310 has 24MHz input clock */
#define CONFIG_SYS_CLK_FREQ	24000000

/* DRAM Base */
#define CONFIG_SYS_SDRAM_BASE		0x40000000

#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_CMDLINE_TAG
#define CONFIG_INITRD_TAG
#define CONFIG_CMDLINE_EDITING

/* Power Management is enabled */
#define CONFIG_PM
#ifdef CONFIG_EXYNOS4412
  #define CONFIG_PM_VDD_ARM	1.2
#else
  #define CONFIG_PM_VDD_ARM	1.1
#endif
#define CONFIG_PM_VDD_INT	1.0
#define CONFIG_PM_VDD_G3D	1.1
#define CONFIG_PM_VDD_MIF	1.1
#define CONFIG_PM_VDD_LDO14	1.8


/*
 * Size of malloc() pool
 * 1MB = 0x100000, 0x100000 = 1024 * 1024
 */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (1 << 20))
						/* initial data */
/*
 * select serial console configuration
 */
#define CONFIG_SERIAL2			1
#define CONFIG_SERIAL_MULTI		1

#define CONFIG_USB_OHCI
#undef CONFIG_USB_STORAGE
#define CONFIG_S3C_USBD
#undef CONFIG_USB_CPUMODE

#define USBD_DOWN_ADDR		0xc0000000

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_BAUDRATE			115200

/***********************************************************
 * Command definition
 ***********************************************************/
#include <config_cmd_default.h>

#define CONFIG_CMD_PING

#define CONFIG_CMD_USB

#define CONFIG_CMD_MOVINAND

#undef CONFIG_CMD_FLASH
#undef CONFIG_CMD_IMLS
#ifndef CONFIG_TRUSTZONE
//#define CONFIG_CMD_NAND
#endif

#define CONFIG_CMD_CACHE
#define CONFIG_CMD_REGINFO
#define CONFIG_CMD_MMC
#define CONFIG_CMD_MOVI
#define CONFIG_CMD_ELF
#define CONFIG_CMD_FAT
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE

#define CONFIG_CMD_I2C
#define CONFIG_I2C_CMD_TREE
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_HARD_I2C
#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_SYS_I2C_SLAVE		0xFE

#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT

#define CONFIG_SYS_NAND_QUIET_TEST
#define CONFIG_SYS_ONENAND_QUIET_TEST

#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_S3C_HSMMC
/* The macro for MMC channel 0 is defined by default and can't be undefined */

#define MMC_MAX_CHANNEL		5

#define USE_MMC2
#define USE_MMC4

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH

#define CONFIG_ETHADDR		00:40:5c:26:0a:5b
#define CONFIG_NETMASK          255.255.255.0
#define CONFIG_IPADDR		192.168.0.20
#define CONFIG_SERVERIP		192.168.0.10
#define CONFIG_GATEWAYIP	192.168.0.1

#ifdef CONFIG_DEVBOARD
  #define CONFIG_BOOTDELAY	3
#else
  #define CONFIG_BOOTDELAY	0
#endif
/* Default boot commands for Android booting. */
#ifdef CONFIG_SECURE_BOOT
#define CONFIG_BOOTCOMMAND	"emmc open 0; movi read fwbl1 0 40000000; emmc close 0; movi read kernel 0 40008000;movi read rootfs 0 41000000 100000;bootm 40008000 41000000"
#else
#define CONFIG_BOOTCOMMAND	"movi read kernel 0 40008000;movi read ramdisk 0 41000000 100000;bootm 40008000 41000000"
#endif
#define CONFIG_BOOT_RECOVERY_COMMAND	"movi read kernel 0 40008000;movi read recovery 0 41000000 100000;bootm 40008000 41000000"
#define CONFIG_BOOTARGS	""

#define CONFIG_BOOTCOMMAND2	\
		"mmc erase user 0 1072 1;"	\
		"movi r f 1 40000000;emmc open 0;movi w z f 0 40000000;emmc close 0;"	\
		"movi r u 1 40000000;emmc open 0;movi w z u 0 40000000;emmc close 0;"	\
		"movi r k 1 40000000;movi w k 0 40000000;"				\
		"movi r r 1 40000000 100000;movi w r 0 40000000 100000;"		\
		"fdisk -c 0;"								\
		"movi init 0;"								\
		"fatformat mmc 0:1;"							\
		"mmc read 1 48000000 20000 a0000;"					\
		"fastboot flash system 48000000;"					\
		"mmc read 1 48000000 c0000 a0000;"					\
		"fastboot flash userdata 48000000;"					\
		"mmc read 1 48000000 160000 a0000;"					\
		"fastboot flash cache 48000000;"					\
		"reset"

#define CONFIG_BOOTCOMMAND3	"ext3format mmc 0:3;ext3format mmc 0:4;"		\
				"movi read kernel 0 40008000;movi read rootfs 0 41000000 100000;bootm 40008000 41000000"

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_HUSH_PARSER		/* use "hush" command parser	*/
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_SYS_PROMPT		"mixtile # "
#define CONFIG_SYS_CBSIZE	256	/* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE	384	/* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16	/* max number of command args */
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
/* memtest works on */
#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_SDRAM_BASE + 0x5e00000)

#define CONFIG_SYS_HZ			1000

/* valid baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE	(256 << 10)	/* 256 KiB */


#ifdef CONFIG_EVT0_STABLE
#define CONFIG_NR_DRAM_BANKS	2
#else
//#define CONFIG_NR_DRAM_BANKS	8
#define CONFIG_NR_DRAM_BANKS	4
#endif
#define SDRAM_BANK_SIZE         0x10000000    /* 256 MB */
#define PHYS_SDRAM_1            CONFIG_SYS_SDRAM_BASE /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE       SDRAM_BANK_SIZE
#define PHYS_SDRAM_2            (CONFIG_SYS_SDRAM_BASE + SDRAM_BANK_SIZE) /* SDRAM Bank #2 */
#define PHYS_SDRAM_2_SIZE       SDRAM_BANK_SIZE
#define PHYS_SDRAM_3            (CONFIG_SYS_SDRAM_BASE + 2 * SDRAM_BANK_SIZE) /* SDRAM Bank #3 */
#define PHYS_SDRAM_3_SIZE       SDRAM_BANK_SIZE
#define PHYS_SDRAM_4            (CONFIG_SYS_SDRAM_BASE + 3 * SDRAM_BANK_SIZE) /* SDRAM Bank #4 */
#define PHYS_SDRAM_4_SIZE       SDRAM_BANK_SIZE
#define PHYS_SDRAM_5            (CONFIG_SYS_SDRAM_BASE + 4 * SDRAM_BANK_SIZE) /* SDRAM Bank #5 */
#define PHYS_SDRAM_5_SIZE       SDRAM_BANK_SIZE
#define PHYS_SDRAM_6            (CONFIG_SYS_SDRAM_BASE + 5 * SDRAM_BANK_SIZE) /* SDRAM Bank #6 */
#define PHYS_SDRAM_6_SIZE       SDRAM_BANK_SIZE
#define PHYS_SDRAM_7            (CONFIG_SYS_SDRAM_BASE + 6 * SDRAM_BANK_SIZE) /* SDRAM Bank #7 */
#define PHYS_SDRAM_7_SIZE       SDRAM_BANK_SIZE
#define PHYS_SDRAM_8            (CONFIG_SYS_SDRAM_BASE + 7 * SDRAM_BANK_SIZE) /* SDRAM Bank #8 */
#define PHYS_SDRAM_8_SIZE       SDRAM_BANK_SIZE

#define CONFIG_SYS_MONITOR_BASE	0x00000000

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CONFIG_SYS_NO_FLASH		1

#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* 256 KiB */
#define CONFIG_IDENT_STRING		" for 4X12 by Mixtile"

//#define CONFIG_ENABLE_MMU

#ifdef CONFIG_ENABLE_MMU
#define CONFIG_SYS_MAPPED_RAM_BASE	0xc0000000
#define virt_to_phys(x)	virt_to_phy_s5pv310(x)
#else
#define CONFIG_SYS_MAPPED_RAM_BASE	CONFIG_SYS_SDRAM_BASE
#define virt_to_phys(x)	(x)
#endif

//#define CONFIG_SYS_LOAD_ADDR		CONFIG_SYS_MAPPED_RAM_BASE + 0x3e00000
//#define CONFIG_PHY_UBOOT_BASE		CONFIG_SYS_SDRAM_BASE + 0x3e00000
#define CONFIG_PHY_UBOOT_BASE		CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_LOAD_ADDR		CONFIG_PHY_UBOOT_BASE

/*
 *  Fast Boot
*/
#define CONFIG_FASTBOOT_SDFUSE
/* Fastboot variables */
#define CFG_FASTBOOT_TRANSFER_BUFFER            (0x48000000)
#define CFG_FASTBOOT_TRANSFER_BUFFER_SIZE       (0x30000000)   /* 768 MB */
#define CFG_FASTBOOT_ADDR_KERNEL                (0x40008000)
#define CFG_FASTBOOT_ADDR_RAMDISK               (0x40800000)
#define CFG_FASTBOOT_PAGESIZE                   (2048)  // Page size of booting device
#define CFG_FASTBOOT_SDMMC_BLOCKSIZE            (512)   // Block size of sdmmc
#define CFG_PARTITION_START			(0x4000000)

/* Just one BSP type should be defined. */
#if defined(CONFIG_CMD_ONENAND) | defined(CONFIG_CMD_NAND) | defined(CONFIG_CMD_MOVINAND)
#define CONFIG_FASTBOOT
#endif

#if defined(CONFIG_CMD_NAND)
#define CFG_FASTBOOT_NANDBSP
#endif
#if defined(CONFIG_CMD_ONENAND)
#define CFG_FASTBOOT_ONENANDBSP
#endif
#if defined(CONFIG_CMD_MOVINAND)
#define CFG_FASTBOOT_SDMMCBSP
#endif

/*
 * machine type
 */

#ifdef CONFIG_EXYNOS4412
  #define MACH_TYPE_C220		3765	/* SMDKC210 machine ID */
#else
  #define MACH_TYPE_C220		3698	/* SMDKC210 machine ID */
#endif

#define CONFIG_ENV_OFFSET		0x0007C000

/*-----------------------------------------------------------------------
 * Boot configuration
 */
#define CONFIG_FASTBOOT

#define BOOT_ONENAND		0x1
#define BOOT_NAND		0x40000
#define BOOT_MMCSD		0x3
#define BOOT_NOR		0x4
#define BOOT_SEC_DEV		0x5
#define BOOT_EMMC		0x6
#define BOOT_EMMC_4_4		0x7
#define BOOT_USB		0x8

/* Boot device */
#define SDMMC_CH2		0x0
#define SDMMC_CH0		0x4
#define EMMC			0x10
#define EMMC_4_4		0x14
#define USB			0x40

/* nand copy size from nand to DRAM.*/
#define	COPY_BL2_SIZE		0x80000
#define CONFIG_SYS_MAX_NAND_DEVICE     1
#define CFG_NAND_SKIP_BAD_DOT_I	1  /* ".i" read skips bad blocks   */
#define	CFG_NAND_WP		1
#define CFG_NAND_YAFFS_WRITE	1  /* support yaffs write */
#define CFG_NAND_HWECC
#define CONFIG_NAND_BL1_16BIT_ECC
#undef	CFG_NAND_FLASH_BBT

#define CONFIG_SYS_NAND_BASE           (0x0CE00000)
#define NAND_MAX_CHIPS          1

#define NAND_DISABLE_CE()	(NFCONT_REG |= (1 << 1))
#define NAND_ENABLE_CE()	(NFCONT_REG &= ~(1 << 1))
#define NF_TRANSRnB()		do { while(!(NFSTAT_REG & (1 << 0))); } while(0)

#define CFG_NAND_SKIP_BAD_DOT_I	1  /* ".i" read skips bad blocks   */
#define	CFG_NAND_WP		1
#define CFG_NAND_YAFFS_WRITE	1  /* support yaffs write */

#define CFG_NAND_HWECC
#define CONFIG_NAND_BL1_16BIT_ECC
#undef	CFG_NAND_FLASH_BBT

#define CONFIG_ZIMAGE_BOOT

#define CONFIG_ENV_IS_NOWHERE		1
//#define CONFIG_ENV_IS_IN_AUTO		1
#define CONFIG_ENV_SIZE			0x4000

#define CONFIG_DOS_PARTITION		1

//#define CONFIG_SYS_INIT_SP_ADDR	(CONFIG_SYS_LOAD_ADDR - 0x1000000)
//#define CONFIG_SYS_INIT_SP_ADDR	(0x43e00000 - 0x1000000)
#define CONFIG_SYS_INIT_SP_ADDR	(CONFIG_PHY_UBOOT_BASE - 0x1000000)

/*
 * Ethernet Contoller driver
 */
#undef CONFIG_CMD_NFS
#undef CONFIG_CMD_NET

#ifdef CONFIG_CMD_NET
#define CONFIG_NET_MULTI
#define CONFIG_SMC911X
#define CONFIG_SMC911X_BASE	0x5000000
#define CONFIG_SMC911X_16_BIT
#endif /* CONFIG_CMD_NET */

/* GPIO */
#define GPIO_BASE	0x11000000

#define CONFIG_SAMSUNG_ONENAND		1

#if defined(CONFIG_CMD_ONENAND)
  #define CONFIG_C210_ONENAND
#endif

#define CFG_ONENAND_BASE 	(0x0C000000)
#define CFG_ONENANDXL_BASE 	(0x0C600000)
#define CONFIG_SYS_ONENAND_BASE	CFG_ONENAND_BASE
#define CONFIG_SYS_MAX_ONENAND_DEVICE     1

#define CONFIG_BOOT_ONENAND_IROM
#define CONFIG_NAND
#define CONFIG_BOOT_NAND

//#define CFG_PHY_UBOOT_BASE	MEMORY_BASE_ADDRESS + 0x3e00000
#define CFG_PHY_UBOOT_BASE	CONFIG_PHY_UBOOT_BASE
#define CFG_PHY_KERNEL_BASE	MEMORY_BASE_ADDRESS + 0x8000

#define MEMORY_BASE_ADDRESS	0x40000000

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 
  ������Ϣ��
  ����        ��С      ��ַ�ռ�                  ��ռ� 
  bootloader  (3M)      0x00000000 ~ 0x002FFFFF    0     ~ 6143 (6144)(����RESERVE BL1 uboot������)
  kernel      (5M)      0x00300000 ~ 0x005FFFFF    6144  ~ 16383(10240)
  ramdisk     (5M)      0x00800000 ~ 0x00CFFFFF    16384 ~ 26623(10240)
  logo        (25M)     0x00D00000 ~ 0x025FFFFF    26624 ~ 77823(51200)
  recovery    (12M)     0x02600000 ~ 0x031FFFFF    77824 ~ 102399(24576)

  system      (500M)    0x03200000 ~ 0x225FFFFF    102400  ~ 1126399(819200)
  cache       (150M)    0x22600000 ~ 0x2BBFFFFF    1126400 ~ 1433599(307200)
  userdata    (1024M)   0x2BC00000 ~ END

  extern_sd   (ALL)     0x80000000 ~ END           3121152 ~
*/

#define MOVI_BLKSIZE          CFG_FASTBOOT_SDMMC_BLOCKSIZE

#define RESERVE_SIZE          0
#define SAMSUNG_BL_SIZE       (31 * 1024)

#define UBOOT_PART_START      RESERVE_SIZE
#define UBOOT_PART_SIZE       (0x00300000-RESERVE_SIZE)
#define UBOOT_USED_BLK        (0x100000/MOVI_BLKSIZE)
#define UBOOT_PART_FILE       "bootloader.bin"
#define UBOOT_READ_SIZE       (0x80000)

#define KERNEL_PART_START     (UBOOT_PART_START + UBOOT_PART_SIZE)
#define KERNEL_PART_SIZE      (0x00500000)
#define KERNEL_USED_BLK       (KERNEL_PART_SIZE/MOVI_BLKSIZE)
#define KERNEL_PART_FILE       "zImage"

#define RAMDISK_PART_START    (UBOOT_PART_START + UBOOT_PART_SIZE + KERNEL_PART_SIZE)
#define RAMDISK_PART_SIZE     (0x00500000)
#define RAMDISK_USED_BLK      (RAMDISK_PART_SIZE/MOVI_BLKSIZE)
#define RAMDISK_PART_FILE     "ramdisk-uboot.img"
#define RAMDISK_READ_SIZE     (0x400000)    //����ʱ��ȡ�ĳ��ȣ��Ż�����ʱ�䣬����ramdisk�ļ���С������

#define LOGO_PART_START       (UBOOT_PART_START + UBOOT_PART_SIZE + KERNEL_PART_SIZE + RAMDISK_PART_SIZE)
#define LOGO_PART_SIZE        (0x01900000)
#define LOGO_USED_BLK         (0x01900000/MOVI_BLKSIZE)
#define LOGO_PART_FILE        "logo.bin"

#define RECOVERY_PART_START   (UBOOT_PART_START + UBOOT_PART_SIZE + KERNEL_PART_SIZE + RAMDISK_PART_SIZE + LOGO_PART_SIZE)
#define RECOVERY_PART_SIZE    (0x00C00000)
#define RECOVERY_USED_BLK     (RECOVERY_PART_SIZE/MOVI_BLKSIZE)
#define RECOVERY_PART_FILE    "ramdisk-recovery-uboot.img"
#define SYSTEM_PART_FILE      "system.img"

#define OTA_UPDATE_FILE				"update.zip"
/* pic location */
#define PIC_BOOT              LOGO_PART_START           //����logo
#define PIC_UPDATE            (PIC_BOOT + 0x280000)     //��������

#define BOOT_PART_SIZE        (RESERVE_SIZE + UBOOT_PART_SIZE + KERNEL_PART_SIZE + RAMDISK_PART_SIZE + LOGO_PART_SIZE + RECOVERY_PART_SIZE)

#define SYSTEM_PART_SIZE      (0x1F400000)
#define SYSTEM_PART_NUM       1
#define CACHE_PART_SIZE       (0x09600000)
#define CACHE_PART_NUM        2
#ifdef ENABLE_TRUE_SD
  #define USER_DATA_PART_SIZE   (0x40000000)
#else
  #define USER_DATA_PART_SIZE   (0)
#endif
#define USERDATA_PART_NUM     3
#define EXTSD_PART_NUM        4

#ifndef CONFIG_DEVBOARD
#define CONFIG_ZERO_BOOTDELAY_CHECK
#endif

#define CHECK_KEY_TIME				100  //10*100ms = 1S

//recovery
#define RECOVERY_MSG_BLK			((SAMSUNG_BL_SIZE/512 +1)-4)
#define RECOVERY_MSG_LEN      3

//logo
#define LOGO_BUF_ADDRESS			0x50000000
#define LOGO_PIC_WIDTH				1024
#define LOGO_PIC_HEIGHT				768

#endif	/* __CONFIG_H */
