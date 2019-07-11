#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h>
#include<dirent.h>
  
#define MAXCOM 1000 // max number of letters to be supported 
#define MAXLIST 100 // max number of commands to be supported 
  
// Clearing the shell using escape sequences 
#define clear() system("clear"); 
  
// Greeting shell during startup 
void init_shell() 
{ 
    clear(); 
    printf("\n\n\n\n******************"
        "************************"); 
    printf("\n\n\n\t****NUESTRO SHELL****"); 
    printf("\n\n\t-SISTEMAS OPERATIVOS-"); 
    printf("\n\n\n\n*******************"
        "***********************"); 
    char* username = getenv("USER"); 
    printf("\n\n\nUsuario ingresante: @%s", username); 
    printf("\n"); 
    sleep(2); 
    clear(); 
} 

// Function to take input 
int takeInput(char* str) 
{ 
    char* buf; 
  
    buf = readline("\n> "); 
    if (strlen(buf) != 0) { 
        add_history(buf); 
        strcpy(str, buf); 
        return 0; 
    } else { 
        return 1; 
    } 
} 
  
// Function to print Current Directory. 
void printDir() 
{ 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("\nDirectorio actual: %s", cwd); 
}

//método secundario de directorio.
void printDir2()
{
   char cwd[1024];
   getcwd(cwd, sizeof(cwd));
   printf("%s", cwd);

} 
  
// Function where the system command is executed 
void execArgs(char** parsed) 
{ 
    // Forking a child 
    pid_t pid = fork();  
  
    if (pid == -1) { 
        printf("\nERROR: Failed forking child.."); 
        return; 
    } else if (pid == 0) { 
        if (execvp(parsed[0], parsed) < 0) { 
            printf("\nNo se puede ejecutar o no existe ese comando..."); 
        } 
        exit(0); 
    } else { 
        // waiting for child to terminate 
        wait(NULL);  
        return; 
    } 
} 
  
// Function where the piped system commands is executed 
void execArgsPiped(char** parsed, char** parsedpipe) 
{ 
    // 0 is read end, 1 is write end 
    int pipefd[2];  
    pid_t p1, p2; 
  
    if (pipe(pipefd) < 0) { 
        printf("\nERROR:Pipe no pudo ser inicializado..."); 
        return; 
    } 
    p1 = fork(); 
    if (p1 < 0) { 
        printf("\nERROR:Could not fork"); 
        return; 
    } 
  
    if (p1 == 0) { 
        // Child 1 executing.. 
        // It only needs to write at the write end 
        close(pipefd[0]); 
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]); 
  
        if (execvp(parsed[0], parsed) < 0) { 
            printf("\nERROR: Could not execute command 1..."); 
            exit(0); 
        } 
    } else { 
        // Parent executing 
        p2 = fork(); 
  
        if (p2 < 0) { 
            printf("\nERROR: Could not fork"); 
            return; 
        } 
  
        // Child 2 executing.. 
        // It only needs to read at the read end 
        if (p2 == 0) { 
            close(pipefd[1]); 
            dup2(pipefd[0], STDIN_FILENO); 
            close(pipefd[0]); 
            if (execvp(parsedpipe[0], parsedpipe) < 0) { 
                printf("\nERRO: Could not execute command 2.."); 
                exit(0); 
            } 
        } else { 
            // parent executing, waiting for two children 
            wait(NULL); 
            wait(NULL); 
        } 
    } 
} 
  
// Help command builtin 
void openHelp() 
{ 
    puts("\n***ASISTENTE DE AYUDA DE SHELL***"
        "\nPABLO BARONA - SANTIAGO RAMIREZ - JULIAN SANCHEZ - SUPROTIK DEY"
        "\nSISTEMAS OPERATIVOS"
        "\nLISTA DE COMANDOS SOPORTADOS:"
        "\n>cd - ir a directorio"
        "\n>clr - limpiar pantalla"
        "\n>quit - salir del programa"
        "\n>Otros comandos del shell de Unix"
        "\n>dir - contenido del directorio"
        "\n>echo - escribe el texto ingreado en pantalla"
        "\n>pause - pausa el Shell hasta undir enter"
        "\n>mkdir - crear un directorio en el directorio actual"
        "\n>hello - algo oculto..."
        "\n>./shellJPS texto.shell - ejecuta los comandos dados en texto.shell, mientras los comandos sean los de esta lista"
        "\n>environ - muestra la lista de todos los caracteres environment"); 
  
    return; 
} 
  
// Function to execute builtin commands 
int ownCmdHandler(char** parsed) 
{ 
    int NoOfOwnCmds = 10, i, switchOwnArg = 0; 
    char* ListOfOwnCmds[NoOfOwnCmds]; 
    char* username;
     
    ListOfOwnCmds[0] = "quit"; 
    ListOfOwnCmds[1] = "cd"; 
    ListOfOwnCmds[2] = "help"; 
    ListOfOwnCmds[3] = "hello";
    ListOfOwnCmds[4] = "clr";
    ListOfOwnCmds[5] = "echo";
    ListOfOwnCmds[6] = "dir";
    ListOfOwnCmds[7] = "mkdir";
    ListOfOwnCmds[8] = "environ";
    ListOfOwnCmds[9] = "pause";
 
    for (i = 0; i < NoOfOwnCmds; i++) { 
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) { 
            switchOwnArg = i + 1; 
            break; 
        } 
    } 
  
    switch (switchOwnArg) { 
    case 1: 
        printf("\nCERRANDO SHELL...\n");
        sleep(1); 
        exit(0); 
    case 2:
        if (parsed[1] != NULL){ 
          if (chdir(parsed[1]) != 0)
          {
            printf("Este directorio no existe.\n");
          }
          else
          {
            printf("Entrando a: %s.\n", parsed[1]);
            chdir(parsed[1]);
          }
        }else{
          printf("No hay argumento\n");
          printf("Manteniéndose en ");
          printDir2();
        }
        return 1; 
    case 3: 
        openHelp(); 
        return 1; 
    case 4: 
        username = getenv("USER"); 
        printf("\nSaludos %s.\n Éste es el shell JPS "
            "\nJPS siglas del grupo que lo creó."
            "\nInteresante que me descubrieras, soy un prototipo de Suprotik Dey\n", 
            username); 
        return 1; 
    case 5:
        clear();
        return 1;
    case 6:
        if (parsed[1] == NULL){
          printf("No se ha ingresado texto\n"); 
        }else{
        int p = 1;
        while(parsed[p] != NULL){
         printf("%s ",parsed[p]);
         p = p + 1;
         }
        printf("\n");
        }
       return 1;
    case 7:
    if (parsed[1] == NULL){
       system("ls");
    }else{
     if (chdir(parsed[1]) !=0){
     printf("El directorio no existe.\n");
     }else{
     chdir("..");
     DIR *d;
     struct dirent *dir;
     d = opendir(parsed[1]);

     if (d){
         while ((dir = readdir(d)) != NULL) {
             printf("%s\n", dir->d_name);
         }
         closedir(d);
      }
     }

    }

       return 1;
     case 8:
     mkdir(parsed[1], 0777);
     return 1;
     case 9:
       system("printenv");
     return 1;
     case 10:
     printf("\n");
     char temporal;
     printf("Shell en pausado. Presione Enter para continuar.\n");
     scanf("%c", &temporal);
     return 1;
    default: 
        break; 
    } 
  
    return 0; 
} 
  
// function for finding pipe 
int parsePipe(char* str, char** strpiped) 
{ 
    int i; 
    for (i = 0; i < 2; i++) { 
        strpiped[i] = strsep(&str, "|"); 
        if (strpiped[i] == NULL) 
            break; 
    } 
  
    if (strpiped[1] == NULL) 
        return 0; // returns zero if no pipe is found. 
    else { 
        return 1; 
    } 
} 
  
// function for parsing command words 
void parseSpace(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, " "); 
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
} 
  
int processString(char* str, char** parsed, char** parsedpipe) 
{ 
  
    char* strpiped[2]; 
    int piped = 0; 
  
    piped = parsePipe(str, strpiped); 
  
    if (piped) { 
        parseSpace(strpiped[0], parsed); 
        parseSpace(strpiped[1], parsedpipe); 
  
    } else { 
  
        parseSpace(str, parsed); 
    } 
  
    if (ownCmdHandler(parsed)) 
        return 0; 
    else
        return 1 + piped; 
} 
  
int main(int argc, char *argv[]) 
{
     
    char inputString[MAXCOM], *parsedArgs[MAXLIST]; 
    char* parsedArgsPiped[MAXLIST]; 
    int execFlag = 0;
    char linea[256];
    char *palabra[(256+1)/2];
    FILE *entrada;
    int num_ln;
    int num_pl;
    int i;

    if (argv[1] != NULL){
    /////
    printf("Procesando en Shell, archivo %s...\n", argv[1]);
    /* Abrir archivo y verificar errores */
   if ((entrada = fopen(argv[1], "r")) == NULL){
      perror(argv[1]);
      printf("Archivo %s no existe en el directorio actual.\n", argv[1]);
      return EXIT_FAILURE;
   }
   
   /* Procesar cada una de las lineas del archivo */
   for (num_ln = 0; fgets(linea, 256, entrada) != NULL; num_ln++){
      
      /* Separar cada linea en palabras */
      num_pl = 0;
      palabra[num_pl] = strtok(linea, " \n");
      while (palabra[num_pl] != NULL)
         palabra[++num_pl] = strtok(NULL, " \n");
      
      printf("", num_ln + 1, num_pl);
      for (i = 0; i < num_pl; i++)
         printf("", i + 1, palabra[i]);
         ownCmdHandler(palabra);
        //
   }
   /* Verificamos si la salida del bucle fue causada por un error */
   if (ferror(entrada)){
      perror(argv[1]);
      fclose(entrada);
      return EXIT_FAILURE;
   }
   printf("Terminando de procesar %s. Cerrando Shell.\n", argv[1]);
   fclose(entrada);


    /////       
    }else{ 
    init_shell(); 
  
    while (1) { 
        // print shell line 
        printDir(); 
        // take input 
        if (takeInput(inputString)) 
            continue; 
        // process 
        execFlag = processString(inputString, 
        parsedArgs, parsedArgsPiped); 
        // execflag returns zero if there is no command 
        // or it is a builtin command, 
        // 1 if it is a simple command 
        // 2 if it is including a pipe. 
  
        // execute 
        if (execFlag == 1) 
            execArgs(parsedArgs); 
  
        if (execFlag == 2) 
            execArgsPiped(parsedArgs, parsedArgsPiped); 
    } 
      printf("holaaa\n");
    }
    return 0; 
} 
