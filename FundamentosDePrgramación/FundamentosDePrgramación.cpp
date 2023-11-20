#include <iostream>
#include <vector>
#include <string>
#include <fstream> // Identificadores - Entrada/Salida
#include <sstream> 
#include <conio.h>
#include "rlutil.h"


using namespace std;
using namespace rlutil;

// Prototipos
void   access();
void   startAsuser();
void   startAsseller();
void   startBuy();
void   processAsanuser();
void   processAsaseller();
void   registerItems();
void   firstaccess();
void   accessAsanuser();
void   accessAsseller();
void   saveFicheros();
void   readUsers();
void   readSellers();
void   readProduct();
void   allUsers();
int    showProducts(int, int, int);
void   deleteProduct();
void   showEditProduct();
void   registerAs();
void   optionModify(int);
void   recover();
void   graphicsOut(int, int, int, int, int, int);
void   figureOut(int, int, int, int);
void   printAgain(string, string, int&, int&, int&);
bool   printProducts(string);
bool   checkUser(const string);
bool   checkSeller(const string);
int    editProduct();
int    limit(int, int, int, int, int, char);
int    horizontalLimit(int, int, int, int, int, int, char);
string asCII(string);
string hideString(string, char);
string readasCci(string);
string safePasword();
string safePasword_assistant(vector<char>&);

// Declaración de estructuras
struct TypUser
{
    int     codigo; // Inicializacion de una variable miembro 
    string  user;
    string  pasword;
};
struct Product
{
    int     codigo{};
    string  nombre;
    float   precio{};
};

// Arreglos globales
vector<TypUser> clientes_1;
vector<TypUser> proveedor_1;
vector<Product> productos;
vector<Product> modeloPro;

int main()
{
    readUsers();
    readSellers();
    readProduct();
    firstaccess();
    saveFicheros();
}

// Ficheros - Leer
void readUsers()
{
    // Archivo(Cliente)
    ifstream userFichero("HistorialdeUsuarios.csv");
    string   linea;
    TypUser  client;

    if (userFichero.is_open())
    {
        while (getline(userFichero, linea))
        {
            istringstream flujo(linea);
            string campo;

            getline(flujo, campo, ';');
            client.codigo = stoi(campo);

            getline(flujo, campo, ';');
            client.user = campo;

            getline(flujo, campo, ';');
            client.pasword = campo;

            bool exist = false;
            for (auto& existing : clientes_1)
            {
                if (existing.codigo == client.codigo && existing.user == client.user && existing.pasword == client.pasword) {
                    exist = true;
                    break;
                }
            }

            if (!exist) // false != true 
            {
                clientes_1.push_back(client);
            }
        }
    }
    else
    {
        cout << "Error. Incapaz de crear o abrir el archivo." << endl;
    }

    userFichero.close();
}

void readSellers()
{
    // Archivo (Proveedor)
    ifstream sellerFichero("HistorialdeProveedores.csv");
    TypUser  seller;
    string   linea;

    if (sellerFichero.is_open())
    {
        while (getline(sellerFichero, linea))
        {
            istringstream flujo(linea);
            string campo;

            getline(flujo, campo, ';');
            seller.codigo = stoi(campo);

            getline(flujo, campo, ';');
            seller.user = campo;

            getline(flujo, campo, ';');
            seller.pasword = campo;

            bool exist = false;
            for (auto& existing : proveedor_1)
            {
                if (existing.codigo == seller.codigo && existing.user == seller.user && existing.pasword == seller.pasword)
                {
                    exist = true;
                    break;
                }
            }

            if (!exist)
            {
                proveedor_1.push_back(seller);
            }
        }
    }
    else
    {
        cout << "Error. Incapaz de crear o abrir el archivo." << endl;
    }

    sellerFichero.close();
}

void readProduct()
{
    ifstream productFichero("Productos.csv");
    Product  products;
    string   linea;

    if (productFichero.is_open())
    {
        while (getline(productFichero, linea))
        {
            istringstream flujo(linea);
            string campo;

            getline(flujo, campo, ';');
            products.codigo = stoi(campo);

            getline(flujo, campo, ';');
            products.nombre = campo;

            getline(flujo, campo, ';');
            products.precio = stof(campo);

            bool exist = false;
            for (auto& existing : productos)
            {
                if (existing.codigo == products.codigo && existing.precio == products.precio && existing.nombre == products.nombre)
                {
                    exist = true;
                    break;
                }
            }

            if (!exist)
            {
                productos.push_back(products);
            }
        }
    }
    else
    {
        cout << "Error. Incapaz de crear o abrir el archivo." << endl;
    }

    productFichero.close();
}

// Ficheros - Escribir
void saveFicheros()
{
    // Archivo (Cliente)
    ofstream userFile("HistorialdeUsuarios.csv");
    for (auto& client : clientes_1)
    {
        userFile << client.codigo << ";" << client.user << ";" << client.pasword << endl;
    }
    userFile.close();

    // Archivo (Proveedor)
    ofstream sellerFile("HistorialdeProveedores.csv");
    for (auto& seller : proveedor_1)
    {
        sellerFile << seller.codigo << ";" << seller.user << ";" << seller.pasword << endl;
    }
    sellerFile.close();

    // Archivo (Producto)
    ofstream productFile("Productos.csv");
    for (auto& product : productos)
    {
        productFile << product.codigo << ";" << product.nombre << ";" << product.precio << endl;
    }
    productFile.close();
}

// Acceso
void firstaccess()
{
    hidecursor();
    locate(48, 11);
    cout << "INICIAR SESION" << endl;
    locate(48, 12);
    cout << "REGISTRARSE" << endl;
    locate(48, 13);
    cout << "RESTABLECER CONTRASENA" << endl;
    locate(48, 14);
    cout << "VER USUARIOS" << endl;
    locate(48, 15);
    cout << "SALIR" << endl;

    int option = limit(0, 4, 1, 46, 11, char(62));
    system("cls");

    switch (option) {
    case 0: access();
        break;
    case 1: registerAs();
        break;
    case 2: recover();
        break;
    case 3: allUsers();
        break;
    case 4:
        break;
    }
}

void access()
{
    hidecursor();
    locate(48, 13);
    cout << "INICIAR SESION COMO CLIENTE" << endl;
    locate(48, 14);
    cout << "INICIAR SESION COMO PROVEEDOR" << endl;

    int option = limit(0, 1, 1, 46, 13, char(62));

    system("cls");

    switch (option)
    {
    case 0: accessAsanuser();
        break;
    case 1: accessAsseller();
        break;
    }
}

void accessAsanuser()
{
    int     contador = 0;
    bool    estado = false;
    string  user_3,
            pasword_3;
    do
    {
        locate(50, 13);
        cout << "INGRESE SU USUARIO";
        figureOut(47, 14, 22, 1);
        locate(51, 15);
        showcursor();
        cin >> user_3;
        hidecursor();
        system("cls");

        locate(50, 13);
        cout << "INGRESE SU CONTRASENA";
        figureOut(47, 14, 25, 1);
        locate(51, 15);
        showcursor();
        pasword_3 = safePasword();
        hidecursor();
        system("cls");

        for (int i = 0; i < clientes_1.size(); i++)
        {
            if (clientes_1[i].user == user_3 && clientes_1[i].pasword == asCII(pasword_3))
            {
                locate(48, 12);
                cout << "BIENVENIDO(A) " << clientes_1[i].user << "!" << endl;
                processAsanuser();
                estado = true;
                break;
            }
        }
        contador++;
        if (contador == 3)
        {
            locate(48, 12);
            cout << "SE QUEDO SIN INTENTOS";
            locate(42, 13);
            system("pause");
            system("cls");
        }

    } while (!estado && contador < 3);
}

void accessAsseller()
{
    int     contador = 0;
    bool    estado = false;
    string  user_3,
            pasword_3;

    do
    {
        locate(50, 13);
        cout << "INGRESE SU USUARIO";
        figureOut(47, 14, 22, 1);
        locate(51, 15);
        showcursor();
        cin >> user_3;
        hidecursor();
        system("cls");
        locate(50, 13);

        cout << "INGRESE SU CONTRASENA";
        figureOut(47, 14, 25, 1);
        locate(51, 15);
        showcursor();
        pasword_3 = safePasword();
        hidecursor();
        system("cls");

        for (int i = 0; i < proveedor_1.size(); i++)
        {
            if (proveedor_1[i].user == user_3 && proveedor_1[i].pasword == asCII(pasword_3))
            {
                locate(48, 12);
                cout << "BIENVENIDO(A) " << proveedor_1[i].user << "!" << endl;
                system("cls");
                estado = true;
                processAsaseller();
                break;
            }
        }
        contador++;
        if (contador == 3)
        {
            locate(48, 12);
            cout << "SE QUEDO SIN INTENTOS";
            locate(42, 13);
            system("pause");
            system("cls");
        }
    } while (!estado && contador < 3);
}

// Registro
void registerAs()
{
    locate(48, 13);
    cout << "REGISTRARSE COMO CLIENTE" << endl;
    locate(48, 14);
    cout << "REGISTRARSE COMO PROVEEDOR" << endl;

    int option = limit(0, 1, 1, 46, 13, char(62));

    system("cls");

    switch (option)
    {
    case 0: startAsuser();
        break;
    case 1: startAsseller();
        break;
    }
}

void startAsuser()
{
    string  user,
            pasword;
    int     codigo;
    TypUser client;

    locate(52, 13);
    cout << "CREAR USUARIO";
    figureOut(47, 14, 22, 1);
    locate(51, 15);
    showcursor();
    cin  >> user;
    hidecursor();

    while (checkUser(user))
    {
        system("cls");
        locate(47, 13);
        cout << "NOMBRE DE USUARIO EN USO" << endl;
        figureOut(47, 14, 22, 1);
        locate(51, 15);
        showcursor();
        cin  >> user;
        hidecursor();
    }
    system("cls");

    locate(51, 13);
    cout << "CREAR CONTRASENA";
    figureOut(47, 14, 22, 1);
    locate(51, 15);
    showcursor();
    pasword = safePasword();
    hidecursor();
    system("cls");

    locate(49, 13);
    cout << "USUSARIO REGISTRADO!";
    codigo = 2000 + proveedor_1.size();
    locate(47, 14);
    cout << "CODIGO DE USUARIO " << char(175) << " " << codigo << endl;

    client.codigo = codigo;
    client.user = user;
    client.pasword = asCII(pasword);
    clientes_1.push_back(client);

    locate(43, 15);
    system("pause");
    system("cls");

    processAsanuser();
}

void startAsseller()
{
    string   user,
             pasword;
    int      codigo;
    TypUser  seller;

    locate(52, 13);
    cout << "CREAR USUARIO";
    figureOut(47, 14, 22, 1);
    locate(51, 15);
    showcursor();
    cin  >> user;
    hidecursor();

    while (checkSeller(user))
    {
        system("cls");
        locate(47, 13);
        cout << "NOMBRE DE USUARIO EN USO" << endl;
        figureOut(47, 14, 22, 1);
        locate(51, 15);
        showcursor();
        cin  >> user;
        hidecursor();
    }

    system("cls");

    locate(51, 13);
    cout << "CREAR CONTRASENA";
    figureOut(47, 14, 22, 1);
    locate(51, 15);
    showcursor();
    pasword = safePasword();
    hidecursor();
    system("cls");

    locate(49, 13);
    cout << "PROVEEDOR REGISTRADO";
    codigo = 2000 + proveedor_1.size();
    locate(47, 14);
    cout << "CODIGO DE USUARIO " << char(175) << " " << codigo << endl;

    seller.codigo = codigo;
    seller.pasword = asCII(pasword);
    seller.user = user;
    proveedor_1.push_back(seller);

    locate(43, 15);
    system("pause");
    system("cls");

    processAsaseller();
}

// Proceso-Opciones - PENDIENTE (PARTE DE PROVEEDORES)
void processAsanuser()
{
    locate(48, 13);
    cout << "INICIAR COMPRA" << endl;
    locate(48, 14);
    cout << "CERRAR SESION" << endl;

    int option = limit(0, 1, 1, 46, 13, char(62));

    system("cls");

    switch (option) {
    case 0: startBuy();
        break;
    case 1: firstaccess();
        break;
    }
}

void processAsaseller()
{
    locate(48, 11);
    cout << "REGISTRAR PRODUCTO";
    locate(48, 12);
    cout << "MODIFICAR PRODUCTO";
    locate(48, 13);
    cout << "ELIMINAR PRODUCTO";
    locate(48, 14);
    cout << "VER PRODUCTOS";
    locate(48, 15);
    cout << "CERRAR SESION" << endl;

    int option = limit(0, 4, 1, 46, 11, char(62));
    system("cls");

    switch (option)
    {
    case 0: registerItems();
        break;
    case 1: showEditProduct();
        break;
    case 2: deleteProduct();
        break;
    case 3: locate(30, 4 + showProducts(productos.size(), 30, 2));
        break;
    case 4: firstaccess();
        break;
    }
}

// Iniciar compra/cancelar(Usuario)
void startBuy()
{
    char    exit = 's',
            confirm = 's';
    bool    estado = false;
    string  nameProduct;

    do
    {
        locate(10, 2);
        cout << "LISTA DE PRODUCTOS DISPONIBLES" << endl;

        showProducts(productos.size(), 10, 2);

        locate(80, 7);
        cout << "NOMBRE DEL PRODUCTO A ADQUIRIR";
        figureOut(84, 8, 20, 1);
        locate(88, 9);
        showcursor();
        cin  >> nameProduct;
        hidecursor();
        system("cls");

        if (!printProducts(nameProduct))
        {
            continue;
        }
        else
        {
            locate(50, 11);
            cout << "COMPRAR OTRO PRODUCTO?";
            locate(54, 13);
            cout << "SI";
            locate(65, 13);
            cout << "NO";

            int option = horizontalLimit(0, 1, 11, 23, 54, 14, char(196));

            system("cls");

            switch (option)
            {
            case 0: startBuy();
                break;
            case 1: exit = 'n';
                break;
            }
        }
    } while (toupper(exit) != 'N');

    locate(52, 11);
    cout << "CONFIRMAR COMPRA?";
    locate(54, 13);
    cout << "SI";
    locate(65, 13);
    cout << "NO";

    int option = horizontalLimit(0, 1, 11, 23, 54, 14, char(196));

    system("cls");

    switch (option)
    {
    case 0: confirm;
        break;
    case 1: confirm = 'n';
        break;
    }

    system("cls");

    if (toupper(confirm) != 'N')
    {
        locate(51, 2);
        cout << "COMPRA(S) REALIZADA!" << endl;

        locate(30, 4 + showProducts(modeloPro.size(), 30, 2));
        system("pause");
        system("cls");
        processAsanuser();
    }
    else
    {
        modeloPro.clear();
        locate(52, 11);
        cout << "VENTA ANULADA!";
        locate(42, 13);
        system("pause");
        system("cls");
        processAsanuser();
    }
}

// Registar producto(Proveedor)
void registerItems()
{
    char        exit = 's';
    Product     products;          //Variable de estructura
    string      nameProduct;
    float       price;
    int         codigo;

    do
    {
        locate(50, 13);
        cout << "INGRESE EL CODIGO";
        figureOut(47, 14, 22, 1);
        locate(51, 15);
        showcursor();
        cin  >> codigo; ;
        hidecursor();
        system("cls");

        locate(50, 13);
        cout << "INGRESE EL NOMBRE";
        figureOut(47, 14, 22, 1);
        locate(51, 15);
        showcursor();
        cin  >> nameProduct;
        hidecursor();
        system("cls");

        locate(50, 13);
        cout << "INGRESE EL PRECIO";
        figureOut(47, 14, 22, 1);
        locate(51, 15);
        showcursor();
        cin  >> price;
        hidecursor();
        system("cls");

        products.codigo = codigo;
        products.nombre = nameProduct;
        products.precio = price;
        productos.push_back(products);

        locate(48, 11);
        cout << "REGISTRAR OTRO PRODUCTO?";
        locate(54, 13);
        cout << "SI";
        locate(65, 13);
        cout << "NO";

        // OTRO
        int option = horizontalLimit(0, 1, 11, 23, 54, 14, char(196));

        system("cls");

        switch (option)
        {
        case 0: exit;
            break;
        case 1: exit = 'n';
            break;
        }

    } while (toupper(exit) != 'N');

    system("cls");
    processAsaseller();
}

// Eliminar producto 
void deleteProduct()
{
    int  code;
    bool flag = 0;

    locate(38, 13);
    cout << "INGRESE EL CODIGO DEL PRODUCTO A ELIMINAR";
    figureOut(47, 14, 22, 1);
    showcursor();
    locate(50, 15);
    cin  >> code;
    hidecursor();
    system("cls");

    for (int i = 0; i < productos.size(); i++)
    {
        if (code == productos[i].codigo)
        {
            locate(40, 12);
            cout << "PRODUCTO SATISFACTORIAMENTE ELIMINADO" << endl;
            productos.erase(productos.begin() + i);
            flag = 1;
            locate(42, 13);
            system("pause");
            break;
        }
    }

    if (!flag)
    {
        locate(48, 12);
        cout << "PRODUCTO INEXISTENTE" << endl;
        locate(42, 13);
        system("pause");
    }
}

// Enseñar Producto(s)
int  showProducts(int untilWhere, int x, int horizontalSide)
{
    int howMuchforOneSide = 0;

    for (int i = 0; i < untilWhere; i++)
    {
        graphicsOut(x, 4 + howMuchforOneSide, 60, 1, 20, 40);
        locate(x + horizontalSide + 1, 5 + howMuchforOneSide);
        cout << productos[i].nombre;
        locate(x + horizontalSide + (5 * 5), 5 + howMuchforOneSide);
        cout << productos[i].codigo;
        locate(x + horizontalSide + 2 + (5 * 9), 5 + howMuchforOneSide);
        cout << productos[i].precio;
        howMuchforOneSide += 4;
    }
    return howMuchforOneSide;
}

bool printProducts(string nameProduct)
{
    Product shop;
    for (int i = 0; i < productos.size(); i++)
    {
        if (productos[i].nombre == nameProduct)
        {
            shop.codigo = productos[i].codigo;
            shop.nombre = productos[i].nombre;
            shop.precio = productos[i].precio;
            modeloPro.push_back(shop);
            return true;
            break;
        }
    }
    return false;
}

// Modificar Producto
int  editProduct()
{
    int code;

    locate(38, 13);
    cout << "INGRESE EL CODIGO DEL PRODUCTO A MODIFICAR";
    figureOut(47, 14, 22, 1);
    showcursor();
    locate(50, 15);
    cin  >> code;
    hidecursor();

    for (int i = 0; i < productos.size(); i++)
    {
        if (code == productos[i].codigo)
        {
            return i;
        }
    }
    return -1;
}

void showEditProduct()
{
    int function = editProduct();

    if (function != -1)
    {
        optionModify(function);
    }
    else
    {
        locate(48, 12);
        cout << "PRODUCTO NO ENCONTRADO" << endl;
        locate(42, 13);
        system("pause");
    }
}

void optionModify(int editProductReturn)
{
    string newName;
    float  price;

    system("cls");
    locate(48, 11);
    cout << "CAMBIAR NOMBRE";
    locate(48, 12);
    cout << "CAMBIAR CODIGO";
    locate(48, 13);
    cout << "CAMBIAR PRECIO";
    locate(48, 14);

    int option = limit(0, 3, 1, 46, 11, char(62));
    system("cls");

    switch (option)
    {
    case 0:
        locate(50, 13);
        cout << "INGRESE EL NOMBRE";
        figureOut(47, 14, 22, 1);
        locate(51, 15);
        showcursor();
        cin  >> newName;
        hidecursor();
        system("cls");

        productos[editProductReturn].nombre = newName;
        system("cls");

        locate(52, 11);
        cout << "CAMBIO EXITOSO!" << endl;
        locate(42, 13);
        system("pause");
        break;
    case 1:
        locate(50, 13);
        cout << "INGRESE EL CODIGO";
        figureOut(47, 14, 22, 1);
        locate(51, 15);
        showcursor();
        cin  >> price;
        hidecursor();
        system("cls");

        productos[editProductReturn].precio = price;
        system("cls");

        locate(52, 11);
        cout << "CAMBIO EXITOSO!" << endl;
        locate(42, 13);
        system("pause");
        break;
    case 2:
        locate(50, 13);
        cout << "INGRESE EL PRECIO";
        figureOut(47, 14, 22, 1);
        locate(51, 15);
        showcursor();
        cin  >> price;
        hidecursor();
        system("cls");

        productos[editProductReturn].precio = price;
        system("cls");

        locate(52, 11);
        cout << "CAMBIO EXITOSO!" << endl;
        locate(42, 13);
        system("pause");
        break;
    }
}

// Ocultar contraseña
string hideString(string newString, char mask)
{
    string oldString = newString;
    for (char& w : oldString)
    {
        w = mask;
    }
    return oldString;
}

string asCII(string saveASCII)
{
    string str;
    vector <string> paswordASCII;
    for (int i = 0; i < saveASCII.length(); i++)
    {
        int ascii = int(saveASCII[i]);
        paswordASCII.push_back(to_string(ascii));
    }

    for (int i = 0; i < paswordASCII.size(); i++)
    {
        str += paswordASCII[i];
    }
    paswordASCII.clear();
    return str;
}

// Ocultar contraseña - Ingreso
string safePasword()
{
    char firstWord;
    vector<char> words;

    firstWord = _getch();
    while (firstWord != 13)
    {
        if (firstWord == 8)
        {
            if (!words.empty())
            {
                words.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            words.push_back(firstWord);
            cout << "*";
        }

        firstWord = _getch();
    }
    return safePasword_assistant(words);
}

string safePasword_assistant(vector<char>& chartoString)
{
    string newstring;
    for (int i = 0; i < chartoString.size(); i++)
    {
        newstring.push_back(chartoString[i]);
    }
    return newstring;
}

// Restablecer contraseña
void recover()
{
    int     codigo_1;
    string  newName;
    bool    estado = false;

    locate(45, 13);
    cout << "INGRESE SU CODIGO DE USUARIO";
    figureOut(47, 14, 22, 1);
    locate(57, 15);
    showcursor();
    cin  >> codigo_1;
    hidecursor();
    system("cls");

    for (int i = 0; i < clientes_1.size(); i++)
    {
        if (clientes_1[i].codigo == codigo_1)
        {
            locate(49, 7);
            cout << "BIENVENIDO " << "USUARIO " << i + 1 << "!";
            locate(56, 9);
            cout << "USUARIO";
            figureOut(47, 10, 23, 1);
            locate(50, 11);
            cout << clientes_1[i].user;
            locate(55, 13);
            cout << "CONTRASENA";
            figureOut(47, 14, 23, 1);
            locate(50, 15);
            cout << hideString(clientes_1[i].pasword, '*');
            locate(47, 17);
            cout << "-------------------------";
            locate(52, 18);
            cout << "NUEVA CONTRASENA";
            figureOut(47, 19, 23, 1);
            locate(50, 20);
            showcursor();
            cin  >> newName;
            hidecursor();

            clientes_1[i].pasword = asCII(newName);
            system("cls");

            locate(47, 11);
            cout << "CONTRASENA ESTABLECIDA!";

            locate(42, 13);
            system("pause");
            system("cls");
            estado = true;
            break;
        }
    }

    if (!estado)
    {
        cout << "Codigo invalido" << endl;
        firstaccess();
    }
}

// Usuario en uso 
bool checkUser(const string name)
{
    for (int i = 0; i < clientes_1.size(); i++)
    {
        if (clientes_1[i].user == name)
        {
            return true;
        }
    }
    return false;
}

bool checkSeller(const string name)
{
    for (int i = 0; i < proveedor_1.size(); i++)
    {
        if (proveedor_1[i].user == name)
        {
            return true;
        }
    }
    return false;
}

// Mostrar Usuarios - Reportes
void allUsers()
{
    int x = 5, y = 2, figureOutY = 0;

    locate(50, 2);
    cout << "USUARIOS REGISTRADOS";

    for (int i = 0; i < clientes_1.size(); i++)
    {
        printAgain("USUARIO", clientes_1[i].user, x, y, figureOutY);
        printAgain("CONTRASENA", hideString(clientes_1[i].pasword, '*'), x, y, figureOutY);
        cout << endl;
    }
}

// Interfaz
void figureOut(int x, int y, int width, int high)
{
    locate(x, y);
    cout << char(201);

    // Linea horizontal superior
    for (int i = 0; i < width; i++)
    {
        locate(x + 1 + i, y);
        cout << char(205);

        if (i == 0)
        {
            // Linea vertical (Izquierda)
            for (int s = 0; s < high; s++)
            {
                locate(x, y + 1 + s);
                cout << char(186) << endl;

                if (s == high - 1)
                {
                    locate(x, y + 2 + s);
                    cout << char(200) << endl;

                    // Linea horizontal inferior
                    for (int m = 0; m < width; m++)
                    {
                        locate(x + 1 + m, y + high + 1);
                        cout << char(205);
                    }
                }
            }
        }

        if (i == width - 1)
        {
            cout << char(187) << endl;

            // Linea vertical (Derecha)
            for (int s = 0; s < high; s++)
            {
                locate(x + width + 1, y + 1 + s);
                cout << char(186) << endl;

                if (s == high - 1)
                {
                    locate(x + width + 1, y + 2 + s);
                    cout << char(188);
                }
            }
        }
    }
}

void graphicsOut(int x, int y, int width, int high, int vertical1, int vertical2)
{
    locate(x, y);
    cout << char(218);

    // Linea horizontal superior
    for (int i = 0; i < width; i++)
    {
        locate(x + 1 + i, y);
        cout << char(196);

        if (i == 0)
        {
            // Linea vertical (Izquierda)
            for (int s = 0; s < high; s++)
            {
                locate(x, y + 1 + s);
                cout << char(179) << endl;

                if (s == high - 1)
                {
                    locate(x, y + 2 + s);
                    cout << char(192) << endl;

                    // Linea horizontal inferior
                    for (int m = 0; m < width; m++)
                    {
                        locate(x + 1 + m, y + high + 1);
                        cout << char(196);
                    }
                }
            }
        }

        // 1era linea interior
        if (i == vertical1)
        {
            locate(x + i, y);
            cout << char(194);
            for (int w = 0; w < high; w++)
            {
                locate(x + i, y + 1 + w);
                cout << char(179) << endl;

                if (w == high - 1)
                {
                    locate(x + i, y + 2 + w);
                    cout << char(193);
                }
            }
        }

        // 2da linea interior
        if (i == vertical2)
        {
            locate(x + i, y);
            cout << char(194);
            for (int w = 0; w < high; w++)
            {
                locate(x + i, y + 1 + w);
                cout << char(179) << endl;

                if (w == high - 1)
                {
                    locate(x + i, y + 2 + w);
                    cout << char(193);
                }
            }
        }

        if (i == width - 1)
        {
            locate(x + width + 1, y);
            cout << char(191) << endl;

            // Linea vertical (Derecha)
            for (int s = 0; s < high; s++)
            {
                locate(x + width + 1, y + 1 + s);
                cout << char(179) << endl;

                if (s == high - 1)
                {
                    locate(x + width + 1, y + 2 + s);
                    cout << char(217);
                }
            }
        }
    }
}

int  limit(int lowerRank, int topRank, int action, int coordinatesX, int coordinatesY, char characterToPrint)
{
    int selectedOption = 0, option = 0;
    int key;
    //setBackgroundColor(BLUE);

    do
    {
        key = getkey();

        switch (key)
        {
        case 14:
            if (selectedOption > lowerRank)
            {
                selectedOption -= action;
                option--;
            }
            break;
        case 15:
            if (selectedOption < topRank)
            {
                selectedOption += action;
                option++;
            }
            break;
        }

        for (int i = 0; i < topRank + 1; i += action)
        {
            locate(coordinatesX, coordinatesY + i);
            if (i == selectedOption)
            {
                cout << characterToPrint;
            }
            else
            {
                cout << " ";
            }
        }
    } while (key != 1);
    //setBackgroundColor(BLACK); 

    return option;
}

int  horizontalLimit(int lowerRank, int topRank, int action, int howFarBucle, int coordinatesX, int coordinatesY, char characterToPrint)
{
    int selectedOption = 0, option = 0;
    int key;

    do
    {
        key = getkey();

        switch (key)
        {
        case 16:
            if (selectedOption > lowerRank)
            {
                selectedOption -= action;
                option--;
            }
            break;
        case 17:
            if (selectedOption < topRank)
            {
                selectedOption += action;
                option++;
            }
            break;
        }

        for (int i = 0; i < howFarBucle; i += action)
        {
            locate(coordinatesX + i, coordinatesY);
            if (i == selectedOption)
            {
                //setColor(10);
                cout << characterToPrint << characterToPrint;
                //setColor(15);
            }
            else
            {
                cout << " ";
            }
        }

    } while (key != 1);

    return option;
}

void printAgain(string whatText1, string whatText2, int& howFarinX, int& howFarinY, int& figureOutY)
{
    locate(47, howFarinY += 2);
    cout << whatText1;

    figureOut(47, howFarinX + figureOutY, 23, 1);

    locate(50, howFarinY += 2);
    cout << whatText2;
    figureOutY += 4;
}