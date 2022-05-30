import numpy as np
from matplotlib import pyplot as plt

plt.rc('font', family='Times New Roman', size=14)

def draw_line_chart():
	
	fig = plt.figure(figsize=(8,3.4))

	ax = fig.add_subplot(1,1,1)
	x = [1,2,3,4,5,6,7,8,9,10]
	y1 = [20.838/29.393,29.499/35.357,72.262/83.430,1335.234/1489.220,2174.576/2399.764
	     ,3040.592/3342.745,4125.542/4525.978,5372.677/5888.385,6766.068/7390.062,8273.630/9000.827]
	plt.plot(x,y1,'*-',alpha=0.8,color = 'chocolate',linewidth=1,label='Unbalanced optimal transport')
	plt.xlim(0.6,10.4)
	plt.ylim(0.7,1)
	ax.tick_params(left=False, bottom=False)
	plt.xticks(x, [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000], rotation=60)
	plt.xlabel("M=N")
	plt.ylabel("Time ratio of SK algorithm",labelpad=4)
	plt.grid(color='#95a5a6',linestyle='--', linewidth=1 ,axis='y',alpha=0.4)
	lines, labels = fig.axes[-1].get_legend_handles_labels()
	fig.legend(lines, labels, loc = 'upper center',ncol=3)

	plt.show()
	
draw_line_chart()