#include "lib.h"

using namespace std;

bool is_valid_char(char c)
{
    if (c == '*' || c == '+' || c == 'M' || c == '0' || c == ' ')
        return true;
    return false;
}

vector<char> get_operative_commands(ifstream& fin)
{
    vector<char> cmd;
    int buf;
    bool power = false;

    while ((buf = fin.get()) != EOF)
    {
        if ((char)buf == 'I')
        {
            power = true;
            buf = fin.get();
        }
        if ((char)buf == '-')
        {
            power = false;
            buf = fin.get();
        }
        if (power)
            cmd.push_back((char)buf);
    }
    return cmd;
}

vector<char> get_commands(ifstream& fin)
{
    vector<char> cmd;
    int buf;

    while ((buf = fin.get()) != EOF)
            cmd.push_back((char)buf);
    return cmd;
}

vector<int> locate_robot(vector< vector<char> > minefield)
{
    vector<int> pos;
    int i = 0;
    int j = 0;

    while (is_valid_char(minefield[i][0]))
	{
		while (is_valid_char(minefield[i][j]))
		{
		    if (minefield[i][j] == 'M')
            {
                pos.push_back(i);
                pos.push_back(j);
                return pos;
            }
			j++;
		}
		i++;
		j = 0;
	}
	pos.push_back(-1);
	pos.push_back(-1);
	return pos;
}

vector< vector<char> > get_minefield(ifstream& fin)
{
	vector< vector<char> > minefield;
	int i = 0;
	int b;
	int j = 0;

	minefield.resize(100);
	while (i < 100)
	{
		minefield[i].resize(100);
		i++;
	}
	i = 0;
	while ((b = fin.get()) != EOF)
	{
		if (is_valid_char((char)b))
		{
			minefield[i][j] = (char)b;
			j++;
		}
		else
		{
			j = 0;
			i++;
		}
	}
	return minefield;
}

vector<int> get_end(vector< vector<char> > minefield)
{
    vector<int> end_pos;
    int n = 0, m = 0;
    int i, j;

    while (is_valid_char(minefield[n][0]))
    {
        while (is_valid_char(minefield[n][m]))
            m++;
        n++;
    }

    for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
        {
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
            {
                if (minefield[i][j] == '0')
                {
                    end_pos.push_back(i);
                    end_pos.push_back(j);
                    return end_pos;
                }
            }
        }
	}


	end_pos.push_back(-1);
	end_pos.push_back(-1);
	return end_pos;
}

void display_minefield(vector< vector<char> > minefield, ofstream& fout)
{
    int n = 0, m = 0;

	while (is_valid_char(minefield[n][0]))
    {
        while (is_valid_char(minefield[n][m]))
            m++;
        n++;
    }

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
        {
			fout << minefield[i][j];
			cout << minefield[i][j];
        }
		fout << endl;
		cout << endl;
	}
}

void solve(ofstream& fout, ifstream& fcmd, ifstream& fin)
{
    vector< vector<char> > minefield = get_minefield(fin);

    vector<char> cmd = get_commands(fcmd);
    vector<int> pos = locate_robot(minefield);
    vector<int> end_pos = get_end(minefield);

    int x = pos[0];
    int y = pos[1];
    int end_x = end_pos[0];
    int end_y = end_pos[1];
    bool power = false;
    int n = 0, m = 0;

	while (is_valid_char(minefield[n][0]))
    {
        while (is_valid_char(minefield[n][m]))
            m++;
        n++;
    }

    minefield[x][y] = ' ';

    for (unsigned int i = 0; i < cmd.size(); i++)
    {
        if (cmd[i] == 'I')
            power = true;
        if (cmd[i] == '-')
            power = false;
        if (power)
        {
            if (cmd[i] == 'N')
            {
                if (x - 1 >= 0)
                {
                    if (minefield[x - 1][y] != '+')
                    {
                        if (minefield[x - 1][y] == '*')
                        {
                            minefield[x - 1][y] = ' ';
                            fout << "no" << endl << endl;
                            display_minefield(minefield, fout);
                            return;
                        }
                        else
                        {
                            minefield[x - 1][y] = ' ';
                            x--;
                            if (i == cmd.size())
                            {
                                fout << "no" << endl << endl;
                                display_minefield(minefield, fout);
                                return;
                            }
                            if (x == end_x && y == end_y && cmd[i + 1] == '-')
                            {
                                fout << "yes" << endl << endl;
                                display_minefield(minefield, fout);
                                return;
                            }
                            if (x == end_x && y == end_y && cmd[i + 1] != '-')
                            {
                                fout << "no" << endl << endl;
                                display_minefield(minefield, fout);
                                return;
                            }
                        }
                    }
                }
            }

            if (cmd[i] == 'S')
            {
                if (x + 1 <= n - 1)
                {
                    if (minefield[x + 1][y] != '+')
                    {
                        if (minefield[x + 1][y] == '*')
                        {
                            fout << "no" << endl << endl;
                            minefield[x + 1][y] = ' ';
                            display_minefield(minefield, fout);
                            return;
                        }
                        else
                        {
                            minefield[x + 1][y] = ' ';
                            x++;
                            if (i == cmd.size())
                            {
                                fout << "no" << endl << endl;
                                display_minefield(minefield, fout);
                                return;
                            }
                            if (x == end_x && y == end_y && cmd[i + 1] == '-')
                            {
                                fout << "yes" << endl << endl;
                                display_minefield(minefield, fout);
                                return;
                            }
                            if (x == end_x && y == end_y && cmd[i + 1] != '-')
                            {
                                fout << "no" << endl << endl;
                                display_minefield(minefield, fout);
                                return;
                            }
                        }
                    }
                }
            }

            if (cmd[i] == 'E')
            {
                if (y - 1 >= 0)
                {
                    if (minefield[x][y - 1] != '+')
                    {
                        if (minefield[x][y - 1] == '*')
                        {
                            fout << "no" << endl << endl;
                            minefield[x][y - 1] = ' ';
                            display_minefield(minefield, fout);
                            return;
                        }
                        else
                        {
                            minefield[x][y - 1] = ' ';
                            y--;
                            if (i == cmd.size())
                            {
                                fout << "no" << endl << endl;
                                display_minefield(minefield, fout);
                                return;
                            }
                            if (x == end_x && y == end_y && cmd[i + 1] == '-')
                            {
                                fout << "yes" << endl << endl;
                                display_minefield(minefield, fout);
                                return;
                            }
                            if (x == end_x && y == end_y && cmd[i + 1] != '-')
                            {
                                fout << "no" << endl << endl;
                                display_minefield(minefield, fout);
                                return;
                            }
                        }
                    }
                }
            }

            if (cmd[i] == 'O')
            {
                if (y + 1 <= m)
                {
                    if (minefield[x][y + 1] != '+')
                    {
                        if (minefield[x][y + 1] == '*')
                        {
                            fout << "no" << endl << endl;
                            minefield[x][y + 1] = ' ';
                            display_minefield(minefield, fout);
                            return;
                        }
                        else
                        {
                            minefield[x][y + 1] = ' ';
                            y++;
                            if (i == cmd.size())
                            {
                                fout << "no" << endl << endl;
                                display_minefield(minefield, fout);
                                return;
                            }
                            if (x == end_x && y == end_y && cmd[i + 1] == '-')
                            {
                                fout << "yes" << endl << endl;
                                display_minefield(minefield, fout);
                                return;
                            }
                            if (x == end_x && y == end_y && cmd[i + 1] != '-')
                            {
                                fout << "no" << endl << endl;
                                display_minefield(minefield, fout);
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    fout << "no" << endl << endl;
    display_minefield(minefield, fout);
}
