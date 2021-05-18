#include "get_next_line.h"

void    gnl(int file)
{
    char *tmp;
    int  return_val;

    return_val = get_next_line(file, &tmp);
    printf("Return value = %i\n", return_val);
    printf("%s\n\n", tmp);
    free(tmp);
}


int main(void)
{
    char *tmp;
    int return_val;

    int file1 = open("file1", O_RDONLY);
    int file2 = open("file2", O_RDONLY);
    int file3 = open("file3", O_RDONLY);
    // return_val = get_next_line(file, &tmp);
    // printf("%i\n", return_val);
    // printf("%s\n", tmp);
    // return_val = get_next_line(file, &tmp);
    // printf("%i\n", return_val);
    // printf("%s\n", tmp);

    while ((return_val = get_next_line(file2, &tmp)) > 0)
    {
        printf("Return value = %i\n", return_val);
        printf("%s\n\n", tmp);
        free(tmp); // need to keep freeing here...

        return_val = get_next_line(file1, &tmp);
        printf("Return value = %i\n", return_val);
        printf("%s\n\n", tmp);
        free(tmp); // need to keep freeing here...
    }
    printf("Return value = %i\n", return_val);
    printf("%s\n\n", tmp);
    free(tmp);

    return_val = get_next_line(file1, &tmp);
    printf("Return value = %i\n", return_val);
    printf("%s\n\n", tmp);
    free(tmp); // need to keep freeing here...
    // char buff[100];
    // return_val = read(file, buff, 0);
    // printf("%i\n", return_val);
    // printf("%s\n", buff);

    close(file1);
    close(file2);
    close(file3);
}