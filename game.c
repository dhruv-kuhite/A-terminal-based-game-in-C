#include "game.h"

void setGridZero()
{
  for (int i = 0; i < 12; i++)
  {
    gameMatrix[i][0] = '|';
    gameMatrix[i][30] = '|';
    for (int j = 1; j < 30; j++)
    {
      if (i == 0 || i == 11)
        gameMatrix[i][j] = '=';
      else
        gameMatrix[i][j] = ' ';
    }
  }
}

void displayGrid()
{

  for (int i = 0; i < 12; i++)
  {

    for (int j = 0; j < 31; j++)
    {

      printf("%c", gameMatrix[i][j]);
    }
    printf("\n");
  }
}

void displaySpaceShip()
{
  int j = 0;

  for (int i = 1; i < current_ship_coordinate; i++)
  {
    gameMatrix[10][i] = ' ';
  }

  for (int i = current_ship_coordinate + 5; i < 30; i++)
  {
    gameMatrix[10][i] = ' ';
  }

  for (int i = current_ship_coordinate; i < current_ship_coordinate + 5; i++)
  {

    gameMatrix[10][i] = spaceship[j];
    j++;
  }
}

void MoveShipAndAttack()
{

  if (_kbhit())
  {

    char key = _getch();

    if ((key == 'a' || key == 'A') && current_ship_coordinate > min_ship_dis)
    {
      current_ship_coordinate--;
    }

    else if ((key == 'd' || key == 'D') && current_ship_coordinate < max_ship_dis)
    {
      current_ship_coordinate++;
    }
    else if ((key == 'e' || key == 'E'))
    {
      int attakpoint = current_ship_coordinate + 2;
      gameMatrix[9][attakpoint] = '^';
    }
  }
}

int checkPreviousValue(int astroid[], int size, int check)
{

  for (int i = 0; i < size; i++)
  {

    if (check == astroid[i])
    {
      check >= 29 ? check = 1 : check++;
    }
  }
  return check;
}

double attackDelay()
{
  LARGE_INTEGER count;
  QueryPerformanceCounter(&count);

  return ((double)count.QuadPart * 1000.0) / (double)freq.QuadPart;
}

void AstroidAttack()
{

  if (astroidPosition == 11)
  {
    astroidPosition = 1;
  }

  for (int i = 0; i < 5 && astroidPosition == 1; i++)
  {
    astroid[i] = (rand() % 29) + 1;

    astroid[i] = checkPreviousValue(astroid, i, astroid[i]);
  }

  for (int i = 0; i < 5; i++)
  {
    // printf("%d\n", astroid[i]);
    if (astroid[i] == -1)
    {
      continue;
    }

    gameMatrix[prevastroidPosition][astroid[i]] = ' ';
    gameMatrix[astroidPosition][astroid[i]] = '0';
  }

  prevastroidPosition = astroidPosition;
  astroidPosition++;
}

void CheckDamage()
{

  for (int i = current_ship_coordinate; i < current_ship_coordinate + 5; i++)
  {
    if (gameMatrix[10][i] == '0')
    {
      hp--;
    }
  }
}

void Moveshipattack()
{

  for (int i = 1; i < 10; i++)
  {

    for (int j = 1; j <= 29; j++)
    {
      if (i == 1 && gameMatrix[i][j] == '^')
      {
        gameMatrix[i][j] = ' ';
        continue;
      }
      else if (gameMatrix[i][j] == '^')
      {
        gameMatrix[i][j] = ' ';
        gameMatrix[i - 1][j] = '^';
      }
    }
  }
}

void checkZeroDestroyed()
{

  for (int i = 0; i < 5; i++)
  {
    if (astroid[i] == ' ')
    {
      continue;
    }

    if (gameMatrix[astroidPosition][astroid[i]] == '^')
    {
      gameMatrix[astroidPosition - 1][astroid[i]] = ' ';
      gameMatrix[astroidPosition][astroid[i]] = ' ';
      astroid[i] = -1;
      score++;
    }
    else if (gameMatrix[astroidPosition - 1][astroid[i]] == '^')
    {
      gameMatrix[astroidPosition - 1][astroid[i]] = ' ';
      gameMatrix[astroidPosition][astroid[i]] = ' ';
      astroid[i] = -1;
      score++;
    }
  }
}

int main()
{

  QueryPerformanceCounter(&freq);

  srand(time(NULL));

  printf("\x1b[?25l"); // hide cursor

  setGridZero(); // set grid valur to " " space

  PrevAttacktime = attackDelay();
  double prevshipAttack = attackDelay();
  double shipattack;
  while (hp > 0) // game loo[p]
  {

    system("cls");

    printf("  hp : %d          Score : %d\n", hp, score);

    displayGrid();

    CheckDamage();
    checkZeroDestroyed();

    attacktime = attackDelay();
    shipattack = attackDelay();

    displaySpaceShip();
    MoveShipAndAttack();

    // printf("%f",attacktime);
    if (attacktime - PrevAttacktime > 0.0010)
    {

      AstroidAttack();
      PrevAttacktime = attacktime;
    }

    if (shipattack - prevshipAttack > 0.0004)
    {

      prevshipAttack = shipattack;
      Moveshipattack();
    }

    printf("\n   Press A and D to MOVE :)");
    printf("\n     Press E to SHOOT");

    Sleep(7);
  }

  system("cls");

    printf("Score : %d\n",score);
  printf("Game Over :(");
  Sleep(3000);

  return 0;
}