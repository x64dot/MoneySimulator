#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>

int check_dir();
void create();
void save(int cash);
int load_cash();
void help();
int beg();
int hack();
int balance(int balance);
void lower_string();

struct PlayerData{
    int cash;
    int rebirths; /* Coming soon */
};

int main(){
    char input[10];
    struct PlayerData* player = (struct PlayerData*)malloc(sizeof(struct PlayerData));

    if (player == NULL){
        return -1;
    }
    
    if(check_dir() == -1){
        create();
    }
    else{
        player->cash = load_cash();
    }

    while (1){
        srand(time(NULL));
        int track = 0;

        printf("Input command: ");

        if (fgets(input, 8, stdin) == NULL){
            free(player);
            printf("Error: Input too long.");

            return -1;
        }

        input[strcspn(input, "\n")] = '\0';

        lower_string(input);

        if (strcmp(input, "help") == 0){
            help();

            save(player->cash);
        }
        else if (strcmp(input, "beg") == 0){
            usleep(4000000);
            track = beg();
            player->cash += track;
            printf("you earned %d from begging!\n", track);

            save(player->cash);

        }
        else if (strcmp(input, "balance") == 0 || strcmp(input, "bal") == 0){
            track = balance(player->cash);

            printf("Cash balance %d\n", track);

            save(player->cash);
        }
        else if (strcmp(input, "hack") == 0){
            usleep(8000000);
            
            track = hack();

            if (track == 100){
                player->cash -= 100;
                puts("You have lost 100 money, due to the fail of the hack.");
            }
            else{
                player->cash += track;
            }
            

            save(player->cash);

        }
        else if (strcmp(input, "exit") == 0){
            save(player->cash);

            free(player);
            return 0;
        }
        else {
            save(player->cash);
            puts("Invalid command.");
        }
  
    }



    free(player);

    return 0;
}

int check_dir(){
    DIR* dir = opendir("/.SimData");

    if (dir == NULL){
        if (errno == ENOENT){
            return -1;
        }
    }

    closedir(dir);
}

void create(){
    FILE* fptr;
    FILE* fptr2;
    mkdir("/.SimData", S_IRWXU | S_IRWXG | S_IRWXO);

    if ((fptr = fopen("/.SimData/data.txt", "r")) == NULL){
        
        fptr2 = fopen("/.SimData/data.txt", "w");

        fclose(fptr);
        fclose(fptr2);

        return;
    }

    fclose(fptr);
    fclose(fptr2);

    return;
}

void save(int cash){
    FILE* fptr;
    char *money;

    money = (char *)malloc(sizeof(char) * 30);
    if (money == NULL) {
        return;
    }


    sprintf(money, "%d", cash);

    
    fptr = fopen("/.SimData/data.txt", "w");
    if (fptr == NULL) {
        free(money);
        return;
    }

    
    if (fprintf(fptr, "%s", money) < 0) {
        free(money);
        fclose(fptr);
        return;
    }

    fclose(fptr);
    free(money);

}

int load_cash(){
    FILE* fptr;

    fptr = fopen("/.SimData/data.txt", "r");

    if (fptr == NULL){
        return 0;
    }

    int cash;
    fscanf(fptr, "%d", &cash);
    
    fclose(fptr);

    return cash;
}

void help(){
    puts("---------------------------");

    puts("Command: \"beg\" to earn money");
    puts("Command: \"hack\" to earn money but with the risk of losing money.");
    puts("Command: \"balance/bal\" to check your balance");

    puts("---------------------------");
}

int beg(){
    return (rand() % 30) + 1;
}

int hack(){
    int random = rand() % 51; 
    random += 50;

    char* arrm[] = {"You have hacked a random stranger successfully!",
                   "You have hacked the FBI, and stole a good portion of their money!"};
    char* arrc[] = {"You have been caught by the FBI and have been forced to pay 100 in cash.",
                    "You have been caught by the NSA and have been forced to pay 100 in cash."};

    for (int i = 2; i * i <= random; i++) {
        if (random % i == 0) {
            srand(time(NULL));

            int rand_int = rand() % 2;

            if (rand_int == 0){
                printf("%s\n", arrm[0]);
                return random;
            }
            else{
                printf("%s\n", arrm[1]);
                return random;
            }
        }

    }

    srand(time(NULL));
    int rand_int = rand() % 2;

    printf("%s\n", arrc[rand_int]);

    return 100;
    
}

int balance(int balance){
    return balance;
}

void lower_string(char *str){
    for (int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }

    return;
}
