#!/bin/bash
rm *.img

make mrproper
rm -rf board/samsung/mixtile4x12/config.mk
echo "CONFIG_SYS_TEXT_BASE = 0x7fd00000" > board/samsung/mixtile4x12/config.mk
echo "CONFIG_EXYNOS4412 = 1" >> board/samsung/mixtile4x12/config.mk
make mixtile4x12_config
make mixtile4x12_config
make -j4
cat bl1/E4412_nbl1.img bl2.bin nop.add u-boot_big.bin bl1/E4412_tzsw.img nop.add > bootloader-mixtile-4412-1G.img

make mrproper
rm -rf board/samsung/mixtile4x12/config.mk
echo "CONFIG_SYS_TEXT_BASE = 0x7fd00000" > board/samsung/mixtile4x12/config.mk
echo "CONFIG_EXYNOS4412 = 1" >> board/samsung/mixtile4x12/config.mk
echo "CONFIG_DDR3_2G = 1" >> board/samsung/mixtile4x12/config.mk
make mixtile4x12_config
make mixtile4x12_config
make -j4
cat bl1/E4412_nbl1_2G.img bl2.bin nop.add u-boot_big.bin bl1/E4412_tzsw_2G.img nop.add >bootloader-mixtile-4412-2G.img

rm bl2.bin u-boot_big.bin u-boot.bin
