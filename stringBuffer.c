#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char *data;      
    size_t length;   
    size_t capacity; 
} StringBuffer;


StringBuffer *sb_init(size_t initial_capacity)
{
    if (initial_capacity == 0)
    {
        initial_capacity = 1; 
    }

   
    StringBuffer *sb = (StringBuffer *)malloc(sizeof(StringBuffer));

    
    if (sb == NULL)
        return NULL;

   
    sb->data = (char *)malloc(initial_capacity * sizeof(char));

   
    if (sb->data == NULL)
    {
        free(sb);
        return NULL;
    }

    
    sb->length = 0;

   
    sb->capacity = initial_capacity;

    
    sb->data[0] = '\0';

    return sb;
}


StringBuffer *sb_append(StringBuffer *sb, const char *str)
{
    size_t str_len = strlen(str);
    size_t required = sb->length + str_len + 1; 

    while (required > sb->capacity)
    {
        size_t new_capacity = sb->capacity * 2;

        char *new_data = realloc(sb->data, new_capacity * sizeof(char));
        if (new_data == NULL)
        {
            return NULL;
        }

        sb->data = new_data;
        sb->capacity = new_capacity;
    }

 
    strcpy(sb->data + sb->length, str);

    
    sb->length += str_len;

    return sb;
}


void sb_free(StringBuffer *sb)
{
    if (sb == NULL)
        return;
    free(sb->data); 
    free(sb);       
}


void sb_print(StringBuffer *sb)
{
    if (sb == NULL)
    {
        printf("\n\nStringBuffer is NULL\n");
        return;
    }
    printf("\n========== StringBuffer Contents ==========\n");
    printf("Contents: %s\n", sb->data);
    printf("Length: %zu\n", sb->length);
    printf("Capacity: %zu\n", sb->capacity);
    printf("========================================== \n\n");
}


int main()
{
    StringBuffer *sb = sb_init(0); 

    if (sb == NULL)
    {
        printf("Failed to initialize StringBuffer\n");
        return 1;
    }

    printf("Initial capacity of String: %zu\n\n", sb->capacity);

    int choice;
    char input[256];

    printf("========== StringBuffer Menu ==========\n");
    printf("1. Append\n");
    printf("2. Exit\n");
    printf("=======================================\n\n");

    while (1)
    {
        printf("Enter your choice (1-2): ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice)
        {
        case 1:
            printf("Enter string to append: ");
            fgets(input, sizeof(input), stdin);

            
            size_t len = strlen(input);
            if (len > 0 && input[len - 1] == '\n')
            {
                input[len - 1] = '\0';
            }

            if (sb_append(sb, input) == NULL)
            {
                printf("Failed to append string\n");
                sb_free(sb);
                return 1;
            }

            sb_print(sb);
            break;

        case 2:
            printf("Exiting...\n");
            sb_free(sb);
            return 0;

        default:
            printf("Invalid choice. Please enter 1 or 2.\n\n");
        }
    }

    return 0;
}