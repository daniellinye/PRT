Het programma wordt gemakkelijk gecompileert, door in uw terminal naar de folder "opdracht2" te gaan en vanuit daar 'make' in de terminal in te voeren. Het programma wordt gecompileerd met de naam: Sheet.
Wel is het belangrijk om de export LD_LIBRARY_PATH=. uit te voeren i.v.m. shared libraries. Deze wordt niet geexport in de makefile omdat het netter is om dat te doen in de console.

Zodra het programma wordt gestart, komt u in een lege sheet terecht met 24 rijen en 80 kolommen. De kolommen zijn alfabetisch genummerd en de rijen numeriek. De huidige cell die geselecteerd is is A1. Via 'q' of 'Q' kunt u in dit hoofdmenu het programma sluiten. U kunt rondbewegen met de pijltjestoetsen en met enter komt u in een edit window. 
Met enter opent er bovenop de geselecteerde cel een window ten grootte van 2 cellen. Hier kunt u de cel van waarde doen veranderen. Druk nogmaals op enter om het window te verlaten en de celwaarde aan te passen naar de ingevoerde waarde.
U kunt ook de cel verwijderen met backspace.
Ook is er functionaliteit met formules =SUM, =AVG en =COUNT.

Het programma wordt gecompileerd met gcc.

Taakverdeling:

Daniël Lin: grootste gedeelte deadline A, unique_ptr, Range, formules

Jordi Boerboom: Testing

Robert Arntzenius: UI, formules
