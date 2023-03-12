<!-- POCRIS SABIN - 312CB  -->

# Tema2 - ThreadPoolExecutor

## Tipuri definite

### `ThreadPool`

Practic, e un stack pentru `Thread`urile ce urmeaza a fi
adaugate.

### `SysConfig`

Acest tip reprezinta specificatiile "calculatorului".

### `Queue`

Bine cunoscutul tip, implementat cu ajutorul listelor
generice simplu inlantuite.

### `Stack`

Bine cunoscutul tip, implementat cu ajutorul listelor
generice simplu inlantuite. x 2

### `IO`

Aici pastrez pointerii spre fisierele de I/O.

### `CPU`

O structura ce "simuleaza" procesorul, necesara pentru
calcularea timpului rularii `Task`urilor.

## Logica - TL;DR

`main()`-ul initializeaza "obiectele" (daca esti un 
programator C++, altfel, variabilele) necesare, urmand
sa apeleze la infinit functia `getCommand()` ce returneaza
un cod ce indica ce operatie trebuie efectuata, conform
inputului. Se apeleaza functiile specifice fiecarei operatie.

Hmm, `assignedIDs` tine toate id-urile atribuite: 
`assignedIDs[id]` poate fi `0`(liber) sau  `1`(luat). Am
ales sa consum mai multa memorie,dar sa fie timpul mai mare
Alte metode ar fi fost sa iterez prin cozi sau sau lucrez
cu masti pe biti, probabil mai lente.

`addTasks()` obtine datele necesare din I/O, initializeaza
`Task`urile si le adauga in coada, apeland `addTaskWaitingQ()`, pentru a fi adaugate in ordine.

Am decis sa "sortez" cand inserez un obiect, astfel
fac o noua coada cu elementele la stanga lui, adaug elementul
meu si apoi restul elementelor.

Cam la fel functioneaza inserarea si la celelalte cozi.

`getTask()` si `getThread()` parcurg obiectele necesare,
si afiseaza obiectul cerut, dupa specificatii.

`printWaitingQ(), `print..Q()`etc, printeaza tipurile de
cozi, dupa specificatii.

`run()` (functia mea preferata <3):
  - incarca `Task`urile in coada `runningQ`
  - ruleaza in paralel
  - verifica daca exista `Task`uri finished si le adauga in coada `Finished`

`finish()` e ca un run, doar ca timpul de executie
este timpul cel mai mare ramas din coada + rularea
pana la eliberarea coadei `waitingQ`

`closeIO()` ,`deleteQue()` si `deleteStack()` sunt folosite
pentru eliberarea memoriei si inchiderea fisierelor. 
