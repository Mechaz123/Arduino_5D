//DATOS DEL ABECEDARIO EN MATRIZ 5D
char abecedario[3][3][3][6][4] ={{ //LETRAS A,B,C PARA EL NUMERO 1
                                   {{"0110", "1001", "1001", "1111", "1001", "1001"},
                                    {"1110", "1001", "1110", "1001", "1001", "1110"},
                                    {"0111", "1000", "1000", "1000", "1000", "0111"}},
                                   // LETRAS D,E,F PARA EL NUMERO 2
                                   {{"1110", "1001", "1001", "1001", "1001", "1110"},
                                    {"1111", "1000", "1110", "1000", "1000", "1111"},
                                    {"1111", "1000", "1000", "1110", "1000", "1000"}},
                                   // LETRAS G,H,I PARA EL NUMERO 3
                                   {{"0111", "1000", "1000", "1011", "1001", "0110"},
                                    {"1001", "1001", "1001", "1111", "1001", "1001"},
                                    {"1111", "0110", "0110", "0110", "0110", "1111"}}},


                                 { //LETRAS J,K,L PARA EL NUMERO 4
                                   {{"1111", "0010", "0010", "0010", "1010", "0100"},
                                    {"1001", "1010", "1100", "1100", "1010", "1001"},
                                    {"1000", "1000", "1000", "1000", "1000", "1111"}},
                                   //LETRAS M,N,O PARA EL NUMERO 5
                                   {{"1001", "1111", "1001", "1001", "1001", "1001"},
                                    {"0000", "0000", "1001", "1101", "1011", "1001"},
                                    {"0110", "1001", "1001", "1001", "1001", "0110"}},
                                    //LETRAS P,Q,R PARA EL NUMERO 6
                                   {{"1111", "1001", "1111", "1000", "1000", "1000"},
                                    {"0100", "1010", "1010", "1010", "1010", "0111"},
                                    {"1110", "1001", "1110", "1100", "1010", "1001"}}},


                                 { //LETRAS S,T,U PARA EL NUMERO 7
                                   {{"0111", "1000", "0110", "0001", "1001", "0110"},
                                    {"1111", "1111", "0110", "0110", "0110", "0110"},
                                    {"1001", "1001", "1001", "1001", "1001", "0110"}},
                                   //LETRAS V,W,X PARA EL NUMERO 8
                                   {{"1001", "1001", "1001", "1001", "1010", "0100"},
                                    {"1001", "1001", "1001", "1001", "1111", "1001"},
                                    {"1001", "0110", "0110", "0110", "0110", "1001"}},
                                   //LETRAS Y,Z PARA EL NUMERO 9
                                   {{"1001", "1001", "0110", "0110", "0110", "0110"},
                                    {"1111", "0001", "0010", "0100", "1000", "1111"}}}
                                };
//VARIABLES DEL PROGRAMA
int aux_j=0, cont=0,anterior_i=5, anterior_j=5, posicion=0;
char mensaje[6][56],LEDS[6][8];

void setup(){
  /*Serial.begin(9600);*/

  for(int i=0;i<18;i++){
    pinMode(i,OUTPUT);
  }
  for(int i=0;i<6;i++){
    digitalWrite(i,HIGH);
  }
  for(int i=18;i<22;i++){
    pinMode(i,INPUT);
  }
}

void loop(){
  Teclado();
}

void Teclado(){
  for(int i=0;i<4;i++){
    analogWrite((i+14),255);
    for(int j=0;j<4;j++){
      if(analogRead(i+14)>900 && analogRead(j+18)>900){
        aux_j=j+18;
        Soltar_Tecla();
        if((anterior_i==5 && anterior_j==5) && (i<3 && j<3)){
          anterior_i=i;
          anterior_j=j;
        }else if((anterior_i==i) && (anterior_j==j)){
          anterior_i=i;
          anterior_j=j;
          cont++;
          if((cont==3) || (i==2 && j==2 && cont==2)){
            cont=0;
          }
        }else if(((anterior_i!=i) && (anterior_j!=j)) || ((anterior_i==i) && (anterior_j!=j)) || ((anterior_i!=i) && (anterior_j==j))){
          if(i<3 && j<3){
            anterior_i=i;
            anterior_j=j;
            cont=0;
          }
        }
        //PINTAR LAS TECLA PRESIONADA
        if(i<3 && j<3){
          Pintar_Tecla(i, j, cont);
        }
        //GUARDAR TECLA PRESIONADA
        if((i==3 && j==0)){
          Guardar_Letra(anterior_i, anterior_j,cont);
        }
        if(i==3 && j==1){
          Tecla_Espacio();
        }
        if(i==3 && j==2){
          Limpiar_Pantalla();
          Imprimir_Mensaje();
        }
      }
    }
    analogWrite((i+14),0);
  }
}

void Soltar_Tecla(){
  do{
  }while(analogRead(aux_j)>900);
}

void Pintar_Tecla(int x, int y, int cont){
  Limpiar_Pantalla();
    char letra[6][4];
    for(int i=0;i<6;i++){
      for(int j=0;j<4;j++){
        letra[i][j]=abecedario[x][y][cont][i][j];
      }
    }
    for(int tiempo=0;tiempo<96;tiempo++){
      for(int i=0;i<6;i++){
      digitalWrite(i,LOW);
      for(int j=0;j<4;j++){
        if(letra[i][j]=='0'){
          digitalWrite((j+6),LOW);
        }else if(letra[i][j]=='1'){
          digitalWrite((j+6),HIGH);
        }
      }
      delay(5.208333);
      digitalWrite(i,HIGH);
      }
    }
}

void Guardar_Letra(int x, int y, int z){
  Limpiar_Pantalla();
    if(anterior_i<3 && anterior_j<3){
      int aux=posicion+4;
      for(int i=0;i<6;i++){
        for(int j=posicion;j<aux;j++){
          mensaje[i][j]=abecedario[x][y][z][i][j-posicion];
        }
      }
      posicion=posicion+4;
      /*for(int i=0;i<6;i++){
        for(int j=0;j<posicion;j++){
          Serial.print("[");
          Serial.print(mensaje[i][j]);
          Serial.print("]");
        }
        Serial.print("\n");
      }*/
    }
}

void Tecla_Espacio(){
  Limpiar_Pantalla();
  int aux=posicion+4;
  for(int i=0;i<6;i++){
    for(int j=posicion;j<aux;j++){
      mensaje[i][j]='0';
    }
  }
  posicion=posicion+4;
}

void Imprimir_Mensaje(){
  Limpiar_Pantalla();
  bool imprimir=true;
  int columna_mensaje=0;
  if(posicion>12){
    for(int i=0;i<6;i++){
      for(int j=posicion;j<(posicion+8);j++){
        mensaje[i][j]='0';
      }
    }
    posicion=posicion+8;
    do{
      //Rotar todo de LEDS a la izquierda
      for(int i=0;i<6;i++){
        for(int j=1;j<8;j++){
          LEDS[i][j-1]=LEDS[i][j];
        }
      }
      for(int i=0;i<6;i++){
        LEDS[i][7]=mensaje[i][columna_mensaje];
      }
      columna_mensaje++;
      if(columna_mensaje==posicion){
        columna_mensaje=0;
      }
      for(int x=0;x<96;x++){
        for(int y=0;y<6;y++){
          digitalWrite(y,LOW);
          for(int z=0;z<8;z++){
            if(LEDS[y][z]=='0'){
              digitalWrite((z+6),LOW);
            }else if(LEDS[y][z]=='1'){
              digitalWrite((z+6),HIGH);
            }
          }
          delay(5.208333);
          digitalWrite(y,HIGH);
        }
      }
      imprimir=Detener();
    }while(imprimir);
  }
}

void Limpiar_Pantalla(){
  for(int i=0;i<6;i++){
    digitalWrite(i,HIGH);
  }
  for(int i=6;i<14;i++){
    digitalWrite(i,LOW);
  }
}

bool Detener(){
  bool imprimir=true;
  
  for(int i=0;i<4;i++){
    analogWrite((i+14),255);
    for(int j=0;j<4;j++){
      if(analogRead(i+14)>900 && analogRead(j+18)>900){
        if(i==0 && j==3){
          anterior_i=5;
          anterior_j=5;
          aux_j=0;
          cont=0;
          posicion=0;
          for(int x=0;x<6;x++){
            for(int y=0;y<56;y++){
              mensaje[x][y]='0';
            }
          }
          for(int x=0;x<6;x++){
            for(int y=0;y<8;y++){
              LEDS[x][y]='0';
            }
          }
          Limpiar_Pantalla();
          imprimir=false;
          return imprimir;
        }
      }
    }
  }
  return imprimir;
}
