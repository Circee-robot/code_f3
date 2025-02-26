import numpy as np
import matplotlib.pyplot as plt

tab = np.loadtxt("datawawa.csv", delimiter=",")
plt.plot(tab)
plt.axhline(10000, ls="--", color="r")

print(f"mean={tab[300:].mean()}")

plt.show()