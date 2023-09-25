#include "daisy_petal.h"
#include "terrarium.h"

#include "sample.h"

#define BATCH_SIZE 4

daisy::DaisyPetal hw;
daisy::Switch fsw = hw.switches[terrarium::Terrarium::FOOTSWITCH_1];
daisy::Led led;

bool play = false;
unsigned int wav_pointer = sizeof(daisy::WAV_FormatTypeDef);

static void audioCallback(daisy::AudioHandle::InputBuffer in,
                          daisy::AudioHandle::OutputBuffer out,
                          size_t batch_size) {
  hw.ProcessAllControls();
  led.Update();
  if (fsw.RisingEdge()) {
    play = !play;
    led.Set(play);
  }
  daisy::WAV_FormatTypeDef wav_header;
  memcpy(&wav_header, chrome_sample_wav, sizeof(daisy::WAV_FormatTypeDef));
  if (play && wav_pointer + 1 < CHROME_SAMPLE_WAV_LEN) {
    wav_pointer++;
    for (size_t i = 0; i < batch_size; i++) {
      out[0][i] = chrome_sample_wav[wav_pointer];
    }
  }
}

int main(void) {
  hw.Init();

  hw.SetAudioBlockSize(BATCH_SIZE);

  led.Init(hw.seed.GetPin(terrarium::Terrarium::LED_1), false);
  led.Set(false);

  hw.StartAdc();
  hw.StartAudio(audioCallback);

  while (1) {
    daisy::System::Delay(10);
  }
}