#include <gb/gb.h>
#include "stdint.h"
#include "bgtiles.c"
#include "bgmap.c"

uint8_t backgroundoffset1x;
uint8_t backgroundoffset2x;
uint8_t backgroundoffset3x;
uint8_t backgroundoffset4x;

void interruptLCD() {
    switch (LYC_REG)
    {
        case  0x00:
            move_bkg(backgroundoffset1x,0);
            LYC_REG = 0x10; //16px
            break;

        case  0x10:
            move_bkg(backgroundoffset2x,0);
            LYC_REG = 0x78; //120px
            break;
        case  0x78:
            move_bkg(backgroundoffset3x,0);
            LYC_REG = 0x90; //144px
            break;
        case  0x90:
            move_bkg(backgroundoffset4x,0);
            LYC_REG = 0x00;
            break;
        
        default:
            break;
    }
}

void main(){
    backgroundoffset1x = 0;
    backgroundoffset2x = 0;
    backgroundoffset3x = 0;
    backgroundoffset4x = 0;

    set_bkg_data(0, 12, bgtiles);
    set_bkg_tiles(0, 0, bgmapWidth, bgmapHeight, bgmap);

    STAT_REG = 0x45; // enable LYC=LY
    LYC_REG = 0x00;


    disable_interrupts();
    add_LCD(interruptLCD);
    enable_interrupts();

    set_interrupts(VBL_IFLAG | LCD_IFLAG);

    SHOW_BKG;
    DISPLAY_ON;

    while(1){
        
        backgroundoffset1x += 1;
        backgroundoffset2x += 2;
        backgroundoffset3x += 5;
        backgroundoffset4x += 7;

        delay(50);
    }
}
