#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

#define MAX_PRODUCTOS 100    //lucreciadenisebazan@gmail.com

const int dim = 80;
float acumuladoVentas = 0;

///Estructuras
typedef struct
{
    int dni;
    char nombreYapellido[100];
    char nombreUser[50];
    char claveUser[50];
    char telefono[50];
} usuarioNew;

typedef struct
{
    int idProducto;
    char claseProducto[50];
    float precio;
    int cantidad;
    float total;
} producto;

typedef struct
{
    float acumulado;
} acumuladorVentas;

///Prototipado.
usuarioNew crearUnUsuario();
void crearUsuario(char fileUser[]);
void muestraUser(usuarioNew usuario);
int validacionUser(char fileUser[], char usuario[dim], char clave[dim]);
producto cargaUnProducto();
void verificacionCarga(char fileProducts[], producto arr[], int validos);
int cargarProductos(char fileProducts[], producto arr[], int dim);
producto checkId(char fileProducts[], producto arr[], int pos);
void muestraProductos(producto productos);
void verArrProductos(producto arr[], int validos);
void confirmarProductos(char fileProducts[], producto nuevos);
void actualizacionProducto(char fileProducts[], producto actualizados);
void verArchivoPr(char fileProducts[]);
void mostrarProductosEnMatriz(char nombreArchivo[]);
void busquedaProductos(char fileProducts[], int idBusqueda);
void marcarProducto(char fileProducts[], int idProducto);
void moverMarcado(char fileProducts[], char fileDeleted[]);
float ventasReduccion(char fileProducts[], int idVentas, int cantidad);
acumuladorVentas actualizacionVentas(char fileSell[], float acumulador);
void mostrarPerfilesMatriz(char fileUser[]);

int main()
{

    char fileUser[dim];
    char fileProducts[dim];
    char fileDeleted[dim];
    char fileSell[dim];

    strcpy(fileUser, "usuarios.bin");
    strcpy(fileProducts, "productos.bin");
    strcpy(fileSell, "ventas.bin");
    strcpy(fileDeleted, "productosDel.bin");

    int intento = 0;//control login
    int ingresa = 0;//control login
    char usuario[dim];//login
    char clave[dim];//login

    int caso1 = 0;//control switch1
    int caso2 = 0;//control switch2
    char eleccion;

    int validos1 = 0;
    int idCheck = 0;

    int idVentas = 0;//manejo ventas
    int cantidadVentas = 0;//manejo ventas
    float registroVentas = 0.0;//manejo ventas
    float auxTotal = 0.0;

    int idBusqueda = 0;//para buscar por ID.

    producto arrProductos[dim];

    printf("\t\t ____   ____                   ____                            .___  \n");
    printf("\t\t \\   \\ /   /_____     ____    / ___\\  __ __ _____  _______   __| _/  \n");
    printf("\t\t  \\   Y   / \\__  \\   /    \\  / /_/  >|  |  \\\\__  \\ \\_  __ \\ / __ |  \n");
    printf("\t\t   \\     /   / __ \\_|   |  \\ \\___  / |  |  / / __ \\_|  | \\/\\/ /_/|   \n");
    printf("\t\t    \\___/   (____  /|___|  //_____/  |____/ (____  /|__|   \\____ |   \n");

    do
    {

        printf("\n\n\t\t\tINICIO DE SESION\n");

        printf("\t\t\t----------------\n");

        printf("\n\t1 - Crear usuario \n");
        printf("\n\t2 - Ingresar al sistema \n");
        printf("\n\t3 - Salir del sitema \n\n");

        scanf("%i", &caso1);
        switch(caso1)
        {

        case 1:
            system("cls");
            printf("\t-----------------------------------------------\n");
            printf("\tCreando tu cuenta en VANGUARD INVENTORY MANAGER\n");
            printf("\t-----------------------------------------------\n\n");
            crearUsuario(fileUser);
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            printf("");
            printf("\n\tInicio de sesion");
            printf("");

            printf("\n\tUSUARIO: ");
            fflush(stdin);
            gets(usuario);

            printf("\n\tCLAVE: ");
            fflush(stdin);
            gets(clave);

            int validar = validacionUser(fileUser, usuario, clave);

            if(validar == 1)
            {
                ingresa = 1;
            }
            else
            {
                intento++;
                printf("\n\tUsuario y/o clave incorrecto, intente nuevamente.\n\n");
                system("pause");
            }
            system("cls");
            break;
        case 3:
            system("cls");
            printf("\t\t----------------------------------------------------------\n");
            printf("\t\t|\t     El sistema fue cerrado con exito            |           \n");
            printf("\t\t|Muchas gracias por confiar en Vanguard Inventory Manager|\n");
            printf("\t\t----------------------------------------------------------");
            exit(0);
        }
    }
    while(intento < 2 && ingresa == 0);

    if (ingresa == 1)
    {
        printf("\n\t\t--BIENVENIDO A VANGUARD INVENTORY MANAGER--\n\n");
    }
    else
    {
        printf("\n\t HAS SOBREPASADO EL MAXIMO DE INTENTOS PERMITIDOS\n\n");
        exit(0);
    }

    system("pause");
    system("cls");

    do
    {
        printf("\t\t ____   ____                   ____                            .___  \n");
        printf("\t\t \\   \\ /   /_____     ____    / ___\\  __ __ _____  _______   __| _/  \n");
        printf("\t\t  \\   Y   / \\__  \\   /    \\  / /_/  >|  |  \\\\__  \\ \\_  __ \\ / __ |  \n");
        printf("\t\t   \\     /   / __ \\_|   |  \\ \\___  / |  |  / / __ \\_|  | \\/\\/ /_/|   \n");
        printf("\t\t    \\___/   (____  /|___|  //_____/  |____/ (____  /|__|   \\____ |   \n");

        printf("\n\t---------------------------------------------");
        printf("\n\t\t\tMENU PRINCIPAL");
        printf("\n\t1.-Ingreso de Productos");
        printf("\n\t2.-Reporte de Productos");
        printf("\n\t3.-Ventas/Salidas");
        printf("\n\t4.-Busqueda de Productos");
        printf("\n\t5.-Eliminar Producto");
        printf("\n\t6.-Mostrar usuarios");
        printf("\n\t7.-Salir");
        printf("\n\t---------------------------------------------\n\n");

        scanf(" %i", &caso2);
        switch(caso2)
        {
        case 1:
        {
            char select = 's';
            int agregado = 0;

            validos1 = cargarProductos(fileProducts, arrProductos, dim);

            printf("\nLos productos ingresados son los siguientes: \n");

            verArrProductos(arrProductos, validos1);

            printf("\nDe ser correctos los datos 'S' para guardar 'N' para salir. \n");
            fflush(stdin);
            scanf(" %c", &select);

            if(select == 's')
            {

                verificacionCarga(fileProducts, arrProductos, validos1);

            }
        }
        break;

        case 2:

            mostrarProductosEnMatriz(fileProducts);
            break;

        case 3:

        {
            char select = 's';

            while(select == 's')
            {
                mostrarProductosEnMatriz(fileProducts);

                printf("\nID del producto: \n");
                fflush(stdin);
                scanf(" %i", &idVentas);

                printf("\nCantidad: \n");
                fflush(stdin);
                scanf(" %i", &cantidadVentas);

                registroVentas = ventasReduccion(fileProducts, idVentas, cantidadVentas);
                auxTotal += registroVentas;
                moverMarcado(fileProducts, fileDeleted);

                printf("\nPulse S para vender otro producto, N para salir.");
                fflush(stdin);
                scanf(" %c", &select);
            }

            acumuladorVentas actualizacion = actualizacionVentas(fileSell, auxTotal);
            printf("\n\nTotal acumulado en ventas: $%0.2f\n", actualizacion.acumulado);
        }

        break;

        case 4:
            printf("Búsqueda de Productos:\n");

            printf("Ingrese el ID del producto que desea buscar: ");
            fflush(stdin);
            scanf("%i", &idBusqueda);

            busquedaProductos(fileProducts, idBusqueda);
            printf("\n");
            break;

        case 5:
        {
            int idProducto;

            printf("Ingrese el ID del producto a eliminar: ");
            fflush(stdin);
            scanf("%d", &idProducto);

            marcarProducto(fileProducts, idProducto);

            moverMarcado(fileProducts, fileDeleted);
            break;
        }
        case 6:
            mostrarPerfilesMatriz(fileUser);
            break;
        case 7:
        {
            system("cls");
            printf("\t\t----------------------------------------------------------\n");
            printf("\t\t|\t     El sistema fue cerrado con exito            |           \n");
            printf("\t\t|Muchas gracias por confiar en Vanguard Inventory Manager|\n");
            printf("\t\t----------------------------------------------------------");
            exit(0);
            break;
        }

        }

        printf("\nDesea volver al menu principal? s/n ");
        fflush(stdin);
        scanf("%c", &eleccion);

        system("cls");

    }
    while(eleccion == 's');
}

///Funciones.
usuarioNew crearUnUsuario()
{
    usuarioNew usuario;

    printf("\tIngrese su DNI: ");
    fflush(stdin);
    scanf("%i", &usuario.dni);

    printf("\n\tIngrese su nombre y apellido: ");
    fflush(stdin);
    gets(&usuario.nombreYapellido);

    printf("\n\tIngrese un nombre de usuario: ");
    fflush(stdin);
    gets(usuario.nombreUser);

    printf("\n\tIngrese una clave: ");
    fflush(stdin);
    gets(usuario.claveUser);

    printf("\n\tIngrese un telefono de contacto: ");
    fflush(stdin);
    gets(&usuario.telefono);

    return usuario;
}

void muestraUser(usuarioNew usuario)
{

    puts("\n-------------------------------\n");
    printf("\nDNI: %i", usuario.dni);
    printf("\nNombre y apellido: %s", usuario.nombreYapellido);
    printf("\nUsuario: %s", usuario.nombreUser);
    printf("\nTelefono: %s", usuario.telefono);
    puts("\n-------------------------------\n");
}

void verArchivoUserr(char fileUser[])
{
    usuarioNew userMuestra;

    FILE *ver;

    ver = fopen(fileUser, "r+b");

    if(ver!=NULL)
    {
        while(!feof(ver))
        {
            fread(&userMuestra, sizeof(usuarioNew), 1, ver);

            if(!feof(ver))
            {
                muestraUser(userMuestra);
            }
        }
        fclose(ver);
    }
}

void crearUsuario(char fileUser[])
{
    usuarioNew usuarioCreacion;
    usuarioNew usuarioCheck;

    int usuarioRepetido = 0;

    FILE *creacion;

    creacion = fopen(fileUser, "a+b");

    if(creacion!=NULL)
    {
        usuarioCreacion = crearUnUsuario();

        while(!feof(creacion))
        {
            fread(&usuarioCheck, sizeof(usuarioNew), 1, creacion);

            if(strcmp(usuarioCheck.nombreUser, usuarioCreacion.nombreUser) == 0)
            {
                usuarioRepetido = 1;
            }
        }

        if(usuarioRepetido == 1)
        {
            printf("\n\nEse nombre de usuario ya se encuentra registrado.\n");

        }
        else
        {
            fwrite(&usuarioCreacion, sizeof(usuarioNew), 1, creacion);
        }

        fclose(creacion);
    }
}

int validacionUser(char fileUser[], char usuario[dim], char clave[dim])
{
    usuarioNew usuarioValidar;

    int validar = 0;

    FILE *validacion;

    validacion = fopen(fileUser, "rb");

    if(validacion!=NULL)
    {
        while(!feof(validacion))
        {
            fread(&usuarioValidar, sizeof(usuarioNew), 1, validacion);

            if(!feof(validacion))
            {
                if (strcmp(usuario, usuarioValidar.nombreUser) == 0 && strcmp(clave, usuarioValidar.claveUser) == 0)
                {
                    validar = 1;
                }
            }
        }
        fclose(validacion);
    }

    return validar;
}

producto cargaUnProducto()
{
    producto product;

    printf("ID: ");
    fflush(stdin);
    scanf("%i", &product.idProducto);

    printf("Producto: ");
    fflush(stdin);
    gets(product.claseProducto);

    printf("Precio: $");
    fflush(stdin);
    scanf("%f", &product.precio);

    printf("Cantidad: ");
    fflush(stdin);
    scanf("%i", &product.cantidad);

    return product;
}

void muestraProductos(producto productos)
{
    puts("\n---------------------");
    printf("ID: %i", productos.idProducto);
    printf("\t\nProducto: %s", productos.claseProducto);
    printf("\t\nPrecio: $%0.2f", productos.precio);
    printf("\t\nCantidad %i", productos.cantidad);
    printf("\t\nTotal: $%0.2f", productos.precio*productos.cantidad);
    puts("\n---------------------\n");
}

void verArrProductos(producto arr[], int validos)
{
    int i = 0;

    while(i<validos)
    {
        muestraProductos(arr[i]);

        i++;
    }
    printf("\n");
}



void verArchivoPr(char fileProducts[])
{
    producto productoMuestra;

    FILE *ver;

    ver = fopen(fileProducts, "rb");

    if(ver!=NULL)
    {
        while(!feof(ver))
        {
            fread(&productoMuestra, sizeof(producto), 1, ver);

            if(!feof(ver))
            {
                muestraProductos(productoMuestra);
            }
        }
        fclose(ver);
    }
}

int cargarProductos(char fileProducts[], producto arr[], int dim)
{
    int i = 0;
    char eleccion = 's';

    while(i < dim && eleccion == 's')
    {
        arr[i] = cargaUnProducto();

        producto retornoPositivo = checkId(fileProducts, arr, i);

        if(retornoPositivo.idProducto == arr[i].idProducto)
        {
            printf("\nEl producto ingresado con ID %i se encuentra en stock, se actualizara la cantidad.\n", retornoPositivo.idProducto);
            muestraProductos(retornoPositivo);
        }

        i++;

        printf("Desea continuar con la carga? s/n");
        fflush(stdin);
        scanf("%c", &eleccion);
    }
    return i;
}

producto checkId(char fileProducts[], producto arr[], int pos)
{
    producto retornoProd;

    producto checkeo;

    FILE *check;

    check = fopen(fileProducts, "rb");

    if(check!=NULL)
    {
        while(!feof(check))
        {
            fread(&checkeo, sizeof(producto), 1, check);

            if(!feof(check) && checkeo.idProducto == arr[pos].idProducto)
            {
                retornoProd = checkeo;
                return retornoProd;
                fclose(check);
            }
        }
    }

}

void verificacionCarga(char fileProducts[], producto arr[], int validos)
{
    int i;
    int encontrado;

    producto auxProducto;

    FILE *verificacion;

    verificacion = fopen(fileProducts, "a+b");

    if (verificacion != NULL)
    {
        for (i = 0; i < validos; i++)
        {
            encontrado = 0;

            rewind(verificacion);

            while (fread(&auxProducto, sizeof(producto), 1, verificacion) == 1)
            {
                if (auxProducto.idProducto == arr[i].idProducto)
                {
                    encontrado = 1;
                    break;
                }
            }

            if (encontrado)
            {
                actualizacionProducto(fileProducts, arr[i]);
            }
            else
            {
                confirmarProductos(fileProducts, arr[i]);
            }
        }

        fclose(verificacion);
    }
}

void actualizacionProducto(char fileProducts[], producto actualizados)
{
    producto prodActualizado;

    FILE *actualizar;

    actualizar = fopen(fileProducts, "r+b");

    if(actualizar!=NULL)
    {
        while(!feof(actualizar))
        {
            fread(&prodActualizado, sizeof(producto), 1, actualizar);

            if(!feof(actualizar) && prodActualizado.idProducto == actualizados.idProducto)
            {
                fseek(actualizar, (-1)*sizeof(producto), SEEK_CUR);

                prodActualizado.cantidad += actualizados.cantidad;

                fwrite(&prodActualizado, sizeof(producto), 1, actualizar);
                break;
            }
        }
        fclose(actualizar);
    }
}

void confirmarProductos(char fileProducts[], producto nuevos)
{
    producto prodNuevo;

    FILE *confirmar;

    confirmar = fopen(fileProducts, "ab");

    if(confirmar!=NULL)
    {
        prodNuevo = nuevos;

        fwrite(&prodNuevo, sizeof(producto), 1, confirmar);

        fclose(confirmar);
    }
}


void mostrarProductosEnMatriz(char fileProducts[])
{
    producto aux;

    printf("Reporte de Productos:\n");

    printf("%-12s %-12s %-12s %-12s %-12s\n", "ID", "Producto", "Precio", "Cantidad", "Total");

    FILE *archivo = fopen(fileProducts, "rb");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    while(!feof(archivo))
    {
        if (fread(&aux, sizeof(producto), 1, archivo) == 1)
        {
            if(aux.idProducto != -1)
            {
                printf("%-12i %-12s $%-11.2f %-12i $%-11.2f\n", aux.idProducto, aux.claseProducto, aux.precio, aux.cantidad, aux.precio * aux.cantidad);
            }
        }
    }

    fclose(archivo);
}

void busquedaProductos(char fileProducts[], int idBusqueda)
{
    producto productoEncontrado;

    FILE *archivo = fopen(fileProducts, "rb");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    int encontrado = 0;

    while (!feof(archivo))
    {
        fread(&productoEncontrado, sizeof(producto), 1, archivo);

        if (!feof(archivo) && productoEncontrado.idProducto == idBusqueda)
        {
            muestraProductos(productoEncontrado);
            encontrado = 1;
            break;
        }
    }

    fclose(archivo);

    if (!encontrado)
    {
        printf("El producto con el ID %i no fue encontrado.\n", idBusqueda);
    }
}

void marcarProducto(char fileProducts[], int idProducto)
{
    FILE *archivo = fopen(fileProducts, "r+b");

    producto prod;

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }


    while (fread(&prod, sizeof(producto), 1, archivo) == 1)
    {
        if (prod.idProducto == idProducto)
        {
            prod.idProducto = -1;
            fseek(archivo, -sizeof(producto), SEEK_CUR); // Retroceder para sobrescribir el registro
            fwrite(&prod, sizeof(producto), 1, archivo);
            printf("El producto con ID %d ha sido eliminado.\n", idProducto);
            fclose(archivo);
            return;
        }
    }

    printf("El producto con ID %d no existe.\n", idProducto);
    fclose(archivo);
}

void moverMarcado(char fileProducts[], char fileDeleted[])
{
    producto prodDelete;

    FILE *prod;
    FILE *mover;

    prod = fopen(fileProducts, "r+b");
    mover = fopen(fileDeleted, "wb");

    if(prod!=NULL && mover != NULL)
    {
        while(!feof(prod))
        {
            fread(&prodDelete, sizeof(producto), 1, prod);

            if(!feof(prod) && prodDelete.idProducto == -1)
            {
                fwrite(&prodDelete, sizeof(producto), 1, mover);
            }
        }
        fclose(prod);
        fclose(mover);
    }
}

float ventasReduccion(char fileProducts[], int idVentas, int cantidad)
{
    producto prodVentas;

    Pila cantidadContador;
    Pila cantidadStock;
    Pila aux;

    inicpila(&cantidadContador);
    inicpila(&cantidadStock);
    inicpila(&aux);

    int contador1 = 0;
    int contador2 = 0;
    char select = 's';
    float totalVentas = 0;

    FILE *ventas;

    ventas = fopen(fileProducts, "r+b");

    if(ventas != NULL)
    {
        while(fread(&prodVentas, sizeof(producto), 1, ventas) == 1)
        {
            if(prodVentas.idProducto == idVentas)
            {
                while(contador1 < cantidad)
                {
                    apilar(&cantidadContador, 1);
                    contador1++;
                }
                while(contador2 < prodVentas.cantidad)
                {
                    apilar(&cantidadStock, 1);
                    contador2++;
                }
                while(!pilavacia(&cantidadContador) && !pilavacia(&cantidadStock))
                {
                    apilar(&aux, desapilar(&cantidadContador));
                    apilar(&aux, desapilar(&cantidadStock));
                }
                if(pilavacia(&cantidadStock) && !pilavacia(&cantidadContador))
                {
                    printf("\nLa venta que desea realizar excede el stock del producto, desea cubrir la venta con la totalidad de las existencias (S) o vender una cantidad diferente (N)? \n");
                    fflush(stdin);
                    scanf(" %c", &select);
                    if(select == 's')
                    {
                        prodVentas.cantidad -= contador2;
                        if(prodVentas.cantidad == 0)
                        {
                            prodVentas.idProducto = -1;
                        }
                        fseek(ventas, (-1) * sizeof(producto), SEEK_CUR);
                        fwrite(&prodVentas, sizeof(producto), 1, ventas);

                        totalVentas = prodVentas.precio * contador2;

                        printf("La venta registro un total de $%0.2f", totalVentas);
                    }
                }
                else
                {
                    prodVentas.cantidad -= cantidad;
                    if(prodVentas.cantidad == 0)
                    {
                        prodVentas.idProducto = -1;
                    }
                    fseek(ventas, (-1) * sizeof(producto), SEEK_CUR);
                    fwrite(&prodVentas, sizeof(producto), 1, ventas);

                    totalVentas = prodVentas.precio * cantidad;

                    printf("La venta registro un total de $%0.2f", totalVentas);
                }
                break;
            }
        }
        fclose(ventas);
    }
    return totalVentas;
}

acumuladorVentas actualizacionVentas(char fileSell[], float acumulador)
{
    FILE *ventas;

    ventas = fopen(fileSell, "wb");

    acumuladorVentas aux;
    acumuladorVentas acumulo;

    if(ventas!=NULL)
    {
        fread(&aux, sizeof(acumuladorVentas), 1, ventas);

        acumulo.acumulado = aux.acumulado;

        fseek(ventas, 0, SEEK_SET);

        acumulo.acumulado += acumulador;

        fwrite(&acumulo, sizeof(acumuladorVentas), 1, ventas);
    }

    fclose(ventas);

    return acumulo;
}

void mostrarPerfilesMatriz(char fileUser[])
{
    int i, j;

    printf("%-25s %-10s %-15s %-25s\n", "Nombre y apellido", "DNI",  "Usuario", "Telefono");

    FILE *usermatr = fopen(fileUser, "rb");

    if(usermatr!=NULL)
    {
        fseek(usermatr, 0, SEEK_END);
        int cantidadRegistros = ftell(usermatr)/sizeof(usuarioNew);

        int fila = cantidadRegistros;
        int col = cantidadRegistros;

        usuarioNew matrizperfiles[fila][col];

        fseek(usermatr, 0, SEEK_SET);

        for (i = 0; i < fila; i++)
        {
            for (j = 0; j < col; j++)
            {
                fread(&matrizperfiles[i][j], sizeof(usuarioNew), 1, usermatr);
            }
            break;
        }

        for (i = 0; i < fila; i++)
        {
            for (j = 0; j < col; j++)
            {
                printf("%-25s %-10i %-15s %-25s\n", matrizperfiles[i][j].nombreYapellido, matrizperfiles[i][j].dni, matrizperfiles[i][j].nombreUser, matrizperfiles[i][j].telefono);
            }
            break;
        }

        fclose(usermatr);
    }
}
