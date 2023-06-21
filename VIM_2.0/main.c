#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

#define MAX_PRODUCTOS 100

const int fila = 50;
const int col = 50;
const int dim = 80;

///Estructuras
typedef struct
{
    int dni;
    char nombreYapellido[50];
    char nombreUser[50];
    char claveUser[50];
    int telefono;
} usuarioNew;

typedef struct
{
    int idProducto;
    char claseProducto[50];
    float precio;
    int cantidad;
    float total;
} producto;


///Prototipado.
usuarioNew crearUnUsuario();
void crearUsuario(char fileUser[]);
void muestraUser(usuarioNew usuario);
int validacionUser(char fileUser[], char usuario[dim], char clave[dim]);
producto cargaUnProducto();
int validarProductosId(char fileProducts[], producto *arr[], int pos);
void cargarProductos(producto arr[dim]);
void muestraProductos(producto productos);
void verArrProductos(producto arr[], int validos);
void confirmarProductos(char fileProducts[], producto arr[], int validos);
void verArchivoPr(char fileProducts[]);
void ArchMatriz(char fileProducts[], const int fila, const int col);
void mostrarProductosEnMatriz(char nombreArchivo[], producto arr[], int validos); //case 2
void busquedaProductos(char fileProducts[], int idBusqueda); //case 4
void marcarProducto(char fileProducts[], int idProducto); //case 5
void moverMarcado(char fileProducts[], char fileDeleted[]);

int main()
{

    char fileUser[dim];
    char fileProducts[dim];
    char fileDeleted[dim];

    strcpy(fileUser, "usuarios.bin");
    strcpy(fileProducts, "productos.bin");
    strcpy(fileDeleted, "productosDel.bin");

    int intento = 0;//control login
    int ingresa = 0;//control login
    char usuario[dim];//login
    char clave[dim];//login

    int caso1 = 0;//control switch1
    int caso2 = 0;//control switch2
    char eleccion;

    int validos1 = 0;
    int validos2 = 0;
    int arrayCheck = 0;
    int idCheck = 0;

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
                printf("\n\tLos datos ingresados son incorrectos, intente nuevamente.\n\n");
                system("pause");
            }
            system("cls");
            break;
        case 3:
            system("cls");
            printf("\t\t----------------------------------------------------------\n");
            printf("\t\t|\t     El sistema fue cerrado con exito            |           \n");
            printf("\t\t| Muchas gracias por confiar en Vanguard Inventory Manager|\n");
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
            printf("\t\nA continuacion ingrese el ID del producto para verificarlo en la base de datos.\n");
            fflush(stdin);

            printf("ID: \n");
            fflush(stdin);
            scanf("%i", &idCheck);

            verArrProductos(arrProductos, validos1);

            printf("\t\nDe ser correcta la informacion ingresada pulse 1\n");
            fflush(stdin);
            scanf("%i", &arrayCheck);

            if(arrayCheck == 1)
            {
                confirmarProductos(fileProducts, arrProductos, validos1);
                printf("\t\nLos datos fueron guardados correctamente.\n");

            }
            else
            {
                printf("\t\nINTENTE NUEVAMENTE\n");
            }
            break;

        case 2:
            printf("Reporte de Productos:\n");

            FILE *archivo = fopen("productos.bin", "rb");
            if (archivo == NULL)
            {
                printf("No se pudo abrir el archivo.\n");
                break;
            }

            producto arrProductos[MAX_PRODUCTOS];
            int validos1 = 0;

            while (validos1 < MAX_PRODUCTOS && fread(&arrProductos[validos1], sizeof(producto), 1, archivo) == 1)
            {
                validos1++;
            }

            fclose(archivo);

            mostrarProductosEnMatriz("productos.bin", arrProductos, validos1);
            printf("\n");
            break;
        case 3:

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

        case 7:
        {
            system("cls");
            printf("El sistema fue cerrado con exito");
            exit(0);
            break;
        }
        }

        printf("Desea volver al menu principal? s/n");
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

    printf("Ingrese su nombre y apellido: ");
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
    scanf("%i", &usuario.telefono);

    return usuario;
}

void muestraUser(usuarioNew usuario)
{
    usuarioNew userShow;

    puts("\n---------------------\n");
    printf("DNI: %i", userShow.dni);
    printf("Nombre y apellido: %s", userShow.nombreYapellido);
    printf("Usuario: %s", userShow.nombreUser);
    printf("Telefono: %i", userShow.telefono);
    puts("\n---------------------\n");
}

void crearUsuario(char fileUser[])
{
    usuarioNew usuarioCreacion;

    FILE *creacion;

    creacion = fopen(fileUser, "ab");

    if(creacion!=NULL)
    {
        usuarioCreacion = crearUnUsuario();

        fwrite(&usuarioCreacion, sizeof(usuarioNew), 1, creacion);

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

int validarProductosId(char fileProducts[], producto *arr[], int pos)
{
    producto prodValidacion;

    FILE *validarProductos;

    validarProductos = fopen(fileProducts, "rb");

    int val = 0;

    if(validarProductos!=NULL)
    {
        while(!feof(validarProductos))
        {
            fread(&prodValidacion, sizeof(producto), 1, validarProductos);

            if(!feof(validarProductos) && prodValidacion.idProducto == arr[pos]->idProducto)
            {
                val = 1;
            }
            else
            {
                val = 0;
            }
        }
    }
}

void cargarProductos(producto arr[dim])
{
    int i = 0;
    char eleccion = 's';
    int capturaCheck = 0;

    while(i<dim && eleccion == 's')
    {
        arr[i] = cargaUnProducto();

//        capturaCheck = validarProductosId(fileProducts, arr[], i);

        if(capturaCheck == 1)
        {
            printf("El producto existe en la base de datos, desea agregar cantidad al producto.");///VER
        }
        else
        {
            printf("El producto no existe en base de datos, desea cargarlo?");///VER
        }

        i++;
    }

}

void confirmarProductoExistente(char fileProducts[], producto arr[], int validos)
{
    producto prodActualizado;

    int i = 0;

    FILE *actualizado;

    actualizado = fopen(fileProducts, "a+b");

    if(actualizado!=NULL)
    {
        while(!feof(actualizado) && i < validos)
        {
            fread(&prodActualizado, sizeof(producto), 1, actualizado);

            if(!feof(actualizado) && arr[i].idProducto == prodActualizado.idProducto)
            {
                fseek(actualizado, (-1)*sizeof(producto), SEEK_CUR);
                prodActualizado = arr[i];
                fwrite(&prodActualizado, sizeof(producto), 1, actualizado);
            }
        }
        fclose(actualizado);
    }
}

void confirmarProductos(char fileProducts[], producto arr[], int validos)
{
    producto prodCopia;
    int i = 0;

    FILE *confirmar;

    confirmar = fopen(fileProducts, "ab");

    if(confirmar!=NULL)
    {
        while(i<validos)
        {
            prodCopia = arr[i];
            fwrite(&prodCopia, sizeof(producto), 1, confirmar);
            i++;
        }
        fclose(confirmar);
    }
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


void mostrarProductosEnMatriz(char nombreArchivo[], producto arr[], int validos)
{
    printf("%-12s %-12s %-12s %-12s %-12s\n", "ID", "Producto", "Precio", "Cantidad", "Total"); //EL %-12s funciona de la siguiente manera el " - " indica que se aplicará un justificado a la izquierda.
    //El 12 indica que la cadena se mostrará en un campo de ancho fijo de 12 caracteres.
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < validos; i++)
    {
        if (fread(&arr[i], sizeof(producto), 1, archivo) == 1 && arr[i].idProducto != -1)
        {
            printf("%-12i %-12s $%-11.2f %-12i $%-11.2f\n", arr[i].idProducto, arr[i].claseProducto, arr[i].precio, arr[i].cantidad, arr[i].precio * arr[i].cantidad);
        }
    }

    fclose(archivo);
}

//case 4 //BUSCA EL PRODUCTO POR EL ID PERO SI HAY MUCHOS PRODUCTOS CON UN MISMO ID SOLO MUESTRA UNO SOLO.
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
            // Marcamos el producto como eliminado
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

void ventasReduccion(char fileProducts[], int idVentas, int cantidad)
{
    producto prodVentas;

    FILE *ventas;

    ventas = fopen(fileProducts, "w+b");

    if(ventas!=NULL)
    {
        while(!feof(ventas))
        {
            fread(&prodVentas, sizeof(producto), 1, ventas);

            if(!feof(ventas) && prodVentas.idProducto == idVentas)
            {
                prodVentas.cantidad -= cantidad;
                fseek(ventas, (-1)*sizeof(producto), SEEK_CUR);
                fwrite(&prodVentas, sizeof(producto), 1, ventas);
            }
        }
    }
}




//int contarVenta(int cantidad)
//{
//    Pila pila1, aux;
//    inicpila(&pila1);
//
//    int i = 0;
//
//    while(i<=cantidad)
//    {
//        apilar(&pila1, 1);
//        i++;
//    }
//    return i;
//}
