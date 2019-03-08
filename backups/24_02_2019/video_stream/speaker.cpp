#include "speaker.h"

Speaker::Speaker(QObject *parent) :
    QObject(parent)
{
    periods = 2;
    buffer_frames = (8192*periods)>>2;
    frequency = 44100;
    started = false;

}
Speaker::~Speaker()
{
}

void Speaker::start()
{
   init();
   started = true;
}
bool Speaker::isStarted()
{
    return started;
}
void Speaker::stop()
{
    snd_pcm_drain(pcm_handle);
    if(snd_pcm_close(pcm_handle))
    {
        free(pcm_handle);

    }
    started = false;
}

void Speaker::playSound(safe_sound  *sound)
{
    sound->mutex.lock();
    while ((pcmreturn = snd_pcm_writei(pcm_handle, sound->sound, frames)) < 0 && started) {
     snd_pcm_prepare(pcm_handle);
     //add wait condition here
     sound->cond.wait(&sound->mutex);
    fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>>>>\n");
    }
    sound->mutex.unlock();


}

void Speaker::init()
{

    fprintf(stderr, "Initialising Speaker! \n");


    unsigned int frequency_exact;
    snd_pcm_stream_t stream = SND_PCM_STREAM_PLAYBACK;
    snd_pcm_hw_params_t *hwparams;
    char *pcm_name;
    pcm_name = strdup("plughw:0,0");
    snd_pcm_hw_params_alloca(&hwparams);

    if (snd_pcm_open(&pcm_handle, pcm_name, stream, 0) < 0) {
      fprintf(stderr, "Error opening Playback PCM device %s\n", pcm_name);
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
    frames = periodsize >> 2;

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

