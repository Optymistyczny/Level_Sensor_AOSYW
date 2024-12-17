#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <stdint.h>

typedef enum { OKK, ERR } status_t;
status_t initialize();
status_t getDistance_m(float*);
status_t getDistance_mm(float*);
status_t getTemperature_Celcious(float*);
status_t getTemperature_Fahrenheit(float*);
status_t getDistanceSensorName(char*, const uint8_t);
status_t getTempSensorName(char*, const uint8_t);

// Użycie CMSIS-V2
// Model klient-serwer
// Wątek, który czeka na pojawienie się w kolejce żądania - obsługa i pójście "spać"
// Semafor liczący, kolejka
// Metoda put umieszczająca żądanie w kolejce
// Wskaźnik na void* - adres komórki pamięci z najmniejszą adresacją dostępną (8 bit np.)
 
// Implementacja z wykorzystaniem FreeRTOS'a, kolejki i wzorca klient-serwer:
// Dwa taski (kliencki) -nr 1 dpowiedzialny za umieszczanie żądań w kolejce. Nr 2 odpowiedzialny za obsługę zakolejkowanych żądań. Kiedy żądań nie ma - task nr 2 jest uśpiony. 
// Oba taski korzystają z semafora liczącego, żeby było wiadome ile zadań umieszczone jest w kolejne. Task nr 1 inkrementuje semafor a task nr 2 go dekrementuje. 

// Dlaczego kolejka? Eliminuje zagrożenie równoczesnego dostępu do zasobów, czyli zapewnia, że dwa różne taski nie będą odwoływały się do struktur jak np. sensor_t* sensor_array[SENSORS].

// Co mogłaby mieć w sobie kolejka?
// Wskaźniki do takich oto struktur danych:

// -----------------------------
// | request_t | request_type |    (temperature or distance)
// -----------------------------
// |   void*   |    value     |   ( dzięki request_t wiadomo na jaki typ zrzutować sobie wskaźnik do adresu pamięci celem przechowania wyniku)
// -----------------------------

// Problem - zmiana interfejsu spowoduje, że trzeba będzie przebudować testy itd. 
// Rozwiązanie - wydzielenie kolejnego modułu z API typowo FreeRTOSowego.

#endif // SENSORMANAGER_H
