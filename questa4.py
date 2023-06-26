import numpy as np

def calcular_intervalo_decrescimento(matriz_leslie):
    frações = np.linspace(0, 1, 1000)  # Intervalo de frações de 0 a 1
    autovalores_dominantes = []

    for f in frações:
        matriz_modificada = matriz_leslie.copy()
        matriz_modificada[0, :] *= (1 - f)  # Reduz a taxa de nascimento por faixa etária

        autovalor_dominante = np.max(np.abs(np.linalg.eigvals(matriz_modificada)))
        autovalores_dominantes.append(autovalor_dominante)

    # Encontra o intervalo em que o autovalor dominante é menor que 1
    intervalo_decrescimento = [frações[i] for i, autovalor in enumerate(autovalores_dominantes) if autovalor < 1]

    return intervalo_decrescimento

# Exemplo de uso:
matriz_exemplo = [
    [0.0, 0.0, 0.5, 0.8, 0.3, 0.0],
    [0.8, 0.0, 0.0, 0.0, 0.0, 0.0],
    [0.0, 0.9, 0.0, 0.0, 0.0, 0.0],
    [0.0, 0.0, 0.9, 0.0, 0.0, 0.0],
    [0.0, 0.0, 0.0, 0.8, 0.0, 0.0],
    [0.0, 0.0, 0.0, 0.0, 0.3, 0.0]
]

intervalo_decrescimento = calcular_intervalo_decrescimento(matriz_exemplo)
print("Intervalo de frações para decréscimo da população:", intervalo_decrescimento)