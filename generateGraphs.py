import matplotlib.pyplot as plt

import csv

graph1_x = []
graph1_y = []


xplane= ["Cache Size", "Block Size", "Associativity"]
for l in range(2):
	level = "level"+str(l)
	for i in range(3):
		#GRAPH 1
		graph_x = []
		graph_y = []

		fileName = level+'/graph'+str(i+1)+'data.csv'
		with open(fileName) as f:
			reader = csv.reader(f)
			data = list(reader)
		for j in range(len(data)):
			graph_x.append(data[j][0])
			graph_y.append(data[j][1])
		
		plt.title(level + ": Graph " + str(i+1))
		plt.plot(graph_x, graph_y, label="Level 0")
		plt.xlabel(xplane[i])
		plt.ylabel('Miss Rate')
		plt.legend()
		plt.show()

		saveName = level+"_graph"+str(i) +".png"
		plt.savefig("graphs/" + saveName)

		graph_x.clear()
		graph_y.clear()




