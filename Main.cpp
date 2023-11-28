#include<iostream>

#include <vector>

#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <fstream>

#include <set>



//! UClase tipo Sopa de Numeros.

/*!

  * Clase que simula una Sopa de Numeros

  * \author    Alejandra Carrera y Adelis Vargas

  * \version   1.0

  * \date      2023-11-05

*/





using namespace std;

int** secuencia;        /**Matriz global auxiliar usada para almacenar la secuencia de digitos a buscar

                        en la matriz. La cantidad de filas de esta matriz auxiliar estara dada

                        por la cantidad de digitos del numero introducido por el usuario,

                        la columna 0 almacenara el digito mas significativo del numero buscando,

                        columna 1 almacenara la fila donde se encontro el digito de la columna 0,

                        la columna 2 almacenara la columna donde se encontro el digito de la columna 0,

                        la columna 3 almacenara la direccion adyacente respecto al digito anterior

                        0->arriba, 1->abajo, 2->Izquierda, 3->derecha, 4->Arriba a la izquierda,

                        5->arriba a la derecha, 6->abajo a la izquierda, 7->abajo a la derecha*/

int digitos;            ///variable global para almacenar la cantidad de digitos que tiene el numero a buscar



void ponerNULL(int fila)    ///Usada para limpiar los datos en la variable de secuencia

{

    for(int i=fila;i<digitos;i++){

        secuencia[i][1]=-1;

        secuencia[i][2]=-1;

        secuencia[i][3]=-1;

    }

}



bool buscarRepetidos(int fila, int columna)     ///Funcion para buscar si hay alguna coordenada que se repita en la secuencia

{

    for(int i=0;i<digitos;i++)

        if(secuencia[i][1]==fila && secuencia[i][2]==columna)

            return true;

    return false;

}



int contarDigitos(int num)      ///Funcion para contar cantidad de digitos del numero buscado

{

    if(num==0){

        return 0;

    }else{

        return 1 + contarDigitos(num/10);

    }

}



void liberarMatriz(int** matriz, int M) ///Funcion usada para liberar la memoria reservada dinamicamente por la matriz secuencia

{

    ///Liberar la memoria asignada a la matriz

    for(int i=0;i<M;i++)

        delete[] matriz[i];

    delete[] matriz;

}



class SopaDeNumeros {

private:

    //! M

        /*!

        Matrriz que simula una sopa de numeros

        */

    int M[20][20];

    //! fila

        /*!

        Cantidad de filas que posee la matriz

        */

    int fila;

    //! columna

        /*!

        cantidad de columnas que posee la matriz

        */

    int columna;



public:

    //! Constructor.

    /*!

      * Constructor SopaDeNumeros

      * Usage: SopaDeNumeros st;

      * Constructor de la matriz vacia.

    */



    SopaDeNumeros() {           //constructor

        fila = 0;

        columna = 0;

    }



    //! Constructor.

    /*!

      * Constructor GenerarMatrizAleatoria

      * Usage: GenerarMatrizAleatoria st;

      * \param f cantidad de filas

      * \param c cantidad de columnas

      * Construye la matriz con una cantidad f de filas y c de columnas y llena cada espacio de manera aleatoriacon con un entero del 0 al 9.

    */

    void GenerarMatrizAleatoria(int f, int c) {     //Metodo para generar una matriz aleatoria de f filas y c columnas

        // Generar números aleatorios y llenar la matriz

        fila = f;                       //asigno tamano de filas de la matriz

        columna = c;                    //asigno tamano de columnas de la matriz SopaDeNumeros



        srand(time(NULL));              //Inicializo generador de numeros aleatorios

        for (int i=0; i<fila; i++)        //recorro cada fila con este bucle

            for(int j=0;j<columna;j++)  //recorro cada columna fila a fila

                M[i][j]=rand()%10;      //asigno valor aleatorio a cada elemento de la matriz

    }



    //! Método MostrarMatriz

        /*!

        * \usage SopaDeNumeros MostrarMatriz();

        * Muestra en pantalla la matriz hecha.

        */

    void MostrarMatriz() {

        cout << "Matriz: " << endl;

        for (int i=0; i<fila; i++) {

            cout<<"\t\t";

            for (int j=0; j<columna; j++) {

                cout << M[i][j] << " ";

            }

            cout << endl;

        }

    }



    //! Método Read

        /*!

        * \usage SopaDeNumero Read();

        * \param in fil cantidad de filas

        * \param col cantidad de columnas

        * Lee un archivo y se crea la sopa de numeros a partir del mismo

        */

    void Read(int fil, int col) {

        fila = fil;

        columna= col;

        string file;

        cout<<"Entre el nombre del archivo del cual desea generar la matriz: ";

        cin>>file;

        ifstream archivo;

        archivo.open(file.c_str(),ios::in);

        if(archivo.fail()){

                cout<<"No se pudo abrir el archivo";

                return;

            }

        for (int i = 0; i < fila; i++) {

            for (int j = 0; j < columna; j++) {

                archivo >> M[i][j];

            }

        }



        archivo.close();

    }



    //! Método BuscarNumeroDado

        /*!

        * \param numeroBuscado valor que se buscara en la matriz

        * \return Posicion del primer termino del numero buscado y direccion que hay que seguir para  encontrarlo

        * \usage SopaDeNumeros BuscarNumeroDado(numeroBuscado);

        * Busca un numero digitado por el usuario y da su posicion con el camino a recorrer para encontrarlo

        */

    void BuscarNumeroDado(int numeroBuscado){    //Funcion para buscar un numero instroducido por el usuario

        if(fila == 0 && columna == 0){

            cout<<"No se ha creado la matriz aun\n\n";

        }else{

            for(int i=0;i<fila;i++){                //recorro la matriz buscando el primer digito de el numero a buscar

                for(int j=0;j<columna;j++){

                    if(M[i][j]==secuencia[0][0]){   //Comparo si cada elemento de la matriz es igual al primer digito del numero buscado

                        //Si coincide un elemento de la atriz con el primer digito del numero buscado

                        ponerNULL(0);           //Limpio la secuencia para evitar datos malos

                        secuencia[0][1]=i;      //Guardo en la fila de la matriz donde se encontro el primer digito

                        secuencia[0][2]=j;      //Guardo en la columna de la matriz donde se encontro el primer digito

                        if(digitos >1){

                            //Si la cantidad de digitos del numero a buscar es mayor que 1 busco en las casillas adyacentes

                            //a donde encontre el primer digito del numero buscado

                            BuscarAdyacentes(i,j,secuencia[1][0],1);

                        }else{

                            //Si el numero introducido por el usuario tiene solo un digito, muestro sus coordenadas

                            cout<<"El numero se encontro en la posicion ("<<secuencia[0][1]<<","<<secuencia[0][2]<<")\n";

                        }

                    }

                }

            }

        }

    }



    /*!

    \brief Metodo para buscar un numero dado en las posiciones adyacentes a unas coordenadas dadas

    \param [in] f      Cantidad de filas de la matriz

    \param [in] c      Cantidad de columnas de la matriz

    \param [in] numeroBuscado  Numero a busc ar dentro de la matriz

    \param [in] salto  Auxiliar para guardar la posicion de fila y columna

    \return Direccion a seguir para encontrar el  numero buscado.

    */

    void BuscarAdyacentes(int f, int c, int numeroBuscado, int salto) {

        int adyacentes[8][2] = {    //Matriz de ayuda para buscar en casillas adyacentes

            {-1, 0}, // Arriba

            {1, 0},  // Abajo

            {0, -1}, // Izquierda

            {0, 1},  // Derecha

            {-1, -1},// Arriba a la izquierda

            {-1, 1}, // Arriba a la derecha

            {1, -1}, // Abajo a la izquierda

            {1, 1}   // Abajo a la derecha

        };



    //Verificar cada coordenada adyacente

        for(int i=0;i<8;i++)    //arreglo para recorrer las 8 casillas adyacentes a una posicion dada

        {

            //Coordenadas de la casilla adyacente

            int nuevaFila = f + adyacentes[i][0];

            int nuevaColumna = c + adyacentes[i][1];



            //Verificar limites de la matriz

            if(nuevaFila >= 0 && nuevaFila < fila && nuevaColumna >= 0 && nuevaColumna < columna)

            {

                //Verificar si el numero coincide y no esta repetido

                if(M[nuevaFila][nuevaColumna]==numeroBuscado&&buscarRepetidos(nuevaFila,nuevaColumna)==false){

                    //si coincide el siguiente digito del numero buscado con alguno de los numeros de las casillas adyacentes

                    ponerNULL(salto);                   //Limpio los valores de la secuencia

                    secuencia[salto][1]=nuevaFila;      //guardo la fila donde se encontro el digito correspondiente a buscar

                    secuencia[salto][2]=nuevaColumna;   //guardo la columna

                    secuencia[salto][3] = i;            //guardo la posicion donde se encontro (arriba, abajo,izquierda...)

                    //Verifico si no estoy buscando el ultimo digito del numero buscado

                    if(salto<digitos-1){

                        //si no es el ultimo digito del numero buscado Busco en sus casillas dyacentes correspondientes

                        BuscarAdyacentes(nuevaFila,nuevaColumna,secuencia[salto+1][0],salto+1);

                    }else{

                        //Si encontre todos los digitos de manera adyacentes doy las coordenadas del primer digito

                        //y la ruta para eencontrar los demas digitos de manera adyacente

                        for(int k=0;k<digitos;k++){

                            if(k==0){

                                cout<<"El numero se encuentra en la posicion ("<<secuencia[k][1]<<","<<secuencia[k][2]<<")";

                            }else{

                                switch(secuencia[k][3]){

                                    case 0:{

                                        cout<<" -> Arriba("<<secuencia[k][1]<<","<<secuencia[k][2]<<")";

                                        break;

                                    }

                                    case 1:{

                                        cout<<" -> Abajo("<<secuencia[k][1]<<","<<secuencia[k][2]<<")";

                                        break;

                                    }

                                    case 2:{

                                        cout<<" -> Izquierda("<<secuencia[k][1]<<","<<secuencia[k][2]<<")";

                                        break;

                                    }

                                    case 3:{

                                        cout<<" -> Derecha("<<secuencia[k][1]<<","<<secuencia[k][2]<<")";

                                        break;

                                    }

                                    case 4:{

                                        cout<<" -> Arriba a la Izquierda("<<secuencia[k][1]<<","<<secuencia[k][2]<<")";

                                        break;

                                    }

                                    case 5:{

                                        cout<<" -> Arriba a la derecha("<<secuencia[k][1]<<","<<secuencia[k][2]<<")";

                                        break;

                                    }

                                    case 6:{

                                        cout<<" -> Abajo a la izquierda("<<secuencia[k][1]<<","<<secuencia[k][2]<<")";

                                        break;

                                    }

                                    case 7:{

                                        cout<<" -> Abajo a la derecha("<<secuencia[k][1]<<","<<secuencia[k][2]<<")";

                                        break;

                                    }

                                    default:break;

                                }



                            }

                        }

                        cout<<endl;

                    }



                }

            }

        }

    }

    //Metodo para buscar la cantidad de numeros de K cifras que pueden formarse en la matriz

    //! Método buscarNumerosDeKCifras

       /*!

       * \param k cantidad de digitos que tendran los numeros a encontrar

       * \usage SopaDeNumeros buscarNumerosDeKCifras(k);

       * A partir de un numero introducido por el usuario se buscaran numeros en la matriz con esa cantidad de digitos y se imprimiran en un  vector.

       */

    void buscarNumerosDeKCifras(int k) {

        if(fila == 0 && columna == 0){

            cout<<"No se ha creado la matriz aun\n\n";

        }else{

            vector<string> numerosEncontrados;      //vector para almacenar los numeros de k cifras encontrados

            for (int i = 0; i < fila; i++) {        //recorro cada fila de la matriz

                for (int j = 0; j < columna; j++) { //recorro cada columna de la matriz

                    //Teniendo en cuenta que en una posicion puede haber un 0, uso una cadena de caracteres para

                    //almacenar tambien los 0 a la izquierda

                    string numeroHorizontal;

                    // Buscar números de k cifras horizontalmente hacia la derecha

                    if (j + k <= columna) {         //Verifico que no me paso de los limites de la matriz hacia la derecha

                        numeroHorizontal = "";

                        for (int l = 0; l < k; l++) {

                            numeroHorizontal += ('0'+M[i][j + l]);  //almaceno el numero formado como caracteres

                        }

                        numerosEncontrados.push_back(numeroHorizontal); //guardo el numero formado de k cifras

                    }

                    // Buscar números de k cifras horizontalmente hacia la Izquierda

                    if (j - k >= 0) {               //Verifico que no me paso de los limites de la matriz hacia la izquierda

                        numeroHorizontal = "";

                        for (int l = 0; l < k; l++) {

                            numeroHorizontal += ('0'+M[i][j-l]);

                        }

                        numerosEncontrados.push_back(numeroHorizontal);

                    }



                    string numeroVertical;

                    // Buscar números de k cifras verticalmente hacia abajo

                    if (i + k <= fila) {            //Verifico que no me paso de los limites de la matriz hacia abajo

                        numeroVertical = "";

                        for (int l = 0; l < k; l++) {

                            numeroVertical += ('0'+M[i + l][j]);

                        }

                        numerosEncontrados.push_back(numeroVertical);

                    }

                    // Buscar números de k cifras verticalmente hacia arriba

                    if (i - k >= 0) {               //Verifico que no me paso de los limites de la matriz hacia arriba

                        numeroVertical = "";

                        for (int l = 0; l < k; l++) {

                            numeroVertical += ('0'+M[i - l][j]);

                        }

                        numerosEncontrados.push_back(numeroVertical);

                    }



                    string numeroDiagonal;

                    // Buscar números de k cifras en diagonal hacia abajo y a la derecha

                    if (i + k <= fila && j + k <= columna) {    //Verifico que no me paso de los limites de la matriz hacia abajo y a la derecha

                        numeroDiagonal = "";

                        for (int l = 0; l < k; l++) {

                            numeroDiagonal += ('0'+M[i + l][j + l]);

                        }

                        numerosEncontrados.push_back(numeroDiagonal);

                    }

                    // Buscar números de k cifras en diagonal hacia abajo y a la izquierda

                    if (i + k <= fila && j - k >= 0) {          //Verifico que no me paso de los limites de la matriz hacia abajo y a la izquierda

                        numeroDiagonal = "";

                        for (int l = 0; l < k; l++) {

							numeroDiagonal += ('0'+M[i + l][j - l]);

                        }

                        numerosEncontrados.push_back(numeroDiagonal);

                    }

                    // Buscar números de k cifras en diagonal hacia arriba y a la derecha

                    if (i - k >= 0 && j + k <= columna) {

                        numeroDiagonal = "";

                        for (int l = 0; l < k; l++) {

							numeroDiagonal += ('0'+M[i - l][j + l]);

                        }

                        numerosEncontrados.push_back(numeroDiagonal);

                    }

                    // Buscar números de k cifras en diagonal hacia arriba y a la izquierda

                    if (i - k >= 0 && j - k >= 0) {

                        numeroDiagonal = "";

                        for (int l = 0; l < k; l++) {

                            numeroDiagonal += ('0'+M[i - l][j - l]);

                        }

                        numerosEncontrados.push_back(numeroDiagonal);

                    }

                }

            }



            //muetro la cantidad de combinaciones encontradas

            cout<<"Total de numeros de "<<k<<" cifras encontrados: "<<numerosEncontrados.size()<<endl;

            set<string> numerosUnicos;          //variable usada para almacenar las combinaciones NO repetidas

            for (int i=0; i<numerosEncontrados.size(); i++){       //Bucle para visualizar las combinaciones de numeros encontradas

                cout<<numerosEncontrados[i]<<" ";

                numerosUnicos.insert(numerosEncontrados[i]);

            }

            //Visualizo la cantidad de combinaciones no repetidas

            cout<<"\nHay en total "<<numerosUnicos.size()<<" no repetidos.\n";

        }

    }

};



int main(){

    SopaDeNumeros juego; // Crear una instancia de la clase SopaDeNumeros

    int opcion = -1;      //Variable para almacenar las opciones disponibles

        do{ //Ciclo do-while para mostrar las opciones disponibles mientras no se escoja la opcion 5 de salir y terminar el programa

            cout<<"Escoja una opcion:"<<endl

                <<"1- Generar matriz aleatoria."<<endl

                <<"2- Cargar desde fichero."<<endl

                <<"3- Buscar numero en sopa de numeros."<<endl

                <<"4- Buscar numeros de K cifras."<<endl

                <<"5- Salir"<<endl;

            cin>>opcion;



            switch(opcion){

                case 1:{//Generar matriz aleatoria con las dimensiones entradas por el usuario

                    int fila, columna;

                    do {

                        cout << "Ingrese un numero de filas entre 10 y 20: ";

                        cin >> fila;

                        if (fila < 10 || fila > 20) {

                            cout << "Numero de filas incorrecto" << endl;

                        }

                    } while (fila < 10 || fila > 20);



                    do {

                        cout << "Ingrese un numero de columnas entre 10 y 20: ";

                        cin >> columna;

                        if (columna < 10 || columna > 20) {

                            cout << "Numero de columnas incorrecto" << endl;

                        }

                    } while (columna < 10 || columna > 20);



                    juego.GenerarMatrizAleatoria(fila,columna); //Llamada al metodo para generar matriz aleatoria

                    juego.MostrarMatriz();                      //Llamada para visualizar la matriz disponible

                    break;

                }

                case 2:{//Leer datos de la matriz a partir de fichero

                    int fila, columna;

                    do {

                        cout << "Ingrese un numero de filas entre 10 y 20: ";

                        cin >> fila;

                        if (fila < 10 || fila > 20) {

                            cout << "Numero de filas incorrecto" << endl;

                        }

                    } while (fila < 10 || fila > 20);



                    do {

                        cout << "Ingrese un numero de columnas entre 10 y 20: ";

                        cin >> columna;

                        if (columna < 10 || columna > 20) {

                            cout << "Numero de columnas incorrecto" << endl;

                        }

                    } while (columna < 10 || columna > 20);



                    juego.Read(fila,columna);

                    juego.MostrarMatriz();

                    break;

                }

                case 3:{//Introduce un numero y lo busca dentro de la matriz

                    int numeroBuscado;

                    cout<<"Ingrese el numero a buscar: ";

                    cin>>numeroBuscado;

                    digitos = contarDigitos(numeroBuscado);     //llamo funcion para contar la cantidad de digitos que tiene el numero a buscar

                    cout<<"El numero tiene "<<digitos<<" digitos.\n";



                    secuencia = new int*[digitos];   //Doy dimensiones a la matriz auxiliar secuencia con una cantidad de filas

                                                    //igual a la cantidad de digitos que tiene el numero a buscar

                    int tembuscado = numeroBuscado;

                    for(int i=digitos-1;i>=0;i--)   //algoritmo para separar cada digito del numero a buscar

                    {

                        secuencia[i] = new int[4];  //Cada fila de la variable secuencia tendra 4 columnas

                        secuencia[i][0] = tembuscado%10;    //guardo el ultimo digito del numero a buscar en la 1era posicion y asi sucesivamente

                        tembuscado /=10;    //Eliminar el ultimo digito del numero buscado

                    }

                    juego.BuscarNumeroDado(numeroBuscado);  //llamo al metodo de buscar numero en la matriz

                    liberarMatriz(secuencia,digitos);       //Elimino la meroria reservada en variable auxiliar secuencia

                    break;

                }

                case 4:{//Buscar posibles combinaciones con k cifras en vertical, horizontal y diagonal

                    int cantidadDeCifras = 0;

                    do{

                        cout<<"Entre la cantidad de cifras: ";

                        cin>>cantidadDeCifras;

                        if (cantidadDeCifras <= 1) {

                            cout << "Cantidad de cifras incorrecto, asegurese de introducir una cantidad de cifras mayor a 1." << endl;

                        }

                    }while(cantidadDeCifras <= 1);



                    juego.buscarNumerosDeKCifras(cantidadDeCifras);

                    break;

                }

                case 5:{

                    cout<<"Usted ha salido del programa.\n\n";

                    break;

                }

                default:{//en caso de que se escoja una opcion que no esta entre las disponibles

                    cout<<"Opcion incorrecta\n\n"<<endl;

                    break;

                }

            }



        }while(opcion != 5);    //Si la opcion es 5 termina el programa

    return 0;

}


