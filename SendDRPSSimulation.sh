#!/bin/bash
echo "*********************************************** Wilkommen zu DRPS Simulation, beta version ******************************************************************";
echo "--- Haben Sie die Simulationsparameter im file toy_2inner_det_configuration.txt überprüft? Wenn nein, bitte überprüfen Sie und wieder beginnen---";
read -p "(Y/N): " confirm && [[ $confirm == [yY] || $confirm == [yY][eE][sS] ]] ||  exit 1;
echo "--- bitte wählen Sie einen String , um die Ausgabe zu identifizieren ---";
read outputstring;
echo "--- bitte wählen Sie die Anzahl der Quell Schritte in z-Bereich (0-200 cm) ---";
read nsteps;
echo "--- Nach der Simulation, können Sie die PDF- Grundstücke im Verzeichnis pdffiles finden ---";
./DRPS_toy -c toy_2inner_det_configuration.txt -o $outputstring -n $nsteps 
for f in $( ls psfiles/*${outputstring}* ); do
    ps2pdf $f
    
done 
mv *.pdf pdffiles/
echo "**************************************************************************************************************************************************************";
