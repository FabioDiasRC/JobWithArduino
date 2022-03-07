#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define endereco  0x27
#define colunas   20
#define linhas    4

LiquidCrystal_I2C lcd(endereco, colunas, linhas);

int pino_sensor = 7;
int valor = 1; //Variavel leitura sensor
int contador = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  Serial.begin(9600);
  pinMode(pino_sensor, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("Contador de Abelhas");
  lcd.setCursor(0, 1);
  lcd.print("UFMG");
  lcd.setCursor(0, 3);
  lcd.print("Contador: 0");
  delay(2000);
  
}

void loop()
{
  //Le o pino do sensor
  valor = digitalRead(pino_sensor);
  //Verifica se algum objeto foi detectado (valor = 0)
  if (valor == 0)
  {
    //Incrementa o contador
    contador++;
    //Mostra o valor do contador no display
    lcd.setCursor(10, 3);
    lcd.print(contador);
    //Mostra o valor do contador no serial monitor
    Serial.println("Contador de Abelhas");
    Serial.println("UFMG");
    Serial.print("Contador: ");
    Serial.println(contador);
    //Loop caso o objeto fique parado em frente ao sensor
    while (digitalRead(pino_sensor) == 0)
    {
      delay(100);
    }
  }
}
