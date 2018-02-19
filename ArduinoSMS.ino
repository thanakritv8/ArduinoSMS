#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
SMSGSM sms;
int numdata;
boolean started=false;
char smsbuffer[160];
char n[20];
char dataChar;
String tel;
String msg;
int SendStatus = 0;

void setup()
{
     Serial.begin(9600);
     Serial.println("GSM Shield testing.");
     if (gsm.begin(2400)) {
          Serial.println("\nstatus=READY");
          started=true;
     } else Serial.println("\nstatus=IDLE");
};

void loop()
{
     while (Serial.available() > 0) {
          dataChar = Serial.read();
          //Serial.print(dataChar);
          if (dataChar == '*'){
              SendStatus++;
          } else if (SendStatus == 0 && dataChar != '#') {
              tel += dataChar;
          } else if (SendStatus >= 1 && dataChar != '#') {
              msg += dataChar;
          } else if (dataChar == '#') {
              SendStatus = -1;
          }
     }
     if(started) {
          if (SendStatus == -1){
              char _tel[11];
              char _msg[200];
              tel.toCharArray(_tel, 11);
              msg.toCharArray(_msg, 200);
              Serial.println(_tel);
              Serial.println(_msg);
              if (sms.SendSMS(_tel, _msg)){
                Serial.println("\nSMS sent OK");
              }
              tel = "";
              msg = "";
              SendStatus = 0;
          }
          
     }
     delay(100);
};
