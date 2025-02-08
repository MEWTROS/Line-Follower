// Left Sensors Value Initialization
int s1 = 0; //DO ---> Pin 2
int s2 = 0;
int s3 = 0;
// Middle Sensors Value Initialization
int s4 = 0; // D3 ---> Pin 5
int s5 = 0;
// Right Sensors Value Initialization
int s6 = 0;
int s7 = 0;
int s8 = 0; // D7 ---> Pin 9
// 9th Single Sensor (For Stopping) Value Initialization
int s9 = 0;
//1 is white, no red
//0 is black, red
#define led 13 // LED pin

// Motor Speed (PWM)
int spd = 155;

// Motor Pin Declaration
// Left Motor
const int lmf = A5;
const int lmb = A4;

// Right Motor
const int rmb = A2;
const int rmf = A1;

// Speed Controller PWM Pins for Both Motors
#define lpwm 11
#define rpwm 10

// Function declarations (prototypes)
void forward();
void right();
void left();
void Stop();
void sharpRight();
void sharpLeft();

void setup() {
    // Pin 2,3,4,5,6,7,8,9 are for Sensor Array (D0, D1, D2, D3, D4, D5, D6, D7, D8), Set as INPUT
    for (int i = 2; i <= 9; i++) {
        pinMode(i, INPUT);
    }

    // Motor Pin Set for OUTPUT
    pinMode(A5, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A1, OUTPUT);

    // PWM Pins as OUTPUT
    pinMode(lpwm, OUTPUT);
    pinMode(rpwm, OUTPUT);
}

void loop() {
    // Reading Sensor Array Values
    s1 = digitalRead(2);
    s2 = digitalRead(3);
    s3 = digitalRead(4);
    s4 = digitalRead(5);
    s5 = digitalRead(6);
    s6 = digitalRead(7);
    s7 = digitalRead(8);
    s8 = digitalRead(9); 

    // Reading Extra 9th Sensor Value
    s9 = digitalRead(12);

    // Sharp Right Turn (all right sensors detect the line)
    if (s6 == 0 && s7 == 0 && s8 == 0) {
        sharpRight();  // Custom function for sharp right turns
        digitalWrite(led, LOW);
    }

    // Sharp Left Turn (all left sensors detect the line)
    else if (s1 == 0 && s2 == 0 && s3 == 0) {
        sharpLeft();  // Custom function for sharp left turns
        digitalWrite(led, LOW);
    }

    // Forward
    else if (s4 == 0 || s5 == 0) {
        forward();
        digitalWrite(led, LOW);
    }

    // Right
    else if ((s6 == 0 || s7 == 0 || s8 == 0) || (s1==0 && s8==0)) {
        right();
        digitalWrite(led, LOW);
    }

    // Left
    else if (s1 == 0 || s2 == 0 || s3 == 0) {
        left();
        digitalWrite(led, LOW);
    }
    

    // Stop the robot if all sensors detect the line (all sensors are 0)
    if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 0 && s6 == 0 && s7 == 0 && s8 == 0) {
        Stop();
    }
}


void forward() {
    analogWrite(lpwm, spd);
    analogWrite(rpwm, spd);
    digitalWrite(rmf, HIGH);
    digitalWrite(rmb, LOW);
    digitalWrite(lmf, HIGH);
    digitalWrite(lmb, LOW);
    delay(10);
}

void left() {
    analogWrite(lpwm, spd);
    analogWrite(rpwm, spd);
    digitalWrite(rmf, LOW);
    digitalWrite(rmb, HIGH);
    digitalWrite(lmf, HIGH);
    digitalWrite(lmb, LOW);
    delay(10);
}

void right() {
    analogWrite(lpwm, spd);
    analogWrite(rpwm, spd);
    digitalWrite(rmf, HIGH);
    digitalWrite(rmb, LOW);
    digitalWrite(lmf, LOW);
    digitalWrite(lmb, HIGH);
    delay(10);
}

void Stop() {
    analogWrite(lpwm, spd);
    analogWrite(rpwm, spd);
    digitalWrite(rmf, LOW);
    digitalWrite(rmb, LOW);
    digitalWrite(lmf, LOW);
    digitalWrite(lmb, LOW);
    digitalWrite(led, HIGH); // Turn on LED when stopping
}

void sharpRight() {
    // Right motor moves forward, left motor moves backward for a sharp right pivot
    analogWrite(lpwm, spd);  // Adjust speed if needed
    analogWrite(rpwm, spd);
    digitalWrite(rmf, HIGH);
    digitalWrite(rmb, LOW);  // Right motor forward
    digitalWrite(lmf, LOW);  // Left motor backward
    digitalWrite(lmb, HIGH);
    delay(100);  // Adjust delay for desired sharpness of turn
}

void sharpLeft() {
    // Left motor moves forward, right motor moves backward for a sharp left pivot
    analogWrite(lpwm, spd);  // Adjust speed if needed
    analogWrite(rpwm, spd);
    digitalWrite(rmf, LOW);  // Right motor backward
    digitalWrite(rmb, HIGH);
    digitalWrite(lmf, HIGH); // Left motor forward
    digitalWrite(lmb, LOW);
    delay(100);  // Adjust delay for desired sharpness of turn
}
