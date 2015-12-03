from scipy import stats as st
from matplotlib import pyplot as pp
import matplotlib.patches as mpatches
import matplotlib as mpl
from matplotlib.ticker import Locator
import numpy as np
import operator
import csv
import collections
import math
import copy




# Figure - Rapid Optical Density Calibration Plot
# RODD = [0.01,	0.03,	0.07,	0.1,	0.17,	0.18,	0.26,	0.46,	0.76]
# SPEC = [0.0155,	0.0392,	0.0753,	0.1091,	0.1582,	0.1758,	0.2332,	0.4397,	0.7296]

RODD = [0.01,	0.05,	0.09,	0.12,	0.14,	0.16,	0.18,	0.34,	0.76]
SPEC = [0.0325,   0.08145, 0.13062, 0.16941, 0.18323, 0.21266, 0.23708, 0.41538, 0.92972]
MAPPED = [0.04,	0.09,	0.13,	0.16,	0.18,	0.21,	0.25,	0.41,	0.94]
linear = [0,0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1]

#------------- Scatter Expression plots -------------- #
figWidth = 5
figHight = 5
line_width = 3
marker_size = 10
axis_fontsize = 14
legend_fontsize = 10

mpl.rcParams['xtick.major.size'] = 5
mpl.rcParams['xtick.major.width'] = 1.1
mpl.rcParams['xtick.minor.size'] = 3
mpl.rcParams['xtick.minor.width'] = 1.1

mpl.rcParams['ytick.major.size'] = 5
mpl.rcParams['ytick.major.width'] = 1.1
mpl.rcParams['ytick.minor.size'] = 3
mpl.rcParams['ytick.minor.width'] = 1.1
mpl.rcParams['font.weight'] = 'light'
mpl.rcParams['font.sans-serif'] = 'Arial'
mpl.rcParams['text.usetex'] = False

cal_poly = np.polyfit(RODD, SPEC, 1)
cal_func =  np.poly1d(cal_poly)
x_vals = np.linspace(0, 1, 50)
print(cal_func)

# --- Calibration Plot --- #
fig = pp.figure(figsize=(figWidth, figHight))
ax = pp.subplot()
p1 = ax.plot(RODD, SPEC, color = '#000000', linestyle = 'none',
             marker = 'o', markersize = 8, markeredgecolor = 'none', label="Raw RODD OD")
# p3 = ax.plot(x_vals, cal_func(x_vals), color = "r", linewidth = 1, linestyle = '--', label="Spectro. Calibration Fit")
p4 = ax.plot(MAPPED, SPEC, color = "r", marker = 'o', markersize = 8, linestyle = 'none', label="Calibrated RODD OD600")
p2 = ax.plot(linear, linear, color = '#000000', linewidth = 1, linestyle ='--', label="1:1 RODD to OD600\n Relationship")
p1[0].set_clip_on(False)
ax.set_ylim([0,1])
xaxis = fig.gca().xaxis
ax.xaxis.set_ticks_position('bottom')
ax.yaxis.set_ticks_position('left')
for axis in ['top','bottom','left','right']:
  ax.spines[axis].set_linewidth(2)
ax.set_xlabel('RODD Values (a.u.)', fontsize = 16)
ax.set_ylabel("Spectro. Absorbance (OD600)", fontsize = 16)
ax.tick_params(axis='x', labelsize=14)
ax.tick_params(axis='y', labelsize=14)
ax.set_title("RODD Calibration Curve", fontsize = 20)
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles, labels, fontsize = 12, frameon=False, loc="upper left")
pp.tight_layout()
fig.savefig('calibration_curve.pdf')
