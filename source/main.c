// Includes
#include <PA9.h>       // Include for PA_Lib

// PAGfxConverter Include
#include "gfx/all_gfx.c"
#include "gfx/all_gfx.h"
#include "mapping.h"
#include "meow.h"

#define XMAX 15
#define YMAX 15

struct cell {
  int po;
  int stat;
  int win;
};

s16 level = 0;
s16 fade;
u8 black = 0;

int catdir; // Cat direction
int catx, caty; // Cat position
int reset = 0;
int nbsprites = 6;
int dot_step = 10;
int bottomcatx = -29;
int bottomcaty = -8;
int sidecatx = -29;
int sidecaty = -22;
int topcatx = -32;
int topcaty = -38;
int fliptopcatx = 9;
int flipsidecatx = 6;
int flipbottomcatx = 7;

int initcatx[6] = {6, 7, -29, -29, -32, 9};
int initcaty[6] = {-22, -8, -8, -22, -38, -38};

int lx[200];
int ly[200];
int lx2[200];
int ly2[200];
int ld[200];

struct cell cel[YMAX][XMAX];

int addx0[6] = {1, 0, -1, -1, -1, 0};
int addy0[6] = {0, 1, 1, 0, -1, -1};
int addx1[6] = {1, 1, 0, -1, 0, 1};
int addy1[6] = {0, 1, 1, 0, -1, -1};

/*int _loc2[6] = {1, 0, 0, -1, 0, 0};
int _loc1[6] = {0, 1, 1, 0, -1, -1};*/

int directiony[6] = {0, 1, 1, 0, -1, -1};
int directionx1[6] = {1, 1, 0, -1, 0, 1};
int directionx2[6] = {1, 0, -1, -1, -1, 0};

int direction[6] = {4, 5, 2, 1, 0, 3};

int get_nearest() {
    int _loc2;
    int _loc6;
    int _loc1;
    int _loc3;
    int _loc5;
    int _loc4;
    int _loc8;
    int _loc9;
    int _loc10;
    int _loc11;
    cel[caty][catx].po = 0;
    lx[0] = catx;
    ly[0] = caty;
    int _loc12 = 1;
    int _loc7 = 999;
    
    int po;
    
    for ( po = 1; po < 200; po++) {
        _loc3 = 0;
        for (_loc2 = 0; _loc2 < _loc12; ++_loc2) {
            int _loc5 = lx[_loc2];
            int _loc4 = ly[_loc2];
            for (_loc1 = 0; _loc1 < 6; ++_loc1) {
                int _loc9 = _loc4 % 2 ? (_loc5 + addx1[_loc1]) : (_loc5 + addx0[_loc1]);
                int _loc8 = _loc4 + addy0[_loc1];
                if (cel[_loc8][_loc9].stat != 1)
                  continue;
                if (cel[_loc8][_loc9].po >= 0)
                  continue;
                cel[_loc8][_loc9].po = po;
                lx2[_loc3] = _loc9;
                ly2[_loc3] = _loc8;
                ++_loc3;
                if (cel[_loc8][_loc9].win && po < _loc7)
                  _loc7 = po;
            }
        }
        if (_loc3 == 0)
          break;
        for (_loc2 = 0; _loc2 < _loc3; ++_loc2)
        {
          lx[_loc2] = lx2[_loc2];
          ly[_loc2] = ly2[_loc2];
        }
        _loc12 = _loc3;
    }
    if (_loc7 == 999)
      return (0);
    _loc3 = 0;
    for (_loc2 = 0; _loc2 < YMAX; ++_loc2) {
      for (_loc6 = 0; _loc6 < XMAX; ++_loc6) {
        if (cel[_loc2][_loc6].po == _loc7 && cel[_loc2][_loc6].win) {
          lx[_loc3] = _loc6;
          ly[_loc3] = _loc2;
          ++_loc3;
        }
      }
    }
    if (_loc3 == 0)
      return (0);
      _loc11 = PA_RandMax(_loc3-1);
    _loc5 = lx[_loc11];
    _loc4 = ly[_loc11];
    for (_loc10 = 0; _loc10 < 200; ++_loc10) {
      _loc3 = 0;
      for (_loc1 = 0; _loc1 < 6; ++_loc1) {
        _loc9 = _loc4 % 2 ? (_loc5 + addx1[_loc1]) : (_loc5 + addx0[_loc1]);
        _loc8 = _loc4 + addy0[_loc1];
        
        if (cel[_loc8][_loc9].stat != 1)
          continue;
        if (cel[_loc8][_loc9].po >= cel[_loc4][_loc5].po)
          continue;
        lx[_loc3] = _loc9;
        ly[_loc3] = _loc8;
        ld[_loc3] = _loc1;
        ++_loc3;
      }
      if (_loc3 == 0)
        return (0);
      _loc11 = PA_RandMax(_loc3-1);
      _loc5 = lx[_loc11];
      _loc4 = ly[_loc11];
      // Find cat position
      if (cel[_loc4][_loc5].po == 1) {
        catx = _loc5;
        caty = _loc4;
        catdir = 0;
        // Find cat direction
        for (_loc1 = 0; _loc1 < 6; ++_loc1)
        {
          _loc9 = _loc4 % 2 ? (_loc5 + addx1[_loc1]) : (_loc5 + addx0[_loc1]);
          _loc8 = _loc4 + addy0[_loc1];
          if (cel[_loc8][_loc9].po == 0)
            catdir = (_loc1 + 3) % 6;
        }
        return (1);
      }
    }
    return (0);
}

int rand_move() {
    int _loc6 = catx;
    int _loc5 = caty;
    int _loc2 = 0;
    int _loc1, _loc4 ,_loc3;
    for (_loc1 = 0; _loc1 < 6; ++_loc1) {
        _loc4 = _loc5 % 2 ? (_loc6 + addx1[_loc1]) : (_loc6 + addx0[_loc1]);
        _loc3 = _loc5 + addy0[_loc1];
        if (cel[_loc3][_loc4].stat != 1) {
            continue;
        }
        lx[_loc2] = _loc4;
        ly[_loc2] = _loc3;
        ld[_loc2] = _loc1;
        ++_loc2;
    }
    if (_loc2 == 0) {
        return (0);
    }
    int _loc7 = PA_RandMax(_loc2-1);
    catx = lx[_loc7];
    caty = ly[_loc7];
    catdir = ld[_loc7];
    return (1);
}

int goto_win() {
  int _loc5 = catx;
  int _loc4 = caty;
  int _loc1, _loc2, _loc3;
  for (_loc1 = 0; _loc1 < 6; ++_loc1) {
    _loc3 = _loc4 % 2 ? (_loc5 + addx1[_loc1]) : (_loc5 + addx0[_loc1]);
    _loc2 = _loc4 + addy0[_loc1];
    if (cel[_loc2][_loc3].stat != 1)
      continue;
    if (cel[_loc2][_loc3].win) {
      catx = _loc3;
      caty = _loc2;
      catdir = _loc1;
      reset = 1;
      return (1);
    }
  }
  
  return (0);
}

int go_out() {
    int _loc5 = catx;
    int _loc4 = caty;
    int _loc1, _loc2, _loc3;
    for (_loc1 = 0; _loc1 < 6; ++_loc1) {
        _loc3 = _loc4 % 2 ? (_loc5 + addx1[_loc1]) : (_loc5 + addx0[_loc1]);
        _loc2 = _loc4 + addy0[_loc1];
        if (cel[_loc2][_loc3].stat == 0) {
            catx = _loc3;
            caty = _loc2;
            catdir = _loc1;
            return (1);
        }
    }
    return (0);
}

// Make the cat run in catdir direction
void flee_cat() {
  int i;
  PA_SetSpriteXY(0, direction[catdir], 256, 256);
  PA_WaitForVBL();
  PA_SetSpriteAnim(0, direction[catdir], 0);
  if (caty%2 == 0)
    catx += directionx2[catdir];
  else
    catx += directionx1[catdir];
  caty += directiony[catdir];
  if (caty%2 ==0)
		PA_SetSpriteXY(0, direction[catdir], 21*(catx-2) + initcatx[catdir] - (caty-2)/2, 16*(caty-2) + initcaty[catdir]);
	else
		PA_SetSpriteXY(0, direction[catdir], 21*(catx-2) + dot_step + initcatx[catdir] - (caty-2)/2, 16*(caty-2) + initcaty[catdir]);
  PA_WaitForVBL();
  PA_StartSpriteAnimEx(0, direction[catdir], 1, 5, 20, ANIM_UPDOWN, 1);
  for(i = 0; i < 36; i++) PA_WaitForVBL();
}

// remove the current sprite
// define a new position
// draw a sprite at the new position
void move_cat() {
  int i;
  int oldcatx = catx;
  int oldcaty = caty;

  // Hide the cat sprite  
  PA_SetSpriteXY(0, direction[catdir], 256, 256);
  PA_WaitForVBL();

  PA_OutputText(1,0,YMAX+4,"old direction : %d", catdir);

  if (go_out() == 0) {
  	if (goto_win() == 0) {
      if (get_nearest() == 0) {
        if (rand_move() == 0) {
          reset = 1;
        }
      }
    }
  }
	
	PA_OutputText(1,0,YMAX+2,"direction : %d    ", catdir);
	PA_OutputText(1,0,YMAX+3,"%d %d %d %d   ", oldcatx, oldcaty, catx, caty);

	PA_SetSpriteAnim(0, direction[catdir], 0);

	if ((oldcaty-2)%2 ==0)
		PA_SetSpriteXY(0, direction[catdir], 21*(oldcatx-2) + initcatx[catdir] - (oldcaty-2)/2, 16*(oldcaty-2) + initcaty[catdir]);
	else
		PA_SetSpriteXY(0, direction[catdir], 21*(oldcatx-2) + dot_step + initcatx[catdir] - (oldcaty-2)/2, 16*(oldcaty-2) + initcaty[catdir]);

	if (reset != 1)
	{
    PA_StartSpriteAnimEx(0, direction[catdir], 1, 5, 20, ANIM_UPDOWN, 1);
    for(i = 0; i < 36; i++) PA_WaitForVBL();
	}
	else {
	  if (cel[caty][catx].win) {  // Win or lose?
      PA_StartSpriteAnimEx(0, direction[catdir], 1, 5, 20, ANIM_UPDOWN, 1);
      for(i = 0; i < 36; i++) PA_WaitForVBL();
      
      int repeat = 3;
      if ((caty==2) || (caty==13))
        repeat = 2;
      for (i=0; i<repeat; i++)
        flee_cat();
    }
    else {
      // Kill the cat
     	//PA_SetDefaultSound (127, 11025, 0);
	    PA_PlaySimpleSound(meow);
      PA_SetSpriteAnim(0, direction[catdir], 1);
      for(i = 0; i < 5*60; i++) PA_WaitForVBL();
    }
	}
	
	//for(i = 0; i < 40; i++) PA_WaitForVBL();
	
	/*PA_StartSpriteAnimEx(0, direction[catdir], 0, 4, 8, ANIM_UPDOWN, 1);
	
	for(i = 0; i < 38; i++) PA_WaitForVBL();
	
	PA_OutputText(1,0,YMAX+2,"direction : %d %d %d    ", catdir, _loc1[catdir], _loc2[catdir]);
	
	if ((caty-2)%2 ==0)
		PA_SetSpriteXY(0, direction[catdir], 21*(catx-2) + initcatx[catdir] - (caty-2)/2, 16*(caty-2) + initcaty[catdir]);
	else
		PA_SetSpriteXY(0, direction[catdir], 21*(catx-2) + dot_step + initcatx[catdir] - (caty-2)/2, 16*(caty-2) + initcaty[catdir]);
		
	PA_SetSpriteAnim(0, direction[catdir], 0);*/
}

int reset_game() {

  int i,j,k;

  // Hide all cat sprites
  for (i=0; i<nbsprites; i++) {
    PA_SetSpriteXY(0, i, 256, 256);
    PA_SetSpriteAnim(0, i, 0);
  }

  // Hide all dot sprites
  for (i=2 ; i< YMAX-2; i++)
    for (j=2 ; j< XMAX-2; j++) {
  	  if (cel[i][j].stat == 2) {
        int map = (j-2)+(i-2)*11+1;
        if ((i-2)%2 == 0)
        	PA_SetSpriteXY(0, map+nbsprites-1, 256, 192);
        else
        	PA_SetSpriteXY(0, map+nbsprites-1, 256, 192);
      }
    }
  
  // Wait a little
  for(level = 79; level <= 0; level--) PA_WaitForVBL();
  
  // Reset the cel matrix
	for (i=0 ; i< YMAX; i++)
		for (j=0 ; j< XMAX; j++) {
			cel[i][j].stat = 0;
			cel[i][j].po = -1;
			cel[i][j].win = 0;
		}
  
  // Reset the indices
  for (i = 0; i < 200; i++) {
    lx[i] = 0;
    ly[i] = 0;
    lx2[i] = 0;
    ly2[i] = 0;
    ld[i] = 0;
  }

  // Set the cat position at the center of the screen
  catx = XMAX/2;
  caty = YMAX/2;
  
  lx[0] = catx;
  ly[0] = caty;
  
  cel[caty][catx].stat = 2;
  catdir = 2;
  
  for (i = 2; i < YMAX - 2; i++)
    for (j = 2; j < XMAX - 2; j++)
      cel[i][j].stat = 1;

  // Draw the cat on screen
  if ((caty-2)%2 ==0)
		PA_SetSpriteXY(0, direction[catdir], 21*(catx-2) + initcatx[catdir] - (caty-2)/2, 16*(caty-2) + initcaty[catdir]);
	else
		PA_SetSpriteXY(0, direction[catdir], 21*(catx-2) + dot_step + initcatx[catdir] - (caty-2)/2, 16*(caty-2) + initcaty[catdir]);

  // Random matrix intialisation
  for (i = 0; i < 20; i++) {
      int rx = PA_RandMax(XMAX-1);
      int ry = PA_RandMax(YMAX-1);
      
      if (rx != catx && ry != caty) {
          if (cel[ry][rx].stat == 1) {
              cel[ry][rx].stat = 2;
          }
      }
  }
  
  // Display the dots on screen
  for (i = 2; i < YMAX - 2; i++)
    for (j = 2; j < XMAX - 2; j++) {
      if (cel[i][j].stat == 2) {
        //int map = 11*(i-2)+1;
        int map = (j-2)+(i-2)*11+1;
        if ((i-2)%2 == 0)
        	PA_SetSpriteXY(0, map+nbsprites-1, (map-1-(i-2)*11)*21+5-(i-2)/2, (i-2)*16+1);
        else
        	PA_SetSpriteXY(0, map+nbsprites-1, (map-1-(i-2)*11)*21+15-(i-2)/2, (i-2)*16+1);
      }
    }
    
  // Initialize the winning positions
  for (i = 0; i < YMAX; i++) {
    for (j = 0; j < XMAX; j++) {
      if (cel[i][j].stat != 1)
        continue;
      for (k = 0; k < 6; k++) {
        int nx = i % 2 ? (j + addx1[k]) : (j + addx0[k]);
        int ny = i + addy0[k];
        if (cel[ny][nx].stat == 0)
          cel[i][j].win = 1;
      }
    }
  }
  
  reset = 0;
  
  // Wait a little bit
  for(level = 0; level < 80; level++) PA_WaitForVBL();
  
  return 1;
}

// Handle the background fading effect 
void HBL_function(void) {
   s16 vcount = PA_GetVcount();
   vcount++;
   if(vcount > 192) vcount = 0; // Get correct vcount
   fade = (vcount+(level*4)-192)>>2;   
   if(fade < 0) fade = 0;
   if(fade > 31) fade = 31;
   
   if(black) PA_SetBrightness(0, fade-31);
   else PA_SetBrightness(0, 31-fade);
}   

// Function: main()
int main(int argc, char ** argv) {

  int i,j;

	PA_Init();    // Initializes PA_Lib
	PA_InitVBL(); // Initializes a standard VBL
	PA_InitRand();
 	PA_InitSound(); 
	
	/*PA_InitText(1,0);
  PA_SetTextCol(1,31,31,31);*/
	
	// Load top background
	PA_Init16bitBg(1, 3);
	PA_Load16bitBitmap(1,ecranhaut_Bitmap);
	
	// Load bottom background
	PA_Init16bitBg(0, 3);
	PA_Load16bitBitmap(0,ecranbas_Bitmap);

  // Load sprite palettes
	PA_LoadSpritePal(0, 0, (void*)cat_Pal);
	PA_LoadSpritePal(0, 1, (void*)darkgreen2_Pal);

  // Create cat sprites (facing left)
	PA_CreateSprite(0, 0, (void*)topcat_Sprite, OBJ_SIZE_64X64, 1, 0, 256, 256);  // top left cat
	PA_CreateSprite(0, 1, (void*)sidecat_Sprite, OBJ_SIZE_64X64, 1, 0, 256, 256);  // left cat
	PA_CreateSprite(0, 2, (void*)bottomcat_Sprite, OBJ_SIZE_64X64, 1, 0, 256, 256);   // bottom left cat
	
  /*
  PA_StartSpriteAnim(0, 0, 0, 4, 8);
  PA_StartSpriteAnim(0, 1, 4, 8);
  PA_StartSpriteAnim(0, 2, 0, 4, 8);
  */
  
  // Clone previously created cat sprites to create cat sprites facing right
  PA_CloneSprite(0, 3, 0);  // top right cat
  PA_SetSpriteHflip(0, 3, 1);
  PA_SetSpriteXY(0, 3, 256, 256);
  
  PA_CloneSprite(0, 4, 1);  // right cat
  PA_SetSpriteHflip(0, 4, 1);
  PA_SetSpriteXY(0, 4, 256, 256);
  
  PA_CloneSprite(0, 5, 2);  // bottom right cat
  PA_SetSpriteHflip(0, 5, 1);
  PA_SetSpriteXY(0, 5, 256, 256);
  
  /*
  PA_StartSpriteAnim(0, 3, 0, 4, 8);
  PA_StartSpriteAnim(0, 4, 0, 4, 8);
  PA_StartSpriteAnim(0, 5, 0, 4, 8);
  */

  // Create XMAX*YMAX dot sprites
  PA_CreateSprite(0, nbsprites, (void*)darkgreen2_Sprite, OBJ_SIZE_32X32, 1, 1, 256, 192);
	for (i=1 ; i< XMAX*YMAX ; i++)
		PA_CloneSprite(0, i+nbsprites, nbsprites);

	int posx, posy;

	irqSet(IRQ_HBLANK, HBL_function);
	irqEnable(IRQ_HBLANK);
	
  reset_game();

	int x,y;

	while (1) {  // Infinite loop to keep the program running
	  if (reset==1 || Pad.Newpress.Select)
      reset_game();
		if (Stylus.Released) {
			x = Stylus.X;
			y = Stylus.Y;
			if (Mapping[y][x]!=0) {
				posy = (Mapping[y][x]-1)/11;
				posx = Mapping[y][x] - 1 - posy*11;
				
				PA_OutputText(1,0,YMAX,"stylus: %d %d %d %d %d           ", posy, posx, Mapping[y][x], (Mapping[y][x]-1-posy*11)*21+5-posy/2, posy*16+1);
				PA_OutputText(1,0,YMAX+1,"cat pos: %d %d           ", caty, catx);
				
				if (cel[posy+2][posx+2].stat == 1 && (caty != posy+2 || catx != posx+2)) {
  				
          // make stylus position unavailable for the cat
				  cel[posy+2][posx+2].stat = 2;
				
					// display dot sprite on stylus position
					if (posy%2 == 0)
						PA_SetSpriteXY(0, Mapping[y][x]+nbsprites-1, (Mapping[y][x]-1-posy*11)*21+5-posy/2, posy*16+1);
					else
						PA_SetSpriteXY(0, Mapping[y][x]+nbsprites-1, (Mapping[y][x]-1-posy*11)*21+15-posy/2, posy*16+1);

					// move the cat
					move_cat();
					
					// reinitialize weight matrix
          for (i=0 ; i< YMAX; i++)
        		for (j=0 ; j< XMAX; j++)
        		  cel[i][j].po = -1;
        		  
        	/*for (i=0 ; i< YMAX; i++)
            for (j=0 ; j< XMAX; j++)
              PA_OutputText(1,j,i,"%d ", cel[i][j].stat);*/
				}
			}
		}
			
		PA_WaitForVBL();
	}
	
	return 0;
}
