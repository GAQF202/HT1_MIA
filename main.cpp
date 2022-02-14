#include <iostream>
#include <cstring>
using namespace std;

struct profesor{
    int id_profesor;
    char CUI[13];
    char nombre[25];
    char curso[25];
};

struct estudiante{
    int id_estudiante;
    char CUI[13];
    char nombre[25];
    char carnet[10];
};

int main()
{  
    // "HEADERS"
    void crearEstudiante();
    void crearProfesor();
    void leerArchivo();

    FILE *file;
    string input = "";
    string menu = "Nombre: Gerson Aaron Quinia Folgar\nCarnet:201904157\n1. Registro de Profesor\n2. Registro de Estudiante\n3. Ver Registros\n4. Salir\n";

    // VERIFICA QUE EL ARCHIVO EXISTA Y SI NO LO CREA
    if (!(file = fopen("./registros.bin", "r"))) 
    {
        file = fopen("./registros.bin", "wb");
        fclose(file);
    }

    // CICLO PARA QUE EL PROGRAMA SE EJECUTE
    while (true)
    {   
        cout << menu;
        cin >> input;
        if(strcmp(input.c_str(),"1")==0){
            crearProfesor();
        }else if(strcmp(input.c_str(),"2")==0){
            crearEstudiante();
        }else if(strcmp(input.c_str(),"3")==0){
            leerArchivo();
        }else if(strcmp(input.c_str(),"4")==0){
            return 0;
        }
    }
    

    return 0;
}

void crearEstudiante(){ 
    estudiante student;
    string input = "";
    // IDENTIFICADOR PARA SABER QUE ES UN ESTUDIANTE
    char id = 'e';
    FILE *file = fopen("./registros.bin", "ab");

    printf("Ingresa el id del estudiante\n");
    cin >> input;
    student.id_estudiante = atoi(input.c_str());
    printf("Ingresa el CUI del estudiante\n");
    cin >> input;
    strcpy(student.CUI,input.c_str());
    printf("Ingresa el Nombre del estudiante\n");
    cin >> input;
    strcpy(student.nombre,input.c_str());
    printf("Ingresa el Carnet del estudiante\n");
    cin >> input;
    strcpy(student.carnet,input.c_str());

    // ESCRIBE EN EL ARCHIVO LOS DATOS DE ESTUDIANTE
    fwrite(&id,sizeof(id),1,file);
    fwrite(&student,sizeof(estudiante),1,file);
    fclose(file);
}

void crearProfesor(){ 
    profesor teacher;
    string input = "";

    FILE *file = fopen("./registros.bin", "ab");
    char id = 'p';

    printf("Ingresa el id del profesor\n");
    cin >> input;
    teacher.id_profesor = atoi(input.c_str());
    printf("Ingresa el CUI del profesor\n");
    cin >> input;
    strcpy(teacher.CUI,input.c_str());
    printf("Ingresa el Nombre del profesor\n");
    cin >> input;
    strcpy(teacher.nombre,input.c_str());
    printf("Ingresa el Curso que imparte el profesor\n");
    cin >> input;
    strcpy(teacher.curso,input.c_str());

    // ESCRIBE EN EL ARCHIVO LOS DATOS DEL PROFESOR
    fwrite(&id,sizeof(id),1,file);
    fwrite(&teacher,sizeof(teacher),1,file);
    fclose(file);
}

void leerArchivo(){
    FILE *file = fopen("./registros.bin", "rb");

    // GUARDO EL TAMANIO DEL ARCHIVO PARA SABER HASTA DONDE RECORRERLO
    fseek(file,0,SEEK_END);
    int file_size = ftell(file);

    estudiante student;
    profesor teacher;
    // VARIABLE PARA MOVERME CON FSEEK
    int move=0;
    // VARIABLE PARA SABER QUE TIPO DE STRUCT VIENE
    char ver;
    // ME MUEVO A LA PRIMERA POSICION DEL ARCHIVO
    fseek(file,0,SEEK_SET);
    fread(&ver,1,1,file);
    fseek(file,1,SEEK_SET);

    // MIENTRAS NO LLEGUE AL FINAL DE ARCHIVO SIGUE RECORRIENDOSE
    while (move != file_size){

        if(ver == 'e'){

            fread(&student,sizeof(estudiante),1,file);
            cout << "----------ESTUDIANTE----------" << endl;
            cout << "Id:     " << student.id_estudiante << endl;
            cout << "CUI:    " << ((string)student.CUI).substr(0,13) << endl;
            cout << "Nombre: " << ((string)student.nombre).substr(0,25) << endl;
            cout << "Carnet: " << ((string)student.carnet).substr(0,10) << endl;
            cout << "------------------------------" << endl;
            // SUMO A LA VARIABLE DE MOVIMIENTO Y ME MUEVO AL SIGUIENTE CARACTER
            move += 53;
            fseek(file,move,SEEK_SET);
            fread(&ver,1,1,file);

        }else if(ver == 'p'){

            cout << "-----------PROFESOR-----------" << endl;
            fread(&teacher,sizeof(profesor),1,file);
            cout << "Id:     " << teacher.id_profesor << endl;
            cout << "CUI:    " << ((string)teacher.CUI).substr(0,13) << endl;
            cout << "Nombre: " << ((string)teacher.nombre).substr(0,25) << endl;
            cout << "Curso:  " << ((string)teacher.curso).substr(0,25) << endl;
            cout << "------------------------------" << endl;
            // SUMO A LA VARIABLE DE MOVIMIENTO Y ME MUEVO AL SIGUIENTE CARACTER
            move += 69;
            fseek(file,move,SEEK_SET);
            fread(&ver,1,1,file);

        }
    }

    fclose(file);
    
}