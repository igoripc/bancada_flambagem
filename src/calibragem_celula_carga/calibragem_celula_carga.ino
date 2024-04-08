#include <HX711.h>

// Defina os pinos da celula de carga
#define pinDT  11
#define pinSCK  10

HX711 scale;

void setup() {
  Serial.begin(57600);

  scale.begin(pinDT, pinSCK); 
  scale.set_scale(); 

  delay(100);
  scale.tare(); 

  Serial.println("Balança Zerada");
}

void loop() {
  // Leitura da média de 3 medidas
  float leitura = scale.get_units(3); 
  // Visualização do valor no monitor serial com 3 casas decimais
  Serial.println(leitura, 3);

  delay(100);
}