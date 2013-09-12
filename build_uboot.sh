#!/bin/bash
rm *.img

make mrproper
make mixtile4x12_config
make mixtile4x12_config
make -j4
cat bl1/E4412_nbl1.img bl2.bin nop.add u-boot_big.bin bl1/E4412_tzsw.img nop.add > bootloader-mixtile-4412.img

rm bl2.bin u-boot_big.bin u-boot.bin
