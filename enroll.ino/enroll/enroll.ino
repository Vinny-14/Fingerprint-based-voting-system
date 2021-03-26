#include <Adafruit_Fingerprint.h>

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
#define S4 4

int b = 0;
int voters[]= {};
int n = sizeof(voters)/sizeof(voters[0]); 
String names[] = {};
int count = 1;
String phone;


uint8_t id;

void setup()
{
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(S4,INPUT);
  
  Serial.begin(9600);
  while (!Serial); 
  delay(100);
  Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

  finger.begin(57600);
  lcd.init();
  lcd.backlight();
  delay(100);
  Serial.println("\n\nWelcome to my decentralized biometric voting system");
  lcd.setCursor(3,0);         
  lcd.print("Welcome!");       
  delay(2000);
  lcd.clear();
  lcd.print("  Please Enroll");
  lcd.setCursor(0,1);
  lcd.print("  Fingerprint ");
  delay(2000);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);
}

uint8_t readnumber(void)
{
  uint8_t num = 0;

  while (num == 0) 
  {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

  //byte b;
  long j = 0;
  void getPhone()
  {
    while (Serial.available() == 0)
    {
      j = Serial.parseInt();

      Serial.print("Phone number is ");
      Serial.println(j);
      phone = j;
      return phone;
    }
  }

void loop()                     // run over and over again
{
  Serial.println("Ready to enroll a fingerprint!");
  Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");

  lcd.clear();
  lcd.print("Enter Finger ID");
  


  id = readnumber();
  if (id == 0) 
  {// ID #0 not allowed, try again!
     return;
  }

  Serial.println(char(26));
  Serial.print("Enrolling ID #");
  Serial.println(id); 
  lcd.clear();
  lcd.print(id);
  delay(1000);

  lcd.clear();
  lcd.print("Enter Phone No");
  delay(1000);
  Serial.println("Please type the Phone Number for the user");
  String number[10];

  void getPhone();
  Serial.print("Enrolling Phone...");
  Serial.println(phone); 
  lcd.clear();
  lcd.print(phone);
  delay(1000);
  
  lcd.clear();
  lcd.print("  Place Finger");
  lcd.setCursor( 0, 1);
  lcd.print("   To enroll");


  

  while (!  getFingerprintEnroll() );
}

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      lcd.clear();
      lcd.print("Image Taken");
      delay(1000);
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
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

  Serial.println("Remove finger");
  lcd.clear();
  lcd.print("Remove Finger");
  delay(2000);
  
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  lcd.clear();
  lcd.print("   Place Same ");
  lcd.setCursor( 0, 1);
  lcd.print("  Finger Again");
  
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
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
  Serial.print("Creating model for #");  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    lcd.clear();
    lcd.print("  Fingers Dont ");
    lcd.setCursor(0, 1);
    lcd.print("     Match");
    delay(1000);
    lcd.clear();
    lcd.print(" Please Retry");
    delay(1000);
    
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
    lcd.clear();
    lcd.print("Stored!");
    delay(1000);
    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  return true;
}
