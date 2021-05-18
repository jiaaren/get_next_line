#include "get_next_line.h"

int main(void)
{
    char *tmp;
    int file;
    int return_val;

    file = open("textfile2.txt", O_RDONLY);
    // return_val = get_next_line(file, &tmp);
    // printf("%i\n", return_val);
    // printf("%s\n", tmp);
    // return_val = get_next_line(file, &tmp);
    // printf("%i\n", return_val);
    // printf("%s\n", tmp);

    while ((return_val = get_next_line(-1, &tmp)))
    {
        printf("Return value = %i\n", return_val);
        printf("%s\n", tmp);
        printf("\n");
        free(tmp); // need to keep freeing here...
    }
    printf("Return value = %i\n", return_val);
    printf("%s\n", tmp);

    // char buff[100];
    // return_val = read(file, buff, 0);
    // printf("%i\n", return_val);
    // printf("%s\n", buff);

    free(tmp);
    close(file);
}