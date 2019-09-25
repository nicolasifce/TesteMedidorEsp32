#include <WiFi.h>
#include <PubSubClient.h>
#include <ThingSpeak.h>

//Dados da rede local
const char* rede = "ALHN-DDEE";
const char* senha = "6402196136";

//Dados da conta Thingspeak
unsigned long canal = 859902;
const char* apiWrite = "JE1YIDWE4TP4FY3Q";
const char* apiRead = "35FILT56MUCBAKIN";

WiFiClient wifiClient;


double valor = 0.0;
boolean direcao = true;

void setup() 
{
 pinMode(2, OUTPUT);//Habilita o LED onboard como saída.
 Serial.begin(115200);
 //Conectando ao Wifi
 WiFi.begin(rede, senha);

 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Conectando ao Wifi");
 }
 Serial.println("Wifi Conectado");
  
 ThingSpeak.begin(wifiClient);
 
}


void loop() 
{
  Limite();
  //Criando dados a serem enviados 
  float energiagraf = sin(valor);
  float intensidadegraf = cos(valor);
  float calorgraf = tan(valor);
  

//Preparando dados dos canais
//  ThingSpeak.setField(1,energiagraf);
//  ThingSpeak.setField(2,intensidadegraf);
//  ThingSpeak.setField(3,calorgraf);
//Enviando dados tratados
//  ThingSpeak.writeFields(canal,apiWrite);
//Fazendo letura do canal
   int led = ThingSpeak.readFloatField(862705,1);
   if(led == 0){
    digitalWrite(2,LOW);
    }else{
     digitalWrite(2,HIGH);
    }
     
   Serial.println(led);
  delay(20000);
}

void Direcao(boolean d){
  if (d == false){
  valor = valor - 0.1;
  }else{
  valor = valor + 0.1; 
  }
}

void Limite(){
  
  if(valor > 0.90 ){
    direcao = false;
   }else if(valor < -0.90){
    direcao = true;
   }
   Direcao(direcao);
}
