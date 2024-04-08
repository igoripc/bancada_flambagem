#include <HX711.h>
#include <LiquidCrystal_I2C.h>

#define pinDT_A  13
#define pinSCK_A  12

#define pinDT_B  11
#define pinSCK_B  10

#define pinDT_C  9
#define pinSCK_C  8

#define pinBotao 7

LiquidCrystal_I2C lcd(0x27, 16, 2);

HX711 scale_A;
HX711 scale_B;
HX711 scale_C;

void setup() {
  Serial.begin(57600);

  // Célula A
  scale_A.begin(pinDT_A, pinSCK_A); // CONFIGURANDO OS PINOS DA BALANÇA
  scale_A.set_scale(110126); // LIMPANDO O VALOR DA ESCALA
  scale_A.tare(); // ZERANDO A BALANÇA PARA DESCONSIDERAR A MASSA DA ESTRUTURA

  // Célula B
  scale_B.begin(pinDT_B, pinSCK_B); // CONFIGURANDO OS PINOS DA BALANÇA
  scale_B.set_scale(-1536723); // LIMPANDO O VALOR DA ESCALA
  scale_B.tare(); // ZERANDO A BALANÇA PARA DESCONSIDERAR A MASSA DA ESTRUTURA

  // Célula C
  scale_C.begin(pinDT_C, pinSCK_C); // CONFIGURANDO OS PINOS DA BALANÇA
  scale_C.set_scale(105721); // LIMPANDO O VALOR DA ESCALA
  scale_C.tare(); // ZERANDO A BALANÇA PARA DESCONSIDERAR A MASSA DA ESTRUTURA

  pinMode(pinBotao, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up interno

  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Bancada Flambagem");

  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");

  Serial.println("Balança Zerada");
  delay(1000);
  lcd.clear();
}


void loop() {
  // Verifica se o botão foi pressionado
  if (digitalRead(pinBotao) == LOW) {
    scale_A.tare(); // Zera a balança
    scale_B.tare(); // Zera a balança
    scale_C.tare(); // Zera a balança
    Serial.println("Balança Zerada"); // Envia mensagem para o monitor serial
    delay(500); // Pequeno atraso para evitar leituras múltiplas ao manter o botão pressionado
  }

  // Célula A
  float medida_A = scale_A.get_units(1);

  // Célula B
  float medida_B = scale_B.get_units(1);

  // Célula C
  float medida_C = scale_C.get_units(1); 
  
 
  // Print dos valores
  Serial.print("A: ");
  Serial.print(medida_A, 3);
  Serial.print("  B: ");
  Serial.print(medida_B, 3);
  Serial.print("  C: ");
  Serial.println(medida_C, 3);

  // Garantindo que apenas valores positivos sejam exibidos no display
  medida_A = abs(medida_A);
  medida_B = abs(medida_B);
  medida_C = abs(medida_C);

  // Formatando as medidas como strings com 3 casas decimais
  char str_A[10]; // 7 caracteres para incluir o sinal, o ponto decimal e o caractere nulo
  char str_B[10];
  char str_C[10];
  
  dtostrf(medida_A, 6, 3, str_A);
  dtostrf(medida_B, 6, 3, str_B);
  dtostrf(medida_C, 6, 3, str_C);

  // Exibindo os valores formatados no display LCD
  lcd.setCursor(0, 0);
  lcd.print("A:");
  lcd.print(str_A);

  lcd.setCursor(0, 1);
  lcd.print("B:");
  lcd.print(str_B);

  lcd.setCursor(9, 0);
  lcd.print("|");
  lcd.print("C:");
  lcd.setCursor(9, 1);
  lcd.print("|");
  lcd.print(str_C);

  delay(100);
}

