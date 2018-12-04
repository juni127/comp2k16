//DevIL - Imagens
#include<IL/il.h>

#define MAX_IMAGE 32

GLuint texid[MAX_IMAGE];
ILuint image[MAX_IMAGE];


// Inicia o DevIL
void inicia_textura(){
    if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION){
        printf("wrong DevIL version \n");
        return -1;
    }
    ilInit(); 

    ilGenImages(MAX_IMAGE, image); /* Generation of one image name */
    glGenTextures(MAX_IMAGE, texid); /* Texture name generation */
}

/* Load an image using DevIL and return the devIL handle (-1 if failure) */
int loadImage(char *filename)
{
    ILboolean success; 
    success = ilLoadImage(filename); /* Loading of the image filename by DevIL */
    success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); 
 
    return image;
}

void abrir_imagem(char * path, int slot){
    /* load the file picture with DevIL */
    ilBindImage(image[slot]); /* Binding of image name */
    loadImage(path);
 
    /* OpenGL texture binding of the image loaded by DevIL  */
    glBindTexture(GL_TEXTURE_2D, texid[slot]); /* Binding of texture name */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
    0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */

}

void escolher_imagem(int slot){
    /* load the file picture with DevIL */
    ilBindImage(image[slot]); /* Binding of image name */
 
    /* OpenGL texture binding of the image loaded by DevIL  */
    glBindTexture(GL_TEXTURE_2D, texid[slot]); /* Binding of texture name */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
    0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */    
}