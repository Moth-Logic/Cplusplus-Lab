#include <iostream>
#include <string>
#include <limits>
#include "Clist.h"
#include "CircleList.h"
#include "DCircleList.h"

struct Persona {
    std::string nombre;
    bool pieDerecho;

    Persona(const std::string& n = "", bool pd = true)
        : nombre(n), pieDerecho(pd) {
    }
};

std::ostream& operator<<(std::ostream& os, const Persona& p) {
    os << p.nombre << " ("
        << (p.pieDerecho ? "pie derecho" : "pie izquierdo") << ")";
    return os;
}

void limpiarBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int n;
    std::cout << "Cantidad de personas: ";
    std::cin >> n;
    limpiarBuffer();

    Clist<Persona>* lista = nullptr;

    int tipo;
    std::cout << "Tipo de lista:\n";
    std::cout << "1. CircleList (simple)\n";
    std::cout << "2. DCircleList (doble)\n";
    std::cout << "Opcion: ";
    std::cin >> tipo;
    limpiarBuffer();

    if (tipo == 1) {
        lista = new CircleList<Persona>();
    }
    else {
        lista = new DCircleList<Persona>();
    }

    for (int i = 0; i < n; i++) {
        std::string nombre;
        std::cout << "Nombre de la persona " << (i + 1) << ": ";
        std::getline(std::cin, nombre);
        lista->insertBack(Persona(nombre, true));
    }

    int modo;
    std::cout << "Modo:\n";
    std::cout << "1. Regular (siempre izquierda)\n";
    std::cout << "2. Dirigido\n";
    std::cout << "Opcion: ";
    std::cin >> modo;
    limpiarBuffer();

    std::cout << "\nLista inicial:\n";
    lista->print();

    int ronda = 1;

    while (lista->getSize() > 1) {
        std::cout << "\n--- Ronda " << ronda << " ---\n";

        bool izquierda = true;

        if (modo == 2) {
            int dir;
            std::cout << "Direccion del conteo:\n";
            std::cout << "1. Izquierda (horario)\n";
            std::cout << "2. Derecha (antihorario)\n";
            std::cout << "Opcion: ";
            std::cin >> dir;
            limpiarBuffer();
            izquierda = (dir == 1);
        }

        // La rima tiene 9 partes => 8 saltos
        for (int i = 0; i < 8; i++) {
            if (izquierda) {
                lista->next();
            }
            else {
                lista->previous();
            }
        }

        Persona elegida = lista->getFront();

        std::cout << "Conteo termina en: " << elegida.nombre << "\n";
        std::cout << "Estado de la lista:\n";
        lista->print();

        if (elegida.pieDerecho) {
            // Cambia de pie
            Persona p = lista->remove();
            p.pieDerecho = false;
            lista->insert(p);
            lista->next(); // el siguiente conteo inicia con la persona siguiente
            std::cout << p.nombre << " cambia de pie.\n";
        }
        else {
            // Sale del circulo
            Persona p = lista->remove();
            std::cout << p.nombre << " sale del circulo.\n";
        }

        std::cout << "Lista despues de la ronda:\n";
        lista->print();

        ronda++;
    }

    Persona ganadora = lista->getFront();
    std::cout << "\nLa persona elegida es: " << ganadora.nombre << std::endl;

    delete lista;
    return 0;
}