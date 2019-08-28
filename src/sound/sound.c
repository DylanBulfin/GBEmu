#include <portaudio.h>
#include <stddef.h>
#include <stdio.h>

#define SAMPLE_RATE 65536

PaStream *stream;
PaError err;

typedef struct
{
    float HIGH;
    float LOW;
}
paTestData;

int pabuffermaker(const void *inputBuffer, void *outputBuffer,
		  unsigned long framesPerBuffer,
		  const PaStreamCallbackTimeInfo* timeInfo,
		  PaStreamCallbackFlags statusFlags,
		  void *userData ) {
    
    paTestData *data = (paTestData*)userData;


    int *out = (int*)outputBuffer;
    unsigned int i;
    (void) inputBuffer; /* Prevent unused variable warning. */


/* Caution:  cycle_count / 2 must be less than framesPerBuffer or else you will have a distorted sqaure wave */
    int cycle_position = 0; //track position on cycle
    int cycle_count = 64; //change frequency by altering this value. lower values = higher pitch and vice-versa

    for( i=0; i<framesPerBuffer; i++ ){
	if(cycle_position <= cycle_count){ /*Write Low Value to output buffer*/
	    *out++ = data->LOW; /*increment output buffer counter and write Low Value*/
	    cycle_position++; /*increment position on cycle*/
	}
	

	else{   /*Write HIGH Value to output buffer*/
	    *out++ = data->HIGH; /*increment output buffer counter and write High Value*/
	    cycle_position++; /*increment position on cycle*/
	    if(cycle_position == cycle_count * 2)cycle_position = 0; /*reset position on cycle*/
	}
    }

    return 0;

}

static paTestData data;

void test_method() {
    data.HIGH = 10.f;
    data.LOW = -10.f;

    //    err = Pa_Initialize();

    //    err = Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, pabuffermaker, &data);

    //err = Pa_StartStream(stream);

    (void) err;
}

void shutdown_audio() {
    /*
    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error;
    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;
    Pa_Terminate();
    return;
 error:
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    */
}
