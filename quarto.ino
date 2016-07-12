//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define vermelhoSamsung 0xE0E036C9
#define verdeSamsung 0xE0E028D7
#define amareloSamsung 0xE0E0A857
#define azulSamsung 0x71A1FE88
#define playSamsung 0x6A618E02
#define voltaSamsung 0x75D1D566
#define pauseSamsung 0xE0F44528
//----------------------------------------------------------------------------------
#define vermelhoDuoSat 0xEFB24D
//----------------------------------------------------------------------------------
#define amareloLG 0x20DF4EB1
#define verdeLG 0x20DF8E71
#define vermelhoLG 0x20DFC639
#define azulLG 0x20DF8679
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#include <TrueRandom.h>
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
const byte interruptor = 9;
const byte rele = 10;
byte saidaRele;
byte estadoInterruptor;
boolean trava = false;
//...............................................................
int Dados[3];
const int IR = 6;
unsigned long memoriaM;
int atraso = 400;
boolean contadorTrava = true;
IRrecv irrecv(IR);
decode_results results;
/////////////////////////////////////////////////////////////////
void setup() {
  pinMode(interruptor, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(rele, OUTPUT);
  digitalWrite(3, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 1);
  digitalWrite(rele, 1);
  //...............................................................
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
  //...............................................................
  Serial.begin(9600);
  irrecv.enableIRIn();
  Serial.println("Vamos la...");
}
/////////////////////////////////////////////////////////////////
void loop() {
  serial = Serial.read();
  saidaRele = digitalRead(rele);
  estadoInterruptor = digitalRead(interruptor);
  //RF.............................................................
  Mirf.getData((byte *) &Dados);
  delay(50);
  quarto = Dados[0];
  sala = Dados[1];
  todos = Dados[2];
  //Trava............................................................
  if (memoriaM > millis() ) {
  }
  else {
    if (contadorTrava == true) {
      contadorTrava = false;
      Serial.println("Destravado.");
      Serial.println("");
    }
    //Interruptor....................................................
    if ((estadoInterruptor == 1) && (trava == true)) {
      trava = false;
      Serial.println("Interruptor alterado.");
      alteraQuarto();
      travar();
    }
    else if ((estadoInterruptor == 0) && (trava == false)) {
      trava = true;
      Serial.println("Interrruptor alterado.");
      alteraQuarto();
      travar();
    }
    //Todos.........................................................
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
    //Quarto.........................................................
    if (quarto == dadosAlteraQuarto) {
      alteraQuarto();
      travar();
    }
    else if (quarto == dadosLigaQuarto) {
      ligaQuarto();
      travar();
    }
    else if (quarto == dadosDesligaQuarto) {
      desligaQuarto();
      travar();
    }
    //Sala.................................................................................
    if (sala == dadosAlteraSala) {
      alteraSala();
      travar();
    }
    else if (sala == dadosLigaSala) {
      ligaSala();
      travar();
    }
    else if (sala == dadosDesligaSala) {
      desligaSala();
      travar();
    }
    //USB............................................................
    if (serial == 'a') {
      alteraQuarto();
      travar();
    }

    if (serial == 'b') {
      alteraSala();
      travar();
    }

    if (serial == 'c') {
      alteraTodos();
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
void alteraTodos() {
  digitalWrite(rele, !saidaRele);
  Serial.println("Todos os reles foram alterados.");
  Dados[2] = dadosAlteraTodos;
  enviaDados();
}
void ligaTodos() {
  ligaQuarto();
  Dados[2] = dadosTodosLigados;
  enviaDados();
}
void desligaTodos() {
  desligaQuarto();
  Dados[2] = dadosTodosDesligados;
  enviaDados();
}
//...............................................................
void alteraQuarto() {
  Serial.println("O rele que muda o estado da luz do quarto, foi alterado.");
  digitalWrite(rele, !saidaRele);
}
//...............................................................
void alteraSala() {
  Serial.println("O rele que muda o estado da luz do sala, foi alterado.");
  Dados[1] = dadosAlteraSala;
  enviaDados();
}
//............................................................
void ligaSala() {
  Serial.println("O rele que muda o estado da luz do sala foi ligado.");
  Dados[1] = dadosLigaSala;
  enviaDados();
}
//............................................................
void desligaSala() {
  Serial.println("O rele que muda o estado da luz do sala foi desligado.");
  Dados[1] = dadosDesligaSala;
  enviaDados();
}
//............................................................
void enviaDados() {
  Mirf.send((byte *) &Dados);
  while (Mirf.isSending()) {
    delay(10);
  }
  Serial.println("Enviado...");
}
//..............................................................
void travar() {
  contadorTrava = true;
  memoriaM = millis() + atraso;
  Serial.println("Travado.");
  sala = 0;
  quarto = 0;
  todos = 0;
}
//.................................................................................
void ligaQuarto() {
  digitalWrite(rele, LOW);
  Serial.println("Rele ligado.");
}
//.................................................................................
void desligaQuarto() {
  digitalWrite(rele, HIGH);
  Serial.println("Rele desligado.");
}
//.................................................................................
