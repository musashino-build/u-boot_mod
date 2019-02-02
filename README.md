U-Boot 1.1.4 modification for NEC routers
==========

Compiled snapshot/test images
--------------------------
WIP

Table of contents
-----------------

- [Introduction](#introduction)
- [Supported devices](#supported-devices)
- [Known issues](#known-issues)
- [Modifications, changes](#modifications-changes)
	- [Other](#other)
	- [Supported FLASH chips](#supported-flash-chips)
- [How to install it?](#how-to-install-it)
	- [Cautions, backups](#cautions-backups)
	- [Using OpenWrt](#using-openwrt)
- [How to use it?](#how-to-use-it)
- [How to compile the code?](#how-to-compile-the-code)
    - [Building on Linux](#building-on-linux)
    - [Building on OS X](#building-on-macos-os-x)
- [License, outdated sources etc.](#license-outdated-sources-etc)
- [Credits](#credits)

Introduction
------------

This repository is a fork of pepe2k/u-boot_mod for NEC Aterm series routers.

Supported devices
-----------------

Currently supported devices:

- **Atheros AR9344**:
  - NEC Aterm WR8750N
  - NEC Aterm WR9500N
  - NEC Aterm WG600HP

I tested this modification on Aterm WR8750N, with OpenWrt firmware. If you are not sure about the version of your device, please contact with me **before** you try to make an upgrade. Changing bootloader to a wrong version will probably damage your router and you will need special hardware to fix it, so please, **be very careful**.

More information about supported devices:

| Model | SoC | FLASH | RAM | U-Boot image | U-Boot env |
|:--- | :--- | ---: | ---: | ---: | ---: |
| NEC Aterm WR8750N | AR9344 | 8 MiB | 128 MiB DDR2 | 128 KiB | (None) |
| NEC Aterm WR9500N | AR9344 | 16 MiB | 128 MiB DDR2 | 128 KiB | (None) |
| NEC Aterm WG600HP | AR9344 | 8 MiB | 128 MiB DDR2 | 128 KiB | (None) |

*(LZMA) - U-Boot binary image is compressed with LZMA.*
*(R/W) - environment exists in separate FLASH block which allows you to save it and keep after power down.*
*(RO) - environment is read only, you can change and add new variables only during runtime.*

Known issues
------------

(unknown)

Modifications, changes
----------------------

### Other

Moreover:

- Faster boot up
- Unnecessary information from boot up sequence were removed
- FLASH chip is automatically recognized (using JEDEC ID)
- Ethernet MAC is set from FLASH (no more "No valid address in FLASH. Using fixed address")
- Automatic kernel booting can be interrupted using any key
- Better UART serial console driver with support for different baud rates

### Supported FLASH chips

FLASH type detection may be very useful for people who has exchanged the FLASH chip in their routers. You will not need to recompile U-Boot sources, to have access to overall FLASH space in U-Boot console.

If you use FLASH type which is not listed below, this version of U-Boot will try to get information about the chip using **Serial Flash Discoverable Parameter** (**SFDP**, more information: https://www.jedec.org/standards-documents/docs/jesd216b) standard. If your chip does not support SFDP, it will use default size for your router and, in most supported models, updating the ART image will not be available.

Currently supported FLASH types:

**4 MiB**:

- Spansion S25FL032P (4 MiB, JEDEC ID: 01 0215)
- Atmel AT25DF321 (4 MiB, JEDEC ID: 1F 4700)
- EON EN25Q32 (4 MiB, JEDEC ID: 1C 3016)
- EON EN25F32 (4 MiB, JEDEC ID: 1C 3116)
- Micron M25P32 (4 MiB, JEDEC ID: 20 2016)
- Windbond W25Q32 (4 MiB, JEDEC ID: EF 4016)
- Macronix MX25L320 (4 MiB, JEDEC ID: C2 2016)
- GigaDevice GD25Q32 (4 MiB, JEDEC ID: C8 4016)

**8 MiB**:

- Spansion S25FL064P (8 MiB, JEDEC ID: 01 0216)
- Atmel AT25DF641 (8 MiB, JEDEC ID: 1F 4800)
- EON EN25Q64 (8 MiB, JEDEC ID: 1C 3017)
- Micron M25P64 (8 MiB, JEDEC ID: 20 2017)
- Windbond W25Q64 (8 MiB, JEDEC ID: EF 4017)
- Macronix MX25L64 (8 MiB, JEDEC ID: C2 2017, C2 2617)
- GigaDevice GD25Q64 (8 MiB, JEDEC ID: C8 4017)

**16 MiB**:

- Winbond W25Q128 (16 MB, JEDEC ID: EF 4018)
- Winbond W25Q128FW (16 MB, JEDEC ID: EF 6018, 1,8 V)
- Macronix MX25L128 (16 MB, JEDEC ID: C2 2018, C2 2618)
- Spansion S25FL127S (16 MB, JEDEC ID: 01 2018)
- Micron N25Q128 (16 MB, JEDEC ID: 20 BA18)
- GigaDevice GD25Q128 (16 MiB, JEDEC ID: C8 4018)

How to install it?
------------------

### Cautions, backups

**You do so at your own risk!**
**If you make any mistake or something goes wrong during upgrade, in worst case, your router will not boot again!**

It is a good practice to backup your original U-Boot image/partition **before** you make any changes. For example, using OpenWrt (NEC Aterm WR8750N with 8 MiB FLASH):

```
cat /proc/mtd
```

This command will show you all **MTD** (Memory Technology Device) partitions:

```
dev:    size   erasesize  name
mtd0: 00020000 00010000 "u-boot"
mtd1: 00010000 00010000 "config"
mtd2: 00010000 00010000 "art"
mtd3: 00fc0000 00010000 "firmware"
```

As you can see, `u-boot` partition size is **0x20000** (128 KiB) and my image for this model has the same size. You should remember about this if you want to use `mtd` utility or serial console and U-Boot command line, to change the bootloader.

To backup `u-boot` partition in RAM, run:

```
cat /dev/mtd0 > /tmp/uboot_backup.bin
```

And then connect to your router using `SCP protocol` and download from `/tmp` the `uboot_backup.bin` file.

### Using OpenWrt

WIP

How to use it?
--------------

WIP

How to compile the code?
------------------------

### Building on Linux

You can use one of the free toolchains:

- Recommended and used for snapshots build: [OpenWrt SDK in ath79 target for A71xx MIPS (snapshot)](http://downloads.openwrt.org/snapshots/targets/ath79/generic/openwrt-sdk-ath79-generic_gcc-7.4.0_musl.Linux-x86_64.tar.xz),
- or any others...

I am using **OpenWrt Toolchain in ath79 target for AR71xx MIPS** (in WSL) and all binary images were/will be built using this set.

All you need to do, after choosing a toolchain, is to modify [Makefile](Makefile) - change or remove `export MAKECMD` and if needed add `export PATH`. For example, to use OpenWrt Toolchain instead of Sourcery CodeBench Lite, download it and extract into `toolchain` folder, inside the top dir and change first lines in [Makefile](Makefile):

```
export BUILD_TOPDIR=$(PWD)
export STAGING_DIR=$(BUILD_TOPDIR)/tmp

export MAKECMD=make --silent ARCH=mips CROSS_COMPILE=mips-openwrt-linux-uclibc-
export PATH:=$(BUILD_TOPDIR)/toolchain/bin/:$(PATH)
```

To build image, run `make model` inside top dir, for example, command:

```
make nec_wr8750n
```

will start building U-Boot image for **NEC Aterm WR8750N**.

### Building on macOS (OS X)

(unknown)

License, outdated sources etc.
------------------------------

**[U-Boot](http://www.denx.de/wiki/U-Boot/WebHome "U-Boot")** project is Free Software, licensed under version 2 of the **GNU General Public License**. All information about license, contributors etc., are included with sources, inside *u-boot* folder.

You should know, that most routers, especially those based on Atheros SoCs, uses very old versions of U-Boot (1.1.4 is from 2005/2006). So, *these sources are definitely outdated* (do not even try to merge them with official release), but it was easier for me to modify them, than move TP-Link/Atheros changes to the current version. Moreover, lot of unnecessary code fragments and source files were removed for ease of understanding the code.

Credits
-------

- Thanks to pepe2k for original u-boot_mod
- Thanks to M-K O'Connell for donating a router with QCA9563
- Thanks to Krzysztof M. for donating a TL-WDR3600 router
- Thanks to *pupie* from OpenWrt forum for his great help
- Thanks for all donators and for users who contributed in code development
