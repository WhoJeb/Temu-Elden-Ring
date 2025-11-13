#include <stdlib.h>
#include <unistd.h> // For sleep()
#include <string.h> // For strcmp()
#include <stdio.h> // for rand()
#include <time.h>

void RefreshScreen() {
  printf("\033[2J"); // Clears the entire screen
  printf("\033[H");  // Moves the cursor to the top-left corner (0,0)
}

int rv(int a, int b) {
  srand(time(NULL));
  int c = rand() % (b - a + 1); // max - min + 1
  return c;
}

void play(char *boss, int siege) {
  if (siege == 1) {
    RefreshScreen();
    printf("---- SIEGE ----\n\n");
  } else {
    RefreshScreen();
  }
  printf("%s challenges you to battle\n\n", boss);

  int health_mod = 10;
  int boss_health = rv(1, health_mod);
  int player_damage;

  printf("Hint: %d\n", boss_health);

  printf("Enter a value between 1 and %d -> ", health_mod);
  scanf("%d", &player_damage);

  if (boss_health == player_damage) {
    RefreshScreen();
    printf("%s Vanquished\n", boss);
    sleep(2);
    RefreshScreen();

  } else {
    printf("You Died\n");
    exit(0);
  }
}

int main() {
  char bosses[][35] = {
    "Malenia, Blade of Miquella",
    "Radagon of the Golden Order",
    "Godfrey, First Elden Lord",
    "Starscourge Radahn",
    "Alecto, Black Knife Ringleader",
    "Elden Beast",
    "Divine Beast Dancing Lion", 
    "Blackgaol Knight", 
    "Black Knight Edredd", 
    "Red Wolf of Radagon",
    "Beastman of Farum Azula (Duo)",
    "Crucible Knight Ordovis",
    "Loretta, Knight of the Haligtree",
    "Lichdragon Fortissax",
    "Death Rite Bird", 
    "Margit, the Fell Omen", 
    "Night's Cavalry",
    "Deathbird",
    "Bloodhound Knight Darriwil",
    "Black Knife Assassin",
    "Ancient Hero of Zamor",
    "Leonine Misbegotten",
    "Rennala, Queen of the Full Moon",
    "Ancient Dragon Lansseax",
    "Godskin Apostle",
    "Erdtree Burial Watchdog",
    "Sanguine Noble",
    "Flying Dragon Greyll",
    "Spirit-Caller Snail",
    "Soldier of Godrick",
    "Flying Dragon Agheel"
  }; 

  while (1) {
    int rush = rv(1, 5);
    int index = rv(sizeof(bosses) / sizeof(bosses[0]), 0);

    // Siege Mode
    if (rush == 3) {
      printf("You discovered the castle of %s\n", bosses[index]);
      printf("Do  you wish to lay siege? (y/n) -> ");
      char str[3];
      scanf("%s", str);
      if (strcmp(str, "y") || strcmp(str, "Y")) {
        for (int i = 0; i < rush; i++) {
          play(bosses[i+rush], 1);
        }

        // Final Boss
        printf("You stumble upon the throne room\n");
        sleep(2);
        play(bosses[index], 1); // Fight the final boss of the castle
        printf("Successfully laid siege on %s's castle\n\n", bosses[index]);
        printf("Do you wish to continue (y/n) -> ");

        char str[3];
        scanf("%s", str);
        if (strcmp(str, "y") || strcmp(str, "Y")) {
          continue;
        } else if (strcmp(str, "n") || strcmp(str, "N")) {
          return 0; // Still not working correctly
        } else {
          printf("Invalid input");
          return 1;
        }
      } else if (strcmp(str, "n") || strcmp(str, "N")) {
        continue;
      } else {
        printf("Invalid input");
        exit(1);
      }
    }
    
    // Regular Gameplay
    play(bosses[index], 0);
  }

  return 0;
}
