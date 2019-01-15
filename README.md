**Autor: Patrycja Karbownik**

## AAL_Problem-Chinskiego-Listonosza
## AAL_8. Projekt z przedmiotu Analiza Algorytmów

W lasku Kampinoskim jest wiele ścieżek biegowo-rowerowych. Przygotowując się pod maraton zawodnik chce przebiec wszystkimi ścieżkami. Każdą ze ścieżek można pobiec w obu kierunkach i każda z nich ma określoną długość.
Należy wyznaczyć taką trasę biegaczowi która pokryje wszystkie ścieżki gdzie sumaryczny dystans będzie najmniejszy.

Problem postawiony w treści zadania jest problemem chińskiego listonosza. Sprowadza się on do znalezienia cyklu przechodzącego przez wszystkie krawędzie grafu co najmniej raz, w którym suma wag krawędzi jest najmniejszą możliwą sumą wag krawędzi spośród wszystkich takiego rodzaju cykli w grafie.

### Kompilacja
Kompilacja wykonuje się poprzez wywołanie make w folderze z plikami źródłowymi.

### Wywołanie:
./aal \<flag> \<parameters>

### Argumenty wywołania: 
| Flagi | Parametry | Znaczenie |
| ------ | ------ | ------ |
| -file| <file_name> | Wykonuje program z danymi z pliku o nazwie file_name. Plik musi znajdować się w folderze data |
| -eulerian | <number_of_vertices> <number_of_edges> | Wykonuje program z wygenerowanymi danymi. Generowany jest graf, który posiada cykl eulera. |
| -2odd | <number_of_vertices> <number_of_edges> |  Wykonuje program z wygenerowanymi danymi. Generowany jest graf, który posiada dwa nieparzyste wierzchołki. |
| -moreOdd | <number_of_vertices> <number_of_edges> <number_of_odd_vertices> |  Wykonuje program z wygenerowanymi danymi. Generowany jest graf, który posiada więcej niż dwa nieparzyste wierzchołki. |

Parametry number_of_vertices, number_of_edges i number_of_odd_vertices służą do sparametryzowania generatora.

### Format pliku w wywołaniu z parametrem -file:
v01 v02 le0 <br />
v11 v12 le1 <br />
... <br />
vi1 vi2 lei <br />

vi1 - indeks początkowego wierzchołka opisywanej krawędzi <br />
vi2 - indeks końcowego wierzchołka opisywanej krawędzi <br />
lei - długość opisywanej krawędzi

### Wyjscie
Na wyjsciu otrzymujemy przebieg cyklu eulera oraz jego długość.
Wyświetlana wcześniej struktura grafu wspomaga analizę problemu.

### Wykorzystane algorytmy:
- DFS - lekko zmodyfikowany do szukania cyklu Eulera oraz 
- Dijsktra - do wyszukiwania najkrótszych ścieżek między nieparzystymi wierzchołkami grafu
- Brute-force - do szukania minimalnego skojarzenia (połączenie nieparzystych wierzchołków w pary, które daje najmniejszą sumę wag). W algorytmie wykorzystywany też algorytm DFS.