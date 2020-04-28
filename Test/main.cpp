/****************************************************************************
 *  Copyright (C) 2020 Lu Meng and Chen Xueqing.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <future>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdint>
#include <csignal>
#include <unistd.h>

#include "switch.h"
#include "main.h"
#include "welcome.h"

#ifdef LINUX
#include "keyboard.h"
#else
#include <windows.h>
#include <conio.h>
#endif

using namespace std;

Word *word = new Word{0, "", ""};
Player_line *player_line = new Player_line{"", 25};
Fall *fall = new Fall(51, 10);
Timer *timer = new Timer();
Status *status = new Status();

int main()
{
    int start;
    cout << "Press any key and enter to start..." << endl;
    cin >> start;
    thread t_welcome(welcome);
    t_welcome.join();
    init();
#ifdef LINUX
    setBufferedInput(false);
#endif
    thread t_game(game);
    t_game.detach();
    thread t_player(player);
    t_player.detach();
    thread t_timer(tick);
    t_timer.join();
    if (status->won)
    {
#ifdef LINUX
        setBufferedInput(true);
#endif
        cout << "Congratulations! You won!" << endl;
        cout << "The word is \"" << word->target << "\"" << endl;
    }
#ifndef LINUX
    std::system("pause");
#endif
    destroy();
    return 0;
}

void game()
{
    bool caught = false;
    while (!(status->won))
    {
        caught = update();
        if (caught)
        {
            player_line->fill_bucket(1);
        }
        else
        {
            player_line->fill_bucket(0);
        }
        fall->push(rand_str(fall->col));
        print();
        judge();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    return;
}

void player()
{
#ifdef LINUX
    int ch1, ch2, ch3;
    while (!(status->won))
    {
        ch1 = -1;
        ch2 = -1;
        ch3 = -1;
        ch1 = getchar();
        if (ch1 != 27)
        {
            goto sleep;
        }
        ch2 = getchar();
        if (ch2 != 91)
        {
            goto sleep;
        }
        ch3 = getchar();
        if (ch3 == 68 && player_line->index > 1) //left
        {
            player_line->update(-1);
        }
        else if (ch3 == 67 && player_line->index < fall->col - 2) //right
        {
            player_line->update(1);
        }
        print();
    sleep:
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    return;
#else
    int ch1, ch2;
    while (!(status->won))
    {
        ch1 = -1;
        ch2 = -1;
        if (_kbhit())
        {
            ch1 = _getch();
            if (ch1 != 224)
            {
                goto sleep;
            }
            ch2 = _getch();
            if (ch2 == 75 && player_line->index > 1) //left
            {
                player_line->update(-1);
            }
            else if (ch2 == 77 && player_line->index < fall->col - 2) //right
            {
                player_line->update(1);
            }
            print();
        }
    sleep:
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    return;
#endif
}

void tick()
{
    static int period = 1000;
    while (!(status->won))
    {
        timer->countdown--;
        this_thread::sleep_for(chrono::milliseconds(period));
    }
}

void init()
{
    srand(time(NULL));
    word->init(word_list[rand() % LIST_LENGTH]);
    player_line->init(fall->col);
}

string rand_str(int l)
{
    string s;
    for (int i = 0; i < l; i++)
    {
        char c = ' ';
        int p = rand() % 1000;
        if (p < DENSITY)
        {
            c = char(rand() % 26 + 97);
            while ((word->display).find(c) != string::npos)
            {
                c = char(rand() % 26 + 97);
            }
        }
        s += c;
    }
    return s;
}

void print_fall()
{
    for (vector<string>::iterator it = (fall->display).end() - 1; it != (fall->display).begin() - 1; it--)
    {
        if (it == (fall->display).end() - 1)
        {
            cout << *it << " ";
            timer->print();
            cout << endl;
        }
        else
        {
            cout << *it << endl;
        }
    }
}

void print()
{
#ifdef LINUX
    std::system("clear");
#else
    std::system("cls");
#endif
    print_fall();
    player_line->print();
    cout << "\n\n";
    word->print();
    cout << "\n";
}

char update_word(char c)
{
    int pos = (word->target).find(c);
    if (pos != string::npos)
    {
        word->reveal(c);
        return c;
    }
    return '\0';
}

bool update()
{
    char left = update_word((fall->display)[0][player_line->index - 1]);
    char mid = update_word((fall->display)[0][player_line->index]);
    char right = update_word((fall->display)[0][player_line->index + 1]);
    if (left != '\0' || mid != '\0' || right != '\0')
    {
        return true;
    }
    return false;
}

void judge()
{
    status->won = (word->display == word->target);
}

void destroy()
{
    delete word;
    word = NULL;
    delete player_line;
    player_line = NULL;
    delete fall;
    fall = NULL;
    delete timer;
    timer = NULL;
    delete status;
    status = NULL;
}
