unsigned long t1;
unsigned long t2;
unsigned long pulse_width;
const int speed = 30;
const int motorDelay = 3;
int Gi = 0;
bool GV = true;
//Declaration
//////////////////// STEP ENGINE VARIABLES ////////////////////////// /
const int stepPinVD = 52;
const int dirPinVD = 53;
const int stepPinHD = 24;
const int dirPinHD = 25;
const int stepPinVB = 50;
const int dirPinVB = 51;
const int stepPinHB = 22;
const int dirPinHB = 23;
/////////////////// SENSOR VARIABLES //////////////////////////// //////
////////Front/////////////
const int sensEchoFr = 26;
const int sensTrigFr = 27;
//////// Right //////////////
const int sensEchoHsFr = 28;
const int sensTrigHsFr = 29;
const int sensEchoHsSi = 30;
const int sensTrigHsSi = 31;
//////// Left /////////////
const int sensEchoVsFr = 34;
const int sensTrigVsFr = 35;
const int sensEchoVsSi = 36;
const int sensTrigVsSi = 37;
/////// Down //////////////
const int sensEchoFrNr = 42;
const int sensTrigFrNr = 43;
const int sensEchoHsNr = 44;
const int sensTrigHsNr = 45;
const int sensEchoVsNr = 46;
const int sensTrigVsNr = 47;
//////////////////// LENGTH VARIABLES //////////////////////////// //////
// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DISTUPP = 580;
const unsigned int MAX_DISTNER = 580;
const unsigned int MAX_SIDA = 580;
const unsigned int MAX_FRAMSIDOR = 1050;
///////////// TURN 90 DEGREES FORWARD FUNCTION //////////////////
// For the vacuum cleaner to turn 90 degrees, one wheel needs to move 475 mm.
// This corresponds to 505 steps
int vanSvangFram () {
int i = 0;
while (i <505) {
digitalWrite (dirPinHD, LOW);
digitalWrite (stepPinHD, HIGH);
delayMicroseconds (motorDelay);
digitalWrite (stepPinHD, LOW);
int cnt = 0;
while (cnt <6) {
digitalWrite (stepPinHB, HIGH);
digitalWrite (stepPinVB, HIGH);
delayMicroseconds (motorDelay / 6);
digitalWrite (stepPinHB, LOW);
digitalWrite (stepPinVB, LOW);
cnt = cnt + 1;
 delay (speed / 6); // Comments off and replaces withone of the sensors. in 8 steps, everyone has gone through
 }
i = i +1;
}
}
int hogSvangFram () {
int i = 0;
while (i <505) {
digitalWrite (dirPinVD, LOW);
digitalWrite (stepPinVD, HIGH);
delayMicroseconds (motorDelay);
digitalWrite (stepPinVD, LOW);
int cnt = 0;
while (cnt <6) {
digitalWrite (stepPinHB, HIGH);
digitalWrite (stepPinVB, HIGH);
delayMicroseconds (motorDelay / 6);
digitalWrite (stepPinHB, LOW);
digitalWrite (stepPinVB, LOW);
cnt = cnt + 1;
delay (speed / 6); // Comments off and replaces with one of the sensors. in 8 steps, everyone has gone through
}
i = i +1;
}
}
///////////// TURN 90 DEGREES BEHIND FUNCTION //////////////////
// For the vacuum cleaner to turn 90 degrees, one wheel needs to move 475mm.
// This corresponds to 505 steps
int hogSvangBak () {
int i = 0;
while (i <505) {
digitalWrite (dirPinHD, HIGH);
digitalWrite (stepPinHD, HIGH);
delayMicroseconds (motorDelay);
digitalWrite (stepPinHD, LOW);
delayMicroseconds (motorDelay);
delay;
i = i +1;
}
}
int vanSvangBak () {
int i = 0;
while (i <505) {
digitalWrite (dirPinVD, HIGH);
digitalWrite (stepPinVD, HIGH);
delayMicroseconds (motorDelay);
digitalWrite (stepPinVD, LOW);
delayMicroseconds (motorDelay);
delay;
i = i +1;
}
}
//////// Checking the sensor Pages ////////////////////////
int sensPagesColl (int inputEcho, int inputTrig) {
// const int tempSensor = input
// Measure how long the echo pin was held high (pulse width)
// Note: the micros () counter will overflow after ~ 70 min
int x = 1;
digitalWrite (inputTrig, HIGH); // Sends a signal 0.000010 s
delayMicroseconds (10);
digitalWrite (inputTrig, LOW);
while (digitalRead (inputEcho) == 0); // The signal has not arrived back time shooting starts
 t1 = micros ();
while (x == 1) {// The signal has returned
 x = digitalRead (inputEcho); // Switches to 0 when the signal is back
 t2 = micros ();
 if (t2-t1> 5800) {// The limit was just over for unambiguous answer
 x = 0; // If the time goes longer than the measuring distance is interrupted on it.
 }
}
pulse_width = t2 - t1;
return pulse_width;
delay (10);
}
////////////// CHECK SENSORS AHEAD FUNCTION //////////////////////////
int sensUppKoll (int inputEcho, int inputTrig) {
// const int tempSensor = input
// Measure how long the echo pin was held high (pulse width)
// Note: the micros () counter will overflow after ~ 70 min
int x = 1;
digitalWrite (inputTrig, HIGH); // Sends a signal 0.000010 s
delayMicroseconds (10);
digitalWrite (inputTrig, LOW);
while (digitalRead (inputEcho) == 0); // The signal has not arrived back time shooting starts
 t1 = micros ();
while (x == 1) {// The signal has returned
 x = digitalRead (inputEcho); // Switches to 0 when the signal is back
 t2 = micros ();
 if (t2-t1> 600) {// The limit was just over for unambiguous answer
 x = 0; // If the time goes longer than the measuring distance is interrupted on it.
 }
}
pulse_width = t2 - t1;
if (pulse_width> MAX_DISTUPP) {
 pinMode (4, OUTPUT);
 digitalWrite (4, LOW);
 return true;
} else {
 pinMode (4, OUTPUT);
 digitalWrite (4, HIGH);
 return false;
}
// Wait at least 60ms before next measurement
// Measuring 17 cm takes 0.1 s round trip for 800 cm, delay is recommended 60 ms. Therefore, this can be reduced to
// 40/800 = 1/20 => 60/20 = 3 ms, Tests 10 ms because the sound anyway tar 100 ms.
delay (10);
}
//////////////////////// Check the sensors pages front //////////////////////
int sensFramSidaKoll (int inputEcho, int inputTrig) {
// const int tempSensor = input
// Measure how long the echo pin was held high (pulse width)
// Note: the micros () counter will overflow after ~ 70 min
int x = 1;
digitalWrite (inputTrig, HIGH); // Sends a signal 0.000010 s
delayMicroseconds (10);
digitalWrite (inputTrig, LOW);
while (digitalRead (inputEcho) == 0); // The signal has not arrived back time shooting starts
 t1 = micros ();
while (x == 1) {// The signal has returned
 x = digitalRead (inputEcho); // Switches to 0 when the signal is back
 t2 = micros ();
 if (t2-t1> 1100) {// The limit was just over for unambiguous answer
 x = 0; // If the time goes longer than the measuring distance is interrupted on it.
 }
}
pulse_width = t2 - t1;
if (pulse_width> MAX_FRAMSIDOR) {
 pinMode (4, OUTPUT);
 digitalWrite (4, LOW);
 return true;
} else {
 pinMode (4, OUTPUT);
 digitalWrite (4, HIGH);
 return false;
}
// Wait at least 60ms before next measurement
// Measuring 17 cm takes 0.1 s round trip for 800 cm, delay is recommended 60 ms. Therefore, this can be reduced to
// 40/800 = 1/20 => 60/20 = 3 ms, Tests 10 ms because the sound anyway tar 100 ms.
delay (10);
}
////////////// CHECK SENSORS DOWN FUNCTION /////////////////////////// P.S.S
int sensNerKoll (int inputEcho, int inputTrig) {
// const int tempSensor = input
// Measure how long the echo pin was held high (pulse width)
// Note: the micros () counter will overflow after ~ 70 min
int x = 1;
t1 = micros ();
digitalWrite (inputTrig, HIGH);
delayMicroseconds (10);
digitalWrite (inputTrig, LOW);
while (digitalRead (inputEcho) == 0);
 t1 = micros ();
while (x == 1) {
 x = digitalRead (inputEcho);
 t2 = micros ();
 if (t2-t1> 600) {
 x = 0;
 }
}
pulse_width = t2 - t1;
if (pulse_width <MAX_DISTNER) {
 pinMode (4, OUTPUT);
 digitalWrite (4, LOW);
 return true;
} else {
 pinMode (4, OUTPUT);
 digitalWrite (4, HIGH);
 return false;
}
delay (10);
}
//////////////////////////////////////////////////////////
int checkSense () {
// Check of Sensors OUT Reason why they flicker is because they jumps the function to the next. 8 times / lap
if (Gi == 0) {
 lookUppFrNerVsHs (); // Checks the sensor that is up and directed in direction of travel, returns false on detection
}
if (Gi == 25) {
 lookUppVsHsNerFr (); // Do not check the sensor on the underside connected yet
}
if (Gi == 75) {
 Gi = -1;
}

}
/////////////// Function up front side and down front wheels ////////////////
int lookUppVsHsNerFr () {
bool x = true;
bool y = true;
bool z = true;
x = sensNerKoll (sensEchoFrNr, sensTrigFrNr);
y = sensFramSidaKoll (sensEchoHsFr, sensTrigHsFr);
z = sensFramSidaKoll (sensEchoVsFr, sensTrigVsFr);
// If y = obstacle right side, then turn left
if (y == false) {
 vanSvangFram ();
}
// If z = obstacle left side, then turn right
if (z == false) {
 hogSvangFram ();
}
// If x = step forward ......
if (x == false) {
 kBak ();
 int LVHS = sensSidornaKoll (sensEchoHsSi, sensTrigHsSi);
 int LVVS = sensSidornaKoll (sensEchoVsSi, sensTrigVsSi);
 if (LVHS <= LVVS) {
 vanSvangFram ();
 }
 else {
 hogSvangFram ();
 }
}
}
///////////////// Function look up center and down in front of side wheels
////////////////////
int lookUppFrNerVsHs () {
bool x = true;
bool y = true;
bool z = true;
x = sensUppKoll (sensEchoFr, sensTrigFr);
y = sensNerKoll (sensEchoVsNr, sensTrigVsNr);
z = sensNerKoll (sensEchoHsNr, sensTrigHsNr);
if (x == false) {
  setup();
 int LVHS = sensSidornaKoll (sensEchoHsSi, sensTrigHsSi);
 int LVVS = sensSidornaKoll (sensEchoVsSi, sensTrigVsSi);
 if (LVHS <LVVS) {
 vanSvangFram ();
 }
 if (LVHS> LVVS) {
 hogSvangFram ();
 }
 if (LVHS == LVVS) {
 hogSvangFram ();
 }

}
if (y == false) {
 hogSvangBak ();
}
if (z == false) {
 vanSvangBak ();
}

}
/////////////// Drive straight ahead //////////////////
void kRaktfram () {
 digitalWrite (dirPinVD, LOW);
 digitalWrite (dirPinHD, LOW);
 digitalWrite (stepPinVD, HIGH);
 digitalWrite (stepPinHD, HIGH);
 delayMicroseconds (motorDelay);
 digitalWrite (stepPinVD, LOW);
 digitalWrite (stepPinHD, LOW);
 int cnt = 0;
 while (cnt <6) {
 digitalWrite (stepPinHB, HIGH);
 digitalWrite (stepPinVB, HIGH);
 delayMicroseconds (motorDelay / 6);
 digitalWrite (stepPinHB, LOW);
 digitalWrite (stepPinVB, LOW);
 cnt = cnt + 1;
 delay (speed / 6); // Comments off and replaces with one of the sensors. in 8 steps, everyone has gone through
 }



}
////////////////////////// Bake the vacuum cleaner halfway turn//////////////////////////////////////////
void kBak () {
int i = 0;
while (i <= 150) {
 digitalWrite (dirPinVD, HIGH);
 digitalWrite (dirPinHD, HIGH);
 digitalWrite (stepPinVD, HIGH);
 digitalWrite (stepPinHD, HIGH);
 delayMicroseconds (motorDelay);
 digitalWrite (stepPinVD, LOW);
 digitalWrite (stepPinHD, LOW);
 delayMicroseconds (motorDelay);
 delay; // Comments off and replaces with one of the sensors. in 8 steps, everyone has gone through
 i = i + 1;
}
}
void setup () {
/////////// TO STEP ENGINE CONTROL PIN DEFINITION //////////////////////
pinMode (stepPinVD, OUTPUT);
pinMode (dirPinVD, OUTPUT);
pinMode (stepPinHD, OUTPUT);
pinMode (dirPinHD, OUTPUT);
pinMode (stepPinVB, OUTPUT);
pinMode (dirPinVB, OUTPUT);
pinMode (stepPinHB, OUTPUT);
pinMode (dirPinHB, OUTPUT);
////////////// TO SENSOR PIN DEFINITION //////////////////////////
// The Trigger pin will tell the sensor to range find
pinMode (sensTrigFr, OUTPUT);
digitalWrite (sensTrigFr, LOW);
pinMode (sensTrigHsFr, OUTPUT);
digitalWrite (sensTrigHsFr, LOW);
pinMode (sensTrigHsSi, OUTPUT);
digitalWrite (sensTrigHsSi, LOW);
pinMode (sensTrigVsFr, OUTPUT);
digitalWrite (sensTrigVsFr, LOW);
pinMode (sensTrigVsSi, OUTPUT);
digitalWrite (sensTrigVsSi, LOW);
pinMode (sensTrigFrNr, OUTPUT);
digitalWrite (sensTrigFrNr, LOW);
pinMode (sensTrigHsNr, OUTPUT);
digitalWrite (sensTrigHsNr, LOW);
pinMode (sensTrigVsNo, OUTPUT);
digitalWrite (sensTrigVsNr, LOW);
}
////////////// THE MAIN PROGRAM //////////////////////////
// This loop runs all the time, like a while loop
void loop () {
while (Gi <= 75) {
if (Gi! = 0 or Gi! = 25) {
Straight forward (); // Make the vacuum cleaner drive straight ahead
}
// Check Sensors OUT The reason they flicker is because they jump out function to the next. 8 times / lap
if (Gi == 0) {
 lookUppFrNerVsHs (); // Checks the sensor that is up and directed in direction of travel, returns false on detection
}
if (Gi == 25) {
 lookUppVsHsNerFr (); // Do not check the sensor on the underside connected yet
}
if (Gi == 75) {
 Gi = -1;
}
// checkSense ();
Gi = Gi + 1;
}
}
