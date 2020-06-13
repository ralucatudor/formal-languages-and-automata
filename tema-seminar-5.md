##### Prerequisites:
    Limbajele regulate sunt inchise la:
        - substitutii regulate
        - morfisme
        - morfisme inverse
        - la intersectie (practic intersectie de automate)

##### CERINTA
Spuneți dacă limbajul următor este sau nu regulat. 
Dacă limbajul este regulat construiți un automat finit
 determinist care sa ıl accepte, dacă nu, demonstrati 
 folosind lema de pompare pentru REG că limbajul nu
  este regulat L = {a^k w c (wR) | w ∈ {a, b, c} ∗ , k ≥ 2} 

  aaaaa bbcbbbcb c bcbbbcbb
  unde R inseamna oglinditul cuvantului: abcaaR = aacba. 
  ALTERNATIV pentru max 5 puncte: L = {a^k−1 b^2l+3 | k, l ≥ 5}.

---

L = { aa+ w c (wR) }

L = { aaaaaaa abcabc  c  cbacba }

Presupunem prin absurd ca L este un limbaj regulat.

fie H substitutia regulata:
    a -> { lambda }
    b -> { b }
    c -> { c }

Notam cu L' H(L). Se observa ca si L' este regulat.
	
L' = { w c (wR) | w={c,b}*}
L' = { {b, c}* c ({b, c}*R) }

Fie X = { b* c b* }, X este REG

----
A, B, limbaje regulate => A intersectie B este regulat
identice? A = B <-> (A ^ ~B) v (B ^ ~A) = {0}


Notam cu P intersectia dintre L' si X
=> P = { b^i c b^i, i natural }, P REG.

Fie F substitutie regulata, in particular morfism:
    a -> {b}
    c -> {cb}
    b -> {b}

F(cc) = cbcb
F-1(cbb) = c{a,b} = {ca, cb}

F(P') = P

Fie P' trecerea lui P prin morfismul invers lui F.
P' = { x^i c y^(i-1), unde i natural; x,y in { a, b }} adica
P' = { {a,b}^i c {a,b}^(i-1), unde i natural}.
P' este si el REG

Ne uitam la P' intersectact cu { a* c b* } si notam cu P''
P'' = { a^i c b^(i-1) }

Q = P'' prin morfismul:
	a -> a
	b -> b
	c -> b
=> Q = { a^i b^i } care nu este REG 
Contradictie