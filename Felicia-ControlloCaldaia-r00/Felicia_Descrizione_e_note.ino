/* 
Sistema per la gestione di due ventole (termoconvettori) e di una caldaia
per la climatizzazione invernale di imbarcazioni.
Lo studio è stato sviluppato per Felicia di Enzo Bucciarelli.

I controlli installati sono i seguenti:
Encoder 1 con pulsante;
Encoder 2 con pulsante;
Led 1;
Led 2;
Led 3;
Termosensore NTC 10K.
Fotoresistenza per il controllo della luminosita del pannello comandi.

Le funzioni gestite sono le seguenti:
Controllo accensionee e spegnimento Caldaia;
Controllo accensione, spegnimento e velocità Ventilatore (termoconvettore) 1;
Controllo accensione, spegnimento e velocità Ventilatore (termoconvettore) 2;

CONTROLLO ACCENSIONE E SPEGNIMENTO CALDAIA
Il contatto di servizio che comanda l'accensione della caldaia deve predisporre
l'accensione quando viene richiesto l'avviamento di almeno uno dei due motori
(termoconvettori).

CONTROLLO ACCENSIONE, SPEGNIMENTO E VELOCITA VENTILATORE 1 & 2
I due ventilatori (termoconvettori) sono associati ognuno ad un encoder e più
precisamente, il motore 1 all'encoder di sinistra (encoder 1) e il motore 2
all'encoder di destra (encoder 2).

Lo stato dei motori all'accensione è SPENTO.
La velocità effettiva dei motori all'accensione è settata a 0 (motore fermo)
La velocità richiesta è settata al valore settato l'ultima volta che sono stati in funzione.

Ogni encoder è dotato della funzione pulsante la quale agisce sullo stato dei
motori scambiandola da Spento (default) ad Acceso e viceversa.

I valori delle velocità richieste per i motori sono conservati nella memoria non volatile
interna così da garantire la memorizzazione del dato anche ad apparecchiatura spenta

Per una migliore gestione della rumorosità dei motori nelle velocità intermedie, la funzione
PWM ha la frequenza di lavoro impostabile così da poter ottimizzare il punto di lavoro 
elettrico con le risonanze meccaniche dei motori
*/

/*
Librerie
EEPROM.h - Gestione dell'EEPROM interna al processore. Le operazioni di scrittura della
memoria non volatile sono gestite sempre come cambiamenti così da aumentare la vita
effettiva del dispositivo.

Encoder.h - Gestisce la lettura degli encoder attraverso l'uso degli interrupt

Bounce2.h - Gestisce la lettura degli switch con l'introduzione di un filtro
per il debounce e la gestione del cambio di stato.
*/

