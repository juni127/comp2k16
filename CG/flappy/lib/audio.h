#define BITS 8

#define REPETIR_AUDIO 1

mpg123_handle *mh;
unsigned char *buffer;
size_t buffer_size;
size_t done;
int err;

int driver, block = 0;
ao_device *dev;

ao_sample_format format;
int channels, encoding;
long rate;

pthread_t thread_sfx;
 
void inicia_audio(){
	ao_initialize();
	driver = ao_default_driver_id();
	mpg123_init();
	mh = mpg123_new(NULL, &err);
	buffer_size = mpg123_outblock(mh);
	buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));
}

void * rodar(void * pointer){
	/* decode and play */
    int flag = 0;
    while (flag != 12){
        if(!block){
            flag = mpg123_read(mh, buffer, buffer_size, &done);
            ao_play(dev, buffer, done);
        }
    }
}

void abrir_audio(char * caminho){
    block = 1;
    mpg123_open(mh, caminho);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);
}

void finaliza_audio(){
	free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();
}

void tocar_audio(){
    block = 0;
    pthread_cancel(&thread_sfx);
    pthread_create(&thread_sfx, NULL, rodar, NULL);
}