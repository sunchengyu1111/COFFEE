import numpy as np
from matplotlib import pyplot as plt
from pylab import *

plt.rc('font', family='Times New Roman', size=30)

def autolabel(rects,Num=1,rotation1=60,NN=1):
	for rect in rects:
		height = rect.get_height()
		plt.text(rect.get_x()-0.04+rect.get_width()/2., Num*height, '%s' % float(height*NN),rotation=rotation1)

def draw_Histogram():
	fig = plt.figure(figsize=(16,6))
	
	ax = fig.add_subplot(1,3,1)
	ax.set_title('AMD R7')
	x = [1,2,3,4,5]
	y = [5,10,15,20]
	Y1 = [7.422/7.422,33.235/33.235,212.702/212.702,2135.594/2135.594,13854.362/13854.362,]
	Y2 = [7.422/5.982,33.235/25.150,212.702/95.978,2135.594/382.823,13854.362/1532.151,]
	Y3 = [7.422/4.758,33.235/20.033, 212.702/81.556,2135.594/318.214,13854.362/1299.539,]
	Y4 = [7.422/1.965,33.235/8.085,212.702/33.182,2135.594/132.788,13854.362/539.216,]
	index = np.arange(5)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width*1.5,Y1,bar_width,alpha=opacity,facecolor = 'forestgreen',edgecolor = 'white',label='Typical')
	rec2 = plt.bar(index-bar_width*0.5,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='+COFFEE-C2R optimization')
	rec3 = plt.bar(index+bar_width*0.5,Y3,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='+Blocking optimization')
	rec4 = plt.bar(index+bar_width*1.5,Y4,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='+Micro-kernel optimization')	
	plt.xlim(0.6,5.4)
	plt.ylim(0,26)
	plt.xticks(x ,['1000','2000','4000','8000','16000'],rotation=60) 
	plt.yticks(y)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	ax.tick_params(left=False, bottom=False)
	plt.xlabel('M=N')  
	plt.ylabel('Speed up')  

	bx = fig.add_subplot(1,3,2)
	bx.set_title('Intel Core i5')
	x = [1,2,3,4,5]
	y = [2.5,5.0,7.5,10.0]
	Y1 = [4.485/4.485,  21.223/21.223,105.875/105.875,582.440/582.440, 5181.614/5181.614,]
	Y2 = [4.485/4.691,21.223/18.487, 105.875/74.312,582.440/294.780, 5181.614/1167.493,]
	Y3 = [4.485/3.063, 21.223/12.802,105.875/ 51.259,582.440/205.538, 5181.614/823.794,]
	Y4 = [4.485/1.563, 21.223/8.102, 105.875/33.839,582.440/134.788, 5181.614/536.457,]
	index = np.arange(5)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width*1.5,Y1,bar_width,alpha=opacity,facecolor = 'forestgreen',edgecolor = 'white',label='Typical')
	rec2 = plt.bar(index-bar_width*0.5,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='+COFFEE-C2R optimization')
	rec3 = plt.bar(index+bar_width*0.5,Y3,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='+Blocking optimization')
	rec4 = plt.bar(index+bar_width*1.5,Y4,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='+Micro-kernel optimization')
	plt.xlim(0.6,5.4)
	plt.ylim(0,10)
	plt.xticks(x ,['1000','2000','4000','8000','16000'],rotation=60)
	plt.yticks(y)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	bx.tick_params(left=False, bottom=False)
	plt.xlabel('M=N')

	cx = fig.add_subplot(1,3,3)
	cx.set_title('Mac M1')	
	x = [1,2,3,4,5]
	y = [1,2,3,4]
	Y1 = [7.561/7.561,23.515/ 23.515,146.741/146.741,544.645/544.645,2643.489/2643.489,]
	Y2 = [7.561/6.118, 23.515/19.323, 146.741/77.471,544.645/311.129,2643.489/1517.253,]
	Y3 = [7.561/5.645,23.515/17.982,146.741/73.049, 544.645/293.938,2643.489/1194.397, ]
	Y4 = [7.561/4.100,23.515/12.219,146.741/49.737,544.645/200.890,2643.489/811.551,]
	index = np.arange(5)+1  
	bar_width = 0.2 
	opacity = 1.0 
	rec1 = plt.bar(index-bar_width*1.5,Y1,bar_width,alpha=opacity,facecolor = 'forestgreen',edgecolor = 'white',label='Typical')
	rec2 = plt.bar(index-bar_width*0.5,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='+COFFEE-C2R optimization')
	rec3 = plt.bar(index+bar_width*0.5,Y3,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='+Blocking optimization')
	rec4 = plt.bar(index+bar_width*1.5,Y4,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='+Micro-kernel optimization')
	plt.xlim(0.6,5.4)
	plt.ylim(0,4)
	cx.tick_params(left=False, bottom=False)
	plt.xticks(x ,['1000','2000','4000','8000','16000'],rotation=60) 
	plt.yticks(y)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	plt.xlabel('M=N') 
	
	lines, labels = fig.axes[-1].get_legend_handles_labels()
	fig.legend(lines, labels, loc = 'upper center', ncol = 2)
	plt.show()

draw_Histogram()