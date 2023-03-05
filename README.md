# Ponto Biometrico Digital Com ESP266


<img src="https://github.com/oliveeiralucas/PontoBiometrico/blob/main/favicon.png" alt="exemplo imagem" weight="300px" height="300px">

> Este projeto consiste em um sistema de ponto biométrico digital desenvolvido com ESP8266. O dispositivo é capaz de capturar as impressões digitais dos usuários e registrar as marcações de entrada e saída em um servidor central, permitindo o controle de acesso e a gestão de frequência de funcionários de empresas ou instituições.

### Ajustes e melhorias

O projeto ainda está em desenvolvimento e as próximas atualizações serão voltadas nas seguintes tarefas:

- [x] Finalização da prototipação
- [x] Finalização da API
- [x] Finalização do servidor
- [ ] Finalizar Front-End
- [ ] Implementação de visor OLED

## 💻 Pré-requisitos

Antes de começar, verifique se você atendeu aos seguintes requisitos:

* Instalou a biblioteca `<http://arduino.esp8266.com/stable/package_esp8266com_index.json>`
* Instalou a IDE do Arduino `<https://www.arduino.cc/en/software>`
* Instalou a Biblioteca do Arduino `<esp8266 by esp8266 community>`
* Instalação do conversor USB Serial `<NodeMCU V2 / ESP32 com conversor USB serial CP210x>`
* Instalação do conversor USB Serial `<NodeMCU com conversor USB serial CH340G (V3)>`
* Instalação das Bibliotecas `<ESP8266WiFi.h/Adafruit_Fingerprint.h/WiFiClientSecure.h>`


## ☕ Usando <nome_do_projeto>

Para usar <nome_do_projeto>, siga estas etapas:

```
<Baixe os itens citados anteriormente, faça as conexões necessárias entre esp8266 e o Sensor, altere o código com seu wifi, senha e api do google >
```

Adicione comandos de execução e exemplos que você acha que os usuários acharão úteis. Fornece uma referência de opções para pontos de bônus!

## 📫 Contribuindo para <nome_do_projeto>
<!---Se o seu README for longo ou se você tiver algum processo ou etapas específicas que deseja que os contribuidores sigam, considere a criação de um arquivo CONTRIBUTING.md separado--->
Para contribuir com <nome_do_projeto>, siga estas etapas:

1. Bifurque este repositório.
2. Crie um branch: `git checkout -b <nome_branch>`.
3. Faça suas alterações e confirme-as: `git commit -m '<mensagem_commit>'`
4. Envie para o branch original: `git push origin <nome_do_projeto> / <local>`
5. Crie a solicitação de pull.

Como alternativa, consulte a documentação do GitHub em [como criar uma solicitação pull](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request).

## 🤝 Colaboradores

Agradecemos às seguintes pessoas que contribuíram para este projeto:

<table>
  <tr>
    <td align="center">
      <a href="#">
        <img src="https://avatars3.githubusercontent.com/u/31936044" width="100px;" alt="Foto do Iuri Silva no GitHub"/><br>
        <sub>
          <b>Iuri Silva</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="#">
        <img src="https://s2.glbimg.com/FUcw2usZfSTL6yCCGj3L3v3SpJ8=/smart/e.glbimg.com/og/ed/f/original/2019/04/25/zuckerberg_podcast.jpg" width="100px;" alt="Foto do Mark Zuckerberg"/><br>
        <sub>
          <b>Mark Zuckerberg</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="#">
        <img src="https://miro.medium.com/max/360/0*1SkS3mSorArvY9kS.jpg" width="100px;" alt="Foto do Steve Jobs"/><br>
        <sub>
          <b>Steve Jobs</b>
        </sub>
      </a>
    </td>
  </tr>
</table>


## 🔎 Como o Projeto Funciona 
> O sistema é baseado em uma placa ESP8266 que se comunica com um sensor de impressão digital e um display OLED. Através de uma interface amigável, os usuários podem fazer suas marcações de ponto, que são registradas em um banco de dados centralizado e acessível através de uma API. O dispositivo também possui recursos de segurança, como autenticação de usuários e criptografia de dados.

## 📝 Licença

Esse projeto está sob licença. Veja o arquivo [LICENÇA](LICENSE.md) para mais detalhes.

[⬆ Voltar ao topo](#nome-do-projeto)<br>
