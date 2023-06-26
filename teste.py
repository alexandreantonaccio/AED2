import numpy as np

matriz_leslie = np.array([[0.0, 0.0, 0.5, 0.8, 0.3, 0.0],
                          [0.8, 0.0, 0.0, 0.0, 0.0, 0.0],
                          [0.0, 0.9, 0.0, 0.0, 0.0, 0.0],
                          [0.0, 0.0, 0.9, 0.0, 0.0, 0.0],
                          [0.0, 0.0, 0.0, 0.8, 0.0, 0.0],
                          [0.0, 0.0, 0.0, 0.0, 0.3, 0.0]])

autovalores, autovetores = np.linalg.eig(matriz_leslie)
maior_autovalor = max(autovalores)
taxa_liquida_reproducao = maior_autovalor

indice_autovalor = np.where(np.isclose(autovalores, maior_autovalor))[0][0]
autovetor_especifico = autovetores[:, indice_autovalor]

print(maior_autovalor)
print(autovetor_especifico)
