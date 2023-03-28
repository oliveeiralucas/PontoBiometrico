# Ponto Biometrico Digital Com ESP266


<p align="center"><img src="https://github.com/oliveeiralucas/PontoBiometrico/blob/main/favicon.png" weight="300px" height="300px" display="block" margin= "auto"></p>

> Este projeto consiste em um sistema de ponto biométrico digital desenvolvido com ESP8266. O dispositivo é capaz de capturar as impressões digitais dos usuários e registrar as marcações de entrada e saída em um servidor central, permitindo o controle de acesso e a gestão de frequência de funcionários de empresas ou instituições.

## ⚙️ Ajustes e melhorias

O projeto ainda está em desenvolvimento e as próximas atualizações serão voltadas nas seguintes tarefas:

- [x] Finalização da prototipação
- [x] Finalização da API
- [x] Finalização do servidor
- [ ] Finalizar Front-End
- [ ] Implementação de visor OLED


## 🔎 Como o Projeto Funciona 
> O sistema é baseado em uma placa ESP8266 que se comunica com um sensor de impressão digital e um display OLED. Através de uma interface amigável, os usuários podem fazer suas marcações de ponto, que são registradas em um banco de dados centralizado e acessível através de uma API. O dispositivo também possui recursos de segurança, como autenticação de usuários e criptografia de dados.


## 💻 Pré-requisitos

Antes de começar, verifique se você atendeu aos seguintes requisitos:

* Instalou a biblioteca `<http://arduino.esp8266.com/stable/package_esp8266com_index.json>`
* Instalou a IDE do Arduino `<https://www.arduino.cc/en/software>`
* Instalou a Biblioteca do Arduino `<esp8266 by esp8266 community>`
* Instalação do conversor USB Serial `<NodeMCU V2 / ESP32 com conversor USB serial CP210x>`
* Instalação do conversor USB Serial `<NodeMCU com conversor USB serial CH340G (V3)>`
* Instalação das Bibliotecas `<ESP8266WiFi.h/Adafruit_Fingerprint.h/WiFiClientSecure.h>`


## ☕ Usando <Ponto_Biometrico_Digital>

Para usar <Ponto_Biometrico_Digital>, siga estas etapas:

```
<Baixe os itens citados anteriormente, faça as conexões necessárias>
```
> Baixe os itens citados anteriormente, faça as conexões necessárias entre esp8266 e o Sensor, altere o código com seu wifi, senha e api do google, após rode o código que ele deverá funcionar.

## 📫 Contribuindo para <Ponto_Biometrico_Digital>

Para contribuir com <Ponto_Biometrico-Digital>, siga estas etapas:

1. Bifurque este repositório.
2. Crie um branch: `git checkout -b <nome_branch>`.
3. Faça suas alterações e confirme-as: `git commit -m '<mensagem_commit>'`
4. Envie para o branch original: `git push origin <nome_do_projeto> / <local>`
5. Crie a solicitação de pull.

> Além disso, você poderá dar sugestões de melhoria no código e na idéia geral do projeto

## Tecnologias usadas e Linguagens
* C++
* HTML5
* CSS 3
* FONTAWESOME 5
* API GoogleSheet


## 🤝 Colaboradores

Agradecemos às seguintes pessoas que contribuíram para este projeto:

<table>
  <tr>
    <td align="center">
      <a href="#">
        <img src="https://avatars.githubusercontent.com/u/124714081?v=4" width="100px;" alt="Foto do Lucas"/><br>
        <sub>
          <b>Lucas Waidman de Oliveira </b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="#">
        <img src="https://media.licdn.com/dms/image/D4D03AQErt-4KkQTIAQ/profile-displayphoto-shrink_800_800/0/1677337899985?e=2147483647&v=beta&t=a2HP0rKSQy1L6XxQDuIKGiDVUQJ5l1lXWHlB2bhxPa8" width="100px;" alt="Foto do Dirceu"/><br>
        <sub>
          <b>Dirceu Aparecido da Silva Junior </b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="#">
        <img src="https://avatars.githubusercontent.com/u/54957276?v=4" width="100px;" alt="Foto do jaoo"/><br>
        <sub>
          <b>João Vitor da Costa Andrade</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="#">
        <img src="https://instagram.fldb3-1.fna.fbcdn.net/v/t51.2885-19/306032424_186369877177276_4312125635918152468_n.jpg?stp=dst-jpg_s150x150&_nc_ht=instagram.fldb3-1.fna.fbcdn.net&_nc_cat=104&_nc_ohc=LpaeTo1XVgwAX9ao4JB&edm=AOQ1c0wBAAAA&ccb=7-5&oh=00_AfDdPfXH2fxCz1mnpHga1iECRB5kXG1jGxbjcoSroTEh6A&oe=6409068C&_nc_sid=8fd12b" width="100px;" alt="Foto do jaoo"/><br>
        <sub>
          <b>Davi Demiciano Giovani</b>
        </sub>
      </a>
    </td>
  </tr>
</table>

## 📝 Licença

Esse projeto está sob licença. Veja o arquivo [LICENÇA](LICENSE.md) para mais detalhes.

[⬆ Voltar ao topo](#nome-do-projeto)<br>
