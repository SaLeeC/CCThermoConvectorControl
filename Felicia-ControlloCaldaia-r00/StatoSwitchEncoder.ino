void StatoSwitchEncoder()
//#################################################################################################  
//Aggiorna lo stato degli switch degli encoder

{
//Aggiorna lo stato dello switch dell'encoder1
  myEnc1Click.update();
//Controlla/aggiorna lo stato dello switch dell'encoder 1
  if (myEnc1Click.read() == LOW)
  {
//Aggiorna lo stato della variabile Switch
    myEnc1Switch = !myEnc1Switch;
//Attende il rilascio del pulsante
    do
    {
      myEnc1Click.update();
    }
    while (myEnc1Click.read() == LOW);
  }
  digitalWrite(Motore1LED, myEnc1Switch);
//Copia lo stato dello switch nella variabile di stato del Motore 1
  MotoreRichiesto[0] = myEnc1Switch;

//Aggiorna lo stato dello switch dell'encoder2
  myEnc2Click.update();
//Aggiorna la variabile non volatile associata alla Velocità Richiesta del motore 1
//Se il motore si accende preleva il valore dalla memoria non volatile
  if (MotoreRichiesto[0] == HIGH)
  {
    MotoreVelocitaRichiesta[0] = EEPROM.read(Motore1SpeedRequiredAddress);
  }
//Se il motore si spegne memorizza il valore corrente della velocità richiesta 
//nella variabile non volatile
  else
  {
    EEPROM.update(Motore1SpeedRequiredAddress, MotoreVelocitaRichiesta[0]);
  }



//Controlla/aggiorna lo stato dello switch dell'encoder 2
  if (myEnc2Click.read() == LOW)
  {
//Aggiorna lo stato della variabile Switch
    myEnc2Switch = !myEnc2Switch;
//Attende il rilascio del pulsante
    do
    {
      myEnc2Click.update();
    }
    while (myEnc2Click.read() == LOW);
  }
//Aggiorna lo stato del LED di segnalazione
  digitalWrite(Motore2LED, myEnc2Switch);
//Aggiorna lo stato dellla variabile di stato del Motore 2
  MotoreRichiesto[1] = myEnc2Switch;
//Aggiorna la variabile non volatile associata alla Velocità Richiesta del motore 2
//Se il motore si accende preleva il valore dalla memoria non volatile
  if (MotoreRichiesto[1] == HIGH)
  {
    MotoreVelocitaRichiesta[1] = EEPROM.read(Motore2SpeedRequiredAddress);
  }
//Se il motore si spegne memorizza il valore corrente della velocità richiesta 
//nella variabile non volatile
  else
  {
    EEPROM.update(Motore2SpeedRequiredAddress, MotoreVelocitaRichiesta[1]);
  }
//  return;
}
