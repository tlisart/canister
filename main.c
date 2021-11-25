/*
Example main for the art_engine library for generative art pixel per pixel and
physics dynamics

Author : Théo Lisart
2021
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // Integer size handling

#include "artengine.h"

// engine variables : sWidth, sDepth

#define _height 438
#define _width 625

#define width 438      // integer
#define height 625     // integer

#define projectName "NAME"

/*
Pixels and sub-pixels, the subdivision should be done such as the number of sub-pixels
per pixels must fit perfectly.
*/

void main(){
  /*
  Starting by defining the abstract image structure, doing pixel per pixel,
  the first approach is the heavy, not so smart 1D array to a 1D array of

      Greyscale    - 1
      RGB          - 2
      Alpha + RGB  - 3

  Pixel per pixel allows for heavy lifting such as implementation of various
  noises and of course all effects.

  Structure : First int of the table : sets the type of coloring
  */


  int n = width * height;

  // Initiating frame
  int *vFrame;
  vFrame = calloc(n, sizeof(int)*3); // Setting to greyscale

  int init_x = 0;
  int init_y = 0;
  int subWidth = 100;
  int subHeight = 100;

/*
  for(int i = 0; i < 14; i ++){
    int *color; color = calloc(3, sizeof(int)); color[0] = i*5; color[1] = i*5; color[2] = 50+i;
    setSubPixel(init_x + i*25, init_y + i*25, width, height, subWidth, subHeight, color, &vFrame);
    free(color);
  }*/

  // Cellular automata basis
  int sizeSubBlock = 1;
  int maxIteration = 90;
  int offSet = 0;
  int *color1; color1 = calloc(3, sizeof(int)); color1[0] = 255; color1[1] = 0; color1[2] = 15;
  int *color2; color2 = calloc(3, sizeof(int)); color2[0] = 40; color2[1] = 20; color2[2] = 150;

  dayAndNightCellularAutomaton(sizeSubBlock, maxIteration, width, height, color1, color2, offSet, &vFrame);
  //drawPixel(init_x, init_y, width, height, color, &vFrame);
  //convertToGreyscale(n, width, height, &vFrame);
  int amp = 10;
  //reverseColor(n, width, height, &vFrame);
  rgbNoiser(0, 0, width - 1, height - 1, width, height, amp, &vFrame);
  6
  cToBitmap(n, width, height, projectName, &vFrame);

  // Freeing memory
  free(vFrame);
//  free(color);
}
