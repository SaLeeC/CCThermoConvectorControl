/* 

Felicia - Controllo Caldaia
r00
22 febbraio 2016 

*/


#include "Thermistor4.h"

//Associa i piedini degli encoder a costanti
#define myEnc1A 3
#define myEnc1B 7
#define myEnc2A 2
#define myEnc2B 4

//Associa i piedini dei pulsanti degli encoder a costanti
#define myEnc1ClickPin 9
#define myEnc2ClickPin 8

//Associa il piedino di controllo del relay caldaia ad una costante
#define CaldaiaRelay 13
//Associa il piedino di controllo del LED di segnalazione della caldaia ad una costante
#define CaldaiaLED 14

//Associa il piedino dei LED Motore del pannello di comando a delle costanti
#define Motore1LED 16
#define Motore2LED 15

//Associa ad una costante la porta collegata al piedino Enable
#define Motore1Enable 12
#define Motore2Enable 11

//Associa ad una costante la porta PWM di controllo dei motori
#define Motore1Port 6
#define Motore2Port 5

//Associa il nuovo valore del prescaler (frequenza) del PWM per i motori
// ad una costante (default 64) 
#define MotorePwmPrescaler 8

//Associa il piedino per la lettura della luce ambiente ad una costante
#define LuminositaAmbiente 4

//Associa il piedino per la lettura della temperatura dell'acqua
#define NTCTemperaturaAcqua 5

//Associa la temperatura acqua di attivazione dei motori ad una costante
#define TemperaturaAcquaON 45

//Associa la temperatura acqua di disattivazione dei motori ad una costante
#define TemperaturaAcquaOFF 40

//Associa il valore minimo di luminostà dei LED ad una costante
#define LEDOffSet 254

/*
I LED del pannello di controllo sono a luminositta adattiva funzione della luminosità
ambiente. Questo viene realizzato tramite il controllo del comune dei LED collegato
al piedino PWM associato alla questa costante. La luminostà dei LED è INVERSAMENTE
proporzionale al valore del PWM (0 massima luminosita, 255 LED spenti)
*/
#define CommonLED 10

//Assegna l'adress della memoria non volatile per la memorizzazione della velocità
//richiesta per ogni motore
#define Motore1SpeedRequiredAddress 0
#define Motore2SpeedRequiredAddress 1

/*
Definisce il parametro velocità massima. In questa versione il modulo PWM è
a 8 bit e la variabile per lo storage della velocità è un byte per cui il limite
è a 255 ma, se si cambia hardware e si va verso qualcosa di più risoluto
si deve aggiornare le variabili
*/
#define maxSpeed 255

//Associa ad una costante il gradiente di variazione per la copertura del gap fra 
//velocità attuale e richiesta. Il gradiente è espresso in step/ciclo dove il ciclo
//è il tempo impiegato dal controller per completare un ciclo della sub Loop
#define GradientSpeed 5

//Associa ad una costante il tempo morto per ogni ciclo
#define DelayCiclo 100

//Associa ad una costante il numero di cicli per il lampeggio dei LED
#define FlashCicli 5

#include <EEPROM.h>
#include <Encoder.h>
#include <Bounce2.h>

//Variabile di appoggio per la gestione della luminostà dei LED
int AppoLuminosita;


// Associa i piedini A e B dei due encoder ai rispettivi Digital del controller 
Encoder myEnc1(myEnc1A, myEnc1B);
Encoder myEnc2(myEnc2A, myEnc2B);

//Variabile di servizio per la consultazione dell'encoder
long newPosition;


//Crea gli ogegtti Bounce
Bounce myEnc1Click = Bounce();
Bounce myEnc2Click = Bounce();
boolean myEnc1Switch;
boolean myEnc2Switch;

//Crea l'array per lo stato dei motori (LOW or HIGH)  
boolean MotoreRichiesto[2] = {0,0};

//Crea la variabile di gruppo per l'enable dei motori
boolean MotoriEnable = LOW;

//Crea l'array per la velocità corrente e richiesta dei motori (0-maxSpeed)
//La velocità Attuale è il parametro attualmente inviato al PWM di controllo del motore
//La velocità Richiesta è il parametro al quale il motore dovrà arrivare ed è salvato nell'EEPROM
byte MotoreVelocitaRichiesta[2] = {EEPROM.read(Motore1SpeedRequiredAddress),EEPROM.read(Motore2SpeedRequiredAddress)};
byte MotoreVelocitaAttuale[2] = {0,0};

//Crea la variabile per lo Stato Caldaia (LOW spenta HIGH accesa)
boolean CaldaiaStato = LOW;

//Crea la variabile per la temperatura dell'acqua
int TemperaturaAcqua;


//Contatore dei cicli
int ContatoreCicli = 0;
boolean FlashOnOff = LOW;

void setup() 
{

//Inizializza il canale di comunicazione seriale per la fase di debug
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");

//Setta la frequenza di funzionamento del PWM sui piedini  dei Motori
  setPwmFrequency(Motore1Port, MotorePwmPrescaler);
  setPwmFrequency(Motore2Port, MotorePwmPrescaler);

//Inizializza i LED del pannello di controllo
  pinMode(CaldaiaLED, OUTPUT);
  digitalWrite(CaldaiaLED,LOW);
  pinMode(Motore1LED, OUTPUT);
  digitalWrite(Motore1LED,LOW);
  pinMode(Motore2LED, OUTPUT);
  digitalWrite(Motore2LED,LOW);  

//Inizializza la porta per gli enable e il treno PWM di controllo dei motori
  pinMode(Motore1Port, OUTPUT);  
  pinMode(Motore2Port, OUTPUT);
  pinMode(Motore1Enable, OUTPUT);  
  pinMode(Motore2Enable, OUTPUT);  

//Imposta il piedino comune dei LED del pannello di controllo
  pinMode(CommonLED, OUTPUT);

//Inizializza come ingressi associati ad un PullUp i pin collegati al click
//degli encoder
  pinMode(myEnc1ClickPin, INPUT_PULLUP);
  pinMode(myEnc2ClickPin, INPUT_PULLUP);

//Associa il pin all'oggetto di controllo Switch degli encoder
  myEnc1Click.attach(myEnc1ClickPin);
  myEnc2Click.attach(myEnc2ClickPin);
  
//Setta il tempo di debounce in ms
  myEnc1Click.interval(5);
  myEnc2Click.interval(5);

//Inizializza la porta per il controllo del relay che comanda la caldaia
  pinMode(CaldaiaRelay, OUTPUT);
  digitalWrite(CaldaiaRelay, LOW);  
}


void loop() 
{

//#################################################################################################  
//Aggiusta la luminosità dei LED
  LuminositaLED();

//Controlla lo stato dei motori
  StatoMotori();
  
  StatoSwitchEncoder();

  StatoCaldaia(); 
 
//Possibile miglioramento - Lo stato degli encoder viene controllato e aggiornato 
//solo se i motori sono attivi
  StatoEncoder(); 

  ContatoreCicli ++;
  delay(100);

}
