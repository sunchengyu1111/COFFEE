import numpy as np
from matplotlib import pyplot as plt

plt.rc('font', family='Times New Roman', size=30)

def draw_line_chart():
	
	fig = plt.figure(figsize=(16,6))
	
	ax = fig.add_subplot(1,1,1)
	x = [1,2,3,4,5,6,7,8,9,10]
	y1 = [1336.668,1390.35,1424.808,1440.944,1460.896,1419.264,1436.288,1370.592,1366.016,1349.664]
	for num in range (0,len(y1)):
		y1[num]=1336.668/y1[num]
	y2 = [10107.050,6061.797,3060.433,2156.773,1408.437,674.577,244.983,131.507,61.725,51.289]
	for num in range (0,len(y2)):
		y2[num]=10107.050/y2[num]/pow(2,num)
	plt.plot(x,y1,'*-',alpha=0.8,color='darkviolet',linewidth=1,label='Row rescaling')
	plt.plot(x,y2,'x-',alpha=0.8,color='chocolate',linewidth=2,label='Column rescaling')
	
	plt.ylim(0.36,1.0)
	plt.xlim(0.6,10.4)
	ax.tick_params(left=False, bottom=False,pad=0.5)
	plt.xticks(x, [ '1', '2', '4', '8', '16', '32', '64', '128', '256', '512'])
	plt.xlabel("Number of processors",fontsize=30)
	plt.ylabel("Parallel efficiency",fontsize=30)
	# plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='x',alpha=0.4)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)

	lines, labels = fig.axes[-1].get_legend_handles_labels()
	fig.legend(lines, labels, loc = 'upper center', ncol = 6, fontsize=30)
	
	plt.show()
	
draw_line_chart()