# Ponto Biometrico Digital Com ESP266
Este projeto consiste em um sistema de ponto biométrico digital desenvolvido com ESP8266. O dispositivo é capaz de capturar as impressões digitais dos usuários e registrar as marcações de entrada e saída em um servidor central, permitindo o controle de acesso e a gestão de frequência de funcionários de empresas ou instituições.

O sistema é baseado em uma placa ESP8266 que se comunica com um sensor de impressão digital e um display OLED. Através de uma interface amigável, os usuários podem fazer suas marcações de ponto, que são registradas em um banco de dados centralizado e acessível através de uma API. O dispositivo também possui recursos de segurança, como autenticação de usuários e criptografia de dados.

Este projeto é ideal para empresas e instituições que desejam implementar um sistema de ponto biométrico digital eficiente e seguro, sem depender de equipamentos caros ou complexos. Com a simplicidade e versatilidade da plataforma ESP8266, é possível desenvolver soluções personalizadas e adaptáveis às necessidades específicas de cada usuário.
<hr>

<samp><h2> Instruções de Instalação:  <h2></samp>
<hr>
Para realizar a instalação e a utilização do projeto, você precisará instalar todas as biblitecas e driver necessários para utilizar o esp8266, sensor biométrico e realizar a conexão com a internet
  
Segue abaixo as bibliotecas necessárias para o projeto:
  <ul>
    <li> http://arduino.esp8266.com/stable/package_esp8266com_index.json </li>
    <li> esp8266 by esp8266 community - Essa já vem instalada junto com a IDE do Arduino</li>
    <li> https://www.arduino.cc/en/software - Arduino IDE (nesse projeto estou utilizando a v.2.0.4)</li>
     <li> Instalação do NodeMCU V2 / ESP32 com conversor USB serial CP210x
         <li> <a href="https://s3-sa-east-1.amazonaws.com/robocore-tutoriais/163/CP210x_Windows_Drivers.zip" target="_blank"> Windowns</a> </li>
          <li> <a href="[https://s3-sa-east-1.amazonaws.com/robocore-tutoriais/163/CP210x_Windows_Drivers.zip](https://s3-sa-east-1.amazonaws.com/robocore-tutoriais/163/CP210x_Mac_OSX_VCP_Driver.zip)" target="_blank"> MAC OSX </a> </li>
           <li> <a href="[https://s3-sa-east-1.amazonaws.com/robocore-tutoriais/163/CP210x_Windows_Drivers.zip](https://s3-sa-east-1.amazonaws.com/robocore-tutoriais/163/CP210x_Linux-3-x-x-VCP-Driver-Source.zip)" target="_blank"> Linux </a> </li>
    </li>
  
    <p> Esse passo é muito importante, pois sem ele não haverá comunicação entre a IDE e o módulo NODE MCU
     <li> </li>
     <li> </li>
     <li> </li>
     <li> </li>
    
  </ul>

<samp><article
</article></samp>
