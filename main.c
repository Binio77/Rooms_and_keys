#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#define NAME_SIZE 100000

typedef struct Person {
    char name[100000];
    int key_count;
}Person;

typedef struct Room{
    int room_number;
    struct Person *key_holder;
}Room;

void input_room(Room *_rooms, int _number_of_rooms)
{
    for(int i = 0; i < _number_of_rooms; i++)
    {
        scanf("%i", &((_rooms + i)->room_number));
        (_rooms + i)->key_holder = NULL;
    }
}
void output(Room *_rooms, int _number_of_rooms)
{
    printf("%s\n", "LOG:");
    for (int i = 0; i < _number_of_rooms; i++)
    {
        Room *room = &_rooms[i];
        printf("Room %i: ", room->room_number);
        struct Person *pers = room->key_holder;
        if (pers != NULL)
            printf("%s, keys: %i",pers->name,pers->key_count);
        else
            printf(" - ");
        printf("\n");
    }
}

int find_room_index(Room *_rooms, int _room_number, int _num_of_rooms)
{
    for(int i = 0; i < _num_of_rooms; i++)
    {
        if((_rooms + i)->room_number == _room_number)
            return i;
    }
    return -1;
}

int main()
{
    int room_count;
    scanf("%i", &room_count);
    bool quit = false;
    Room* rooms = (Room*)malloc(sizeof(Room) * room_count);
    input_room(rooms, room_count);
    while(!quit) {
        char choice;
        getchar();
        choice = getchar();

        switch (choice) {
            case 'D': {
                char name[100000];
                int room_index;
                scanf("%i", &room_index);
                scanf("%s", name);
                Person *new_person = (Person*) malloc(sizeof(Person));
                new_person->key_count = 1;
                strcpy(new_person->name, name);
                Room *room = &rooms[room_index];
                if(room->key_holder != NULL)
                {

                    room->key_holder->key_count--;
                    if(room->key_holder->key_count <= 0)
                        free(rooms[room_index].key_holder);
                }
                rooms[room_index].key_holder = new_person;

                break;
            }
            case 'B': {
                int persons_room_index, room_number, room_index;
                scanf("%i", &persons_room_index);
                scanf("%i", &room_number);
                room_index = find_room_index(rooms, room_number, room_count);

                if(room_index < 0 || rooms[persons_room_index].key_holder == NULL)
                    printf("%c\n", '!');
                else {
                    rooms[persons_room_index].key_holder->key_count++;
                    Room *room = &rooms[room_index];
                    if(room->key_holder != NULL)
                        room->key_holder->key_count--;
                    rooms[room_index].key_holder = rooms[persons_room_index].key_holder;
                }
                break;
            }
            case 'P': {
                output(rooms, room_count);
                break;
            }
            case 'Q': {
                quit = true;
                break;
            }
        }
    }

    return 0;
}
