//DevIL - Imagens
#include<IL/il.h>

#define MAX_IMAGE 32

GLuint texid[MAX_IMAGE];
int    image[MAX_IMAGE];


// Inicia o DevIL
void initDevil(){
    if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION){
        printf("wrong DevIL version \n");
        return -1;
    }
    ilInit(); 
}

/* Load an image using DevIL and return the devIL handle (-1 if failure) */
int loadImage(char *filename)
{
    ILboolean success; 
    ILuint image; 
 
    ilGenImages(1, &image); /* Generation of one image name */
     ilBindImage(image); /* Binding of image name */
     success = ilLoadImage(filename); /* Loading of the image filename by DevIL */
 
    if (success) /* If no error occured: */
    {
        /* Convert every colour component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
           success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); 
 
        if (!success)
           {
                 return -1;
           }
    }
    else
        return -1;
 
    return image;
}

void openAndBind(char * path, int slot){
    /* load the file picture with DevIL */
    image[slot] = loadImage(path);
    if (image[slot] == -1 )
    {
        //printf("Can't load picture file %s by DevIL \n", argv[1]);
        return -1;
    }
 
    /* OpenGL texture binding of the image loaded by DevIL  */
    glGenTextures(1, &(texid[slot])); /* Texture name generation */
    glBindTexture(GL_TEXTURE_2D, texid[slot]); /* Binding of texture name */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
    0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */
}