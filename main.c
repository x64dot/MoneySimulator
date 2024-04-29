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

struct PlayerData{
    int cash;
    int rebirths;
};

int check_dir();
void create();
void save(int cash, int rebirths);
int load_cash(int *rebirths);
void help();
int beg(int rebirths);
int hack(int rebirths);
int balance(int balance);
void lower_string();
void rebirth(struct PlayerData* player);
void rebirth_count(int rebirths);

int main(){
    char input[20];
    struct PlayerData* player = (struct PlayerData*)malloc(sizeof(struct PlayerData));

    if (player == NULL){
        return -1;
    }
    
    if(check_dir() == -1){
        create();
        player->cash = 0;
        player->rebirths = 0;
    }
    else{
        player->cash = load_cash(&(player->rebirths));
    }

    while (1){
        srand(time(NULL));
        int track = 0;

        printf("Input command: ");

        if (fgets(input, 18, stdin) == NULL){
            free(player);
            printf("Error: Input too long.");

            return -1;
        }

        input[strcspn(input, "\n")] = '\0';

        lower_string(input);
        
        if (strcmp(input, "help") == 0){
            help();
            save(player->cash, player->rebirths);
        }
        else if (strcmp(input, "beg") == 0){
            usleep(4000000);
            track = beg(player->rebirths);
            player->cash += track;
            printf("You earned %d from begging!\n", track);
            save(player->cash, player->rebirths);
        }
        else if (strcmp(input, "balance") == 0 || strcmp(input, "bal") == 0){
            track = balance(player->cash);
            printf("Cash balance: %d\n", track);
            save(player->cash, player->rebirths);
        }
        else if (strcmp(input, "hack") == 0){
            usleep(8000000);
            track = hack(player->rebirths);
            if (track == 100 * (player->rebirths + 1)){
                player->cash -= 100;
                puts("You have lost 100 money, due to the failure of the hack.");
            }
            else{
                player->cash += track;
            }
            save(player->cash, player->rebirths);
        }
        else if (strcmp(input, "rebirth") == 0){
            rebirth(player);
        }
        else if (strcmp(input, "exit") == 0){
            save(player->cash, player->rebirths);
            free(player);
            return 0;
        }
        else if (strcmp(input, "rebirths") == 0){
            save(player->cash, player->rebirths);
            rebirth_count(player->rebirths);
            
        }
        else {
            puts("Invalid command.");
            save(player->cash, player->rebirths);
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

    return 0;
}

void create() {
    FILE *fptr;
    FILE *fptr2;

    mkdir("/.SimData", S_IRWXU | S_IRWXG | S_IRWXO);

    if ((fptr = fopen("/.SimData/data.txt", "r")) == NULL) {
        fptr2 = fopen("/.SimData/data.txt", "w");
        if (fptr2 != NULL) { 
            fclose(fptr2);
        }
        return;
    }

    if (fptr != NULL) { 
        fclose(fptr);
    }
    return;
}

void save(int cash, int rebirths){
    FILE* fptr;
    char *data;

    data = (char *)malloc(sizeof(char) * 30);
    if (data == NULL) {
        return;
    }

    sprintf(data, "%d %d", cash, rebirths);

    fptr = fopen("/.SimData/data.txt", "w");
    if (fptr == NULL) {
        free(data);
        return;
    }

    if (fprintf(fptr, "%s", data) < 0) {
        free(data);
        fclose(fptr);
        return;
    }

    fclose(fptr);
    free(data);
}

int load_cash(int *rebirths){
    FILE* fptr;

    fptr = fopen("/.SimData/data.txt", "r");

    if (fptr == NULL){
        *rebirths = 0;
        return 0;
    }

    int cash;
    fscanf(fptr, "%d %d", &cash, rebirths);
    
    fclose(fptr);

    return cash;
}

void help(){
    puts("---------------------------");

    puts("Command: \"beg\" to earn money by begging.");
    puts("Command: \"hack\" to earn money but with the risk of losing money.");
    puts("Command: \"balance/bal\" to check your balance.");
    puts("Command: \"rebirth\" to be reborned, and earn more.");
    puts("Command: \"rebirths\" to check your rebirth count.");

    puts("---------------------------");
}

int beg(int rebirths){
    int base_cash = (rand() % 30) + 1;
    return base_cash * (rebirths + 1);
}

int hack(int rebirths){
    int random = rand() % 51; 
    random += 50;

    char* arrm[] = {"You have hacked a random stranger successfully!",
                   "You have hacked the FBI, and stole a good portion of their money!"};
    char* arrc[] = {"You have been caught by the FBI and have been forced to pay.",
                    "You have been caught by the NSA and have been forced to pay."};

    for (int i = 2; i * i <= random; i++) {
        if (random % i == 0) {
            srand(time(NULL));

            int rand_int = rand() % 2;

            if (rand_int == 0){
                printf("%s\n", arrm[0]);
                return (random * (rebirths + 1));
            }
            else{
                printf("%s\n", arrm[1]);
                return (random * (rebirths + 1));
            }
        }
    }

    srand(time(NULL));
    int rand_int = rand() % 2;

    printf("%s\n", arrc[rand_int]);

    return 100 * (rebirths + 1);
}

int balance(int balance){
    return balance;
}

void lower_string(char *str){
    for (int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

void rebirth(struct PlayerData* player) {
    int base_cost = 500;
    int cost = base_cost * (player->rebirths + 1);

    char input[10];
    while (1) {
        printf("Are you sure you want to rebirth? This will cost %d cash. (yes/no): ", cost);


        if (fgets(input, 8, stdin) == NULL) {
            printf("Error: Input too long.\n");
            return;
        }
        

        input[strcspn(input, "\n")] = '\0';

      
        lower_string(input);

        if (strcmp(input, "yes") == 0) {
            if (player->cash >= cost) {
                player->cash = 0;
                player->rebirths++;
                printf("Congratulations! You have been reborn. Your rebirth count is now %d.\n", player->rebirths);
            } else {
                printf("You don't have enough cash to rebirth.\n");
            }
            break; 
        } else if (strcmp(input, "no") == 0) {
            printf("Rebirth aborted.\n");
            break; 
        } else {
            printf("Invalid input. Please enter \"yes\" or \"no\".\n");
        }
    }
}

void rebirth_count(int rebirths){
    printf("Rebirth count: %d\n", rebirths);
}
