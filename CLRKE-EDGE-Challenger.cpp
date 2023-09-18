// SPRINT-3-EDGE
/*
 Simulação do Projeto utilizando:
  1- potenciometro para a simulação de uma usina hitrelétrica
  1- Sensor de temperatura para a simulação de uma usina de Biomassa
  1- fotorresistor para a simulção de uma placa fotovoltaica
*/
//Inclusão de Bibliotecas'
#include <WiFi.h>
#include <HTTPClient.h>
// definir as portas do arduino/Esp32 //
#define ldr A0
int umidade = A2;
int umidadevalor = 0;
int vldr = 0;
int PinoDoSensor = 1;
int vtmp = 0;


char ssid[] = "CLARKE";                                        // SSID da rede Wi-Fi
char password[] = "clarke";                                    // Senha da rede Wi-Fi


char serverAddress[] = "https://api.tago.io/data";             // Endereço do servidor para enviar os dados
char contentHeader[] = "application/json";
char tokenHeader[]   = "a54c68df-c783-4302-a853-1bcaa22176c7"; // TagoIO Token



void setup() {
  pinMode(ldr, INPUT);
  Serial.begin(9600);
  init_WiFi();
}

void init_WiFi() {
  Serial.print("Conectando no Wi-Fi ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado ao Wi-Fi");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  delay(5000);
  umidadevalor = analogRead(umidade);
  vldr = analogRead(ldr);
  vtmp = analogRead(PinoDoSensor); // Fazendo a leitura do pino A0, conectado ao sensor

  float tensao = vtmp * 5.0;              // Convertendo a leitura em tensão.
  tensao /= 1024.0;                       // Convertendo a tensão em dados (1024 faixas de dados)
  float celsius = (tensao - 0.5) * 100;   // Converção de 10mV por ºC , com desvio de
  Serial.println("Temperaturas Medidas"); // Título
  Serial.print(celsius);
  Serial.println(" C");
  Serial.println("");
  delay(1000);
  Serial.println("luminosidadee"); // Título
  Serial.print(vldr);
  Serial.println(" - Luminosidade");
  Serial.println("");
  delay(1000);
  Serial.println("Umidade medida"); // Título
  Serial.print(map(umidadevalor, 0, 1023, 0, 100));
  Serial.println(" de umidade");
  Serial.println("");
  delay(1000);

  // extremo alto de todas
  while ((map(umidadevalor, 0, 1023, 0, 100) >= 66, 6) && (vldr >= 207) && (celsius >= 124, 80))
  {
    Serial.println("todas muito");
    Serial.println("Elevadas");
    // releitura dos sensores
    umidadevalor = analogRead(umidade);
    vldr = analogRead(ldr);
    vtmp = analogRead(PinoDoSensor); // Fazendo a leitura do pino A0, conectado ao sensor
    tensao = vtmp * 5.0;             // Convertendo a leitura em tensão.
    tensao /= 1024.0;                // Convertendo a tensão em dados (1024 faixas de dados)
    celsius = (tensao - 0.5) * 100;  // Converção de 10mV por ºC , com desvio de
  }
  // extremo Baixo de todas
  while ((map(umidadevalor, 0, 1023, 0, 100) <= 33, 3) && (vldr <= 103) && (celsius <= 15))
  {
    Serial.println("desempenho");
    Serial.println("Baixo");

    // releitura dos sensores
    umidadevalor = analogRead(umidade);
    vldr = analogRead(ldr);
    vtmp = analogRead(PinoDoSensor); // Fazendo a leitura do pino A0, conectado ao sensor
    tensao = vtmp * 5.0;             // Convertendo a leitura em tensão.
    tensao /= 1024.0;                // Convertendo a tensão em dados (1024 faixas de dados)
    celsius = (tensao - 0.5) * 100;  // Converção de 10mV por ºC , com desvio de
  }

  // para o VLDR ligar a 33% e os outros a menos de 33%
  if (vldr >= 103 && (celsius <= 15) && (map(umidadevalor, 0, 1023, 0, 100) <= 33, 3))
  {
    Serial.println("maior producao");
    Serial.println("Energia Solar");
    delay(5000);
  }

  if (((vldr <= 206) && (vldr >= 104)) && (celsius <= 30) && (map(umidadevalor, 0, 1023, 0, 100) <= 66, 6))
  {
    Serial.println("maior producao");
    Serial.println("Energia Solar");
    delay(5000);
  }

  if ((vldr >= 207) && (celsius <= 70) && (map(umidadevalor, 0, 1023, 0, 100) <= 100))
  {
    Serial.println("maior producao");
    Serial.println("Energia Solar");
    delay(5000);
  }

  // finalização do VLDR
  umidadevalor = analogRead(umidade);
  vldr = analogRead(ldr);
  vtmp = analogRead(PinoDoSensor); // Fazendo a leitura do pino A0, conectado ao sensor
  tensao = vtmp * 5.0;             // Convertendo a leitura em tensão.
  tensao /= 1024.0;                // Convertendo a tensão em dados (1024 faixas de dados)
  celsius = (tensao - 0.5) * 100;  // Converção de 10mV por ºC , com desvio de

  // Começo do CELSIUS

  if (((celsius >= 15)) && (vldr <= 103) && (map(umidadevalor, 0, 1023, 0, 100) <= 33, 3))
  {
    Serial.println("maior producao");
    Serial.println("Energia Biomassa");
    delay(5000);
  }

  if (((celsius >= 16) && (celsius <= 70)) && (vldr <= 206) && (map(umidadevalor, 0, 1023, 0, 100) <= 66, 6))
  {

    Serial.println("maior producao");

    Serial.println("Energia Biomassa");
    delay(5000);
  }

  if ((celsius >= 71) && (vldr <= 207) && (map(umidadevalor, 0, 1023, 0, 100) <= 100))
  {

    Serial.println("maior producao");

    Serial.println("Energia Biomassa");
    delay(5000);
  }

  // finalização do CELSIUS
  umidadevalor = analogRead(umidade);
  vldr = analogRead(ldr);
  vtmp = analogRead(PinoDoSensor); // Fazendo a leitura do pino A0, conectado ao sensor
  tensao = vtmp * 5.0;             // Convertendo a leitura em tensão.
  tensao /= 1024.0;                // Convertendo a tensão em dados (1024 faixas de dados)
  celsius = (tensao - 0.5) * 100;  // Converção de 10mV por ºC , com desvio de

  // Começo de UMIDADE
  if ((map(umidadevalor, 0, 1023, 0, 100) >= 33, 3) && (celsius <= 15) && (vldr <= 103))
  {

    Serial.println("maior producao");

    Serial.println("hidreletrica");
    delay(5000);
  }

  if (((map(umidadevalor, 0, 1023, 0, 100) >= 33, 3) && (map(umidadevalor, 0, 1023, 0, 100) <= 66, 6)) && (vldr <= 206) && (celsius <= 70))
  {

    Serial.println("maior producao");

    Serial.println("hidreletrica");
    delay(5000);
  }

  if ((map(umidadevalor, 0, 1023, 0, 100) >= 66, 6) && (vldr <= 207) && (celsius <= 124, 80))
  {

    Serial.println("maior producao");
    Serial.println("hidreletrica");
    delay(5000);
  }
    // Criando o objeto JSON com os valores dos sensores
  String json = "{";
  json += "\"umidadevalor\":" + String(umidadevalor) + ",";
  json += "\"vldr\":" + String(vldr) + ",";
  json += "\"celsius\":" + String(getTemperature(vtmp)); // Você precisa implementar a função getTemperature para converter o valor em Celsius
  json += "}";

  // Enviando o objeto JSON para o servidor
  sendToServer(json);

}

void sendToServer(String data) {
  HTTPClient client;
  client.begin(serverAddress);
  client.addHeader("Content-Type", "application/json");

  // Envie os dados para o servidor
  int statusCode = client.POST(data);

  if (statusCode == 200) {
    Serial.println("Dados enviados com sucesso!");
  } else {
    Serial.print("Falha no envio. Código de status: ");
    Serial.println(statusCode);
  }

  client.end();
}

