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

#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef MAIN_H_GLOBAL
#define MAIN_H_EXTERN
#else
#define MAIN_H_EXTERN extern
#endif

#define DENSITY 20 //in 1000

const int LIST_LENGTH = 10;
const std::string word_list[LIST_LENGTH] = {"engineering", "hangman", "brainstorm", "random", "envelope", "interface", "iceberg", "humour", "lemon", "commander"};

class Fall
{
public:
    std::vector<std::string> display;
    int col; //only odd number
    int row;
    Fall(int col, int row)
    {
        this->col = col;
        this->row = row;
        for (int i = 0; i < this->row; i++)
        {
            (this->display).push_back("");
        }
    }
    void push(std::string str)
    {
        (this->display).erase((this->display).begin());
        (this->display).push_back(str);
    }
};

class Word
{
public:
    int length;
    std::string target;
    std::string display;
    void init(std::string target)
    {
        this->target = target;
        this->length = this->target.length();
        this->display = std::string(this->length, '-');
    }
    void reveal(char c)
    {
        int last_pos = (this->target).find(c);
        while (last_pos != std::string::npos)
        {
            (this->display).replace(last_pos, 1, std::string(1, c));
            if (last_pos >= this->length)
            {
                break;
            }
            int pos = (this->target).find(c, last_pos + 1);
            last_pos = pos;
        }
    }
    void print()
    {
        std::cout << this->display;
    }
};

class Player_line
{
public:
    std::string display;
    int index;
    void init(int length)
    {
        this->display = std::string((length - 3) / 2, ' ') + "\\_/" + std::string((length - 3) / 2, ' ');
    }
    void fill_bucket(int m)
    {
        if (m == 1)
        {
            if ((this->display).find("_") != std::string::npos)
            {
                (this->display).replace((this->display).find("_"), 1, "+");
            }
        }
        else
        {
            if ((this->display).find("+") != std::string::npos)
            {
                (this->display).replace((this->display).find("+"), 1, "_");
            }
        }
    }
    void update(int dir)
    {
        if (dir == -1)
        {
            this->display = (this->display).substr(1) + ' ';
            this->index--;
        }
        if (dir == 1)
        {
            (this->display) = ' ' + (this->display).substr(0, (this->display).size() - 1);
            this->index++;
        }
    }
    void print()
    {
        std::cout << this->display;
    }
};

class Timer
{
public:
    int countdown;
    Timer()
    {
        this->countdown = 100;
    };
    void print()
    {
        std::cout << "COUNTDOWN: " << this->countdown;
    };
};

class Status
{
public:
    bool won;
    Status()
    {
        this->won = false;
    }
};

void game();
void player();
void tick();
void init();
std::string rand_str(int l);
void print_upper();
void print();
char update_word(char c);
bool update();
void destroy();

#endif // __MAIN_H__