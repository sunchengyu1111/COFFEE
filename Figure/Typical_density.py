import numpy as np
from matplotlib import pyplot as plt
from pylab import *

plt.rc('font', family='Times New Roman', size=30)

def draw_Histogram():
	fig = plt.figure(figsize=(16,4.8))

	ax = fig.add_subplot(1,1,1)
	x = [1,2,3,4,5,6,7,8,9]
	Y1 = [3811.197,3858.541,6267.526,9594.915,11260.502,10966.071,15288.026,20437.867,20946.546]
	Y2 = [3783.681,3888.372,6153.991,9861.159,11525.427,11646.990,15097.878,19559.677,20026.686]
	Y3 = [3770.447,3802.410,5991.559,9357.953,11312.342,10849.521,14838.617,19438.135,19589.814]
	index = np.arange(9)+1  
	bar_width = 0.2
	opacity = 1.0	
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='Dense matrix')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='Medium dense matrix')
	rec3= plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='Sparse matrix')
	
	plt.ylim(0,24000)
	# plt.yscale('symlog')
	plt.xlim(0.6,9.4)
	plt.xticks(x ,['8000','9000','10000','11000','12000','13000','14000','15000','16000'],rotation=60) 
	ax.tick_params(left=False, bottom=False)
	plt.xlabel('M=N')  
	plt.ylabel('Time (ms)')  
	
	# plt.suptitle('Title')
	lines, labels = fig.axes[-1].get_legend_handles_labels()
	fig.legend(lines, labels, loc = 'upper center', ncol = 3)
	plt.show()

draw_Histogram()