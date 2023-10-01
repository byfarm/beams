import matplotlib.pyplot as plt
import pandas as pd


def main():
    data = pd.read_csv("data.csv")
    x = list(data.iloc[:, 0])
    S = (data.iloc[:, 1])
    M = (data.iloc[:, 2])
    T = (data.iloc[:, 3])
    Y = (data.iloc[:, 4])
    print(Y)

    max_s = max(abs(S)) * 1.1
    max_m = max(abs(M)) * 1.1
    max_t = max(abs(T)) * 1.1
    max_y = max(abs(Y)) * 1.1

    fig, plot = plt.subplots(4, layout="constrained", figsize=(10, 9.5))

    plot[0].plot(x, S)
    plot[1].plot(x, M)
    plot[2].plot(x, T)
    plot[3].plot(x, Y)

    plot[0].set_title("Shear")
    plot[0].set_xlabel("x (ft)")
    plot[0].set_ylabel("Shear (lbs)")
    plot[0].grid(True)
    plot[0].set_xlim(0, x[-1])
    plot[0].set_ylim(-max_s, max_s)
    plot[0].axhline(0, color='black', linewidth=0.5)

    plot[1].set_title("Moment")
    plot[1].set_xlabel("x (ft)")
    plot[1].set_ylabel("Moment (lb-ft)")
    plot[1].grid(True)
    plot[1].set_xlim(0, x[-1])
    plot[1].set_ylim(-max_m, max_m)
    plot[1].axhline(0, color='black', linewidth=0.5)

    plot[2].set_title("Angle")
    plot[2].set_xlabel("x (ft)")
    plot[2].set_ylabel("Angle")
    plot[2].grid(True)
    plot[2].set_xlim(0, x[-1])
    plot[2].set_ylim(-max_t, max_t)
    plot[2].axhline(0, color='black', linewidth=0.5)

    plot[3].set_title("position")
    plot[3].set_xlabel("x (ft)")
    plot[3].set_ylabel("position {ft}")
    plot[3].grid(True)
    plot[3].set_xlim(0, x[-1])
    plot[3].set_ylim(-max_y, max_y)
    plot[3].axhline(0, color='black', linewidth=0.5)


    # fig.show()
    fig.savefig("plot.png")


if __name__ == "__main__":
    main()
