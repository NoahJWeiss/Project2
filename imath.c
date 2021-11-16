#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>

#define THREADS 4

#define filterWidth 3
#define filterHeight 3

#define RGB_MAX 255

typedef struct {
	 unsigned char r, g, b;
} PPMPixel;

struct parameter {
	PPMPixel *image;         //original image
	PPMPixel *result;        //filtered image
	unsigned long int w;     //width of image
	unsigned long int h;     //height of image
	unsigned long int start; //starting point of work
	unsigned long int size;  //equal share of work (almost equal if odd)
};


/*This is the thread function. It will compute the new values for the region of image specified in params (start to start+size) using convolution.
    (1) For each pixel in the input image, the filter is conceptually placed on top ofthe image with its origin lying on that pixel.
    (2) The  values  of  each  input  image  pixel  under  the  mask  are  multiplied  by the corresponding filter values.
    (3) The results are summed together to yield a single output value that is placed in the output image at the location of the pixel being processed on the input.
 
 */
void *threadfn(void *params)
{
	
	int laplacian[filterWidth][filterHeight] =
	{
	  -1, -1, -1,
	  -1,  8, -1,
	  -1, -1, -1,
	};

	
    /*For all pixels in the work region of image (from start to start+size)
      Multiply every value of the filter with corresponding image pixel. Note: this is NOT matrix multiplication.
      Store the new values of r,g,b in p->result.
     */
		
	return NULL;
}


/*Create a new P6 file to save the filtered image in. Write the header block
 e.g. P6
      Width Height
      Max color value
 then write the image data.
 The name of the new file shall be "name" (the second argument).
 */
void writeImage(PPMPixel *image, char *name, unsigned long int width, unsigned long int height)
{

    
}

/* Open the filename image for reading, and parse it.
    Example of a ppm header:    //http://netpbm.sourceforge.net/doc/ppm.html
    P6                  -- image format
    \# comment           -- comment lines begin with
    \#\# another comment  -- any number of comment lines
    200 300             -- image width & height
    255                 -- max color value
 
 Check if the image format is P6. If not, print invalid format error message.
 Read the image size information and store them in width and height.
 Check the rgb component, if not 255, display error message.
 Return: pointer to PPMPixel that has the pixel data of the input image (filename)
 */
PPMPixel *readImage(const char *filename, unsigned long int *width, unsigned long int *height)
{
    char buff[32];
    PPMPixel *img;

	//read image format
    FILE *fp;
    int ch, rgb_colors;

    fp = fopen(filename, "rb");

    if(!fp) {
        perror("Unable to open file");
        exit(1);
    }

    if (!fgets(buff, sizeof(buff), fp)) {
        perror("Error reading from file");
        exit(1);
    }

	//check the image format by reading the first two characters in filename and compare them to P6.
    if (buff[0] != 'P' || buff[1] != '6') {
        perror("Not a P6 image");
        exit(1);
    } else {
        printf("header: %s", buff);
        printf("Correct file type\n");
    }

	//If there are comments in the file, skip them. You may assume that comments exist only in the header block.
    ch = getc(fp);
    while (ch == '#') {
        while (getc(fp) != '\n');
        ch = getc(fp);
    }
    ungetc(ch, fp);
	
	//read image size information
	if (fscanf(fp, "%ld %ld", width, height) != 2) {
        printf("Instead read %ln %ln", width, height);
        fprintf(stderr, "Error reading image size\n");
        exit(1);
    }

	//Read rgb component. Check if it is equal to RGB_MAX. If  not, display error message.
    if (fscanf(fp, "%d", &rgb_colors) != 1) {
        fprintf(stderr, "Error reading color depth");
        exit(1);
    } else {
        if (rgb_colors != RGB_MAX) {
            fprintf(stderr, "Not 255 colors");
            exit(1);
        }
    }

    while (fgetc(fp) != '\n');
    
    //allocate memory for img. NOTE: A ppm image of w=200 and h=300 will contain 60000 triplets (i.e. for r,g,b), ---> 180000 bytes.
    img = (PPMPixel*) malloc(3 * *width * *height * sizeof(PPMPixel));

    if (!img) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    //read pixel data from filename into img. The pixel data is stored in scanline order from left to right (up to bottom) in 3-byte chunks (r g b values for each pixel) encoded as binary numbers.
    if (fread(img, 3, *width * *height, fp) != *width * *height) {
        fprintf(stderr, "Image read failed");
        exit(1);
    }

    fclose(fp);    



	return img;
}

void showPPM(PPMPixel *image)
{
    int i;

    if (image) {
        for(i=-1;i<100;i++){
            printf("Number: %d\n",i);
            printf("R: %d ",image[i].r );
            printf("G: %d ",image[i].g );
            printf("B: %d\n ",image[i].b );

        }
    }
}

/* Create threads and apply filter to image.
 Each thread shall do an equal share of the work, i.e. work=height/number of threads.
 Compute the elapsed time and store it in *elapsedTime (Read about gettimeofday).
 Return: result (filtered image)
 */
PPMPixel *apply_filters(PPMPixel *image, unsigned long w, unsigned long h, double *elapsedTime) {

    PPMPixel *result;
    //allocate memory for result

    //allocate memory for parameters (one for each thread)

    /*create threads and apply filter.
     For each thread, compute where to start its work.  Determine the size of the work. If the size is not even, the last thread shall take the rest of the work.
     */
   

   //Let threads wait till they all finish their work.


	return result;
}


/*The driver of the program. Check for the correct number of arguments. If wrong print the message: "Usage ./a.out filename"
    Read the image that is passed as an argument at runtime. Apply the filter. Print elapsed time in .3 precision (e.g. 0.006 s). Save the result image in a file called laplacian.ppm. Free allocated memory.
 */
int main(int argc, char *argv[])
{
	//load the image into the buffer
    unsigned long int w, h;
    double elapsedTime = 0.0;
    PPMPixel *image;

    if (argc == 2) {
        image = readImage(argv[1], &w, &h);

        showPPM(image);
    } else {
        printf("Usage: imath <filename>.ppm\n");
        exit(0);
    }
	
	return 0;
}
