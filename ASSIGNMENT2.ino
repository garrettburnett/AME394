//ASSIGNMENT 2
int analog_no = 5 ;// define A5 as input signal pin

int pins[] = {3,5,6,9,10};
 int fadeValue =250;
void setup() {
Serial.begin(9600);
}

void loop() {
  // fade in from min to max in increments of 5 points:
 
  // fade out from max to min in increments of 5 points:

  int pin_value;
  int temperature;
  
  pin_value = analogRead(analog_no);
  
  temperature = (125*pin_value)>>8 ;
  Serial.print("Current temperature is ") ;
  temperature-=60;
  temperature = temperature * 9/5 +32;
  Serial.print(temperature) ;
  Serial.println("F");


  int meterPerc = map (temperature, 70, 150,0,100);
   Serial.println(meterPerc);

 for (int thisLed = 0; thisLed < 5; thisLed++) {
    // if the array element's index is less than ledLevel,
    // turn the pin for this element on:

   if(meterPerc<=10){analogWrite(pins[0], 40);}
   if(meterPerc>10 && meterPerc <=20){analogWrite(pins[0], 255);}

   if(meterPerc > 20 && meterPerc <=30){analogWrite(pins[0], 255);
                analogWrite(pins[1], 40);
   }

   if(meterPerc > 30 && meterPerc <=40){analogWrite(pins[0], 255);
                analogWrite(pins[1], 255);
   }

   if(meterPerc > 40 &&  meterPerc<=50){analogWrite(pins[0], 255);
                analogWrite(pins[1], 255);
                analogWrite(pins[2], 40);
   }
   if(meterPerc > 50 && meterPerc <=60){analogWrite(pins[0], 255);
                analogWrite(pins[1], 255);
                analogWrite(pins[2], 255);
   }

   if(meterPerc > 60 && meterPerc <=70){analogWrite(pins[0], 255);
                analogWrite(pins[1], 255);
                analogWrite(pins[2], 255);
                analogWrite(pins[3], 40);
   }

   if(meterPerc  > 70 && meterPerc <=80){analogWrite(pins[0], 255);
                analogWrite(pins[1], 255);
                analogWrite(pins[2], 255);
                analogWrite(pins[3], 255);
   }

   if(meterPerc  > 80 && meterPerc <=90){analogWrite(pins[0], 255);
                analogWrite(pins[1], 255);
                analogWrite(pins[2], 255);
                analogWrite(pins[3], 255);
                analogWrite(pins[4], 40);
   }

    if(meterPerc  > 90 && meterPerc <= 100){analogWrite(pins[0], 255);
                analogWrite(pins[1], 255);
                analogWrite(pins[2], 255);
                analogWrite(pins[3], 255);
                analogWrite(pins[4], 255);
   }
   
 
    
 }
}


