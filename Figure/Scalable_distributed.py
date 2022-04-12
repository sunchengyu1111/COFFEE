import numpy as np
from matplotlib import pyplot as plt

plt.rc('font', family='Times New Roman', size=30)

def draw_line_chart():
	
	fig = plt.figure(figsize=(8,4.8))

	bx = fig.add_subplot(1,1,1)
	x1 = [1,2,3,4,5,6]
	
	y1 = [85509.572,30773.354, 25043.880, 14446.166, 9351.966, 8394.228]
	y2 = [39355.064,18364.434, 10055.625, 8031.260, 5430.560, 3544.579]
	for num in range (0,len(y1)):
		y1[num]=425509.659/y1[num]
	for num in range (0,len(y2)):
		y2[num]=425509.659/y2[num]
	plt.plot(x1,y1,'*-',alpha=0.8,color='darkviolet',linewidth=1,label='MPICH')
	plt.plot(x1,y2,'x-',alpha=0.8,color='chocolate',linewidth=2,label='COFFEE-MPI')
	
	plt.ylim(0,125)
	plt.xlim(0.6,6.4)
	bx.tick_params(left=False, bottom=False)
	plt.xticks(x1, ['16','32','64','128','256','512'])
	plt.xlabel("Number of processors")
	plt.ylabel("Speedup")

	# plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='x',alpha=0.4)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	plt.legend(ncol=4,fontsize=22)
	
	plt.show()
	
draw_line_chart()