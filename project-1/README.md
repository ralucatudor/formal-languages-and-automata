#  Project no. 1



- NFA (Nondeterministic Finite Automaton) - and implicitly DFA (Deterministic Finite Automaton) - Membership;\
 See [NFA](https://infoarena.ro/problema/nfa) on infoarena (my submission can be found [here](https://infoarena.ro/job_detail/2590331))
- Generating the shortest 100 words accepted by an automaton.

<img align="right" src="draw-finite-state-machine/automaton.gv.png">

### Example
As seen in input.txt and output.txt...\
For the automaton in the image, we have:\
string "aabbaaabaa" -> is accepted\
string "aabbaaabaabbbbbbbbb" -> is not accepted

and the first 100 generated words are:\
ab\
ba\
aaab\
aaba\
abaa\
abbb\
...\
bbbbaaba\
bbbbabaa\
bbbbabbb\
bbbbbaaa\
bbbbbabb\
bbbbbbab\
bbbbbbba

Note! I was able to plot this finite state machine automatically (see [source code](draw-finite-state-machine/app.py)) in **Python**. I used ***Graphviz*** - installed the Graphviz package and then added its `bin/` subdirectory containing the layout commands for rendering graph descriptions (dot, circo, neato, etc.) in my systems’ path.\
My Python file generated a graph description in the DOT language. I used the render()-method to save the source code and render it with the default layout program (dot) => resulting (in my case) the above PNG file.
