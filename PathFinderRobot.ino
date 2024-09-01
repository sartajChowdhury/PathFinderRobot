// ---------------------------------------------------------------------------
// Example NewPing library sketch that pings 3 sensors 20 times a second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define SONAR_NUM 2      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define front 3
#define left 5
#define pwmleftwheel 6
#define pwmrightwheel 9
#define buzzer 4

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(12, 11, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(8, 7, MAX_DISTANCE)
};

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(front, OUTPUT);
  digitalWrite(front, LOW);
  pinMode(left, OUTPUT);
  digitalWrite(left, LOW);
  analogWrite(pwmleftwheel, 40);
  analogWrite(pwmrightwheel, 30);
}

void loop() {
  delay(75);
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print(i);
    Serial.print("=");
    Serial.print(sonar[i].ping_cm());
    Serial.print("cm ");
  }

  int front_dist = sonar[0].ping_cm();
  int left_dist = sonar[1].ping_cm();
  int left_thresh = 21;
  int front_thresh = 21;

  bool front_close = (front_dist <= front_thresh) && (front_dist > 1);
  bool left_close = (left_dist <= left_thresh) && (left_dist > 1 );

 
  if (front_close){
    digitalWrite(front,HIGH);
    Serial.print("CLOSE111 ");
    }
  if (!front_close){
    digitalWrite(front,LOW);
    Serial.print("FAR111 ");
    }
  if (!left_close){
    digitalWrite(left,LOW);
    Serial.print("FAR");
    }
  if (left_close){
    digitalWrite(left,HIGH);
    Serial.print("CLOSE");
  }

  if(left_close && front_close){
    analogWrite(pwmleftwheel, 85);
    }

  if(left_close && !front_close){
    analogWrite(pwmleftwheel,38);
    analogWrite(pwmrightwheel, 31);
  }

  if(!left_close){
    digitalWrite(front,LOW);
    analogWrite(pwmrightwheel, 46);
    digitalWrite(left,LOW);
    delay(75);
    analogWrite(pwmleftwheel, 38);
    analogWrite(pwmrightwheel, 27);
    //go straight
    digitalWrite(left,HIGH);
    delay(75);
  }

  int thermoVal = analogRead(3);
 
  if(thermoVal > 270){
    analogWrite(pwmrightwheel, 0);
    analogWrite(pwmleftwheel, 0);
    analogWrite(buzzer, 255);
    delay(100000000);
  }
 
  Serial.println();
}
