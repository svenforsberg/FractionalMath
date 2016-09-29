#include "Arduino.h"
#include "FractionalMath.h"


FractionalMath::FractionalMath(char q_val)
{
	_q_val=q_val;
}


int FractionalMath::sat16(long x) //OK!
{
  if(x > Q_MAX_L){
    return Q_MAX; //Overflow at 32767.
  }
  else if( x < Q_MIN_L ){
    return Q_MIN; //Overflow at -32768.
  }
  else{
    return (int)x;
  }
}

int FractionalMath::addInt(int a,int b) //OK!
{
  long temp;
  temp=(long)a+(long)b;
  return sat16(temp);
}

int FractionalMath::multiplyInt(int a,int b) //OK!
{
  int result;
  long temp;
  temp=(long)a * (long)b;
  temp+=(1L << (_q_val-1));
  result=sat16(temp >> _q_val);
  return result;
}

int FractionalMath::multiplyIntQ0(int a,int b) //OK
{
  int result;
  long temp;
  temp=(long)a * (long)(b*2);
  temp+=1L;
  result=sat16(temp >> 1);
  return result;
}

int FractionalMath::divInt(int a, int b)
{
  int result;
  long temp;
  temp=(long)a << _q_val;
  if ((temp >= 0 && b >= 0) || (temp < 0 && b < 0))
    temp += b / 2;
  else
    temp -= b / 2;

  result=sat16(temp / b);
  return result;
}

int FractionalMath::divIntQ0(long a, long b) //OK!
{
  int result;
  long temp;
  temp=(long)a;
  if ((temp >= 0 && b >= 0) || (temp < 0 && b < 0))
    temp += b / 2;
  else
    temp -= b / 2;

  result=sat16(temp / b);
  return result;
}

void FractionalMath::tic_m()
{
  _timestamp=millis();
}

void FractionalMath::toc_m()
{
  unsigned long dT=(millis()-_timestamp);
  Serial.print("Elapsed milliseconds=");
  Serial.println(dT);
}

void FractionalMath::tic_u()
{
  _timestamp=micros();
}

void FractionalMath::toc_u()
{
  unsigned long dT=(micros()-_timestamp);
  Serial.print("Elapsed microseconds=");
  Serial.println(dT);
}

int FractionalMath::quick_rms(int data[],int N) //OK. Calcluates average rectified value! 
{
  int i=0;
  long sum=0;
  for(i=0;i<N;i++)
  {
    sum+=ABS_16(data[i]);
  }
  return divIntQ0(sum,N);
}

int FractionalMath::float2Int(float x) //OK!
{
  long temp;
  int result;
  if(x>=0) temp=(long)(x*Q_SCALE_F(_q_val)+0.5);
  else temp=(long)(x*Q_SCALE_F(_q_val)-0.5);
  result=sat16(temp);
  return result;
}

float FractionalMath::int2Float(int x) //OK!
{
  return ((float)x/Q_SCALE_F(_q_val));
}
