//#################################################################################################  
/* 
   Tabella dei COUNT letti dall'ADC a 10 bit 
   interno all'arduino con una NTC da 10K collegata verso massa e una resistenza da 4700 ohm verso il +5
   Per l'ottimizzazione dei valori della resistenza e dunque dei count rispetto alla temperatura 
   utilizzate il fglio di calcolo "NTC10k-Tabella conversione"
   Il range di temperature misurate va da 105 °C a -40 °c
*/

//                   0     9     8     7     6     5     4     3     2    1
int CountT[146] = {                               112,  115,  118,  121,  124
                 ,  128,  131,  134,  138,  142,  145,  149,  153,  157,  161
                 ,  165,  170,  174,  179,  183,  188,  193,  198,  203,  209
                 ,  214,  220,  226,  231,  237,  244,  250,  256,  263,  269
                 ,  276,  283,  290,  298,  305,  313,  320,  328,  336,  344
                 ,  353,  361,  370,  378,  387,  396,  405,  415,  424,  433
                 ,  443,  453,  462,  472,  482,  492,  502,  512,  522,  533
                 ,  543,  553,  564,  574,  584,  595,  605,  615,  626,  636
                 ,  646,  656,  666,  676,  686,  696,  706,  715,  725,  734
                 ,  744,  753,  762,  771,  779,  788,  796,  805,  813,  820
                 ,  828,  836,  843,  850,  857,  864,  870,  877,  883,  889
                 ,  895,  901,  906,  911,  917,  921,  926,  931,  935,  940
                 ,  944,  948,  951,  955,  958,  962,  965,  968,  971,  974
                 ,  976,  979,  981,  984,  986,  988,  990,  992,  994,  996
                 ,  997,  999, 1000, 1002, 1003, 1004, 1005, 1007, 1008, 1009
                 , 1010
                 };


//////////////////////////////////////////////////////////////////////////////////////////////////////

//La riga seguente è il punto d'entrata della routine quando si legge l'ingresso analogico
//con un processo che verifica la qualità della misura
//int LeggeTemperatura(int tAnalogico, int tCampioni, int tTolleranza)

//La riga seguente è il punto di entrata per la routine con lettura diretta dell'ingresso
//analogico assegnato come parametro
int LeggeTemperatura(int tAnalogico)
/*Legge la Temperatura dalle NTC
  Funzione che renstituisce il valore INTERO della temperatura misurata da un sensore 
  termico resistivo di tipo NTC con valore nominale 10 kohm.
  Nel caso in cui s'intenda gestire i valori intermedi fra un grado e l'altro si dovrà
  cambiare il tipo di funzione da int a float oltre ad inserire un adeguato codice alla 
  fine del loop (for) di individuazione della temperatura.
  Il processo di individuazione è effettuato per confronto con il contenuto di un Array
  nel quale sono riportati i valori espressi in count associati ad ogni grado misurabile
  nel campo di misura compreso fra -40 e +105 °C (campo di funzionamento standard per le NTC
  commerciali). E' possibile reperire NTC in grado di funzionare in un campo di misura più
  esteso ma in questo caso bisogna aggiornare l'array.
  I valori di count sono calcolati con una resistenza in serie verso il +5 del valore di
  4700 ohm. Per maggiori dettagli consultare il foglio di calcolo specifico
*/
{
  int i;
  int lCount;
//La riga seguente è remmata in quanto usa per la lettura degli ingressi analogici la sub 
//che effettua sequenza di lettura con controllo di qualità del valore letto. 
//  lCount=CampionaAnalogico(tAnalogico, tCampioni, tTolleranza);
//La riga che segue effettua la lettura secca del sensore NTC che misura la temperatura dell'acqua
  lCount = analogRead(tAnalogico);
  
/*Trova la temperatura.
  il processo opera per confronto fra i count letti dall'A/D converter e
  la tabella di valori di riferimento CountT[] indicizzata per step di un grado centigrado
  Come trova il primo valore superiore fissa la temperatura. In questo modo si ottiene la
  temperatura più prossima per eccesso
*/
  for (i = 145; lCount < CountT[i]; i--)
  {
    //In questo loop è possibile inserire del codice per gestire la strategia di avvicinamento
    //alla temperatrura di riferimento (es.:avanzamento a "bolle" o progressioni geometriche o 
    //ricerca per prossimità con il valore precedente o ....)  
  }
  //Restituisce il complemento a Tmax (105°C) che rappresenta la temperatura misurata
  return (105-i);
}

