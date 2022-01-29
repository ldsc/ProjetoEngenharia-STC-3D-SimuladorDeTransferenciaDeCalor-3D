import numpy as np
import matplotlib.pyplot as plt
import math

def temperature(x,t, alfa):
  Ti = 300
  Tf = 1000
  return Tf - (Tf - Ti)*math.erf(x/(2.0*math.sqrt(alfa*t)))

def maior_erro(x_sim, t_sim, t, alfa):
  T_analitico = []
  erro = []
  erro_relativo = []

  for x in x_sim:
    T_analitico.append(temperature(x, t, alfa))

  for i in range(len(t_sim)):
    erro.append(abs(t_sim[i] - T_analitico[i]))
    erro_relativo.append(erro[i]/t_sim[i]*100.0)
  print('tempo: ' + str(t))
  print('erro: ' + str(max(erro)))
  print('erro relativo: ' + str(max(erro_relativo)))

x = np.linspace(0,0.10374,100)
t = [50.0, 100.0]

k = 40
rho = 1600
cp = 4000
alfa = k/(rho*cp)

for _t in t:
  T = []
  for i in x:
    T.append(temperature(i, _t, alfa))
  plt.plot(x, T, 'bo')

###################
f = open('vertical100.000000.dat', 'r')
x_sim = []
t_sim = []
for i in f:
    split = i.split(';')
    x_sim.append(float(split[0]))
    t_sim.append(float(split[1].replace('\n', '').replace(' ', '')))

t_sim.sort(reverse=True)
for i in range(len(t_sim)):
    if t_sim[0] == 1000.0:
        t_sim.pop(0)
        x_sim.pop(-1)
    else:
        break
print('Tamanho: ' + str(max(x_sim) - min(x_sim)))
plt.plot(x_sim, t_sim, 'r+')
maior_erro(x_sim, t_sim, 100.0, alfa)

f = open('vertical50.000000.dat', 'r')
x_sim = []
t_sim = []
for i in f:
    split = i.split(';')
    x_sim.append(float(split[0]))
    t_sim.append(float(split[1].replace('\n', '').replace(' ', '')))

t_sim.sort(reverse=True)
for i in range(len(t_sim)):
    if t_sim[0] == 1000.0:
        t_sim.pop(0)
        x_sim.pop(-1)
    else:
        break
print('Tamanho: ' + str(max(x_sim) - min(x_sim)))
plt.plot(x_sim, t_sim, 'r+')
maior_erro(x_sim, t_sim, 50.0, alfa)


plt.legend(['Analitico - 100', 'Analitico - 50', 'Simulador - 100', 'Simulador - 50'])
plt.show()
