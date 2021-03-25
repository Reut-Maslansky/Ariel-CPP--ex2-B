#include "Board.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace ariel
{
    Board::Board()
    {
        rows = 0;
        cols = 0;
        b.push_back(vector<char>(1, '_'));
    }

    void Board::post(unsigned int row, unsigned int column, Direction direction, string message)
    {
        if (message.length() == 0)
        {
            return;
        }

        if (direction == Direction::Vertical)
        {
            if (row + message.length() > rows)
            {
                for (int i = 0; i < (row + message.length() - rows - 1); i++)
                {
                    b.push_back(vector<char>(b.at(0).size(), '_'));
                }
                rows = b.size() - 1;
            }
            if (column > cols)
            {
                for (unsigned int i = 0; i <b.size(); i++)
                {
                    for (int j = 0; j < (column - cols); j++)
                    {
                        b.at(i).push_back('_');
                    }
                }
                cols = b.at(0).size() - 1;
            }
        }
        else
        {
            if (row > rows)
            {
                for (int i = 0; i < (row - rows); i++)
                {
                    b.push_back(vector<char>(b.at(0).size(), '_'));
                }
                rows = b.size() - 1;
            }

            if (column + message.length() > cols)
            {
                for (unsigned int i = 0; i < b.size(); i++)
                {
                    for (int j = 0; j < (column + message.length() - cols - 1); j++)
                    {
                        b.at(i).push_back('_');
                    }
                }
                cols = b.at(0).size() - 1;
            }
        }
        
        for (unsigned int i = 0; i < message.length(); i++)
        {
            if (direction == Direction::Vertical)
            {
                b.at(row + i).at(column) = message.at(i);
            }
            else
            {
                b.at(row).at(column + i) = message.at(i);
            }
        }
    }

    string Board::read(unsigned int row, unsigned int column, Direction direction, unsigned int length)
    {
        if (length == 0)
        {
            return "";
        }

        if ((row > rows && direction == Direction::Vertical) || (column > cols && direction == Direction::Horizontal))
        {
            string ans;
            for (int i = 0; i < length; i++)
            {
                ans += "_";
            }
            return ans;
        }

        unsigned int space_len = 0;
        unsigned int char_len = length;

        if (row + length > rows && direction == Direction::Vertical)
        {
            space_len = row + length - rows - 1;
            char_len = length - space_len;
        }
        else if (column + length > cols && direction == Direction::Horizontal)
        {
            space_len = column + length - cols - 1;
            char_len = length - space_len;
        }
        string msg;
        for (unsigned int i = 0; i < char_len; i++)
        {
            if (direction == Direction::Horizontal)
            {
                msg += b.at(row).at(column + i);
            }
            else
            {
                msg += b.at(row + i).at(column);
            }
        }

        for (int i = 0; i < space_len; i++)
        {
            msg += "_";
        }

        return msg;
    }

    void Board::show()
    {
        for (unsigned long i = 0; i < b.size(); i++)
        {
            cout << i << ":\t";
            for (unsigned long j = 0; j < b.at(i).size(); j++)
            {
                cout << b.at(i).at(j);
            }
            cout << endl;
        }
    }
}