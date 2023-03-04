#include <math.h>
#include "image.h"

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
    Sx = w/im.w;
    Sy = h/im.h;

    float Xorig, Yorig = 0;
    for (int c=0; c!=im.c; c++)
    {
        for (int y=0; y!=h; y++)
        {
        // Original coordinate system position calculation
        Yorig = (y/Sy)+(0.5/Sy)-0.5;
            for (int x=0; x!=w; x++)
            {
                Xorig = (x/Sx)+(0.5/Sx)-0.5;
                set_pixel(imageResized, x, y, c, nn_interpolate(im, Xorig, Yorig, c));
            }
        }
    }
    return imageResized;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    return 0;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    return make_image(1,1,1);
}

