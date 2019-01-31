/*
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * This file contains the configuration parameters
 * for Qualcomm Atheros AR934x based devices
 *
 * Reference designs: AP123, MI124, DB120
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _DB12X_H
#define _DB12X_H

#include <config.h>
#include <configs/qca9k_common.h>
#include <soc/soc_common.h>

/*
 * ==================
 * GPIO configuration
 * ==================
 */
#if defined(CONFIG_FOR_NEC_AR934X)

	#define CONFIG_QCA_GPIO_MASK_IN		GPIO16
	#define CONFIG_QCA_GPIO_MASK_OUT_INIT_H	GPIO13

#endif

/*
 * ================
 * Default bootargs
 * ================
 */
#if defined(CONFIG_FOR_NEC_AR934X)

	/* nothing */

#else

	#define CONFIG_BOOTARGS	"console=ttyS0,115200 root=31:02 "\
				"rootfstype=squashfs init=/sbin/init "\
				"mtdparts=ath-nor0:128k(u-boot),1024k(kernel),2816k(rootfs),64k(config),64k(art)"

#endif

/*
 * =============================
 * Load address and boot command
 * =============================
 */
#if defined(CONFIG_FOR_NEC_AR934X)

	#define CFG_LOAD_ADDR		0x9F040000

#else

	#define CFG_LOAD_ADDR		0x9F020000

#endif

#define CONFIG_BOOTCOMMAND	"bootm " MK_STR(CFG_LOAD_ADDR)

/*
 * =========================
 * Environment configuration
 * =========================
 */
#define CFG_ENV_ADDR		0x9F01EC00
#define CFG_ENV_SIZE		0x1000
#define CFG_ENV_SECT_SIZE	0x10000

/*
 * ===========================
 * List of available baudrates
 * ===========================
 */
#define CFG_BAUDRATE_TABLE	\
		{ 600,    1200,   2400,    4800,    9600,    14400, \
		  19200,  28800,  38400,   56000,   57600,   115200 }

/*
 * ==================================================
 * MAC address/es, model and WPS pin offsets in FLASH
 * ==================================================
 */
#if defined(CONFIG_FOR_NEC_AR934X)

	#define OFFSET_MAC_DATA_BLOCK		0x020000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS		0x000006

#else

	#define OFFSET_MAC_DATA_BLOCK		0x010000
	#define OFFSET_MAC_DATA_BLOCK_LENGTH	0x010000
	#define OFFSET_MAC_ADDRESS		0x00FC00
	#define OFFSET_ROUTER_MODEL		0x00FD00
	#define OFFSET_PIN_NUMBER		0x00FE00

#endif

/*
 * =========================
 * Custom changes per device
 * =========================
 */

/*
 * - NEC Aterm WR8750N uses 9600bps as the
 *   baudrate in the stock bootloader/firmware
 * - all LEDs are connected to ath9k chip
 * - there is no u-boot-env partition
 * - OEM bootloader uses 192.168.0.1 as the
 * 	device ip
 */
#if defined(CONFIG_FOR_NEC_AR934X)

	#undef CONFIG_BAUDRATE
	#define CONFIG_BAUDRATE	9600
	#undef CONFIG_IPADDR
	#undef CONFIG_SERVERIP
	#define CONFIG_IPADDR	192.168.0.1
	#define CONFIG_SERVERIP	192.168.0.2
	#undef CONFIG_NETCONSOLE
	#undef CONFIG_NETCONSOLE_PORT
	#undef CFG_ENV_IS_IN_FLASH
	#define CFG_ENV_IS_NOWHERE
	#undef CONFIG_CMD_DHCP
	#undef CONFIG_CMD_HTTPD
	#undef CONFIG_CMD_LED
	#undef CONFIG_CMD_MAC
	#undef CONFIG_UPG_SCRIPTS_FW
	#undef CONFIG_UPG_SCRIPTS_UBOOT
	#undef CONFIG_BTN_RECOVERY_SCRIPT

#endif

/*
 * ===========================
 * HTTP recovery configuration
 * ===========================
 */
#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS	CFG_LOAD_ADDR

/* Firmware size limit */
#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(192 * 1024)

/*
 * ========================
 * PLL/Clocks configuration
 * ========================
 */
#define CONFIG_QCA_PLL	QCA_PLL_PRESET_550_400_200

/*
 * ==================================
 * For upgrade scripts in environment
 * ==================================
 */
#define CONFIG_UPG_UBOOT_SIZE_BACKUP_HEX	0x20000

/*
 * ===================
 * Other configuration
 * ===================
 */

/* Cache lock for stack */
#define CONFIG_INIT_SRAM_SP_OFFSET	0xbd007000

#endif /* _DB12X_H */
