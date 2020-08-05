//#################################################################################################  
//Adegua la luminosità dei LED in funzione della luminosità esterna

void LuminositaLED()
/*
Regola la luminostà dei LED in funzione della luce ambiente
Il fotosensore va indicativamente da 700 ohm in piena luce a circa
100kohm al buio che corrisponde a circa 0.5V in piena luce a circa 5V
al buio.
Il valore letto dal AD converter va da 0 a 1024 mentre i valori ammessi
dal PWM va da 0 (massima luminosità) a 255 (LED Spenti). Il processo
riduce il valore letto dall'AD converter nel range del PWM dividendolo
per 4 e per far si che al ridursi della luce i LED riducano la loro luminosità
si ottiene il valore PWM sottraendo a 255 il valore condizionato dell'AD Converter.
Per evitare che i LED si spengano completamente al buio, si aggiunge un offset al
valore ottenuto dall'elaborazione precedente.
*/
{
  if (MotoriEnable == LOW && ContatoreCicli > FlashCicli)
  {
    ContatoreCicli = 0;
    FlashOnOff = ! FlashOnOff;
  }
  
  AppoLuminosita = (analogRead(LuminositaAmbiente)/4)+50;
  //Serial.println(AppoLuminosita);
  if (AppoLuminosita > LEDOffSet)
  {
    AppoLuminosita = LEDOffSet;
  }
  if(FlashOnOff == LOW)
  {
    analogWrite(CommonLED,AppoLuminosita);
  }
  else
  {
    analogWrite(CommonLED,255);
  }
    
}
