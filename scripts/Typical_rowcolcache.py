import numpy as np
from matplotlib import pyplot as plt

plt.rc('font', family='Times New Roman', size=30)

def autolabel(rects,Num=1,rotation1=60,NN=1):
	for rect in rects:
		height = rect.get_height()
		plt.text(rect.get_x()-0.04+rect.get_width()/2., Num*height, '%s' % float(height*NN),rotation=rotation1)

def draw_Histogram():
	fig = plt.figure(figsize=(16,6))

	bx = fig.add_subplot(1,1,1)
	x  = [1,2,3,4,5,6,7,8]
	Y1 = [0.8,0.8,0.8,1.2,1.2,1.2,1.2,1.2]
	Y2 = [0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8]
	Y3 = [0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2]
	Y4 = [5.5,6.4,6.3,6.6,6.4,6.5,6.5,6.6]
	Y5 = [0.7,0.8,0.8,0.8,0.8,0.8,0.8,2.1]
	Y6 = [0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.6]
	index = np.arange(8)+1  
	bar_width = 0.1
	opacity = 1.0
	rec1 = plt.bar(index-bar_width*2.5,Y1,bar_width,alpha=opacity,facecolor = 'forestgreen',edgecolor = 'white',label='Row-L1')
	rec2 = plt.bar(index-bar_width*1.5,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='Row-L2')
	rec3 = plt.bar(index-bar_width*0.5,Y3,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='Row-L3')
	rec4 = plt.bar(index+bar_width*0.5,Y4,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='Column-L1')
	rec5 = plt.bar(index+bar_width*1.5,Y5,bar_width,alpha=opacity,facecolor = 'grey',edgecolor = 'white',label='Column-L2')
	rec6 = plt.bar(index+bar_width*2.5,Y6,bar_width,alpha=opacity,facecolor = 'red',edgecolor = 'white',label='Column-L3')
	plt.ylim(0,7)
	plt.xticks(x ,['2000','4000','6000','8000','10000','12000','14000','16000'],rotation=60,fontsize=26) 
	bx.tick_params(left=False, bottom=False)
	plt.xlabel('M=N')   
	plt.ylabel('Miss Rate (%)')
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	
	lines, labels = fig.axes[-1].get_legend_handles_labels()
	fig.legend(lines, labels, loc = 'upper center', ncol = 3, fontsize=26)
	plt.show() 

draw_Histogram()