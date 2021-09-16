#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct edge {       //dois pontos e peso/custo
    int a;
    int b;
    int w;
};

bool comp(edge a, edge b) {     //comparar o custo de duas arestas
    if (a.w < b.w)
        return true;

    return false;
}

class mst {     //arvore de abrangencia minima
public:
    int n, a, b;
    int* par;

    vector<edge> ar;            //conjunto das arestas

    mst(int sz) {               //inicialização
        n = sz;

        par = new int[n + 1];

        for (int i = 0; i <= n; i++)
            par[i] = -1;
    }

    int find(int a) {                   //
        if (par[a] == -1) return a;

        return par[a] = find(par[a]);
    }

    void merge(int a, int b) {      //guardar na posiçao a de par o valor b
        par[a] = b;
    }

    int cal() {                 //Algoritmo de Kruskal
        int sum = 0;
        int m = ar.size();

        sort(ar.begin(), ar.end(), comp);       //organiza as edges pelo seu custo por causa do algoritmo de Kruskal

        for (int i = 0; i < m; i++) {
            a = find(ar[i].a);                  //encontra e atribui os nodes da aresta
            b = find(ar[i].b);

            if (a != b) {               //verificação de nao serem o mesmo node
                sum += ar[i].w;         //adiciona a soma o custo do caminho entre os dois/da aresta
                merge(a, b);
            }
        }

        return sum;
    }
};

class circuit {
public:
    vector<vector<int>> v;
    int mx, total, q3, q4;

    vector<int> order, SCC;
    vector<vector<int>> ar, tr;
    vector<vector<pair<int, int>>> adj;     //matriz de adjacencias
    int n, m, q;
    int* vis;                       //marca se o node ja foi visitado ou não

    circuit(int sz) {
        mx = 0;             //número de poi's do maior circuito
        total = 0;          //numero de circuitos
        q3 = 0;             //tamanho da maior via
        q4 = 0;             //tamanho total das vias
        n = sz;

        vector<int> temp;                       //inicializar os vetores
        for (int i = 0; i <= n; i++)
            ar.push_back(temp), tr.push_back(temp);

        vector<pair<int, int>> temp2;

        for (int i = 0; i <= n; i++)
            adj.push_back(temp2);

        vis = new int[n + 1];

        for (int i = 0; i <= n; i++)
            vis[i] = 0;
    }

    void input() {                      //preencher os vetores com os inputs
        cin >> m >> q;
        for (int i = 0; i < m; i++) {
            int x, y, w;
            cin >> x >> y >> w;
            adj[x].push_back(make_pair(y, w));
            ar[x].push_back(y);
            tr[y].push_back(x);

        }
    }

    void dfs(int node) {                //procura em profundidade primeiro
        vis[node] = 1;

        for (int child : ar[node]) {           //vai buscar os nodes em ar[node] e verifica se ja foram visitados, caso nao, faz a procura em profundidade nesse
            if (vis[child] == 0)
                dfs(child);
        }

        order.push_back(node);              //adiciona o node a order
    }

    void dfs1(int node) {                   //procura em profundidade igual a de cima mas adiciona os nodes a um SCC
        vis[node] = 1;

        for (int child : tr[node])
            if (vis[child] == 0)
                dfs1(child);

        SCC.push_back(node);
    }
    //Parte do Kosaraju, com as DFS em cima
    void scc() {                            //construir SCC's  (componentes fortemente ligados) 
        for (int i = 1; i <= n; i++)        //faz dfs em todos os nodes nao visitados
            if (vis[i] == 0) dfs(i);

        for (int i = 1; i <= n; i++)        //marca todos os nodes como nao visitados
            vis[i] = 0;

        for (int i = 1; i < n; i++) {
            if (vis[order[n - i]] == 0) {   //se o node atual nao tiver sido visitado
                SCC.clear();                //limpa o stack para os SCC, para se puder começar um novo

                dfs1(order[n - i]);         //faz a procura em profundidade para determinar o SCC

                if (SCC.size() > 1) {       //verifica se SCC é valido, e nesse caso adiciona a lista de SCC
                    total++;
                    mx = max(mx, (int)SCC.size());
                    v.push_back(SCC);
                }
            }
        }
    }
    //Parte de Kruskal
    void buildmst() {                       //fazer a Minimum Spanning Tree (árvore de abrangencia minima)
        for (int i = 0; i < total; i++) {   //só faz o numero de vezes igual ao numero de circuitos
            int siz = v[i].size();          //vai buscar o tamanho/numero de nodes do circuito atual
            unordered_map<int, int> s;      //se pertencem ao mesmo scc(?)
            mst obj(siz);                   //var obj do tipo mst que usa o tamanho do SCC como argumento

            for (int j = 0; j < siz; j++)   //
                s[v[i][j]] = j + 1;

            for (int j = 0; j < siz; j++) { //para cada node do circuito atual
                int node = v[i][j];
                for (auto x : adj[node])                //prepara as arestas para o algoritmo de Kruskal
                    if (s.find(x.first) != s.end()) {
                        edge e;
                        e.a = s[node];
                        e.b = s[x.first];
                        e.w = x.second;
                        obj.ar.push_back(e);

                    }
            }
            int ans = obj.cal();        //Chama algoritmo de Kruskal e calcula os valores para questões 3 e 4
            q3 = max(q3, ans);
            q4 += ans;
        }
    }
};

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        circuit c(n);
        c.input();              //guardar o grafo
        c.scc();                //calcular as melhores ciclovias

        if (c.q == 1)                           //input de quantos dados são pedidos na resposta
            cout << c.total << endl;
        if (c.q == 2)
            cout << c.total << " " << c.mx << endl;
        if (c.q == 3) {
            c.buildmst();                   //fazer a arvore de abrangencia minima
            cout << c.total << " " << c.mx << " " << c.q3 << endl;
        }
        if (c.q == 4) {
            c.buildmst();
            cout << c.total << " " << c.mx << " " << c.q3 << " " << c.q4 << endl;
        }
    }
}