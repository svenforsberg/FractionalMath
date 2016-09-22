/*
	Mean.h - Library for computing mean value of fixed point numbers.
	Number of values=2^mean_shift, i.e. mean shift=3 gives 2^3=8 values.
	Maximum number of values per average output=32768 (mean_shift=15)
*/
#ifndef Mean_h
#define Mean_h

#include "Arduino.h"

//#define Q 12 //0.0002 Max 8 //3.147 0.787
//#define Q 13 //0.0001 Max 4 //3.136 0.784
#define Q 14 //0.00006 Max 2 //0.785339
//#define Q 15 //0.00003 Max 1 //0.785492

#define Q_MAX ((1<<15)-1)
#define Q_MIN -(1<<15)
#define Q_MAX_L ((1L<<15)-1L)
#define Q_MIN_L -(1L<<15)
#define Q_SCALE_F (float)(1L<<Q)
#define Q_UNITY (1<<Q)

#define MEAN_SHIFT 2
#define MEAN_N (1<<MEAN_SHIFT)

#define _ABS(X) (X ^ (X>>15))-(X>>15)
#define ABS_16(X) (X==-32768 ? (32767) : _ABS(X))

class FractionalMath
{
	public:
		FractionalMath(int q_val);
		int CalcMean(int indata,int *utdata);
		static inline int sat16(long x); //OK!
		static inline int addInt(int a,int b); //OK!
		static inline int multiplyIntQ0(int a,int b);
		static inline int divInt(int a, int b);
		static inline int divIntQ0(long a, long b);
		void tic_m();
		void toc_m();
		void tic_u();
		void toc_u();
		inline int quick_rms(int data[],int N);
		int float2Int(float x);
		float int2Float(int x);
	private:
		unsigned int _mean_ct;
		int _mean_shift;
		long _mean_val;
};




#endif