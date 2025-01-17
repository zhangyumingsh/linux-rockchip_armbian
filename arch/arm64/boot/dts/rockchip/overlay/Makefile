# SPDX-License-Identifier: GPL-2.0
dtbo-$(CONFIG_ARCH_ROCKCHIP) += \
	rk3588-dsi.dtbo       \
	rk3588-mcp2515.dtbo   \
	rk3588-spi0.dtbo      \
	rk3588-tft_35.dtbo    \
	rk3588-hdmi.dtbo      \
	rk3588-i2c1-m0.dtbo   \
	rk3588-i2c1-m2.dtbo   \
	rk3588-i2c2-m4.dtbo   \
	rk3588-i2c3-m2.dtbo   \
	rk3588-i2c5-m2.dtbo   \
	rk3588-i2c6-m0.dtbo   \
	rk3588-i2c7-m3.dtbo   \
	rk3588-spi0-m2.dtbo   \
	rk3588-spi2-m1.dtbo	  \
	rk3588-spi3-m2.dtbo   \
	rk3588-spi4-m2.dtbo   \
	rk3588-pwm0-m2.dtbo   \
	rk3588-pwm12-m1.dtbo  \
	rk3588-pwm14-m1.dtbo  \
	rk3588-pwm2-m0.dtbo   \
	rk3588-pwm6-m0.dtbo   \
	rk3588-uart0-m2.dtbo  \
	rk3588-uart2-m0.dtbo  \
	rk3588-uart3-m2.dtbo  \
	rk3588-uart4-m2.dtbo  \
	rk3588-uart6-m1.dtbo  \
	rk3588-uart9-m1.dtbo  
	
	
scr-$(CONFIG_ARCH_ROCKCHIP) += \
	rk3588-fixup.scr

dtbotxt-$(CONFIG_ARCH_ROCKCHIP) += \
	README.rockchip-overlays

targets += $(dtbo-y) $(scr-y) $(dtbotxt-y)

always-y       := $(dtbo-y) $(scr-y) $(dtbotxt-y)
clean-files    := *.dtbo *.scr
