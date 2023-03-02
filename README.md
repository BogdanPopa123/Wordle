Popa Bogdan-Florin 312CC



Problema 1 - timp de lucru: aproximativ 3 ore

Mod de rezolvare:
Functia 'onespace' returneaza stringul primit ca argument,
dar daca exista mai multe spatii intre cuvinte, acestea vor
fi reduse la un singur spatiu. De exemplu, daca vom pasa ca
argument stringul 'for      each    number   of    the following',
functia va returna 'for each number of the following'.
Stringul este returnat ca argument, intrucat functia este void.
Apoi, cu ajutorul functiei 'underscore' vom sublinia keywordurile
din stringul generat cu ajutorul functiei 'onespace', ce genereaza
underscoruri pentru pozitiile aferente.
Iar apoi, cu ajutorul functiei 'finalUnderscore' vom reconstitui
sublinierea stringului 'onespace' la stringul initial, ce contine
eventual mai multe spatii intre cuvinte. De exemplu, cu ajutorul
acestei functii, se va genera sublinierea pentru:
'for      each    number   of    the following'
 _____________
 functia primind ca argumente textul initial, textul cu un singur
 spatiu intre cuvinte, precum si sublinierea aferenta acestuia.
 Vom aplica acest procedeu pentru fiecare rand imputat de la tastatura.


 Problema 2 - timp de lucru: aproximativ 6 ore

 Mod de rezolvare:

 Mai intai populam dictionarul initial, cuvintele din acesta
 avand prioritatea 0, dupa care salvam in cuvinte[][] cuvintele
 ce vor trebui sa fie autocompletate. Pentru a rezolva aceasta
 problema, ne vom folosi de 3 functii auxiliare:

 search - care va cauta printre toate randurile dictionarului
 daca cuvantul primit ca argument face match cu vreunul 
 dintre randurile dictionarului. Daca se gaseste, functia
 va returna randul in dictionar la care s a facut match, iar
 in caz contrar se va returna -1

 addword - care adauga un nou cuvant in dictionar

 starsearch - care este folosita pentru a cauta in dictionar
 cuvntele de forma "cuv*". Aceasta functie va cauta daca 
 cuvantul primit ca argument exista deja in dictionar.
 Daca da, va returna randul in dictionar la care acest cuvant
 a fost gasit. In caz contrar, se va returna -1.

 Acum, ajutandu ne de cele trei functii vom trata fiecare
 cuvant: in cazul semnelor ortografice (.,?!:) le vom afisa
 fara niciun fel de prelucrare. In cazul cuvintelor cu steluta,
 vom efectua un starsearch. Daca rezultatul returnat este >=0,
 atunci crestem prioritatea cuvantului de pe randul cu numarul 
 returnat, si vom afisa cuvantul din dictionar ce se afla pe randul
 reprezentat de numarul returnat, iar in caz contrar adaugam 
 un nou cuvant in dictionar, pe care il si afisam.
 In cazul cuvintelor fara steluta, vom efectua un search. Daca
 rezultatul returnat este >=0, atunci crestem prioritatea
 cuvantului de pe randul cu numarul returnat, si vom afisa
 cuvantul din dictioar ce se afla pe randul reprezentat
 de numarul returnat, iar in caz contrar adaugam un nou
 cuvant in dictionar, pe care il si afisam.

 
 Problema 3- timp de lucru: aproximativ 4 ore

 Mod de lucru.
 Mai intai convertim numarul dat in binar, stocand
 fiecare bit in elementele unui vector, dupa care
 vom retine ultimii 6n+4 biti (bitii de care avem nevoie)
 in primele 6n+4 pozitii ale vectorului.
 Vom implemeta 4 functii: adunare, rotatie, interschimbare
 si xor, ficare primind ca argumente doi vectori int[4],
 ce reprezinta cele doua numere asupra carora se efectueaza
 operatiile. Vom mai implementa functia operatie, care
 ia ca argumente doi vectori int[4], precum si
 un pointer catre o functie care primeste ca argument
 tot doi vectori int[4] (*func)(int[4], int[4]).
 Am creat un struct functionStruct care are un singur camp, anume
 pointer catre o functie care primeste ca argument doi
 vectori int[4].
 In main am creat un vector de tipul functionStruct, numit vect[4],
 in fiecare pozitie a vectorului aflandu-se pointer catre una din cele
 patru operatii: adunare, interschimbare, rotatie si xor.
 Apoi tot ce trebuie sa facem este sa parcurgem vectorul cu biti
 si sa apelam functia 'operatie', pasand ca argument cele doua
 numere pe 4 biti, sub forma de vectori, precum si pointer catre
 functia corestunzatoare, in functie de bitii de operatie.
 Rezultatul final va fi apoi convertit in decimal si afisat.



 Problema 4 - wordle - timp de lucru - aproximtiv 8 ore

 Mai intai, vom incepe prin a initializa o matrice de tip
 *window[7][7], fiecare element reprezentand una dintre
 casutele in care userul ca inputa caractere de la tastatura.
 Vom mai avea o matrice char pentru cuvinte, care contine toate
 cuvintele posibile care pot fi ghicite, precum si o matrice
 char ce contine optiunile meniului: 'exit' si 'restart'

 Restul programului se va desfasura in interiorul unui
 infinite loop (while (1)), deoarece dorim ca acesta sa aiba
 caracter de continuitate (dorim sa iesim din program doar cand
 selectam optiunea de exit din meniu). Mai intai vom genera
 un numar random intre 0-26, cu ajutorul caruia vom alege
 din matricea char de cuvinte cuvantul ce va trebui sa fie
 ghicit. 

 Dupa ce am selectat cuvantul random, vom curata ecranul
 terminalului dupa care vom 'desena' contururile ferestrei
 principale si a ferestrelor in care inputam caracterele,
 precum si conturul ferestrei in care vom afisa eventualele
 mesaje. 

 Vom avea un for pentru fiecare din cele 6 guessuri pe care
 jucatorul le are la dispozitie. Acest for poate fi intrerupt
 doar daca jucatorul a ghicit cuvantul. Fiecare iteratie
 a acestui for va contine un while in care ne vom ocupa
 de tastele apasate de utilizator. Daca este o litera
 a alfabetului si avem loc unde sa o punem, o vom afisa
 in casuta corespunzatoare, in vectorul guess[] salvand incercarea
 userului de a ghici cuvantul cautat. 
 
 La apasarea tastei backspace vom sterge caracterul din casuta
 anterioara si ne vom muta cu o casuta mai in spate.
 
 La apasarea tastei enter vom verifica daca au fost introduse exact 5
 caractere (daca userul va incerca sa introduca mai mult de 5 caractere,
 inputurile ulterioare de litere vor fi ignorate). In cazul in care au fost
 introduse 5 caractere, vom apela functia check() care ne va indica
 cum trebuie colorata fiecare litera din cuvantul respectiv,
 dupa care se va iesi din while-loopul in care ne aflam.
 In cazul in care au fost introduse mai putin de 5 caractere,
 se va afisa un mesaj sugestiv pentru a l atentiona pe utilizator.

 Functia check primeste ca argumente doi vectori char[6], anume
 incercarea utilizatorului precum si cuvantul ce trebuie ghicit.
 Functia check va returna in numar int de 5 cifre ce este format din cifrele
 1, 2 si 3. Cifra 1 simbolizeaza verdele, 2 simbolizeaza galben, iar 3
 simbolizeaza negru. De exemplu, numarul 12233 returnat de functia
 de check indica faptul ca prima casuta a cuvantului trebuie colorata
 verde, urmatoarele doua galben, iar ultimele doua negru.

 La apasarea tastei ':' (care face sa nu mai intram in while loopul
 care se ocupa de inputurile userului), sau la terminarea forului destinat
 celor 6 guessuri ale userului, vom avea nevoie de meniu (am iesit din for
 loop fie pentru ca acesta s a terminat - win sau lose -, fie pentru ca
 am apasat tasta ':') care sa ii permita userului sa inceapa un joc nou
 sau sa iasa din aplicatie.
 Daca userul doreste sa inceapa un joc nou, vom curata terminalul,
 dupa care infinite loop-ul (while(1)) va lua totul de la capat,
 incepand cu refreshul ferestrelor, generarea unui numar random
 pentru a alege un cuvant din lista si asa mai departe.
 Daca userul doreste sa iasa din program, vom apela functia exit()
 cu care vom iesi din program si vom reveni la terminalul normal.

