//Gestisce lo stato dei motori
//

void StatoMotori()
{
  switch (CaldaiaStato)
  {
    case LOW:
//In questa condizione predispone lo spegnimento dei motori
      MotoriSpegne();
      
    case HIGH:
//Legge e controlla la temperatura dell'acqua e se è superiore alla soglia di accensione dei motori 
      if (LeggeTemperatura(NTCTemperaturaAcqua) > TemperaturaAcquaON)
      {
//Predispone lo sblocco dei motori        
        MotoriEnable = HIGH;
//Chiama la RegimeMotori per attualizzare la variazione        
        RegimeMotori();
//Spegne il lampeggio dei LED del pannello di controllo        
        FlashOnOff = LOW;
      }
      else
      {
//Controlla se la temperatura dell'acqua è scesa sotto la soglia di spegnimento.
//Esiste una fascia di temperature comprese fra la soglia di accensione e quella di 
//spegnimento dei motori nella quale non viene effettuata alcuna variazione 
        if (LeggeTemperatura(NTCTemperaturaAcqua) < TemperaturaAcquaOFF)
        {
//In questa condizione predispone lo spegnimento dei motori
          MotoriSpegne();      
        }
      }
    
  }
  Serial.println();
}



void RegimeMotori()
{
  if (MotoriEnable == LOW)
  {
//Spegne i motori
    Serial.print("Spegne i motori");
    digitalWrite(Motore1Enable, LOW);
    digitalWrite(Motore2Enable, LOW);
    MotoreVelocitaAttuale[0] = 0;
    MotoreVelocitaAttuale[1] = 0;
  }
  else
  {
//Controlla se il Motore 1 è richiesto
    if (MotoreRichiesto[0] == HIGH)
    {
//Attiva il canale di potenza 1
      digitalWrite(Motore1Enable, HIGH);
//Controlla se la velocità attuale è diversa da quella richiesta
      if (MotoreVelocitaAttuale[0] < MotoreVelocitaRichiesta[0])
      {
        MotoreVelocitaAttuale[0] ++;
      }
      if (MotoreVelocitaAttuale[0] > MotoreVelocitaRichiesta[0])
      {
        MotoreVelocitaAttuale[0] = MotoreVelocitaRichiesta[0];
      }
      analogWrite (Motore1Port, MotoreVelocitaAttuale[0]);
    }
//Altrimenti assume il Motore1 come non richiesto e spegne il canale di potenza
//corrispondente e setta a 0 la velocitta attiale
    else
    {
      digitalWrite(Motore1Enable, LOW);
      MotoreVelocitaAttuale[0] = 0;
    }
//Controlla se il Motore 2 è richiesto
    if (MotoreRichiesto[1] == HIGH)
    {
//Controlla se la velocità attuale è diversa da quella richiesta
      digitalWrite(Motore2Enable, HIGH);
      if (MotoreVelocitaAttuale[1] < MotoreVelocitaRichiesta[1])
      {
        MotoreVelocitaAttuale[1] ++;
      }
      if (MotoreVelocitaAttuale[1] > MotoreVelocitaRichiesta[1])
      {
        MotoreVelocitaAttuale[1] = MotoreVelocitaRichiesta[1];
      }
      analogWrite (Motore2Port, MotoreVelocitaAttuale[1]);
    }
//Altrimenti assume il Motore2 come non richiesto e spegne il canale di potenza
//corrispondente e setta a 0 la velocitta attiale
    else
    {
      digitalWrite(Motore2Enable, LOW);
      MotoreVelocitaAttuale[1] = 0;
    }
  }
  Serial.print("Motore 1 ");
  Serial.print(MotoreVelocitaAttuale[0]);
  Serial.print("  -  Motore 2 ");
  Serial.print(MotoreVelocitaAttuale[1]);

}


void MotoriSpegne()
{
//In questo caso spegne entrambe i motori, setta a zero la velocità attuale e lascia la 
//velocità richiesta al valore attuale    
  MotoriEnable = LOW;
  MotoreVelocitaAttuale[0]=0;
  MotoreVelocitaAttuale[1]=1;
//Chiama la RegimeMotori per attualizzare le variazioni
  RegimeMotori();
}
