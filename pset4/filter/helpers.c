#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

int pixel_blur(int a, int b, int height, int width, RGBTRIPLE * original_image, RGBTRIPLE out_blurred_image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int avg_rbg = ( image[i][j].rgbtRed +  image[i][j].rgbtGreen +  image[i][j].rgbtBlue) / 3;
            image[i][j].rgbtRed = avg_rbg;
            image[i][j].rgbtGreen = avg_rbg;
            image[i][j].rgbtBlue = avg_rbg;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //Creates the sepia colors
            int sepRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            int sepGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            int sepBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            // caps the numbers to 255
            if(sepRed > 255)
            {
                sepRed = 255;
            }
            if(sepGreen > 255)
            {
                sepGreen = 255;
            }
            if(sepBlue > 255)
            {
                sepBlue = 255;
            }
            //Changes the pixel color values to the sepia ones
            image[i][j].rgbtRed = sepRed;
            image[i][j].rgbtGreen = sepGreen;
            image[i][j].rgbtBlue = sepBlue;

        }
    }
    return;

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE tmpImage = image[i][j];
            image[i][j] = image[i][(width - j)];
            image[i][(width - j)] = tmpImage;
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    size_t image_size = height * width * sizeof(RGBTRIPLE);
    RGBTRIPLE * original_image = malloc(image_size);

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            // original_image + i * height + j   RGBTRIPLE * -> pointer to cell
            // image[i][j]                       RGBTRIPLE   -> cell
            *(original_image + i * width + j) = image[i][j];
        }
    }

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            pixel_blur(i, j, height, width, original_image, image);
        }
    }

    return;
}
// avrages out the rgb value in a 3x3 around the current pixel
int pixel_blur(int a, int b, int height, int width, RGBTRIPLE * original_image, RGBTRIPLE out_blurred_image[height][width])
{
    int sumRed = 0;
    int sumGreen = 0;
    int sumBlue = 0;
    int avgRed = 0;
    int avgGreen = 0;
    int avgBlue = 0;
    RGBTRIPLE * temp_pixel = NULL;

    int min_height = fmax(0, a - 1);
    int max_height = fmin(height - 1, a + 1);
    int min_width = fmax(0, b - 1);
    int max_width = fmin(width - 1, b + 1);

    int grid_size = (max_height - min_height + 1) * (max_width - min_width + 1);
    for(int i = min_height; i <= max_height; i++) {
        for(int j = min_width; j <= max_width; j++) 
        {
            temp_pixel = original_image + i * width + j;
            sumRed += temp_pixel->rgbtRed; //out_blurred_image[i][j].rgbtRed;
            sumGreen += temp_pixel->rgbtGreen; //out_blurred_image[i][j].rgbtGreen;
            sumBlue += temp_pixel->rgbtBlue; //out_blurred_image[i][j].rgbtBlue;
        }
    }

    avgRed = (sumRed + grid_size / 2) / grid_size;
    avgGreen = (sumGreen + grid_size / 2) / grid_size;
    avgBlue = (sumBlue + grid_size / 2) / grid_size;

    out_blurred_image[a][b].rgbtRed = avgRed;
    out_blurred_image[a][b].rgbtGreen = avgGreen;
    out_blurred_image[a][b].rgbtBlue = avgBlue;

    return 0;
// starting block = avg
}
