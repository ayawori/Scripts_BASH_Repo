import numpy as np
from scipy.integrate import odeint
import matplotlib.pyplot as plt

# Total population, N.
N = 269728
# Initial number of infected and recovered individuals, I0 and R0.
I0, R0 = 1, 0
# Everyone else, S0, is susceptible to infection initially.
S0 = N - I0 - R0
# Contact rate, beta, and mean recovery rate, gamma, (in 1/days).
beta, gamma = 0.5, 1/10 
beta2 = 2.0
beta3 = 0.2
# A grid of time points (in days)
t = np.linspace(0, 365, 365)

# The SIR model differential equations.
def deriv(y, t, N, beta, gamma):
    S, I, R = y
    dSdt = -beta * S * I / N
    dIdt = beta * S * I / N - gamma * I
    dRdt = gamma * I
    return dSdt, dIdt, dRdt

# Initial conditions vector
y0 = S0, I0, R0
# Integrate the SIR equations over the time grid, t.
ret = odeint(deriv, y0, t, args=(N, beta, gamma))
ret2 = odeint(deriv, y0, t, args=(N, beta2, gamma))
ret3 = odeint(deriv, y0, t, args=(N, beta3, gamma))
S, I, R = ret.T
S2, I2, R2 = ret2.T
S3, I3, R3 = ret3.T

# Plot the data on three separate curves for S(t), I(t) and R(t)
fig = plt.figure(facecolor='w')
ax = fig.add_subplot(111, facecolor='#dddddd', axisbelow=True)
#ax.plot(t, S, 'b', alpha=0.5, lw=2, label='Susceptible')

ax.plot(t, I3, 'g', alpha=0.5, lw=2, label='Total Inf(R0=0.1)')
ax.plot(t, I3*0.65, 'b', alpha=0.5, lw=2, label='Inf(R0=0.1, sympto)')
ax.plot(t, I3*0.35, 'r', alpha=0.5, lw=2, label='Inf(R0=0.1, asympto)')

#ax.plot(t, I2*0.65, 'y', alpha=0.5, lw=2, label='Infected(R0=2.0)')
#ax.plot(t, I3*0.65, 'b', alpha=0.5, lw=2, label='Infected(R0=0.1)')
#ax.plot(t, R, 'g', alpha=0.5, lw=2, label='Recovered with immunity')
ax.set_xlabel('Time /days')
ax.set_ylabel('Total Population (269728)')
ax.set_ylim(0,50000)
ax.yaxis.set_tick_params(length=0)
ax.xaxis.set_tick_params(length=0)
ax.grid(b=True, which='major', c='w', lw=2, ls='-')
legend = ax.legend()
legend.get_frame().set_alpha(0.5)
for spine in ('top', 'right', 'bottom', 'left'):
    ax.spines[spine].set_visible(False)
plt.show()
