int a, b, c, d, MenuSeleccionado = 0;
int aux, tiempo, scoreD, auxE, scoreC, auxD = 0;
int dificultad = 300;

int pos = 3;
bool Carril1, Carril2, Carril3 = 0;

// Con 1 saltas // Con 0 estás quieto
bool EstoySaltando, EstoySaltando2 = 0;
bool Tierra[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
bool Aire[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool Aire2[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int estados[] = {1,2,3};

/////////////////////////////////////////////// DINOSAURIO///////////////////////////////////////////
byte DINO_PARADO[8] = {B01111,B01101,B01111,B01110,B11110,B11110,B01010,B01010}; 
byte DINO_PIE_DERE[8] = {B01111,B01101,B01111,B01110,B11110,B11110,B01000,B01000};
byte DINO_PIE_IZQU[8] = {B01111,B01101,B01111,B01110,B11110,B11110,B00010,B00010};
byte Cactus1[8] = {B01101,B01101,B01101,B01111,B01100,B01100,B01100,B01100};
byte Cactus2[8] = {B10100,B10101,B10101,B10111,B11100,B00100,B00100,B00100};
byte AveParada[] = {0x00,0x08,0x18,0x1F,0x00,0x00,0x00,0x00};
byte AveAletea[] = {0x00,0x08,0x18,0x1F,0x07,0x03,0x01,0x00};
byte Carro[8] = {B11000,B11100,B01110,B01111,B01111,B01110,B11100,B11000};


#include <LiquidCrystal.h>
#include <LiquidMenu.h>

LiquidCrystal lcd_1(7, 6, 5, 4, 3, 2);

LiquidLine Linea1(1,0, "Dinosaurio");
LiquidLine Linea2(1,1, "Carretera");
LiquidLine Linea3(1,2, "Puntuaciones");
LiquidLine Linea4(1,3, "Apagar Consola");

LiquidScreen Pantalla1(Linea1, Linea2, Linea3, Linea4);

LiquidLine Linea1_2(1,0, "Jugar ");
LiquidLine Linea2_2(1,1, "Puntuacion ");
LiquidLine Linea3_2(1,2, "Dificultad");
LiquidLine Linea4_2(1,3, "Atras");

LiquidScreen Pantalla2(Linea1_2, Linea2_2, Linea3_2, Linea4_2);

LiquidLine Linea1_3(1,0, "Jugar ");
LiquidLine Linea2_3(1,1, "Puntuacion ");
LiquidLine Linea3_3(1,2, "Dificultad");
LiquidLine Linea4_3(1,3, "Atras");

LiquidScreen Pantalla3(Linea1_3, Linea2_3, Linea3_3, Linea4_3);

LiquidLine Linea1_4(1,0, "Dificultad 1");
LiquidLine Linea2_4(1,1, "Dificultad 2");
LiquidLine Linea3_4(1,2, "Dificultad 3");

LiquidScreen Pantalla4(Linea1_4, Linea2_4, Linea3_4);

LiquidMenu menu(lcd_1, Pantalla1, Pantalla2, Pantalla3, Pantalla4);
void setup() {

  lcd_1.begin(20,4); 
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);

    // Bienvenida
    lcd_1.print("Bienvenidos");
    delay(1000);
    lcd_1.setCursor(0, 1);
    lcd_1.print("A mi consola");
    delay(1000);
    lcd_1.setCursor(0, 2);
    lcd_1.print("By Jesus Vargas");
    delay(1000);
    lcd_1.setCursor(0, 3);
    lcd_1.print("UCLA");
    delay(2000);
    lcd_1.clear();

  // Inicializar variables para la skin del dinosaurio

  lcd_1.createChar(0,DINO_PARADO);             
  lcd_1.createChar(1,DINO_PIE_DERE);          
  lcd_1.createChar(2,DINO_PIE_IZQU);
  lcd_1.createChar(4,Cactus2);
  lcd_1.createChar(3,Carro);


  // Menu General
  Linea1.set_focusPosition(Position::LEFT);
  Linea2.set_focusPosition(Position::LEFT);
  Linea3.set_focusPosition(Position::LEFT);
  Linea4.set_focusPosition(Position::LEFT);

  Linea1.attach_function(1, MenuDinosaurio);
  Linea2.attach_function(1, MenuCarretera);
  Linea3.attach_function(1, PuntuacionGeneral);
  Linea4.attach_function(1, Apagado);

  menu.add_screen(Pantalla1);

  // Menu del juego del dinosaurio
  Linea1_2.set_focusPosition(Position::LEFT);
  Linea2_2.set_focusPosition(Position::LEFT);
  Linea3_2.set_focusPosition(Position::LEFT);
  Linea4_2.set_focusPosition(Position::LEFT);

  Linea1_2.attach_function(1, JugarDino);
  Linea2_2.attach_function(1, Puntuacion);
  Linea3_2.attach_function(1, MenuDificultad);
  Linea4_2.attach_function(1, Salir);

  menu.add_screen(Pantalla2);
  // Menu del juego del ahorcado
  Linea1_3.set_focusPosition(Position::LEFT);
  Linea2_3.set_focusPosition(Position::LEFT);
  Linea3_3.set_focusPosition(Position::LEFT);
  Linea4_3.set_focusPosition(Position::LEFT);

  Linea1_3.attach_function(1, JugarCarretera);
  Linea2_3.attach_function(1, PuntuacionCarretera);
  Linea3_3.attach_function(1, MenuDificultad);
  Linea4_3.attach_function(1, Salir);

  menu.add_screen(Pantalla3);
  //Menu de dificultad
  Linea1_4.set_focusPosition(Position::LEFT);
  Linea2_4.set_focusPosition(Position::LEFT);
  Linea3_4.set_focusPosition(Position::LEFT);

  Linea1_4.attach_function(1, Dificultad1);
  Linea2_4.attach_function(1, Dificultad2);
  Linea3_4.attach_function(1, Dificultad3);

  menu.add_screen(Pantalla4);

  Pantalla1.set_displayLineCount(4);
  Pantalla2.set_displayLineCount(4);
  Pantalla3.set_displayLineCount(4);
  Pantalla4.set_displayLineCount(4);
  // Establecer el foco del menu en la primera opcion
  menu.set_focusedLine(0);

  menu.update();
}
void loop(){
  d = digitalRead(11);
  selectOption();
  a = digitalRead(8);
	c = digitalRead(10);

  if(a == HIGH){
    menu.switch_focus(true);
    delay(300);
    menu.update();
  }
  else if(c == HIGH){
    menu.switch_focus(false);
    delay(300);
    menu.update();
  }
}

void selectOption(){
  if(digitalRead(9) == HIGH){
    Serial.println("Boton");
    menu.call_function(1);
    delay(500);
  }
}
void PrintHola(){
  lcd_1.clear();
  lcd_1.print("Hola");
  delay(3000);
}
void PrintLolo(){
  lcd_1.clear();
  lcd_1.print("Lolo");
  delay(3000);
}
void MenuDinosaurio(){
  menu.change_screen(2);
  menu.set_focusedLine(0);
}

void MenuCarretera(){
  menu.change_screen(3);
  menu.set_focusedLine(0);
}

void MenuDificultad(){
  menu.change_screen(4);
  menu.set_focusedLine(0);
}

void Dificultad1(){
  lcd_1.clear();
  lcd_1.print("dificultad cambiada con exito");
  delay(1000);
  dificultad = 300;
  auxD = 1;
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void Dificultad2(){
  lcd_1.clear();
  lcd_1.print("dificultad cambiada con exito");
  delay(1000);
  dificultad = 200;
  auxD = 2;
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void Dificultad3(){
  lcd_1.clear();
  lcd_1.print("dificultad cambiada con exito");
  delay(1000);
  dificultad = 150;
  auxD = 3;
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void PuntuacionGeneral(){
  lcd_1.clear();
  lcd_1.print("Score Dinosaurio:");
  lcd_1.setCursor(0,1);
  lcd_1.print(scoreD);
  lcd_1.setCursor(0,2);
  lcd_1.print("Score Carretera:");
  lcd_1.setCursor(0,3);
  lcd_1.print(scoreC);
  delay(5000);
}

void  PuntuacionCarretera(){
  lcd_1.clear();
  lcd_1.print("Su puntuacion es: ");
  lcd_1.setCursor(0,1);
  lcd_1.print(scoreC);
  delay(5000);
}

void JugarCarretera(){
  lcd_1.clear();
  while(true){

    Carril1 = digitalRead(11);
    Carril2 = digitalRead(8);
    Carril3 = digitalRead(10);

    if(Carril1 == HIGH){
      pos = 1;
    }
    if(Carril2 == HIGH){
      pos = 2;
    }
    if(Carril3 == HIGH){
      pos = 3;
    }
    if(pos == 1){
      lcd_1.setCursor(2,1);
      lcd_1.write(byte(3));
      lcd_1.setCursor(2,3);
      lcd_1.print(" ");
      lcd_1.setCursor(2,2);
      lcd_1.print(" ");
    }

    if(pos == 2){
      lcd_1.setCursor(2,2);
      lcd_1.write(byte(3));
      lcd_1.setCursor(2,3);
      lcd_1.print(" ");
      lcd_1.setCursor(2,1);
      lcd_1.print(" ");
    }

    if(pos == 3){
      lcd_1.setCursor(2,3);
      lcd_1.write(byte(3));
      lcd_1.setCursor(2,2);
      lcd_1.print(" ");
      lcd_1.setCursor(2,1);
      lcd_1.print(" ");
    }

    // Bucle para imprimir aves
    for (int i = 0; i < 20; i++){
      if (i == 2){
        continue;
      }
      lcd_1.setCursor(i,2);
      if (Aire[i] == 1){
        lcd_1.print(">");
      }
      else{
        lcd_1.print(" ");
      }
      lcd_1.setCursor(i,1);
      if (Aire2[i] == 1){
        lcd_1.print(">");
      }
      else{
        lcd_1.print(" ");
      }
      lcd_1.setCursor(i,3);
      if (Tierra[i] == 1){
          lcd_1.write(">");
      }
      else{
        lcd_1.print(" ");
      }
    }
    // Bucle para avanzar en Tierra
    for (int i = 0; i < 19; i++){
      Tierra[i] = Tierra[i+1];
      Tierra[i+1] = 0;
      Aire[i] = Aire[i+1];
      Aire[i+1] = 0;
      Aire2[i] = Aire2[i+1];
      Aire2[i+1] = 0;
    }

    lcd_1.setCursor(10,0);
    lcd_1.print("Score:");
    lcd_1.print(tiempo);

    if(tiempo % 7 == 0)
      Tierra[19] = 1; //Cactus
    else
      Tierra[19] = 0; //Sin cactus

    if(tiempo % 23 == 0  && Tierra[19] == 0)
      Aire[19] = 1; //volador
    else
      Aire[19] = 0; //volador
    
    if(tiempo % 13 == 0  && Tierra[19] == 0 && Aire[19] == 0)
      Aire2[19] = 1; //volador
    else
      Aire2[19] = 0; //volador
    
    ////////////////COLISIONES////////////////////////
    if(Tierra[2] && pos == 3){
      break;
    }

    if(Aire[2] && pos == 2){
      break;
    }

    if(Aire2[2] && pos == 1){
      break;
    }
    
    if(auxD == 1){
      if(tiempo % 8 == 0){
        dificultad -= 2;
      }
    }
    else if(auxD == 2){
      if(tiempo % 13 == 0){
        dificultad -= 2;
      }
    }
    else if(auxD == 3){
      if(tiempo % 7 == 0){
        dificultad -= 2;
      }
    }
    delay(dificultad);
    tiempo++;
  }
    lcd_1.clear();
    lcd_1.setCursor(0,0);
    lcd_1.print("Game Over");
    lcd_1.setCursor(0,1);
    lcd_1.print("Gracias por jugar");
    scoreC = tiempo;
    tiempo = 0;
    for (int i = 0; i<=20; i++){
      Tierra[i] = 0;
      Aire[i] = 0;
      Aire2[i] = 0;
    }
    delay(5000);
}

void Puntuacion(){
  lcd_1.clear();
  lcd_1.print("Su puntuacion es: ");
  lcd_1.setCursor(0,1);
  lcd_1.print(scoreD);
  delay(5000);
}

void JugarDino(){
  lcd_1.clear();
  while(true){
    EstoySaltando = digitalRead(11);
    EstoySaltando2 = digitalRead(8);
    if(EstoySaltando2 == HIGH){
      lcd_1.setCursor(2,1);
      lcd_1.write(byte(0));
      lcd_1.setCursor(2,3);
      lcd_1.print(" ");
    }
    else if(EstoySaltando == HIGH){
      lcd_1.setCursor(2,2);
      lcd_1.write(byte(0));
      lcd_1.setCursor(2,3);
      lcd_1.print(" ");
    }
    else{
      /*lcd_1.setCursor(2,1);
      lcd_1.print(" ");
      lcd_1.setCursor(2,2);
      lcd_1.print(" ");
      lcd_1.setCursor(2,3);
      lcd_1.print("0");*/
      if(auxE == 1){
      lcd_1.setCursor(2,1);
      lcd_1.print(" ");
      lcd_1.setCursor(2,2);
      lcd_1.print(" ");
      lcd_1.setCursor(2,3);
      lcd_1.write(byte(0));
      }
      if(auxE == 2){
      lcd_1.setCursor(2,1);
      lcd_1.print(" ");
      lcd_1.setCursor(2,2);
      lcd_1.print(" ");
      lcd_1.setCursor(2,3);
      lcd_1.write(byte(1));
      }
      if(auxE == 3){
      lcd_1.setCursor(2,1);
      lcd_1.print(" ");
      lcd_1.setCursor(2,2);
      lcd_1.print(" ");
      lcd_1.setCursor(2,3);
      lcd_1.write(byte(2));
      }
      if(auxE == 4){
        auxE = 0;
      }
      auxE += 1;
    }

    // Bucle para imprimir aves
    for (int i = 0; i < 20; i++){
      if (i == 2){
        continue;
      }
      lcd_1.setCursor(i,2);
      if (Aire[i] == 1){
        lcd_1.print("<");
      }
      else{
        lcd_1.print(" ");
      }
      lcd_1.setCursor(i,1);
      if (Aire2[i] == 1){
        lcd_1.print("<");
      }
      else{
        lcd_1.print(" ");
      }
      lcd_1.setCursor(i,3);
      if (Tierra[i] == 1){
          lcd_1.write(byte(4));
      }
      else{
        lcd_1.print(" ");
      }
    }



    // Bucle para avanzar en Tierra
    for (int i = 0; i < 19; i++){
      Tierra[i] = Tierra[i+1];
      Tierra[i+1] = 0;
      Aire[i] = Aire[i+1];
      Aire[i+1] = 0;
      Aire2[i] = Aire2[i+1];
      Aire2[i+1] = 0;
    }

    lcd_1.setCursor(10,0);
    lcd_1.print("Score:");
    lcd_1.print(tiempo);

    if(tiempo % 7 == 0)
      Tierra[19] = 1; //Cactus
    else
      Tierra[19] = 0; //Sin cactus

    if(tiempo % 23 == 0  && Tierra[19] == 0)
      Aire[19] = 1; //volador
    else
      Aire[19] = 0; //volador
    
    if(tiempo % 13 == 0  && Tierra[19] == 0 && Aire[19] == 0)
      Aire2[19] = 1; //volador
    else
      Aire2[19] = 0; //volador
    

    if(Tierra[2] && EstoySaltando == 0 && EstoySaltando2 == 0){
      break;
    }

    if(Aire[2] && EstoySaltando == 1 && EstoySaltando2 == 0){
      break;
    }

    if(Aire2[2] && EstoySaltando == 0 && EstoySaltando2 == 1){
      break;
    }

    if(auxD == 1){
      if(tiempo % 8 == 0){
        dificultad -= 2;
      }
    }
    else if(auxD == 2){
      if(tiempo % 13 == 0){
        dificultad -= 2;
      }
    }
    else if(auxD == 3){
      if(tiempo % 27 == 0){
        dificultad -= 2;
      }
    }
    delay(dificultad);
    tiempo++;
  }
    lcd_1.clear();
    lcd_1.setCursor(0,0);
    lcd_1.print("Game Over");
    lcd_1.setCursor(0,1);
    lcd_1.print("Gracias por jugar");
    scoreD = tiempo;
    tiempo = 0;
    for (int i = 0; i<=20; i++){
      Tierra[i] = 0;
      Aire[i] = 0;
      Aire2[i] = 0;
    }
    delay(5000);
}

void Apagado(){
  lcd_1.clear();
  while(d == LOW){
    d = digitalRead(11);
  }
}

void Salir(){
  menu.change_screen(1);
  menu.set_focusedLine(0);
}