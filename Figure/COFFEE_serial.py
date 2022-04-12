import numpy as np
from matplotlib import pyplot as plt

plt.rc('font', family='Times New Roman', size=14)

def draw_line_chart():
	
	fig = plt.figure(figsize=(16,4.4))

	ax = fig.add_subplot(3,3,1)
	ax.set_title('AMD')
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,]
	y1 = [7.422, 33.235, 102.856, 212.702, 368.838, 569.798, 848.387, 2135.594, 2025.112, 3441.345, 5276.192, 6546.597, 6302.475, 8333.169, 10354.331, 13854.362,]
	y3 = [2.964, 10.472, 23.294, 40.943, 63.703, 91.817, 125.298, 164.039, 213.702, 253.853, 310.565, 377.634, 448.317, 508.408, 592.994, 667.207,]
	y2 = [6.157, 24.096, 54.274, 96.391, 149.302, 219.003, 296.133, 380.427, 479.188, 597.948, 723.698, 861.793, 1012.784, 1175.690, 1349.000, 1539.930,]
	plt.plot(x,y1,'*-',alpha=0.8,color = 'chocolate',linewidth=1,label='Typical')
	plt.plot(x,y2,'x-',alpha=0.8,color = 'seagreen',linewidth=2,label='COFFEE-C2R')
	plt.plot(x,y3,'^-',alpha=0.8,color = 'darkviolet',linewidth=2,label='COFFEE-CPU')
	
	plt.ylim(0,14000)
	plt.xlim(0.6,16.4)
	ax.tick_params(left=False, bottom=False)
	plt.xticks([])
	plt.xlabel("M=N")
	plt.ylabel("Time (ms)",labelpad=4)
	# plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='x',alpha=0.4)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	

	bx = fig.add_subplot(3,3,4)
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,]
	y1 = [106.311, 222.138, 356.350, 531.543, 653.118, 811.532, 997.874, 2167.316, 1619.750, 2160.146, 2418.879, 2615.924, 2683.306, 2899.414, 3052.143, 5219.382,]
	y3 = [20.757, 40.074, 60.455, 81.820, 101.327, 123.514, 141.917, 162.244, 183.461, 204.871, 225.302, 247.861, 274.993, 296.476, 319.709, 331.408,]
	y2 = [ 47.872, 95.260, 142.960, 193.106, 243.277, 292.243, 333.348, 384.948, 429.770, 479.071, 524.028, 570.507, 617.284, 666.934, 713.498, 760.033,]
	plt.plot(x,y1,'*-',alpha=0.8,color = 'chocolate',linewidth=1,label='Typical')
	plt.plot(x,y2,'x-',alpha=0.8,color = 'seagreen',linewidth=2,label='COFFEE-C2R')
	plt.plot(x,y3,'^-',alpha=0.8,color = 'darkviolet',linewidth=2,label='COFFEE-CPU')
	
	plt.ylim(0,5300)
	plt.xlim(0.6,16.4)
	bx.tick_params(left=False, bottom=False)
	plt.xticks([])
	plt.xlabel("N(M=8000)")
	plt.ylabel("Time (ms)",labelpad=10)
	# plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='x',alpha=0.4)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	
	
	cx = fig.add_subplot(3,3,7)
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,]	
	y1 = [63.431, 130.565, 297.141, 534.403, 833.999, 1177.416, 1662.414, 2128.046, 2634.723, 3140.125, 3642.039, 3955.383, 4634.011, 5099.289, 5945.684, 6733.754,]
	y3 = [20.875, 41.233, 61.867, 84.351, 102.078, 122.751, 142.231, 161.891, 183.443, 204.347, 222.993, 243.734, 262.354, 284.161, 305.761, 330.057,]
	y2 = [48.295, 95.728, 143.572, 191.342, 237.436, 285.330, 333.824, 381.244, 428.515, 477.557, 523.826, 570.870, 618.695, 664.150, 712.480, 766.407,]
	plt.plot(x,y1,'*-',alpha=0.8,color = 'chocolate',linewidth=1,label='Typical')
	plt.plot(x,y2,'x-',alpha=0.8,color = 'seagreen',linewidth=2,label='COFFEE-C2R')
	plt.plot(x,y3,'^-',alpha=0.8,color = 'darkviolet',linewidth=2,label='COFFEE-CPU')
	
	plt.ylim(0,6800)
	plt.xlim(0.6,16.4)
	cx.tick_params(left=False, bottom=False)
	plt.xticks(x, [ '1000', '2000', '3000', '4000', '5000', '6000', '7000', '8000', '9000', '10000','11000', '12000', '13000', '14000', '15000','16000', ], rotation=60)
	plt.xlabel("M(N=8000)")
	plt.ylabel("Time (ms)",labelpad=10)
	# plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='x',alpha=0.4)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	

	dx = fig.add_subplot(3,3,2)
	dx.set_title('Intel')
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,]	
	y1 = [4.485, 21.223, 55.235, 105.875, 179.798, 282.918, 406.332, 582.440, 796.013, 1056.278, 1346.351, 1695.218, 2090.724, 2574.308, 3081.228, 5181.614,]
	y2 = [4.691, 18.487, 41.930, 74.312, 115.861, 166.292, 225.934, 294.780, 371.897, 458.112, 553.277, 657.333, 772.628, 894.541, 1027.993, 1167.493,]
	y3 = [1.977, 8.196, 18.655, 34.300, 54.027, 77.962, 106.879, 137.800, 176.732, 217.812, 252.366, 312.570, 369.954, 433.879, 495.845, 555.169,]
	plt.plot(x,y1,'*-',alpha=0.8,color = 'chocolate',linewidth=1,label='Typical')
	plt.plot(x,y2,'x-',alpha=0.8,color = 'seagreen',linewidth=2,label='COFFEE-C2R')
	plt.plot(x,y3,'^-',alpha=0.8,color = 'darkviolet',linewidth=2,label='COFFEE-CPU')
	
	plt.ylim(0,5200)
	plt.xlim(0.6,16.4)
	dx.tick_params(left=False, bottom=False)
	plt.xticks([])
	plt.xlabel("M=N")
	# plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='x',alpha=0.4)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	

	ex = fig.add_subplot(3,3,5)
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,]	
	y1 = [51.408, 114.254, 175.270, 252.967, 322.727, 401.417, 476.365, 584.507, 692.744, 809.088, 923.459, 1040.902, 1176.811, 1333.913, 1477.452, 1676.500,]
	y2 = [37.156, 74.142, 110.108, 148.534, 185.272, 222.131, 258.345, 293.865, 330.848, 366.303, 403.383, 438.390, 474.786, 510.952, 547.677, 583.867,]
	y3 = [16.490, 34.404, 51.828, 66.691, 86.952, 104.078, 122.021, 137.991, 157.051, 170.087, 189.682, 207.635, 225.824, 238.995, 254.858, 276.314,]
	plt.plot(x,y1,'*-',alpha=0.8,color = 'chocolate',linewidth=1,label='Typical')
	plt.plot(x,y2,'x-',alpha=0.8,color = 'seagreen',linewidth=2,label='COFFEE-C2R')
	plt.plot(x,y3,'^-',alpha=0.8,color = 'darkviolet',linewidth=2,label='COFFEE-CPU')
	
	plt.ylim(0,1700)
	plt.xlim(0.6,16.4)
	ex.tick_params(left=False, bottom=False)
	plt.xticks([])
	plt.xlabel("N(M=8000)")
	# plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='x',alpha=0.4)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)

	
	fx = fig.add_subplot(3,3,8)
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,]	
	y1 = [38.171, 86.268, 154.201, 232.063, 317.357, 401.531, 490.759, 583.933, 677.164, 776.333, 877.125, 1001.957, 1095.949, 1243.722, 1410.052, 1543.420,]
	y2 = [36.806, 73.499, 110.470, 147.409, 184.304, 220.693, 257.758, 294.354, 331.350, 367.990, 405.274, 442.033, 478.415, 515.564, 552.473, 587.038,]
	y3 = [17.009, 34.222, 51.398, 68.640, 85.936, 99.813, 120.391, 138.102, 155.010, 172.857, 189.688, 200.376, 224.325, 241.751, 258.894, 276.724,]
	plt.plot(x,y1,'*-',alpha=0.8,color = 'chocolate',linewidth=1,label='Typical')
	plt.plot(x,y2,'x-',alpha=0.8,color = 'seagreen',linewidth=2,label='COFFEE-C2R')
	plt.plot(x,y3,'^-',alpha=0.8,color = 'darkviolet',linewidth=2,label='COFFEE-CPU')
	
	plt.ylim(0,1600)
	plt.xlim(0.6,16.4)
	fx.tick_params(left=False, bottom=False)
	plt.xticks(x, [ '1000', '2000', '3000', '4000', '5000', '6000', '7000', '8000', '9000', '10000','11000', '12000', '13000', '14000', '15000','16000', ], rotation=60)
	plt.xlabel("M(N=8000)")
	# plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='x',alpha=0.4)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	

	gx = fig.add_subplot(3,3,3)
	gx.set_title('ARM V8')
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,]	
	y1 = [7.561, 23.515, 53.359, 146.741, 235.739, 316.902, 424.000, 544.645, 650.267, 760.382, 908.803, 1102.971, 1245.615, 1409.942, 1625.245, 2643.489,]
	y2 = [6.118, 19.323, 43.564, 77.471, 121.102, 174.799, 238.178, 311.129, 396.239, 493.538, 630.866, 750.471, 879.798, 1022.540, 1222.993, 1517.253,]
	y3 = [4.100, 12.219, 27.755, 49.737, 77.727, 112.269, 152.842, 200.890, 255.602, 316.108, 382.368, 455.988, 534.308, 619.105, 711.258, 811.551,]
	plt.plot(x,y1,'*-',alpha=0.8,color = 'chocolate',linewidth=1,label='Typical')
	plt.plot(x,y2,'x-',alpha=0.8,color = 'seagreen',linewidth=2,label='COFFEE-C2R')
	plt.plot(x,y3,'^-',alpha=0.8,color = 'darkviolet',linewidth=2,label='COFFEE-CPU')
	
	plt.ylim(0,2700)
	plt.xlim(0.6,16.4)
	gx.tick_params(left=False, bottom=False)
	plt.xticks([])
	plt.xlabel("M=N")
	# plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='x',alpha=0.4)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	

	hx = fig.add_subplot(3,3,6)
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,]
	y1 = [50.392, 132.137, 231.773, 347.743, 406.897, 439.867, 490.215, 544.613, 571.707, 595.682, 639.430, 697.219, 730.185, 768.507, 830.168, 946.492,]
	y2 = [38.000, 75.873, 113.798, 151.639, 189.545, 227.901, 266.165, 304.357, 345.340, 382.485, 421.579, 458.842, 497.819, 535.457, 574.196, 612.977,]
	y3 = [25.235, 49.635, 74.551, 99.785, 124.489, 149.785, 174.561, 200.285, 227.180, 252.952, 278.658, 304.214, 329.627, 353.723, 379.261, 405.669,]
	plt.plot(x,y1,'*-',alpha=0.8,color = 'chocolate',linewidth=1,label='Typical')
	plt.plot(x,y2,'x-',alpha=0.8,color = 'seagreen',linewidth=2,label='COFFEE-C2R')
	plt.plot(x,y3,'^-',alpha=0.8,color = 'darkviolet',linewidth=2,label='COFFEE-CPU')
	
	plt.ylim(0,1000)
	plt.xlim(0.6,16.4)
	hx.tick_params(left=False, bottom=False)
	plt.xticks([])
	plt.xlabel("N(M=8000)")
	# plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='x',alpha=0.4)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	
	
	ix = fig.add_subplot(3,3,9)
	x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,]
	y1 = [47.556, 96.166, 167.660, 245.103, 321.461, 395.788, 470.172, 544.361, 618.036, 692.901, 767.498, 847.242, 923.149, 1018.320, 1091.810, 1177.539,]
	y2 = [38.054, 76.093, 114.363, 152.496, 190.220, 228.855, 266.467, 304.924, 342.398, 380.472, 419.144, 456.684, 495.508, 532.715, 572.047, 610.310,]
	y3 = [24.766, 49.642, 74.446, 99.638, 125.105, 150.235, 175.441, 200.432, 225.303, 250.290, 275.255, 301.622, 325.177, 350.276, 375.231, 400.230,]
	plt.plot(x,y1,'*-',alpha=0.8,color = 'chocolate',linewidth=1,label='Typical')
	plt.plot(x,y2,'x-',alpha=0.8,color = 'seagreen',linewidth=2,label='COFFEE-C2R')
	plt.plot(x,y3,'^-',alpha=0.8,color = 'darkviolet',linewidth=2,label='COFFEE-CPU')
	
	plt.ylim(0,1200)
	plt.xlim(0.6,16.4)
	ix.tick_params(left=False, bottom=False)
	plt.xticks(x, [ '1000', '2000', '3000', '4000', '5000', '6000', '7000', '8000', '9000', '10000','11000', '12000', '13000', '14000', '15000','16000', ], rotation=60)
	plt.xlabel("M(N=8000)")
	# plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='x',alpha=0.4)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)

	lines, labels = fig.axes[-1].get_legend_handles_labels()
	fig.legend(lines, labels, loc = 'upper center',ncol=3)

	plt.show()
	
draw_line_chart()