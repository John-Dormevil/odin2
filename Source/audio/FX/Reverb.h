/*
** Odin 2 Synthesizer Plugin
** Copyright (C) 2020 TheWaveWarden
**
** Odin 2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Odin 2 is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/

// The implementation for this ZitaReverb module is taken from zita-rev1 with some adjustments. See
// https://github.com/royvegard/zita-rev1 for the original code.

#ifndef __REVERB_H
#define __REVERB_H

#include "ParametricEQ.h"

class Diff1 {
private:
	friend class ZitaReverb;

	Diff1(void);
	~Diff1(void);

	void init(int size, float c);
	void fini(void);

	float process(float x) {
		float z = _line[_i];
		x -= _c * z;
		_line[_i] = x;
		if (++_i == _size)
			_i = 0;
		return z + _c * x;
	}

	int _i;
	float _c;
	int _size;
	float *_line;
};

// -----------------------------------------------------------------------

class Filt1 {
private:
	friend class ZitaReverb;

	Filt1(void) : _slo(0), _shi(0) {
	}
	~Filt1(void) {
	}

	void set_params(float del, float tmf, float tlo, float wlo, float thi, float chi);

	float process(float x) {
		_slo += _wlo * (x - _slo) + 1e-10f;
		x += _glo * _slo;
		_shi += _whi * (x - _shi);
		return _gmf * _shi;
	}
	float _gmf;
	float _glo;
	float _wlo;
	float _whi;
	float _slo;
	float _shi;
};

// -----------------------------------------------------------------------

class RevDelay {
private:
	friend class ZitaReverb;

	RevDelay(void);
	~RevDelay(void);

	void init(int size);
	void fini(void);

	float read(void) {
		return _line[_i];
	}

	void write(float x) {
		_line[_i++] = x;
		if (_i == _size)
			_i = 0;
	}

	int _i;
	int _size;
	float *_line;
};

// -----------------------------------------------------------------------

class Vdelay {
private:
	friend class ZitaReverb;

	Vdelay(void);
	~Vdelay(void);

	void init(int size);
	void fini(void);
	void set_delay(int del);

	float read(void) {
		float x = _line[_ir++];
		if (_ir == _size)
			_ir = 0;
		return x;
	}

	void write(float x) {
		_line[_iw++] = x;
		if (_iw == _size)
			_iw = 0;
	}

	int _ir;
	int _iw;
	int _size;
	float *_line;
};

// -----------------------------------------------------------------------

class ZitaReverb {
public:
	ZitaReverb(void);
	~ZitaReverb(void);

	void setSampleRate(float fsamp);
	void fini(void);

	void prepare();
	float* process(float input[2]);

	void set_delay(float v);
	void set_xover(float v);
	void set_rtlow(float v);
	void set_rtmid(float v);
	void set_fdamp(float v);
	void set_opmix(float v);
	void set_rgxyz(float v);
	void set_eq1(float f, float g);
	//void set_eq2(float f, float g);

private:
	float _fsamp;

	Vdelay _vdelay0;
	Vdelay _vdelay1;
	Diff1 _diff1[8];
	Filt1 _filt1[8];
	RevDelay _delay[8];

	volatile int _cntA1;
	volatile int _cntB1;
	volatile int _cntC1;
	int _cntA2;
	int _cntB2;
	int _cntC2;

	float _ipdel;
	float _xover;
	float _rtlow;
	float _rtmid;
	float _fdamp;
	float _opmix;
	float _rgxyz;

	float _g0, _d0;
	float _g1, _d1;

	ParametricEQ _pareq1;
	//ParametricEQ _pareq2;

	static float _tdiff1[8];
	static float _tdelay[8];
};

// -----------------------------------------------------------------------

#endif