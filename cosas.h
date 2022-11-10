#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
    int s;
    int t;
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
                canvas->FillEllipse(Brushes::Red,x, y, 5, 5);
            else if (i == cbDestino->SelectedIndex)
                canvas->FillEllipse(Brushes::Blue,x, y, 5, 5);
            else
                canvas->DrawEllipse(Pens::Black,x, y, 5, 5);
            
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
    void actualizarCombobox(ComboBox^ cbPartida, ComboBox^ cbDestino) {
        for (int i = 0; i < estaciones.size(); i++) {
            cbPartida->Items->Add(to_String(estaciones[i].getNombre()));
            cbDestino->Items->Add(to_String( estaciones[i].getNombre()));
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
    void dijkstra(ComboBox^ cbPartida) {
        vector<float> distancias;
        vector<bool> pasos;
        for (int i = 0; i < estaciones.size(); i++) {
            distancias.push_back(999999999.0f);
            pasos.push_back(false);
        }
        distancias[cbPartida->SelectedIndex] = 0;

        for (int i = 0; i < estaciones.size()-1; i++) {
            int x = distancia_minima(distancias, pasos);
            pasos[x] = true;
            for (int j = 0; j < estaciones.size(); j++) {
                if (!pasos[j] && matriz[x][j] && distancias[x] != 999999999.0f && distancias[x] + matriz[x][j] < distancias[j])
                    distancias[j] = distancias[x] + matriz[x][j];
            }
        }
        cout << "Estacion      Tiempo en minutos de la estacion" << endl;
        for (int i = 0; i < estaciones.size();i++) {
            cout << estaciones[i].getNombre() << "    " << distancias[i]<<endl;
        }
    }
};