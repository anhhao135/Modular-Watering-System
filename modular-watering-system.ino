#include <Servo.h>
#include <Stepper.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <rotary.h>


Rotary r = Rotary(2, 3,4);        // there is no must for using interrupt pins !!
// Half-step mode
#define HALF_STEP

// Define I2C_LCD
LiquidCrystal_I2C  lcd(0x27, 20,4);


// Define your Function information

int maxNumber = 14;
char* myFunctions[] = {
  "Home Module 1",
  "Home Module 2",
  "Home Module 3",
  "Check Water Level",
  "Turn Pump On",
  "Turn Pump Off",
  "Module 1 Moisture",
  "Module 2 Moisture",
  "Module 3 Moisture",
  "Check Temperature",
  "Check Humidity",
  "Water Module 1",
  "Water Module 2",
  "Water Module 3",
};

int x = 0;



#define DHT11_PIN 12
#define STEPS 2038


#define FULL_MOISTURE_1 290
#define NO_MOISTURE_1 620
#define FULL_MOISTURE_2 250
#define NO_MOISTURE_2 590
#define FULL_MOISTURE_3 290
#define NO_MOISTURE_3 600 //callibrate lower and upper ranges of moisture sensors


#define ANGLE_1 22
#define ANGLE_2 46
#define ANGLE_3 70

#define LOWERED_ANGLE 45
#define RETRACT_ANGLE 95


dht DHT;


Stepper moduleOne (STEPS,25,23,24,22);
Stepper moduleTwo (STEPS,33,31,32,30);
Stepper moduleThree (STEPS,49,47,48,46);






int basePin = 10;
int armPin = 11;
int relayPin = 7;
int colOne = A0;
int colTwo = A1;
int colThree = A2;
int moistOne = A3;
int moistTwo = A4;
int moistThree = A5;



Servo base;
Servo arm;


void setup() {
  // put your setup code here, to run once:


  Serial.begin(9600);


   lcd.begin();
  lcd.backlight();
  
  lcd.clear (); // go home
  lcd.setCursor(0,0);
  
  lcd.print ("Modular Watering");
  lcd.setCursor(0, 1);
  lcd.print("System");
  lcd.setCursor(0, 2);
  lcd.print("M.W.S.");
  lcd.setCursor(0,3);
  lcd.print("(c) TREEHUGGERS 2019");
  
  delay(3000);
  lcd.clear();
  
  lcd.print("Select Function");
  delay(2000);
  //lcd.backlight();                      // only needed for 0x3F I2C Adapter

  // ------- Quick 3 blinks of backlight  -------------
  blinkLCD();

  char lcdline1[20];
  sprintf (lcdline1, "Function #:  %02i", x + 1);    // index starts at 0
  lcd.setCursor(0, 0);
  lcd.print (lcdline1);
  lcd.setCursor(0, 1);
  lcd.print(myFunctions[x]);


 
pump_off();

  
  
moduleOne.setSpeed(10);
moduleTwo.setSpeed(10);
moduleThree.setSpeed(10);


delay(1000);




}


void loop() {




  volatile unsigned char result = r.process();
  if (result) {
    result == DIR_CCW ? x = x - 1 : x = x + 1;

    if (x < 0) {             // no values < 0; later: use unsigned int
      blinkLCD();
      x = maxNumber - 1;    // roll over
    }

    if (x > maxNumber - 1) {           // no more strings
      // ------- Quick 3 blinks of backlight  -------------
      blinkLCD();
      x = 0;                 // roll over
    }

    char lcdline1[13];
    sprintf (lcdline1, "Function #:  %02i", x + 1);
    lcd.setCursor(0, 0);
    lcd.print (lcdline1);
    lcd.setCursor(0, 1);
    lcd.print("                      ");              // erase previous content
    lcd.setCursor(0, 1);
    lcd.print(myFunctions[x]);


  }

  if (r.buttonPressedReleased(25)) {

    switch (x) {
      case 0:
        lcdScreen1();
        Function_1();                    
        break;
      case 1:
        lcdScreen1();
        Function_2();                      
        break;
      case 2:
        lcdScreen1();
        Function_3();                      
        break;
      case 3:
        lcdScreen1();
        Function_4();                       
        break;
      case 4:
        lcdScreen1();
        Function_5();                     
        break;
      case 5:
        lcdScreen1();
        Function_6();                     
        break;
      case 6:
        lcdScreen1();
        Function_7();                     
        break;
      case 7:
        lcdScreen1();
        Function_8();                      
        break;
      case 8:
        lcdScreen1();
        Function_9();                      
        break;
      case 9:
        lcdScreen1();
        Function_10();                      
        break;
      case 10:
        lcdScreen1();
        Function_11();                      
        break;
      case 11:
        lcdScreen1();
        Function_12();                      
        break;
      case 12:
        lcdScreen1();
        Function_13();                      
        break;
      case 13:
        lcdScreen1();
        Function_14();                      
        break;

    }
    blinkLCD();
    lcd.clear (); // go home
    lcd.print ("");
    lcd.setCursor(0, 1);
    lcd.print("Function Executed!");           //
    delay(1500);
    //lcd.backlight();                      // only needed for 0x3F I2C Adapter

    // ------- Quick 3 blinks of backlight  -------------
    blinkLCD();
    x = 0;                                  // reset to start position
    lcd.clear();
    char lcdline1[13];
    sprintf (lcdline1, "Function #:  %02i", x + 1);
    lcd.print (lcdline1);
    lcd.setCursor(0, 1);
    lcd.print(myFunctions[x]);
  }

  



  
  
  
}



void homePlate (int module){
  
  if(module == 1){

        lcd.clear();
    lcd.print("HOMING MODULE 1");
    
  while(analogRead(colOne) > 500){
    moduleOne.step(1);

    
    
  }
  }

   if(module == 2){

        lcd.clear();
    lcd.print("HOMING MODULE 2");
  while(analogRead(colTwo)> 500){
    moduleTwo.step(1);


  }
  }

   if(module == 3){

        lcd.clear();
    lcd.print("HOMING MODULE 3");
  while(analogRead(colThree) > 500){
    moduleThree.step(1);

  }
  }


  digitalWrite(25, LOW);
  digitalWrite(23, LOW);
  digitalWrite(24, LOW);
  digitalWrite(22, LOW);

  digitalWrite(30, LOW);
  digitalWrite(31, LOW);
  digitalWrite(32, LOW);
  digitalWrite(33, LOW);

  digitalWrite(46, LOW);
  digitalWrite(47, LOW);
  digitalWrite(48, LOW);
  digitalWrite(49, LOW);


lcd.clear();
lcd.print("MODULE ");
lcd.print(module);
lcd.print(" HOMED!");
delay(200);


  

}






double check_moisture(int module){

  if(module == 1){
    double raw = analogRead(moistOne);
    double percent = (NO_MOISTURE_1 - raw) / (NO_MOISTURE_1 - FULL_MOISTURE_1);
    lcd.clear();
    lcd.print("MODULE 1 MOISTURE:");
    lcd.setCursor(0,1);
    lcd.print(percent*100);
    lcd.print(" %");
    delay(100);
    
    return percent * 100;
    
  }

    if(module == 2){
    double raw = analogRead(moistTwo);
    double percent = (NO_MOISTURE_2 - raw) / (NO_MOISTURE_2 - FULL_MOISTURE_2);
    lcd.clear();
    lcd.print("MODULE 2 MOISTURE:");
    lcd.setCursor(0,1);
    lcd.print(percent*100);
    lcd.print(" %");
    delay(100);
    return percent * 100;
    
  }

    if(module == 3){
    double raw = analogRead(moistThree);
    double percent = (NO_MOISTURE_3 - raw) / (NO_MOISTURE_3 - FULL_MOISTURE_3);
    lcd.clear();
    lcd.print("MODULE 3 MOISTURE:");
    lcd.setCursor(0,1);
    lcd.print(percent*100);
    lcd.print(" %");
    delay(100);
    
    return percent * 100;
    
  }

  
}


double check_temperature(){

  int chk = DHT.read11(DHT11_PIN);

  delay(500);

  lcd.clear();
  lcd.print("TEMPERATURE: ");
  lcd.print((int)DHT.temperature);
  lcd.print(" C");

  lcd.setCursor(0,2);
  lcd.print("FOR AMERICANS: ");
  lcd.print((int)((DHT.temperature * 1.8) + 32));
  lcd.print(" F");
  

  return DHT.temperature; //has a period of 1.5s.
}


double check_humidity(){

  int chk = DHT.read11(DHT11_PIN);


  delay(500);

  lcd.clear();
  lcd.print("HUMIDITY: ");
  lcd.print((int)DHT.humidity);
  lcd.print(" %");
  

  return DHT.humidity; //has a period of 1.5s.
}


bool check_waterlevel(){

  int raw = analogRead(A8);

  if (raw <950){
    lcd.clear();
    lcd.print("WATER LEVEL OK!");
    delay(100);
    
    return 1;
  }
  
  else{
    lcd.clear();
    lcd.print("WATER LOW");
    delay(300);
    return 0;
  }



  
  
}





void move_base_to(int module){
  
  base.attach(basePin);

  if (module == 1){
    base.write(ANGLE_1);
    }

  if (module == 2){
    base.write(ANGLE_2);
    }

  if (module == 3){
    base.write(ANGLE_3);
    }


delay(2000);


  base.detach();

}



void lower_arm(){

int angle;

  

arm.attach(armPin);

  for(angle = RETRACT_ANGLE; angle > LOWERED_ANGLE ; angle--)  
  {                                  
    arm.write(angle);               
    delay(15);                   
  } 
}

void retract_arm(){


int angle;

  for(angle = LOWERED_ANGLE; angle < RETRACT_ANGLE ; angle++)  
  {                                  
    arm.write(angle);               
    delay(15);                   
  } 


  delay(1000);
  

  arm.detach();
  
}



void pump_on(){

  pinMode(relayPin, OUTPUT);
  

  digitalWrite(relayPin, LOW);
}



void pump_off(){

  digitalWrite(relayPin, HIGH);
}




int water_until_moist(int module){

  lcd.clear();
  lcd.print("WATERING MODULE ");
  lcd.print(module);

  delay(500);
  
  



  pinMode(relayPin, OUTPUT);



 
  if (module == 3){

    int water_level = check_waterlevel();
    int moisture = check_moisture(3);


    move_base_to(3);
    lower_arm();
    delay(1000);

   
    if (check_moisture(3) > 90){

      retract_arm();
      return 1;
      
    }

    if(check_waterlevel == 0){

      retract_arm();
      return 0;
    }
    

    while (water_level == 1 && moisture <90 ){

    moisture = check_moisture(3);
    water_level = check_waterlevel();

      pump_on();
      
    }

    pump_off();

    delay(500);
    

    retract_arm();

        lcd.clear();
  lcd.print("MODULE ");
  lcd.print(module);
  lcd.print(" WATERED!");

      if(check_waterlevel == 0){

      retract_arm();
      return 0;
    }



    else return 1;

  }





  if (module == 2){

    int water_level = check_waterlevel();
    int moisture = check_moisture(2);


    move_base_to(2);
    lower_arm();
    delay(1000);

   
    if (check_moisture(2) > 90){

      retract_arm();
      return 1;
      
    }

    if(check_waterlevel == 0){

      retract_arm();
      return 0;
    }
    

    while (water_level == 1 && moisture <90 ){

    moisture = check_moisture(2);
    water_level = check_waterlevel();

      pump_on();
      
    }

    pump_off();

    delay(500);
    

    retract_arm();

        lcd.clear();
  lcd.print("MODULE ");
  lcd.print(module);
  lcd.print(" WATERED!");

      if(check_waterlevel == 0){

      retract_arm();
      return 0;
    }



    else return 1;

  }






    if (module == 1){

    int water_level = check_waterlevel();
    int moisture = check_moisture(1);


    move_base_to(1);
    lower_arm();
    delay(1000);

   
    if (check_moisture(1) > 90){

      retract_arm();
      return 1;
      
    }

    if(check_waterlevel == 0){

      retract_arm();
      return 0;
    }
    

    while (water_level == 1 && moisture <90 ){

    moisture = check_moisture(1);
    water_level = check_waterlevel();

      pump_on();
      
    }

    pump_off();

    delay(500);
    

    retract_arm();

        lcd.clear();
  lcd.print("MODULE ");
  lcd.print(module);
  lcd.print(" WATERED!");

      if(check_waterlevel == 0){

      retract_arm();
      return 0;
    }



    else return 1;

  }


  }




void plate_counterclockwise (int module){


  if (module == 1){
    moduleOne.step(1);
  }

  if (module == 2){
    moduleTwo.step(1);
  }

  if (module == 3){
    moduleThree.step(1);
  }


  
}

void plate_clockwise (int module){


  if (module == 1){
    moduleOne.step(-1);
  }

  if (module == 2){
    moduleTwo.step(-1);
  }

  if (module == 3){
    moduleThree.step(-1);
  }


  
}


void homeAll(){

  homePlate(1);
  homePlate(2);
  homePlate(3);
  
}





void blinkLCD() {
  for (int i = 0; i < 3; i++)
  {
    lcd.noBacklight();
    delay(50);
    lcd.backlight();
    delay(50);
  }
}

void lcdScreen1() {                                   // instead of the real mixing process, just for demo

  lcd.setCursor(0, 0);
  lcd.print("Now Executing   ");
  // scroll 13 positions (string length) to the left
  // to move it offscreen left:
  for (int positionCounter = 0; positionCounter < 5; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(200);
  }

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 5; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(200);
  }

}

void Function_1() {

  homePlate(1);
  // produce the requested Function -> stepper motor actions
}

void Function_2() {
  homePlate(2);
  
  // produce the requested Function -> stepper motor actions
}

void Function_3() {
  homePlate(3);
  
  // produce the requested Function -> stepper motor actions
}

void Function_4() {
  while(digitalRead(4) == 1){

    check_waterlevel();
    
    
  }

  
  
  // produce the requested Function -> stepper motor actions
}

void Function_5() {

 while(digitalRead(4) == 1){

  pump_on();
 }


 pump_off();
 
  
  // produce the requested Function -> stepper motor actions
}

void Function_6() {

  pump_off();
  // produce the requested Function -> stepper motor actions
}

void Function_7() {

   while(digitalRead(4) == 1){

  check_moisture(1);
  delay(2500);
   }
  
  // produce the requested Function -> stepper motor actions
}

void Function_8() {

 while(digitalRead(4) == 1){
  
  check_moisture(2);
  delay(2500);
  // produce the requested Function -> stepper motor actions
}
}

void Function_9() {

   while(digitalRead(4) == 1){

  
  check_moisture(3);
  delay(2500);
  // produce the requested Function -> stepper motor actions
}

}

void Function_10() {

    while(digitalRead(4) == 1){

        check_temperature();
  delay(2500);
    
  }



  
  // produce the requested Function -> stepper motor actions
}

void Function_11() {


 while(digitalRead(4) == 1){
  

  check_humidity();
  delay(2500);

 }
  
  
  // produce the requested Function -> stepper motor actions
}

void Function_12() {

  water_until_moist(1);
  // produce the requested Function -> stepper motor actions
}

void Function_13() {

  water_until_moist(2);
  // produce the requested Function -> stepper motor actions
}

void Function_14() {

  water_until_moist(3);
  // produce the requested Function -> stepper motor actions
}



void demo(){

  while(digitalRead(4) == 1){
    
  }


  
}

  
