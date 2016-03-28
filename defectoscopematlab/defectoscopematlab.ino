/*
Name:		defectoscmatlab.ino
Created:	29.02.2016 16:30:11
Author:	adigyran
*/

// the setup function runs once when you press reset or power the board
#include "CNCArduinosteps.h"
#include <TimerThree.h>
#include <TimerOne.h>
#include <elapsedMillis.h>
int led = 13;
elapsedMillis timeElapsed;
elapsedMicros pulseXelapsed;
volatile long desiredXfreq;
volatile long desiredYfreq;
volatile bool enableX;
volatile bool enableY;
volatile bool enableXfreq;
volatile bool enableYfreq;
CNCArduinostepsClass CNCdefectoscope;
boolean ledState = LOW;
void setup() {
	pinMode(led, OUTPUT);
	pinMode(30, OUTPUT);
	pinMode(32, OUTPUT);
	//pinMode(3, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(52, OUTPUT);
	pinMode(46, OUTPUT);
	pinMode(44, OUTPUT);
	pinMode(20, INPUT);
	pinMode(21, INPUT);
	pinMode(19, INPUT);
	pinMode(18, INPUT);
	pinMode(12, OUTPUT);
	enableX = false;
	enableY = false;
    //Timer1.initialize(205000);
	//Timer1.attachInterrupt(blinkLED);
    //Timer1.start();
	//digitalWrite(30, HIGH);
	//digitalWrite(32, HIGH);
//	Timer1.stop();
	//Timer3.initialize(5000);
	//Timer3.attachInterrupt(blink12);
	//Timer3.start();
	//Timer3.stop();
	Serial.begin(9600);
	Serial.println("start");
	//pinMode(3, INPUT);
	pinMode(3, INPUT);
	//pinMode(2, INPUT);
	CNCdefectoscope.init();
	attachInterrupt(3, yinti, FALLING); //20
	attachInterrupt(2, yinti2, FALLING); //21
	attachInterrupt(4, xinti, FALLING); //19
    attachInterrupt(5, xinti2, FALLING); //18
	Serial.println(CNCdefectoscope.getcurrencoord().currentXs);
	//Enablepin = 52;
	//DirpinX = 46;
	//DirpinY = 44;
	CNCdefectoscope.setpins(46, 44, 13, 2, 52);
	//CNCdefectoscope.setcalibration(0.012, 0.024);
	//CNCdefectoscope.setdxdy(100, 100);
}

void yinti2()
{
	CNCdefectoscope.Yinterpt(false); //в нуле
	Serial.println("Yconv");
}
void yinti()
{
	CNCdefectoscope.Yinterpt(true); // на максимуме
	Serial.println("Yconv2");
}
void xinti2()
{
	CNCdefectoscope.Xinterpt(false); //в нуле
	Serial.println("Xconv");
}
void xinti()
{
	CNCdefectoscope.Xinterpt(true); //на максимуме
	Serial.println("Xconv2");
}

void blink12()
{
	digitalWrite(3, digitalRead(3) ^ 1);
}
void blinkLED()
{
	digitalWrite(13, digitalRead(13) ^ 1);
}

int StepX(long speedX)
{
	elapsedMicros tolrx =0;
	//digitalWrite(led, digitalRead(led) ^ 1);
	digitalWrite(led, LOW);
		//long itrk = tolr;
		Serial.println(speedX);
		//delay(speedX);
		
		//delayMicroseconds(speedX*100);

		//long itrek = tolr;
		while (tolrx < speedX)
		{
		//long itrk = tolrx;
		//	Serial.println(itrk);
		}
		long itrek = tolrx;
		Serial.println(itrek);
		//if (tolr > speedX)
		//{
		//	long itrk = tolr;
		//	Serial.println(itrk);
		//	return 1;
		//}
		digitalWrite(led, HIGH);

}
int StepY(long speedY)
{
	elapsedMicros tolry = 0;

	//digitalWrite(12, digitalRead(12) ^ 1);
	//long itrk = tolr;
	//Serial.println(speedX);
	//delay(speedX);

	//delayMicroseconds(speedX*100);

	//long itrek = tolr;
	while (tolry < speedY)
	{

	}
	long itrek = tolry;
	Serial.println(itrek);
	//if (tolr > speedX)
	//{
	//	long itrk = tolr;
	//	Serial.println(itrk);
	//	return 1;
	//}

}

void StepsX(long speedXf, long stepXf)
{
	for (long i = 1;i < stepXf; i++)
	{
		//if (pulseXelapsed > 100000) {
		Serial.print("x");
		Serial.println(i);
		int g = StepX(speedXf);
		//delayMicroseconds(1000);
		//pulseXelapsed = 0;
		//}
	}
}
void StepsY(long speedYf, long stepYf)
{
	for (long i = 1;i < stepYf; i++)
	{
		//if (pulseXelapsed > 100000) {
		Serial.print("y");
		Serial.println(i);
		int g = StepY(speedYf);
		//delayMicroseconds(1000);
		//pulseXelapsed = 0;
		//}
	}
}

void serialEvent()
{
	//String lof = "";
	String irr = Serial.readStringUntil('\n');
	Serial.println(irr);
	if (irr.charAt(0) == '>') {
		//	{
		//	char lo[20];
		//while (Serial.available()>0)
		//{

		//		}
		//	String ekkfk = "asd ";
		//	ekkfk.concat(eventrs);
		String	lof = irr.substring(4, irr.length());
		//Serial.print(irr.length());
		//Serial.print(irr);
		String casestring = irr.substring(1, 4);
		Serial.println(casestring);
		Serial.println(lof);
		//Serial.println(CNCdefectoscope.getcurrencoord().currentXs);
		CNCdefectoscope.serialhandler(casestring, lof.toInt(),lof);
		if (casestring.equals("X1"))
		{
			desiredXfreq = lof.toInt();
			Timer1.setPeriod(desiredXfreq);
			Serial.print(lof +"\n\r");
		}
		else if (casestring.equals("Y1"))
		{
			desiredYfreq = lof.toInt();
			Timer1.setPeriod(desiredYfreq);
		}
		else if (casestring.equals("XE"))
		{
			if (lof.equals("true"))
			{
				//if (enableXfreq == true)
				//{
					Timer1.restart();
					Serial.print("start\n\r");
				//}
				//else
				//{
				//	Timer1.start();
				//}
				//enableX = true;
				
			}
			else if (lof.equals("false"))
			{
				Timer1.stop();
				Serial.print("stop\n\r");
				//enableX = false;
			}
		}
		else if (casestring.equals("YE"))
		{
			if (lof.equals("true"))
			{
				//enableY = true;
			}
			else if (lof.equals("false"))
			{
				//enableY = false;
			}
		}
		else if (casestring.equals("XT"))
		{
			long desiredXsteps = lof.toInt();
			Serial.print("ff\n");
			StepsX(100000, desiredXsteps);
		}
		else if (casestring.equals("YT"))
		{
			long desiredYsteps = lof.toInt();
			Serial.print("ffd\n");
			StepsY(100000, desiredYsteps);
			
		}
	//	if (casestring.equals("B1"))
	//	{
		//	motorrpm = lof.toInt();
		//	Serial.write("tkjkjd\n\r");
	//	}
	//	else if (casestring.equals("S1"))
	//	{
	//		motorrpm = lof.toInt();
	//	}
	//	else if (casestring.equals("S2"))
	//	{

//			servorpm = lof.toInt();
	//		FrequencyTimer2::setPeriod(servorpm);
	//		Timer1.setPeriod(servorpm);
	//	}
	//	else if (casestring.equals("E1"))
		//{

		//	String servoenable = irr.substring(3, 8);
			//Serial.print(servoenable);
			//Serial.print("\n\r");
		//	if (servoenable.equals("true"))
			//{
			//	servoenabled = true;
			//	FrequencyTimer2::enable();
			//	Timer1.start();
			//	digitalWrite(enablepin, HIGH);
		//	}
			//else if (servoenable.equals("false"))
			//{
			//	FrequencyTimer2::disable();
			//	Timer1.stop();
			//	servoenabled = false;
			//	digitalWrite(enablepin, LOW);
		//	}
		//}
		//else if (casestring.equals("D1"))
		//{

//			String directionright = irr.substring(3, 8);
			//Serial.print(servoenable);
			//Serial.print("\n\r");
//			if (directionright.equals("true"))
//			{
				//servoenabled = true;
				//FrequencyTimer2::enable();
//				digitalWrite(dirpin, HIGH);
//			}
	//		else if (directionright.equals("false"))
	//		{
				//FrequencyTimer2::disable();
				//servoenabled = false;
	//			digitalWrite(dirpin, LOW);
	//		}
	//	}
		//switch (casechar)
		//{
		//case 'a':
		//	motorrpm = lof.toInt();
		//		break;

		//	case 'b':
		//		motorrpm = lof.toInt();
		//		break;
		//	default:
		//	break;
		//}
		//lfof = lof.toInt();
		//	ekkfk.concat(" ");
		//ekkfk.concat(lof);
		//	Serial.println(ekkfk);
		//	eventrs++;
		//}


		//	Serial.println(irr);
		//Serial.println(servorpm);
		//Serial.println(irr.substring(1, 3));
		//Serial.println(i);
		//Serial.println(Serial.readString());
		//Serial.println(Serial.read());
	}
}
// the loop function runs over and over again until power down or reset
void loop() {
	//Serial.print(timeElapsed+"\n\r");
	//if (timeElapsed >1000)
	//{
	//	ledState = !ledState;         // toggle the state from HIGH to LOW to HIGH to LOW ... 
	//	digitalWrite(led, digitalRead(led) ^ 1);
	//	timeElapsed = 0;              // reset the counter to 0 so the counting starts over...
	//}
}
