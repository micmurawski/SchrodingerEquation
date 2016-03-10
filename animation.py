#from __future__ import divsion
#from __future__ import print_function

import glob
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation as anim
import scipy.optimize as o
import scipy.special as s
from scipy.fftpack import *

Nx = 100
data = np.loadtxt('output')
print(data.shape)
print('number of frames in file:',data.shape[0]/Nx)


frames_num = data.shape[0]/Nx -1
x = np.linspace(0,1,Nx)
t = np.linspace(0,frames_num,frames_num+1)
X, T = np.meshgrid(x,t)
#data = np.reshape(data,X.shape)


density = np.reshape(data[:,0]**2+data[:,1]**2 ,X.shape)
re_psi = np.reshape(data[:,0],X.shape)
im_psi = np.reshape(data[:,1],X.shape)

print(X.shape)
print(density.shape)

fig = plt.figure()
ax1 = fig.add_subplot(111,xlim=(0,1),ylim=(-3.,3.))
psi_re, = ax1.plot([],[],label=r'$Re$ $\psi$')
psi_im, = ax1.plot([],[],label=r'$Im$ $\psi$')
psi2,   = ax1.plot([],[],label=r'$|\psi|$')
#phase,  = ax1.plot([],[],label=r'$arg \psi$')
ax1.grid(True)
ax1.legend()
#fig.show()

print(type(psi2))


def init():
    
    psi_re.set_data([],[])
    psi_im.set_data([],[])
    psi2.set_data([],[])
    #phase.set_data([],[])
    
    #return (psi_re,psi_im)
    #return psi2
    return (psi2,psi_re,psi_im)

def animate(i):
    #print('frame',i)
    
    psi_re.set_data(x,re_psi[i,:])
    psi_im.set_data(x,im_psi[i,:])
    #psi_im.set_data(x,data[i,:].imag)
    psi2.set_data(x,density[i,:])
    #phase.set_data([],[])
    #phase.set_data(x,np.angle(data[i,:]))
    
    #return (psi_re,psi_im)
    #return (psi2,phase)
    return (psi2,psi_re,psi_im)

# specify time steps and duration
#frames = data.shape[1]
#print("frames:",frames_num)

anim = anim.FuncAnimation(fig, animate, init_func=init, frames=int(frames_num), interval=200, blit=True)
plt.show()
