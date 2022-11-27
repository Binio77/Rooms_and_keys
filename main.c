#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define NAMESIZE 30

typedef struct Person
{
    char name[NAMESIZE];
    int number_of_keys, index;
}Person;

typedef struct Room
{
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

void output(Room *_rooms, int _number_of_rooms, Person *_people, int _num_of_people)
{
    printf("%i \n", _number_of_rooms);
    for (int i = 0; i < _number_of_rooms; i++)
    {
        Room *room = &_rooms[i];
        printf("loop i=%i", i);
        printf(" room=%i ", room->room_number);
        struct Person *pers = room->key_holder;
        if (pers != NULL)
            printf("%s %i",pers->name,pers->number_of_keys);
        else
            printf("EMPTY");
        printf("\n");
    }
}

void change_num_of_people(Person **_people, int _num_of_people)
{
    *_people = realloc(*_people, _num_of_people * sizeof(Person));
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
    int num_of_rooms, num_of_people = 0;
    int quit = 0;
    scanf("%i", &num_of_rooms);
    
    Room* rooms = malloc(num_of_rooms * sizeof(Room));
    input_room(rooms, num_of_rooms);
    Person* people = malloc(num_of_people * sizeof(Person));
    
    while (quit == 0)
    {
        printf("new loop -- Enter D/B/P/Q\n");
        getchar();
        char choice = getchar();
        switch (choice)
        {
            case 'D':
            {
                
                char name[NAMESIZE];
                int room_index;
                scanf("%s", name);
                scanf("%i", &room_index);
                
                num_of_people++;
                
                change_num_of_people(&people, num_of_people);
                Person new_person;
                new_person.number_of_keys = 1;
                strcpy(new_person.name, name);
                new_person.index = num_of_people - 1;
                Room *room = &rooms[room_index];

                if(room->key_holder != NULL)
                {
                    room->key_holder->number_of_keys--;
                    people[num_of_people - 1] = new_person;
                    room->key_holder = &(people[num_of_people - 1]);

                    if (room->key_holder->number_of_keys <= 0)
                    {
                        if(room->key_holder->index != num_of_people - 1)
                        {
                            for (int i = room->key_holder->index; i < num_of_people - 1; i++)
                            {
                                people[i] = people[i + 1];
                                people[i].index--;
                            }
                        }

                        num_of_people--;
                        change_num_of_people(&people, num_of_people);


                    }
                }
                else
                {
                    people[num_of_people - 1] = new_person;
                    room->key_holder = &(people[num_of_people - 1]);
                }

                break;
            }
            case 'B':
            {
                int persons_room_index, room_number, room_index;
                scanf("%i", &persons_room_index);
                scanf("%i", &room_number);
                room_index = find_room_index(rooms, room_number, num_of_rooms);

                if(room_index < 0)
                    printf("%c", '!');
                else
                {
                    rooms[persons_room_index].key_holder->number_of_keys++;
                    Room *room = &rooms[room_index];
                    room->key_holder->number_of_keys--;
                    rooms[room_index].key_holder = rooms[persons_room_index].key_holder;

                    if(room->key_holder->number_of_keys <= 0)
                    {
                        if(room->key_holder->index != num_of_people - 1)
                        {
                            for (int i = room->key_holder->index; i < num_of_people - 1; i++)
                            {
                                people[i] = people[i + 1];
                                people[i].index--;
                            }
                        }

                        num_of_people--;
                        change_num_of_people(&people, num_of_people);


                    }


                }
                break;
            }
            case 'P':
            {
                output(rooms, num_of_rooms, people, num_of_people);
                break;
            }
            case 'Q':
            {
                quit = 1;
                break;
            }
        }
    }
    
        
    free(rooms);
    free(people);
    return 0;
}

