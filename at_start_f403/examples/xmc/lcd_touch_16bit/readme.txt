/**
  **************************************************************************
  * @file     readme.txt
  * @brief    readme
  **************************************************************************
  */

  this demo is based on the at-start board, in this demo, provides a basic
  example of how to use the xmc firmware library and an associate driver to
  perform read/write operations on the lcd. and use spi3 drive touch screen,
  user can drow picture on the lcd.when used must be use the tft_lcd_demo board.
  attention: tft_lcd_demo board lcd id is 0x9341 and the touchscreen is resistive
  touchscreen.

  the pin to pin with lcd and xmc:
  - spi1_sck  pa5     --->   spi_sck
  - spi1_miso pa6     --->   spi_miso
  - spi1_mosi pa7     --->   spi_mosi
  - gpio      pb6     --->   lcd_cs
  - gpio      pb9     --->   lcd_reset
  - gpio      pb11    --->   lcd_pen
  - gpio      pb8     --->   lcd_bl
  - xmc_a0    pf0     --->   lcd_rs
  - xmc_ne1   pd7     --->   lcd_cs
  - xmc_nwe   pd5     --->   lcd_wr
  - xmc_noe   pd4     --->   lcd_rd
  - xmc_d0    pd14    --->   data[0]
  - xmc_d1    pd15    --->   data[1]
  - xmc_d2    pd0     --->   data[2]
  - xmc_d3    pd1     --->   data[3]
  - xmc_d4    pe7     --->   data[4]
  - xmc_d5    pe8     --->   data[5]
  - xmc_d6    pe9     --->   data[6]
  - xmc_d7    pe10    --->   data[7]
  - xmc_d8    pe11    --->   data[8]
  - xmc_d9    pe12    --->   data[9]
  - xmc_d10   pe13    --->   data[10]
  - xmc_d11   pe14    --->   data[11]
  - xmc_d12   pe15    --->   data[12]
  - xmc_d13   pd8     --->   data[13]
  - xmc_d14   pd9     --->   data[14]
  - xmc_d15   pd10    --->   data[15]
  for more detailed information. please refer to the application note document AN0106.


