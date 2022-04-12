import numpy as np
from matplotlib import pyplot as plt

plt.rc('font', family='Times New Roman', size=30)

def draw_line_chart():
	
	fig = plt.figure(figsize=(8,4.8))

	ax = fig.add_subplot(1,1,1)

	x1 = [1,2,3,4,5,6]	
	y1 = [101573.090, 30036.553, 21111.076, 12589.908, 4126.646, 2930.057]
	y2 = [68135.964, 17248.956, 8685.075, 4397.200, 2357.859, 1858.818]
	for num in range (0,len(y1)):
		y1[num]=425509.659/y1[num]
	for num in range (0,len(y2)):
		y2[num]=425509.659/y2[num]
	plt.plot(x1,y1,'*-',alpha=0.8,color='darkviolet',linewidth=1,label='MPICH')
	plt.plot(x1,y2,'x-',alpha=0.8,color='chocolate',linewidth=2,label='COFFEE-MPI')
	
	plt.ylim(0,240)
	plt.xlim(0.6,6.4)
	ax.tick_params(left=False, bottom=False)
	plt.xticks(x1, ['16','32','64','128','256','512'])
	plt.xlabel("Number of processors")
	plt.ylabel("Speedup")

	# plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='x',alpha=0.4)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	plt.legend(ncol=4,fontsize=22)
	
	plt.show()
		
draw_line_chart()