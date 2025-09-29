// --- Definição dos Pinos e Constantes ---

// Pinos dos LEDs de status
const int ledVerde = 13;     // Moto no local correto
const int ledAmarelo = 12;   // Moto em movimento / fora da zona segura
const int ledVermelho = 11;  // Alerta (não estacionada corretamente)

// Pinos do Sensor Ultrassônico (Proximidade)
const int trigPin = 5;
const int echoPin = 6;

// Pino do Potenciômetro (GPS simulado)
const int potPin = A0;

// Constantes de Limite
const int DISTANCIA_LIMITE = 15;   // Distância em cm para "moto no local correto"
const int VALOR_GPS_LIMITE = 500;  // Valor do Potenciômetro para "moto em área segura"

// Variáveis para o Ultrassônico
long duracao;
int distancia;

// Variáveis para o Potenciômetro
int valorGPS;

// Variável de status
String statusMoto;

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  Serial.println("Protótipo IoT iniciado...");
}

void loop() {
  // 1. Apaga todos os LEDs
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);

  // 2. Leitura do Potenciômetro (GPS simulado)
  valorGPS = analogRead(potPin);

  // 3. Leitura do Sensor Ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracao = pulseIn(echoPin, HIGH);
  distancia = duracao * 0.034 / 2;

  // 4. Lógica de Status (Controle dos LEDs e mensagem)
  if (valorGPS < VALOR_GPS_LIMITE && distancia > 0 && distancia < DISTANCIA_LIMITE) {
    digitalWrite(ledVerde, HIGH);
    statusMoto = "Moto no local correto";
  } else if (valorGPS >= VALOR_GPS_LIMITE) {
    digitalWrite(ledAmarelo, HIGH);
    statusMoto = "Moto em movimento / fora da zona segura";
  } else {
    digitalWrite(ledVermelho, HIGH);
    statusMoto = "ALERTA! Moto na zona segura, mas não estacionada corretamente";
  }

  // 5. Envio em JSON via Serial
  Serial.print("{\"status\":\"");
  Serial.print(statusMoto);
  Serial.print("\",\"gps\":");
  Serial.print(valorGPS);
  Serial.print(",\"distancia\":");
  Serial.print(distancia);
  Serial.println("}");

  delay(1000);
}
