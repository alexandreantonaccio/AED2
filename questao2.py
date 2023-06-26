import numpy as np

def distribuicao_etaria(matriz_leslie, distribuicao_inicial, num_geracoes):
    matriz_leslie = np.array(matriz_leslie)
    distribuicao_atual = np.array(distribuicao_inicial)
    distribuicao_etaria = [distribuicao_atual.tolist()]
    
    for _ in range(num_geracoes):
        distribuicao_proxima = np.dot(matriz_leslie, distribuicao_atual)
        distribuicao_atual = distribuicao_proxima
        distribuicao_etaria.append(distribuicao_atual.tolist())
    
    return distribuicao_etaria

matriz_leslie = [
    [0.0, 0.0, 0.5, 0.8, 0.3, 0.0],
    [0.8, 0.0, 0.0, 0.0, 0.0, 0.0],
    [0.0, 0.9, 0.0, 0.0, 0.0, 0.0],
    [0.0, 0.0, 0.9, 0.0, 0.0, 0.0],
    [0.0, 0.0, 0.0, 0.8, 0.0, 0.0],
    [0.0, 0.0, 0.0, 0.0, 0.3, 0.0]
]

distribuicao_inicial = [50, 40, 30, 20, 10, 5]
num_geracoes = 101

distribuicao_etaria = distribuicao_etaria(matriz_leslie, distribuicao_inicial, num_geracoes)
for i, distribuicao in enumerate(distribuicao_etaria):
    if i >= 100 :
        print("Geração", i, ":", distribuicao)