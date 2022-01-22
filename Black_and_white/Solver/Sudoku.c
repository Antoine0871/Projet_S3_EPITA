#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef enum bool{
    false,
    true
}bool;

char grid[9][9];

void FillSudoku(char str[81]){
    int index = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if(str[index] == '.')
            {
                grid[i][j] = (0+48);
            }
            else{
                grid[i][j] = str[index];
            }
            index++;
        }
    }
}

void PrintSudo(){
    for (int i = 0; i < 9; i++)
    {
        if(i == 3 || i == 6)
            printf("\n");
        for (int j = 0; j < 9; j++)
        {
            printf("%c",grid[i][j]);
            if(j == 2 || j == 5)
                printf(" ");
        }
        printf("\n");
    }

}

bool is_column_solved(int x){
    char totest;
            for (int i = 0; i < 9; i++)
            {
                totest = grid[i][x];

                for (int j = i + 1; j < 9; j++)
                {
                    if (totest == grid[j][x])
                    {
                        return false;
                    }
                }
            }

            return true;
}


bool is_line_solved(int y){
    char totest;
        for (int i = 0; i < 9; i++)
        {
            totest = grid[y][i];

            for (int j = i + 1; j < 9; j++)
            {
                if (totest == grid[y][j])
                {
                    return false;
                }
            }
        }

        return true;
    }


bool is_square_solved(int x, int y){
    int topleftx = x - (x % 3);
    int toplefty = y - (y % 3);
    char totest;
    for (int testx = topleftx; testx < topleftx + 3; testx++)
    {
        for (int testy = toplefty; testy < toplefty + 3; testy++)
        {
            for (int i = topleftx; i < topleftx + 3; i++)
            {
                totest = grid[testx][testy];

                for (int j = testy; j < toplefty + 3; j++)
                {
                    if (totest == grid[i][j] && (j != testy || i != testx)
                    ) // j!= testy || i != testx, pour que je ne renvois pas false dans le cas ou je suis sur la même case
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}


bool is_solved()
    {
        for (int i = 0; i < 9; i++)
        {
            if (!is_line_solved(i))
            {
                return false;
            }

            if (!is_column_solved(i))
            {
                return false;
            }

            for (int j = 0; j < 9; j++)
            {
                if (!is_square_solved(i, j))
                {
                    return false;
                }
            }
        }

        return true;
    }


bool already_in_column(int x, int val)
    {
        for (int i = 0; i < 9; i++)
        {

            if ((val+48) == grid[i][x])
            {
                return true;
            }
        }

        return false;
    }


bool already_in_line(int y, int val)
    {
        for (int i = 0; i < 9; i++)
        {

            if ((val+48) == grid[y][i])
            {
                return true;
            }
        }

        return false;
    }


bool already_in_square(int x, int y, int val)
    {
        int topleftx = x - (x % 3);
        int toplefty = y - (y % 3);

        for (int i = topleftx; i < topleftx + 3; i++)
        {
            for (int j = toplefty; j < toplefty + 3; j++)
            {
                if ((val+48) == grid[i][j])
                {
                    return true;
                }
            }
        }

        return false;
    }


bool solve_rec(int x, int y)
        {
            x += y / 9;
            y = y % 9;
            if (x == 9)
                return true;

            if (grid[x][y] != (0+48))
            {
                return solve_rec(x, y + 1);
            }

            for (int k = 1; k <= 9; k++)
            {
                if (!already_in_line(x, k) && !already_in_column(y, k) && !already_in_square(x, y, k))
                {
                    grid[x][y] = (k+48);

                    if (solve_rec(x, y + 1))
                        return true;
                }
            }

            grid[x][y] = (0+48);
            return false;
        }


void solve()
        {
            solve_rec(0, 0);
        }


void Opentxt(FILE* fichier){
    int charActual = 0;
    int index = 0;
    char str[81];
    if(fichier != NULL)
    {
        do
        {
            charActual = fgetc(fichier);
           if((charActual> (0+48) && charActual <= (9+48)) || charActual == '.'){
               str[index] = charActual;
               index++;
           }
            
        } while (charActual != EOF);

        fclose(fichier);
    }
    FillSudoku(str);
}


void Createtxt(char* nameOftxt){
    FILE* fichier2 = NULL;
    fichier2 = fopen(nameOftxt,"w");

    for (int i = 0; i < 9; i++)
    {
        if(i == 3 || i == 6){
            fputs("\n",fichier2);
        }
        for (int j = 0; j < 9; j++)
        {
            if(j == 3 || j == 6){
                fputs(" ", fichier2);}
            fputc(grid[i][j],fichier2);
            
        }
        fputs("\n",fichier2);
    }
    fclose(fichier2);
}

void Solve_Sudoku(char path[])
{
    FILE* fichier = NULL;
    fichier = fopen(path, "r+");

    char nameOftxt[50];
    int index = 0;
    int i = 0;
    while(path[i] != '\0')
    {

            if (path[i] == '.'){
                nameOftxt[index] = '.';
                index++;
                nameOftxt[index] = 'r';
                index++;
                nameOftxt[index] = 'e';
                index++;
                nameOftxt[index] = 's';
                index++;
                nameOftxt[index] = 'u';
                index++;
                nameOftxt[index] = 'l';
                index++;
                nameOftxt[index] = 't';
                index++;
            }
            nameOftxt[index] = path[i];
            index++;
	    i++;

    }
    nameOftxt[index++] = '\0';

    if(fichier != NULL)
    {
        Opentxt(fichier);
        solve();
        Createtxt(nameOftxt);
    }
}
/*
int main(int argc, char *argv[])
{
	argc++;	
	Solve_Sudoku(argv[1]);
	return 0;
}*/

