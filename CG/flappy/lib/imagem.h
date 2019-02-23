void abrirImagem(GLuint * texid, ILuint * image, char * path){
    ilGenImages(1, image); /* Generation of one image name */
    glGenTextures(1, texid);

    ilBindImage(*image); /* Binding of image name */
    ilLoadImage(path); /* Loading of the image filename by DevIL */
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); 
}

void selecionarImagem(GLuint texid, ILuint image){
    /* OpenGL texture binding of the image loaded by DevIL  */
    ilBindImage(image); /* Binding of image name */
    glBindTexture(GL_TEXTURE_2D, texid); /* Binding of texture name */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
    0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */
}

void mostrarImagem(float x1, float x2, float y1, float y2, float z1, float z2){
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(x1, y1, z1);
        glTexCoord3i(0, 0, 0); glVertex3f(x1, y2, z1);
        glTexCoord3i(1, 0, 0); glVertex3f(x2, y2, z2);
        glTexCoord3i(1, 1, 0); glVertex3f(x2, y1, z2);
    glEnd();
}