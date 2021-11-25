/*
The Art Engine is build to fit perfectly my needs, which are a flexible yet
powerful drawing tool for generative art and mathematical exercices which I
think are either fun or interesting.

The main idea is to compress into one header
file all functions needed to produce generative art based on pixel manipulation
added the hability to export to various formats. At this stage live visualization
is not expected to be implemented, but who really knows.
*/

// Toolbox
int getIndex(int width, int height, int pos_x, int pos_y){
  /*Returns 1D index of x-y position*/
  return pos_x + pos_y * width;
}

int getIndexTree(int width, int height, int pos_x, int pos_y){
  /*Returns 1D index of x-y position*/
  return 3*(pos_x + pos_y * width);
}

int colorfix(int width, int height, int **vFrame){

  /*Safeguard after color manipulation to avoid under and overflow*/
  int n = width*height;
  for(int i = 0; i < 3*n; i++){
    if((*vFrame)[i] > 255){(*vFrame)[i] = 255;}
    else if((*vFrame)[i] < 0){(*vFrame)[i] = 0;}
  }
  return 1;
}

// Image treatment -----------------------------------------------------------------
float getLumen(float R, float G, float B){
  /*
  INPUT : RGB data
  OUTPUT : Greyscale representation (CIE)
  Desc : Greyscale representation conversion as */

  return 0.2126 * R   +   0.7152 * G   +   0.0722 * B;
}

int convertToGreyscale(int n, int width, int height, int **vFrame){
  /*
  INPUT : RGB image
  OUTPUT : Greyscale image using CIE recom

  Desc : Output greyscale in same format than the input int/RGB
  */

  int i = 0; float bufferLumen = 0;
  printf("Converting RGB to Greyscale\n");

  while(i < 3*n){
    bufferLumen = getLumen((*vFrame)[i], (*vFrame)[i + 1], (*vFrame)[i + 2]);  // Computing value
    (*vFrame)[i] = (int) bufferLumen; (*vFrame)[i + 1] = (int) bufferLumen; (*vFrame)[i + 2] = (int) bufferLumen;  // Recording value
    i = i + 3;
  }

  return 1;
}


int reverseColor(int n, int width, int height, int **vFrame){

  /*
  INPUT : RGB image
  OUTPUT : Reverse color based on 255 RGB
  Desc : reversing colors can be done by just changing the RGB makup.

    newR = 255 - r
    newG = 255 - g
    newB = 255 - b
  */

  for(int i = 0; i < 3*n; i++){
    (*vFrame)[i] = 255 - (*vFrame)[i];
  }
}


int drawLine(int girth, int x_s, int y_s, int x_f, int y_f, int *color, int **vFrame){
  /*
  Starts at the first point, then goes through the list, adjusting colors to draw
  a line. First we draw a one pixel line parametrically, with roundings, then
  we extend to fit girth.
  */

  int minIndex;
  int maxIndex;

  return 1;
}


int drawPixel(int pos_x, int pos_y, int width, int height, int *color, int **vFrame){
  /*
  Draws a pixel on the given frame
  */

  int R = color[0];
  int G = color[1];
  int B = color[2];

  int i_init = 3*(pos_x + width*pos_y);
  (*vFrame)[i_init] = R; (*vFrame)[i_init + 1] = G; (*vFrame)[i_init + 2] = B;
}


int setSubPixel(int init_x, int init_y, int width, int height, int subWidth, int subHeight, int *color, int **vFrame){
  /*
  Colorize a subpixel from all
  INEFFICIENT WAY OF DOING IT
  */

  int R = color[0];
  int G = color[1];
  int B = color[2];

  int init_i = 3*(init_x + width * init_y);
  int finish_i = 3*((init_x + subWidth) + width * (init_y + subHeight));

  int i = init_i;
  int count = 0;

  while (i < finish_i) {

    /*Checking if inside subpixel*/
    if(count < subWidth){
      (*vFrame)[i] = R; (*vFrame)[i + 1] = G; (*vFrame)[i + 2] = B;
      i += 3;
      count ++;

    }else if(count >= subWidth){
      i+= 3*(width - subWidth);
      count = 0;
    }
  }

  return 1;
}


int rgbNoiser(int init_x, int init_y, int noiseWidth, int noiseHeight, int width, int height, int amp, int **vFrame){
  /*
  Using seed noise source randomly adds variation error to pixel data
  */

  int init_i = 3*(init_x + width * init_y);
  int finish_i = 3*(init_x + noiseWidth + width*(init_y + noiseHeight));

  int i = init_i;
  int count = 0;

  while (i < finish_i) {

    int var = (float) (rand() % (amp + 1));
    if(count < noiseWidth){

      int dice = (rand() % 2);
      if(dice == 0){
        (*vFrame)[i] = (*vFrame)[i] + var;
        (*vFrame)[i + 1] = (*vFrame)[i + 1] + var;
        (*vFrame)[i + 2] = (*vFrame)[i + 2] + var;
      }else{
        (*vFrame)[i] = (*vFrame)[i] - var;
        (*vFrame)[i + 1] = (*vFrame)[i + 1] - var;
        (*vFrame)[i + 2] = (*vFrame)[i + 2] - var;
      }

      i += 3;
      count ++;

    }else if(count >= noiseWidth){
      i+= 3*(width - noiseWidth);
      count = 0;
    }
  }

  colorfix(width, height, &(*vFrame));
  return 1;
}

int diffusor(int init_x, int init_y, int finish_x, int finish_y, float amp, int **vFrame){
  /*
  Given diffusion center, diffuse light
  */
}


/*

CONVECTION DIFFUSION

*/


int greyScottDiffusion(int sizeSubBlock, int maxIteration, int width, int height, int offSet, int **vFrame){
  /*
  Famous reaction-diffusion model, the local diffusion is modeled according to color code.
  Heuristic definition of density by pixel.

  The model describes the chemical reaction between two elements.
    U is being consumed
    V is being produced                    U + 2V -> 3V
    P is inert final product                    V ->  P

    Adding U : Feed rate F
    Removing V : kill rate k

    Pattern : Diffusion rate of U : D_u == 2* D_v


    Non-linear diffusion equation

    \dot{u} = -uv^2 + F(1 - u) + D_u\Delta u
    \dot{v} = uv^2 -(F + k)v + D_v\Delta v

    Double-iteration discretization scheme
    (centered finite difference)
  */



}

/*

CELLULAR AUTOMATION

*/

int setUpRandCellular(int n, int width, int height, int **board){
  /*
  Prepare the board as 1D array of ones and zeroes
  Must be improved based on seed
  */

  for(int i = 0; i < n; i++){
    int state = (int) (rand() % (1 + 1));   // Either one or zero
    (*board)[i] = state;
  }
  return 1;
}

int printCellular(int sizeSubBlock, int width, int height, int width_b, int height_b, int n, int offSet, int *color1, int *color2, int *board, int **vFrame){
  /*
  Takes a 1D array, translate it to RGB
  */

  // Setting new print to zero
  for(int i = 0; i < height_b - 1; i++){
    for(int j = 0; j < width_b - 1; j++){

      if(board[j + i*width_b] == 1){
        setSubPixel(j*sizeSubBlock + offSet, i*sizeSubBlock + offSet, width, height, sizeSubBlock, sizeSubBlock, color1, &(*vFrame));
      }else if(board[j + i*width_b] == 0){
        setSubPixel(j*sizeSubBlock + offSet, i*sizeSubBlock + offSet, width, height, sizeSubBlock, sizeSubBlock, color2, &(*vFrame));
      }
    }
  }
  return 1;
}


int dayAndNightCellularAutomaton(int sizeSubBlock, int maxIteration, int width, int height, int *color1, int *color2, int offSet, int **vFrame){
  /*
  The Day and Night cellular automata is the
    B3678/S34678
    rule set for 2D cellular automata
  */

  int width_b = (int) width / sizeSubBlock;
  int height_b = (int) height / sizeSubBlock;

  int n = width_b * height_b;

  int *board; board = calloc(n, sizeof(int));

  setUpRandCellular(n, width, height, &board);

  for(int i = 0; i < maxIteration; i++){

    int *buff; buff = calloc(n, sizeof(int));

    for(int j = 1; j < height_b - 1; j++){
      for(int k = 1; k < width_b - 1; k++){

        if(board[k + j*width_b] == 0){
          int count = 0;
          if(board[(k + 1) + j*width_b] == 1){count++;}
          if(board[(k - 1) + j*width_b] == 1){count++;}
          if(board[k + (j + 1)*width_b] == 1){count++;}
          if(board[k + (j - 1)*width_b] == 1){count++;}
          if(board[(k + 1) + (j + 1)*width_b] == 1){count++;}
          if(board[(k - 1)+ (j - 1)*width_b] == 1){count++;}
          if(board[(k - 1) + (j + 1)*width_b] == 1){count++;}
          if(board[(k + 1)+ (j - 1)*width_b] == 1){count++;}

          if(count == 3 || count == 6 || count == 7 || count == 8){
            buff[k + j*width_b] = 1;
          }else{buff[k + j*width_b] = 0;}

        }else if(board[k + j*width_b] == 1){
          int count = 0;
          if(board[(k + 1) + j*width_b] == 1){count++;}
          if(board[(k - 1) + j*width_b] == 1){count++;}
          if(board[k + (j + 1)*width_b] == 1){count++;}
          if(board[k + (j - 1)*width_b] == 1){count++;}
          if(board[(k + 1) + (j + 1)*width_b] == 1){count++;}
          if(board[(k - 1)+ (j - 1)*width_b] == 1){count++;}
          if(board[(k - 1) + (j + 1)*width_b] == 1){count++;}
          if(board[(k + 1)+ (j - 1)*width_b] == 1){count++;}

          if(count == 3 || count == 4 || count == 6 || count == 7 || count == 8){
            buff[k + j*width_b] = 1;
          }else{buff[k + j*width_b] = 0;}
        }
      }
    }

    // Saving Frame
    for(int i = 0; i < n; i++){
      board[i] = buff[i];
    }
  }

  // Printing the cellular automata
  printCellular(sizeSubBlock, width, height, width_b, height_b, n, offSet, color1, color2, board, &(*vFrame));
  free(board);

  return 1;
}

/*


// ------------------------------ MATH -----------------------------------------


*/
float mLine(int xi, int yi, int xf, int yf, float x){
  return (float) ((yf-yi)/(xf-xi))*x - (yf - ((yf-yi)/(xf-xi))*xf);
}

/*


// Image conversion ----------------------------------------------------------------


*/

int cToBitmap(int n, int width_in, int height_in, char *projectName, int **vFrame){
  /*
  INPUT : Information about image
  OUTPUT : bitmap file (bmp) - lossless, simple print of the file

  Desc : bitmaps are RAW format of image data, either in greyscale or RGB.
  Bitmaps only accept strict int sizes
  */

  //width, height, and bitcount are the key factors:
  int32_t width = width_in;
  int32_t height = height_in;

  uint16_t bitcount = 24;//<- 24-bit bitmap

  //take padding in to account
  int width_in_bytes = ((width * bitcount + 31) / 32) * 4;

  //total image size in bytes, not including header
  uint32_t imagesize = width_in_bytes * height;

  //this value is always 40, it's the sizeof(BITMAPINFOHEADER)
  const uint32_t biSize = 40;

  //bitmap bits start after headerfile,
  //this is sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
  const uint32_t bfOffBits = 54;

  //total file size:
  uint32_t filesize = 54 + imagesize;

  //number of planes is usually 1
  const uint16_t biPlanes = 1;

  //create header:
  unsigned char header[54] = { 0 };
  memcpy(header, "BM", 2);
  memcpy(header + 2 , &filesize, 4);
  memcpy(header + 10, &bfOffBits, 4);
  memcpy(header + 14, &biSize, 4);
  memcpy(header + 18, &width, 4);
  memcpy(header + 22, &height, 4);
  memcpy(header + 26, &biPlanes, 2);
  memcpy(header + 28, &bitcount, 2);
  memcpy(header + 34, &imagesize, 4);

  //Creating pixel data
  unsigned char* buf = malloc(imagesize);

  for(int row = height - 1; row >= 0; row--)
  {
      for(int col = 0; col < width; col++)
      {
          buf[row * width_in_bytes + col * 3 + 0] = (*vFrame)[getIndexTree(width, height, col, row) + 2];      //blue
          buf[row * width_in_bytes + col * 3 + 1] = (*vFrame)[getIndexTree(width, height, col, row) + 1];      //green
          buf[row * width_in_bytes + col * 3 + 2] = (*vFrame)[getIndexTree(width, height, col, row) + 0];      //red
      }
  }

  FILE *fout = fopen("projects/img.bmp", "wb");
  fwrite(header, 1, 54, fout);
  fwrite((char*)buf, 1, imagesize, fout);
  fclose(fout);
  free(buf);

  return 1;
}
