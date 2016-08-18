#----------------------
#graph
#(c) H.Buchmann FHNW 2015
#----------------------
import collections

class Node:
	def _adjList(self):
		pass

	def _name(self):
		pass

	def _nodecolor(self):
		return None
	
class Graph:
	def bfs(anchor):		#TODO use yield
		done=set()
		queue=collections.deque(anchor)
		while queue:
			n=queue.popleft()
			if n in done:continue
			done.add(n)
			queue.extend(n._adjList())
		return done
				
class Graphviz:
	def quote(s):
		return '"'+s+'"'
		
	def __init__(self,lst,default_nodecolor='none'):
		print(	
'''
digraph module {
  node[fontname="luxisri",
  shape=rectangle,
  color='''+default_nodecolor+'''
  style=filled]
''')
		for n in lst:
			col= n._nodecolor()
			if col:
				print(Graphviz.quote(n._name())+'[color='+col+']')
		for n in lst:
			print(Graphviz.quote(n._name())+'->{',end='')
			for nn in n._adjList():
				print('"'+nn._name()+'";',end='')
			print('}')
		print('}')			
