//#################################################################################################  
//Aggiorna lo stato della caldaia

void StatoCaldaia()
/*
Setta la variabile CaldaiaStato come da tabella seguente
+--------+--------+-------+
|Motore 1!Motore 2|Caldaia|
+--------+--------+-------+
!  LOW   |  LOW   |  LOW  |
+--------+--------+-------+
|  HIGH  |  LOW   |  HIGH |
+--------+--------+-------+
|  LOW   |  HIGH  |  HIGH |
+--------+--------+-------+
|  HIGH  |  HIGH  |  HIGH |
+--------+--------+-------+

*/
{
  CaldaiaStato = myEnc1Switch || myEnc2Switch;
  digitalWrite(CaldaiaRelay, CaldaiaStato);
  digitalWrite(CaldaiaLED, CaldaiaStato);
/*
  Serial.print("Motore 1 ");
  Serial.print(myEnc1Switch);
  Serial.print(" - Motore 2 ");
  Serial.print(myEnc2Switch);
  Serial.print(" - Caldaia ");
  Serial.println(CaldaiaStato);
*/
//  return
}
