// SPDX-License-Identifier: GPL-2.0+
/*
 * FB driver for the ILI9341 LCD display controller
 *
 * This display uses 9-bit SPI: Data/Command bit + 8 data bits
 * For platforms that doesn't support 9-bit, the driver is capable
 * of emulating this using 8-bit transfer.
 * This is done by transferring eight 9-bit words in 9 bytes.
 *
 * Copyright (C) 2013 Christian Vogelgsang
 * Based on adafruit22fb.c by Noralf Tronnes
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <video/mipi_display.h>

#include "fbtft.h"

//#define TXBUFLEN (8 * PAGE_SIZE)

#define DRVNAME	"fb_nv4301"
#define WIDTH		480
#define HEIGHT		272

static int init_display(struct fbtft_par *par)
{
    par->fbtftops.reset(par);

    /* startup sequence for MI0283QT-9A */
    write_reg(par, MIPI_DCS_SOFT_RESET);
    mdelay(10);
    write_reg(par, MIPI_DCS_SET_DISPLAY_OFF);
	
	gpiod_set_value_cansleep(par->gpio.dc, 1);
	mdelay(20);
	gpiod_set_value_cansleep(par->gpio.dc, 0);
	msleep(200);
	gpiod_set_value_cansleep(par->gpio.dc, 1);
	mdelay(120);
	
	write_reg(par, 0xff ,0xa5 );
	write_reg(par, 0xE7 ,0x10 );
	write_reg(par, 0x35 ,0x01 );
	write_reg(par, 0x3A ,0x01 );
	write_reg(par, 0x40 ,0x01 );
	write_reg(par, 0x41 ,0x03 );
	write_reg(par, 0x55 ,0x01 );
	write_reg(par, 0x44 ,0x15 );
	write_reg(par, 0x45 ,0x15 );
	write_reg(par, 0x7d ,0x03 );

	write_reg(par, 0xc1 ,0xa0 );
	write_reg(par, 0xc2 ,0x14 );
	write_reg(par, 0xc3 ,0x10 );
	
	write_reg(par, 0xc6 ,0x3a );
	write_reg(par, 0xc7 ,0x25 );
	write_reg(par, 0xc8 ,0x11 );
	
	write_reg(par, 0x7a ,0x79 );
	write_reg(par, 0x6f ,0x5f );//0x1f
	write_reg(par, 0x78 ,0x4b );
	
	write_reg(par, 0x73 ,0x08 );
	write_reg(par, 0x74 ,0x12 );
	
	write_reg(par, 0xc9 ,0x00 );
	write_reg(par, 0x67 ,0x11 );
	write_reg(par, 0x51 ,0x20 );
	write_reg(par, 0x52 ,0x7c );
	write_reg(par, 0x53 ,0x1c );
	write_reg(par, 0x54 ,0x77 );
	write_reg(par, 0x46 ,0x0a );
	write_reg(par, 0x47 ,0x2a );
	write_reg(par, 0x48 ,0x0a );
	write_reg(par, 0x49 ,0x1a );
	write_reg(par, 0x56 ,0x43 );
	write_reg(par, 0x57 ,0x42 );
	write_reg(par, 0x58 ,0x3c );
	write_reg(par, 0x59 ,0x64 );
	write_reg(par, 0x5a ,0x41 );
	write_reg(par, 0x5b ,0x3c );
	write_reg(par, 0x5c ,0x02 );
	write_reg(par, 0x5d ,0x3c );
	write_reg(par, 0x5e ,0x1f );
	write_reg(par, 0x60 ,0x80 );
	write_reg(par, 0x61 ,0x3f );
	write_reg(par, 0x62 ,0x21 );
	write_reg(par, 0x63 ,0x07 );
	write_reg(par, 0x64 ,0xe0 );
	write_reg(par, 0x65 ,0x01 );
	write_reg(par, 0xca ,0x20 );
	write_reg(par, 0xcb ,0x52 );
	write_reg(par, 0xcc ,0x10 );
	write_reg(par, 0xcD ,0x42 );
	write_reg(par, 0xD0 ,0x20 );
	write_reg(par, 0xD1 ,0x52 );
	write_reg(par, 0xD2 ,0x10 );
	write_reg(par, 0xD3 ,0x42 );
	write_reg(par, 0xD4 ,0x0a );
	write_reg(par, 0xD5 ,0x32 );
	write_reg(par, 0xe5 ,0x06 );
	write_reg(par, 0xe6 ,0x00 );
	write_reg(par, 0x6e ,0x14 );
	write_reg(par, 0x80 ,0x04 );
	write_reg(par, 0xA0 ,0x00 );
	write_reg(par, 0x81 ,0x07 );
	write_reg(par, 0xA1 ,0x05 );
	write_reg(par, 0x82 ,0x06 );
	write_reg(par, 0xA2 ,0x04 );
	write_reg(par, 0x83 ,0x39 );
	write_reg(par, 0xA3 ,0x39 );
	write_reg(par, 0x84 ,0x3a );
	write_reg(par, 0xA4 ,0x3a );
	write_reg(par, 0x85 ,0x3f );
	write_reg(par, 0xA5 ,0x3f );
	write_reg(par, 0x86 ,0x2c );
	write_reg(par, 0xA6 ,0x2a );
	write_reg(par, 0x87 ,0x43 );
	write_reg(par, 0xA7 ,0x47 );
	write_reg(par, 0x88 ,0x08 );
	write_reg(par, 0xA8 ,0x08 );
	write_reg(par, 0x89 ,0x0f );
	write_reg(par, 0xA9 ,0x0f );
	write_reg(par, 0x8a ,0x17 );
	write_reg(par, 0xAa ,0x17 );
	write_reg(par, 0x8b ,0x10 );
	write_reg(par, 0xAb ,0x10 );
	write_reg(par, 0x8c ,0x16 );
	write_reg(par, 0xAc ,0x16 );
	write_reg(par, 0x8d ,0x14 );
	write_reg(par, 0xAd ,0x14 );
	write_reg(par, 0x8e ,0x11 );
	write_reg(par, 0xAe ,0x11 );
	write_reg(par, 0x8f ,0x14 );
	write_reg(par, 0xAf ,0x14 );
	write_reg(par, 0x90 ,0x06 );
	write_reg(par, 0xB0 ,0x06 );
	write_reg(par, 0x91 ,0x0f );
	write_reg(par, 0xB1 ,0x0f );
	write_reg(par, 0x92 ,0x16 );
	write_reg(par, 0xB2 ,0x16 );
	write_reg(par, 0xff ,0x00 );
	write_reg(par, 0x11 );
	mdelay(120);	
	write_reg(par, 0x29 );
	mdelay(10);	

    return 0;
}

static void set_addr_win(struct fbtft_par *par, int xs, int ys, int xe, int ye)
{
   write_reg(par, 0x2a, (xs >> 8) & 0xFF, xs & 0xFF, (xe >> 8) & 0xFF, xe & 0xFF);
   write_reg(par, 0x2b, (ys >> 8) & 0xFF, ys & 0xFF, (ye >> 8) & 0xFF, ye & 0xFF);

   write_reg(par, 0x2c);

}

static int set_var(struct fbtft_par *par)
{
  switch (par->info->var.rotate) {
	case 270:
		//write_reg(par, 0x36, 0xa0 ); //rgb
		write_reg(par, 0x36, 0x60 ); //rgb
		break;
	case 180:
		//write_reg(par, 0x36, 0x0  ); //rgb
		write_reg(par, 0x36, 0xC0 ); //rgb
		break;
	case 90:
		//write_reg(par, 0x36, 0x60 ); //rgb
		write_reg(par, 0x36, 0xa0 ); //rgb
		break;
	default:
		//write_reg(par, 0x36, 0xC0 ); //rgb
		write_reg(par, 0x36, 0x0  ); //rgb
		break;
	}


    return 0;
}

static struct fbtft_display display = {
    .regwidth = 8,
    .width = WIDTH,
    .height = HEIGHT,
//    .txbuflen = TXBUFLEN,
    .gamma_num = 2,
    .gamma_len = 14,
    .fbtftops = {
        .init_display = init_display,
        .set_addr_win = set_addr_win,
        .set_var = set_var,
    },
};


FBTFT_REGISTER_DRIVER(DRVNAME, "NV3041A", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:hd43017");
MODULE_ALIAS("platform:hd43017");

MODULE_DESCRIPTION("HD43017 LCD driver");
MODULE_AUTHOR("BTT <zhangym@biqu3d.com>");
MODULE_LICENSE("GPL v2");
