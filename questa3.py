import numpy as np

def autovalor_dominante(matriz_leslie):
    matriz_leslie = np.array(matriz_leslie)
    autovalores, _ = np.linalg.eig(matriz_leslie)
    autovalor_dominante = max(autovalores)
    return autovalor_dominante


matriz_leslie = [
    [0.0, 0.0, 0.5, 0.8, 0.3, 0.0],
    [0.8, 0.0, 0.0, 0.0, 0.0, 0.0],
    [0.0, 0.9, 0.0, 0.0, 0.0, 0.0],
    [0.0, 0.0, 0.9, 0.0, 0.0, 0.0],
    [0.0, 0.0, 0.0, 0.8, 0.0, 0.0],
    [0.0, 0.0, 0.0, 0.0, 0.3, 0.0]
]

autovalor_dominante = autovalor_dominante(matriz_leslie)
print("Autovalor dominante:", autovalor_dominante)