#!/usr/bin/python3
#-------------------
#eary-init.py
#(c) H.Buchmann FHNW 2015
#-------------------
import sys
import re
import graph
import collections

class Symbol:
	list={}	#name module
	
class Module(graph.Node):
	GlobalConstructor=re.compile('_GLOBAL__(sub_)?I_\\S+')
	GlobalDestructor =re.compile('_GLOBAL__(sub_)?D_\\S+')
	list=collections.OrderedDict()
	init=[]
	gConstructorC=0
	gDestructorC=0
	def __init__(self,name):
		self.name=name
		self.use=set()
		self.references=set() 
		self.undefined=set()
		self.gConstructorI=-1     # gConstructorI>=0 position in elf file init_array
		self.gDestructorI=-1      # gDestructorI >=0 position in elf file fini_array
		self.visited=False
		self.onStack=False # for circular import
		Module.list[name]=self

	def _name(self):
		if (self.gConstructorI>=0) or (self.gDestructorI>=0):
			return self.name+'(C'+str(self.gConstructorI)+',D'+str(self.gDestructorI)+')'
		return self.name

	def _adjList(self):
		return self.use

	def _nodecolor(self):
		if self.gindex>=0:return 'red'

	def show():
		for m in Module.list.values():
			print(m._name())
			for mm in m.use:
				print('\t',mm._name())
			for sym in m.undefined:
				print('\t?',sym)

	def symbol(self,typ,name):
		if Module.GlobalConstructor.match(name):
			self.gConstructorI=Module.gConstructorC
			Module.gConstructorC+=1
		if Module.GlobalDestructor.match(name):
			self.gDestructorI=Module.gDestructorC
			Module.gDestructorC+=1
		if typ.isupper():
			Symbol.list[name]=self
		
	def resolve(self):
		for sym in self.references:
			mm=Symbol.list.get(sym)
			if mm:
				self.use.add(mm)
			else:
				self.undefined.add(sym)

	def tsort(self):
		if self.onStack:
			print('circular import',file=sys.stderr)
			sys.exit(1)	
		if self.visited:
			return
		self.visited=True
		self.onStack=True
		for m in self.use:
			m.tsort()
		self.onStack=False
		if (self.gConstructorI>=0) or (self.gDestructorI>=0):
			Module.init.append(self)
		
class Reader:
	def empty(self,l):
		if not l=='\n':
			print('***error line:',self.lineN,' :empty line expected',file=sys.stderr)
			exit(1)
		self.status=self.file

	def file(self,l):
		self.m=Module(l[0:l.rindex('.')])
		self.status=self.symbol
	
	def symbol(self,l):
		if l=='\n':
			self.status=self.file
			return
		sym=l.split()
		l=len(sym)
		if l==3:              #defined: addr type name
			self.m.symbol(sym[1],sym[2])
		elif l==2:            #undefined:   U name
			self.m.references.add(sym[1])
		else:
			print('***error line:',self.lineN,l,'is not a symbol')
			exit(1)

	def __init__(self):
		self.status=None
		self.lineN=1
		self.m=None
		self.status=self.empty
		for l in sys.stdin:
			self.status(l)
			self.lineN+=1

class Initializer:
	def __resolve():
		for m in Module.list.values():
			m.resolve()

	def __tsort():	# topological sort
		for m in Module.list.values():
			m.tsort()


	def graph():
		graph.Graphviz(Module.init,default_nodecolor='grey')

	def initlist():
		print('extern const sys::Mod::Entry __InitSequence[]={')
		for m in Module.init:
			print('{%3d'%m.gConstructorI+',%3d'%m.gDestructorI+',"'+str(m.name)+'"},')		
		print('{  0,  0, 0}};')

	def usage():
		print('usage: ',sys.argv[0],'init|graph'
	"""
	input from stdin
	output to stdout""",file=sys.stdout)

	def __init__(self):
		Reader()
		Initializer.__resolve()
#		Module.show()
		Initializer.__tsort()
		sys.argv.append('') # for index [1]
		{
		 'init':Initializer.initlist,
		 'graph':Initializer.graph
		}.get(sys.argv[1],Initializer.usage)()

Initializer()

