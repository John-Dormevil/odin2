#include "CombFilter.h"

CombFilter::CombFilter()
{
}


CombFilter::~CombFilter()
{
}


float CombFilter::doFilter(float p_input){

    //todo audio bug when increasing delay_time

	m_delay_time_smooth =  (m_delay_time_smooth - m_delay_time_control) * 0.999 + m_delay_time_control;

    //calc read index
    float read_index = (float)m_write_index - m_delay_time_smooth * m_samplerate;
    int read_index_trunc = floor(read_index);
    int read_index_next = read_index_trunc + 1;
    float frac = read_index - (float)read_index_trunc;

    //check boundaries
    read_index_trunc = read_index_trunc < 0 ? read_index_trunc + COMB_BUFFER_LENGTH : read_index_trunc; 
    read_index_next  = read_index_next  < 0 ? read_index_next  + COMB_BUFFER_LENGTH : read_index_next;
    read_index_next  = read_index_next  >= COMB_BUFFER_LENGTH ? read_index_next  - COMB_BUFFER_LENGTH : read_index_next;

    float output = linearInterpolation(circular_buffer[read_index_trunc], circular_buffer[read_index_next], frac);

    circular_buffer[m_write_index] = p_input + output * m_feedback * m_positive_comb;
    incWriteIndex();

    //set sample behind readindex to zero to avoid reading that signal when increasing delay time
    //circular_buffer[read_index_trunc] = 0.f; // todo not enough? (time jumps over this)

    return (p_input + output) * 0.5f;
}