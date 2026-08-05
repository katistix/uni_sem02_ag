#import "@preview/fletcher:0.5.1" as fletcher: diagram, node, edge

#set page(margin: 1.5cm)
#set text(font: "New Computer Modern", size: 11pt)

= Algoritmica grafurilor
== Examen colocviu -- Semestrul II, 2024-2025

*Timp de lucru: 70 minute*

#line(length: 100%)

+ *(10 puncte)* Care sunt valorile atributelor $d$ și $pi$ ce rezultă din rularea algoritmului $B F S$ pe graful de mai jos, vârful 3 este vârful sursă (de pornire).

  #align(center)[
    #diagram(
      node-stroke: 1pt,
      edge-stroke: 1pt,
      node((0,0), [7], shape: circle),
      node((1,0), [6], shape: circle),
      node((2,0), [2], shape: circle),
      node((3,0.5), [3], shape: circle),
      node((0,1), [5], shape: circle),
      node((1,1), [4], shape: circle),
      node((2,1), [1], shape: circle),
      edge((0,0), (1,0)),
      edge((0,0), (0,1)),
      edge((0,0), (1,1)),
      edge((1,0), (1,1)),
      edge((1,0), (2,0)),
      edge((2,0), (3,0.5)),
      edge((2,0), (2,1)),
      edge((2,0), (1,1)),
      edge((0,1), (1,1)),
      edge((1,1), (2,1))
    )
  ]

+ *(10 puncte)* Fie $G = (V, E)$, graful de mai jos. Care sunt valorile atributelor $d$ și $f$ ale vârfurilor grafului $G$ dacă algoritmul $D F S$ este rulat pe graf. Presupuneți că bucla _for_ din procedura $D F S$ prelucrează vârfurile în ordine alfabetică și listele de adiacență sunt ordonate alfabetic după eticheta vârfurilor. Dați și lista de adiacență a grafului.

  #align(center)[
    #diagram(
      node-stroke: 1pt,
      edge-stroke: 1pt,
      node((0,0), [d], shape: circle),
      node((0,1), [c], shape: circle),
      node((0,2), [g], shape: circle),
      node((1,1), [a], shape: circle),
      node((2,0), [e], shape: circle),
      node((2,1), [h], shape: circle),
      node((2,2), [f], shape: circle),
      node((3,1), [b], shape: circle),
      node((4,0.5), [i], shape: circle),
      node((4,1.5), [l], shape: circle),
      node((5,1), [j], shape: circle),
      node((6,0.5), [k], shape: circle),
      node((6,1.5), [m], shape: circle),
      edge((0,0), (1,1)),
      edge((0,1), (1,1)),
      edge((0,2), (1,1)),
      edge((0,0), (2,0)),
      edge((0,2), (2,2)),
      edge((1,1), (2,0)),
      edge((1,1), (2,1)),
      edge((1,1), (2,2)),
      edge((2,1), (3,1)),
      edge((2,0), (3,1)),
      edge((2,2), (3,1)),
      edge((3,1), (4,0.5)),
      edge((3,1), (4,1.5)),
      edge((4,0.5), (5,1)),
      edge((4,1.5), (5,1)),
      edge((4,0.5), (4,1.5)),
      edge((5,1), (6,0.5)),
      edge((5,1), (6,1.5)),
      edge((6,0.5), (6,1.5))
    )
  ]

+ *(10 puncte)* Fie graful $G = (V, E)$ simplu și neorientat de mai jos. Trebuie adăugate muchii astfel încât ciclul eulerian să aibă lungimea minimă? Dacă da, care? Justificați.

  #align(center)[
    #diagram(
      node-stroke: 1pt,
      edge-stroke: 1pt,
      node((0,2), [A], shape: circle),
      node((1,1), [B], shape: circle),
      node((2,0), [E], shape: circle),
      node((3,1), [F], shape: circle),
      node((4,2), [H], shape: circle),
      node((3,3), [G], shape: circle),
      node((1,3), [C], shape: circle),
      node((2,2), [D], shape: circle),
      edge((0,2), (1,1), [5]),
      edge((1,1), (2,0), [1]),
      edge((2,0), (3,1), [7]),
      edge((3,1), (4,2), [9]),
      edge((4,2), (3,3), [8]),
      edge((3,3), (1,3), [4]),
      edge((1,3), (0,2), [1]),
      edge((2,2), (0,2), [12]),
      edge((2,2), (1,1), [3]),
      edge((2,2), (2,0), [2]),
      edge((2,2), (4,2), [3]),
      edge((2,2), (1,3), [10])
    )
  ]

+ *(15 puncte)* Ce întoarce algoritmul Bellman-Ford dacă este rulat pe următorul graf? Luați ca sursă vârful $f$. Arătați pașii efectuați de algoritm și valorile atributelor $d$ și $pi$. Explicați.

  #align(center)[
    #diagram(
      node-stroke: 1pt,
      edge-stroke: 1pt,
      node((0,2), [s], shape: circle),
      node((1,1), [a], shape: circle),
      node((1,2), [b], shape: circle),
      node((1,3), [c], shape: circle),
      node((2,1), [e], shape: circle),
      node((2,3), [d], shape: circle),
      node((3,0.5), [f], shape: circle),
      node((3,2), [g], shape: circle),
      node((3,3.5), [h], shape: circle),
      edge((0,2), (1,1), [4], "->"),
      edge((0,2), (1,2), [4], "->"),
      edge((0,2), (1,3), [3], "->"),
      edge((1,2), (1,1), [-2], "->"),
      edge((1,3), (1,2), [2], "->"),
      edge((1,3), (2,3), [1], "->"),
      edge((1,2), (2,3), [4], "->"),
      edge((1,1), (2,1), [3], "->"),
      edge((2,3), (2,1), [-3], "->"),
      edge((2,1), (3,0.5), [2], "->"),
      edge((3,0.5), (2,3), [2], "->"),
      edge((2,3), (3,2), [7], "->"),
      edge((3,2), (3,3.5), [-2], "->"),
      edge((3,3.5), (1,3), [10], "->")
    )
  ]

+ *(15 puncte)* Care sunt valorile atributelor $v.d$ și $pi$ dacă este rulat algoritmul lui Dijkstra pe următorul graf? Arătați cum se modifică $S$. Luați ca sursă vârful $c$. Explicați.

  #align(center)[
    #diagram(
      node-stroke: 1pt,
      edge-stroke: 1pt,
      node((0,2), [s], shape: circle),
      node((1,1), [a], shape: circle),
      node((1,3), [c], shape: circle),
      node((2,2), [d], shape: circle),
      node((3,1), [b], shape: circle),
      node((3,3), [e], shape: circle),
      node((4,1), [f], shape: circle),
      node((4,3), [g], shape: circle),
      node((5,2), [t], shape: circle),
      edge((0,2), (1,1), [4], "->"),
      edge((0,2), (1,3), [4], "->"),
      edge((1,1), (3,1), [8], "->"),
      edge((1,1), (2,2), [2], "->"),
      edge((1,3), (2,2), [7], "->"),
      edge((1,3), (3,3), [1], "->"),
      edge((2,2), (3,1), [1], "->"),
      edge((2,2), (3,3), [6], "->"),
      edge((2,2), (4,1), [4], "->"),
      edge((2,2), (5,2), [14], "->"),
      edge((3,1), (4,1), [7], "->"),
      edge((3,3), (4,3), [2], "->"),
      edge((4,1), (5,2), [9], "->"),
      edge((4,3), (5,2), [10], "->")
    )
  ]

+ *(15 puncte)* Care sunt valorile atributelor $k e y$ și $pi$ dacă este rulat algoritmul lui Prim pe următorul graf? Luați ca și sursă vârful 1. Explicați.

  #align(center)[
    #diagram(
      node-stroke: 1pt,
      edge-stroke: 1pt,
      node((0,1), [1], shape: circle),
      node((1,0), [2], shape: circle),
      node((1,2), [4], shape: circle),
      node((2,0), [3], shape: circle),
      node((2,2), [5], shape: circle),
      node((3,0), [6], shape: circle),
      node((3,2), [7], shape: circle),
      edge((0,1), (1,0), [1]),
      edge((0,1), (1,2), [4]),
      edge((1,0), (2,0), [2]),
      edge((1,0), (1,2), [6]),
      edge((1,0), (2,2), [4]),
      edge((2,0), (2,2), [5]),
      edge((2,0), (3,0), [6]),
      edge((2,0), (3,2), [8]),
      edge((1,2), (3,2), [4], bend: 30deg),
      edge((2,2), (3,2), [7]),
      edge((3,0), (3,2), [30], bend: -30deg)
    )
  ]

+ *(15 puncte)* Determinați fluxul maxim în rețeaua de transport $G$ de mai jos. Explicați.

  #align(center)[
    #diagram(
      node-stroke: 1pt,
      edge-stroke: 1pt,
      node((0,1), [s], shape: circle),
      node((1,0), [a], shape: circle),
      node((1,2), [c], shape: circle),
      node((2,0), [b], shape: circle),
      node((2,2), [d], shape: circle),
      node((3,1), [t], shape: circle),
      edge((0,1), (1,0), [9], "->"),
      edge((0,1), (1,2), [6], "->"),
      edge((1,0), (2,0), [7], "->"),
      edge((1,0), (2,2), [4], "->"),
      edge((1,2), (2,0), [6], "->"),
      edge((1,2), (2,2), [4], "->"),
      edge((2,0), (3,1), [5], "->"),
      edge((2,2), (3,1), [10], "->")
    )
  ]

+ *(10 puncte)* Desenați un graf pentru care algoritmul lui Ford-Fulkerson găsește fluxul maxim în cel mai rău caz în maxim 35 de pași.

+ *(10 puncte)* Vârfurile unui graf neorientat $G = (V, E)$ sunt numerotate de la $1, 2, ..., 2222$. Muchia $(i, j)$ există dacă $|i - j| <= 3$, unde $i != j$. Care din următoarele afirmații sunt adevărate:
  - #sym.square.empty $G$ este Hamiltonian.
  - #sym.square.empty $G$ conține un cuplaj perfect.
  - #sym.square.empty $G$ conține un ciclu Eulerian.

+ *(15 puncte)* Matricea de incidență a unui graf orientat $G = (V, E)$ fără bucle este o matrice $|V| times |E|$, unde $B = (b_{i j})$ astfel încât
  $ b_{i j} = cases(
    -1 "arcul" j "pleacă din" i,
    1 "arcul" j "intră în vârful" i,
    0 "în rest."
  ) $
  Ce reprezintă elementele matricii $B \cdot B^T$ ($B^T$ este transpusa matricii $B$)?

+ *(15 puncte)* Cu ce valori se vor repondera muchiile grafului de mai jos dacă se vrea determinarea drumului de cost minim între toate perechile de vârfuri cu algoritmul $Johnson$?

  #align(center)[
    #diagram(
      node-stroke: 1pt,
      edge-stroke: 1pt,
      node((0,0), [1], shape: circle),
      node((1,0), [4], shape: circle),
      node((0,1), [2], shape: circle),
      node((1,1), [3], shape: circle),
      edge((0,0), (0,1), [-3], "->"),
      edge((0,0), (1,1), [-1], "->"),
      edge((1,1), (0,1), [-2], "->"),
      edge((1,0), (1,1), "->")
    )
  ]

+ *(15 puncte)* Este adevărat că un cuplaj $M$ al unui graf $G$ este maxim dacă și numai dacă $G$ nu conține $M$-lanțuri de creștere? Justificați.

+ *(15 puncte)* Fie $G = (V, E)$ graful constrângerilor ($G$ nu conține circuite de pondere negativă). Cum se poate rezolva sistemul de constrângeri cu ajutorul algoritmului de drum minim Bellman-Ford fără a adăuga vârful suplimentar $v_0$? Trebuie modificat algoritmul Bellman-Ford? (Soluția unui sistem de constrângeri poate fi găsită ca și drumul de pondere minimă din graful de constrângeri.)

+ *(10 puncte)* Fie $K_{5,2}$ un graf simplu și neorientat. Graful conține (bifați răspunsul/răspunsurile corect/corecte):
  - #sym.square.empty un lanț Eulerian.
  - #sym.square.empty un cuplaj perfect.
  - #sym.square.empty un ciclu Eulerian.
  - #sym.square.empty un ciclu Hamiltonian.
  - #sym.square.empty nici un raspuns de mai sus.

+ *(20 puncte)* Fie graful $G = (V, E)$ bipartit și ponderat de mai jos și $M = {(X_2, Y_2), (X_1, Y_1)}$ un cuplaj inițial. Găsiți cuplajul de pondere maximă pentru acest graf. Explicați pașii algoritmului și detaliați rezolvarea.

  #align(center)[
    #diagram(
      node-stroke: 1pt,
      edge-stroke: 1pt,
      node((0,0), [$Y_1$], shape: circle),
      node((1,0), [$Y_2$], shape: circle),
      node((2,0), [$Y_3$], shape: circle),
      node((0,1), [$X_1$], shape: circle),
      node((1,1), [$X_2$], shape: circle),
      node((2,1), [$X_3$], shape: circle),
      edge((0,1), (0,0), [1]),
      edge((0,1), (1,0), [4]),
      edge((1,1), (0,0), [3]),
      edge((1,1), (1,0), [8]),
      edge((2,1), (1,0), [6]),
      edge((2,1), (2,0), [1])
    )
  ]
