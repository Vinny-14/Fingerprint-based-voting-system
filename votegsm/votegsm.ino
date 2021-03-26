#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
//int val;


#include <LiquidCrystal_I2C.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)

SoftwareSerial mySerial(2, 3);



#else
#define mySerial Serial1

#endif


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define S1 7
#define S2 6
#define S3 5
#define sim800l_RX 11 //RX1 on Arduino Mega
#define sim800l_TX 10 //TX1 on Arduino Mega
#define sim800l_RST 2
#define sim800l_

//using namespace std;
int vote1 = 0;
int vote2 = 0;
int vote3 = 0;
int vote = vote1 + vote2 + vote3;
int b = 0;
int voters[] = {1, 2, 3, 4, 5, 6};
int n = sizeof(voters) / sizeof(voters[0]);
char teamNumber = 1000;
int voteNumber = vote;
int refID = 001;


String names[] = {"Martha", "Wanjiru", "Jack", "Max", "Dr. Akuon", "Prof Ouma"};
String numbers[] = {"+254728603208", "+254703535853", "+254712897106", "+254102927170", "+254713136333",  "+254794016563"};
String phone = numbers[b - 1];
int count = 0;

SoftwareSerial sim(10, 11);
int _timeout;
String _buffer;
uint8_t id;

void setup()
{
  //push buttons
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);

  //active low
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  //system initializing
  lcd.init();
  lcd.backlight();

  //GSM
  _buffer.reserve(50);
  sim.begin(9600);
  delay(1000);

  //Serial monitor
  Serial.begin(9600);
  delay(100);
  Serial.println("\n\nWelcome to my decentralized biometric voting system");
  lcd.setCursor(3, 0);
  lcd.print("Welcome!");
  delay(2000);
  lcd.clear();
  lcd.print("   Biometric ");
  lcd.setCursor(0, 1);
  lcd.print(" Voting Machine ");
  delay(3200);

}
String _readSerial()
{
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}
void SendMessage()
{
  Serial.println("Sending SMS...");               //Show this message on serial monitor
  sim.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  if (b == 1 )
  {
    sim.print("AT+CMGS=\"+254728603208\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
  }
  else if (b == 2)
  {
    sim.print("AT+CMGS=\"+254703535853\"\r");
  }
  else if (b == 3)
  {
    sim.print("AT+CMGS=\"+254712897106\"\r");
  }
  else if (b == 4)
  {
    sim.print("AT+CMGS=\"+254102927170\"\r");
  }
  else if (b == 5)
  {
    sim.print("AT+CMGS=\"+254713136333\"\r");
  }

  int voteNumber = vote;
  
  String z = {". Thank you."};
  String r = {"Your voting Ref ID. is KEV2021N00"};

  if (voteNumber == 1)
  {
    String x = {"Congratulations on being our first voter. "};
    delay(500);
    sim.print(x + r + refID + z);       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
    refID++;
    delay(500);
    sim.print((char)26);// (required according to the datasheet)
    delay(500);
    sim.println();
    Serial.println("Text Sent");
    delay(500);
  }
    if (voteNumber == 2)
  {
    String x = {"Thanks for being our 2nd voter. "};
    delay(500);
    sim.print(x + r + refID + z);       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
    refID++;
    delay(500);
    sim.print((char)26);// (required according to the datasheet)
    delay(500);
    sim.println();
    Serial.println("Text Sent");
    delay(500);
  }
    if (voteNumber == 3)
  {
    String x = {"Thanks for being our 3rd voter. "};
    delay(500);
    sim.print(x + r + refID + z);       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
    refID++;
    delay(500);
    sim.print((char)26);// (required according to the datasheet)
    delay(500);
    sim.println();
    Serial.println("Text Sent");
    delay(500);
  }
  
  else if (voteNumber == 6)
  {
    String x = {"Thank you for being our last voter. "};
    delay(500);
    sim.print(x + r + refID + z);       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
    refID++;
    delay(500);
    sim.print((char)26);// (required according to the datasheet)
    delay(500);
    sim.println();
    Serial.println("Text Sent");
    delay(500);
  }
  
  else
  {
  delay(500);
  String x = {"Thanks for being our "};
  String r = {"th voter. Your voting Ref ID. is KEV2021N00"};
  refID++;
  sim.print(x + voteNumber + r+ refID + z);       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  sim.print((char)26);// (required according to the datasheet)
  delay(500);
  sim.println();
  Serial.println("Text Sent");
  delay(500);
  }
}


void loop()
{


  lcd.clear();
  lcd.setCursor(2 , 0);
  lcd.print("Place finger");
  lcd.setCursor (0, 1);
  lcd.print("for verification");
  delay(1500);
  //lcd.clear ();
  finger.begin(57600);
  delay(5);


  Serial.println(F("Reading sensor parameters")); finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);

  finger.getTemplateCount();

  if (finger.templateCount == 0)
  {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else
  {
    Serial.println("Waiting for valid finger...");
    Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }


  uint8_t getFingerprintID();
  uint8_t p = finger.getImage();


  switch (p)
  {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();

  switch (p)
  {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();


  if (p == FINGERPRINT_OK)
  {
    b = finger.fingerID;

    if (voters[b - 1] == b)
    {
      lcd.clear();
      Serial.println("Found a print match!");
      lcd.setCursor(0, 0);
      lcd.print("Welcome, ");
      lcd.print(names[b - 1]);
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Proceed to vote");
      delay(2000);
      lcd.clear();

      lcd.print("Waiting...");
      Serial.println(phone);
      int i = 0;




      for (i = 0; i < 1;)

      {

        bool  voted = false;

        if (digitalRead(S1) == 0)
        {
          vote1++;
          vote++;
          voteNumber++;
          teamNumber = 1033;
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("You have voted");
          lcd.setCursor(2, 1);
          lcd.print("Successfully");
          delay(1000);
          SendMessage();
          lcd.clear();
          lcd.setCursor(2, 0);
          lcd.print("Thank you");
          lcd.setCursor(3, 1);
          lcd.print("Goodbye!");
          delay(2000);
          lcd.clear();
          voters[b - 1] = 0;
          lcd.setCursor(2, 0);
          lcd.print("A");
          lcd.setCursor(2, 1);
          lcd.print(vote1);
          lcd.setCursor(6, 0);
          lcd.print("B");
          lcd.setCursor(6, 1);
          lcd.print(vote2);
          lcd.setCursor(10, 0);
          lcd.print("C");
          lcd.setCursor(10, 1);
          lcd.print(vote3);
          delay(3000);
          break;
        }

        else if (digitalRead(S2) == 0)
        {
          vote2++;
          vote++;
          voteNumber++;
          teamNumber = 1045;
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("You have voted");
          lcd.setCursor(2, 1);
          lcd.print("Successfully");
          delay(2000);
          SendMessage();
          lcd.clear();
          lcd.setCursor(2, 0);
          lcd.print("Thank you");
          lcd.setCursor(3, 1);
          lcd.print("Goodbye!");
          delay(2000);
          lcd.clear();
          voters[b - 1] = 0;
          lcd.setCursor(2, 0);
          lcd.print("A");
          lcd.setCursor(2, 1);
          lcd.print(vote1);
          lcd.setCursor(6, 0);
          lcd.print("B");
          lcd.setCursor(6, 1);
          lcd.print(vote2);
          lcd.setCursor(10, 0);
          lcd.print("C");
          lcd.setCursor(10, 1);
          lcd.print(vote3);
          delay(3000);
          break;
        }

        else if (digitalRead(S3) == 0)
        {
          vote3++;
          vote++;
          voteNumber++;
          teamNumber = 1060;
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("You have voted");
          lcd.setCursor(2, 1);
          lcd.print("Successfully");
          delay(2000);
          SendMessage();
          lcd.clear();
          lcd.setCursor(2, 0);
          lcd.print("Thank you");
          lcd.setCursor(3, 1);
          lcd.print("Goodbye!");
          delay(2000);
          lcd.clear();
          voters[b - 1] = 0;
          lcd.setCursor(2, 0);
          lcd.print("A");
          lcd.setCursor(2, 1);
          lcd.print(vote1);
          lcd.setCursor(6, 0);
          lcd.print("B");
          lcd.setCursor(6, 1);
          lcd.print(vote2);
          lcd.setCursor(10, 0);
          lcd.print("C");
          lcd.setCursor(10, 1);
          lcd.print(vote3);
          delay(3000);
          break;
        }

      }
      lcd.clear();
      lcd.print(vote1 & vote2 & vote3);
      return b;
    }


    else
    {
      lcd.clear();
      lcd.print(" Only One Entry");
      lcd.setCursor(3, 1);
      lcd.print(" Allowed");
      delay(2000);
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Goodbye!");
      delay(1000);
      lcd.clear();
    }
    return b;
  }




  else if (p == FINGERPRINT_NOTFOUND)
  {
    lcd.clear();
    Serial.println("Did not find a match");
    lcd.setCursor(0, 0);
    lcd.print("Match failed");
    //delay (2000);
    lcd.setCursor(0, 1);
    lcd.print("User denied!");
    delay (2000);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Please Retry");
    delay (1000);
    return p;
  }

  lcd.print(vote1 && vote2 && vote3);
  delay(3000);
}
