import numpy as np
from matplotlib import pyplot as plt
from pylab import *

plt.rc('font', family='Times New Roman', size=14)

def draw_Histogram():
	temp = 0.0
	fig = plt.figure(figsize=(16,3.6))

	ax = fig.add_subplot(1,5,1)
	x = [1,2,3,4,5,6,7,8,9,10]
	Y1 = [8917.112,9513.982,13477.120,18769.026,18185.441,23403.033,24850.603,33102.354,35557.368,42691.122]
	Y2 = [5346.060991, 5574.421167, 6968.202114, 9241.979837,9960.385,12933.772,15530.719, 21941.168,23127.458, 30822.624]
	Y3 = [5328.142166, 5249.992132, 6307.651997, 7819.782019, 8256.601095, 10416.326, 12737.589, 16153.527,17352.833, 21557.456]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		temp = temp + Y2[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(10)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='MPICH-SALaR')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-MPI')
	
	plt.ylim(0,43000)
	plt.xlim(0.6,10.4)
	plt.xticks([])
	ax.tick_params(left=False, bottom=False)
	plt.xlabel('M=N')  
	plt.xticks(x ,['23040','46080','69120','92160','115200','138240','161280','184320','207360','230400'],rotation=60)
	plt.ylabel('Time (ms)') 


	cx = fig.add_subplot(1,5,2)
	x = [1,2,3,4,5,6,7,8,9,10]
	Y1 = [8568.555,10970.037,14789.314,18753.571,20013.189,22718.910,24269.204,28153.939,28386.883,30090.715]
	Y2 = [5457.977,6495.606,7394.384,8693.850,9377.330,10543.393,11632.619,13902.107,14111.197,15586.332]
	Y3 = [5135.409,5811.113,6507.493,7198.011,7827.155,8736.032,9534.890,10498.209,11338.066,12349.391]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		temp = temp + Y2[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(10)+1  
	bar_width = 0.2
	opacity = 1.0 
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='MPICH-SALaR')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-MPI')
	
	plt.ylim(0,31000)
	plt.xlim(0.6,10.4)
	plt.xticks([])
	cx.tick_params(left=False, bottom=False)
	plt.xticks(x ,['23040','46080','69120','92160','115200','138240','161280','184320','207360','230400'],rotation=60)
	plt.xlabel('N(M=92160)')  


	dx = fig.add_subplot(1,5,3)
	x = [1,2,3,4,5,6,7,8,9,10]
	Y1 = [7977.395,10944.576,14529.854,19330.760,20824.697,24041.482,25533.399,30392.168,32374.585,34605.786]
	Y2 = [5257.315,6811.460,8196.627,10161.055,11148.620,12969.509,15168.495,19137.341,19688.452,21825.075]
	Y3 = [4814.606,5837.189,6818.693,7847.203,8859.622,10005.838,11849.694,13008.265,14961.852,16422.954]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		temp = temp + Y2[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(10)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='MPICH-SALaR')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-MPI')
	
	plt.ylim(0,35000)
	plt.xlim(0.6,10.4)
	plt.xticks([])
	dx.tick_params(left=False, bottom=False)
	plt.xlabel('N(M=161280)')
	plt.xticks(x ,['23040','46080','69120','92160','115200','138240','161280','184320','207360','230400'],rotation=60)


	gx = fig.add_subplot(1,5,4)
	x = [1,2,3,4,5,6,7,8,9,10]
	Y1 = [17309.249,16349.182,17543.911,18736.495,17108.476,18192.478,19202.684,20242.681,21344.777,22443.979]
	Y2 = [6426.983,6664.091,7658.987,8680.037,8313.598,9218.535,10102.442,11014.735,12122.326,13315.257]
	Y3 = [5921.274,5838.564,6501.029,7195.993,6683.491,7363.667,7819.851,8459.632,8915.411,9608.834]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		temp = temp + Y2[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(10)+1  
	bar_width = 0.2 
	opacity = 1.0 
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='MPICH-SALaR')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-MPI')
	
	plt.ylim(0,23000)
	plt.xlim(0.6,10.4)
	gx.tick_params(left=False, bottom=False)
	plt.xticks(x ,['23040','46080','69120','92160','115200','138240','161280','184320','207360','230400'],rotation=60) 
	plt.xlabel('M(N=92160)')


	hx = fig.add_subplot(1,5,5)
	x = [1,2,3,4,5,6,7,8,9,10]
	Y1 = [19519.088,19189.933,21532.572,23570.524,22063.511,23684.062,25445.261,27242.504,29107.023,30859.704]
	Y2 = [6738.740,7798.455,9936.115,11633.617,11636.332,13043.844,15360.829,17360.204,19630.439,21466.706]
	Y3 = [6653.923,7033.560,8310.117,9474.972,9148.834,10282.251,11375.629,12053.868,12996.389,14794.686]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		temp = temp + Y2[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(10)+1  
	bar_width = 0.2
	opacity = 1.0 
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='MPICH-SALaR')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-MPI')
	
	plt.ylim(0,31000)
	plt.xlim(0.6,10.4)
	hx.tick_params(left=False, bottom=False)
	plt.xticks(x ,['23040','46080','69120','92160','115200','138240','161280','184320','207360','230400'],rotation=60)
	plt.xlabel('M(N=161280)')

	lines, labels = fig.axes[-1].get_legend_handles_labels()
	fig.legend(lines, labels, loc = 'upper center', ncol = 8)
	plt.show()
	
draw_Histogram()