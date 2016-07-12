//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define vermelhoSamsung 0xE0E036C9
#define verdeSamsung 0xE0E028D7
#define amareloSamsung 0xE0E0A857
#define azulSamsung 0x71A1FE88
#define playSamsung 0x6A618E02
#define voltaSamsung 0x75D1D566
#define pauseSamsung 0xE0F44528
#define powerSamsung 0xE0E040BF
//----------------------------------------------------------------------------------
#define vermelhoDuoSat 0xEFB24D
//----------------------------------------------------------------------------------
#define amareloLG 0x20DF4EB1
#define verdeLG 0x20DF8E71
#define vermelhoLG 0x20DFC639
#define azulLG 0x20DF8679
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <string.h>
#include <Wire.h>
#include <IRremote.h>
/////////////////////////////////////////////////////////////////
const int dadosAlteraQuarto = 1;
const int dadosAlteraSala = 2;
const int dadosLigaSala = 3;
const int dadosDesligaSala = 4;
const int dadosLigaQuarto = 5;
const int dadosDesligaQuarto = 6;
const int dadosAlteraTodos = 9;
const int dadosTodosLigados = 7;
const int dadosTodosDesligados = 8;
int quarto;
int sala;
int todos;
int serial;
/////////////////////////////////////////////////////////////////
int Dados[3];
int chave;
int USB;
const int IR = 6;
unsigned long memoriaM;
const int atraso = 400;
int contadorMelodia;
boolean contadorTrava = true;
IRrecv irrecv(IR);
IRsend irsend;
decode_results results;
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void setup() {
  Mirf.cePin = 8;
  Mirf.csnPin = 7;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"dados");
  Mirf.setTADDR((byte *)"dados");
  Mirf.payload = sizeof(Dados);
  Mirf.channel = 0;
  Mirf.config();
  //////////////////
  //   sck = 13   //
  //   miso = 12  //
  //   mosi = 11  //
  //   ce = 8     //
  //   csn = 7    //
  //////////////////
  //.................................................................................
  delay(6000);
  Serial.begin(9600);
  Serial.println("Vamos la...");
  Serial.println("");
  //.................................................................................
  irrecv.enableIRIn();
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void loop() {
  //RF.............................................................
  serial = Serial.read();
  Mirf.getData((byte *) &Dados);
  delay(50);
  quarto = Dados[0];
  sala = Dados[1];
  todos = Dados[2];
  //Trava............................................................................
  if (memoriaM > millis() ) {
    Serial.println("Travado...");
  }
  else {
    //.................................................................................
    while (contadorTrava == true) {
      contadorTrava = false;
      Serial.println("...Destravado.");
      Serial.println("");
    }
    //Todos.............................................................................
    if (todos == dadosAlteraTodos) {
      alteraTodos();
      travar();
    }
    if (todos == dadosTodosLigados) {
      ligaTodos();
      travar();
    }
    if (todos == dadosTodosDesligados) {
      desligaTodos();
      travar();
    }
    //Sala.............................................................................
    if (sala == dadosAlteraSala) {
      alteraSala();
      travar();
    }
    else if (sala == dadosLigaSala) {
      ligaSala();
      travar();
    }
    else  if (sala == dadosDesligaSala) {
      desligaSala();
      travar();
    }
    //USB..............................................................................
    if (serial == 'a') {
      ligaQuarto();
      travar();
    }
    else if (serial == 'b') {
      desligaQuarto();
      travar();
    }
    else if (serial == 'c') {
      ligaSala();
      travar();
    }
    else if (serial == 'd') {
      desligaSala();
      travar();
    }
    else if (serial == 'e') {
      ligaTodos();
      travar();
    }
    else if (serial == 'f') {
      desligaTodos();
      travar();
    }
    else if(serial == 'g'){
      irsend.sendNEC(0xE0E040BF,HEX);
      travar();
    }
    //IR...............................................................................
    if (irrecv.decode(&results)) {
      if ((results.value == vermelhoSamsung) or (results.value == amareloLG)) {
        Serial.println("Botão 'vermelho Samsung' ou 'amarelo LG' precionado.");
        alteraSala();
        travar();
      }
      else if ((results.value == verdeSamsung) or (results.value == verdeLG)) {
        Serial.println("Botão 'verde Samsung' ou 'verde LG' precionado.");
        alteraQuarto();
        travar();
      }
      else if ((results.value == amareloSamsung) or (results.value == vermelhoLG)) {
        Serial.println("Botão 'amarelo Samsung' ou 'vermelho LG' precionado.");
        alteraTodos();
        travar();
      }
      else {
        Serial.println(results.value, HEX);
        Serial.println("");
      }
      delay(50);
      irrecv.resume(); // Receive the next value
    }
  }
}
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void alteraQuarto() {
  Dados[0] = dadosAlteraQuarto;
  enviaDados();
  Serial.println("Foi alterado o estado do rele, presente na quarto.");
}
//.................................................................................
void ligaQuarto() {
  Dados[0] = dadosLigaQuarto;
  enviaDados();
  Serial.println("Foi alterado o estado do rele presente no quarto foi ligado.");
}
//.................................................................................
void desligaQuarto() {
  Dados[0] = dadosDesligaQuarto;
  enviaDados();
  Serial.println("Foi alterado o estado do rele presente no quarto foi desligado.");
}
//.................................................................................
void alteraSala() {
  Dados[1] = dadosAlteraSala;
  enviaDados();
  Serial.println("Foi alterado o estado do rele, presente na sala.");
}
//.................................................................................
void ligaSala() {
  Dados[1] = dadosLigaSala;
  enviaDados();
  Serial.println("Foi alterado o estado do rele presente na sala para ligado.");
}
//.................................................................................
void desligaSala() {
  Dados[1] = dadosDesligaSala;
  enviaDados();
  Serial.println("Foi alterado o estado do rele presente na sala para desligado.");
}
//.................................................................................
void alteraTodos() {
  alteraSala();
  Dados[2] = dadosAlteraTodos;
  enviaDados();
  Serial.println("Foi alterado o estado de todos reles.");
}
void ligaTodos() {
  Dados[2] = dadosTodosLigados;
  enviaDados();
  Serial.println("Foi alterado o estado de todos reles para ligado.");
}
void desligaTodos() {
  Dados[2] = dadosTodosDesligados;
  enviaDados();
  Serial.println("Foi alterado o estado de todos reles para desligado.");
}
//.................................................................................

void enviaDados() {
  Mirf.send((byte *) &Dados);
  while (Mirf.isSending()) {
    delay(10);
  }
}
//.................................................................................
void travar() {
  contadorTrava = true;
  memoriaM = millis() + atraso;
  sala = 0;
  quarto = 0;
  todos = 0;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


