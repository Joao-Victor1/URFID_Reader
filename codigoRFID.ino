#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

int buzzerPin = 7;


void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
  Serial.println("Aproxime um cartão RFID...");
}
int valor = 100;


int desconta(){
    valor--;
  Serial.println(valor);
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.println("Cartão detectado!");

    byte cardID[4] = {mfrc522.uid.uidByte[0], mfrc522.uid.uidByte[1], mfrc522.uid.uidByte[2], mfrc522.uid.uidByte[3]};



    if (isCardRegistered(cardID)) {
      

      // Cartão cadastrado, emita um sinal sonoro positivo
      emiteSomPositivo();
      Serial.println("Cartão cadastrado!");
    } else {
      // Cartão não cadastrado, emita um sinal sonoro negativo
      emiteSomNegativo();
      Serial.println("Cartão não cadastrado!");
    }
    delay(1000);
  }
}

bool isCardRegistered(byte cardID[4]) {
  // Substitua com os IDs dos cartões RFID cadastrados
  byte registeredCard1[4] = {0x60, 0x96, 0x6D, 0x2C};
  byte registeredCard2[4] = {0x55, 0x66, 0x77, 0x88};
  byte registeredCard3[4] = {0xB1, 0x68, 0x50, 0x1E};

  if (memcmp(cardID, registeredCard1, 4) == 0 || memcmp(cardID, registeredCard2, 4) == 0 || memcmp(cardID, registeredCard3, 4) == 0) {
    for (int i = 0; i < 4; i++) {
      Serial.print(cardID[i], HEX);
      Serial.println(' '); 
      
    }
    Serial.print("Valor: ");
    desconta();

    return true;
  }


  for (int i = 0; i < 4; i++) {
      Serial.println(cardID[i], HEX);
      Serial.println(' '); 
    }
  return false;

  
}



void emiteSomPositivo() {
  tone(buzzerPin, 1500, 500);
}

void emiteSomNegativo() {
  tone(buzzerPin, 300, 500); // Emite o som negativo
}
