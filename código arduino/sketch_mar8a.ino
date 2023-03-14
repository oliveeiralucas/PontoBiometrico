//Essa seção do código realiza a inclusão das bibliotecas no código
#include <Adafruit_Fingerprint.h> //Biblioteca do sensor
#include <WiFiClientSecure.h> //Biblioteca do wifi
#include <ESP8266WiFi.h>  //Biblioteca do servidor


//Esse objeto é responsável por criar um ip estático, assim ele não fica variando cada vez que conecta no wifi
//Para a utilização dessa sessão em seu código é necessário acessar o cmd e digitar "ipconfig"
//Copiar mascara de sub rede, ipv4 e gateway padrão

IPAddress ip(10, 21, 1, 255);   //mudar o ultimo digito (ipv4)
IPAddress ip1(10, 21, 0, 254);  //mascara de subrede
IPAddress ip2(255, 255, 0, 0);  //gateway padrão


//Essa parte do código fica responsável pela configuração do wifi
WiFiServer server(80); // Porta 80


const char* ssid = "Unifil Computacao"; // nome da sua rede WiFi
const char* password = ""; // senha da sua rede WiFi
const char* host = "script.google.com"; // host da planilha do Google
const char* GAS_ID = "AKfycbzZnwU0cFINui6qhKp7S0Km4HOMw5ZJ73aHNaVUD2d-C2gmGDJtAsg37jbEB0Nu6C8C"; // ID do Google Apps Script


//Objeto responsável por controlar o sensor de digitais
SoftwareSerial mySerial(D7, D8);
Adafruit_Fingerprint fingerprintSensor = Adafruit_Fingerprint(&mySerial);

int desligarWifi = -1;
int botao = D1;

void setup() //Void Setup
{
  Serial.begin(9600);
  Serial.begin(115200);
  setupFingerprintSensor();   //Inicializa o sensor de digitais
  conexaoWifi();

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
}

void update_google_sheet(int _id) //Comunica com a planilha google
{
    conexaoWifi();
    // Use WiFiClient class to create TCP connections
    WiFiClientSecure client;
    client.setInsecure(); // essa é a linha mágica que faz tudo funcionar

    //----------------------------------------Processamento de dados e envio de dados
    String url = "/macros/s/" + String(GAS_ID) + "/exec?ID=";

    url += String(_id);

    Serial.print("Solicitando URL: ");
    Serial.println(url);

    // Isso enviará a solicitação para o servidor
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
        "Host: " + String(host) + "\r\n" +
        "Connection: close\r\n\r\n");

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
  desligarWifi = 0;
}

//Espera até que se digite algo no monitor serial e retorna o que foi digitado
String getCommand()
{
  while(!Serial.available()) yield();
  return Serial.readStringUntil('\n');
  desligarWifi = 1;
}

//Cadastro da digital
void storeFingerprint() // Função para armazenar digitais
{
  Serial.println(F("Qual a posição para guardar a digital? (1 a 149)"));

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
  if(fingerprintSensor.storeModel(location) != FINGERPRINT_OK)
  {
    //Se chegou aqui deu erro, então abortamos os próximos passos
    Serial.println(F("Erro storeModel"));
    return;
  }

  //Se chegou aqui significa que todos os passos foram bem sucedidos
  Serial.println(F("Sucesso!!!"));
  desligarWifi = 0;
}

//Verifica se a digital está cadastrada
void checkFingerprint() // Função para checkar digitais
{
  Serial.println(F("Encoste o dedo no sensor"));

  //Espera até pegar uma imagem válida da digital
  while (fingerprintSensor.getImage() != FINGERPRINT_OK) yield();

  //Converte a imagem para o padrão que será utilizado para verificar com o banco de digitais
  if (fingerprintSensor.image2Tz() != FINGERPRINT_OK)
  {
    //Se chegou aqui deu erro, então abortamos os próximos passos
    Serial.println(F("Erro image2Tz"));
    return;
  }
  
  //Procura por este padrão no banco de digitais
  if (fingerprintSensor.fingerFastSearch() != FINGERPRINT_OK)
  {
    //Se chegou aqui significa que a digital não foi encontrada
    Serial.println(F("Digital não encontrada"));
    return;

  }

  Serial.print(F("Digital encontrada com confiança de "));
  Serial.print(fingerprintSensor.confidence);
  Serial.print(F(" na posição "));
  Serial.println(fingerprintSensor.fingerID);
  desligarWifi = 1;
  conexaoWifi();
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
  desligarWifi = 0;

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
  desligarWifi = 0;

}

void conexaoWifi() // Realiza a conexão com a internet
{
  if (desligarWifi == 1)
  {
    Serial.println();
    Serial.println();
    Serial.print("Connecting to "); // Mensagem apresentada no monitor série  
    Serial.println(ssid); // Apresenta o nome da rede no monitor série
    WiFi.begin(ssid, password); // Inicia a ligação a rede

  while (WiFi.status() != WL_CONNECTED)
   {
    delay(500);
    Serial.print("."); // Enquanto a ligação não for efectuada com sucesso é apresentado no monitor série uma sucessão de “.”
    }
    Serial.println("");
    Serial.println("WiFi connected"); // Se a ligação é efectuada com sucesso apresenta esta mensagem no monitor série
    // Servidor
    server.begin(); // Comunicação com o servidor
    Serial.println("Servidor iniciado"); //é apresentado no monitor série que o  servidor foi iniciado
    // Impressão do endereço IP
    Serial.print("Use o seguinte URL para a comunicação: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP()); //Abrindo o Brower com este IP acedemos á pagina HTML de controlo dos LED´s, sendo que este IP só está disponível na rede à qual o ESP8266 se encontra ligado
    Serial.println("/");
    
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
  desligarWifi = 0;
}

void login2 ()
{ // Cria um painel de login para excluir um banco
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
  desligarWifi = 0;

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
