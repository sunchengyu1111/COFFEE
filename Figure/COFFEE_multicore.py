import numpy as np
from matplotlib import pyplot as plt
from pylab import *

plt.rc('font', family='Times New Roman', size=14)

def autolabel(rects,Num=1,rotation1=60,NN=1):
	for rect in rects:
		height = rect.get_height()
		plt.text(rect.get_x()-0.04+rect.get_width()/2., Num*height, '%s' % float(height*NN),rotation=rotation1)

def draw_Histogram():
	temp=0
	fig = plt.figure(figsize=(16,4.4))

	ax = fig.add_subplot(3,3,1)
	ax.set_title('AMD')
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13]
	Y3 = [2609.472513, 3312.963009, 4105.086088, 4151.344538, 4993.005276, 5779.831886, 6747.085094, 7731.556416, 8841.073990, 9905.371428, 11114.755154, 12347.528458, 13623.373032,]
	Y1 = [8797.767639, 10498.012304, 13473.479748, 16517.916918, 21479.104757, 21336.112738, 28222.989798, 29824.067116, 53406.167269, 48167.831182, 56606.336594, 74482.998371, 102193.706751,]
	Y2 = [3000.045061, 3808.119535, 4678.251982, 4764.909029, 5680.029154, 6692.281723, 7798.958778, 8940.488100, 10173.793077, 11486.719847, 12886.890173, 14303.702354, 15811.541796,]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(13)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='COFFEE-C2R')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-CPU')
	
	plt.ylim(0,105000)
	plt.xlim(0.6,13.4)  
	plt.xticks([])
	ax.tick_params(left=False, bottom=False)
	plt.ylabel('Time (ms)\nP=2',labelpad=5) 


	bx = fig.add_subplot(3,3,4)
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13]
	Y3 = [1564.056635, 1972.084045, 2416.782618, 2932.810068, 3469.866037, 4215.470791, 4735.222340, 5457.352638, 5309.456110, 5879.547834, 6817.086935, 7467.187881, 8409.102201,]
	Y1 = [2740.792990, 4077.491999, 6010.497570, 7433.186531, 8775.727272, 11106.282711, 13644.844532, 16427.257061, 23963.157654, 19059.096098, 23349.845648, 26880.619764, 33305.317402,]
	Y2 = [1605.534792, 2028.381348, 2509.999752, 3040.340185, 3645.171642, 4307.260036, 4957.527876, 5682.776213, 5415.355921, 6124.820948, 6861.740828, 7673.478365, 8485.239267,]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(13)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='COFFEE-C2R')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-CPU')
	
	plt.ylim(0,34000)
	plt.xlim(0.6,13.4)  
	plt.xticks([])
	bx.tick_params(left=False, bottom=False)
	plt.ylabel('Time (ms)\nP=4',labelpad=10) 


	cx = fig.add_subplot(3,3,7)
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13]

	Y3 = [1194.307327, 1446.344137, 1775.124073, 2167.990685, 2561.629534, 3060.357809, 3533.456564, 4010.002136, 4513.735533, 5050.215721, 5851.450205, 6690.777540, 7089.962482,]
	Y1 = [1762.472391, 2242.783308, 2975.777149, 3660.968542, 3882.995129, 4948.838234, 5594.598770, 6675.363302, 9503.194571, 9207.373142, 10955.218792, 13021.908283, 15124.610901, ]
	Y2 = [1198.190451, 1700.552225, 1828.907251, 2326.080322, 2626.601934, 3078.124523, 3606.056213, 4021.819592, 4835.932732, 5492.777824, 5934.072733, 6840.800047, 7193.164110,]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(13)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='COFFEE-C2R')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-CPU')
	
	plt.ylim(0,16000)
	plt.xlim(0.6,13.4)  
	plt.xticks([])
	plt.ylabel('Time (ms)',labelpad=10)
	plt.xticks(x ,['8000','9000','10000','11000','12000','13000','14000','15000','16000','17000','18000','19000','20000'],rotation=60)
	plt.xlabel('M=N')	
	cx.tick_params(left=False, bottom=False)
	plt.ylabel('Time (ms)\nP=8')


	dx = fig.add_subplot(3,3,2)
	dx.set_title('Intel')
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13]
	Y3 = [2251.124859, 2845.687389, 3536.739588, 3562.540293, 4255.547285, 4968.420506, 5782.500267, 6605.855942, 7500.719786, 8495.146990, 9505.960464, 10654.635429, 11847.594023,]
	Y1 = [3503.715754, 4746.457338, 6121.787071, 6392.379999, 7748.645306, 9569.544554, 11467.757702, 13631.580353, 23784.982920, 18243.612289, 20843.646526, 23295.073509, 28153.319359,]
	Y2 = [2534.737587, 3208.945751, 3957.298279, 3991.067410, 4744.974852, 5565.747023, 6446.313143, 7404.633045, 8414.031506, 9510.829210, 10650.402784, 11855.648756, 13154.233456,]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(13)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='COFFEE-C2R')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-CPU')
	
	plt.ylim(0,29000)
	plt.xlim(0.6,13.4)  
	plt.xticks([])	
	dx.tick_params(left=False, bottom=False)
	

	ex = fig.add_subplot(3,3,5)
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13]
	Y3 = [1734.451056, 2232.328415, 2768.691301, 3334.974051, 3919.623375, 4587.992191, 5340.069532, 6181.363821, 5832.602501, 6621.733189, 7365.584135, 8194.922686, 9080.899954, ]
	Y1 = [2035.876274, 2616.630316, 3209.233284, 4062.540054, 5062.576056, 6072.524071, 7472.811937, 8956.125736, 9638.645411, 10221.693277, 11719.112396, 13263.074398, 14897.087097,]
	Y2 = [1765.595913, 2242.280722, 2770.853519, 3356.018782, 4001.274824, 4654.816866, 5458.839893, 6225.651264, 5885.869503, 6648.549318, 7477.124691, 8286.984205, 9231.128454,]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(13)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='COFFEE-C2R')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-CPU')
	
	plt.ylim(0,15000)
	plt.xlim(0.6,13.4)  
	plt.xticks([])	
	ex.tick_params(left=False, bottom=False)
	

	fx = fig.add_subplot(3,3,8)
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13]
	Y3 = [1893.747807, 2369.893312, 2928.846359, 3568.293333, 4236.027002, 4976.056576, 5811.796188, 6634.497404, 7547.610283, 8552.912474, 9534.738541, 10630.069017, 11794.267178]
	Y1 = [2186.128378, 2704.515696, 3488.533258, 4224.813938, 5475.630045, 6339.928627, 7813.676596, 9082.670689, 10607.595682, 12197.703362, 14086.236954, 16216.307640, 17655.954361,]
	Y2 = [1936.053514, 2462.901354, 3034.130812, 3683.238029, 4378.393888, 5168.128967, 5979.700327, 6860.862017, 7797.480106, 8795.747519, 9874.241114, 11042.678833, 12234.916449,]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(13)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='COFFEE-C2R')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-CPU')
	
	plt.ylim(0,18000)
	plt.xlim(0.6,13.4)  
	plt.xticks(x ,['8000','9000','10000','11000','12000','13000','14000','15000','16000','17000','18000','19000','20000'],rotation=60)
	plt.xlabel('M=N')	
	fx.tick_params(left=False, bottom=False)
	

	gx = fig.add_subplot(3,3,3)
	gx.set_title('ARM V8')
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13]
	Y3 = [2908.327000, 3677.069000, 4562.820000, 4610.914000, 5505.995000, 6461.409000, 7429.762000, 8529.818000, 9710.710000, 10945.619000, 12407.215000, 13761.800000, 15213.142000,]
	Y1 = [4361.247000, 5449.467000, 6418.163000, 6542.424000, 7624.264000, 9052.189000, 10186.203000, 11878.099000, 18777.906000, 15074.407000, 16374.222000, 18733.475000, 20555.997000,]
	Y2 = [3208.208000, 4076.403000, 5013.055000, 5059.989000, 6030.266000, 7074.038000, 8195.684000, 9405.907000, 10752.606000, 12196.378000, 13573.758000, 15234.852000, 16886.567000,]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(13)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='COFFEE-C2R')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-CPU')
	
	plt.ylim(0,21000)
	plt.xlim(0.6,13.4)  
	plt.xticks([])	
	gx.tick_params(left=False, bottom=False)
	

	hx = fig.add_subplot(3,3,6)
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13]
	Y3 = [1500.067000, 1890.604000, 2297.962000, 2782.699000, 3343.794000, 3942.541000, 4564.872000, 4368.530000, 4965.775000, 5615.078000, 6295.810000, 7012.833000, 7789.559000,]
	Y1 = [1868.860000, 2373.141000, 3112.128000, 3744.520000, 4431.572000, 5403.875000, 6134.934000, 6156.048000, 6847.989000, 7732.480000, 8433.180000, 9693.100000, 10376.811000,]
	Y2 =[1644.342000, 2110.847000, 2668.370000, 3135.441000, 3713.759000, 4373.317000, 5046.453000, 4840.411000, 5511.692000, 6218.545000, 6977.003000, 7772.253000, 9868.201000,]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(13)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='COFFEE-C2R')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-CPU')
	
	plt.ylim(0,11000)
	plt.xlim(0.6,13.4)  
	plt.xticks([])	
	hx.tick_params(left=False, bottom=False)
	

	ix = fig.add_subplot(3,3,9)
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13]
	Y3 = [759.865000, 970.788000, 1187.960000, 1446.887000, 1717.655000, 2020.318000, 2327.759000, 2706.033000, 3061.922000, 3430.710000, 3845.874000, 4289.283000, 4786.394000,]
	Y1 = [951.855000, 1210.002000, 1463.865000, 1824.878000, 2205.867000, 2561.706000, 2919.909000, 3453.330000, 3810.725000, 4406.410000, 4830.630000, 5576.800000, 6056.649000,]
	Y2 = [830.611000, 1086.518000, 1312.790000, 1585.212000, 1873.830000, 2192.798000, 2604.760000, 2988.471000, 3396.393000, 3840.249000, 4275.650000, 4886.210000, 5421.991000,]
	for num in range (0,len(Y1)):
		temp = temp + Y1[num]/Y3[num]
		print(Y1[num]/Y3[num])
	print(temp)

	index = np.arange(13)+1  
	bar_width = 0.2
	opacity = 1.0
	rec1 = plt.bar(index-bar_width,Y1,bar_width,alpha=opacity,facecolor = 'darkorange',edgecolor = 'white',label='MPICH-Ring')
	rec2 = plt.bar(index,Y2,bar_width,alpha=opacity,facecolor = 'dodgerblue',edgecolor = 'white',label='COFFEE-C2R')
	rec3 = plt.bar(index+bar_width,Y3,bar_width,alpha=opacity,facecolor = 'deeppink',edgecolor = 'white',label='COFFEE-CPU')
	
	plt.ylim(0,6500)
	plt.xlim(0.6,13.4)  
	ix.tick_params(left=False, bottom=False)
	plt.xticks(x ,['8000','9000','10000','11000','12000','13000','14000','15000','16000','17000','18000','19000','20000'],rotation=60)
	plt.xlabel('M=N')

	lines, labels = fig.axes[-1].get_legend_handles_labels()
	fig.legend(lines, labels, loc = 'upper center', ncol = 8)
	plt.show()
	
draw_Histogram()