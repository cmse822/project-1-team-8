import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict
import scipy.stats as st
from mpl_toolkits.axes_grid1 import make_axes_locatable

path = "./matrix_multiplication_team_8_hpcc.csv"
data = pd.read_csv(path)
plot_name = 'performance_hpcc_intel_18'
use_time = True
peak_perf = 2.4
plot_title = 'HPCC cluster Intel 18 performance'

mflops_s_data = defaultdict(list)

for idx, row in data.iterrows():
    n = row['N']

    if use_time:
        mflops_s_data[n].append(row['Time'])
    else:
        if row['Performance'] != np.inf:
            mflops_s_data[n].append(row['Performance'] / 10 ** 3)


x = []
means = []
ci_lows = []
ci_highs = []
y_max = max(mflops_s_data.values())[0]
x_max = max(mflops_s_data.items())[0]
for n, perf_data in mflops_s_data.items():
    x.append(n)

    if use_time:
        flops = (2*n**3 - n**2) / 10**6
        perf_data = flops/(np.array(perf_data) * (10 ** 3))
        means.append(np.mean(perf_data))
    else:
        means.append(np.mean(perf_data))

    ci_low, ci_high = st.t.interval(0.95, len(perf_data)-1, loc=np.mean(perf_data), scale=st.sem(perf_data))
    ci_lows.append(ci_low)
    ci_highs.append(ci_high)

# Plot the line
fig, ax = plt.subplots()

ax.plot(x, means, label='Mean')

# Plot the confidence interval as a shaded area
ax.fill_between(x, ci_lows, ci_highs, color='gray', alpha=0.3, label='95% Confidence Interval')

# Add a horizontal line at peak performance
ax.axhline(y=peak_perf, color='red', label='Peak Perf')

plt.xlabel('N')
plt.ylabel('GFLOPs/s')
plt.title(plot_title)
plt.legend()

plt.savefig(f'{plot_name}.png')