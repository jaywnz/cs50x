#include <math.h>
#include <stdlib.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over columns
        for (int j = 0; j < width; j++)
        {
            // Calculate average of each channel
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // Apply average to all channels to get equivalent shade
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int centre = round(width / 2.0);
    int counter = 0;
    RGBTRIPLE tmp[1][1];

    // For every row, swap pixels on horizontally opposite sides
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < centre; j++)
        {
            tmp[0][0] = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = tmp[0][0];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create array to store average values
    RGBTRIPLE values[height][width];
    int pixel_count = 0;

    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over columns
        for (int j = 0; j < width; j++)
        {
            int row_shift = -1;
            int col_shift = -1;
            float blue_value = 0.0;
            float green_value = 0.0;
            float red_value = 0.0;

            // Collect all channels values from grid around pixel
            while (col_shift < 2)
            {
                row_shift = -1;
                while (row_shift < 2)
                {
                    // Catch boundary errors
                    if (i + row_shift >= height || j + col_shift >= width)
                    {
                        break;
                    }
                    if (i + row_shift < 0)
                    {
                        row_shift++;
                    }
                    if (j + col_shift < 0)
                    {
                        col_shift++;
                    }
                    // Add channel values
                    blue_value += image[i + row_shift][j + col_shift].rgbtBlue;
                    green_value += image[i + row_shift][j + col_shift].rgbtGreen;
                    red_value += image[i + row_shift][j + col_shift].rgbtRed;
                    pixel_count++;
                    row_shift++;
                }
                col_shift++;
            }

            // Calculate averages in each channel for given pixel
            values[i][j].rgbtBlue = round(blue_value / pixel_count);
            values[i][j].rgbtGreen = round(green_value / pixel_count);
            values[i][j].rgbtRed = round(red_value / pixel_count);
            pixel_count = 0;
        }
    }

    // Apply calculated average values to image pixels
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            image[k][l].rgbtBlue = values[k][l].rgbtBlue;
            image[k][l].rgbtGreen = values[k][l].rgbtGreen;
            image[k][l].rgbtRed = values[k][l].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE values[height][width];
    RGBTRIPLE grid[3][3];

    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over columns
        for (int j = 0; j < width; j++)
        {
            int row_shift = -1;
            int col_shift = -1;

            // Find 3x3 grid around pixel
            while (row_shift < 2)
            {
                // Reset row counter
                col_shift = -1;
                while (col_shift < 2)
                {
                    // Catch boundary errors
                    if (i + row_shift < 0)
                    {
                        row_shift++;
                    }
                    if (j + col_shift < 0)
                    {
                        col_shift++;
                    }
                    if (j + col_shift > width - 1)
                    {
                        break;
                    }
                    // Add channel values to grid array
                    grid[row_shift + 1][col_shift + 1].rgbtBlue = image[i + row_shift][j + col_shift].rgbtBlue;
                    grid[row_shift + 1][col_shift + 1].rgbtGreen = image[i + row_shift][j + col_shift].rgbtGreen;
                    grid[row_shift + 1][col_shift + 1].rgbtRed = image[i + row_shift][j + col_shift].rgbtRed;
                    col_shift++;
                }
                row_shift++;
            }

            // Calculate Gx and Gy values from grid around pixel
            int gx_blue = 0;
            int gy_blue = 0;
            int gx_green = 0;
            int gy_green = 0;
            int gx_red = 0;
            int gy_red = 0;

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    gx_blue += (grid[k][l].rgbtBlue * gx[k][l]);
                    gx_green += (grid[k][l].rgbtGreen * gx[k][l]);
                    gx_red += (grid[k][l].rgbtRed * gx[k][l]);

                    gy_blue += (grid[k][l].rgbtBlue * gy[k][l]);
                    gy_green += (grid[k][l].rgbtGreen * gy[k][l]);
                    gy_red += (grid[k][l].rgbtRed * gy[k][l]);

                    // Clear grid
                    grid[k][l].rgbtBlue = 0;
                    grid[k][l].rgbtGreen = 0;
                    grid[k][l].rgbtRed = 0;
                }
            }

            // Calculate combined Sobel value for each channel
            double gx_gy_blue = sqrt(pow((float) gx_blue, 2.0) + pow((float) gy_blue, 2.0));
            double gx_gy_green = sqrt(pow((float) gx_green, 2.0) + pow((float) gy_green, 2.0));
            double gx_gy_red = sqrt(pow((float) gx_red, 2.0) + pow((float) gy_red, 2.0));

            // Check for and adjust levels over 255
            if (gx_gy_blue > 255)
            {
                gx_gy_blue = 255.0;
            }
            if (gx_gy_green > 255)
            {
                gx_gy_green = 255.0;
            }
            if (gx_gy_red > 255)
            {
                gx_gy_red = 255.0;
            }

            // Record calculated Sobel values before moving on to next pixel in image
            values[i][j].rgbtBlue = round(gx_gy_blue);
            values[i][j].rgbtGreen = round(gx_gy_green);
            values[i][j].rgbtRed = round(gx_gy_red);
        }
    }

    // Apply Gx/Gy values to image pixels
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n].rgbtBlue = values[m][n].rgbtBlue;
            image[m][n].rgbtGreen = values[m][n].rgbtGreen;
            image[m][n].rgbtRed = values[m][n].rgbtRed;
        }
    }
    return;
}
