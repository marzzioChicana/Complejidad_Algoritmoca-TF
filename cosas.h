#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
using namespace std;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
string to_string(String^ txt1) {
    string txt2;
    for (int i = 0; i < txt1->Length; ++i) {
        txt2.push_back(char(txt1[i]));
    }
    return txt2;
}
String^ to_String(string txt1) {
    String^ txt2 = gcnew String("");
    for (int i = 0; i < txt1.size(); ++i) {
        txt2 += Char(txt1[i]);
    }
    return txt2;
}
class Estacion {
    string nombre;
    double coordx;
    double coordy;
public:
    Estacion(string _nombre) {
        nombre = _nombre;
        coordx = coordy = 0;
    }
    void setCoords(double x, double y) { coordx = x; coordy = y; }
    string getNombre() { return nombre; }
    double getX() { return coordx; }
    double getY() { return coordy; }
};
class GrafoEstaciones {
    vector<vector<long double>> matriz;
    vector<Estacion> estaciones;
    vector<Estacion> deletedEstaciones;
public:
    GrafoEstaciones() {
    }
    bool seRepiteEstacion(string estacion) {
        for (int i = 0; i < estaciones.size(); i++) {
            if (estacion == estaciones.at(i).getNombre())
                return true;
        }
        return false;
    }
    int indexByName(string nombre) {
        for (int i = 0; i < estaciones.size(); i++) {
            if (nombre == estaciones[i].getNombre()) {
                return i;
            }
        }
        return -1;
    }
    void agregarArista(string estacion_s, string estacion_d, long double tiempo) {
        if (!seRepiteEstacion(estacion_s)) {
            estaciones.push_back(Estacion(estacion_s));
            matriz.push_back(vector<long double>());
            for (int i = 0; i < matriz.size(); i++)
                matriz[i].push_back(0.0f);
            for (int i = 0; i < matriz.size() - 1; i++)
                matriz[matriz.size() - 1].push_back(0.0f);
        }
        if (!seRepiteEstacion(estacion_d)) {
            estaciones.push_back(Estacion(estacion_d));
            matriz.push_back(vector<long double>());
            for (int i = 0; i < matriz.size() - 1; i++)
                matriz[i].push_back(0.0f);
            for (int i = 0; i < matriz.size(); i++)
                matriz[matriz.size() - 1].push_back(0.0f);
        }
        matriz[indexByName(estacion_s)][indexByName(estacion_d)] = tiempo;
    }
    void mostrarListaDeAdyasencia() {
        for (int i = 0; i < matriz.size(); i++) {
            cout << i << ": " << estaciones[i].getNombre() << ": ";
            for (int j = 0; j < matriz.size(); j++) {
                if (matriz[i][j] != 0)
                    cout << " [" << estaciones[j].getNombre() << " - " << matriz[i][j] << " min]";
            }
            cout << endl;
            cout << endl;
            cout << endl;
        }
    }
    void leer() {
        ifstream file("help.csv");
        string anho, mes, e_p, e_d, stiempo;
        long double tiempo;
        int n = 0;
        getline(file, e_p);
        while (!file.eof()) {
            getline(file, anho, ',');
            getline(file, anho, ',');
            getline(file, mes, ',');
            getline(file, e_p, ',');
            getline(file, e_d, ',');
            getline(file, stiempo, '\n');
            if (stiempo != "") {
                tiempo = stold(stiempo);
                agregarArista(e_p, e_d, tiempo);
            }
            n++;
        }
    }
    void leercoords() {
        ifstream file("coords.txt");
        string nombre, sx, sy;
        double x, y;
        while (!file.eof()) {
            getline(file, nombre, ',');
            getline(file, sx, ',');
            getline(file, sy, '\n');
            x = stod(sx);
            y = stod(sy);
            cout << x << " " << y << endl;
            estaciones[indexByName(nombre)].setCoords(x+12.811326f,y+53.770425f);
        }
    }
    void graficar(Graphics^ canvas, ComboBox^ cbPartida, ComboBox^ cbDestino) {
        vector<pair<int, int>> puntos;
        for (int i = 0; i < estaciones.size(); i++) {
            int x, y;
            x = (estaciones[i].getY() * 24 * 1.269395) -1230;
            y = (720 - estaciones[i].getX() * 24 * 1.962618)+2455;
            puntos.push_back(pair<int, int>(x, y));
            if (i == cbPartida->SelectedIndex)
                canvas->FillEllipse(Brushes::Red,x-4, y-4, 8, 8);
            else if (i == cbDestino->SelectedIndex)
                canvas->FillEllipse(Brushes::Blue,x-4, y-4, 8, 8);
            else
                canvas->DrawEllipse(Pens::Black,x-4, y-4, 8, 8);
            
        }
        for (int i = 0; i < matriz.size(); i++)
        {
            for (int j = 0; j < matriz[i].size(); j++)
            {
                if (matriz[i][j] != 0) {
                    canvas->DrawLine(Pens::Black, Point(puntos[i].first, puntos[i].second), Point(puntos[j].first, puntos[j].second));
                }
            }
        }
    }
    void actualizarCombobox(ComboBox^ cbPartida, ComboBox^ cbDestino, ComboBox^ cbEstacionesND) {
        for (int i = 0; i < estaciones.size(); i++) {
            cbPartida->Items->Add(to_String(estaciones[i].getNombre()));
            cbDestino->Items->Add(to_String(estaciones[i].getNombre()));
            cbEstacionesND->Items->Add(to_String( estaciones[i].getNombre()));
        }
    }
    int distancia_minima(vector<float> distancias, vector<bool> pasos) {
        float minimo = 999999999.0f;
        int index;
        for (int i = 0; i < estaciones.size(); i++) {
            if (pasos[i] == false && distancias[i] <= minimo) {
                minimo = distancias[i];
                index = i;
            }
        }
        return index;
    }
    void printPath(int i, vector<int> parents, RichTextBox^ txtRuta, vector<Estacion> est)
    {
        if (i == -1) {
            return;
        }
        printPath(parents[i], parents, txtRuta, est);
        txtRuta->Text += to_String(est[i].getNombre());
        txtRuta->Text += "\n";
        cout << est[i].getNombre() << " -> ";
    }
    void heapify(vector<Estacion> est, int n, int i)
    {
        int largest = i; 
        int l = 2 * i + 1; 
        int r = 2 * i + 2; 
        if (l < n && indexByName(est[l].getNombre()) < indexByName( est[largest].getNombre()))
            largest = l;
        if (r < n && indexByName(est[r].getNombre()) < indexByName(est[largest].getNombre()))
            largest = r;
        if (largest != i) {
            Estacion aux = est[i];
            est[i] = est[largest];
            est[largest] = aux;
            heapify(est, n, largest);
        }
    }
    vector<Estacion> sort(vector<Estacion> _est) {
        vector<Estacion> est=_est;
        for (int i = est.size() / 2 - 1; i >= 0; i--)
            heapify(est, est.size(), i);
        for (int i = est.size() - 1; i >= 0; i--) {
            Estacion aux = est[0];
            est[0] = est[i];
            est[i] = aux;
            heapify(est, i, 0);
        }
        return est;
    }
    vector<vector<long double>> deleteVertex(vector<vector<long double>> matrix, int vertex, int* s, int* t) {
        vector<vector<long double>> m = matrix;
        if (vertex > m.size()) {
            return m;
        }
        else {
            m.erase(m.begin() + vertex);
            for (int i = 0; i < m.size(); i++) {
                m[i].erase(m[i].begin() + vertex);
            }
            if (*s >= vertex) {
                s -= 1;
            }
            if (*t >= vertex) {
                t -= 1;
            }
        }
        return m;
    }
    bool existPath(vector<vector<long double>> matrix, int s, int t)
    {
        vector<vector<bool>> mat;
        for (int i = 0; i < matrix.size(); i++) {
            mat.push_back(vector<bool>());
            for (int j = 0; j < matrix.size(); j++) {
                mat[i].push_back(false);
            }
        }
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.size(); j++) {
                if(matrix[i][j]>0)
                    mat[i][j] = true;
            }
        }
        for (int k = 0; k < matrix.size(); k++) {
            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < matrix.size(); j++) {
                    mat[i][j] = mat[i][j] || mat[i][k] && mat[k][j];
                }
            }
        }
        if (s >= matrix.size() || t >= matrix.size()) {
            return false;
        }
        if (mat[s][t])
            return true;
        return false;
    }
    void dijkstra2(ComboBox^ cbPartida, ComboBox^ cbDestino, RichTextBox^ txtRuta, Label^ tiempo) {
        int* s = new int(cbPartida->SelectedIndex);
        int* t =new int (cbDestino->SelectedIndex);
        if (s < 0 || t < 0)
            return;
        txtRuta->Text = "";
        vector<vector<long double>> matrix = matriz;
        vector<Estacion> est = estaciones;
        deletedEstaciones = sort(deletedEstaciones);
        for (int i = 0; i < deletedEstaciones.size(); i++) {
            matrix = deleteVertex(matrix, indexByName(deletedEstaciones[i].getNombre()),s,t);
        }
        int nVertices = matrix[0].size();
        vector<int> shortestDistances(nVertices);
        vector<bool> added(nVertices);
        if (!existPath(matrix, *s, *t)) {
            tiempo->Text = "No existe un camino";
            return;
        }

        for (int i = 0; i < nVertices; i++) {
            shortestDistances[i] = INT_MAX;
            added[i] = false;
        }

        shortestDistances[*s] = 0;
        vector<int> parents(nVertices);
        parents[*s] = -1;
        for (int i = 1; i < nVertices; i++) {
            int nearestVertex = -1;
            int shortestDistance = INT_MAX;
            for (int j = 0; j < nVertices; j++) {
                if (!added[j] && shortestDistances[j] < shortestDistance) {
                    nearestVertex = j;
                    shortestDistance = shortestDistances[j];
                }
            }
            added[nearestVertex] = true;
            for (int j = 0; j < nVertices; j++) {
                int edgeDistance = matrix[nearestVertex][j];
                if (edgeDistance > 0 && ((shortestDistance + edgeDistance) < shortestDistances[j])) {
                    parents[j] = nearestVertex;
                    shortestDistances[j] = shortestDistance + edgeDistance;
                }
            }
        }

        tiempo->Text = "";
        tiempo->Text += shortestDistances[*t];
        tiempo->Text += " min";
        for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++) {
            if (vertexIndex == *t) {
                cout << "\n" << est.at(*s).getNombre() << " -> ";
                cout << est.at(vertexIndex).getNombre() << " \t\t ";
                cout << shortestDistances[vertexIndex] << endl;
                printPath(vertexIndex, parents, txtRuta, est);
            }
        }
    }
    void eliminarEstacion(ComboBox^ cbEstacionesND, RichTextBox^ txtRuta) {
        deletedEstaciones.push_back(Estacion(to_string(cbEstacionesND->Text)));
        txtRuta->Text = "";
        for (int i = 0; i < deletedEstaciones.size(); i++) {
            txtRuta->Text += to_String(deletedEstaciones[i].getNombre());
            txtRuta->Text += "\n";
        }
    }
};