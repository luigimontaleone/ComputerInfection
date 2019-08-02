Computer Infection

Cos'è ?
Un gioco sviluppato da Luigi Montaleone e Simone Mungari per il progetto di Programmazione ad Oggetti :
Computer Infection è una rivisitazione del famoso gioco "Virus Attack", l'obiettivo è quello di completare i livelli (al momento 2 ma con facilità di aggiunta di altri) portando la percentuale di completamento della mappa al 75%, la percentuale aumenta ogni volta che il giocatore riuscirà a completare un "taglio" della mappa, in base alla grandezza del taglio verrà aumentata la percentuale di completamento.

Come si gioca?
-Per muovere il giocatore si usano le frecce direzionali, esso potrà muoversi soltanto lungo il bordo nero;
-Per tagliare la mappa si usa il tasto spazio/barra spaziatrice, tenerlo premuto insieme ad una direzione per continuare il taglio, se si vuole tornare indietro basta lasciare la barra spaziatrice;
-Per completare un taglio, è necessario che il giocatore arrivi (mentre si continua a tagliare) ad un altro punto sul bordo della mappa che non sia quello da cui si è partiti (attenzione ai nemici!), a quel punto la zona tagliata si colorerà.

Legenda dei valori della matrice logica:
-1 : percorso del player mentre taglia;
0 : vuoto;
1 : bordo;
3 : boss;
4 : nemico base;
5 : bonus;
7 : zona della mappa tagliata.

Come si avvia?
Andare nella cartella ComputerInfection/src e digitare i seguenti comandi da terminale:
1) g++ *.cpp -lallegro -lallegro_primitives -lallegro_image -lallegro_ttf -lallegro_font -lallegro_acodec -lallegro_audio -o computerInfection
2) ./computerInfection

Et voilà!
 
