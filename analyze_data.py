import pandas as pd


def main():
    data = pd.read_csv("data.csv")
    x = list(data.iloc[:, 0])
    S = list(data.iloc[:, 1])
    M = list(data.iloc[:, 2])

    max_s = max(S)
    max_m = max(M)
    min_s = min(S)
    min_m = min(M)
    print()
    print(f"Max Shear: {max_s} lbs")
    print(f"Min Shear: {min_s} lbs")
    print(f"Max Moment: {max_m} lb-ft")
    print(f"Min Moment: {min_m} lb-ft")

    interested_points = [4.3, 3]

    for point in interested_points:
        idx = x.index(point)
        print()
        print(f"Data at x = {point} ft:")
        print(f"    Shear: {S[idx]} lbs")
        print(f"    Moment: {M[idx]} lb-ft")


if __name__ == "__main__":
    main()
