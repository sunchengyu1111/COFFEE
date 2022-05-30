import numpy as np
from matplotlib import pyplot as plt
from pylab import *

plt.rc('font', family='Times New Roman', size=14)

def draw_Histogram():
	temp = 0.0
	fig = plt.figure(figsize=(16,3.6))

	ax = fig.add_subplot(1,5,1)
	x = [1,2,3,4,5,6,7,8,9,10]
	Y1 = [221.931934, 1003.760099, 2258.204937, 4521.301031, 5840.885878, 8747.452021, 11939.492941, 14604.751110, 17604.825974, 22703.845978,]
	Y2 = [206.161976, 1047.607183, 2430.180073, 4712.023973, 6008.905888, 8877.990007, 12043.047905, 14815.821171, 17986.280918, 22408.630064,]
	Y3 = [206.379175, 714.694977, 1649.001837, 3292.778969, 4694.032192, 6995.200872, 9863.735914, 11571.468830, 13647.192955, 16029.891014,]
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
	plt.ylim(0,21000)
	plt.xlim(0.6,10.4)
	plt.xticks([])
	ax.tick_params(left=False, bottom=False)
	plt.xlabel('M=N')  
	plt.xticks(x ,['23040','46080','69120','92160','115200','138240','161280','184320','207360','230400'],rotation=60)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	plt.ylabel('Time (ms)') 

	cx = fig.add_subplot(1,5,2)
	x = [1,2,3,4,5,6,7,8,9,10]
	Y1 = [943.537951, 2049.854040, 3102.185011, 4535.459995, 5396.187067, 6720.760107, 7874.391079, 10068.958998, 10488.234997, 12014.882088,]
	Y2 = [1011.121988, 2217.138052, 3280.093908, 4720.146894, 5579.582930, 6882.543087, 8004.983902, 10196.560144, 10619.441032, 12208.082199,]
	Y3 = [673.768997, 1448.948145, 2342.730999, 3278.041124, 4255.294085, 5282.500029, 6346.457005, 7446.359158, 8601.058006, 9782.135010,]
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
	plt.ylim(0,12100)
	plt.xlim(0.6,10.4)
	plt.xticks([])
	cx.tick_params(left=False, bottom=False)
	plt.xticks(x ,['23040','46080','69120','92160','115200','138240','161280','184320','207360','230400'],rotation=60)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	plt.xlabel('N(M=92160)')  

	dx = fig.add_subplot(1,5,3)
	x = [1,2,3,4,5,6,7,8,9,10]
	Y1 = [1438.041925, 3208.291054, 4825.703144, 6993.205070, 8280.110121, 10208.885908, 11896.429062, 15732.360840, 19012.264013, 23280.097008,]
	Y2 = [1582.205057, 3352.514029, 4998.388052, 7158.066988, 8442.275047, 10396.414995, 12029.551983, 16815.187931, 19439.794064, 23356.046963,]
	Y3 = [1037.886143, 2372.947931, 3823.509932, 5276.970863, 6753.534079, 8281.713009, 9870.813131, 11586.237907, 13516.724825, 16561.234951,]
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
	plt.ylim(0,23500)
	plt.xlim(0.6,10.4)
	plt.xticks([])
	dx.tick_params(left=False, bottom=False)
	plt.xlabel('N(M=161280)')
	plt.xticks(x ,['23040','46080','69120','92160','115200','138240','161280','184320','207360','230400'],rotation=60)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)

	gx = fig.add_subplot(1,5,4)
	x = [1,2,3,4,5,6,7,8,9,10]
	Y1 = [1272.120953, 2179.684162, 3362.849951, 4523.159027, 4904.335976, 5970.590830, 7003.736973, 7977.105856, 9091.200113, 10225.333929,]
	Y2 = [1333.887815, 2350.207090, 3545.907021, 4737.004995, 5074.252129, 6128.368139, 7164.541960, 8177.284002, 9292.137861, 10375.540972,]
	Y3 = [839.838028, 1469.774008, 2336.565971, 3273.365021, 3627.418041, 4450.546980, 5257.514000, 6038.727999, 6893.537045, 7714.422941,]
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
	plt.ylim(0,10600)
	plt.xlim(0.6,10.4)
	gx.tick_params(left=False, bottom=False)
	plt.xticks(x ,['23040','46080','69120','92160','115200','138240','161280','184320','207360','230400'],rotation=60) 
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	plt.xlabel('M(N=92160)')

	hx = fig.add_subplot(1,5,5)
	x = [1,2,3,4,5,6,7,8,9,10]
	Y1 = [1596.069098, 3484.927177, 5821.805954, 7836.822987, 8432.839870, 10158.486843, 11899.072886, 13635.095119, 16625.881195, 20997.053146,]
	Y2 = [1825.809956, 3684.176922, 6004.477024, 8034.821987, 8608.076811, 10344.617128, 12093.447924, 13782.475948, 16948.824167, 20657.313108, ]
	Y3 = [1546.705961, 2925.863981, 4632.526875, 6332.245827, 6918.099880, 8403.228998, 9867.938995, 11334.547043, 12889.699841, 15091.902018,]
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
	plt.ylim(0,21000)
	plt.xlim(0.6,10.4)
	hx.tick_params(left=False, bottom=False)
	plt.xticks(x ,['23040','46080','69120','92160','115200','138240','161280','184320','207360','230400'],rotation=60)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	plt.xlabel('M(N=161280)')

	lines, labels = fig.axes[-1].get_legend_handles_labels()
	fig.legend(lines, labels, loc = 'upper center', ncol = 8)
	plt.show()
	
draw_Histogram()