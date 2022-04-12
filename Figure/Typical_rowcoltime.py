import numpy as np
from matplotlib import pyplot as plt
from pylab import *

plt.rc('font', family='Times New Roman', size=30)

def autolabel(rects,Num=1.1,rotation1=60,NN=1):
	for rect in rects:
		height = rect.get_height()
		plt.text(rect.get_x()-0.1+rect.get_width()/2., Num*height, '%s' % float(height*NN),rotation=60, fontsize=20)

def draw_Histogram():

	fig = plt.figure(figsize=(16,6))

	bx = fig.add_subplot(1,1,1)
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
	Y1 = [1.6, 17.5, 71.2, 154.985000, 274.758000, 419.859000, 597.037000, 792.007000, 1057.074000, 1352.325000, 1670.358000, 2063.701000, 2456.290000, 2908.714000, 3480.444000, 5005.144000,]
	Y2 = [1.2, 4.9, 11.1, 19.7, 30.9, 44.5, 61.1, 79.9, 101.1, 125.5, 151.156000, 180.887000, 211.828000, 245.496000, 282.349000, 320.720000,]
	for num in range (0,len(Y1)):
		Y1[num]=round(Y1[num],1)
	for num in range (0,len(Y2)):
		Y2[num]=round(Y2[num],1)
	index = np.arange(16)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width*0.5,Y1,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='Column rescaling')
	rec2 = plt.bar(index+bar_width*0.5,Y2,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='Row rescaling')

	autolabel(rec1)
	autolabel(rec2)
	
	plt.ylim(0,7000)
	plt.xlim(0.6,16.4)
	plt.xticks(x ,['1000','2000','3000','4000','5000','6000','7000','8000','9000','10000','11000','12000','13000','14000','15000','16000'],rotation=60) 
	bx.tick_params(left=False, bottom=False)
	plt.xlabel('M=N')  
	plt.ylabel('Time (ms)') 

	lines, labels = fig.axes[-1].get_legend_handles_labels()	
	fig.legend(lines, labels, loc = 'upper center', ncol = 6, fontsize=26)
	
	# plt.suptitle('Title')
	plt.show()

draw_Histogram()