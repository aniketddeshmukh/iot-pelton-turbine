//for pressure sensor no.4 is 0.469
//for pressuer sensor no.3 is 0.459
//for pressure sensor no.1 is 0.464
//P3 is at higher pressure(left)
//P4 is at lower pressure(right)
//A0 is connected to Pressure sensor no 4
//A1 is connected to Pressure sensor no 3
//A2 is connected to Potentiometer
//A3 is connected to Pressure sensor no 1
//D3 is connected to IR Sensor


const float OffSet1 = 0.469  ;           
const float OffSet3 = 0.459 ;
const float OffSet4 = 0.469 ;
float Va,Vb,Vc,P4,P3,P1;
int pot = 0;
int potvalue;
int rpm = 0;
unsigned long millisBefore;
volatile int holes;
const unsigned long duration = 1000;
String s =";";
int potmeterPin1 =A2;
      
          
void setup() 
{
  Serial.begin(9600); 
  pinMode(A2,INPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A3,INPUT);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), count, RISING);
  delay(1000);
 
}

int potentiometer(){
  pot = analogRead(potmeterPin1);
  //Serial.println(pot);
//  Serial.print("Valve Open %: ");

  if (pot < 830 && pot >=660) {
    potvalue=100;
  }
  else if (pot < 660 && pot >=525){
    potvalue=90;
  }
    else if (pot < 525 && pot >=390){
    potvalue=80;
  }
    else if (pot < 390 && pot >=343){
    potvalue=75;
  }
    else if (pot < 343 && pot >=210){
    potvalue=70;
  }
  else if (pot < 210 && pot >=70){
    potvalue=60;
  }
  else if (pot < 70 && pot >=40){
    potvalue=50;
  }
  else if (pot < 40 && pot >=27){
    potvalue=40;
  }
  else if (pot < 27 && pot >=22){
    potvalue=30;
  }
  else if (pot < 22 && pot >=16){
    potvalue=25;
  }
  else if (pot < 16 && pot >=9){
    potvalue=20;
  }
  else if (pot < 9 && pot >=6){
    potvalue=10;
  }
  else if (pot < 6 && pot >=0){
    potvalue=0;
  }   
   Serial.print(potvalue);
   return potvalue;
}

float venturi() {
  Vc = analogRead(0) * 5.00 / 1024;
  P4 = (Vc - OffSet4) * 400;
  
  Vb = analogRead(1) * 5.00 / 1024; 
  P3 = (Vb - OffSet3) * 400;

  //Serial.print("Pressure 4: ");
  //Serial.print (s);
  //Serial.print (P4, 1);
  //Serial.println(" KPa");

  //Serial.print("Pressure 3: ");
  //Serial.print (s);
  //Serial.print(P3, 1);
  //Serial.println(" KPa");

  float diff = P3 - P4;
  Serial.print (s);
  Serial.print(diff);   //pressure in pascal
  Serial.print(s);
  float Var = 4.43455E-05;
  
  // while uploading to blynk multiply with 1000 then flow rate will be Litre/sec
  
  //Serial.print("Flow Rate: ");
  if (diff>0)
  {
    float flow = Var * sqrt((P3-P4)*1000);     // flow rate in m3/sec
    Serial.print (flow*1000);  // flow rate in Litre/Sec
    Serial.print (s);
    return flow;
  }
  else
  {
    float flow=0;
    Serial.print(flow);
    Serial.print(s);
    return flow;
  }

  
}


float single_pressure() 
{
  Va = analogRead(3) * 5.00 / 1024; 
  P1 = (Va - OffSet1) * 400;
  float P11=P1/9.81;
  
//  Serial.println(Va, 3);
  //Serial.print("Pressure Head: ");
//  Serial.print(P1, 1);
//  Serial.print(s);
  Serial.print(P11, 1);
  Serial.print(s);
  //Serial.println(" KPa");

  return P11;
}

int rpm_()
{
  Serial.print(rpm);
  Serial.print(s);
  if (millis() - millisBefore > duration) {
    rpm = (holes / 12.0)*(60000/duration);
    holes = 0;
    millisBefore = millis();
  }
  delay(100);

  return rpm;
}

void count() 
{
  holes++;
}


void loop(){
  int  potvalue1=potentiometer();
  float flowvalue1=venturi();
  float pressurevalue1=  single_pressure();
  int rpmvalue1=  rpm_();
  float  Efficiency=(1.06748E-03)*rpmvalue1/(flowvalue1*pressurevalue1);
  Serial.println(Efficiency);   
  delay(1000);
}
  

//
//Q=Flow/1000;
//H=P1/9.81;
//N=RPM;
//T=We*0.231;
//Efficiency=(1.06748E-03)*N*T/(Q*H);
