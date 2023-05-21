#define Aio 2
#define Bio 3

int dir;
int num;
int armed = 0;

void Aio_inter()
{
  int value = digitalRead(Aio) << 1 | digitalRead(Bio);
  //Serial.println(value);

  switch (value)
  {
    case 0:
        if (armed)
        {
            //Serial.print("end:");
            //Serial.println(dir);
            armed = 0;
            if (dir)
              num--;
             else
              num++;
  Serial.print("num: ");
  Serial.println(num);
            dir = 0;
        }
        break;
    case 1:
    case 3:
        if (armed)
          dir = 2 - value;
        break;
    case 2:
        armed = 1;
        break;
  }

  return;
}

void setup(){
  Serial.begin(115200);
  pinMode(Aio, INPUT);
  pinMode(Bio, INPUT);
 
  attachInterrupt(digitalPinToInterrupt(Aio), Aio_inter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Bio), Aio_inter, CHANGE);

  Serial.println("setup");
}

void loop()
{
  //Serial.print("num: ");
  //Serial.println(num);
  delay(100); 
}