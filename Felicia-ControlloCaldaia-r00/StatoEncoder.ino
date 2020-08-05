//#################################################################################################  
//Legge e gestisce gli encoder


void StatoEncoder()
{
//Carica nella variabile temporanea il valore associato adesso all'encoder 1
  newPosition = myEnc1.read();
//Controlla l'over e l'under flow e lo limita ai valori ammessi.
  EncoderVerificaLimiti();
//Aggiorna il valore della funzione encoder dopo aver controllato l'eventuale
//superamento dei limiti 
  myEnc1.write(newPosition);
//Aggiorna la variabile di destinazione
  MotoreVelocitaRichiesta[0]=newPosition;
/*  
  if (newPosition != oldPosition1) 
  {
    oldPosition1 = newPosition;
    MotoreVelocitaRichiesta[0] = oldPosition1;
    Serial.print("1 - ");
    Serial.print(oldPosition1);
  }
*/
    Serial.print("1 - ");
    Serial.print(MotoreVelocitaRichiesta[0]);

//Carica nella variabile temporanea il valore associato adesso all'encoder 2
  newPosition = myEnc2.read();
//Controlla l'over e l'under flow e lo limita ai valori ammessi.
  EncoderVerificaLimiti();
//Aggiorna il valore della funzione encoder dopo aver controllato l'eventuale
//superamento dei limiti 
  myEnc2.write(newPosition);
//Aggiorna la variabile di destinazione
  MotoreVelocitaRichiesta[1]=newPosition;
    Serial.print(" 2 - ");
    Serial.print(MotoreVelocitaRichiesta[1]);
  Serial.println();
}


//Mantiene la variabile di conta della funzione Encoder all'interno dei limiti prefissati
void EncoderVerificaLimiti()
{
  if (newPosition>255)
  {
    newPosition=255;
  }
  if (newPosition<0)
  {
    newPosition=0;
  }

}
