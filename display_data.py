import matplotlib.pyplot as plt
import pandas as pd


data = pd.read_csv("data.csv")
x = list(data.iloc[:, 0])
S = (data.iloc[:, 1])
M = (data.iloc[:, 2])

max_s = max(abs(S)) * 1.1
max_m = max(abs(M)) * 1.1

fig, plot = plt.subplots(2, layout="constrained", figsize=(10, 9.5))


plot[0].plot(x, S)
plot[1].plot(x, M)

plot[0].set_title("Shear")
plot[0].set_xlabel("x (ft)")
plot[0].set_ylabel("Shear (lbs)")
plot[0].grid(True)
plot[0].set_xlim(0, x[-1])
plot[0].set_ylim(-max_s, max_s)
plot[0].axhline(0, color='black', linewidth=0.5)

plot[1].set_title("Moment")
plot[1].set_xlabel("x (ft)")
plot[1].set_ylabel("lb-ft")
plot[1].grid(True)
plot[1].set_xlim(0, x[-1])
plot[1].set_ylim(-max_m, max_m)
plot[1].axhline(0, color='black', linewidth=0.5)

# fig.show()
fig.savefig("plot.png")
