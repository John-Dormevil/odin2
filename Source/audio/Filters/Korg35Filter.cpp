#include "Korg35Filter.h"



Korg35Filter::Korg35Filter(void)
{
    m_is_lowpass = true;

	//init
	m_k = 0.01;
	m_alpha = 0.0;

	m_LPF1.setLP();
	m_LPF2.setLP();
	m_HPF1.setHP();
	m_HPF2.setHP();

	reset();
}


Korg35Filter::~Korg35Filter(void)
{
}

void Korg35Filter::reset()
{
	m_LPF1.reset();
	m_LPF2.reset();
	m_HPF1.reset();
	m_HPF2.reset();

}

void Korg35Filter::update()
{
	Filter::update();
	
	// BZT
	double wd = 2 * 3.141592653 * m_freq_modded;
	double t = 1.0 / m_samplerate;
	double wa = (2.0 / t)* tan(wd * t / 2.0);
	double g = wa * t / 2.0;

	double G = g / (1.0 + g);

	m_LPF1.m_alpha = G;
	m_LPF2.m_alpha = G;
	m_HPF1.m_alpha = G;
	m_HPF2.m_alpha = G;

	m_alpha = 1.0 / (1.0 - m_k * G + m_k * G * G);

	if (m_is_lowpass) {
		m_LPF2.m_beta = (m_k - m_k * G) / (1.0 + g);
		m_HPF1.m_beta = -1.0 / (1.0 + g);
		m_LPF1.m_beta = (m_k - m_k * G) / (1.0 + g);
		m_HPF2.m_beta = -1.0 / (1.0 + g);
	} else {
		m_HPF2.m_beta = -1.0 * G / (1.0 + g);
		m_LPF1.m_beta = 1.0 / (1.0 + g);
		m_HPF2.m_beta = -1.0 * G / (1.0 + g);
		m_LPF1.m_beta = 1.0 / (1.0 + g);
	}
}

double Korg35Filter::doFilter(double xn)
{
	double y;
	if (m_is_lowpass)
	{
		double y1 = m_LPF1.doFilter(xn);
		double s35 = m_LPF2.getFeedbackOutput() + m_HPF1.getFeedbackOutput();
		double u = m_alpha * (y1 + s35);

        if (m_overdrive < 1.){
		    //interpolate here so we have possibility of pure linear Processing
		    u = u * (1. - m_overdrive) + m_overdrive * fasttanh(u);
	    } else {
		    u = fasttanh(m_overdrive * u);
	    }

		y = m_k * m_LPF2.doFilter(u);
		m_HPF1.doFilter(y);
	} else {
		double y1 = m_HPF1.doFilter(xn);
		double s35 = m_HPF2.getFeedbackOutput() + m_LPF1.getFeedbackOutput();
		double u = m_alpha * (y1 + s35);


        if (m_overdrive < 1.){
		    //interpolate here so we have possibility of pure linear Processing
		    u = u * (1. - m_overdrive) + m_overdrive * fasttanh(u);
	    } else {
		    u = fasttanh(m_overdrive * u);
	    }

		y = m_k * u;
		m_LPF1.doFilter(m_HPF2.doFilter(y));
	}	
	y /= m_k;

	return y;
}

void Korg35Filter::setResControl(double res){
    //note: m_k must never be zero else division by zero
    //note2 original was 1.99 but dont want self oscillation
	m_k = res * 1.95 + 0.01;
}
