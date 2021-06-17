#include<iostream>
#include<fstream>
#include<windows.h>
#include<conio.h>
using namespace std;

COORD coord={0,0};

void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int temp = 0;
int read_hs;

class play_game1
{
    protected:
        int X = 14, Y = 14;
        int food_x = 5, food_y = 40;
        int tailX[100], tailY[100];
        int tail_count = 0;
        int flag = 0;
        int life = 3;

        int width=50, height=20;
        int small_bh=7, small_bw=20;
        int score_bh=7, score_bw=18;

        int abcd = 0;

    public:
        int gameOver = 0;
        static int score;
        void setup()
        {
            X = 14;
            Y = 14;
            if(X==food_x && Y==food_y)
            {
                label1:
                food_x = rand() % 20;
                if(food_x <= 0)
                    goto label1;

                label2:
                food_y = rand() % 50;
                if(food_y <= 0)
                    goto label2;
            }
        }

        void draw()
        {
            int i, j, k;
            gotoxy(0,0);
            for(i=0 ; i<(height+2) ; i++)
            {
                for(j=0 ; j<(width+2) ; j++)
                    cout << " ";
            }
            gotoxy(0,0);
            cout << "\n\n\n\n\t";
            for(i=0 ; i<height ; i++)
            {
                for(j=0 ; j<width ; j++)
                {
                    if(i==0 || i==(height-1) || j==0 || j==(width-1))
                    {
                        if(i==0 || i==(height-1))
                            cout << "=";
                        else
                            cout << "|";
                    }
                    else
                    {
                        if(i==food_x && j==food_y)
                            cout << "#";

                        else if(i==X && j==Y)
                            cout << "O";

                        else
                        {
                            int ext = 0;
                            for(k=0 ; k<tail_count ; k++)
                            {
                                if(i==tailX[k] && j==tailY[k])
                                {
                                    cout << "*";
                                    ext = 1;
                                }
                            }
                            if(ext==0)
                                cout << " ";

                        }
                    }
                }
                cout << "\n\t";
            }
        }

        void draw_score_box()
        {
            int i,j;
            gotoxy(8,26);
            for(i=0 ; i<small_bh ; i++)
            {
                for(j=0 ; j<small_bw ; j++)
                {
                    if(i==0 || i==(small_bh-1) || j==0 || j==(small_bw-1))
                        cout << "*";

                    else
                        cout << " ";
                }
                cout << "\n\t";
            }

            int x = 4 + small_bw + 10;
            int y = 4 + height + 2;
            gotoxy(x,y);
            for(i=0 ; i<score_bh ; i++)
            {
                for(j=0 ; j<score_bw ; j++)
                {
                    if(i==0 || i==(score_bh-1) || j==0 || j==(score_bw-1))
                        cout << "*";

                    else
                        cout << " ";
                }
                    y++;
                    gotoxy(x,y);
            }
            x = 4 + small_bw - 13;
            y = 4 + height + 2 + 2;
            gotoxy(x,y);
            cout << "  SNAKE";
            x += 2;
            y += 2;
            gotoxy(x,y);
            cout << "     GAME";
            x = 4 + small_bw + 13;
            y = 4 + height + 2 + 2;
            gotoxy(x,y);
            cout << "Score : ";
            gotoxy(x,y+2);
            cout << "Life  : ";
        }

        void input()
        {
            char ch;
            if(kbhit())
            {
                ch = getch();
                switch(ch)
                {
                    case 'w':
                        flag = 1;
                        break;
                    case 's':
                        flag = 2;
                        break;
                    case 'z':
                        flag = 3;
                        break;
                    case 'a':
                        flag = 4;
                        break;
                    case 'x':
                        flag = 5;
                        break;
                }
            }
        }

        void logic()
        {
            int i;
            int previousX = tailX[0];
            int previousY = tailY[0];
            int previous2X, previous2Y;

            tailX[0] = X;
            tailY[0] = Y;
            for(i=1 ; i<tail_count ; i++)
            {
                previous2X = tailX[i];
                previous2Y = tailY[i];
                tailX[i] = previousX;
                tailY[i] = previousY;
                previousX = previous2X;
                previousY = previous2Y;
            }

            if(X==food_x && Y==food_y)
            {
                label1:
                food_x = rand() % 20;
                if(food_x <= 0)
                {
                    goto label1;
                }
            label2:
                food_y = rand() % 50;
                if(food_y <= 0)
                {
                    goto label2;
                }
                score++;
                tail_count++;
            }

            if(X<=0 || X>=(height-1) || Y<=0 || Y>=(width-1))
            {
                life--;
                gameOver++;
            }
            for(i=1 ; i<tail_count ; i++)
            {
                if(X==tailX[i] && Y==tailY[i])
                {
                    gameOver = 3;
                }
            }
            switch(flag)
            {
                case 1:
                    X--;
                    break;
                case 2:
                    Y++;
                    break;
                case 3:
                    X++;
                    break;
                case 4:
                    Y--;
                    break;
                case 5:
                    gameOver = 3;
                    break;
            }
            if(score == 19 && abcd==0)
            {
                label3:
                food_x = rand() % 20;
                if(food_x <= 0)
                {
                    goto label3;
                }
                label4:
                food_y = rand() % 50;
                if(food_y <= 0)
                {
                    goto label4;
                }
                abcd = 1;
            }
            if(score == 27 && abcd==1)
            {
                label5:
                food_x = rand() % 20;
                if(food_x <= 0)
                {
                    goto label5;
                }
            label6:
                food_y = rand() % 50;
                if(food_y <= 0)
                {
                    goto label6;
                }
                abcd = 2;
            }
        }

        void print_score()
        {
            gotoxy(45,28);
            cout << score;
            gotoxy(45,30);
            cout << life;
        }

        void time_delay()
        {
            int t;
            int t1;
            for(t1=1 ; t1<=55 ; t1++)
            {
                for(t=1 ; t<=100000 ; t++);
            }
        }
};

int play_game1:: score = 0;

class play_game2 : public play_game1
{
    public:
        play_game2()
        {
            X = 12; Y = 12;
            food_x = 5; food_y = 40;
            tail_count = 0;
            flag = 0;
            gameOver = 0;
            life = 3;
            width=50; height=20;
            small_bh=7; small_bw=20;
            score_bh=7; score_bw=18;
            abcd = 0;
        }

        void setup()
        {
            X = 12;
            Y = 12;
            if(X==food_x && Y==food_y)
            {
                label1:
                food_x = rand() % 20;
                if(food_x <= 0)
                {
                    goto label1;
                }
                label2:
                food_y = rand() % 50;
                if(food_y <= 0)
                {
                    goto label2;
                }
            }
        }

        void draw()
        {
            int i, j, k, a;
            gotoxy(0,0);
            for(i=0 ; i<(height+2) ; i++)
            {
                for(j=0 ; j<(width+2) ; j++)
                    cout << " ";
            }
            gotoxy(0,0);
            cout << "\n\n\n\n\t";
            for(i=0 ; i<height ; i++)
            {
                for(j=0 ; j<width ; j++)
                {
                    if(i==0 || i==(height-1) || j==0 || j==(width-1))
                    {
                        if(i==0 || i==(height-1))
                            cout << "=";

                        else
                            cout << "|";
                    }
                    else
                    {
                        if(i==food_x && j==food_y)
                            cout << "#";

                        else if(i==X && j==Y)
                            cout << "O";

                        else
                        {
                            int ext = 0;
                            for(k=0 ; k<tail_count ; k++)
                            {
                                if(i==tailX[k] && j==tailY[k])
                                {
                                    cout << "*";
                                    ext = 1;
                                }
                            }
                            if(ext==0)
                            {
                                cout << " ";
                            }
                        }
                    }
                }
                cout << "\n\t";
            }
            gotoxy(18,9);
            for(a=0 ; a<27 ; a++)
                cout << "=";

            gotoxy(18,19);
            for(a=0 ; a<27 ; a++)
                cout << "=";
        }

        void logic()
        {
            int i, j, h;
            int previousX = tailX[0];
            int previousY = tailY[0];
            int previous2X, previous2Y;

            tailX[0] = X;
            tailY[0] = Y;
            for(i=1 ; i<tail_count ; i++)
            {
                previous2X = tailX[i];
                previous2Y = tailY[i];
                tailX[i] = previousX;
                tailY[i] = previousY;
                previousX = previous2X;
                previousY = previous2Y;
            }
            for(i=0 ; i<height ; i++)
            {
                for(j=0 ; j<width ; j++)
                {
                    if(i==5)
                    {
                        for(h=10 ; h<37 ; h++)
                        {
                            if(food_x==i && food_y==h)
                            {
                                label7:
                                food_x = rand() % 20;
                                if(food_x <= 0)
                                {
                                    goto label7;
                                }
                                label8:
                                food_y = rand() % 50;
                                if(food_y <= 0)
                                {
                                    goto label8;
                                }
                                break;
                            }
                        }
                    }
                    if(i==15)
                    {
                        for(h=10 ; h<37 ; h++)
                        {
                            if(food_x==i && food_y==h)
                            {
                                label9:
                                food_x = rand() % 20;
                                if(food_x <= 0)
                                {
                                    goto label9;
                                }
                                label10:
                                food_y = rand() % 50;
                                if(food_y <= 0)
                                {
                                    goto label10;
                                }
                                break;
                            }
                        }
                    }
                }
            }

            if(X==food_x && Y==food_y)
            {
                label1:
                food_x = rand() % 20;
                if(food_x <= 0)
                {
                    goto label1;
                }
                label2:
                food_y = rand() % 50;
                if(food_y <= 0)
                {
                    goto label2;
                }
                score++;
                tail_count++;
            }

            if(X<=0 || X>=(height-1) || Y<=0 || Y>=(width-1))
            {
                life--;
                gameOver++;
            }
            for(i=1 ; i<tail_count ; i++)
            {
                if(X==tailX[i] && Y==tailY[i])
                {
                    gameOver = 3;
                }
            }

            if(X==5 || X==15)
            {
                for(h=10 ; h<37 ; h++)
                {
                    if(Y==h)
                    {
                        life--;
                        gameOver++;
                        break;
                    }
                }
            }

            switch(flag)
            {
                case 1:
                    X--;
                    break;
                case 2:
                    Y++;
                    break;
                case 3:
                    X++;
                    break;
                case 4:
                    Y--;
                    break;
                case 5:
                    gameOver = 3;
                    break;
            }
            if(score == 49 && abcd==0)
            {
                label5b:
                food_x = rand() % 20;
                if(food_x <= 0)
                {
                    goto label5b;
                }
            label6b:
                food_y = rand() % 50;
                if(food_y <= 0)
                {
                    goto label6b;
                }
                abcd = 1;
            }
        }

        void time_delay()
        {
            int t;
            int t1;
            for(t1=1 ; t1<=50 ; t1++)
            {
                for(t=1 ; t<=100000 ; t++);
            }
        }
};

class play_game3 : public play_game2
{
    public:
        play_game3()
        {
            X = 11; Y = 15;
            food_x = 5; food_y = 40;
            tail_count = 0;
            flag = 0;
            gameOver = 0;
            life = 3;
            width=50; height=20;
            small_bh=7; small_bw=20;
            score_bh=7; score_bw=18;
            abcd = 0;
        }

        void setup()
        {
            X = 11;
            Y = 15;
            if(X==food_x && Y==food_y)
            {
                label1:
                food_x = rand() % 20;
                if(food_x <= 0)
                {
                    goto label1;
                }
                label2:
                food_y = rand() % 50;
                if(food_y <= 0)
                {
                    goto label2;
                }
            }
        }

        void draw()
        {
            int i, j, k, a;
            gotoxy(0,0);
            for(i=0 ; i<(height+2) ; i++)
            {
                for(j=0 ; j<(width+2) ; j++)
                    cout << " ";
            }
            gotoxy(0,0);
            cout << "\n\n\n\n\t";
            for(i=0 ; i<height ; i++)
            {
                for(j=0 ; j<width ; j++)
                {
                    if(i==0 || i==(height-1) || j==0 || j==(width-1))
                    {
                        if(i==0 || i==(height-1))
                            cout << "=";

                        else
                            cout << "|";
                    }
                    else
                    {
                        if(i==food_x && j==food_y)
                            cout << "#";

                        else if(i==X && j==Y)
                            cout << "O";

                        else
                        {
                            int ext = 0;
                            for(k=0 ; k<tail_count ; k++)
                            {
                                if(i==tailX[k] && j==tailY[k])
                                {
                                    cout << "*";
                                    ext = 1;
                                }
                            }
                            if(ext==0)
                            {
                                cout << " ";
                            }
                        }
                    }
                }
                cout << "\n\t";
            }
            int m, n;
            gotoxy(18,9);
            for(m=18 ; m<=46 ; m += 14)
            {
                for(n=9 ; n<=19 ; n++)
                {
                    gotoxy(m,n);
                    cout << "|";
                }
            }
        }

        void logic()
        {
            int i, j, h;
            int previousX = tailX[0];
            int previousY = tailY[0];
            int previous2X, previous2Y;
            tailX[0] = X;
            tailY[0] = Y;
            for(i=1 ; i<tail_count ; i++)
            {
                previous2X = tailX[i];
                previous2Y = tailY[i];
                tailX[i] = previousX;
                tailY[i] = previousY;
                previousX = previous2X;
                previousY = previous2Y;
            }
            for(i=0 ; i<height ; i++)
            {
                for(j=0 ; j<width ; j++)
                {
                    if(j==10 || j==24 || j==38)
                    {
                        for(h=5 ; h<16 ; h++)
                        {
                            if(food_x==h && food_y==j)
                            {
                                label7:
                                food_x = rand() % 20;
                                if(food_x <= 0)
                                {
                                    goto label7;
                                }
                                label8:
                                food_y = rand() % 50;
                                if(food_y <= 0)
                                {
                                    goto label8;
                                }
                            }
                        }
                    }
                }
            }

            if(X==food_x && Y==food_y)
            {
                label1:
                food_x = rand() % 20;
                if(food_x <= 0)
                {
                    goto label1;
                }
                label2:
                food_y = rand() % 50;
                if(food_y <= 0)
                {
                    goto label2;
                }
                score++;
                tail_count++;
            }

            if(X<=0 || X>=(height-1) || Y<=0 || Y>=(width-1))
            {
                life--;
                gameOver++;
            }
            for(i=1 ; i<tail_count ; i++)
            {
                if(X==tailX[i] && Y==tailY[i])
                    gameOver = 3;
            }

            if(Y==10 || Y==24 || Y==38)
            {
                for(h=5 ; h<16 ; h++)
                {
                    if(X==h)
                    {
                        life--;
                        gameOver++;
                        break;
                    }
                }
            }

            switch(flag)
            {
                case 1:
                    X--;
                    break;
                case 2:
                    Y++;
                    break;
                case 3:
                    X++;
                    break;
                case 4:
                    Y--;
                    break;
                case 5:
                    gameOver = 3;
                    break;
            }

            if(score == 81 && abcd==0)
            {
                label5c:
                food_x = rand() % 20;
                if(food_x <= 0)
                {
                    goto label5c;
                }
            label6c:
                food_y = rand() % 50;
                if(food_y <= 0)
                {
                    goto label6c;
                }
                abcd = 1;
            }
        }

        void time_delay()
        {
            int t;
            int t1;
            for(t1=1 ; t1<=45 ; t1++)
            {
                for(t=1 ; t<=100000 ; t++);
            }
        }
};

void draw_title(void);
void loading(void);
void print_menu(void);
void game_instructions(void);
void play_game(void);
void view_high_score(void);

int main()
{
    ifstream f;

    f.open("high score.txt", ios::in);
    f >> read_hs;
    f.close();
    draw_title();
    print_menu();

    return 0;
}

void draw_title()
{
    cout << endl << endl << endl << endl;
    cout << "\t *******    **      **      ***      **   **   *******" << endl;
    cout << "\t **         ****    **     ** **     **  **    **         " << endl;
    cout << "\t *******    **********    **   **    *****     ***** " << endl;
    cout << "\t      **    **   *****   *********   **  **    **         " << endl;
    cout << "\t      **    **    ****   **     **   **   **   **         " << endl;
    cout << "\t *******    **      **   **     **   **    **  *******" << endl;
    cout << endl << endl;
    cout << "\t         ******     **     **      **  ******" << endl;
    cout << "\t         **        ****    ***    ***  **         " << endl;
    cout << "\t         **       **  **   ****  ****  ****     " << endl;
    cout << "\t         ** ***  ********  **  **  **  **         " << endl;
    cout << "\t         **   *  **    **  **      **  **         " << endl;
    cout << "\t         ******  **    **  **      **  ******" << endl;
    loading();
    cout << endl << endl << "\tPress any key to continue ...";
    getch();
}

void loading()
{
    cout << endl << endl << endl << endl << endl;
    cout << "\t\t";
    for (int m=1 ; m<=20 ; m++)
    {
        cout << ". ";
        for(int d1=1 ; d1<=9000 ; d1++)
        {
            for(int d2=1 ; d2 <= 9000 ; d2++);
        }
    }
}

void print_menu()
{
    int choice;
    do
    {
    system("cls");
    cout << endl << endl << endl;
    cout << "\t1)  Game Instructions" << endl << endl;
    cout << "\t2)  Play Game" << endl << endl;
    cout << "\t3)  View High Scores" << endl << endl;
    cout << "\t4)  Exit" << endl << endl << endl << endl;
    cout << "\tEnter your choice : ";
    cin >> choice;
    switch(choice)
    {
    case 1:
        game_instructions();
        break;

    case 2:
        play_game();
        break;

    case 3:
        view_high_score();
        break;

    case 4:
        exit(0);
        break;

    default:
        break;
    }
    }while(choice != 4);
}

void game_instructions()
{
    int i;
    system("cls");
    cout << "\n\n\t\t\tGAME INSTRUCTIONS\t\n";
    for(i=1 ; i<=40 ; i++)
    {
        cout << "_ ";
    }
    cout << endl << endl << endl << endl;
    cout << " 1. Press the below given character keys to move the snake" << endl << endl << endl;
    cout << "\t-> Press 'w' to move upwards\n\t-> Press 'z' to move downwards\n\t-> Press 'a' to move left\n\t-> Press 's' to move right" << endl << endl << endl;
    cout << " 2. Collect/Eat the food that is shown on the screen to increase your score" << endl << endl << endl;
    cout << " 3. One food is equivalent to 1 point" << endl << endl << endl;
    cout << " 4. Do not hit the border or the snake's body itself" << endl << endl << endl;
    cout << " 5. There are total 3 levels in the game, the difficulty increases in the           consecutive levels\n\n    If the score reaches multiples of 40, that would take the game to the next      level" << endl << endl << endl;
    cout << " 6. Press 'x' to exit the game" << endl << endl << endl << endl << endl;
    cout << "\tGOOD LUCK !!!" << endl << endl << endl <<endl;
    cout << "\tPress any key to return ...";
    getch();
}

void play_game()
{
    play_game1::score = 0;
    play_game1 p1;
    p1.gameOver = 0;
    temp = 0;
    p1.setup();
    p1.draw_score_box();
    while( p1.gameOver != 3 )
    {
        if(p1.gameOver==1 && temp==0)
        {
            p1.setup();
            temp = 1;
        }
        if(p1.gameOver==2 && temp==1)
        {
            p1.setup();
            temp = 2;
        }
        if(p1.gameOver==3 && temp==2)
        {
            p1.setup();
            temp = 3;
        }

        p1.logic();
        p1.print_score();
        p1.draw();
        p1.input();

        if(p1.score==40)
        {
            temp = 0;
            play_game2 p2;
            p2.gameOver = 0;
            temp = 0;
            p2.setup();
            p2.draw_score_box();
            while( p2.gameOver != 3 )
            {
                if(p2.gameOver==1 && temp==0)
                {
                    p2.setup();
                    temp = 1;
                }
                if(p2.gameOver==2 && temp==1)
                {
                    p2.setup();
                    temp = 2;
                }
                if(p2.gameOver==3 && temp==2)
                {
                    p2.setup();
                    temp = 3;
                }
                p2.logic();
                p2.print_score();
                p2.draw();
                p2.input();

                if(p2.score==80)
                {
                    temp = 0;
                    play_game3 p3;
                    p3.gameOver = 0;
                    temp = 0;
                    p3.setup();
                    p3.draw_score_box();
                    while( p3.gameOver != 3 )
                    {
                        if(p3.gameOver==1 && temp==0)
                        {
                            p3.setup();
                            temp = 1;
                        }
                        if(p3.gameOver==2 && temp==1)
                        {
                            p3.setup();
                            temp = 2;
                        }
                        if(p3.gameOver==3 && temp==2)
                        {
                            p3.setup();
                            temp = 3;
                        }
                        p3.logic();
                        p3.print_score();
                        p3.draw();
                        p3.input();
                    }
                    gotoxy(1,33);
                    break;
                }
            }
            gotoxy(1,33);
            break;
        }
    }

    gotoxy(1,33);

    ofstream fout;
    int h = play_game1:: score;
    if(h > read_hs)
    {
        fout.open("high score.txt", ios::out);
        fout << h;
        fout.close();
    }
    cout << "\tPress any key to return...";
    getch();
}

void view_high_score()
{
    ifstream fin;
    int vhs;
    fin.open("high score.txt", ios::in);
    fin >> vhs;
    fin.close();

    system("cls");
    cout << endl << endl << endl << "\t\tHIGH SCORE  ===>   " << vhs << endl;
    cout << endl << "\t\tPress any key to return...";
    getch();
}
