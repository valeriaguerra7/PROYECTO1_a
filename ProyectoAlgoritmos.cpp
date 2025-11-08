#include <iostream> //bibliotecas que se necesitan:
#include <cstdlib> // se usa para rand, srand y exit
#include <ctime> // se usa para time y la funcionalidad de los números aleatorios
using namespace std;

void menuAcciones(); // en esta parte decalro funciones :)
void mostrarRecursos();
void explorarPlaneta();
void repararNave();
void enviarSenales();
void eventoNocturno();
bool verificarCondiciones();

int combustible = 30; // Variables globales
int oxigeno = 50;
int suministros = 40;
int integridad_nave = 100;
int days = 0;

int main() {
    srand(time(0)); // este inicia el generador de los números aleatorios conforme al reloj
    cout << "|| BIENVENIDO CAPITAN ||\n";
    mostrarRecursos(); // Imprime los recursos actuales en nuestra pantalla
    while (true) { // este es un bucle, se repite hasta que algo no cumpla con las condiciones (break)
        menuAcciones(); // muestra el menú y ejecuta la acción escogida

        if (!verificarCondiciones()) break; // si ya se perdió o se gano, se sale del bucle

        eventoNocturno(); // cuando se hace de noche, sucede un evento aleatorio
        mostrarRecursos(); // imprime los recursos actuales en nuestra pantalla

        if (!verificarCondiciones()) break; // vuelve a revisar si se perdió o se ganó
    }
    return 0;
}

void mostrarRecursos() { // Imprime los recursos actuales en nuestra pantalla
    cout << "\n--- ESTADO ACTUAL DE LA NAVE ---" << endl;
    cout << "Combustible: " << combustible << " unidades" << endl;
    cout << "Oxigeno: " << oxigeno << " unidades" << endl;
    cout << "Suministros: " << suministros << " unidades" << endl;
    cout << "Integridad de la nave: " << integridad_nave << "%" << endl;
    cout << "Dias: " << days << "/10" << endl;
}

void explorarPlaneta() { //Realiza la exploración de un planeta
    cout << "\nExplorando planeta..." << endl;

    if (combustible < 15) { // Valida si el combustible es suficiente para la exploración
        cout << "No tienes suficiente combustible para explorar (necesitas 15 unidades)." << endl;
        return;
    }
    combustible -= 15; // gasta 15 unidades de combustible

    if ((rand() % 100) < 60) { // Genera un número entre 0 y 99 y si es menor a 60, encuentra oxigeno(60% de probabilidad)
        int oxigenoEncontrado = 20 + (rand() % 21); // genera un número entre 20 y 40 (cantidad de oxigeno encontrado)
        oxigeno += oxigenoEncontrado;
        cout << "Encontraste " << oxigenoEncontrado << " unidades de oxigeno." << endl;
    }

    if ((rand() % 100) < 25) { // Genera un número del 0 al 99 y si es menor a 25, se encuentra combustible (25% de probabilidad)
        int combustibleEncontrado = 10 + (rand() % 21); // genera un número entre 10 y 30 (cantidad de combustible encontrado)
        combustible += combustibleEncontrado;
        cout << "Encontraste " << combustibleEncontrado << " unidades de combustible." << endl;
    }

    if ((rand() % 100) < 50) { // Genera un número entre 0 y 99 y si es menor a 50, encuentra suministros (50% de probabilidad)
        int suministrosEncontrados = 30 + (rand() % 71); // Genera un número entre 30 y 100 (cantidad de suministros encontrados)
        suministros += suministrosEncontrados;
        cout << "Encontraste " << suministrosEncontrados << "unidades de suministros." << endl;
    }

    if ((rand() % 100) < 25) { // Genera un número entre 0 y 99 y si es menor a 25 se sufre una tormenta eléctrica (25% de probabilidad)
        int dano = 10 + (rand() % 11); // entre 10 y 20
        integridad_nave -= dano;
        cout << "Tormenta eléctrica: la nave perdio" << dano << "de integridad." << endl;
        if (integridad_nave < 0) integridad_nave = 0;
    }

    if ((rand() % 100) < 25) {  // Genera un número entre 0 y 99 y si es menor a 25 ocurre un aterrizaje forzado (25% de probabilidad)
        int dano = 10 + (rand() % 11); // Entre 10 y 20
        integridad_nave -= dano;
        cout << "Aterrizaje forzado: la nave sufrio " << dano << "de daño." << endl;
        if (integridad_nave < 0) integridad_nave = 0;
    }
    days++; // Incrementa 1 al valor de la variable "days"
}

void repararNave() { // Subproceso para reparar la nave
    cout << "\nReparando nave..." << endl;
    if (integridad_nave >= 100) { // Si la integridad de la nave esta perfecta no se puede realizar
        cout << "La nave ya está en perfecto estado (100% de integridad)." << endl;
        return;
    }

    int maxReparable = 100 - integridad_nave; // aqui calcula que tanto se puede reparar la nave
    int maxPosible = suministros / 10; // cada 1% cuesta 10 unidades
    cout << "Integridad actual: " << integridad_nave << "%" << endl;
    cout << "Suministros disponibles: " << suministros << " unidades" << endl;
    cout << "Puedes reparar hasta " << min(maxReparable, maxPosible) << "%" << endl;

    int porcentaje;
    cout << "¿Cuanto porcentaje deseas reparar?: ";
    cin >> porcentaje;

    if (porcentaje <= 0) { //verifica si el valor ingresado es un valor positivo
        cout << "Debes ingresar un valor positivo." << endl;
        return;
    }

    int costo = porcentaje * 10; // cada % cuesta 10 unidades

    if (costo > suministros) {
        cout << "No tienes suficientes suministros. Necesitas " << costo << " unidades." << endl;
        return;
    }

    if (integridad_nave + porcentaje > 100) { // si se intenda reparar más del 100%, se ajusta
        cout << "Ajuste automático: solo se reparará hasta el 100%." << endl;
        porcentaje = maxReparable;
        costo = porcentaje * 10;
    }

    suministros -= costo; // disminuyen los suministros y se reparan
    integridad_nave += porcentaje;
    if (integridad_nave > 100) integridad_nave = 100;
    cout << "Reparación completada. Integridad actual: " << integridad_nave << "%" << endl;
    days++; // avanza el día
}

void enviarSenales() { // Enviar señales
    cout << "\nEnviando señal..." << endl;
    int evento = rand() % 2; // puede ser 0 o 1 (50/50)

    if (evento == 0) {
        combustible += 20; // se obtienen 20 unidades de combsutible
        cout << "Recibiste ayuda y obtuviste 20 unidades de combustible." << endl;
    } else { // se resta un 15% de integridad y 20 unidades de suministros
        integridad_nave -= 15;
        suministros -= 20;
        if (suministros < 0) suministros = 0;
        cout << "Piratas espaciales atacaron tu nave (-15% integridad, -20 suministros)." << endl;
    }
    days++; // avanzas de día
}

void eventoNocturno() { // Evento nocturno
    cout << "\nHa pasado la noche. Dia " << days << endl;
    cout << "Consumo diario: -20 oxigeno, -30 suministros." << endl;

    oxigeno -= 20; // cada noche disminuye el oxígeno y suministros
    suministros -= 30;
    if (oxigeno < 0) oxigeno = 0;
    if (suministros < 0) suministros = 0;

    if ((rand() % 100) < 15) { // Evento aleatorio (15% de probabilidad)
        cout << "\n--- EVENTO NOCTURNO ---" << endl;
        int tipo = rand() % 3;

        if (tipo == 0) { // tormenta cósmica disminuye el oxígeno
            oxigeno -= 10;
            if (oxigeno < 0) oxigeno = 0;
            cout << "Tormenta cósmica: perdiste 10 unidades de oxígeno." << endl;

        } else if (tipo == 1) { // si el encuentro con los alienígenas es amistoso ganas combsutible, si no lo son pierdes un 10% de integridad
            cout << "Encuentro alienígenas detectados..." << endl;
            if (rand() % 2 == 0) {
                combustible += 20;
                cout << "Amistosos: recibiste 20 unidades de combustible." << endl;
            } else {
                integridad_nave -= 10;
                cout << "Hostiles: la nave perdió 10% de integridad." << endl;
            }

        } else { // campo de meteritos
            cout << "Campo de meteoritos detectado!" << endl;
            cout << "1. Maniobrar (gasta combustible)\n2. Recibir impacto (daña la nave)" << endl;
            int decision; // el jugador debe decidir entre maniobrar o recibir el impacto
            cin >> decision;

            if (decision == 1) { // gastas combustible
                int gasto = 10 + (rand() % 21); // entre 10 y 30
                combustible -= gasto;
                if (combustible < 0) combustible = 0;
                cout << "Maniobras evasivas: gastaste " << gasto << " unidades de combustible." << endl;
            } else { // pierdes integridad
                int danio = 15 + (rand() % 11); // entre 15 y 25
                integridad_nave -= danio;
                if (integridad_nave < 0) integridad_nave = 0;
                cout << "Impacto directo: perdiste " << danio << "% de integridad." << endl;
            }
        }
    }
}

bool verificarCondiciones() { // Verificar condiciones de la partida (si ganas o pierdes)
    if (days >= 10) { // Si sobreviviste los 10 días
        cout << "\n=== MISION COMPLETADA ===" << endl;
        cout << "Has sobrevivido 10 días en el espacio. ¡Felicidades Capitan" << endl;
        mostrarRecursos();
        return false;
    }

    if (integridad_nave <= 0) { // si la nave esta en mal estado
        cout << "\n=== GAME OVER ===" << endl;
        cout << "La nave ha sido destruida." << endl;
        mostrarRecursos();
        return false;
    }

    if (oxigeno <= 0) { // si te quedaste sin oxígeno
        cout << "\n=== GAME OVER ===" << endl;
        cout << "Te has quedado sin oxigeno." << endl;
        mostrarRecursos();
        return false;
    }

    if (combustible <= 0) { // si te quedaste sin combsutible
        cout << "\n=== GAME OVER ===" << endl;
        cout << "Te has quedado sin combustible." << endl;
        mostrarRecursos();
        return false;
    }
    return true; // si esta todo bien, continua el juego
}

void menuAcciones() { // Menú de acciones
    int op; // la opción que escoge le jugador
    bool opcionValida; // repite si escoge alguna opción invalida
    do {
        cout << "\n--- MENU DE ACCIONES ---" << endl;
        cout << "1. Explorar planeta" << endl;
        cout << "2. Reparar nave" << endl;
        cout << "3. Enviar senal" << endl;
        cout << "4. Rendirse" << endl;
        cout << "Selecciona una op: ";
        cin >> op;
        opcionValida = true;
        switch (op) {
            case 1: explorarPlaneta(); break;
            case 2: repararNave(); break;
            case 3: enviarSenales(); break;
            case 4:
                cout << "\nTe has rendido. GAME OVER." << endl;
                exit(0); //Termina el programa
            default:
                cout << "Op no valida. Intenta de nuevo." << endl;
                opcionValida = false;
                break;
        }
    } while (!'opcionValida); // se repite hasta que se escoja una opción valida
}
