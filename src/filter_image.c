#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

void l1_normalize(image im)
{
    // TODO
    // Assert 1 channel image
    assert(im.c == 1);

    float cumsum = 0.0;
    int size = im.h*im.w;

    for (int i=0; i<size; i++)
    {
        cumsum += im.data[i];
    }
    scale_image(im, 0, 1/cumsum);
}

image make_box_filter(int w)
{
    // TODO
    image im = make_image(w,w,1);
    // Adds one to each image possition
    shift_image(im, 0, 1.0);
    // Normalize values
    l1_normalize(im);
    return im;
}

image convolve_image(image im, image filter, int preserve)
{
    // TODO
    assert(im.c == filter.c || filter.c == 1);

    // Make resulting image
    image imgRes = make_image(im.w, im.h, im.c);
    // Padding amount
    int Padx = floor(filter.w/2.);
    int Pady = floor(filter.h/2.);

    // Pixels to get from image and filter
    float filPix, imPix = 0.;

    for (int y=0; y!=im.h; y++)
    {
        for (int x=0; x!=im.w; x++)
        {   
            if (preserve == 1)
            {
                for (int ch=0; ch!=im.c; ch++)
                {
                    float dstPix = 0.;
                    for (int Fy = y-Pady; Fy!=filter.h-Pady+y; Fy++)
                    {
                        for (int Fx=x-Padx; Fx!=filter.w-Padx+x; Fx++)
                        {
                            filPix = get_pixel(filter, Fx+Padx, Fy+Pady, 0);
                            imPix = get_pixel(im, Fx, Fy, ch);
                            dstPix += (imPix*filPix);
                        }
                    }
                    set_pixel(imgRes, x, y, ch, dstPix);
                }
            }
            else
            {
                float dstPix = 0.;
                for (int Fy = y-Pady; Fy!=filter.h-Pady+y; Fy++)
                {
                    for (int Fx=x-Padx; Fx!=filter.w-Padx+x; Fx++)
                    {
                        for (int ch=0; ch!=im.c; ch++)
                        {
                            imPix = get_pixel(im, Fx, Fy, ch);
                            if (im.c == filter.c)
                            {
                                filPix = get_pixel(filter, Fx+Padx, Fy+Pady, ch);
                            }
                            else
                            {
                                filPix = get_pixel(filter, Fx+Padx, Fy+Pady, 0);
                            }  
                            dstPix += (imPix*filPix);   
                        }
                    }
                }
                set_pixel(imgRes, x, y, 0, dstPix);
            }
        }
    }
    return imgRes;
}

image make_highpass_filter()
{
    image highPassFilter = make_image(3,3,1);
    // First row values
    set_pixel(highPassFilter, 0, 0, 0, 0);
    set_pixel(highPassFilter, 1, 0, 0, -1);
    set_pixel(highPassFilter, 2, 0, 0, 0);
    // Second row values
    set_pixel(highPassFilter, 0, 1, 0, -1);
    set_pixel(highPassFilter, 1, 1, 0, 4);
    set_pixel(highPassFilter, 2, 1, 0, -1);
    // Third row values
    set_pixel(highPassFilter, 0, 2, 0, 0);
    set_pixel(highPassFilter, 1, 2, 0, -1);
    set_pixel(highPassFilter, 2, 2, 0, 0);
    
    // TODO
    return highPassFilter;
}

image make_sharpen_filter()
{
    // TODO
    image sharpenFilter = make_image(3,3,1);
    // First row values
    set_pixel(sharpenFilter, 0, 0, 0, 0);
    set_pixel(sharpenFilter, 1, 0, 0, -1);
    set_pixel(sharpenFilter, 2, 0, 0, 0);
    // Second row values
    set_pixel(sharpenFilter, 0, 1, 0, -1);
    set_pixel(sharpenFilter, 1, 1, 0, 5);
    set_pixel(sharpenFilter, 2, 1, 0, -1);
    // Third row values
    set_pixel(sharpenFilter, 0, 2, 0, 0);
    set_pixel(sharpenFilter, 1, 2, 0, -1);
    set_pixel(sharpenFilter, 2, 2, 0, 0);
    
    return sharpenFilter;
}

image make_emboss_filter()
{
    // TODO
    image embossFilter = make_image(3,3,1);
    // First row values
    set_pixel(embossFilter, 0, 0, 0, -2);
    set_pixel(embossFilter, 1, 0, 0, -1);
    set_pixel(embossFilter, 2, 0, 0, 0);
    // Second row values
    set_pixel(embossFilter, 0, 1, 0, -1);
    set_pixel(embossFilter, 1, 1, 0, 1);
    set_pixel(embossFilter, 2, 1, 0, 1);
    // Third row values
    set_pixel(embossFilter, 0, 2, 0, 0);
    set_pixel(embossFilter, 1, 2, 0, 1);
    set_pixel(embossFilter, 2, 2, 0, 2);

    return embossFilter;
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO
// Yes, all of then need normalization between [0,1] if we want to show the output as image

image make_gaussian_filter(float sigma)
{
    // TODO
    return make_image(1,1,1);
}

image add_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image sub_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image make_gx_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_gy_filter()
{
    // TODO
    return make_image(1,1,1);
}

void feature_normalize(image im)
{
    // TODO
}

image *sobel_image(image im)
{
    // TODO
    return calloc(2, sizeof(image));
}

image colorize_sobel(image im)
{
    // TODO
    return make_image(1,1,1);
}
