#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define endereco  0x27
#define colunas   20
#define linhas    4
#define espacoEEPROM 1000

//definicao da localizacao do lcd
LiquidCrystal_I2C lcd(endereco, colunas, linhas);

int pino_sensor = 7;
int valor = 1;
int contador = 0;
int variavelInt;
int tempoAnterior = 0;
int address;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  Serial.begin(9600);
  pinMode(pino_sensor, INPUT);

  //o que sera mostrado no lcd (sem o contador de espacos)
  lcd.setCursor(0, 0);
  lcd.print("Contador de Abelhas");
  lcd.setCursor(0, 1);
  lcd.print("UFMG");
  lcd.setCursor(0, 3);
  lcd.print("Contador: 0");
}

void loop()
{
  //sensor infravermelho
  valor = digitalRead(pino_sensor);
  if (valor == 0)
  {
    contador++;
    lcd.setCursor(10, 3);
    lcd.print(contador);
    Serial.println(contador);

    while (digitalRead(pino_sensor) == 0)
    {
      delay(100);
    }
  }
   
     //codigo para modificar o contador e o valor da memoria EEPROM a ser salvo no espaço
     //no caso o valor deve ser dado em milisegundos
     //o intervalo de tempo é somado após tempoAnterior (exemplo: "tempoAnterior+5" é um intervalo de 5 segundos)
     int timing = (millis()/1000);
     if ( timing >= tempoAnterior+5) {      
        
        tempoAnterior = timing;
        variavelInt = contador;
        //salvando na memoria EEPROM
        EEPROM.write(address, variavelInt);

        //leitura e analise pelo monitor serial
        int value = EEPROM.read(address);
        Serial.println("-------------------------------------------");
        Serial.println("Contador de Abelhas");
        Serial.println("UFMG");
        Serial.print("Contador: ");
        Serial.println(contador);
        Serial.print("intervalo: ");
        Serial.println(address);
        Serial.print("valor salvo: ");
        Serial.println(value, DEC);
        Serial.println("-------------------------------------------");

        //valor deve ser o de espacos usados, ou 1024 para conferir todos os possiveis valores
        int espaco = 26;
        for ( int i = 0; i <= espaco; i++){
              int value = EEPROM.read(i);
                  Serial.println("-------------------------------------------");
                  Serial.print("espaço: ");
                  Serial.println(i);
                  Serial.print("valor salvo: ");
                  Serial.println(value, DEC);
                  Serial.println("-------------------------------------------");
            }

        lcd.setCursor(0, 2);
        lcd.print("Espacos:(    /1024)");
        lcd.setCursor(9, 2);
        lcd.print(address+1);
        
        address ++;
        contador = 0;
    }
 }
