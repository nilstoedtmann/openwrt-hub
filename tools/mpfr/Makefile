#
# Copyright (C) 2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=mpfr
PKG_VERSION:=2.3.2

PKG_SOURCE_URL:=http://www.mpfr.org/mpfr-2.3.2
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_MD5SUM:=527147c097874340cb9cee0579dacf3b

include $(INCLUDE_DIR)/host-build.mk

HOST_CONFIGURE_ARGS += \
	--enable-static \
	--disable-shared \
	--with-gmp=$(STAGING_DIR_HOST)

$(eval $(call HostBuild))
