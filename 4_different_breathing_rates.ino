#include <AP_Sync.h>


AP_Sync streamer(Serial);

int pump2 = 8;
int pump1 = 9;
//bool runYet = false;

void setup() {
  pinMode(pump1, OUTPUT);
  pinMode(pump2, OUTPUT);
  Serial.begin(9600);
  pinMode(12, OUTPUT);

  streamer.sync("location", String(0));
}


void loop() {

  streamer.sync("location", String(0));

  //  char option;
  // 4 different options
  //when you type "1" it will run the code for sighing.
  //when you type "2" the code for sleep will run
  //when you type "3" the code for scared wil run
  //when you type "4" the code for anxious will run


  while (Serial.available() > 0) {

    streamer.sync("pump1", pump1);
    streamer.sync("pump2", pump2);
    //    option = Serial.read();
    String option = Serial.readString();
    if (option == "1") { //sighing
      //      streamer.sync("function", option);
      sighing();
    }

    if (option == "2") { //sleep
      sleep();

    }

    if (option == "3") { //anxious
      anxious();
    }

    if (option == "4") { //off
      off();
    }
  }

}

//these loops run only once!!
void sighing() { //press 1 - inhalation time is much longer than exhalation time. Meant to test if it gives the idea of boredom
  for (int i = 0; i < 3; i++) {
    analogWrite(pump1, 255);
    analogWrite(pump2, 0);
    //    Serial.println("working");
    for (int i = 0; i <= 3000; i += 16) {
      streamer.sync("location", String(i));
    }
    analogWrite(pump1, 0);
    analogWrite(pump2, 255);
    for (int i = 3000; i >= 0; i -= 30) {
      streamer.sync("location", String(i));
    }
  }
  analogWrite(pump1, 0);
  analogWrite(pump2, 0);
  Serial.println("done_sighing");
  digitalWrite(12, LOW);
}

void sleep() { //press 2 - inhalation and exhalation time are the same . Test if it gives the idea of sleepiness
  for (int i = 0; i < 4; i++) {
    analogWrite(pump1, 255);
    analogWrite(pump2, 0);
    for (int i = 0; i <= 3000; i += 16) {
      streamer.sync("location", String(i));
    }
    analogWrite(pump1, 0);
    analogWrite(pump2, 255);
    for (int i = 3000; i >= 0; i -= 16) {
      streamer.sync("location", String(i));
    }
  }
  analogWrite(pump1, 0);
  analogWrite(pump2, 0);
  Serial.println("done_sleep");
}


void anxious() { //press 3 - trembling and shaking inhalation and exhalation time. Meant to test if it gives the idea of anxiousness/nervousness

  //setting the bag up with some air inside so the fluctuations are noticeble
  //digitalWrite(12, HIGH);
  analogWrite(pump1, 255);
  analogWrite(pump2, 0);
  for (int i = 0; i <= 3000; i += 20) {
    streamer.sync("location", String(i));
  }

  //up and down movement that happens every 200 miliseconds, 25 times
  for (int i = 0; i < 15; i++) {
    analogWrite(pump1, 0);
    analogWrite(pump2, 255);
    for (int i = 0; i <= 500; i += 20) {
      streamer.sync("location", String(i));
    }
    analogWrite(pump1, 255);
    analogWrite(pump2, 0);
    for (int i = 500; i >= 0; i -= 20) {
      streamer.sync("location", String(i));
    }
  }

  //turning both pumps off
  analogWrite(pump1, 0);
  analogWrite(pump2, 0);
  Serial.println("done_anxious");
}


void off() { //press 4 - completly off, no sound. Meant to test if it gives the idea of aliveness/death
  analogWrite(pump1, 0);
  analogWrite(pump2, 0);
  streamer.sync("location", String(0));
  Serial.println("done_off");

}


