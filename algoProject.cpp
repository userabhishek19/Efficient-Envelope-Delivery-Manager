#include <iostream>
#include <vector>
using namespace std;

#define V 5
#define INF 99999
#define NUM_ENVELOPES 4

struct envelope {
    int env_loc;
    int del_loc;
};

int dist[V][V];
int del_dist[NUM_ENVELOPES];
int env_dist[NUM_ENVELOPES];
int flag = 1;

void func(int driv_loc, envelope env[], int del_dist[], int env_dist[], int tot_env) {
    if (flag == 1) {
        for (int i = 0; i < tot_env; i++) {
            env_dist[i] = dist[driv_loc][env[i].env_loc];
        }
    }
    flag = 0;

    int temp = INF, temp2 = -1, temp3 = -1;
    for (int i = 0; i < tot_env; i++) {
        if (temp >= env_dist[i]) {
            temp = env_dist[i];
            temp2 = i;
        }
    }

    for (int i = 0; i < tot_env; i++) {
        if (temp >= del_dist[i]) {
            temp = del_dist[i];
            temp3 = i;
        }
    }

    if (temp == INF) {
        return;
    }

    if (temp3 != -1) {
        cout << temp3 + 1 << " envelope will be delivered" << endl;
        del_dist[temp3] = INF;
        driv_loc = temp3;
        for (int i = 0; i < tot_env; i++) {
            if (env_dist[i] != INF) {
                env_dist[i] = dist[driv_loc][env[i].env_loc];
            }
        }
    } else {
        cout << temp2 + 1 << " envelope will be collected" << endl;
        driv_loc = temp2;
        env_dist[temp2] = INF;
        for (int i = 0; i < tot_env; i++) {
            if (env_dist[i] != INF) {
                env_dist[i] = dist[driv_loc][env[i].env_loc];
            }
        }
        del_dist[temp2] = dist[driv_loc][env[temp2].del_loc];
    }
    func(driv_loc, env, del_dist, env_dist, tot_env);
}

void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt) {
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

void floydWarshall(int graph[][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    cout << "The following matrix shows the shortest distances between every pair of vertices \n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                cout << "INF" << " ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    int a = 5;
    int input[a][a];
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            if (i == j) {
                input[i][j] = 0;
            } else {
                input[i][j] = INF;
            }
        }
    }

    vector<pair<int, int>> adj[a];
    addEdge(adj, 0, 1, 15);
    addEdge(adj, 0, 4, 25);
    addEdge(adj, 1, 2, 35);
    addEdge(adj, 1, 3, 45);
    addEdge(adj, 1, 4, 55);
    addEdge(adj, 2, 3, 65);
    addEdge(adj, 3, 4, 75);

    int v, w;
    for (int u = 0; u < a; u++) {
        cout << "Node " << u << " makes an edge with \n";
        for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
            v = it->first;
            w = it->second;
            for (int i = 0; i < a; i++) {
                input[u][v] = w;
            }
            cout << "\tNode " << v << " with edge weight =" << w << "\n";
        }
    }

    cout << "Matrix is" << endl;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            if (input[i][j] == INF) {
                cout << "INF" << " ";
            } else {
                cout << input[i][j] << " ";
            }
            if (j == 4) {
                cout << endl;
            }
        }
    }

    int graph[V][V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = input[i][j];
        }
    }

    floydWarshall(graph);

    int dri_loc, tot_env;
    cout << "Enter the vertex where the driver is located. Choose from 0, 1, 2, 3, 4" << endl;
    cin >> dri_loc;
    cout << "Enter the number of envelopes" << endl;
    cin >> tot_env;

    envelope env[NUM_ENVELOPES];
    for (int i = 0; i < tot_env; i++) {
        cout << "Enter the envelope location of " << i + 1 << " envelope" << endl;
        cin >> env[i].env_loc;
        cout << "Enter the delivery location of " << i + 1 << " envelope" << endl;
        cin >> env[i].del_loc;
    }

    for (int i = 0; i < tot_env; i++) {
        del_dist[i] = INF;
    }

    func(dri_loc, env, del_dist, env_dist, tot_env);

    return 0;
}
