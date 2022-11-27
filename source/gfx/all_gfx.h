//Gfx converted using Mollusk's PAGfx Converter

//This file contains all the .h, for easier inclusion in a project

#ifndef ALL_GFX_H
#define ALL_GFX_H

#ifndef PAGfx_struct
    typedef struct{
    void *Map;
    int MapSize;
    void *Tiles;
    int TileSize;
    void *Palette;
    int *Info;
} PAGfx_struct;
#endif


// Sprite files : 
extern const unsigned char bottomcat_Sprite[24576] __attribute__ ((aligned (4))) ;  // Pal : cat_Pal
extern const unsigned char topcat_Sprite[24576] __attribute__ ((aligned (4))) ;  // Pal : cat_Pal
extern const unsigned char sidecat_Sprite[24576] __attribute__ ((aligned (4))) ;  // Pal : cat_Pal
extern const unsigned char darkgreen2_Sprite[1024] __attribute__ ((aligned (4))) ;  // Pal : darkgreen2_Pal

// Background files : 
extern const unsigned short ecranhaut_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short ecranbas_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap


// Palette files : 
extern const unsigned short cat_Pal[33] __attribute__ ((aligned (4))) ;
extern const unsigned short darkgreen2_Pal[27] __attribute__ ((aligned (4))) ;


#endif

