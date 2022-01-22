#include "BlackandWhite.h"
#include "PixelOperation/pixel_operations.h"
#include <SDL/SDL_rotozoom.h>
#include "Display/display.h"
#include <math.h>


SDL_Surface* First_LineBlur(SDL_Surface* image_surface, int width)
{

    for(int i =0; i<1;i++){
	    int j = 0;
            Uint32 pixel_00 = get_pixel(image_surface, j, i);
            Uint8 red1,green1,blue1;
            SDL_GetRGB(pixel_00, image_surface->format, &red1, &green1, &blue1);

	    int red,green,blue;
	    red = 0;
	    green = 0;
	    blue = 0;
	    red+=red1;
	    green+=green1;
	    blue+=blue1;

            Uint8 r,g,b;
	    r = 0;
            g = 0;
            b = 0;

            Uint32 pixel = get_pixel(image_surface,j+1,i);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red+=r;
            blue+=b;
            green+=g;

	    r = 0;
            g = 0;
            b = 0;
            pixel = get_pixel(image_surface,j+1,i+1);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red+=r;
            blue+=b;
            green+=g;

	    r = 0;
            g = 0;
            b = 0;

            pixel = get_pixel(image_surface,j,i+1);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red+=r;
            blue+=b;
            green+=g;

            red1 = red/4;
            green1 = green/4;
            blue1 = blue/4;

	    pixel = SDL_MapRGB(image_surface->format, red1, green1, blue1);
            put_pixel(image_surface, j, i, pixel);

	    for(j = 1; j<width-1; j++)
	    {

		    red= 0;
		    green = 0;
		    blue = 0;

		    red1 = 0;
		    green1 = 0;
		    blue1 = 0;

		    r = 0;
                    g = 0;
                    b = 0;
		    pixel_00 = get_pixel(image_surface, j, i);
		    Uint8 red,green,blue;
		    SDL_GetRGB(pixel_00, image_surface->format, &red, &green, &blue);

		    red += red1;
		    green+=green1;
		    blue += blue1;


		    r = 0;
                    g = 0;
                    b = 0;
		    pixel = get_pixel(image_surface,j-1,i);
		    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
		    red+=r;
		    blue+=b;
		    green+=g;

		    r = 0;
                    g = 0;
                    b = 0;
		    pixel = get_pixel(image_surface,j-1,i+1);
                    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                    red+=r;
                    blue+=b;
                    green+=g;

		    r = 0;
                    g = 0;
                    b = 0;
		    pixel = get_pixel(image_surface,j,i+1);
                    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                    red+=r;
                    blue+=b;
                    green+=g;

		    r = 0;
                    g = 0;
                    b = 0;
		    pixel = get_pixel(image_surface,j+1,i+1);
                    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                    red+=r;
                    blue+=b;
                    green+=g;

		    r = 0;
                    g = 0;
                    b = 0;
		    pixel = get_pixel(image_surface,j+1,i);
                    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                    red+=r;
                    blue+=b;
                    green+=g;

		    red1 = red/6;
		    green1 = green/6;
		    blue1 = blue/6;

		    pixel = SDL_MapRGB(image_surface->format, red1, green1, blue1);
		    put_pixel(image_surface, j, i, pixel);
	    }

	    red= 0;
            green = 0;
	    blue = 0;

	    red1= 0;
	    green1=0;
	    blue1=0;

	    r = 0;
            g = 0;
            b = 0;
	    j = width-1;
	    pixel_00 = get_pixel(image_surface, j, i);
            SDL_GetRGB(pixel_00, image_surface->format, &red1, &green1, &blue1);


	    red += red1;
	    green+=green1;
	    blue += blue1;


            r = 0;
            g = 0;
            b = 0;
	    pixel = get_pixel(image_surface,j-1,i);
	    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
	    red+=r;
	    blue+=b;
	    green+=g;

	    r = 0;
            g = 0;
            b = 0;
	    pixel = get_pixel(image_surface,j-1,i+1);
	    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
	    red+=r;
	    blue+=b;
	    green+=g;

	    r = 0;
            g = 0;
            b = 0;
	    pixel = get_pixel(image_surface,j,i+1);
	    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
	    red+=r;
	    blue+=b;
	    green+=g;

	    red1 = red/4;
	    green1 = green/4;
	    blue1 = blue/4;

	    pixel = SDL_MapRGB(image_surface->format, red1, green1, blue1);
            put_pixel(image_surface, j, i, pixel);
    }
    return image_surface;
}

SDL_Surface* Array_Blur(SDL_Surface* image_surface, int width, int height)
{


	for(int i = 1; i<height-1;i++)
    {

	    int j = 0;
            Uint32 pixel_00 = get_pixel(image_surface, j, i);
            Uint8 red1,green1,blue1;
            SDL_GetRGB(pixel_00, image_surface->format, &red1, &green1, &blue1);

            int red,green,blue;
	    red = 0;
	    green = 0;
	    blue = 0;

            red+=red1;
            green+=green1;
            blue+=blue1;

            Uint8 r,g,b;
	    r = 0;
            g = 0;
            b = 0;

            Uint32 pixel = get_pixel(image_surface,j+1,i);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red+=r;
            blue+=b;
            green+=g;

	    r = 0;
            g = 0;
            b = 0;
            pixel = get_pixel(image_surface,j+1,i+1);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red+=r;
            blue+=b;
            green+=g;

	    r = 0;
            g = 0;
            b = 0;
            pixel = get_pixel(image_surface,j,i+1);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red+=r;
            blue+=b;
            green+=g;

	    r = 0;
            g = 0;
            b = 0;
	    pixel = get_pixel(image_surface,j+1,i-1);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red+=r;
            blue+=b;
            green+=g;

	    r=0;
	    g=0;
	    b=0;
	    pixel = get_pixel(image_surface,j,i-1);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red+=r;
            blue+=b;
            green+=g;


            red1 = red/6;
            green1 = green/6;
            blue1 = blue/6;

	    pixel = SDL_MapRGB(image_surface->format, red1, green1, blue1);
            put_pixel(image_surface, j, i, pixel);

            for(j = 1; j<width-1; j++)
	    {

		    red= 0;
                    green = 0;
                    blue = 0;

		    red1=0;
		    blue1=0;
		    green1=0;


		    pixel_00 = get_pixel(image_surface, j, i);
		    SDL_GetRGB(pixel_00, image_surface->format, &red1, &green1, &blue1);


                    red+=red1;
                    green+=green1;
                    blue+=blue1;


		    r = 0;
		    g = 0;
	    	    b = 0;
                    pixel = get_pixel(image_surface,j-1,i);
                    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                    red+=r;
                    blue+=b;
                    green+=g;

		    r = 0;
		    g = 0;
		    b = 0;
                    pixel = get_pixel(image_surface,j-1,i+1);
                    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                    red+=r;
                    blue+=b;
                    green+=g;

		    r = 0;
                    g = 0;
                    b = 0;
                    pixel = get_pixel(image_surface,j,i+1);
                    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                    red+=r;
                    blue+=b;
                    green+=g;

		    r = 0;
                    g = 0;
                    b = 0;
                    pixel = get_pixel(image_surface,j+1,i+1);
                    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                    red+=r;
                    blue+=b;
                    green+=g;


		    r = 0;
                    g = 0;
                    b = 0;
                    pixel = get_pixel(image_surface,j+1,i);
                    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                    red+=r;
                    blue+=b;
                    green+=g;

		    r = 0;
                    g = 0;
                    b = 0;
		    pixel = get_pixel(image_surface,j+1,i-1);
                    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                    red+=r;
                    blue+=b;
                    green+=g;



		    r = 0;
                    g = 0;
                    b = 0;
		    pixel = get_pixel(image_surface,j,i-1);
                    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                    red+=r;
                    blue+=b;
                    green+=g;

		    r = 0;
                    g = 0;
                    b = 0;
		    pixel = get_pixel(image_surface,j-1,i-1);
                    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                    red+=r;
                    blue+=b;
                    green+=g;


                    red1 = red/9;
                    green1 = green/9;
                    blue1 = blue/9;

		    pixel = SDL_MapRGB(image_surface->format, red1, green1, blue1);
                    put_pixel(image_surface, j, i, pixel);

	    }

	    red= 0;
	    green = 0;
	    blue = 0;

	    red1=0;
	    blue1=0;
	    green1=0;

	    j = width-1;
	    pixel_00 = get_pixel(image_surface, j, i);
	    SDL_GetRGB(pixel_00, image_surface->format, &red1, &green1, &blue1);

	    red+=red1;
	    green+=green1;
	    blue+=blue1;




	    r = 0;
	    g = 0;
	    b = 0;
            pixel = get_pixel(image_surface,j-1,i);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red+=r;
            blue+=b;
            green+=g;

	    r = 0;
            g = 0;
            b = 0;
            pixel = get_pixel(image_surface,j-1,i+1);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red+=r;
            blue+=b;
            green+=g;

	    r = 0;
            g = 0;
            b = 0;
            pixel = get_pixel(image_surface,j,i+1);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red+=r;
            blue+=b;
            green+=g;

	    r = 0;
            g = 0;
            b = 0;
	    pixel = get_pixel(image_surface,j+1,i-1);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red+=r;
            blue+=b;
            green+=g;


	    r = 0;
            g = 0;
            b = 0;
	    pixel = get_pixel(image_surface,j,i-1);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            red+=r;
            blue+=b;
            green+=g;



            red1 = red/6;
            green1 = green/6;
            blue1 = blue/6;
	    pixel = SDL_MapRGB(image_surface->format, red1, green1, blue1);

            put_pixel(image_surface, j, i, pixel);

    }

    return image_surface;
}


float Local_Average2(int i, int j, SDL_Surface* imageBlur)
{
	int width =  imageBlur->w;
        int height = imageBlur->h;

	int size = 25;

	float Average = 0.0f;
	
	Uint8 r  = 0;

	int image_i = i-size/2;
	int image_j = j - size / 2 ;

	for(int x = 0; x < size; x++,image_i++)
        {
                for(int y = 0 ; y< size ; y++,image_j++)
                {
                        if(image_i >= 0&& image_i < width && image_j >= 0 && image_j < height)
                        {
                                Uint32 pixel = get_pixel(imageBlur,image_i,image_j);
                                SDL_GetRGB(pixel, imageBlur->format, &r,&r,&r);
                                Average += r;
                        }
                }
                image_j = j - size/2;
        }
	float square_of_size = (size*size);
	Average = Average/square_of_size;
	return (int)Average;

}

int Sauvola(int i, int j, SDL_Surface* imageBlur)
{
	printf("%d\n",i);
	
        int width =  imageBlur->w;
	int height = imageBlur->h;

        int size = 21;

        float average = Local_Average2(i,j,imageBlur);
	float standard_deviation = 0.0f;
	float Threshold = 0.0f;
        
	Uint8 r = 0;

	int image_i = i - size / 2;
	int image_j = j - size / 2;
	for(int x = 0; x < size; x++,image_i++)
        {
                for(int y = 0 ; y< size ; y++,image_j++)
                {
                        if(image_i >= 0&& image_i < width && image_j >= 0 && image_j < height)
                        {
                                Uint32 pixel = get_pixel(imageBlur,image_i,image_j);
                                SDL_GetRGB(pixel, imageBlur->format, &r,&r,&r); 
				
				standard_deviation += ((r - average)*(r - average));

                                
                        }
                }
		image_j = j - size/2;
        }
	float square_of_size = (size*size);
	standard_deviation = (standard_deviation/(square_of_size));
        standard_deviation = sqrt(standard_deviation);

        Threshold = average * (1+ 0.5*((standard_deviation/128) - 1));
	return (int)Threshold;
}

void Grayscale(int height, int width,SDL_Surface* image_surface)
{
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
                Uint32 pixel = get_pixel(image_surface, j, i);
                Uint8 r, g, b;
                SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                int average = (0.2125*r + 0.7154*g + 0.0721*b); //grayscale
                pixel = SDL_MapRGB(image_surface->format, average, average, average);
                put_pixel(image_surface, j, i, pixel);

        }
    }

}

void increase_Contrast(SDL_Surface* image_surface)
{
        int height = image_surface ->h;
        int width = image_surface ->w;

        for(int i = 0; i<height; i++)
        {
                for(int j = 0; j<width; j++)
                {
                        Uint32 pixel = get_pixel(image_surface, j, i);
                        Uint8 r, g, b;
                        SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                        double result = r;
                        result = 0.5+0.5*sin(M_PI*((result/255)-0.5));
                        r = result*255;
                        pixel = SDL_MapRGB(image_surface->format,r,r,r);
                        put_pixel(image_surface, j, i, pixel);
                }
        }

}


void Make_image_black(SDL_Surface* image_surface)
{
    int width = image_surface->w;
    int height = image_surface->h;

    for(int i = 3; i<height-5; i+=2)
    {
        for(int j = 3; j<width-5; j+=2)
        {
                Uint32 pixel = get_pixel(image_surface, j, i);
                Uint8 r,g,b;
                SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

		if(r == 0)
		{
			pixel = get_pixel(image_surface,j+1,i);
			r = 0;
			SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
			pixel = SDL_MapRGB(image_surface->format, 0, 0, 0);
			put_pixel(image_surface, j+1, i, pixel);

			pixel = get_pixel(image_surface,j,i-1);
                        r = 0;
                        SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
                        pixel = SDL_MapRGB(image_surface->format, 0, 0, 0);
			put_pixel(image_surface, j,i-1, pixel);


			pixel = get_pixel(image_surface,j-1,i-1);
                        r = 0;
                        SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
                        pixel = SDL_MapRGB(image_surface->format, 0, 0, 0);
                        put_pixel(image_surface, j-1, i-1, pixel);


			pixel = get_pixel(image_surface,j+1,i-1);
                        r = 0;
                        SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
                        pixel = SDL_MapRGB(image_surface->format, 0, 0, 0);
                        put_pixel(image_surface, j+1, i-1, pixel);


			pixel = get_pixel(image_surface,j-1,i);
                        r = 0;
                        SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
                        pixel = SDL_MapRGB(image_surface->format, 0, 0, 0);
                        put_pixel(image_surface, j-1,i, pixel);


			pixel = get_pixel(image_surface,j+1,i+1);
                        r = 0;
                        SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
                        pixel = SDL_MapRGB(image_surface->format, 0, 0, 0);
                        put_pixel(image_surface, j+1, i+1, pixel);


			pixel = get_pixel(image_surface,j,i+1);
                        r = 0;
                        SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
                        pixel = SDL_MapRGB(image_surface->format, 0, 0, 0);
                        put_pixel(image_surface, j, i+1, pixel);


			pixel = get_pixel(image_surface,j-1,i+1);
                        r = 0;
                        SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
                        pixel = SDL_MapRGB(image_surface->format, 0, 0, 0);
                        put_pixel(image_surface, j-1,i+1, pixel);
		}
        }
    }
}

SDL_Surface* IncreaseContrast_With_Coef(SDL_Surface *image)
{
    Uint32 pixel;
    Uint8 r,g,b;
    double intensity = 0;
    double total = 0;
    float coef;
    double average;

    //calcul the coefficient
    for (int i = 0; i < image->w; i++)
    {
        for (int j = 0; j < image->h; j++)
    	{
        	pixel = get_pixel(image,i,j);
        	SDL_GetRGB(pixel, image->format, &r, &g, &b);
            	if ((r + g + b) / 3 > 20) 
            	{
            		intensity += (r +  g +  b) / 3;
            		total++;
        	}
    	}
    }

    average = intensity / total;
    if (average > 178)
        coef = 1 + 0.3 + (1 / average);
    else
    	coef = 1 - 0.5 - (1 / average);
    
    //put the new value to the pixel related to the coefficient in the image
    for (int i = 0; i < image->w; i++)
    {
    	for (int j = 0; j < image->h; j++)
    	{
        	pixel = get_pixel(image,i,j);
        	SDL_GetRGB(pixel, image->format, &r, &g, &b);
          
        	r = 255 * powf((float) r / 255, coef);
        	g = 255 * powf((float) g / 255, coef);
        	b = 255 * powf((float) b / 255, coef);

        	pixel = SDL_MapRGB(image->format, r, g, b);
        	put_pixel(image, i, j, pixel);  
   	}
    }
  
    return image;
}

SDL_Surface* Resize_image(SDL_Surface *image, int weight, int height)
{
	double zoomX = 1;
       	double zoomY = 1;

	if(image->w > weight)
	{
		zoomX = weight/(float)image->w;
		zoomY = zoomX;
	}

	if(image->h > height)
	{
		zoomY = height/(float)image->h;
		zoomX = zoomY;
	}

	SDL_Surface *new_image =  zoomSurface(image,zoomX,zoomY,0);
	return new_image;
}

void BlackandWhite(int height,int width,SDL_Surface* image_surface,SDL_Surface* Grayscale_image)
{
    for(int i = 0; i<width; i++)
    {
        for(int j = 0; j<height; j++)
        {
                Uint32 pixel = get_pixel(image_surface, i, j);
                Uint8 r,g,b;
                SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                //int Treshold = Sauvola(i,j,Grayscale);
                if(r>0.92*Local_Average2(i,j,Grayscale_image)) // black or white

                {
                        r = 255;
                }

                else
                {
                        r = 0;
                }
                //printf("%d \n",i);
                pixel = SDL_MapRGB(image_surface->format, r, r, r);
                put_pixel(image_surface, i, j, pixel);

        }
    }
}



