#include "microphone.h"


Microphone::Microphone(QObject *parent) : QThread(parent)
{
    periods = 2;
    buffer_frames = (4096*periods)>>2;
    //fprintf(stderr ,"The requested frame size is: %d\n",buffer_frames);
    //frequency = 44100;
    frequency = RECORDING_FREQUENCY;

    mySS = new(safe_sound);

    my_safe_encode_audio_context.mutex.lock();
    my_safe_encode_audio_context.put_data = false;
    my_safe_encode_audio_context.nb_samples = 0;
    my_safe_encode_audio_context.mutex.unlock();

    context_data_filled_atleast_once = 0;

}

void Microphone::run(){
// Do main stuff here.
    init();

    unsigned char* temp_audio_buffer = (unsigned char *)malloc(periodsize);

    my_safe_encode_audio_context.mutex.lock();
    my_safe_encode_audio_context.nb_samples = periodsize;
    my_safe_encode_audio_context.mutex.unlock();

    mySS->sound = (unsigned char *)malloc(periodsize);

    while(continue_loop)
    {

        while ((pcmreturn = snd_pcm_readi(pcm_handle, temp_audio_buffer, periodsize>>2)) < 0) {
          fprintf(stderr, "Ops!\n");
          snd_pcm_prepare(pcm_handle);
          fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Overrun >>>>>>>>>>>>>>>\n");

        }

        mySS->mutex.lock();
        memcpy(mySS->sound,temp_audio_buffer,periodsize);
        //mySS->cond.wakeAll();
        mySS->mutex.unlock(); //maybe we do not want our video thread to sleep

        emit soundAvailable(mySS);

        if(context_data_filled_atleast_once == 0)
        {
            encoder_audio_buffer =(unsigned char*)malloc(periodsize); //memory leak possible as all the data might not be freed by the encoder
            memcpy(encoder_audio_buffer, temp_audio_buffer, periodsize); //use wait condition

            my_safe_encode_audio_context.mutex.lock();
            my_safe_encode_audio_context.data = encoder_audio_buffer;
            my_safe_encode_audio_context.put_data = true;
            my_safe_encode_audio_context.mutex.unlock(); //more like a wait condition here just to make sure all data is freed,

            emit give_encode_audio_context(&my_safe_encode_audio_context);
            //emit encode_video_signal();
            context_data_filled_atleast_once = 1;

        }
        else
        {
             my_safe_encode_audio_context.mutex.lock();  //audio encoding is taking too long.
            //my_safe_encode_video_context.data = encoder_image_buffer; (redundant to do it here)
            memcpy(encoder_audio_buffer, temp_audio_buffer, periodsize); //use wait condition
            my_safe_encode_audio_context.put_data = true;
            my_safe_encode_audio_context.cond.wakeOne();
            my_safe_encode_audio_context.mutex.unlock(); //more like a wait condition here just to make sure all data is freed,

        }

        //left = *sound<<8 & *(sound + 1);
        //right = *(sound+2) & *(sound + 3);
       // fprintf(stderr,"Left: %d, Right: %d \n", left, right );


        qDebug("Period size is: %d \n",periodsize);

    }

//Close everything
        //free(sound);
        snd_pcm_drain(pcm_handle);
        if(snd_pcm_close(pcm_handle))
        {
            free(pcm_handle);

        }


}
Microphone::~Microphone()
{

}
void Microphone::init()
{
    fprintf(stderr, "Initialising Microphone! \n");


    unsigned int frequency_exact;
    snd_pcm_stream_t stream = SND_PCM_STREAM_CAPTURE;
    snd_pcm_hw_params_t *hwparams;
    char *pcm_name;
    pcm_name = strdup("plughw:0,0");
    snd_pcm_hw_params_alloca(&hwparams);

    if (snd_pcm_open(&pcm_handle, pcm_name, stream, 0) < 0) {
      fprintf(stderr, "Error opening Capture PCM device %s\n", pcm_name);
      exit(-1);
    }
   /* Init hwparams with full configuration space */
    if (snd_pcm_hw_params_any(pcm_handle, hwparams) < 0) {
      fprintf(stderr, "Can not configure this PCM device.\n");
      exit(-1);
    }


    if (snd_pcm_hw_params_set_access(pcm_handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
      fprintf(stderr, "Error setting access.\n");
      exit(-1);
    }



    /* Set sample format */
    if (snd_pcm_hw_params_set_format(pcm_handle, hwparams, SND_PCM_FORMAT_S16_LE) < 0) {
      fprintf(stderr, "Error setting format.\n");
      exit(-1);
    }

    frequency_exact = frequency;
    if (snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, &frequency_exact, 0) < 0) {
      fprintf(stderr, "Error setting rate.\n");
      exit(-1);
    }

    //Handle message in case frequency is not same

    /* Set number of channels */
    if (snd_pcm_hw_params_set_channels(pcm_handle, hwparams, 2) < 0) {
      fprintf(stderr, "Error setting channels.\n");
      exit(-1);
    }

    /* Set number of periods. Periods used to be called fragments. */
    if (snd_pcm_hw_params_set_periods(pcm_handle, hwparams, periods, 0) < 0) {
      fprintf(stderr, "Error setting periods.\n");
      exit(-1);
    }


    /* Set buffer size (in frames). The resulting latency is given by */
    /* latency = periodsize * periods / (rate * bytes_per_frame)     */
    snd_pcm_uframes_t buffer_frames_exact = buffer_frames;
    if (snd_pcm_hw_params_set_buffer_size_near(pcm_handle, hwparams, &buffer_frames_exact) < 0) {
      fprintf(stderr, "Error setting buffersize.\n");
      exit(-1);
    }
    if(buffer_frames!=buffer_frames_exact)
    {
        printf("The desired buffer size of %d could not be set, \n going with nearest size of  %d \n",buffer_frames,buffer_frames_exact);
    }
    buffer_frames = buffer_frames_exact; //Make class property.
    periodsize = (buffer_frames << 2)/periods; // Might give errors for some

      /* Apply HW parameter settings to */
    /* PCM device and prepare device  */
    if (snd_pcm_hw_params(pcm_handle, hwparams) < 0) {
      fprintf(stderr, "Error setting HW params.\n");
      exit(-1);
    }

    //Free memory here
    //free(hwparams);
    //free(pcm_name);

}

void Microphone::stopThread()
{


continue_loop = false; // allow the run command finish by ending while
this->wait();          //wait for the thread to finish
qDebug("The audio thread has successfully finished");


}

void Microphone::startThread()
{
        qDebug()<<"The audio thread is starting!";
        continue_loop = true;
        this->start();
}




