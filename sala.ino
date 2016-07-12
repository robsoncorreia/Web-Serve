//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
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
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
const byte releSala = 10;
const byte interruptor = 5;
unsigned long memoriaM;
const int atraso = 400;
byte trava;
byte saidaReleSala;
byte saidaReleQuintal;
byte estadoInterruptor;
byte contadorTrava;
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void setup() {
  //////////////////
  //   sck = 13   //
  //   miso = 12  //
  //   mosi = 11  //
  //   ce = 8     //
  //   csn = 7    //
  //////////////////
  pinMode(interruptor, INPUT);
  pinMode(releSala, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, 1);
  digitalWrite(releSala, 1);
  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Serial.begin(9600);
  Serial.println("Vamos la...");
  Serial.println("");
  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Mirf.cePin = 8;
  Mirf.csnPin = 7;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"dados");
  Mirf.setTADDR((byte *)"dados");
  Mirf.payload = sizeof(Dados);
  Mirf.channel = 0;
  Mirf.config();
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void loop() {
  //.................................................................................
  serial = Serial.read();
  saidaReleSala = digitalRead(releSala);
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
    if (contadorTrava == 1) {
      contadorTrava = 0;
      Serial.println("Destravado.");
      Serial.println("");
    }
    //.................................................................................
    while (contadorTrava == 1) {
      contadorTrava = 0;
      Serial.println("Destravado.");
      Serial.println("");
    }
    if ((estadoInterruptor == 1) && (trava == 1)) {
      trava = 0;
      Serial.println("Interruptor alterado.");
      alteraSala();
      travar();
    }
    else if ((estadoInterruptor == 0) && (trava == 0)) {
      trava = 1;
      Serial.println("Interruptor alterado.");
      alteraSala();
      travar();
    }
    //Todos.................................................................................
    if (todos == dadosAlteraTodos) {
      alteraTodos();
      travar();
    }
    else if (todos == dadosTodosLigados) {
       ligaTodos();
      travar();
    }
    else if (todos == dadosTodosDesligados) {
      desligaTodos();
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
    //Quarto.................................................................................
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
    //USB.................................................................................
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
  }
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void alteraTodos() {
  alteraSala();
  Dados[2] = dadosAlteraTodos;
  enviaDados();
  Serial.println("Todos os reles mudaram de estado.");
}
void ligaTodos() {
  ligaSala();
  Dados[2] = dadosTodosLigados;
  enviaDados();
  Serial.println("Todos os reles mudaram de estado para ligado.");
}
void desligaTodos() {
  desligaSala();
  Dados[2] = dadosTodosDesligados;
  enviaDados();
  Serial.println("Todos os reles mudaram de estado para desligado.");
}
//.................................................................................
void alteraQuarto() {
  Dados[0] = dadosAlteraQuarto;
  enviaDados();
  Serial.println("O rele que muda o estado da luz da quarto, foi alterado.");
}
void ligaQuarto() {
  Dados[0] = dadosLigaQuarto;
  enviaDados();
  Serial.println("O rele que muda o estado da luz da quarto foi ligado.");
}
void desligaQuarto() {
  Dados[0] = dadosDesligaQuarto;
  enviaDados();
  Serial.println("O rele que muda o estado da luz da quarto foi desligado.");
}
//.................................................................................
void alteraSala() {
  digitalWrite(releSala, !saidaReleSala);
  Serial.print("O rele que muda o estado da luz da sala, foi alterado ");
}
void ligaSala() {
  digitalWrite(releSala, LOW);
  Serial.print("O rele que muda o estado da luz da sala foi ligado.");
}
void desligaSala() {
  digitalWrite(releSala, HIGH);
  Serial.print("O rele que muda o estado da luz da sala foi desligado.");
}
//.................................................................................
void enviaDados() {
  Mirf.send((byte *) &Dados);
  while (Mirf.isSending()) {
    delay(10);
  }
  Serial.println("Enviado.");
}
//.................................................................................
void travar() {
  contadorTrava = 1;
  memoriaM = millis() + atraso;
  Serial.println("Travado.");
  sala = 0;
  quarto = 0;
  todos = 0;
}
//.................................................................................
