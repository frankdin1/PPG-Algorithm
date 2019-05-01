/*
 * Code written by Frank Din for UTA Senior Design Project
 * */
 #include <TFT.h>  // Arduino LCD library
 #include <SPI.h>
/*// SPI pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8
#define mosi  11
#define sclk  13
*/
// SPI pin definition for the Mega. Check the SPI page on Arduino website for more info
#define cs   10
#define dc   9
#define rst  8
#define sda  51
#define scl  52
TFT screen = TFT(cs, dc, rst);// create an instance of the screen library
unsigned long peaktArr[11], pAndt[2][3]; //peaktArr stores the peak values from pAndt; pAndt stores the values from the sensor which are compared to one another to determine a peak
 float tdiff[10];//array to store time difference between consecutive time stamps
  int i = 0;
  int j = 0;
  int k = 0;
  float inst_f = 0;
  int p = 0;
  int a = 0;
  unsigned long calb;
  int xPos = 0;
void setup(){//the entire code in this loop will only happen 1 time
  Serial.begin(9600);
  screen.begin();
  screen.setTextSize(2);
  screen.background(0, 0, 255);
  unsigned long delayTime = millis();//millis() stores the amount of time in milliseconds that has passed since it was introduced into the program. This value is then passed into the variable delayTime
  while(millis() - delayTime <= 3000){ // delayTime has a set value and will not change and the program within the the while loop will run as long the difference between the time that has passed and delayTime is less than 3000 milliseconds or 3 seconds
   screen.setCursor(0,0);//the first value in the bracket determines the column posistion (right or left) while the second value deteermines the row position (up or down)
   screen.print("Welcome To");
   screen.setCursor(0,25);
   screen.print("Chelsea's");
   screen.setCursor(0,50);
   screen.print("Heart Rate");
   screen.setCursor(0,75);
   screen.print("Device");
  }
  screen.background(0,0,255);//make the background color red
  delayTime = millis(); //once again, store the value of time passed
  while(millis() - delayTime <= 3000){
  screen.setCursor(0,0);
  screen.print("Place Finger");
  screen.setCursor(0,25);
  screen.print("On Sensor");
  }
  screen.background(0,0,255);
  screen.setCursor(0,50);
  screen.print("Calibrating");
  
  for(i = 0; i < 3; i++){//read and store 3 values at a time in pAndt   
      unsigned long delayTime = millis();
      pAndt[0][i] = analogRead(A0);//1st row of pAndt stores the sensor values
      pAndt[1][i] = millis();// 2nd row of pAndt stores the time stamp of the sensor values
      while (millis() - delayTime  <=200){//wait 200 ms before reading the next sensor values. this means we read 5 values every second
      }
    }
    for(i = 1; i < 2; i++){   
      if(pAndt[0][i]>pAndt[0][i-1] && pAndt[0][i]>pAndt[0][i+1]){ //compare the 3 values in pAndt to determine a peak
          peaktArr[0] = pAndt[1][i];// store the value of i that satisfies the peak condition
      }
    }
    
  while(j<11){
    //replace the values of the 1st column with those of the 2nd column
    pAndt[0][0] = pAndt[0][1];//replace the values in row 1
    pAndt[1][0] = pAndt[1][1];//replace the values in row 2
   
    //replace the values of the 2nd column with those of the 3rd column
    pAndt[0][1] = pAndt[0][2];//replace the values in row 1
    pAndt[1][1] = pAndt[1][2];//replace the values in row 2
   
    unsigned long delayTime = millis();//
    for(i = 2; i < 3; i++){//read and store 1 value in the 3rd column of pAndt 
      pAndt[0][i] = analogRead(A0);//1st row of pAndt stores the sensor values
      pAndt[1][i] = millis();// 2nd row of pAndt stores the time stamp of the sensor values
      while (millis() - delayTime  <=200){//delay in ms before reading the next value
      }
    }
    for(i = 1; i < 2; i++){   
      if(pAndt[0][i]>pAndt[0][i-1] && pAndt[0][i]>pAndt[0][i+1]){ //compare the 3 values in pAndt to determine a peak
          peaktArr[j++] = pAndt[1][i];// store the value of i that satisfies the peak condition, and do the comparison above until j is 10
      }
    }
  }
    for(i = 0; i < 10; i++){
        tdiff[k++] = (((float)peaktArr[i+1] - (float)peaktArr[i])/1000);//change the time values from unsigned long to float, take the difference between consecutive time values, and convert the result to time in seconds
    }
     for(i = 0; i < 10; i++){
        inst_f = inst_f + (1/tdiff[i]);//convert the time differences to frequencies and take their sum
    }
}

void loop(){
 int xPos = 0;//the position of the x-value which will be used to draw the waveform
 float inst_f = 0;
 for(i = 2; i<11; i++){
  peaktArr[i-2] = peaktArr[i];//remove the 1st 2 values from the peaktArr array and shift all the values until the last 2 "spots" in the array are empty
  }
  j = 9;

  for(i = 1; i<10; i++){
  tdiff[i-1] = tdiff[i];
  }
  while(j<11){
    pAndt[0][0] = pAndt[0][1];
    pAndt[1][0] = pAndt[1][1];

    pAndt[0][1] = pAndt[0][2];
    pAndt[1][1] = pAndt[1][2];
    unsigned long delayTime = millis();//
    for(i = 2; i < 3; i++){//read and store 1 value at a time in pAndt   
      pAndt[0][i] = analogRead(A0);//1st row of pAndt stores the sensor values
      pAndt[1][i] = millis();// 2nd row of pAndt stores the time stamp of the sensor values
      while (millis() - delayTime  <=100){//delay in ms before reading the next value
      }
    }
   
    for(i = 1; i < 2; i++){   
      if(pAndt[0][i]>pAndt[0][i-1] && pAndt[0][i]>pAndt[0][i+1] /*&& pAndt[0][i] >= 0.3*hp*/){ //compare the 3 values in pAndt to determine a peak
          peaktArr[j++] = pAndt[1][i];// store the value of i that satisfies the peak condition, and do the comparison above until j is 10
      }
    }
  }
    tdiff[9] = (((float)peaktArr[10] - (float)peaktArr[9])/1000);
     for(i = 0; i < 10; i++){
        inst_f = inst_f + (1/tdiff[i]);
    }
    screen.background(0,0,255);
    screen.setCursor(0,0);//the 1st value in brackets sets the distance from the left edge of the screen, and the 2nd value sets the distance from the top edge of the screen
    screen.print("Heart rate ");
    screen.setCursor(0,20);
    screen.print((inst_f/10)*60);
    screen.setCursor(75,20);
    screen.println(" bpm");

    while(xPos<=160){
    int sensor = analogRead(A0); 
    int graphHeight = map(sensor,0,682,5,screen.height()/1.5);
    screen.stroke(255,255,255);
    //xPos*2 causes the waveform to reach the end of the screen after 5 s
    screen.line(xPos, (screen.height() - graphHeight), xPos, screen.height() - graphHeight+3); //screen.height() - graphHeight + 5 affects the thickness of the line. The bigger the number you add to screen.height() - graphHeight is, the thicker the line will be
    xPos++;
    unsigned long delayTime = millis();
    while(millis() - delayTime<=25){
    }
 }
  screen.background(0,0,255);//1st value is blue, 2nd value is green and 3rd value is red
  screen.print("Calculating..");
  unsigned long delayTime = millis();
  //while (millis()- delayTime <= ){
  //}
}
