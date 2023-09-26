import matplotlib.pyplot as plt
import pandas as pd


data = pd.read_csv("data.csv")
x = list(data.iloc[:, 0])
S = (data.iloc[:, 1])
M = (data.iloc[:, 2])

Ss = list(S)
Mm = list(M)

max_s = max(S)
max_m = max(M)
idx = Mm.index(max_m)
print("S at 0:", Ss[idx])
min_s = min(S)
min_m = min(M)
print(f"Max Shear: {max_s} lb/ft^2")
print(f"Min Shear: {min_s} lb/ft^2")
print(f"Max Moment: {max_m} lb/ft^2")
print(f"Min Moment: {min_s} lb/ft^2")
max_s = max(abs(S)) * 1.1
max_m = max(abs(M)) * 1.1

fig, plot = plt.subplots(2, layout="constrained", figsize=(10, 9.5))


plot[0].plot(x, S)
plot[1].plot(x, M)

plot[0].set_title("Shear")
plot[0].set_xlabel("x")
plot[0].set_ylabel("lb/ft^2")
plot[0].grid(True)
plot[0].set_xlim(0, x[-1])
plot[0].set_ylim(-max_s, max_s)
plot[0].axhline(0, color='black', linewidth=0.5)

plot[1].set_title("Moment")
plot[1].set_xlabel("x")
plot[1].set_ylabel("lb/ft^2")
plot[1].grid(True)
plot[1].set_xlim(0, x[-1])
plot[1].set_ylim(-max_m, max_m)
plot[1].axhline(0, color='black', linewidth=0.5)

fig.savefig("plot.png")
