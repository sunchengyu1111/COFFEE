import numpy as np
from matplotlib import pyplot as plt

plt.rc('font', family='Times New Roman', size=16)

def draw_Histogram():
	fig = plt.figure(figsize=(16,3))
	
	ax = fig.add_subplot(1,2,1)
	ax.set_title('AMD')
	x = [1,2,3,4,5,6,7,8]
	y = [1,2,3,4,5,6]
	Y1 = [6.6,6.6,6.6,6.6,6.6,6.6,6.6,6.6]
	Y2 = [0.8,0.8,0.8,0.8,0.8,0.8,0.8,6.5]
	Y3 = [0.2,0.2,0.2,0.2,0.2,0.2,0.2,1.2]
	Y4 = [0.9,1.1,1.1,1.1,1.1,1.1,1.1,1.1]
	Y5 = [0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8]
	Y6 = [0.3,0.3,0.3,0.3,0.3,0.3,0.3,0.3]
	index = np.arange(8)+1  
	bar_width = 0.15
	opacity = 1.0
	rec1 = plt.bar(index-bar_width*2.5,Y1,bar_width,alpha=opacity,facecolor = 'forestgreen',edgecolor = 'white',label='Typical-L1')
	rec2 = plt.bar(index-bar_width*1.5,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='Typical-L2')
	rec3 = plt.bar(index-bar_width*0.5,Y3,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='Typical-L3')
	rec4 = plt.bar(index+bar_width*0.5,Y4,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-CPU-L1')
	rec5 = plt.bar(index+bar_width*1.5,Y5,bar_width,alpha=opacity,facecolor = 'grey',edgecolor = 'white',label='COFFEE-CPU-L2')
	rec6 = plt.bar(index+bar_width*2.5,Y6,bar_width,alpha=opacity,facecolor = 'red',edgecolor = 'white',label='COFFEE-CPU-L3')
	plt.ylim(0,7)
	plt.xticks(x ,['2000','4000','6000','8000','10000','12000','14000','16000'],rotation=60,fontsize=14)
	plt.yticks(y)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	ax.tick_params(left=False, bottom=False)
	plt.xlabel('M=N')  
	plt.ylabel('Miss Rate (%)') 
	
	bx = fig.add_subplot(1,2,2)
	bx.set_title('Intel')
	x = [1,2,3,4,5,6,7,8]
	y = [1,2,3,4,5,6]
	Y1 = [5.5,6.4,6.3,6.6,6.4,6.5,6.5,6.6]
	Y2 = [0.7,0.8,0.8,0.8,0.8,0.8,0.8,2.1]
	Y3 = [0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.6]
	Y4 = [0.8,1.0,1.0,1.0,1.0,1.0,1.0,1.0]
	Y5 = [0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8]
	Y6 = [0.3,0.3,0.3,0.3,0.3,0.3,0.3,0.3]
	index = np.arange(8)+1  
	bar_width = 0.15
	opacity = 1.0
	rec1 = plt.bar(index-bar_width*2.5,Y1,bar_width,alpha=opacity,facecolor = 'forestgreen',edgecolor = 'white',label='Typical-L1')
	rec2 = plt.bar(index-bar_width*1.5,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='Typical-L2')
	rec3 = plt.bar(index-bar_width*0.5,Y3,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='Typical-L3')
	rec4 = plt.bar(index+bar_width*0.5,Y4,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-CPU-L1')
	rec5 = plt.bar(index+bar_width*1.5,Y5,bar_width,alpha=opacity,facecolor = 'grey',edgecolor = 'white',label='COFFEE-CPU-L2')
	rec6 = plt.bar(index+bar_width*2.5,Y6,bar_width,alpha=opacity,facecolor = 'red',edgecolor = 'white',label='COFFEE-CPU-L3')
	plt.ylim(0,7)
	plt.xticks(x ,['2000','4000','6000','8000','10000','12000','14000','16000'],rotation=60,fontsize=14) 
	plt.yticks(y)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	bx.tick_params(left=False, bottom=False)
	plt.xlabel('M=N')  
	
	lines, labels = fig.axes[-1].get_legend_handles_labels()
	fig.legend(lines, labels, loc = 'upper center', ncol = 6)
	plt.show() 

draw_Histogram()