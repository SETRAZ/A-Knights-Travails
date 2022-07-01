#include <bits/stdc++.h>
#define ll long long
#define intro cout << "A Knight Travails - DSA Project \n\n"
using namespace std;

// Global variables
map<pair<ll, ll>, ll> chess_position;
map<ll, pair<ll, ll>> chess_postion_reverse;
vector<int> path;

void add_edge(vector<int> adj[], int src, int dest)   //function to add an edge to the graph
{
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}

bool BFS(vector<int> adj[], int src, int dest, int v, int pred[], int dist[])  //using BFS algorithm for implementation
{

    list<int> queue;

    bool visited[v];

    for (int i = 0; i < v; i++)
    {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    visited[src] = true;                              //marking source as visited
    dist[src] = 0;
    queue.push_back(src);

    while (!queue.empty())
    {
        int u = queue.front();
        queue.pop_front();

        for (int i = 0; i < adj[u].size(); i++)
        {
            if (visited[adj[u][i]] == false)
            {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);

                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
    return false;
}

void printShortestDistance(vector<int> adj[], int s, int dest, int v)
{

    int pred[v], dist[v];

    if (BFS(adj, s, dest, v, pred, dist) == false)
    {
        cout << "Given source and destination"
             << " are not connected";
        return;
    }

    int crawl = dest;
    path.push_back(crawl);

    while (pred[crawl] != -1)                       //storing the path taken
    {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }

    cout << "Shortest path length is : "
         << dist[dest];

    cout << "\nPath is::\nstart->";
    for (int i = path.size() - 1; i >= 0; i--)
        cout << "(" << chess_postion_reverse[path[i]].first << "," << chess_postion_reverse[path[i]].second << ") ->";
    cout << "end";
}

bool check_valid_input(ll &x, ll &y, ll &X, ll &Y, vector<pair<ll, ll>> &vecx) //input validation for pawns
{
    if (x <= X && y <= Y && x >= 1 && y >= 1)
    {
        bool flag = true;

        for (ll i = 0; i < vecx.size(); i++)
        {
            if (vecx[i].first != x || vecx[i].second != y)                     //check if new pawn position is clashing with previous pawn position.
            {
                continue;
            }
            else
            {
                flag = false;
            }
        }

        if (flag)
        {
            vecx.push_back(make_pair(x, y));                                   //if no clash is detected, continue and push back new position.
            return true;
        }
        else
        {

            cout << "Duplicated pawn positions provided\nPlease enter again....\n\n";
            return flag;
        }
    }
    else
    {
        cout << "Out of bounds.\nAborting....";
        exit(-1);
    }
}
void check_inputs_start_and_end(ll x, ll y, ll N)                             //input validation for knight
{
    if (x > N || y > N || x < 1 || y < 1)
    {
        cout << "Out of bounds.\nPlease begin again....";
        exit(-1);
    }
    else
    {
    }
}
void check_start_end(ll x, ll y, ll stx, ll sty, ll enx, ll eny)              //for checking blockage at initial and final positions
{
    if (x == stx && y == sty)
    {
        cout << "Initial position blocked by pawn\nPlease begin again....";
        exit(-1);
    }
    else if (x == enx && y == eny)
    {
        cout << "Ending position blocked by pawn\nPlease begin again....";
        exit(-1);
    }
}

int main()
{

    ll chess_board_size;
    ll knight_start_x, knight_start_y;
    ll knight_end_x, knight_end_y;
    ll friendly_pawn_number;

    vector<pair<ll, ll>> friendly_pawn;             //vector for storing the positions of the pawns

    ll temp1, temp2, temp3, temp4;                  //temporary variables
    bool temp5;

    int row[] = {2, 2, -2, -2, 1, 1, -1, -1};       //this row and column indicates the next position that a knight can move to. If a knight is at (i, j),
    int col[] = {-1, 1, 1, -1, 2, -2, 2, -2};       //its next position can be (i + row[i], j + col[j]).

    intro;
    cout << "The algorithm uses BFS algorithm to find the shortest path after removing all edges blocked by friendly pawns.\n";

    cout << "\nEnter the size of the chessboard \n";
    cin >> chess_board_size;

    cout << "Enter the starting position of the knight \n";
    cin >> knight_start_x >> knight_start_y;
    check_inputs_start_and_end(knight_start_x, knight_start_y, chess_board_size);

    cout << "Enter the ending position of the knight \n";
    cin >> knight_end_x >> knight_end_y;
    check_inputs_start_and_end(knight_end_x, knight_end_y, chess_board_size);

    cout << "Enter the number of pawns blocking the knight \n";
    cin >> friendly_pawn_number;

    temp1 = friendly_pawn_number;
    while (temp1--)                                //input pawn positions
    {
        temp4 = friendly_pawn_number - temp1;

        cout << "Enter the x and y co-ordinates of ";
        cout << temp4;
        cout << " pawn\n";
        cin >> temp2 >> temp3;
        check_start_end(temp2, temp3, knight_start_x, knight_start_y, knight_end_x, knight_end_y);
        temp5 = check_valid_input(temp2, temp3, chess_board_size, chess_board_size, friendly_pawn);

        if (!temp5)
        {

            temp1++;
        }
    }

    temp4 = 0;
    for (ll i = 1; i <= chess_board_size; i++)
    {
        for (ll j = 1; j <= chess_board_size; j++)
        {
            chess_position[make_pair(i, j)] = temp4;                //assigning each node of graph a marker
            chess_postion_reverse[temp4] = make_pair(i, j);
            temp4++;
        }
    }

    vector<int> adj[chess_board_size * chess_board_size];
    for (ll i = 1; i <= chess_board_size; i++)
    {
        for (ll j = 1; j <= chess_board_size; j++)                  //traversing the graph.
        {
            for (ll k = 0; k < 8; k++)                              //validating all the next possible positions of the knight.
            {
                if (i + row[k] <= chess_board_size && i + row[k] > 0 && j + col[k] <= chess_board_size && j + col[k] > 0)
                {
                    bool flag = true;
                    for (ll m = 0; m < friendly_pawn.size(); m++)   //checking the presence of a friendly pawn
                    {
                        if ((friendly_pawn[m].first == i && friendly_pawn[m].second == j) || (friendly_pawn[m].first == i + row[k] && friendly_pawn[m].second == j + col[k]))
                            flag = false;
                    }

                    if (flag)
                        add_edge(adj, chess_position[make_pair(i, j)], chess_position[make_pair(i + row[k], j + col[k])]);
                }
            }
        }
    }

    ll source = chess_position[make_pair(knight_start_x, knight_start_y)], dest = chess_position[make_pair(knight_end_x, knight_end_y)];
    if(source == dest){
        cout<<"\nSource is already on destination.";
        exit(0);
    }
    printShortestDistance(adj, source, dest, chess_board_size * chess_board_size);
    sleep(5);
    system("cls");
    intro;

    for (int k = path.size() - 1; k >= 0; k--)
    {
        sleep(2);
        system("cls");
        intro;

        cout << "\n";

        ll x = chess_postion_reverse[path[k]].first;
        ll y = chess_postion_reverse[path[k]].second;
        bool flag;
        bool flag2;
        ll t;

        cout << " ";

        for (ll i = 1; i <= chess_board_size; i++)
        {
            cout << "   " << i;
        }
        cout << "\n\n";

        for (ll i = 1; i <= chess_board_size; i++)
        {
            flag2 = false;
            if (i <= 9)
                cout << i << "   ";
            else
                cout << i << "  ";

            for (ll j = 1; j <= chess_board_size; j++)
            {
                flag = true;

                for (ll k = 0; k < friendly_pawn.size(); k++)
                {

                    if (i == friendly_pawn[k].first && j == friendly_pawn[k].second)
                    {
                        cout << "p   ";

                        flag = false;
                    }
                }

                if (flag)
                {
                    if (i == x && j == y)
                    {
                        cout << "k   ";
                        flag2 = true;
                        t = j;
                    }
                    else
                        cout << "-   ";
                }
            }

            if (flag2)
                cout << " " << i << " " << t << " \n\n";
            else
                cout << "\n\n";
        }
    }
}
