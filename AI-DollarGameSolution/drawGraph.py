import matplotlib.pyplot as plt
import pickle
import random
import time
from graphAutoGenerator import Node

def main():

	graphs = [{}]
	single = {}
	with open("graphs10K-100.pickle","rb") as f:
		try:
			graphs = pickle.load(f)
		except EOFError:
			graphs = []
	f.close()

	graph = graphs[5]

	while True:
		try:
			draw(graph)
			graph[random.randint(0,len(graph)-1)].pushOnEdge()
			graph[random.randint(0,len(graph)-1)].pullOnEdge()
		except KeyboardInterrupt:
			return 1

def draw(graph):

	plt.clf()
	x = []
	y = []
	for n in graph.values():
		x.append(n.getNodeID())
		y.append(n.getVal())

	plt.plot(x,y,marker='o')

	for n in graph.values():
		for c in n.getEdges():
			plt.plot([n.getNodeID(),c.getNodeID()],[n.getVal(),c.getVal()])

	plt.axhline(0,color="red")
	plt.draw()
	plt.pause(0.001)
if __name__ == "__main__":
	main()
