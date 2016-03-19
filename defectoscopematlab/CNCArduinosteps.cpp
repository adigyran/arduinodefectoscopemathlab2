// 
// 
// 

#include "CNCArduinosteps.h"
#include <TimerOne.h>
#include <TimerThree.h>
CNCArduinostepsClass CNCArduinosteps;
volatile long CNCArduinostepsClass::timer1steps;
volatile long CNCArduinostepsClass::timer1stepsfull;
volatile long CNCArduinostepsClass::timer1freq;
volatile long CNCArduinostepsClass::timer1freqspeedup;
volatile long CNCArduinostepsClass::timer1freqspeedupcoef;
volatile bool CNCArduinostepsClass::Yinterptconc;
volatile long CNCArduinostepsClass::timer3steps;
volatile long CNCArduinostepsClass::timer3stepsinter;
volatile long CNCArduinostepsClass::timer1stepsinter;
volatile long CNCArduinostepsClass::timer3stepsfull;
volatile long CNCArduinostepsClass::timer3freq;
volatile long CNCArduinostepsClass::timer3freqspeedup;
volatile long CNCArduinostepsClass::timer3freqspeedupcoef;
volatile bool CNCArduinostepsClass::Xinterptconc;
volatile bool CNCArduinostepsClass::Xinterptconc2;
volatile bool CNCArduinostepsClass::Yinterptconc2;
volatile bool CNCArduinostepsClass::Xarrived;
volatile bool CNCArduinostepsClass::Yarrived;
//void CNCArduinostepsClass::ArrivedX();
void CNCArduinostepsClass::init()
{
	pinsset = false;
	calibset = false;
	//Timer1.initialize(0);
	Yinterptconc = false;
	Xinterptconc = false;
	dxdyset = false;
	Enablepin = 52;
	DirpinX = 46;
	DirpinY = 44;
	
	
	

}

//void CNCArduinostepsClass::Yinterpt()
//{
	//Yinterptconc = true;
//	Serial.println("Yconv");
//}
void CNCArduinostepsClass::StepX(long speedX)
{
	
	//elapsedMicros tolrx = 0;
	//digitalWrite(led, digitalRead(led) ^ 1);
	//digitalWrite(Xpin, LOW);
	PORTB = B00000000;
	//long itrk = tolr;
	//Serial.println(speedX);
	//delay(speedX);

	delayMicroseconds(speedX);

	//long itrek = tolr;
	//while (tolrx < speedX)
	//{
		//long itrk = tolrx;
		//	Serial.println(itrk);
//	}
	//long itrek = tolrx;
	//Serial.println(itrek);
	//if (tolr > speedX)
	//{
	//	long itrk = tolr;
	//	Serial.println(itrk);
	//	return 1;
	//}
	//digitalWrite(Xpin,HIGH);
	PORTB = B01000000;

}
void CNCArduinostepsClass::StepY(long speedY)
{
	//elapsedMicros tolry = 0;
	//digitalWrite(2, LOW);
	//digitalWrite(12, digitalRead(12) ^ 1);
	//long itrk = tolr;
	//Serial.println(speedX);
	//delay(speedX);
	PORTB = B00000000;
	delayMicroseconds(speedY);

	//long itrek = tolr;
	//while (tolry < speedY)
	//{

	//}
	//long itrek = tolry;
	//Serial.println(itrek);
	//if (tolr > speedX)
	//{
	//	long itrk = tolr;
	//	Serial.println(itrk);
	//	return 1;
	//}
	//digitalWrite(2, HIGH);
	PORTB = B10000000; //PORTB & B11111110;
}

void CNCArduinostepsClass::Arrivedtostop()
{
	//int gkk = 4445;
	//long kjfri = 4985495;
	//long oiuiuoi = 4877848;
	//String info = String(gkk) + '&' + String(kjfri) + '&' + String(oiuiuoi);
	//Serial.println(info);
}

void CNCArduinostepsClass::serialcalibratedx(String calibrcommand)
{
	String calibrationtemp = calibrcommand.substring(0, calibrcommand.indexOf('&'));
	String dxtemp = calibrcommand.substring(calibrcommand.indexOf('&') + 1, calibrcommand.indexOf('#'));
	//Serial.println(calibrationtemp);
	//Serial.println(dxtemp);
	double calibrationXtemp = calibrationtemp.substring(0, calibrationtemp.indexOf('$')).toFloat();
	//Serial.println(calibrationXtemp);
	double calibrationYtemp = calibrationtemp.substring(calibrationtemp.indexOf('$') + 1, calibrationtemp.length()).toFloat();
	//Serial.println(calibrationYtemp);
	double dxXtemp = dxtemp.substring(0, dxtemp.indexOf('$')).toFloat();
	//Serial.println(dxXtemp);
	double dxYtemp = dxtemp.substring(dxtemp.indexOf('$') + 1, dxtemp.length()).toFloat();
	//Serial.println(dxYtemp);
	//double calibrationXtemp = amountstri.substring(0, amountstri.indexOf('$')).toFloat();
	///Serial.println(amountstri.substring(0, amountstri.indexOf('$')));
	//double calibrationYtemp = amountstri.substring(amountstri.indexOf('$')+1, amountstri.indexOf('&')).toFloat();
	//Serial.println(amountstri.substring(amountstri.indexOf('$')+1, amountstri.indexOf('&')));
	//double dxXtemp = amountstri.substring(amountstri.indexOf('&')+1, amountstri.indexOf('$')).toFloat();
	//Serial.println(amountstri.substring(amountstri.indexOf('&')+1, amountstri.indexOf('$')));
	//double dxYtemp = amountstri.substring(amountstri.indexOf('$')+1, amountstri.indexOf('#')).toFloat();
	//Serial.println(amountstri.substring(amountstri.indexOf('$')+1, amountstri.indexOf('#')));
	//Serial.println(calibrationXtemp);
	//Serial.println(calibrationYtemp);
	//Serial.println(dxXtemp);
	//Serial.println(dxYtemp);
	setcalibration(calibrationXtemp, calibrationYtemp);
	setdxdy(dxXtemp, dxYtemp);

}

void CNCArduinostepsClass::calibrate()
{
	xsize = 631;
	ysize = 886;
	Serial.println(xsize);
	Serial.println(ysize);
	GotoZero();
	delay(1000);
	long clbtr = 0;
	long d = 26445;
	long rr = 548;
	double fgg = (rr*1.0) / (d*1.0);
	Serial.println(fgg);
	Serial.println("ff");
	Serial.println(xsize);
	Serial.println(ysize);
	long totalstepsclbx = 0;
	maxX = 0;
	for (clbtr = 0;clbtr < 2;clbtr++)
	{
		if (DirX == 1)
		{
			DirX = 0;
		}
		else if (DirX == 0)
		{
			DirX = 1;
		}
		Serial.println(DirX);
		digitalWrite(DirpinX, DirX);
		
		maxX = 0;
		StepsX(100000, 1000);
		totalstepsclbx = maxX + totalstepsclbx;
		Serial.println(totalstepsclbx);
		Serial.println(maxX);
		delay(1000);
	}
	GotoZero();
	delay(1000);
	 clbtr = 0;

	long totalstepsclby = 0;
	maxY = 0;
	for (clbtr = 0;clbtr < 2;clbtr++)
	{
		if (DirY == 1)
		{
			DirY = 0;
		}
		else if (DirY == 0)
		{
			DirY = 1;
		}
		Serial.println(DirY);
		digitalWrite(DirpinY, DirY);

		maxY = 0;
		StepsY(100000, 1000);
		totalstepsclby = maxY + totalstepsclby;
		Serial.println(totalstepsclby);
		Serial.println(maxY);
		delay(1000);
	}
	
	Serial.println(totalstepsclbx);
	Serial.println(maxX);
	totalstepsclbx = totalstepsclbx / clbtr;
	totalstepsclby = totalstepsclby / clbtr;
	Serial.println(totalstepsclbx);
	Serial.println("ss");
	Serial.println(totalstepsclby);
	double tempclx = (xsize*1.0) / (totalstepsclbx*1.0);
	double tempcly = (double)ysize / (double)totalstepsclby;
	//calibrationX = 
	//calibrationY = (double)ysize / (double)totalstepsclby;
	calibset = true;
	setcalibration(tempclx, tempcly);
	Serial.println(tempclx,6);
	Serial.println(tempcly, 6);
	setdxdy(100, 100);
}

void CNCArduinostepsClass::ArrivedX()
{
	Serial.println(timer1stepsinter);
	Xarrived = true;
	Serial.println("arivdX");
}

void CNCArduinostepsClass::ArrivedY()
{
	Serial.println(timer3stepsinter);
	Yarrived = true;
	Serial.println("arivdY");
}

//void CNCArduinostepsClass::Yintert()
//{
	
//	Serial.println("Yconv");
//}

//void CNCArduinostepsClass::Xintert()
//{
//}

void CNCArduinostepsClass::StepsX(long stepsXf, long speedXf)
{
	if (DirX == 0) {
		Xinterptconc = false;
	}
	else if (DirX == 1) {
		Xinterptconc2 = false;
	}
	Serial.println("Dir");
	Serial.println(DirX);
	long i = 0;
	for (i;i < stepsXf; i++)
	{
		if ((!Xinterptconc && (DirX == 1)) || (!Xinterptconc2 && (DirX == 0)))
		//if(!Xinterptconc&&!Xinterptconc2)

		
		{
			//if (pulseXelapsed > 100000) {
			//Serial.print("x");
			//Serial.println(i);
			StepX(speedXf);
			//delayMicroseconds(1000);
			//pulseXelapsed = 0;
			//}
		}
		else break;
	}
	Serial.println(i);
	maxX = i;
}
void CNCArduinostepsClass::StepsY(long stepsYf, long speedYf)
{
	if (DirX == 0) {
		Xinterptconc = false;
	}
	else if (DirX == 1) {
		Xinterptconc2 = false;
	}
	//Xinterptconc = false;
	long i = 0;
	//long j = 0;
	for (i;i < stepsYf; i++)
	{
		if ((!Yinterptconc && DirY ==0)|| (!Yinterptconc2 && DirY == 1)) {
			//if (pulseXelapsed > 100000) {
		//Serial.print("y");
			//Serial.println(i);
			StepY(speedYf);
			
			//	if(!Xinterptconc)
				//{
					//if (pulseXelapsed > 100000) {
					//Serial.print("x");
					//Serial.println(i);
				//StepX(speedYf);
					//delayMicroseconds(1000);
					//pulseXelapsed = 0;
					//}
				//}
				
			//delayMicroseconds(1000);
			//pulseXelapsed = 0;
			//}
		}
		else break;
	}
	Serial.println(i);
	maxY = i;
	//Serial.println(j);
}
void CNCArduinostepsClass::FreqStepsX(long stepsXf, long speedXf)
{
	timer1freqspeedup = speedXf * 10;
	timer1freq = speedXf;
	timer1stepsfull = stepsXf;
	Timer1.initialize(speedXf);
	Xarrived = false;
	timer1freqspeedupcoef = speedXf / 100;
	Serial.println(stepsXf);
	Serial.println(speedXf);
	timer1stepsinter = 0;
	digitalWrite(13, LOW);
	Timer1.attachInterrupt(StepXintr);
	Yinterptconc = false;
	//Timer1.setPeriod(speedXf);
	Timer1.start();

}
void CNCArduinostepsClass::FreqStepsY(long stepsYf, long speedYf)
{
	Yarrived = false;
	timer3freqspeedup = speedYf * 10;
	timer3freq = speedYf;
	digitalWrite(5, LOW);
	timer3stepsfull = stepsYf;
	Timer3.initialize(speedYf);
	timer3freqspeedupcoef = speedYf / 100;
	Serial.println(stepsYf);
	Serial.println(speedYf);
	timer3stepsinter = 0;
	Timer3.attachInterrupt(StepYintr);
	Yinterptconc = false;
	//Timer1.setPeriod(speedXf);
	Timer3.start();
}
void CNCArduinostepsClass::GotoZero()
{
	if (pinsset) {
		Xarrived = false;
		Yarrived = false;
		Serial.println("GoingtoZero");
		DirX =1; //1 правильно

		DirY = 0; //0 правильно
		digitalWrite(DirpinX, DirX);
		digitalWrite(DirpinY, DirY);
		//FreqStepsY(5000, 1000);
		
		//while (!Yarrived)
		//{

        //}
		//FreqStepsY(10000000, 1000);
		Serial.println(digitalRead(18));
		if (digitalRead(18) == HIGH)
		{
			StepsX(1000000, 1000);
		}
		if (digitalRead(21) == HIGH)
		{
			StepsY(1000000, 1000);
		}
		
	
		Serial.println("inzero");
	}
}
void CNCArduinostepsClass::StepXintr()
{
	if (timer1steps > timer1stepsfull || Xinterptconc)
	{
		Timer1.stop();
		timer1stepsinter = timer1steps;
		timer1steps = 1;
		ArrivedX();

		Xinterptconc = false;
		
	}
	//if (timer1freqspeedup > timer1freq)
	//{
	//	timer1freqspeedup = timer1freqspeedup - timer1freqspeedupcoef;
	//	Timer1.initialize(timer1freqspeedup);
	//}
	//if (timer1steps > 200)
	//{
	//	Timer1.setPeriod(4000);
	//}
	
	//Serial.println(timer1steps);
	digitalWrite(13, digitalRead(13) ^ 1);
	timer1steps++;
}
void CNCArduinostepsClass::StepYintr()
{
//	Serial.println(timer3stepsfull);
	if (timer3steps > timer3stepsfull || Yinterptconc)
	{
		Timer3.stop();
		timer3stepsinter = timer3steps;
		timer3steps = 1;
		ArrivedY();
		Yinterptconc = false;

	}
	//if (timer1freqspeedup > timer1freq)
	//{
	//	timer1freqspeedup = timer1freqspeedup - timer1freqspeedupcoef;
	//	Timer1.initialize(timer1freqspeedup);
	//}
	//if (timer1steps > 200)
	//{
	//	Timer1.setPeriod(4000);
	//}

	//Serial.println(timer3steps);
	digitalWrite(2, digitalRead(2) ^ 1);
	timer3steps++;
}
void CNCArduinostepsClass::setpins(byte dirx, byte diry, byte xsteppin, byte ysteppin, byte enablepin)
{
	Xpin = xsteppin;
	Ypin = ysteppin;
	Enablepin = enablepin;
	
	DirpinX = dirx;
	DirpinY = diry;

	pinsset = true;
}

void CNCArduinostepsClass::setdxdy(double dxXunits, double dxYunits)
{
	dxXun = dxXunits;
	dxYun = dxYunits;
	dxdyset = true;
	if (calibset)
	{
		dxX = abs((double)dxXun / calibrationX);
		dxY = abs((double)dxYun / calibrationY);
		Serial.println(dxX);
		Serial.println(dxY);
		Serial.println(dxXun);
		Serial.println(dxYun);


	}
}

void CNCArduinostepsClass::setcalibration(double calibX, double calibY)
{
	calibrationX = calibX;
	calibrationY = calibY;
	Serial.println(calibrationX);
	Serial.println(calibrationY);
	calibset = true;
}

void CNCArduinostepsClass::serialhandler(String command,long amount, String amountstri)
{
	Serial.println(command);
	Serial.println(amount);
	if (command.equals("DXX"))
	{
		dxX = amount;
	}
	else if (command.equals("DXY"))
	{
		dxY = amount;
	}
	else if (command.equals("TAS"))
	{
		Arrivedtostop();
	}
	else if (command.equals("XSS"))
	{
		testingstepsX = amount;

	}
	else if (command.equals("CLB"))
	{
		calibrate();

	}
	else if (command.equals("MTC"))
	{
		serialcalibratedx(amountstri);
	}
	else if (command.equals("ENB"))
	{
		if (amount == 1)
		{
			digitalWrite(Enablepin, HIGH);
			Serial.println(digitalRead(52));

		}
		if (amount == 0)
		{
			digitalWrite(Enablepin, LOW);
			Serial.println(digitalRead(52));
		}
	}

	else if (command.equals("XSD"))
	{
		testingdirX = amount;
		if (testingdirX == 1)
		{
			digitalWrite(DirpinX, HIGH);
			DirX = 1;
		}
		else if (testingdirX == 0)
		{
			digitalWrite(DirpinX, LOW);
			DirX = 0;
		}

	}
	else if (command.equals("GTZ"))
	{
		GotoZero();

	}
	else if (command.equals("YSD"))
	{
		testingdirY = amount;
		if (testingdirY == 1)
		{
			digitalWrite(DirpinY, HIGH);
			DirY = 1;
		}
		else if (testingdirY == 0)
		{
			digitalWrite(DirpinY, LOW);
			DirY = 0;
		}

	}
	else if (command.equals("XSF"))
	{
		testingfreqX = amount;

	}
	else if (command.equals("XSE"))
	{
		testingenableX = amount;
		if (testingenableX)
		{
			StepsX(testingstepsX, testingfreqX);
			digitalWrite(4, HIGH);
			digitalWrite(10, HIGH);
		}
	}
	else if (command.equals("XTF"))
	{
		timer1freq = amount;
	}
	else if (command.equals("XTS"))
	{
		timer1stepsfull = amount;
	}
	else if (command.equals("XTE"))
	{
		Xinterptconc = false;
		//FreqStepsX(timer1stepsfull, timer1freq);
		StepsX(timer1stepsfull, timer1freq);
	}

	else if (command.equals("YTF"))
	{
		timer3freq = amount;
	}
	else if (command.equals("YTS"))
	{
		timer3stepsfull = amount;
	}
	else if (command.equals("YTE"))
	{
		Yinterptconc = false;
		//FreqStepsY(timer3stepsfull, timer3freq);
		StepsY(timer3stepsfull, timer3freq);
	}
	else
	{
		Serial.println("Wrong command");
	}
}

CNCArduinostepsClass::currencoord CNCArduinostepsClass::getcurrencoord()
{
	newcurcord.currentXs = currentX;
	newcurcord.currentYs = currentY;
	return newcurcord;
}

void CNCArduinostepsClass::Yinterpt(bool yplus)
{
//	Yintert();
	Serial.println("Yconvf");
	if (!yplus) {
		Yinterptconc = true;
		Yinterptconc2 = false;
	}
	else if (yplus)
	{
		Yinterptconc2 = true;
		Yinterptconc = false;
	}
	Yarrived = true;
}
void CNCArduinostepsClass::Xinterpt(bool xplus)
{
	
	//	Yintert();
	Serial.println("Xconvf");
	if (!xplus) {
		Xinterptconc = true;
		Xinterptconc2 = false;
	}
	else if (xplus)
	{
		Xinterptconc2 = true;
		Xinterptconc = false;
	}
	Serial.println(Xinterptconc);
	Serial.println(Xinterptconc2);

	Xarrived = true;
}

