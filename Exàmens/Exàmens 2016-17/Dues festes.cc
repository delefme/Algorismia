#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int p; // Nombre de persones
int m; // Nombre de relacions d'enemistat
map<string, int> id; // Relacio persona <-> nombre
vector<string> persones; // Persones en ordre
vector<vector<int>> arestes; // Relacions d'enemistat
vector<bool> pintat; // Si una persona ha estat pintada
vector<int> dist; // Distancia respecte algun node

bool bipartit(int i) {
  queue<int> Q;
  dist[i] = 0;
  Q.push(i);

  while (!Q.empty()) {
    int j = Q.front(); Q.pop();

    for (auto &v : arestes[j]) {
      if (dist[v] == -1) {
        dist[v] = dist[j] + 1;
        pintat[v] = !pintat[j];
        Q.push(v);
      } else {
        if (pintat[j] == pintat[v])
          return false;
      }
    }
  }

  return true;
}

int main() {
  while (cin >> p) {
    persones = vector<string>(p);
    for (int i = 0; i < p; ++i) {
      cin >> persones[i];
      id[persones[i]] = i;
    }

    cin >> m;
    arestes = vector<vector<int>>(p);
    for (int i = 0; i < m; ++i) {
      string ps1, ps2;
      cin >> ps1 >> ps2;

      int p1 = id[ps1];
      int p2 = id[ps2];
      arestes[p1].push_back(p2);
      arestes[p2].push_back(p1);
    }

    pintat = vector<bool>(p);
    dist = vector<int>(p, -1);

    bool espotfer = true;
    for (int i = 0; i < p; ++i) {
      if (dist[i] == -1) { // Si no ha estat visitat
        if (!bipartit(i)) { // comprovem si el seu subgraf es bipartit.
          espotfer = false; // Si no ho es, p calle!
          break;
        }
      }
    }

    if (espotfer) {
      cout << "SI";
      for (int i = 0; i < p; ++i)
        if (pintat[i])
          cout << " " << persones[i];
      cout << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
