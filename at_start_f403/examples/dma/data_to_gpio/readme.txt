/**
  **************************************************************************
  * @file     readme.txt
  * @brief    readme
  **************************************************************************
  */

  this demo is based on the at-start board, in this demo, provides a description
  of how to use a dma channel to transfer a halfword data buffer from embedded
  sram memory to gpioc and gpioc0~gpioc15 output the data of data buffer. dma1
  channel2 is configured to transfer the contents of a 16-halfword data buffer
  stored in embedded sram memory to the gpioc. if transfer full data, the three 
  leds will turn on. user can use logic analyzer get waveform.
