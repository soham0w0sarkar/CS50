#include "helpers.h"
#include <math.h>
#include <stdio.h>




// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++) // looping through all the pixels
    {
        for (int j = 0; j < width; j++)
        {
            float avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed); // finding the average of values of pixel
            avg /= 3;
            avg = round(avg);
            image[i][j].rgbtBlue = avg; // assinging all of them same value so that end result is gray
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

//Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++) // using simple swap function
        {
            int temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = temp;

            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = temp;

            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = temp;
        }
    }
    return;
}

//Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width]; // creating a similar image

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j]; // copying original image in the copy
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j  < width; j++)
        {
            int sumRed = 0;
            int sumBlue = 0;
            int sumGreen = 0;
            int count = 0;

            for (int x = -1; x < 2; x++)
            {
                if (i + x >= 0 && i + x < height) // checking if the pixel is valid to operate
                {
                    for (int y = -1; y < 2; y++)
                    {
                        if (j + y >= 0 && j + y < width)
                        {
                            sumBlue += copy[i + x][j + y].rgbtBlue; // box blur
                            sumGreen += copy[i + x][j + y].rgbtGreen;
                            sumRed += copy[i + x][j + y].rgbtRed;
                            count++; // calculating on how many pixels we have operated
                        }
                    }
                }
            }
            sumBlue = round((float)sumBlue / count); // giving the average value of same type to each of them
            sumGreen = round((float)sumGreen / count);
            sumRed = round((float)sumRed / count);
            image[i][j].rgbtBlue = sumBlue;
            image[i][j].rgbtGreen = sumGreen;
            image[i][j].rgbtRed = sumRed;
        }
    }
    return;
}


//Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width]; // creating a copy image

    int Gx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}; // defining gx and gy
    int Gy[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j]; // copying from original image to copy
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int gxRed = 0;
            int gxBlue = 0;
            int gxGreen = 0;

            int gyRed = 0;
            int gyBlue = 0;
            int gyGreen = 0;

            float pixelg = 0;


            for (int x = -1; x < 2; x++)
            {
                if (i + x >= 0 && i + x < height) // checking if the pixel is valid or not
                {

                    for (int y = -1; y < 2; y++)
                    {
                        if (j + y >= 0 && j + y < width)
                        {
                            gxRed += copy[i + x][j + y].rgbtRed * Gx[x + 1][y + 1]; // applying the algo
                            gxBlue += copy[i + x][j + y].rgbtBlue * Gx[x + 1][y + 1]; // multiplying kernel values with each pixel
                            gxGreen += copy[i + x][j + y].rgbtGreen * Gx[x + 1][y + 1];

                            gyRed += copy[i + x][j + y].rgbtRed * Gy[x + 1][y + 1];
                            gyBlue += copy[i + x][j + y].rgbtBlue * Gy[x + 1][y + 1];
                            gyGreen += copy[i + x][j + y].rgbtGreen * Gy[x + 1][y + 1];
                        }
                    }
                }
            }

            pixelg = pow(gxRed, 2) + pow(gyRed, 2); // sobel operater
            pixelg = round(sqrt((float)pixelg));

            image[i][j].rgbtRed = fmin(pixelg, 255);

            pixelg = pow(gxBlue, 2) + pow(gyBlue, 2);
            pixelg = round(sqrt((float)pixelg));

            image[i][j].rgbtBlue = fmin(pixelg, 255); // capping the value of pixel

            pixelg = pow(gxGreen, 2) + pow(gyGreen, 2);
            pixelg = round(sqrt((float)pixelg));

            image[i][j].rgbtGreen = fmin(pixelg, 255);
        }
    }

    return;

}