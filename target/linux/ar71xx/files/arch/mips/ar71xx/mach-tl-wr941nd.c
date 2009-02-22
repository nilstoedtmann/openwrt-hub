/*
 *  TP-LINK TL-WR941ND board support
 *
 *  Copyright (C) 2009 Gabor Juhos <juhosg@openwrt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/platform_device.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/spi/spi.h>
#include <linux/spi/flash.h>
#include <linux/input.h>

#include <asm/mips_machine.h>

#include <asm/mach-ar71xx/ar71xx.h>
#include <asm/mach-ar71xx/platform.h>

#define TL_WR941ND_GPIO_LED_SYSTEM	2
#define TL_WR941ND_GPIO_LED_QSS		5

#define TL_WR941ND_GPIO_BTN_RESET	3
#define TL_WR941ND_GPIO_BTN_QSS		7

#define TL_WR941ND_BUTTONS_POLL_INTERVAL	20

#ifdef CONFIG_MTD_PARTITIONS
static struct mtd_partition tl_wr941nd_partitions[] = {
	{
		.name		= "u-boot",
		.offset		= 0,
		.size		= 0x020000,
		.mask_flags	= MTD_WRITEABLE,
	} , {
		.name		= "kernel",
		.offset		= 0x020000,
		.size		= 0x100000,
	} , {
		.name		= "rootfs",
		.offset		= 0x120000,
		.size		= 0x2c0000,
	} , {
		.name		= "config",
		.offset		= 0x3e0000,
		.size		= 0x010000,
	} , {
		.name		= "art",
		.offset		= 0x3f0000,
		.size		= 0x010000,
		.mask_flags	= MTD_WRITEABLE,
	} , {
		.name		= "firmware",
		.offset		= 0x020000,
		.size		= 0x3c0000,
	}
};
#endif /* CONFIG_MTD_PARTITIONS */

static struct flash_platform_data tl_wr941nd_flash_data = {
#ifdef CONFIG_MTD_PARTITIONS
        .parts          = tl_wr941nd_partitions,
        .nr_parts       = ARRAY_SIZE(tl_wr941nd_partitions),
#endif
};

static struct spi_board_info tl_wr941nd_spi_info[] = {
	{
		.bus_num	= 0,
		.chip_select	= 0,
		.max_speed_hz	= 25000000,
		.modalias	= "m25p80",
		.platform_data  = &tl_wr941nd_flash_data,
	}
};

static struct gpio_led tl_wr941nd_leds_gpio[] __initdata = {
	{
		.name		= "tl-wr941nd:green:system",
		.gpio		= TL_WR941ND_GPIO_LED_SYSTEM,
		.active_low	= 1,
	}, {
		.name		= "tl-wr941nd:red:qss",
		.gpio		= TL_WR941ND_GPIO_LED_QSS,
		.active_low	= 1,
	}
};

static struct gpio_button tl_wr941nd_gpio_buttons[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= BTN_0,
		.threshold	= 5,
		.gpio		= TL_WR941ND_GPIO_BTN_RESET,
		.active_low	= 1,
	}, {
		.desc		= "qss",
		.type		= EV_KEY,
		.code		= BTN_1,
		.threshold	= 5,
		.gpio		= TL_WR941ND_GPIO_BTN_QSS,
		.active_low	= 1,
	}
};

static void __init tl_wr941nd_setup(void)
{
	ar71xx_add_device_spi(NULL, tl_wr941nd_spi_info,
					ARRAY_SIZE(tl_wr941nd_spi_info));

	ar71xx_add_device_leds_gpio(-1, ARRAY_SIZE(tl_wr941nd_leds_gpio),
					tl_wr941nd_leds_gpio);

	ar71xx_add_device_gpio_buttons(-1, TL_WR941ND_BUTTONS_POLL_INTERVAL,
					ARRAY_SIZE(tl_wr941nd_gpio_buttons),
					tl_wr941nd_gpio_buttons);
	ar91xx_add_device_wmac();
}

MIPS_MACHINE(AR71XX_MACH_MZK_W04NU, "TP-LINK TL-WR941ND", tl_wr941nd_setup);