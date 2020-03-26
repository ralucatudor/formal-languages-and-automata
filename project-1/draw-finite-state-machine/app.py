from graphviz import Digraph

g = Digraph('G', filename='automaton.gv', format='png', engine='dot')

g.node('qi', shape='point')
g.node('1', '1', shape='circle')
g.node('2', '2', shape='circle')
g.node('3', '3', shape='doublecircle')
g.node('4', '4', shape='circle')

g.edge('qi', '1')

g.edge('1', '2', label='a')
g.edge('2', '1', label='a')

g.edge('2', '3', label='b')
g.edge('3', '2', label='b')

g.edge('3', '4', label='a')
g.edge('4', '3', label='a')

g.edge('1', '4', label='b')
g.edge('4', '1', label='b')

g.render('automaton.gv', view=True)
