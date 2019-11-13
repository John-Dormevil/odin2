#pragma once

//#include "../pluginconstants.h"
//#include "../synthfunctions.h"
#ifndef BENCHMARK
#include "../JuceLibraryCode/JuceHeader.h"
#endif

#include <cmath>

#define FILTER_FC_MIN 80        // 80Hz
#define FILTER_FC_MAX 18000     // 18kHz
#define FILTER_FC_DEFAULT 10000 // 10kHz
#define FILTER_Q_DEFAULT 0.707  // Butterworth
#define FILTER_ENV_MOD_SEMITONES_MAX 64
#define FILTER_FREQ_MOD_RANGE_SEMITONES 64

// Filter Abastract Base Class for all filters
class Filter {
public:
	Filter(void);
	~Filter(void);

	inline float pitchShiftMultiplier(float p_semitones) {
		//0.05776226504 = ln(2)/12
		//apparently pow(a,b) is calculated as exp(ln(a)*b), hence this is faster
		return juce::dsp::FastMathApproximations::exp(0.057762f * p_semitones);
		//return std::exp(0.05776226504 * p_semitones);
	}
	float fasttanh(float p_input, float p_tanh_factor) {
// idea2: use curveable x^3
// tanh(3x)
#ifndef BENCHMARK
		return juce::dsp::FastMathApproximations::tanh(p_tanh_factor * p_input);
#else
		return std::tanh(p_tanh_factor * p_input);
#endif
	}

	inline void applyOverdrive(double &pio_input, float p_tanh_factor = 3.5) {
		float overdrive_modded = m_overdrive + 2 * (*m_saturation_mod);
		overdrive_modded       = overdrive_modded < 0 ? 0 : overdrive_modded;
		if (overdrive_modded > 0.01f && overdrive_modded < 1.f) {
			// interpolate here so we have possibility of pure linear Processing
			pio_input = pio_input * (1. - overdrive_modded) + overdrive_modded * fasttanh(pio_input, p_tanh_factor);
		} else if (overdrive_modded >= 1.f) {
			pio_input = fasttanh(overdrive_modded * pio_input, p_tanh_factor);
		}
	}
	double m_freq_base;
	double m_res_base;

	int m_MIDI_note     = 0;
	int m_MIDI_velocity = 0;

	float m_kbd_mod_amount = 0;
	float m_vel_mod_amount = 0;
	float m_env_mod_amount = 0;
	float m_env_value      = 0.f;

	// --- for an aux filter specific like SEM BSF
	//     control or paasband gain comp (Moog)
	double m_aux_control;
	// --- for NLP - Non Linear Procssing
	// bool m_NLP;
	double m_overdrive = 0.;

	virtual void setFreqModPointer(float *p_pointer) {
		m_freq_mod = p_pointer;
	}
	virtual void setResModPointer(float *p_pointer) {
		m_res_mod = p_pointer;
	}
	virtual void setVolModPointer(float *p_pointer) {
		m_vol_mod = p_pointer;
	}
	virtual void setVelModPointer(float *p_pointer) {
		m_vel_mod_mod = p_pointer;
	}
	virtual void setKbdModPointer(float *p_pointer) {
		m_kbd_mod_mod = p_pointer;
	}
	virtual void setSaturationModPointer(float *p_pointer) {
		m_saturation_mod = p_pointer;
	}
	virtual void setEnvModPointer(float *p_pointer) {
		m_env_mod_mod = p_pointer;
	}

public:
	virtual double doFilter(double xn) = 0;
	inline virtual void setSampleRate(double d) {
		m_samplerate = d;
		m_one_over_samplerate = 1.f / d;
	}
	virtual void reset();
	virtual void setResControl(double p_res) {
	}

	inline virtual void update() {

		float kbd_modded = m_kbd_mod_amount + *m_kbd_mod_mod < 0 ? 0 : m_kbd_mod_amount + *m_kbd_mod_mod;
		float vel_modded = m_vel_mod_amount + *m_vel_mod_mod < 0 ? 0 : m_vel_mod_amount + *m_vel_mod_mod;

		m_freq_modded = m_freq_base *
		                pitchShiftMultiplier(*m_freq_mod * FILTER_FREQ_MOD_RANGE_SEMITONES + kbd_modded * m_MIDI_note +
		                                     (m_env_value * (m_env_mod_amount + *m_env_mod_mod) +
		                                      vel_modded * (float)m_MIDI_velocity / 127.f) *
		                                         FILTER_ENV_MOD_SEMITONES_MAX);

		if (m_freq_modded > FILTER_FC_MAX)
			m_freq_modded = FILTER_FC_MAX;
		if (m_freq_modded < FILTER_FC_MIN)
			m_freq_modded = FILTER_FC_MIN;
	}

	double m_mod_frequency = 0;

protected:
	float *m_vol_mod;
	float *m_res_mod;
	float *m_freq_mod;
	float *m_saturation_mod = &m_mod_dummy_zero;
	float *m_env_mod_mod    = &m_mod_dummy_zero;
	float *m_vel_mod_mod    = &m_mod_dummy_zero;
	float *m_kbd_mod_mod    = &m_mod_dummy_zero;

	float m_mod_dummy_zero = 0;

	double m_samplerate;
	double m_one_over_samplerate;
	double m_freq_modded;
	double m_res_modded;
};
