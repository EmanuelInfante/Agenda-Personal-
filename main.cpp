#include <iostream>
#include <iomanip>//setpresition()

//Definimos si estamos en windows o linux para definir funcion d limpiar pantalla
#ifdef WIN32
    #define cls() system("cls");
#else
   #define cls() system("clear");
#endif // WIN32


using namespace std;


//Estructura para el contacto
struct Contacto
{
    string nombre;
    double telefono;
    string correoElectronico;

    //punteros para lista enlazada doble
    struct Contacto *siguienteElemento;
    struct Contacto *anteriorElemento;
};

//Prototipo de funciones
void solicitarDatosContacto(struct Contacto *&);
void insertarContacto(struct Contacto *&, struct Contacto *);
void eliminarContacto(struct Contacto *&);
struct Contacto *buscarContacto(struct Contacto *, string);
void mostrarContactos(struct Contacto *);
void mostrarDatosContacto(struct Contacto *);
string convertirStringMayuscula(string dato);
void eliminarMemoriaDinamica(struct Contacto *);

int main()
{
    cout << "Bienvenido a tu agenda personal." << endl << endl;

    struct Contacto *listaContactos = NULL;

    bool continuarCiclo = true;

    //Ciclo que se ejecuta siempre que no se oprima 4
    do
    {
        cout << "1) Añadir una nueva persona" << endl;
        cout << "2) Eliminar una persona" << endl;
        cout << "3) Mostrar persona(s)" << endl;
        cout << "4) Salir" << endl;

        cout << "Ingrese el número de la opción correspondiente: ";

        int opcion;
        cin >> opcion;
        cin.ignore();

        cls();

        switch(opcion)
        {
        case 1:
            solicitarDatosContacto(listaContactos);
            break;
        case 2:
            eliminarContacto(listaContactos);
            break;
        case 3:
            mostrarContactos(listaContactos);
            break;
        case 4:
            continuarCiclo = false;
            break;
        default:
            break;

        }

    }while(continuarCiclo);

    eliminarMemoriaDinamica(listaContactos);

    return 0;
}


void solicitarDatosContacto(struct Contacto *&Listacontactos)
{
    /*Función que se encarga de solicitar los datos del nuevo contacto, y
    llamar a la función para agregarlos en la lista enlazada*/
    struct Contacto *nuevoContacto = new Contacto();

    cout << "Ingrese el nombre del nuevo contacto: ";
    getline(cin, nuevoContacto ->nombre);

    cout << "Ingrese el número telefónico del contacto: ";
    cin >> nuevoContacto ->telefono ;
    cin.ignore();

    cout << "Ingrese el correo electrónico del usuario: ";
    getline(cin, nuevoContacto ->correoElectronico);

    //Llamamos a función que agregar de forma ordenada el contacto
    insertarContacto(Listacontactos, nuevoContacto);

}


void insertarContacto(struct Contacto *&listaContactos, struct Contacto *nuevoContacto)
{
    /*Función que se encarga de insertar contactos en la lista, de forma alfabética*/

    if(listaContactos == NULL)
    {
        //En caso de que no existan contactos, se crea uno en la lista
        nuevoContacto ->siguienteElemento = NULL;
        nuevoContacto ->anteriorElemento = NULL;
        listaContactos = nuevoContacto;
    }
    else if(listaContactos != NULL)
    {
        //aux que no ayudara a reorrer la lista
        struct Contacto *auxListaContactos = listaContactos;
        bool continuar = true;

        while(continuar)
        {
            for(int i = 0; i < int(auxListaContactos ->nombre.length()); i++)
            {
                /*Si la posicion de la letra actual es igual a la posicion de la letra actual del elemento de la lista, entonces se sigue ejecutando
                el ciclo*/

                if(int(convertirStringMayuscula(nuevoContacto ->nombre)[i]) == int(convertirStringMayuscula(auxListaContactos ->nombre)[i]) &&
                   int(auxListaContactos ->nombre.length()) -1 != i)
                    continue;


                else if(auxListaContactos ->siguienteElemento == NULL &&
                        (int(convertirStringMayuscula(nuevoContacto ->nombre)[i]) > int(convertirStringMayuscula(auxListaContactos ->nombre)[i]) ||
                            (int(auxListaContactos ->nombre.length()) - 1 == i &&
                                convertirStringMayuscula(nuevoContacto ->nombre)[i] == int(convertirStringMayuscula(auxListaContactos ->nombre)[i]))))
                {
                    /*Este caso se ejecuta si el elemento debe ser agregado en la ultima posicion de la lista, osea si el último elemento es NULL y:
                    -la ultima letra del contacto de la lista en el que se va es Mayor a la actual
                    -se encuentra en la ultima letra, son iguales y no hay mas letrar en la palabra de la lista, ejemplo: "Vi" y "Viviana"
                    siendo Vi el último de la lista, agregara a viviana despues de el, ya que la "i" s encuentra en la primera posición de ambas
                    pero no hay más letras para seguir verificando

                    el nuevo nombre empieza a apuntar a NULL*/
                    auxListaContactos ->siguienteElemento = nuevoContacto;
                    nuevoContacto ->anteriorElemento = auxListaContactos;
                    nuevoContacto ->siguienteElemento = NULL;
                    continuar = false;
                    break;
                }

                /*Si la posicion de la letra actual es mayor a la posicion de la letra actual del elemento de la lista, se detiene el ciclo y se
                pasa a la siguiente posición*/
                else if(int(convertirStringMayuscula(nuevoContacto ->nombre)[i]) > int(convertirStringMayuscula(auxListaContactos ->nombre)[i]))
                    break;


                else if(int(convertirStringMayuscula(nuevoContacto ->nombre)[i]) < int(convertirStringMayuscula(auxListaContactos ->nombre)[i]))
                {
                    //Verificamos si el nombre tiene una letra mas cernaca a la A, si es asi, entonces procedemos a agregar el elemento

                    //creamos un for, con el cual verificamos si

                    struct Contacto *auxListaContactos2 = auxListaContactos ->anteriorElemento;

                    if(auxListaContactos2 == NULL)
                    {
                        /*Agregamos el contacto, este caso se ejecuta si solo existe un elemento en la lista, osea si el primer elemento
                        de la lista, con su atributo "anterior" apunta a NULL. Y se agrega como primer elemento en la lista*/
                        listaContactos ->anteriorElemento = nuevoContacto;
                        nuevoContacto ->siguienteElemento = listaContactos;
                        nuevoContacto ->anteriorElemento = NULL;
                        listaContactos = listaContactos ->anteriorElemento;
                    }else
                    {
                        /*EN este caso se agrega si el elemento esta en la mitad, se cambian  los punteros del elemento anterior y siguente,
                        usando un puntero aux para cada elemento (anterior, siguiente) y asignando los valores correspondientes*/
                        auxListaContactos2 ->siguienteElemento = nuevoContacto;
                        auxListaContactos ->anteriorElemento = nuevoContacto;

                        nuevoContacto ->anteriorElemento = auxListaContactos2;
                        nuevoContacto ->siguienteElemento = auxListaContactos;
                    }
                    continuar = false;
                    break;

                }
            }
            //Avanzamos en la lista
            auxListaContactos = auxListaContactos ->siguienteElemento;
        }

    }
    cls();
    cout << "Agregado correctamente" << endl << endl;

}


void eliminarContacto(struct Contacto *&listaContactos)
{
    /*Función que se encarga pedir los datos del contacto a eliminar, solicita a buscarContacto() la existencia del mismo, y lo elimina*/
    cls();

    cout << "Ingresa el nombre del contacto a eliminar(no se toman Mayúsculas o Minúsculas): ";
    string nombreEliminar;
    getline(cin, nombreEliminar);

    //BUscamos el contacto
    struct Contacto *contactoBuscado = buscarContacto(listaContactos, nombreEliminar);

    //Si el contacto no existe, retornamos la función
    if(contactoBuscado == NULL)
    {
        cls();
        cout << "EL contacto buscado no existe." << endl;
        return;
    }

    //Mostramos el contacto, y confirmamos si desea ser eliminado
    cout << "Desea eliminar el contacto: " << endl;
    mostrarDatosContacto(contactoBuscado);

    cout << "1) Si" << endl << "2) No" << endl << "Ingrese el número de su respuesta: ";
    short respuesta;
    cin >> respuesta;

    //Si responde algo diferente a sí retorna al menú
    if(respuesta != 1)
    {
        cls();
        cout << "No se elimino" << endl << endl;
        return;
    }

    //MOdificamos los punteros de los elementos anterio y siguiente, esto hace que ya no se apunte al elemento actual


    if(contactoBuscado ->anteriorElemento == NULL && contactoBuscado ->siguienteElemento == NULL)
    {
        //Si es el unico contacto en la lista, volvemos la lista NULL
        listaContactos = NULL;
    }
    else if(contactoBuscado ->anteriorElemento == NULL)
    {
        //Si el contacto a eliminar es el primero de la lista
        listaContactos = listaContactos ->siguienteElemento;
        listaContactos ->anteriorElemento = NULL;
    }
    else if(contactoBuscado ->siguienteElemento == NULL)
    {
        //Si el contacto a eliminar es el ultimo de la lista
        contactoBuscado ->anteriorElemento ->siguienteElemento = NULL;
    }
    else
    {
        //Se ejecuta cuando el contacto a eliminar se encuentra entre otros dos contactos
        contactoBuscado ->anteriorElemento ->siguienteElemento = contactoBuscado ->siguienteElemento;
        contactoBuscado ->siguienteElemento ->anteriorElemento = contactoBuscado ->anteriorElemento;
    }

    //Eliminamos el elemento actual
    delete contactoBuscado;
    cls();
    cout << "Contacto Eliminado correctamente" << endl << endl;
}


struct Contacto *buscarContacto(struct Contacto *listaContactos ,string nombreBuscar)
{
    /*Función que busca en una lista de contactos el contacto buscado, si lo encuentra lo retorna, en caso contrario retorna un puntero NULL*/
    while(listaContactos != NULL)
    {
        //Recorremos los contactos hasta encontrar coinciedencia en los nombres
        if(convertirStringMayuscula(listaContactos ->nombre) == convertirStringMayuscula(nombreBuscar))
            return listaContactos;

        listaContactos = listaContactos ->siguienteElemento;
    }

    //Le damos valor de NULL si no consigue el contacto
    listaContactos = NULL;
    return listaContactos;

}


void mostrarContactos(struct Contacto *listaContactos)
{
    /*Se encarga de mostrar todos los contactos disponibles en la lista enlazada*/
    struct Contacto *contactoAux = listaContactos;

    if(contactoAux == NULL)
    {
        cout << "NO hay contactos agregados, agregue uno antes de realizar esta operación" << endl << endl;
        return;
    }

    cout << "Contactos Disponibles: " << endl;

    do
    {
        //Llamamos a la función para mostrar el contacto
        mostrarDatosContacto(contactoAux);
        contactoAux = contactoAux ->siguienteElemento;
    }while(contactoAux != NULL);

    cout << endl << endl;
}


void mostrarDatosContacto(struct Contacto *contacto)
{
    /*Función que se encarga unicamente de mostrar los datos de un contacto*/
    cout << "Nombre: " << contacto ->nombre << ", Teléfono: " << fixed << setprecision(0) << contacto ->telefono << ", Email: ";
    cout << contacto ->correoElectronico << endl;
}


string convertirStringMayuscula(string dato)
{
    /*Función que se encarga de convertir una cadena String a mayuscula, para la comparación en código ascii de los nombres*/
    for(int i = 0; i < int(dato.length()); i++)
        dato[i] = toupper(dato[i]);

    return dato;
}


void eliminarMemoriaDinamica(struct Contacto *listaConstactos)
{
    /*Función que se encarga de eliminar toda la memoría dinámica de la lista de contactos, de forma recursiva*/

    //SI la lista esta vacía, no hacemos nada
    if(listaConstactos == NULL)
        return;

    if(listaConstactos ->siguienteElemento != NULL)
    {
        eliminarMemoriaDinamica(listaConstactos ->siguienteElemento);
    }
    if(listaConstactos != NULL)
        delete listaConstactos;
}
