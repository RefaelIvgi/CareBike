//Created By Refael Ivgi

#include <SoftwareSerial.h>;
#include <TinyGPS++.h > ;

static const int RXPin = 6, TXPin = 10;
float LAT,LON; 
int SEND_TWICE=0,DILUG;
int POWER_KEY_GSM=9;
int SMS_ONCES=0;
TinyGPSPlus gps;


SoftwareSerial mySerial(7, 8);
SoftwareSerial ss(RXPin , TXPin);


void setup()
{


mySerial.begin(19200); // For GSM
ss.begin(9600); //For GPS
Serial.begin(9600);

//check for PIN 9 Before Start
if (digitalRead(POWER_KEY_GSM) == LOW)
{
pinMode(9, OUTPUT);
digitalWrite(9,HIGH);

}
}


///פונקציית שליחת הודעה עם המיקום ///

void SHLIHAT_MIKUM()
{
if (SMS_ONCES==1)
{
mySerial.print("\r");
delay(100);
mySerial.print("AT+CMGF=1\r");
delay(100);



mySerial.print("AT+CMGS=\"+972XXXXXXX\"\r"); // insert Phone number
delay(100);


mySerial.print("WARNING FROM CareBike");
mySerial.println("");
mySerial.print("https://www.google.co.il/maps/@");
mySerial.print(LAT);
mySerial.print(",");
mySerial.print(LON)
mySerial.print(",19z?hl=iw\r");
smartDelay(1000);
mySerial.write(0x1A);
delay(1000);

}

;++ SMS_ONCES
}


static void oreh(float mikum , bool valid)
{
if(SEND_TWICE&lt;=2)
{

if (!valid)
{
while (DILUG-- > 1)
Serial.print('*');
Serial.println('');

}
else
{
Serial.println(mikum);
LAT=mikum;
SEND_TWICE++;
}
}
התאמת זמנים // ;
smartDelay(0);

}



static void rohav(float mikum , bool valid)
{
if(SEND_TWICE&lt;=2)
{
if (!valid)
{
while (DILUG-- >1)


Serial.print('*');
Serial.println('');

}
else
{
LON=mikum;
Serial.println(mikum);
SEND_TWICE++;
}
}
smartDelay(0);
}


void loop()
{

Initialization();
digitalWrite(9,HIGH);
delay(200);


int checkFlag = 0;
int DELAY_SHLIHA;
int s1=2;
int s2 =3;

pinMode(s1, INPUT);



pinMode(s2, INPUT);
Serial.println(s1);

if ( digitalRead(s1) == LOW || digitalRead(s2) ==LOW)
{
SMS_ONCES=0;
}


if (digitalRead(s1) == HIGH || digitalRead(s2) == HIGH)
{

while ((DELAY_SHLIHA<1200) && (digitalRead(s1) == HIGH || digitalRead(s2) == HIGH))
{
DELAY_SHLIHA++;
}

DELAY_SHLIHA=0;

if(digitalRead(s1) == HIGH || digitalRead(s2) == HIGH)
{

oreh(gps.location.lat(), gps.location.isValid());
rohav(gps.location.lng(), gps.location.isValid());


SEND_TWICE++;
checkFlag = 1;

if (checkFlag == 1)
{

if(SMS_ONCES<=1)
SHLIHAT_MIKUM();

}
}
}
}


static void smartDelay(unsigned long ms)
{
unsigned long start = millis();
do
{
while (ss.available)


gps.encode(ss.read());

}



while (millis() - start < ms);
}


void initialization()
{
oreh(gps.location.lat(), gps.location.isValid());
rohav(gps.location.lng(), gps.location.isValid());

}



