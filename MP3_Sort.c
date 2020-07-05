#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <dirent.h>

#define MAX_FILES 500
#define MAX_STRING 10

int Get_numfiles(char *file_format);
char ** build_array ();
void print_strings(char *p[], int n);
int *convert_array_string_to_int(char *p[], int n);
void print_int(int arr[], int n);
int *sort_int(int str[], int n) ;
void rename_clear_numerical(char *oldname[], int n);
void check_increment_correct(int arr[], int n);
void rename_num_to_alpha(int arr[], int n);


int main() {
char **arr_files = build_array();
  if (!arr_files) {
    printf ("ERROR: Unable to allocate arr_files!\n");
    return 1;
  } 

    //printf ("%s\n%s\n", arr_files[0], arr_files[1]);
    int num_files = Get_numfiles(".mp3");
    printf("Number of files: %d\n", num_files);
    print_strings(arr_files, num_files);

    int *int_arr = convert_array_string_to_int(arr_files,num_files);
    sort_int(int_arr, num_files);
    check_increment_correct(int_arr, num_files);
    rename_num_to_alpha(int_arr, num_files);
    getch();
    
return 0;
}

void rename_num_to_alpha(int arr[], int n) {
    char c, h;
    int cnt=0;
    char oldname[10];
    for (c = 'A'; c <= 'Z'; c++) {
        for (h = 'A'; h <= 'Z'; h++) {
            if(cnt>=n)
                break;
            sprintf(oldname, "%d%s", arr[cnt], ".mp3");
            char newname[10] = {c, h, '.','m','p','3','\0'};
            if ( rename( oldname, newname ) == 0 ) {
                printf("[%d]\t= %s \t->\t %s\n",cnt, oldname, newname);
            } else {
                fprintf(stderr, "EXIT PROGRAM, An error has occurred renaming %s.\n", oldname);
                getch();
                exit(0);
            }
            cnt++;
        }
    }
}

void check_increment_correct(int arr[], int n) {
    int check;
    for (int i = 0; i < n; i++) {
        if(i==n-1)
            break;
        check = arr[i+1] - arr[i];
        if(check != 1) {
            printf("ERROR, Files not sorted increment correctly. Problem: %d.mp3\n", arr[i]);
            getch();
            exit(0);
        }
    }
    printf("All files sorted increment correctly!\n");
}


void rename_clear_numerical(char *oldname[], int n) { /*NOT USE*/
    int count;
    char newname[10];
    int x;

    for (count = 0; count < n; count++) {
        x = atoi(oldname[count]);
        sprintf(newname, "%d", x);
        strcat(newname,".mp3");
        printf("%s \t\t\t--> \t\t\t%s\n", oldname[count], newname);

        if ( rename( oldname[count], newname ) == 0 ) {
            printf("%s has been renamed %s.\n", oldname[count], newname);
        }
        else {
            fprintf(stderr, "EXIT PROGRAM, An error has occurred renaming %s.\n", oldname[count]);
            getch();
            exit(0);
        }
    }
}


int *sort_int(int str[], int n) {
  int i, j, temp;
  for(i=0; i<n; i++) {
    for(j=i+1; j<n; j++){
      if(str[i] > str[j]) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
      }
    }
  }
return str;
}

int *convert_array_string_to_int(char *p[], int n) {
    int count;
    int *int_niz = malloc (sizeof (int *) * n);
    if (!int_niz) {
        printf("Ne moze da alocira\n");
        return NULL;
    }
    for (count = 0; count < n; count++) {
        int_niz[count] = atoi(p[count]);
    }
    return int_niz;
}

void print_strings(char *p[], int n) {
    int count;
    for (count = 0; count < n; count++)
        printf("%s,  ", p[count]);
    printf("\n");        
}

void print_int(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

char ** build_array () {
  int i = 0;
  char **array = malloc (sizeof (char *) * MAX_FILES);
  if (!array)
    return NULL;
  for (i = 0; i < MAX_FILES; i++) {
    array[i] = malloc (MAX_STRING + 1);
    if (!array[i]) {
      free (array);
      return NULL;
    }
  }

    struct dirent *de; 
    DIR *dr = opendir("."); 
    if (dr == NULL)  { 
        printf("Could not open current directory" ); 
        return 0; 
    } 
    int cnt=0;
    while ((de = readdir(dr)) != NULL)  {
        if (strstr(de->d_name, ".mp3")){
            strncpy (array[cnt], de->d_name, MAX_STRING);
            cnt++;
            if (cnt>=MAX_FILES) {
                printf("Too much files! MAX: %d\n", MAX_FILES);
                exit(0);
            }
        }
    }
    closedir(dr);
 /* BUILD ARRAY
    strncpy (array[0], "ABC", MAX_STRING);
    strncpy (array[1], "123", MAX_STRING);
    strncpy (array[2], "456", MAX_STRING); 
*/
  return array;
}

int alpha(char *p1, char *p2) {
    return(strcmp(p2, p1));
}

int reverse(char *p1, char *p2) {
    return(strcmp(p1, p2));
}

int Get_numfiles(char *file_format) {
    struct dirent *de; 
    DIR *dr = opendir("."); 
    if (dr == NULL)  { 
        printf("Could not open current directory" ); 
        return 0; 
    } 
  
    int i=0;
    while ((de = readdir(dr)) != NULL)  {
        if (strstr(de->d_name, file_format)){
            i++;
        }
    }
    closedir(dr);
    return i;
}



