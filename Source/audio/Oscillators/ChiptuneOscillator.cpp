#include "ChiptuneOscillator.h"
#include <ctime>

#define NOISE_SEGMENT_LENGTH 30

ChiptuneOscillator::ChiptuneOscillator() {
  m_nr_of_wavetables = NUMBER_OF_WAVETABLES + 9; //+9 for draw tables

  // seed random
  std::srand(std::time(nullptr));
}

ChiptuneOscillator::~ChiptuneOscillator() {}

float ChiptuneOscillator::doOscillate() {
  // if(!m_note_on){
  //    return 0.f;
  /*}else*/
  float vol_mod_factor =
      (*m_vol_mod) > 0 ? 1.f + 4 * (*m_vol_mod) : (1.f + *m_vol_mod);
  vol_mod_factor = vol_mod_factor > VOL_MOD_UPPER_LIMIT ? VOL_MOD_UPPER_LIMIT
                                                        : vol_mod_factor;
  vol_mod_factor = vol_mod_factor > VOL_MOD_UPPER_LIMIT ? VOL_MOD_UPPER_LIMIT
                                                        : vol_mod_factor;

  if (m_generate_noise) {
    return generateChipNoise() * m_volume_factor * vol_mod_factor;
  } else {
    return doWavetable() * m_volume_factor * vol_mod_factor;
  }
}

float ChiptuneOscillator::generateChipNoise() {

  // do 3x oversampling here to avoid aliasing
  m_read_index += m_wavetable_inc;
  if (m_read_index > NOISE_SEGMENT_LENGTH * 3) {
    m_read_index = 0.f;
    m_last_noise_value = std::rand() % 16 - 8;
    m_last_noise_value *= 0.125f;
  }

  // do order 9 IIR filter here for downsampling

  // do downsamplingfilter: The filter coefficients are generated by
  // http://www-users.cs.york.ac.uk/~fisher/cgi-bin/mkfscript
  // Butterworth, LP, order 9, SR 132300, CornerFreq1 40000
  xv[0] = xv[1];
  xv[1] = xv[2];
  xv[2] = xv[3];
  xv[3] = xv[4];
  xv[4] = xv[5];
  xv[5] = xv[6];
  xv[6] = xv[7];
  xv[7] = xv[8];
  xv[8] = xv[9];
  xv[9] = m_last_noise_value * 0.019966841051093;
  yv[0] = yv[1];
  yv[1] = yv[2];
  yv[2] = yv[3];
  yv[3] = yv[4];
  yv[4] = yv[5];
  yv[5] = yv[6];
  yv[6] = yv[7];
  yv[7] = yv[8];
  yv[8] = yv[9];
  yv[9] = (xv[0] + xv[9]) + 9 * (xv[1] + xv[8]) + 36 * (xv[2] + xv[7]) +
          84 * (xv[3] + xv[6]) + 126 * (xv[4] + xv[5]) +
          (-0.0003977153 * yv[0]) + (-0.0064474617 * yv[1]) +
          (-0.0476997403 * yv[2]) + (-0.2185829743 * yv[3]) +
          (-0.6649234123 * yv[4]) + (-1.4773657709 * yv[5]) +
          (-2.2721421641 * yv[6]) + (-2.6598673212 * yv[7]) +
          (-1.8755960587 * yv[8]);
  // next output value = yv[9];
  xv[0] = xv[1];
  xv[1] = xv[2];
  xv[2] = xv[3];
  xv[3] = xv[4];
  xv[4] = xv[5];
  xv[5] = xv[6];
  xv[6] = xv[7];
  xv[7] = xv[8];
  xv[8] = xv[9];
  xv[9] = m_last_noise_value * 0.019966841051093;
  yv[0] = yv[1];
  yv[1] = yv[2];
  yv[2] = yv[3];
  yv[3] = yv[4];
  yv[4] = yv[5];
  yv[5] = yv[6];
  yv[6] = yv[7];
  yv[7] = yv[8];
  yv[8] = yv[9];
  yv[9] = (xv[0] + xv[9]) + 9 * (xv[1] + xv[8]) + 36 * (xv[2] + xv[7]) +
          84 * (xv[3] + xv[6]) + 126 * (xv[4] + xv[5]) +
          (-0.0003977153 * yv[0]) + (-0.0064474617 * yv[1]) +
          (-0.0476997403 * yv[2]) + (-0.2185829743 * yv[3]) +
          (-0.6649234123 * yv[4]) + (-1.4773657709 * yv[5]) +
          (-2.2721421641 * yv[6]) + (-2.6598673212 * yv[7]) +
          (-1.8755960587 * yv[8]);
  // next output value = yv[9];
  xv[0] = xv[1];
  xv[1] = xv[2];
  xv[2] = xv[3];
  xv[3] = xv[4];
  xv[4] = xv[5];
  xv[5] = xv[6];
  xv[6] = xv[7];
  xv[7] = xv[8];
  xv[8] = xv[9];
  xv[9] = m_last_noise_value * 0.019966841051093;
  yv[0] = yv[1];
  yv[1] = yv[2];
  yv[2] = yv[3];
  yv[3] = yv[4];
  yv[4] = yv[5];
  yv[5] = yv[6];
  yv[6] = yv[7];
  yv[7] = yv[8];
  yv[8] = yv[9];
  yv[9] = (xv[0] + xv[9]) + 9 * (xv[1] + xv[8]) + 36 * (xv[2] + xv[7]) +
          84 * (xv[3] + xv[6]) + 126 * (xv[4] + xv[5]) +
          (-0.0003977153 * yv[0]) + (-0.0064474617 * yv[1]) +
          (-0.0476997403 * yv[2]) + (-0.2185829743 * yv[3]) +
          (-0.6649234123 * yv[4]) + (-1.4773657709 * yv[5]) +
          (-2.2721421641 * yv[6]) + (-2.6598673212 * yv[7]) +
          (-1.8755960587 * yv[8]);

  // return only the last of the three samples
  return yv[9];

  return m_last_noise_value;
}

void ChiptuneOscillator::update() {
  m_mod_exp_other = (float)m_chiptune_arp.doArpeggiator();
  WavetableOsc1D::update();
}

void ChiptuneOscillator::setSampleRate(float p_samplerate) {
  WavetableOsc1D::setSampleRate(p_samplerate);
  m_samplerate = p_samplerate;
  m_chiptune_arp.setSampleRate(p_samplerate);
  m_dc_blocking_filter.reset();
}

void ChiptuneOscillator::reset() {

  // call baseclass first
  WavetableOsc1D::reset();

  m_chiptune_arp.reset();
  m_read_index = 0.0;

  // reset downsamplingfilter buffers
  for (int i = 0; i < 10; ++i) {
    xv[i] = yv[i] = 0;
  }
}
