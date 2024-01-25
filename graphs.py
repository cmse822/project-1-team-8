import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict
import scipy.stats as st

path = r'/Users/berkatik/Desktop/Courses/CMSE822 - Parallel computing/Assignments/project-1-team-8/output/matrix_multiplication_team_8.csv'
data = pd.read_csv(path)
plot_name = 'performance_chaaran_laptop'

mflops_s_data = defaultdict(list)

for idx, row in data.iterrows():
    n = row['N']

    if row['Performance'] != np.inf:
        mflops_s_data[n].append(row['Performance'])

x = []
means = []
ci_lows = []
ci_highs = []
y_max = max(mflops_s_data.values())[0]
x_max = max(mflops_s_data.items())[0]
for n, perf_data in mflops_s_data.items():
    x.append(n)
    means.append(np.mean(perf_data))
    ci_low, ci_high = st.t.interval(0.95, len(perf_data)-1, loc=np.mean(perf_data), scale=st.sem(perf_data))
    ci_lows.append(ci_low)
    ci_highs.append(ci_high)

# Plot the line
plt.plot(x, means, label='Mean')
plt.hlines(y=y_max, xmin=0, xmax=x_max, colors="r", label="Max Perf.")
# Plot the confidence interval as a shaded area
plt.fill_between(x, ci_lows, ci_highs, color='gray', alpha=0.3, label='95% Confidence Interval')

plt.xlabel('N')
plt.ylabel('MFLOPs/s')
plt.title('MFLOPs/s Vs N')
plt.legend()

plt.savefig(f'{plot_name}.png')