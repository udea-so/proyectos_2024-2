#include <Arduino.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <FreeRTOS.h>

const int sensor = 12; // Pin para el sensor de humedad
const int bomba = 14;  // Pin para la bomba de riego

int valorsensor;
int storedHumidity = 0; // Para almacenar el valor recuperado de la NVS

// Declaración de tareas para FreeRTOS
void leerSensor(void *pvParameters);
void controlarBomba(void *pvParameters);

// Configuración inicial
void setup()
{
  Serial.begin(115200);

  // Inicialización de la NVS
  if (nvs_flash_init() == ESP_ERR_NVS_NO_FREE_PAGES || nvs_flash_init() == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ESP_ERROR_CHECK(nvs_flash_init());
  }

  // Leer el valor almacenado de la NVS (si existe)
  nvs_handle my_handle;
  esp_err_t err = nvs_open("storage", NVS_READWRITE, &my_handle);
  if (err == ESP_OK)
  {
    err = nvs_get_i32(my_handle, "humidity", &storedHumidity);
    if (err == ESP_OK)
    {
      Serial.print("Valor almacenado de humedad: ");
      Serial.println(storedHumidity);
    }
    else
    {
      Serial.println("No se encontraron datos almacenados.");
    }
    nvs_close(my_handle);
  }
  else
  {
    Serial.println("Error al abrir NVS.");
  }

  pinMode(sensor, INPUT_PULLDOWN);
  pinMode(bomba, OUTPUT);

  // Crear las tareas en FreeRTOS
  xTaskCreate(leerSensor, "Leer Sensor", 1000, NULL, 1, NULL);
  xTaskCreate(controlarBomba, "Controlar Bomba", 1000, NULL, 1, NULL);
}

// Tarea para leer el sensor de humedad
void leerSensor(void *pvParameters)
{
  while (true)
  {
    valorsensor = analogRead(sensor);
    Serial.print("Valor del sensor: ");
    Serial.println(valorsensor);

    // Guardar el valor en la NVS
    nvs_handle my_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err == ESP_OK)
    {
      err = nvs_set_i32(my_handle, "humidity", valorsensor);
      if (err == ESP_OK)
      {
        Serial.println("Valor de humedad almacenado correctamente.");
        err = nvs_commit(my_handle);
        if (err != ESP_OK)
        {
          Serial.println("Error al guardar los datos.");
        }
      }
      nvs_close(my_handle);
    }
    else
    {
      Serial.println("Error al abrir NVS.");
    }

    vTaskDelay(5000 / portTICK_PERIOD_MS); // Esperar 5 segundos antes de la siguiente medición
  }
}

// Tarea para controlar la bomba de riego
void controlarBomba(void *pvParameters)
{
  while (true)
  {
    if (valorsensor >= 2100)
    {
      digitalWrite(bomba, HIGH); // Activar la bomba
      delay(500);                // Mantenerla activada por 500ms
      digitalWrite(bomba, LOW);  // Desactivar la bomba
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Esperar 1 segundo antes de comprobar de nuevo
  }
}

void loop()
{
  // En FreeRTOS, el código en el loop no es necesario para las tareas
  // pero si deseas realizar algún monitoreo o función adicional, aquí iría.

  // Monitoreo de uso de memoria (opcional, puedes agregar en este lugar)
  Serial.print("Memoria libre: ");
  Serial.println(ESP.getFreeHeap());

  // Monitoreo de CPU (opcional, puedes agregar en este lugar)
  Serial.print("Uso de CPU: ");
  Serial.println(uxTaskGetSystemState(NULL, 0, NULL)); // Muestra el estado del sistema (no es una medición directa del CPU)

  delay(10000); // Espera de 10 segundos antes de la siguiente medición
}
