#include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "BlackAndWhite/BlackandWhite.h"
#include "BlackAndWhite/Rotate/rotate.h"
#include <SDL/SDL_rotozoom.h>
#include <stdlib.h>
#include <math.h>
#include "BlackAndWhite/PixelOperation/pixel_operations.h"
#include "string.h"
#include <gtk/gtk.h>
//#include <gtk/gtkx.h>

void dilatation_image(SDL_Surface * image)
{
        int w = image->w;
        int h = image->h;
	int ** M = malloc(w*sizeof(int*));
	for(int i = 0; i < w; i++)
	{
		M[i] = malloc(h*sizeof(int));
	}

        //int M[w][h];
        Uint32 pixel;
        Uint8 r,g,b;
	
        for(int i = 0; i < w;i++)
        {
                for(int j = 0; j < h; j++)
                {
			r = 0;
                        pixel = get_pixel(image,i,j);
                        SDL_GetRGB(pixel,image->format,&r,&g,&b);
                        if(r == 0)
                        {
                                if(i>0)
                                {
                                        M[i-1][j] = 0;
                                }
                                if(i<w-1)
                                        M[i+1][j] = 0;
                                if(j>0)
                                        M[i][j-1] = 0;
                                if(j<h-1)
                                        M[i][j+1] = 0;
                        }
			else
				M[i][j] = 255;
                }

        }
        for(int i = 0; i < w; i++)
        {
                for(int j = 0; j < h; j++)
                {
                        Uint8 new_color = M[i][j];
                        pixel = SDL_MapRGB(image->format,new_color,new_color,new_color);
                        put_pixel(image,i,j,pixel);
                }
        }
	for(int i = 0; i < w; i++)
        {
                free(M[i]);
 	}


	free(M);
}
  


void traitment(gchar *path)
{
    SDL_Surface* image_surface;
    
    //Initialize the SDL
    init_sdl();

    //loading image 
    image_surface = load_image(path);
    SDL_Surface* resize= Resize_image(image_surface,500,700); 
    SDL_Surface* resize_image_surface = resize;
    SDL_SaveBMP(resize_image_surface,"../Black_and_white/Images/ImageResized.bmp");
    SDL_Surface* Grayscale_image = load_image(path);

    int test = image_surface->h;

    //saving image before treatment
    SDL_SaveBMP(image_surface,"../Black_and_white/Images/ImageLoad.bmp");
    printf("imageload saved\n");

    //coordonates
    int width = image_surface->w;
    int height = image_surface->h;


    printf("height = %d and width = %d\n", height, width);
    //Grayscale
    Grayscale(height,width,image_surface);
    Grayscale(height,width,Grayscale_image);

    //grayscale save
    SDL_Surface* resize1 = Resize_image(image_surface,500,700);
    resize_image_surface = resize1; 
    
    SDL_SaveBMP(resize_image_surface,"../Black_and_white/Images/Grayscale_resized.bmp");
    //update_surface(screen_surface,resize_image_surface); 
   
    //first increase contrast
    image_surface = IncreaseContrast_With_Coef(image_surface);
    Grayscale_image = IncreaseContrast_With_Coef(Grayscale_image);

    //save contraste image
    SDL_Surface* resize2 = Resize_image(image_surface,500,700);    
    resize_image_surface = resize2;
    

    SDL_SaveBMP(resize_image_surface,"../Black_and_white/Images/Contrast_resized.bmp");
    SDL_SaveBMP(image_surface,"../Black_and_white/Images/Grayscale.bmp");
 
    if (test < 800)
	    SDL_SaveBMP(image_surface,"../Black_and_white/Images/Grayscale_resized.bmp");
 
    printf("grayscale saved \n");
  
    //Seconde increase Contrast
    increase_Contrast(image_surface);  
    increase_Contrast(Grayscale_image);

    //Black And White
    BlackandWhite(height,width,image_surface,Grayscale_image);
    //saving images after pre-treatment
    SDL_SaveBMP(image_surface,"../Black_and_white/Images/BlackandWhite.bmp");
    

    dilatation_image(image_surface);
    SDL_Surface* resize3 = Resize_image(image_surface,500,700);
    resize_image_surface = resize3;
    SDL_SaveBMP(resize_image_surface,"../Black_and_white/Images/BlackandWhite_resized.bmp");
  
    //update_surface(screen_surface,resize_image_surface);
    SDL_SaveBMP(image_surface,"../Black_and_white/Images/BlackandWhite_dilatation.bmp");

    if (test < 800)
	    SDL_SaveBMP(image_surface,"../Black_and_white/Images/BlackandWhite_resized.bmp");

    printf("image Black & white saved\n");    
 

    //Free the image surface.
    //Free the screen surface.
    SDL_FreeSurface(image_surface);
   // SDL_FreeSurface(resize_image_surface);
    SDL_FreeSurface(Grayscale_image);
    SDL_FreeSurface(resize);
    SDL_FreeSurface(resize1);
    SDL_FreeSurface(resize2);
    SDL_FreeSurface(resize3);
    //SDL_FreeSurface(resize_image_surface);
}

void ResizeRotation()
{
   
   SDL_Surface* image_surface;
   init_sdl();
   image_surface = load_image("../Black_and_white/Images/Rotation.bmp");
   
   SDL_Surface* resize;
   resize  = Resize_image(image_surface, 500, 700);
   
   image_surface = resize;
   SDL_SaveBMP(image_surface, "../Black_and_white/Images/Rotation_resized.bmp");

//   SDL_FreeSurface(resize);
   SDL_FreeSurface(image_surface);

}
