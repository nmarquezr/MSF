# wave_simulation.py

import numpy as np
from scipy.special import jn
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import rc
rc('font',**{'family':'serif','serif':['Times New Roman']})
rc('text', usetex=True)
from numba import jit
import imageio
import os

@jit(nopython=True)
def propagate_wave_numba(u, nt, nx, dx, dy, cx, cy, r, c, dt):
    for t in range(1, nt - 1):
        for i in range(1, nx - 1):
            for j in range(1, nx - 1):
                if (i*dx - cx)**2 + (j*dy - cy)**2 < r**2:
                    u[i,j,t+1] = (2 * u[i,j,t] - u[i,j,t-1] +
                                  c**2 * dt**2 * (u[i+1,j,t] - 2 * u[i,j,t] + u[i-1,j,t]) / dx**2 +
                                  c**2 * dt**2 * (u[i,j+1,t] - 2 * u[i,j,t] + u[i,j-1,t]) / dy**2)
    return u

class WaveSimulation:
    def __init__(self, Lx=10, T=5, nx=500, c=2.5):
        self.Lx = Lx
        self.Ly = Lx
        self.T = T
        self.nx = nx
        self.ny = nx
        self.c = c
        self.dx = Lx / (nx - 1)
        self.dy = Lx / (nx - 1)
        self.safety_factor = np.sqrt(0.5) * 0.9
        self.dt = min(self.dx, self.dy) / c * self.safety_factor
        self.nt = int(T / self.dt) + 1
        self.u = np.zeros((nx, nx, self.nt))
        self.x = np.linspace(0, Lx, nx)
        self.y = np.linspace(0, Lx, nx)
        self.X, self.Y = np.meshgrid(self.x, self.y)
        self.cx, self.cy = Lx/2, Lx/2 #Centro de la membrana
        self.x0, self.y0 = Lx/2, Lx/2 #Centro de la onda
        self.r = Lx/2 
        self.sigma = 0.25
        self.initialize_wave()

# Función externa que realiza la propagación de la onda, decorada con @jit para compilación con Numba


    def initialize_wave(self):
        from scipy.special import j0
        
        for i in range(self.nx):
            for j in range(self.ny):
                self.u[i, j, 0] = j0(np.sqrt((self.x[i] - self.x0)**2 + (self.y[j] - self.y0)**2) / self.sigma)
        self.u[:,:,1] = self.u[:,:,0]
        return self.u
    
    
    def propagate_wave(self):
        # Llama a la función externa, pasando los atributos necesarios como argumentos
        self.u = propagate_wave_numba(self.u, self.nt, self.nx, self.dx, self.dy, self.cx, self.cy, self.r, self.c, self.dt)


    def simulate(self):
        self.propagate_wave()
        D = np.sqrt((self.X - self.cx)**2 + (self.Y - self.cy)**2)
        for t in range(self.nt):
            mask = D >= self.r
            self.u[:,:,t][mask] = np.nan


    def generate(self, v_name='wave_simulation'):
        filenames = []
        for t in range(self.nt):
            fig = plt.figure(figsize=(10, 10))
            ax = fig.add_subplot(111, projection='3d')
            ax.set_title(f'$t$: {t * self.dt:.2f}', fontsize=35)
            ax.set_xlabel(r'$x$')
            ax.set_ylabel(r'$y$')
            ax.set_zlabel(r'$u$')
            surf = ax.plot_surface(self.X, self.Y, self.u[:,:,t], cmap='plasma', vmin=-0.25, vmax=1.)
            ax.set_zlim(-1.25, 1.25)
            cax=plt.axes([0.955, 0.4, 0.01, 0.25])
            cax.tick_params(labelsize=20)
            plt.colorbar(surf,cax=cax, orientation='vertical', ticks=[-1, 0, 1])
            
            frame_filename = f'frames/frame_{t}.png'
            plt.savefig(frame_filename)
            filenames.append(frame_filename)
            plt.close()
        os.system(f"ffmpeg -framerate 30 -i frames/frame_%d.png -c:v libx264 -r 60 -pix_fmt yuv420p {v_name}.mp4")  


        for filename in filenames:
            os.remove(filename)
