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
    puts("Command: \"balance/bal\" to check your balance");

    puts("---------------------------");
}

int beg(){
    return (rand() % 30) + 1;
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
