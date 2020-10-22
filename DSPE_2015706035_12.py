import numpy as np
import matplotlib.pylab as plt

fig=plt.figure()
ax=fig.add_subplot(1, 1, 1)

x=np.arange(-10, 10, 0.1)

f1=1/(1+np.exp(-0.5*x))
f2=1/(1+np.exp(-1*x))
f3=1/(1+np.exp(-1.5*x))
f4=1/(1+np.exp(-2*x))
f5=1/(1+np.exp(-2.5*x))
f6=1/(1+np.exp(-3*x))

ax.plot(x, f1)
ax.plot(x, f2)
ax.plot(x, f3)
ax.plot(x, f4)
ax.plot(x, f5)
ax.plot(x, f6)

ax.set_xticks(range(-10, 10))
ax.set_yticks(range(0, 2))
ax.set_xlabel('x')
ax.set_ylabel('f(x)')
plt.show()