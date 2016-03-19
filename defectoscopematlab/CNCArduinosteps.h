// CNCArduinosteps.h

#ifndef _CNCARDUINOSTEPS_h
#define _CNCARDUINOSTEPS_h
#include <elapsedMillis.h>
//#include <TimerOne.h>
//#include <TimerThree.h>
#include <TimerOne\TimerOne.h>
#include <TimerThree\TimerThree.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
// функция для проезда по нужным координатам. изначально едем в ноль, до первого концевика по обоим координатам, потом выполняем функцию поехать на определенное число милимметров
class CNCArduinostepsClass
{
public:
	struct currencoord
	{
		long currentXs;
		long currentYs;
	};
	
	void init();
	void setpins(byte dirx, byte diry, byte xsteppin, byte ysteppin, byte enablepin);
	void setdxdy(double dxXunits, double dxYunits);
	void setcalibration(double calibX, double calibY);
	void serialhandler(String command, long amount,String amountstri);
	
	currencoord getcurrencoord();
	
	static  void Yinterpt(bool yplus); //переменная определяет какой из концевиков сработал, в отрицательном либо положительном направлении
	static  void Xinterpt(bool xplus);
private:

 protected:
	 long dxX, dxY; //DX of each axies in steps -  в шагах
	 double dxXun, dxYun; //DX of each axies in units -  в мм
	 long totalXsteps,totalYsteps; //totalsteps
	 double calibrationX, calibrationY; //calibration to the system units (сколько мм в одном шаге)
	 long currentX, currentY; //в шагах
	 double currentXun, currentYun; // в мм
	 long testingstepsX, testingfreqX;
	 bool testingenableX;
	 byte testingdirX;
	 byte testingdirY;
	 byte DirX, DirY;
	 long maxX, maxY;
	 long xsize, ysize;
	 bool timer1s, timer3s;
	 bool coordintXe, coordintYe;
	 bool Xarrivd, Yarrivd;
	 void serialcalibratedx(String calibrcommand);
	 void calibrate();
	static  volatile long timer1steps, timer3steps,timer1stepsinter,timer3stepsinter;
	static  volatile long timer1stepsfull, timer3stepsfull;
	 static volatile long timer1freq, timer3freq;
	 static volatile long timer1freqspeedup, timer3freqspeedup;
	 static volatile long timer1freqspeedupcoef, timer3freqspeedupcoef;
	 static volatile bool Xinterptconc, Yinterptconc,Xarrived,Yarrived,Xinterptconc2,Yinterptconc2;
	 static void ArrivedX();
	 static void ArrivedY();
	// static void Yintert();
	// static void Xintert();
	 long desirX, desirdY; // where is next stop
	 byte Xpin, Ypin;
	 bool pinsset,calibset,dxdyset;
	 byte DirpinX, DirpinY, Enablepin;
	 void StepsX(long stepsXf,long speedXf); //steps engine in calibration factor. speed means delay in microseconds, wich mean the frequency
	 void StepsY(long stepsYf, long speedYf);
	 void FreqStepsX(long stepsXf, long speedXf);
	 void FreqStepsY(long stepsYf, long speedYf);
	 void SetDirX(byte dirx);
	 void SetDirY(byte diry);
	 void GotoZero();
	 static void StepXintr();
	 static void StepYintr();
	 void StepX(long speedX);
	 void StepY(long speedY);
	 void Arrivedtostop();
	 currencoord newcurcord;




 

};

extern CNCArduinostepsClass CNCArduinosteps;

#endif

