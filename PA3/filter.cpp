#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include "bmplib.h"

using namespace std;

//============================Add function prototypes here======================
void convolve(unsigned char[][SIZE][RGB], 
unsigned char[][SIZE][RGB], int, double[][11]);
void dummy(unsigned char[][SIZE][RGB], unsigned char[][SIZE][RGB]);
void sobel(unsigned char[][SIZE][RGB], unsigned char[][SIZE][RGB]);
void gaussian (double[][11], int, double);
void gaussian_filter(unsigned char[][SIZE][RGB], 
unsigned char[][SIZE][RGB], int, double);
void unsharp(unsigned char[][SIZE][RGB], 
unsigned char[][SIZE][RGB], int, double, double);


//============================Do not change code in main()======================

#ifndef AUTOTEST

int main(int argc, char* argv[])
{
   //First check argc
  if(argc < 3)
    {
      //we need at least ./filter <input file> <filter name> to continue
      cout << "usage: ./filter <input file> <filter name> <filter parameters>";
      cout << " <output file name>" << endl;
      return -1;
    }
   //then check to see if we can open the input file
   unsigned char input[SIZE][SIZE][RGB];
   unsigned char output[SIZE][SIZE][RGB];
   char* outfile;
   int N;
   double sigma, alpha;
   //double kernel[11][11]; causes a wraning

   // read file contents into input array
   int status = readRGBBMP(argv[1], input); 
   if(status != 0)
   {
      cout << "unable to open " << argv[1] << " for input." << endl;
      return -1;
   }
   //Input file is good, now look at next argument
   if( strcmp("sobel", argv[2]) == 0)
   {
     sobel(output, input);
     outfile = argv[3];
   }
   else if( strcmp("blur", argv[2]) == 0)
   {
     if(argc < 6)
       {
	 cout << "not enough arguments for blur." << endl;
	 return -1;
       }
     N = atoi(argv[3]); //kernel size
     sigma = atof(argv[4]); //sigma, S
     outfile = argv[5];
     gaussian_filter(output, input, N, sigma);
   }
   else if( strcmp("unsharp", argv[2]) == 0)
   {
     if(argc < 7)
       {
	 cout << "not enough arguments for unsharp." << endl;
	 return -1;
       }
     N = atoi(argv[3]);
     sigma = atof(argv[4]);
     alpha = atof(argv[5]);
     outfile = argv[6];
     unsharp(output, input, N, sigma, alpha);

   }
   else if( strcmp("dummy", argv[2]) == 0)
   {
     //do dummy
     dummy(output, input);
     outfile = argv[3];
   }
   else
   {
      cout << "unknown filter type." << endl;
      return -1;
   }

   if(writeRGBBMP(outfile, output) != 0)
   {
      cout << "error writing file " << argv[3] << endl;
   }

}   

#endif 

//=========================End Do not change code in main()=====================


// Creates an identity kernel (dummy kernel) that will simply
// copy input to output image and applies it via convolve()
//
// ** This function is complete and need not be changed.
// Use this as an example of how to create a kernel array, fill it in
// appropriately and then use it in a call to convolve.
void dummy(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
   double k[11][11];
   for (int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         k[i][j] = 0;
      }
   }
   k[1][1] = 1;
   convolve(out, in, 3, k);
}


// Convolves an input image with an NxN kernel to produce the output kernel
// You will need to complete this function by following the 
//  instructions in the comments
//convolve works!!
void convolve(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB], 
	      int N, double kernel[][11])
{
 
   int padded[SIZE+10][SIZE+10][RGB];  // Use for input image with appropriate 
                                       // padding
   int temp[SIZE][SIZE][RGB];          // Use for the unclamped output pixel 
                                       // values then copy from temp to out, 
                                       // applying clamping 

   //first set all of padded to 0 (black)
    for (int i = 0; i < (SIZE+10); i++) {
       for (int j = 0; j < (SIZE+10); j++) {
           for(int k=0;k<RGB;k++) {
           padded[i][j][k] = 0;
           }
       }
   }


   //now copy input into padding to appropriate locations
    for (int i = (N/2); i < (SIZE+(N/2)); i++) { 
       for (int j = (N/2); j < (SIZE+(N/2)); j++) {
           for(int k=0;k<RGB;k++) {
           padded[i][j][k] = in[i-(N/2)][j-(N/2)][k];
           }
       }
    }


   //initialize temp pixels to 0 (black), same size as input image
    for (int i = 0; i < (SIZE); i++) {
       for (int j = 0; j < (SIZE); j++) {
           for(int k=0;k<RGB;k++) {
           temp[i][j][k] = 0;
           }
       }
   }



  //now perform convolve (using convolution equation on each pixel of the 
  // actual image) placing the results in temp (i.e. unclamped result)
  //Here we give you the structure of the convolve for-loops, you need
  //to figure out the loop limits
  for(int y= 0;y< SIZE;y++)
    for(int x= 0;x< SIZE;x++)
      for(int k=0;k<RGB;k++)
         for(int i = (-N/2); i<=(N/2); i++)
            for(int j = (-N/2); j<=(N/2); j++)
                  temp[y][x][k] += int(padded[y+i+(N/2)][x+j+(N/2)][k]*kernel[(N/2) + i][(N/2) + j]);
//temp works in doubles and out is in ints/chars
   //now clamp and copy to output
     for(int y= 0;y< SIZE;y++)
         for(int x= 0;x< SIZE;x++)
             for(int k=0;k<RGB;k++)
                 if (temp[y][x][k] > 255) {
                     temp[y][x][k] = 255;
                 } else if (temp[y][x][k] < 0) {
                     temp[y][x][k] = 0;
                 }
    
     for(int y= 0;y< SIZE;y++)
         for(int x= 0;x< SIZE;x++)
             for(int k=0;k<RGB;k++)
                 out[y][x][k] = (unsigned char)temp[y][x][k];
   // You may need to cast to avoid warnings from the compiler:
   // (i.e. out[i][j][k] = (unsigned char) temp[i][j][k];)
}

// You will need to complete this function by following the 
//  instructions in the comments
//works
void sobel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
   double k[11][11];
   double s_h1[3][3] = { {-1, 0, 1}, 
                         {-2, 0, 2}, 
                         {-1, 0, 1} };
   double s_h2[3][3] = { {1, 0, -1}, 
                         {2, 0, -2}, 
                         {1, 0, -1} };
   
   unsigned char h1_soble[SIZE][SIZE][RGB]; //hold intemediate images
   unsigned char h2_soble[SIZE][SIZE][RGB]; 
   int temp_soble[SIZE][SIZE][RGB];

   for (int i = 0; i < 11; i++){
      for(int j=0; j < 11; j++){
         k[i][j] = 0;
      }
   }


   // Copy in 1st 3x3 horizontal sobel kernel (i.e. copy s_h1 into k)
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            k[i][j] = s_h1[i][j];


   // Call convolve to apply horizontal sobel kernel with result in h1_soble
    convolve(h1_soble, in, 3, k);

   // Copy in 2nd 3x3 horizontal sobel kernel (i.e. copy s_h2 into k)
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            k[i][j] = s_h2[i][j];
            

   // Call convolve to apply horizontal sobel kernel with result in h2_soble
    convolve(h2_soble, in, 3, k);


   // Add the two results
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            for (int l = 0; l < RGB; l++)
                temp_soble[i][j][l] = h2_soble[i][j][l] + h1_soble[i][j][l];
    //clamping
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            for (int l = 0; l < RGB; l++)
            if (temp_soble[i][j][l] > SIZE) {
                temp_soble[i][j][l] = 255;
            } else if (temp_soble[i][j][l] < 0) {
                temp_soble[i][j][l] = 0;
            }
    //set values to output
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            for (int l = 0; l < RGB; l++)
                out[i][j][l] = (unsigned char)temp_soble[i][j][l];
}


// Add the rest of your functions here (i.e. gaussian, gaussian_filter, unsharp)
void gaussian(double k[][11], int N, double S)
{ //works!!!!
//A = 1, (xo, yo) = center point (N/2), variance = sigma
    int center = (N/2);
    double sum = 0;
    for (int x = 0; x < N; x++) { 
      for(int y = 0; y < N; y++) {
          double num_y = y - center;
          double num_x = x - center;
          double denom = 2*pow(S,2);
          double y_part = (pow(num_y, 2))/denom;
          double x_part = (pow(num_x, 2))/denom;
          //actual equation
          k[x][y] = exp(-1*(x_part + y_part));
          //get number to divide by to normalize
          sum += k[x][y]; 
          cout << k[x][y] << " | "; //print out in table format
      }
      cout << endl;
    }
    
    cout << endl;
    
    //normalized
    for (int x = 0; x < N; x++) { 
      for(int y = 0; y < N; y++) {
          k[x][y] = k[x][y]/sum;
          cout << k[x][y] << " | ";
      }
        cout << endl;
    }
    
}
//apply sgaussian function
void gaussian_filter(unsigned char out[][SIZE][RGB], 
unsigned char in[][SIZE][RGB], int N, double S) 
{
  double k[11][11];
  gaussian(k, N, S);
    
  convolve(out, in, N, k);
}
//unsharp filter, apply gussian for blurred image, save value of (orig_image - blurred_image) in array d, sharpen by adding a fraction of D to orig_image and save in sharp_image array
void unsharp(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB], int N, double S, double alpha)
{
  gaussian_filter(out, in, N, S);
  //hold subtracted image
  int d[SIZE][SIZE][RGB];
  //unsigned char unsharp_img[SIZE][SIZE][RGB];
  int unsharp_img[SIZE][SIZE][RGB];
   
  //subtract blurred image
  for(int i = 0; i < SIZE; i++) {
      for(int j = 0; j < SIZE; j++) {
         for (int l = 0; l < RGB; l++) {
             d[i][j][l] = in[i][j][l] - out[i][j][l]; 
         }
      }
  }
  //clamp values as some calculations are out of bounds
  for(int i = 0; i < SIZE; i++) {
      for(int j = 0; j < SIZE; j++) {
         for (int l = 0; l < RGB; l++) {
             unsharp_img[i][j][l] = (int) (in[i][j][l] + alpha*(d[i][j][l]));
             if (unsharp_img[i][j][l] > 255) {
                 unsharp_img[i][j][l] = 255;
             } else if (unsharp_img[i][j][l] < 0) {
                 unsharp_img[i][j][l] = 0;
             }
             
             out[i][j][l] = (unsigned char)unsharp_img[i][j][l];
         }
      }
  }
  
    
}
