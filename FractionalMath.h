/*
	FractionalMath.h - Library for fixed point mathematics on the Arduino. Supply Q value in constructor.
	Q	Largest value	Precision
	15	1.0				0.00003
	14	2.0				0.00006
	13	4.0				0.00012
	12	8.0				0.00024
	11	16.0			0.00049
	10	32.0			0.00098
	9	64.0			0.00195
	8	128.0			0.00391
*/
#ifndef FracMath_h
#define FracMath_h

#include "Arduino.h"

#define Q_MAX ((1<<15)-1)
#define Q_MIN -(1<<15)
#define Q_MAX_L ((1L<<15)-1L)
#define Q_MIN_L -(1L<<15)

#define Q_SCALE_F(Q) (float)(1L<<Q)
#define Q_UNITY(Q) (1<<Q)

#define _ABS(X) (X ^ (X>>15))-(X>>15)
#define ABS_16(X) (X==-32768 ? (32767) : _ABS(X))

class FractionalMath
{
	public:
		FractionalMath(char q_val);
		int CalcMean(int indata,int *utdata);
		int sat16(long x);
		int addInt(int a,int b);
		int multiplyIntQ0(int a,int b);
		int divInt(int a, int b);
		int divIntQ0(long a, long b);
		int multiplyInt(int a,int b);
		void tic_m();
		void toc_m();
		void tic_u();
		void toc_u();
		int quick_rms(int data[],int N);
		int float2Int(float x);
		float int2Float(int x);
	private:
		unsigned int _mean_ct;
		int _mean_shift;
		long _mean_val;
		char _q_val;
		unsigned long _timestamp;
};

#endif