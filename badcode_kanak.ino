#define THRESHOLD 700
int f = 90;
int m = 70;
int s = 50;

//int sensor[] = {14, 15, 16, 17, 18};
int sensor[] = {62, 61, 60, 59, 58, 57, 56, 55};
int leftMotor[] = {3, 4};
int rightMotor[] = {5, 6};
int extra = 52;


String pattern = "00000000";
String conPattern;
void setMotors(int leftSpeed, int rightSpeed)
{
  if (leftSpeed >= 0 && rightSpeed >= 0)
  {
    analogWrite(leftMotor[0], leftSpeed);   /*   Forward  */
    analogWrite(leftMotor[1], 0);
    analogWrite(rightMotor[0], rightSpeed);
    analogWrite(rightMotor[1], 0);
  }

  else if (leftSpeed < 0 && rightSpeed < 0)
  {
    leftSpeed = -leftSpeed;
    rightSpeed = -rightSpeed;

    analogWrite(leftMotor[0], 0);
    analogWrite(leftMotor[1], leftSpeed);
    analogWrite(rightMotor[0], 0);
    analogWrite(rightMotor[1], rightSpeed);    /* Backward */
  }

  else if (leftSpeed == 0 && rightSpeed >= 0)
  {
    analogWrite(leftMotor[0], 0);                     /*Left */
    analogWrite(leftMotor[1], 0);
    analogWrite(rightMotor[0], rightSpeed);
    analogWrite(rightMotor[1], 0);
  }

  else if (leftSpeed >= 0 && rightSpeed == 0)

  {
    analogWrite(leftMotor[0], leftSpeed);
    analogWrite(leftMotor[1], 0);
    analogWrite(rightMotor[0], 0);  /*right */
    analogWrite(rightMotor[1], 0);
  }

  else if (leftSpeed >= 0 && rightSpeed <= 0)
  {
    rightSpeed = - rightSpeed;
    analogWrite(leftMotor[0], leftSpeed);  /* turn clockwise */
    analogWrite(leftMotor[1], 0);
    analogWrite(rightMotor[0], 0);
    analogWrite(rightMotor[1], rightSpeed);
  }

  else if (leftSpeed <= 0 && rightSpeed >= 0)
  {

    leftSpeed = - leftSpeed;
    analogWrite(leftMotor[0], 0);
    analogWrite(leftMotor[1], leftSpeed);   /* turn anti clockwise */
    analogWrite(rightMotor[0], rightSpeed);
    analogWrite(rightMotor[1], 0);
  }

}
String getPattern()
{
  //int i;
  for (int i = 0; i < 8 ; i++)
  {
    if (analogRead(sensor[i]) < THRESHOLD) {
      // Serial.println(analogRead(sensor[i]));

      pattern[i] = '0';

    } else {
      // Serial.println(analogRead(sensor[i]));
      pattern[i] = '1';

    }
  }
	 pattern[8] = '\0';
   Serial.println(pattern);
   return pattern;

}

void setup()
{
  Serial.begin(9600);
  Serial.println("Ready");

  pinMode(extra, OUTPUT);
  //digitalWrite(extra, HIGH);

  for (int i = 0; i < 2 ; i++)
  {
    pinMode(leftMotor[i], OUTPUT);
    pinMode(rightMotor[i], OUTPUT);
  }

  for (int i = 0; i < 8; i++)
  {
    pinMode(sensor[i], INPUT);
  }
}



void loop()
{
  getPattern();
  if ((pattern[1] == '1'&&(pattern[0] != '1'||/* pattern[1] == '1' ||*/ (pattern[1] == '1' && pattern[2] == '1'))&&(pattern[7] != '1'&&pattern[6] != '1')))
      {
      //setMotors(0,0);
     // delay(20);
      setMotors(0,80);
      delay(25);
      //setMotors(80,80);
      
    }
else if ((pattern[6] == '1'||/* pattern[6] == '1' ||*/ (pattern[6] == '1' && pattern[5] == '1'))&&(pattern[0] != '1'&&pattern[1] != '1'))
     {
     // setMotors(0,0);
     // delay(20);
      setMotors(80,0);
      delay(25);
      //setMotors(80,80);
      
    }
else if (pattern[0] != '1'&& pattern[7] != '1'&&pattern[1] != '1'&&pattern[6] != '1'&& ( pattern[2] == '1'|| pattern[3] == '1'|| pattern[4] == '1'|| pattern[5] == '1'))
  setMotors(125, 125);
  
//else if (pattern[0] == '1'&& pattern[7] != '1' && pattern[1] == '1' && pattern[2] == '1' && ( pattern[4] == '1' || pattern[5] == '1'))
  else if(pattern == "11111110" || pattern == "11111100" ||pattern == "11111000")
  {
  setMotors(0,0);
  delay(50);
  setMotors(0, 100);
  delay(600);
  }
//else if (pattern[7] == '1'&& pattern[0] != '1'&& pattern[6] == '1' && pattern[5] == '1'&&(pattern[4] == '1' || pattern[3] == '1'))
  
  else if(pattern == "01111111" || pattern == "00111111" ||pattern == "00011111")
 // else if(pattern[0] == '0'&&(pattern == "01111111" || pattern == "00111111" ||pattern == "00011111"))
  {
    //Serial.println("WTF");
 /* setMotors(0,0);
  delay(50);
  setMotors(100,0);
  delay(500);*/
  
  setMotors(80,100);
  delay(300);
  conPattern = getPattern();
  //conPattern = pattern;
  if (conPattern == "00000000")
    {
    setMotors(100,0);
    delay(600);
    }
  else 
    setMotors(100,100);  
  }
else if(pattern == "00000000")
	setMotors(0,0);
else if(pattern == "11111111")
  {
  setMotors(0,0);
  delay(100);
  setMotors(0, 100);
  delay(600);
  }/*
else if(pattern == "10000000")
    {
    setMotors(-100,0);
    delay(50);
    }*/
else if(pattern == "00000001")
    {
    setMotors(0,-100);
    delay(50);
    }
else
	setMotors(0,0);

}
