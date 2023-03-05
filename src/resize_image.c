#include <math.h>
#include "image.h"
#include <stdio.h>

float nn_interpolate(image im, float x, float y, int c)
{
    // TODO Fill in
    // Nearest Neightbour interpolation
    return get_pixel(im, round(x), round(y), c);
}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
    image imageResized = make_image(w, h, im.c);

    // Get resizing coeficients
    float Sx, Sy = 0;
    Sx = w/(float)im.w;
    Sy = h/(float)im.h;

    float Xorig, Yorig = 0;
    float pixel = 0;
    for (int c=0; c!=im.c; c++)
    {
        for (int y=0; y!=h; y++)
        {
        // Original coordinate system position calculation
        //   Reescale + Grid Shifting  
        Yorig = (y/Sy)+(0.5/Sy)-0.5;
            for (int x=0; x!=w; x++)
            {
                Xorig = (x/Sx)+(0.5/Sx)-0.5;
                pixel = nn_interpolate(im, Xorig, Yorig, c);
                set_pixel(imageResized, x, y, c, pixel);
            }
        }
    }
    return imageResized;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    int x1 = floor(x);
    int x2 = ceil(x);
    int y1 = floor(y);
    int y2 = ceil(y);

    // Get sorrounding pixels
    float v1 = get_pixel(im, x1, y1, c);
    float v2 = get_pixel(im, x2, y1, c);
    float v3 = get_pixel(im, x1, y2, c);
    float v4 = get_pixel(im, x2, y2, c);

    float d1,d2,d3,d4,q1,q2,q=0;

    d1 = x-x1;
    d2 = x2-x;

    q1 = v1*d2+v2*d1;
    q2 = v3*d2+v4*d1;

    d3 = y-y1;
    d4 = y2-y;

    q = q1*d4+q2*d3;
    return q;
}

image bilinear_resize(image im, int w, int h)
{
	// TODO
	image imageResized = make_image(w, h, im.c);
    
	// Get resizing coeficients
	float Sx, Sy = 0;
	Sx = w/(float)im.w;
	Sy = h/(float)im.h;
    float Xorig, Yorig = 0;
    for (int c=0; c!=im.c; c++)
    {
        for (int y=0; y!=h; y++)
	    {
            Yorig = (y/Sy)+(0.5/Sy)-0.5;
            for (int x=0; x!=w; x++)
            {
                Xorig = (x/Sx)+(0.5/Sx)-0.5;
                set_pixel(imageResized, x, y, c, bilinear_interpolate(im, Xorig, Yorig, c));  
            } 
        }
    }
	return imageResized;
}

