//Essa seção do código realiza a inclusão das bibliotecas no código
#include <Adafruit_Fingerprint.h> //Biblioteca do sensor
#include <WiFiClientSecure.h> //Biblioteca do wifi
#include <ESP8266WiFi.h>  //Biblioteca do servidor
#include <Wire.h>
#include "SSD1306Wire.h"

//Imagens para o OLED
#include "digital.h"
#include "verificado.h"
#include "impressao_digital.h"
#include "digitalizacao.h"
#include "biometria_erro.h"


//
#define width_image 64
#define height_image 64
//Esse objeto é responsável por criar um ip estático, assim ele não fica variando cada vez que conecta no wifi
//Para a utilização dessa sessão em seu código é necessário acessar o cmd e digitar "ipconfig"
//Copiar mascara de sub rede, ipv4 e gateway padrão

//Essa parte do código fica responsável pela configuração do wifi
WiFiServer server(80); // Porta 80


//Configurações para o Wifi
const char* ssid = "Unifil Computacao"; // nome da sua rede WiFi
const char* password = ""; // senha da sua rede WiFi


//Configurações da API do google
const char* host = "script.google.com"; // host da planilha do Google
const char* GAS_ID = "AKfycbzZnwU0cFINui6qhKp7S0Km4HOMw5ZJ73aHNaVUD2d-C2gmGDJtAsg37jbEB0Nu6C8C"; // ID do Google Apps Script


//Objeto responsável por controlar o sensor de digitais
Adafruit_Fingerprint fingerprintSensor = Adafruit_Fingerprint(&mySerial);
SoftwareSerial mySerial(D7, D5); // Configura as portas do sensor biométrico



SSD1306Wire  display(0x3c, D2, D0); // Configura as portas do OLED


//Variáveis globais que serão utilizadas ao longo do programa
int botao = D4; //Define o botão de acionamento como D1
uint8_t id;
int counter = 1;


void setup() //Void Setup
{
  Serial.begin(9600);
  Serial.begin(115200);
  setupFingerprintSensor();   //Inicializa o sensor de digitais
  display.init();
  display.flipScreenVertically();
}

void setupFingerprintSensor() //Inicia o sensor biométrico
{
  //Inicializa o sensor
  fingerprintSensor.begin(57600);

  //Verifica se a senha está correta
  if(!fingerprintSensor.verifyPassword())
  {
    //Se chegou aqui significa que a senha está errada ou o sensor está problemas de conexão
    Serial.println(F("Não foi possível conectar ao sensor. Verifique a senha ou a conexão"));
    while(true) yield();
  }
}
 
void loop()
{
  //Exibe o menu no monitor serial
  // verifica se há dados disponíveis na porta serial
  String c = Serial.readStringUntil('\n'); // lê uma string do monitor serial
  if (c.equals("m")) 
    { // verifica se a string lida é 'm'
       printMenu();
    }

  if (digitalRead(botao) == 1)
    {
    checkFingerprint();
    }

    display.clear();
    telainicial();
    display.display();
}

void update_google_sheet(int _id)
{
    Serial.print("Connecting to ");
    Serial.println(host);

    // Conectar-se à rede WiFi
    Serial.printf("Conectando-se à rede WiFi %s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        drawProgressBarDemo();
        Serial.print(".");
    }
    Serial.println(" conectado com sucesso");

    // Use WiFiClient class to create TCP connections
    WiFiClientSecure client;
    const int httpPort = 443; // 80 é para HTTP / 443 é para HTTPS!

    client.setInsecure(); // essa é a linha mágica que faz tudo funcionar

    if (!client.connect(host, httpPort)) { // funciona!
        Serial.println("Falha na conexão");
        return;
    }

    //----------------------------------------Processamento de dados e envio de dados
    String url = "/macros/s/" + String(GAS_ID) + "/exec?ID=";

    url += String(_id);

    Serial.print("Solicitando URL: ");
    Serial.println(url);

    // Isso enviará a solicitação para o servidor
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
        "Host: " + String(host) + "\r\n" +
        "Connection: close\r\n\r\n");

    WiFi.disconnect();
    drawImageVerificado();
    Serial.println();
    Serial.println("Conexão encerrada");
}//fim planilha
   
//Exibe o menu no monitor serial
void printMenu()
{
  Serial.println();
  Serial.println(F("Digite um dos números do menu abaixo"));
  Serial.println(F("1 - Cadastrar digital"));
  Serial.println(F("2 - Verificar digital"));
  Serial.println(F("3 - Mostrar quantidade de digitais cadastradas"));
  Serial.println(F("4 - Apagar digital em uma posição"));
  Serial.println(F("5 - Apagar banco de digitais"));

   //Faz a leitura do comando digitado
  String command = getCommand();
  
  //Transforma a string em inteiro
  int i = command.toInt();

  //Verifica qual o número digitado e chama a função correspondente
  switch (i)
  {
    case 1:
      storeFingerprint();
      break;
    case 2:
      checkFingerprint();
      break;
    case 3:
      printStoredFingerprintsCount();
      break;
    case 4:
      login();
      break;
    case 5:
      login2();
      break;
    default:
      Serial.println(F("Opção inválida"));
      break;
  }
}

//Espera até que se digite algo no monitor serial e retorna o que foi digitado
String getCommand()
{
  while(!Serial.available()) yield();
  return Serial.readStringUntil('\n');
  WiFi.disconnect();
}
//Cadastro da digital
void storeFingerprint() // Função para armazenar digitais
    {

    for (size_t i = 1; i < 149; i++)
   {
   uint8_t c = fingerprintSensor.loadModel(i);

    if (c != FINGERPRINT_OK) {
    id = i;
    uint8_t c = fingerprintSensor.loadModel(-1);
    break;
   }
  }

  //Lê o que foi digitado no monitor serial
  Serial.println(F("Encoste o dedo no sensor"));

  //Espera até pegar uma imagem válida da digital
  while (fingerprintSensor.getImage() != FINGERPRINT_OK) yield();
  
  //Converte a imagem para o primeiro padrão
  if (fingerprintSensor.image2Tz(1) != FINGERPRINT_OK)
  {
    //Se chegou aqui deu erro, então abortamos os próximos passos
    Serial.println(F("Erro image2Tz 1"));
    return;
  }
  
  Serial.println(F("Tire o dedo do sensor"));

  delay(2000);

  //Espera até tirar o dedo
  while (fingerprintSensor.getImage() != FINGERPRINT_NOFINGER) yield();

  //Antes de guardar precisamos de outra imagem da mesma digital
  Serial.println(F("Encoste o mesmo dedo no sensor"));

  //Espera até pegar uma imagem válida da digital
  while (fingerprintSensor.getImage() != FINGERPRINT_OK) yield();

  //Converte a imagem para o segundo padrão
  if(fingerprintSensor.image2Tz(2) != FINGERPRINT_OK)
  {
    //Se chegou aqui deu erro, então abortamos os próximos passos
    Serial.println(F("Erro image2Tz 2"));
    return;
  }

  //Cria um modelo da digital a partir dos dois padrões
  if(fingerprintSensor.createModel() != FINGERPRINT_OK)
  {
    //Se chegou aqui deu erro, então abortamos os próximos passos
    Serial.println(F("Erro createModel"));
    return;
  }

  //Guarda o modelo da digital no sensor
  if(fingerprintSensor.storeModel(id) != FINGERPRINT_OK)
  {
    //Se chegou aqui deu erro, então abortamos os próximos passos
    Serial.println(F("Erro storeModel"));
    return;
  }

  //Se chegou aqui significa que todos os passos foram bem sucedidos
  Serial.println(F("Sucesso!!!"));  
}

//Verifica se a digital está cadastrada
void checkFingerprint() // Função para checkar digitais
{
  drawImageVerificaDigital ();
  Serial.println(F("Encoste o dedo no sensor"));

  //Espera até pegar uma imagem válida da digital
  while (fingerprintSensor.getImage() != FINGERPRINT_OK) yield();

  //Converte a imagem para o padrão que será utilizado para verificar com o banco de digitais
  if (fingerprintSensor.image2Tz() != FINGERPRINT_OK)
  {
    //Se chegou aqui deu erro, então abortamos os próximos passos
    Serial.println(F("Erro image2Tz"));
    drawImageBiometriaErro();
    return;
  }
  
  //Procura por este padrão no banco de digitais
  if (fingerprintSensor.fingerFastSearch() != FINGERPRINT_OK)
  {
    drawImageBiometriaErro();
    return;

  }

  Serial.print(F("Digital encontrada com confiança de "));
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  //Seleciona a fonte
  display.setFont(ArialMT_Plain_16);
  display.drawString(63, 10, "Digital reconhecida!");
  display.drawString(63, 45, "Sucesso!");
  display.display(); 
  Serial.print(fingerprintSensor.confidence);
  Serial.print(F(" na posição "));
  Serial.println(fingerprintSensor.fingerID);
  update_google_sheet(fingerprintSensor.fingerID);
  
}

void printStoredFingerprintsCount() // Função para ver quantas digitais tem armazenadas
{
  //Manda o sensor colocar em "templateCount" a quantidade de digitais salvas
  fingerprintSensor.getTemplateCount();

  //Exibe a quantidade salva
  Serial.print(F("Digitais cadastradas: "));
  Serial.println(fingerprintSensor.templateCount);
}

void deleteFingerprint() // Função para apagar uma digital
{
  Serial.println(F("Qual a posição para apagar a digital? (1 a 149)"));

  //Lê o que foi digitado no monitor serial
  String strLocation = getCommand();

  //Transforma em inteiro
  int location = strLocation.toInt();

  //Verifica se a posição é válida ou não
  if(location < 1 || location > 149)
  {
    //Se chegou aqui a posição digitada é inválida, então abortamos os próximos passos
    Serial.println(F("Posição inválida"));
    return;
  }

  //Apaga a digital nesta posição
  if(fingerprintSensor.deleteModel(location) != FINGERPRINT_OK)
  {
    Serial.println(F("Erro ao apagar digital"));
  }
  else
  {
    Serial.println(F("Digital apagada com sucesso!!!"));
  }
}

void emptyDatabase() // Função para apagar o banco de dados
{
  Serial.println(F("Tem certeza que deseja apagar o banco de dados isso poderá danos irreversíveis? (s/N)"));

  //Lê o que foi digitado no monitor serial
  String command = getCommand();

  //Coloca tudo em maiúsculo para facilitar a comparação
  command.toUpperCase();

  //Verifica se foi digitado "S" ou "SIM"
  if(command == "S" || command == "SIM")
  {
    Serial.println(F("Apagando banco de digitais..."));

    //Apaga todas as digitais
    if(fingerprintSensor.emptyDatabase() != FINGERPRINT_OK)
    {
      Serial.println(F("Erro ao apagar banco de digitais"));
    }
    else
    {
      Serial.println(F("Banco de digitais apagado com sucesso!!!"));
    }
  }
  else
  {
    Serial.println(F("Cancelado"));
  }
}

void login ()
{ // Cria um painel de login para excluir uma digital
  painelLogin();
  String username = "";
  String password = "";
  Serial.println("Digite o Usário: ");
  username = getCommand();
  if (username == "admin"){
  Serial.println("Digite a senha:");
  password = getCommand();
  }
  else {
  Serial.print("Nenhum usuário encontrado, por favor tente novamente...");
  }
  if (username == "admin" && password == "t11fl"){
  Serial.println("Login Bem-Sucedido");
  deleteFingerprint();
  }
  else{
  Serial.println("Falha ao efetuar login...");
  }
}

void login2 ()
{ // Cria um painel de login para excluir o banco de dados
  painelLogin();
  String username = "";
  String password = "";
  Serial.println("Digite o Usário: ");
  username = getCommand();
  if (username == "admin"){
  Serial.println("Digite a senha:");
  password = getCommand();
  }
  else {
  Serial.print("Nenhum usuário encontrado, por favor tente novamente...");
  }
  if (username == "admin" && password == "t11fl"){
  Serial.println("Login Bem-Sucedido");
  emptyDatabase();
  }
  else{
  Serial.println("Falha ao efetuar login...");
  }
}
 
void painelLogin()
{ // Cria uma interface de login
    Serial.println(".......................................");
    Serial.println("......................................."); 
    Serial.println("=======================================");
    Serial.println("| BEM VINDO AO PORTAL DE LOGIN DO NPI |");
    Serial.println("|=====================================|");
    Serial.println("| USUÁRIO:                            |");
    Serial.println("| SENHA:                              |");
    Serial.println("|=====================================|");
}

void telainicial()
{
  //Apaga o display
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  //Seleciona a fonte
  display.setFont(ArialMT_Plain_16);
  display.drawString(63, 10, "Sistema de ponto");
  display.drawString(63, 26, "Biométrico");
  display.drawString(63, 45, "NPI");
  display.display();
  
  /*
  display.clear();
  drawImageImpressaoDigital();
  display.display();
  
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(63, 10, "Aperte o Botão");
  display.drawString(63, 26, "Ao lado");
  display.drawString(63, 45, "-->");
  display.display();
  */
  
}

void drawImageVerificaDigital() {
  display.clear();
  display.drawXbm(34, 1, width_image, height_image, colocar_dedo);
  display.display();
}

void drawImageVerificado() {
  display.clear();
  display.drawXbm(34, 1, width_image, height_image, logo_verificado);
   display.display();
   delay(3000);
}

void drawImageImpressaoDigital() {
  display.clear();
  display.drawXbm(34, 1, width_image, height_image, logo_impressao_digital );
   display.display();
}

void drawImageDigitalizacao() {
  display.clear();
  display.drawXbm(34, 1, width_image, height_image, logo_digitalizacao);
   display.display();
}

void drawImageBiometriaErro() {
  display.clear();
  display.drawXbm(34, 1, width_image, height_image, logo_biometria_erro);
   display.display();
}

void drawProgressBarDemo() {
  
  display.clear();
  int progress = (counter / 5) % 100; 
  // draw the progress bar
  display.drawProgressBar(0, 32, 120, 10, progress);

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%");
  display.display();
  counter++;
}