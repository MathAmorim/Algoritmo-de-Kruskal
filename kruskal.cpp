#include <bits/stdc++.h>
using namespace std;

// Estrutura para representar uma aresta
struct Aresta {
  int origem;
  int destino;
  int peso;
};

// Função para comparar arestas por peso
bool compararArestas(Aresta a1, Aresta a2) {
  return a1.peso < a2.peso;
}

// Função para encontrar o pai de um nó no conjunto de disjuntos
int encontrarPai(int conjunto[], int node) {
  if (conjunto[node] == node) {
    return node;
  } else {
    return encontrarPai(conjunto, conjunto[node]);
  }
}

// Função para unir dois conjuntos de disjuntos
void unirConjuntos(int conjunto[], int conjunto1, int conjunto2) {
  int paiConjunto1 = encontrarPai(conjunto, conjunto1);
  int paiConjunto2 = encontrarPai(conjunto, conjunto2);
  conjunto[paiConjunto2] = paiConjunto1;
}

// Função para implementar o algoritmo de Kruskal
void algoritmoKruskal(vector<Aresta>& arestas, int numVertices) {
  // Ordenar as arestas por peso crescente
  sort(arestas.begin(), arestas.end(), compararArestas);

  // Criar um conjunto de disjuntos para armazenar os componentes conectados
  int conjunto[numVertices];
  for (int i = 0; i < numVertices; i++) {
    conjunto[i] = i;
  }

  // Árvore geradora mínima (MST)
  vector<Aresta> mst;
  int pesoTotalMST = 0;

  for (Aresta aresta : arestas) {
    int paiOrigem = encontrarPai(conjunto, aresta.origem);
    int paiDestino = encontrarPai(conjunto, aresta.destino);

    // Verificar se a aresta cria um ciclo
    if (paiOrigem != paiDestino) {
      // Adicionar a aresta à MST
      mst.push_back(aresta);
      pesoTotalMST += aresta.peso;

      // Unir os conjuntos dos vértices
      unirConjuntos(conjunto, paiOrigem, paiDestino);
    }
  }

  // Imprimir a MST
  cout << "Árvore Geradora Mínima:" << endl;
  for (Aresta aresta : mst) {
    cout << aresta.origem << " - " << aresta.destino << " (peso: " << aresta.peso << ")" << endl;
  }

  cout << "Peso total da MST: " << pesoTotalMST << endl;
}

int main() {
  // Ler o número de vértices e arestas
  int numVertices, numArestas;
  cin >> numVertices >> numArestas;

  // Ler as arestas
  vector<Aresta> arestas(numArestas);
  for (int i = 0; i < numArestas; i++) {
    cin >> arestas[i].origem >> arestas[i].destino >> arestas[i].peso;
  }

  // Executar o algoritmo de Kruskal
  algoritmoKruskal(arestas, numVertices);

  return 0;
}
