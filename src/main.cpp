/**
 * @file main.cpp
 * @author Óscar Ignacio Pozo Fernández
 * 
 * @brief Fichero principal de la práctica 
 *        'Sistemas de recomendación. Métodos de Filtrado Colaborativo'
 *        de la asignatura: 'Gestión del Conocimiento en las Organizaciones'
 * 
 * @version 0.2
 * @date 2022-10-21
 */

#include <bits/stdc++.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <utility>  // std::pair


void imprimirMatriz(std::vector<std::vector<char>> matrix) {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void imprimirMatriz(std::vector<std::vector<float>> matrix) {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

std::vector<std::vector<float>> crearMatrizSimilitudes(std::vector<std::vector<char>> &matrixToCopy) {
  std::vector<std::vector<float>> matrizNula;
  for (int i = 0; i < matrixToCopy.size(); i++) {
    std::vector<float> fila;
    for (int j = 0; j < matrixToCopy.size(); j++) {
      fila.push_back(0.0);
    }
    matrizNula.push_back(fila);
  }
  return matrizNula;
}

std::vector<std::vector<char>> readFromFile(std::string fichero) {
  std::vector<std::vector<char>> fileMatrix;
  std::ifstream myfile(fichero);
  std::string linea;

  /**
   * @brief Leemos el fichero línea por línea, almacenamos los caracteres en un string cuando 
   * terminamos de leer la línea, almacenamos el string en la matriz y leemos la siguiente línea.
   */
  if (myfile.is_open()) {
    while (std::getline(myfile, linea)) {
      std::vector<char> fila;
      for (int i = 0; i < linea.size(); i++) {
        if (linea[i] != ' ') {
          fila.push_back(linea[i]);
        }
      }
      fileMatrix.push_back(fila);
    }
    myfile.close();
  } else {
    std::cout << "Fallo al abrir el fichero. El fichero: " << fichero << " no se pudo abrir o no existe." << std::endl;
    std::exit(104);
  }
  return fileMatrix;
};

float mediaUserRatings(std::vector<char> userRatings) {
  float sumatorio = 0, numeroRatings = 0;
  for (int i = 0; i < userRatings.size(); i++) {
    if (userRatings[i] != '-') {
      int sumatorio = sumatorio + (int)userRatings[i];
      numeroRatings++;
    }
  }
  return sumatorio / numeroRatings;
}

std::vector<std::vector<char>> valoresComunes(std::vector<char> userRatingsA, std::vector<char> userRatingsB) {
  std::vector<std::vector<char>> ratingReturnValues;
  std::vector<char> ratingComunesA;
  std::vector<char> ratingComunesB;
  for (int i = 0; i < userRatingsA.size(); i++) {
    if (userRatingsA[i] != '-' && userRatingsB[i] != '-') {
      ratingComunesA.push_back(userRatingsA[i]);
      ratingComunesB.push_back(userRatingsB[i]);
    }
  }
  ratingReturnValues.push_back(ratingComunesA);
  ratingReturnValues.push_back(ratingComunesB);
  return ratingReturnValues;
}

float correlacionPearson(std::vector<char> userRatingsA, std::vector<char> userRatingsB) {
  std::vector<std::vector<char>> valores = valoresComunes(userRatingsA, userRatingsB);
  int mediaUserA = mediaUserRatings(valores[0]);
  int mediaUserB = mediaUserRatings(valores[1]);

  // Valores fórmula de Correlación de Pearson
  float numerador = 0, sumatorioUserA = 0, sumatorioUserB = 0;
  for (int i = 0; i < userRatingsA.size(); i++) {
    if (userRatingsA[i] != '-' && userRatingsB[i] != '-') {
      numerador += ((userRatingsA[i] - mediaUserA) * (userRatingsB[i] - mediaUserB));
      sumatorioUserA += pow(userRatingsA[i] - mediaUserA, 2);
      sumatorioUserB += pow(userRatingsB[i] - mediaUserB, 2);
    }
  }
  float resultado = (numerador / (sqrt(sumatorioUserA) * sqrt(sumatorioUserB))); 
  return resultado;
}

int distanciaEuclidea(std::vector<char> userRatingsA, std::vector<char> userRatingsB) {
  int sumatorio = 0;
  for (int i = 0; i < userRatingsA.size(); i++) {
    if (userRatingsA[i] != '-' && userRatingsB[i] != '-') {
      sumatorio += pow(userRatingsA[i] - userRatingsB[i], 2);
    }
  }
  return sumatorio;
}

float distanciaCoseno(std::vector<char> userRatingsA, std::vector<char> userRatingsB) {
  int numerador = 0, sumatorioUserA = 0, sumatorioUserB = 0;
  for (int i = 0; i < userRatingsA.size(); i++) {
    numerador += (userRatingsA[i] * userRatingsB[i]);
    sumatorioUserA += pow(userRatingsA[i], 2);
    sumatorioUserB += pow(userRatingsB[i], 2);
  }
  float resultado = numerador / (sqrt(sumatorioUserA) * sqrt(sumatorioUserB)); 
  return resultado;
}

void calcularSimilitudes(std::vector<std::vector<char>> matrizRatings, std::vector<std::vector<float>> &matrizSimilitudes, std::string metodo) {
  if (metodo == "Pearson") {
    for (int i = 0; i < matrizRatings.size(); i++) {
      for (int j = 0; j < matrizRatings.size(); j++) {
        matrizSimilitudes[i][j] = correlacionPearson(matrizRatings[i], matrizRatings[j]);
      }
    }
  } else if (metodo == "Coseno") {
    for (int i = 0; i < matrizRatings.size(); i++) {
      for (int j = 0; j < matrizRatings.size(); j++) {
        matrizSimilitudes[i][j] = distanciaCoseno(matrizRatings[i], matrizRatings[j]);
      }
    }
  } else if (metodo == "Euclidea") {
    for (int i = 0; i < matrizRatings.size(); i++) {
      for (int j = 0; j < matrizRatings.size(); j++) {
        matrizSimilitudes[i][j] = distanciaEuclidea(matrizRatings[i], matrizRatings[j]);
      }
    }
  } else {
    std::cout << "Fallo en la elección de Similitud" << std::endl;
  }
}

std::vector<int> calcularPredicciones(std::vector<std::vector<char>> matrizRatings) {
  std::vector<int> usuariosConPrediccion;
  for (int i = 0; i < matrizRatings.size(); i++) {
    for (int j = 0; j < matrizRatings[0].size(); j++) {
      if (matrizRatings[i][j] == '-') {
        usuariosConPrediccion.push_back(i);
      }
    }
  }
  return usuariosConPrediccion;
}

int getIndex(std::vector<float> userSimilarities, float valor) {
  auto it = std::find(userSimilarities.begin(), userSimilarities.end(), valor);
  if (it != userSimilarities.end()) {
    int index = it - userSimilarities.begin();
    return index;
  }
  return -1;
}

std::vector<std::pair<int, float>> calcularVecinos(std::vector<std::vector<char>> matriz, std::vector<char> userRating, std::vector<std::vector<float>> matrizSimilitudes, int numVecinos, std::string metodo, int posicionUsuario, int posicionCalcular) {
  std::vector<std::pair<int, float>> retornoDeVecinos;
  std::vector<int> vecinosCoincidentes;
  std::vector<float> userSimilitudes = matrizSimilitudes[posicionUsuario];
  std::vector<float> userSimilitudes2 = userSimilitudes;
  std::vector<float> similitudesOrdenadas = userSimilitudes;

  // Escogemos los numVecinos con mayor afinidad y trabajamos sobre ellos.
  // Para Pearson y Distancia Coseno ordenamos de mayor a menor.
  std::sort(similitudesOrdenadas.begin(), similitudesOrdenadas.end(), std::greater<float>());
  if (metodo == "Euclidea") {
    // Para la distancia Euclídea ordenamos de menor a mayor.
    std::sort(similitudesOrdenadas.begin(), similitudesOrdenadas.end(), std::less<float>());
  }

  for (int i = 0; i < similitudesOrdenadas.size(); i++) {
    if (vecinosCoincidentes.size() >= numVecinos) break; // Si llegamos al número de vecinos, paramos de añadir
    int usuario = getIndex(userSimilitudes, similitudesOrdenadas[i]);
    userSimilitudes[usuario] = 0;  // Descartamos el usuario ya escogido
    if (matriz[usuario][posicionCalcular] != '-') {
      vecinosCoincidentes.push_back(usuario);
    }
  }

  for (int i = 0; i < vecinosCoincidentes.size(); i++) {
    float valorSimilitud = userSimilitudes2[vecinosCoincidentes[i]];
    std::pair<int, float> userConSuSimilitud = std::make_pair(vecinosCoincidentes[i], valorSimilitud);
    retornoDeVecinos.push_back(userConSuSimilitud);
  }
  return retornoDeVecinos;
}

int prediccionSimple(std::vector<std::vector<char>> matriz, int coordenadaX, int coordenadaY, std::vector<std::pair<int, float>> userConSuSimilitud) {
  float numerador = 0, denominador = 0;
  for (int i = 0; i < userConSuSimilitud.size(); i++) {
    float valorSimilitud = userConSuSimilitud[i].second;
    float calificacionVecinoAlItem = matriz[userConSuSimilitud[i].first][coordenadaY] - '0';  // El -'0' es necesario para que lo reciba correctamente como número
    numerador = numerador + (valorSimilitud * calificacionVecinoAlItem);
    denominador += std::abs(valorSimilitud);
  }
  int resultado = (numerador / denominador);
  char resultadoChar = resultado + '0';
  return resultadoChar;
}

char prediccionDiferenciaMedia(std::vector<std::vector<char>> matriz, int coordenadaX, int coordenadaY, std::vector<std::pair<int, float>> userConSuSimilitud) {
  int mediaUsuarioPredecir = mediaUserRatings(matriz[coordenadaX]);
  float numerador = 0, denominador = 0;
  for (int i = 0; i < userConSuSimilitud.size(); i++) {
    float valorSimilitud = userConSuSimilitud[i].second;
    float calificacionVecinoAlItem = matriz[userConSuSimilitud[i].first][coordenadaY] - '0';
    float mediaVecino = mediaUserRatings(matriz[userConSuSimilitud[i].first]);
    numerador += (valorSimilitud * (calificacionVecinoAlItem - mediaVecino) );
    denominador += std::abs(valorSimilitud);
  }
  int resultado = mediaUsuarioPredecir + (numerador / denominador);
  char resultadoChar = resultado + '0';
  return resultadoChar;
}

std::vector<std::vector<char>> ejecutar(std::vector<std::vector<char>> matriz, std::vector<std::vector<float>> matrizSimilitudes, int numVecinos, std::string metodo, std::vector<int> usuariosConPrediccion, std::string tipoPrediccion) {
  std::vector<std::vector<char>> matrizFinal = matriz; 
  std::vector<std::pair<int, float>> userConSuSimilitud;

  int coordenadaX, coordenadaY;
  for (int i = 0; i < usuariosConPrediccion.size(); i++) {
    coordenadaX = usuariosConPrediccion[i];
    for (int j = 0; j < matrizFinal[0].size(); j++) {
      coordenadaY = j;
      if ( matrizFinal[coordenadaX][coordenadaY] == '-') {
        userConSuSimilitud = calcularVecinos(matriz, matriz[coordenadaX], matrizSimilitudes, numVecinos, metodo, coordenadaX, coordenadaY);    
        if (tipoPrediccion == "Simple") {
          matrizFinal[coordenadaX][coordenadaY] = prediccionSimple(matriz, coordenadaX, coordenadaY, userConSuSimilitud);
        } else if (tipoPrediccion == "Media") {
          matrizFinal[coordenadaX][coordenadaY] = prediccionDiferenciaMedia(matriz, coordenadaX, coordenadaY, userConSuSimilitud);
        }
      }      
    }
  }
  return matrizFinal;
}

void comprobarArgumentos(std::string metrica, int vecinos, std::string prediccion) {
  if (metrica != "Pearson" && metrica != "Coseno" && metrica != "Euclidea") {
    std::cout << "La métrica elegida: " << metrica << " no es un tipo disponible.\nLas métricas disponibles son: Pearson, Coseno y Euclidea." << std::endl;
    std::exit(201);
  } else if (vecinos < 3 || vecinos > 100) {
    std::cout << "Fallo en el número de vecinos. Lo recomendable es escoger mínimo 3 vecinos para comparar y usted ha elegido: " << vecinos << std::endl;
    std::exit(202);
  } else if (prediccion != "Simple" && prediccion != "Media") {
    std::cout << "La predicción elegida: " << prediccion << " no es un tipo disponible.\nLas predicciones disponibles son: Simple y Media." << std::endl;
    std::exit(203);
  }
}

std::string seleccionarMatrizAleatoria() {
  std::vector<std::string> listOfMatrices;
  std::string path = "./ejemplos";
  for (const auto & entry : std::filesystem::directory_iterator(path)) {
    listOfMatrices.push_back(entry.path());
  }
  srand(time(0));
  int randomPosition = (rand() % listOfMatrices.size()) + 0;
  return listOfMatrices[randomPosition];
}

int main(int argc, char* argv[]) {
  std::string fichero = argv[1];    // Nombre del fichero ó Random
  std::string metrica = argv[2];    // Pearson, Coseno o Euclidea
  int vecinos = atoi(argv[3]);      // Nº de Vecinos
  std::string prediccion = argv[4]; // Predicción Simple o Diferencia de Media
  std::cout << "Argumentos de ejecución: " << fichero << " " << metrica << " " << vecinos << " " << prediccion << std::endl;

  comprobarArgumentos(metrica, vecinos, prediccion);
  if (fichero == "Random" || fichero == "random") {
    fichero = seleccionarMatrizAleatoria();
    std::cout << "Fichero seleccionado al azar: " << fichero << std::endl;
  }

  std::vector<std::vector<char>> matrizRatings = readFromFile(fichero);

  std::vector<int> usuariosConPrediccion = calcularPredicciones(matrizRatings);
  
  std::cout << "\nMatriz ratings original: " << std::endl;
  imprimirMatriz(matrizRatings);

  std::vector<std::vector<float>> matrizSimilitudes = crearMatrizSimilitudes(matrizRatings);

  calcularSimilitudes(matrizRatings, matrizSimilitudes, metrica);

  std::cout << "Matriz ratings similitudes: " << std::endl;
  imprimirMatriz(matrizSimilitudes);

  std::vector<std::vector<char>> matrizFinal = ejecutar(matrizRatings, matrizSimilitudes, vecinos, metrica, usuariosConPrediccion, prediccion);
  
  std::cout << "Matriz con las predicciones realizadas: " << std::endl;
  imprimirMatriz(matrizFinal);
}

