
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN    21
#define RST_PIN   22
 
#define SIZE_BUFFER     18
#define MAX_SIZE_BLOCK  16
 
#define LED_BUILTIN 2 //LED EMBEDDED
 
MFRC522 mfrc522(SS_PIN, RST_PIN);
 




#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLECharacteristic *pCharacteristic;

bool deviceConnected = false;
// const int LED = 2; // Could be different depending on the dev board. I used the DOIT ESP32 dev board.



int tagid;

// Veja o link seguinte se quiser gerar seus próprios UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define DHTDATA_CHAR_UUID "6E400003-B5A3-F393-E0A9-E50E24DCCA9E" 


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      Serial.println(rxValue[0]);

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");

        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }
        Serial.println();
        Serial.println("*********");
      }

      
    }
};





void setup()
{
  // Inicia a serial
  Serial.begin(9600);
  // Inicia  SPI bus 
  SPI.begin();
  // Inicia MFRC522    
  mfrc522.PCD_Init();
  Serial.println("Aproxime o seu cartao/TAG do leitor");
  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);





  // Create the BLE Device
  BLEDevice::init("ESP32 RFID"); // Give it a name

  // Configura o dispositivo como Servidor BLE
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Cria o servico UART
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Cria uma Característica BLE para envio dos dados
  pCharacteristic = pService->createCharacteristic(
                      DHTDATA_CHAR_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
                      
  pCharacteristic->addDescriptor(new BLE2902());

  // cria uma característica BLE para recebimento dos dados
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  // Inicia o serviço
  pService->start();

  // Inicia a descoberta do ESP32
  pServer->getAdvertising()->start();
  Serial.println("Esperando um cliente se conectar...");
}



 
void loop()
{ 

   
          // Busca novos cartões 
          if ( ! mfrc522.PICC_IsNewCardPresent())
          {
            return;
          }
          // Seleciona um catão a ser lido
          if ( ! mfrc522.PICC_ReadCardSerial())
          {
            return;
          }
          //Mostra ID na serial
          Serial.print("ID da tag:");
          String conteudo = "";
          byte letra;
          for (byte i = 0; i < mfrc522.uid.size; i++)
          {
            Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
            Serial.print(mfrc522.uid.uidByte[i], HEX);
            conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
            conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
          }
          
          Serial.println();

          conteudo.toUpperCase();

          digitalWrite(LED_BUILTIN, HIGH);
          delay(2000);
          digitalWrite(LED_BUILTIN, LOW);
          delay(2000);




           if (deviceConnected) {

              char rfidDataString[16];
              sprintf(rfidDataString, "%d", conteudo);
              pCharacteristic->setValue(rfidDataString);
              pCharacteristic->notify(); // Envia o valor para o aplicativo!
              Serial.print("*** Enviado BLE: ");
              Serial.print(conteudo);
              Serial.println(" ***");

              
           }
        
}
