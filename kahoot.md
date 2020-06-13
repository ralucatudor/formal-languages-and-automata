# Kahoot
#### Curs 9
- Expresiile regulate au in componenta operatiile reuniune, concatenare si stelare.

- Orice Expresie Regulata se poate transforma intr-un DFA.

- Teorema lui Kleene descrie cum se poate construi o ER dintr-un DFA (un DFA se poate transforma in REGEX prin teorema lui Kleene) (Atentie! Se poate construi un DFA dintr-o ER prin definitie)\
_'For any Regular Expression r that represents Language L(r), there is a Finite Automata that accepts same language.'_

- Substitutia este o functie care duce cuvinte in limbaje. (functie care duce cuvinte in cuvinte - este morfism, nu substitutie)

- Morfism este o functie definita pe SIGMA* cu valori in SIGMA* unde m(xy)=m(x)m(y) si m(lambda)=lambda.

- Teorema lui Kleene: Rij k este multimea cuvintelor care pleaca din starea i si ajung in starea j si folosesc stari de rang <= k.


#### Curs 10

- Daca L1, L2 si L3 au proprietatea ca L1 intersectat cu complement(L2) = L3 si L2, L3 apartin REG, atunci...
R: Nu se stie, L1 apartine/ nu apartine REG 

-> intrebare Examen 2019

Contraexemplu: L3 = multimea vida, L2 = toate cuvintele din limbajul peste {a, b} => complement(L2) = multimea vida si L1 = clasicul {a^n b^n}.

- Daca L1, L2 si L3 au proprietatea ca L1 - L2 = L3 si L2, L3 apartin REG, atunci...
R: Nu se stie, L1 apartine/ nu apartine REG 

-> intrebare Examen 2019

Contraexemplu: L2 foarte mare, sa zicem toate cuvintele din limbajul a, b - {a, b}* - automat Mickey Mouse (o unica stare, initiala, care este si finala, in care merg si cu a si cu b), a.i. L1 - L2 = multimea vida (L3 procesat de o stare finala si atat). L1 de ex a^p, p prim - nu este regulat

- Pentru limbajul L={a, b} si considerand echivalenta pe cuvinte modulo L...\ 
R: avem relatia a echivalent modulo L b.

- Fie A un DFA, consideram echivalenta pe stari (A)...
R: o stare finala din A nu poate fi echivalenta cu o alta stare nefinala din A 
(Cum verific echivalenta pe stari/ daca 2 stari sunt echivalente? Vad ce limbaj imi da prima stare (drept stare initiala), la fel pt a doua - o pun drept stare initiala si vad ce limbaj imi da respectivul automat. Daca limbajele sunt egale, atunci starile sunt echivalente, daca nu, nu. Definitia formala este cea cu stari finale si nefinale - verific cu lambda)

- Minimizarea automatelor in general se face in timp O(N log N), la curs am vazut un algoritm O(N^2).

- Minimizarea DFA pentru limbaje finite (!!atentie ca are o implicatie pe structura grafului) se face in timp liniar O(N).

- Acceptarea in PDA se face... 
R: sunt 3 acceptari: stare finala(a), stiva vida(b), (a) + (b)

- Un PDA este determinist daca delta(q, a, X) are un SINGUR element (sau niciunul) pentru orice q, orice a (litera sau lambda), orice X din 'ro'

- Este decidabil daca o Expresie Regulata cu cel putin 20 de operatori si un DFA cu 20 de stari sunt echivalente? 
R: da, prin transformarea la automate si verificarea daca sunt egale.

(Echivalenta inseamna daca au sau nu limbajele modelate egale!)

- PDA: limbajele modelate de PDA sunt...
R: inchise la reuniune! (NU LA INTERSECTIE! ATENTIE! SUNT INCHISE LA INTERSECTIE CU LIMBAJELE REGULATE)

Cum gandim? Se dau doua PDA, cum fac reuniunea? Se adauga o noua stare - starea aceasta noua cu lambda, Z0 de pe stiva - pune Z0 merge in prima stare initiala din PDA1 , analog merge in PDA2 => reuniunea!
(similar cu reuniunea DFA urilor cu lambda miscari)

- Pentru un PDA avem ca la fiecare tranzitie:
R: se face pop din stiva la un cuvant arbitrar de exact o litera.

- Pentru un PDA avem ca la fiecare tranzitie:
R: se face push in stiva la un cuvant arbitrar inclusiv lambda.

#### Curs 11
- Gramaticile sunt masini generatoare: se da masina si se genereaza toate cuvintele.

- Gramaticile pot avea mai multe simboluri terminale (T) si pot avea doar un simbol de start (S).

- Gramaticile regulate au doar productii liniare la dreapta SAU au doar productii liniare la stanga.

- Gramaticile regulate sunt echivalente cu DFA, NFA...
(Lemma 1 si Lemma 2)

- Gramaticile accepta un cuvant daca se pleaca din S si se rescrie intr-un cuvant format doar din TERMINALE. 

#### Curs 12
- Limbajul {a^n b^n | n > 0} poate fi modelat de gramatici liniare (in care apare cel mult un neterminal in partea dreapta a productiei).

- Se da o gramatica regulata cu nr de neterminale 5. Cate stari va avea automatul lambda-NFA echivalent? Raspuns: 6.

- Se da un NFA cu 7 stari. Cate neterminale va avea gramatica regulata echivalenta? Raspuns: 7.

- Ambiguitate: un cuvant w din G este ambiguu daca: arborii de derivare pentru doua feluri de a genera w sunt distincti.

- Gramatica G este ambigua daca cel putin un cuvant din G este ambiguu.

- Limbajul independent de context L este ambiguu daca toate gramaticile G cu L(G)=L sunt ambigue.

- Eliminarea productiilor vide (empty production) din G se face si se obtine o gramatica G' lambda-echivalenta (Atentie! se poate ca lambda sa nu se poata obtina in limbajul nou, dar sa se poata obtine in limbajul initial).

- Forma normala Chomsky:\
se obtine o gramatica echivalenta cu gramatica de plecare, nu lambda-echivalenta.


#### Curs 14
- Lema de pompare e folositoare pentru a arata ca un limbaj nu e regulat (pentru a arata ca un limbaj nu e acceptat de niciun DFA)

- Lema de pompare se refera la a treia restrictie (cea mai importanta)

