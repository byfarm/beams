import pandas as pd


def main():
    data = pd.read_csv("data.csv")
    x = list(data.iloc[:, 0])
    S = list(data.iloc[:, 1])
    M = list(data.iloc[:, 2])
    T = list(data.iloc[:, 3])

    max_s = max(S)
    max_m = max(M)
    min_s = min(S)
    min_m = min(M)
    max_t = max(T)
    min_t = min(T)
    print()
    print(f"Max Shear: {max_s} lbs")
    print(f"Min Shear: {min_s} lbs")
    print(f"Max Moment: {max_m} lb-ft")
    print(f"Min Moment: {min_m} lb-ft")
    print(f"Max Angle: {max_t} rad")
    print(f"Min Angle: {min_t} rad")

    interested_points = []

    for point in interested_points:
        idx = x.index(point)
        print()
        print(f"Data at x = {point} ft:")
        print(f"    Shear: {S[idx]} lbs")
        print(f"    Moment: {M[idx]} lb-ft")
        print(f"    Angle: {T[idx]} rad")


if __name__ == "__main__":
    main()
