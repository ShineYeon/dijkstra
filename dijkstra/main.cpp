
#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <string>
using namespace std;

#define INF 1000000
#define MAXDIST 1000000 //√‚πﬂ¡ˆø°º≠ ∏Ò¿˚¡ˆ±Ó¡ˆ¿« ∞≈∏Æ∞° MAXDIST∏¶ √ ∞˙«œ∏È √‚πﬂ¡ˆø°º≠ ∏Ò¿˚¡ˆ±Ó¡ˆ ∞• ºˆ æ¯¥Ÿ∞Ì ∞°¡§
#define MAXNODE 100001  //√÷¥Î ≥ÎµÂ¿« ∞≥ºˆ
#define MAXID 900000    //¡ˆø™π¯»£
#define DEBUG 1
#define KEYOFFSET 100000

//≈∞∏¶ ¿˙¿Â«œ¥¬ µ•¿Ã≈Õ∏¶ ∏∏µÈæÓ≥ˆæﬂ«—¥Ÿ.
int indexlist[MAXID];

// function prototypes
void printAdjlist(vector<pair<int, int>>*, int);


class Compare {
public:
    bool operator()(pair<int, int> a, pair<int, int> b) {
        if (a.second == b.second)
            return a.first > b.first;
        return a.second > b.second;
    }
};

// Declare and define structs
typedef struct _region {
    int regionID;       // 100,000~999,999 ªÁ¿Ã¿« ¡§ºˆ
    string regionName;  // ∞¯πÈ¿Ã æ¯¥¬ 20Byte ¿Ã≥ª¿« πÆ¿⁄ø≠
    int isFlood;   // ƒßºˆ ø©∫Œ 1¿Œ ∞ÊøÏ ƒßºˆ, 0¿Œ ∞ÊøÏ ƒßºˆµ«¡ˆ æ ¿Ω.
    _region() {}
    void set(int id, string n, int f) {
        regionID = id;
        regionName = n;
        isFlood = f;
    }
    void print() {
        cout << regionID << " " << regionName << " " << isFlood << "\n";
        //printf("%d %s %d\n", regionID, regionName, isFlood);
    }
}region;



int dijkstra(vector<pair<int, int>>* adjlist, int start, int end, int n, int* dist, region* regions) {
    int i, cnt;
    fill_n(dist, n+1, MAXDIST);
    dist[indexlist[start - KEYOFFSET]] = 0; // define d(s,s)=0
    cnt = 1;
    bool countingFlag = true;    //≥°±Ó¡ˆ ∞¨¥¬¡ˆ ∞ÀªÁ«œ¥¬ «√∑°±◊
    bool* finished = new bool[n+1];
    fill_n(finished, n + 1, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

    pq.push(make_pair(start, 0));
    
    while (!pq.empty()) { //while there are fringe vertices

        //Select an edge between a tree vertex t and a fringe vertex v such that
        //d(s, t) + W(tv) is minimum
        int current = pq.top().first;
        int distance = pq.top().second;
        pq.pop();

        if (finished[indexlist[current - KEYOFFSET]] == true)
            continue;
        
        finished[indexlist[current - KEYOFFSET]] = true;

        if (current == end) {
            countingFlag = false;
        }
        if (countingFlag)
            cnt++;
        if (dist[indexlist[current - KEYOFFSET]] < distance)
            continue;
        for (i = 0; i < adjlist[indexlist[current - KEYOFFSET]].size(); i++) {
            int next = adjlist[indexlist[current - KEYOFFSET]][i].first;
            int nextdistance = adjlist[indexlist[current - KEYOFFSET]][i].second + distance;

            if (regions[indexlist[next - KEYOFFSET]].isFlood == 1) continue;

            if (nextdistance < dist[indexlist[next - KEYOFFSET]]) {
                dist[indexlist[next - KEYOFFSET]] = nextdistance;
                pq.push(make_pair(next, nextdistance));
            }
        }
    }
    delete[] finished;
    return cnt;  //µµ¬¯¡ˆ¡° tree vertexµµ »Æ¿Œ
}

void dijkstra2(vector<pair<int, int>>* adjlist, int start, int end, int n, int* dist, region* regions) {

    int i, cnt;
    fill_n(dist, n+1, MAXDIST);
    dist[indexlist[start - KEYOFFSET]] = 0; // define d(s,s)=0
    cnt = 1; bool countingFlag = true;
    bool* finished= new bool[n+1];
    fill_n(finished, n + 1, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

    int* route = new int[n + 1];
    fill_n(route, n + 1, 0);
    
    pq.push(make_pair(start, 0));
    while (!pq.empty()) { //while there are fringe vertices
        int current = pq.top().first;
        int distance = pq.top().second;
        pq.pop();

        if (finished[indexlist[current - KEYOFFSET]] == true)
            continue;
        finished[indexlist[current - KEYOFFSET]] = true;

        if (current == end)
            countingFlag = false;
        if (countingFlag)
            cnt++;

        for (i = 0; i < adjlist[indexlist[current - KEYOFFSET]].size(); i++) {
            int next = adjlist[indexlist[current - KEYOFFSET]][i].first;
            int nextdistance = adjlist[indexlist[current - KEYOFFSET]][i].second + distance;

            if (regions[indexlist[next - KEYOFFSET]].isFlood == 1) continue;

            if (nextdistance < dist[indexlist[next - KEYOFFSET]]) {
                route[indexlist[next - KEYOFFSET]] = current - KEYOFFSET;
                dist[indexlist[next - KEYOFFSET]] = nextdistance;
                pq.push(make_pair(next, nextdistance));
            }
        }
    }

    
    printf("%d ", cnt);

    vector<int> print;
    int idx = end - KEYOFFSET;
    while (idx>0) {
        print.push_back(idx);
        idx = route[indexlist[idx]];
    }
    for (int i = print.size() - 1; i >= 0; i--) {
        printf("%d ", print[i] + KEYOFFSET);
    }
    printf("\n");
    delete[] finished;

}


/// <summary>
/// ¥Ÿ¿ÕΩ∫∆Æ∂Û æÀ∞Ì∏Æ¡Ú, æÁπÊ¡h ∞°¡ﬂƒ° ±◊∑°«¡
/// ¿Œ¡¢∏ÆΩ∫∆Æ±‚π›
/// </summary>
/// <returns></returns>
int main() {
    int n; int m; int q; // n : ¡ˆø™¡§∫∏¿« ºˆ, m : µµ∑Œ¡§∫∏¿« ºˆ, q : ¡˙¿«¿« ºˆ
    int i;//iterator ∫Øºˆ
    cin >> n >> m >> q;
    //int** adjmat = new int* [n];
    vector<pair<int, int>>* adjlist;
    region* regions = new region[n+1];
    int* dist = new int[n+1];

    int regionID1; int regionID2;  int isFlood; int distance;
    char query;
    char regionName[20];

    adjlist = new vector<pair<int, int>>[n];
    for (i = 0; i < n; i++) {
        //¡ˆø™¡§∫∏ ¿‘∑¬πﬁ±‚
        //¡ˆø™π¯»£ ¡ˆø™¿Ã∏ß ƒßºˆø©∫Œ º¯º≠¥Î∑Œ ¿‘∑¬
        scanf("%d %s %d", &regionID1, regionName, &isFlood);
        //cin >> regionID1 >> regionName >> isFlood;
        regions[i].set(regionID1, regionName, isFlood);
        indexlist[regionID1 - KEYOFFSET] = i;
        //cout << regions[i].regionID << regions[i].regionName << regions[i].isFlood << "\n";
        fflush(stdin);

    }


    for (i = 0; i < m; i++) {
        //µµ∑Œ¡§∫∏ ¿‘∑¬πﬁ±‚
        //¡ˆø™π¯»£1 ¡ˆø™π¯»£2 µµ∑Œ¿«∞≈∏Æ
        scanf("%d %d %d", &regionID1, &regionID2, &distance);
        adjlist[indexlist[regionID1 - KEYOFFSET]].push_back(make_pair(regionID2, distance));
        adjlist[indexlist[regionID2 - KEYOFFSET]].push_back(make_pair(regionID1, distance));

        //        cout << indexlist[regionID1 - KEYOFFSET] << " " << indexlist[regionID2 - KEYOFFSET] << "\n";
        fflush(stdin);
    }


    //Query ¿‘∑¬ πﬁ±‚
    int tree_cnt = 0;
    for (i = 0; i < q; i++) {
        scanf(" %c %d %d", &query, &regionID1, &regionID2);
        //Dijkstra(adjlist, regionID1, regionID2, n, vertex, dist, regions);
        if (query == 'A') {
            if (regions[indexlist[regionID1 - KEYOFFSET]].isFlood == 1 || regions[indexlist[regionID2 - KEYOFFSET]].isFlood == 1) {
                printf("None\n"); //√‚πﬂ¡ˆ≥™ µµ¬¯¡ˆ∞° ƒßºˆµ» ∞ÊøÏ
                continue;
            }
            else {
                tree_cnt = dijkstra(adjlist, regionID1, regionID2, n, dist, regions);
                if (dist[indexlist[regionID2 - KEYOFFSET]] == MAXDIST) {
                    printf("None\n");
                    continue;
                }

                cout << tree_cnt << " " << dist[indexlist[regionID2 - KEYOFFSET]] << " " << regions[indexlist[regionID1 - KEYOFFSET]].regionName << " " << regions[indexlist[regionID2 - KEYOFFSET]].regionName << "\n";
                //printf("%d %d %s %s\n", tree_cnt,
                //    dist[indexlist[regionID2 - KEYOFFSET]],
                //    regions[indexlist[regionID1-KEYOFFSET]].regionName,
                //    regions[indexlist[regionID2-KEYOFFSET]].regionName);

                /*
                ∞Ê∑Œ √£¥¬ πÆ¡¶¥¬ ø™¿∏∑Œ ∞Ê∑Œ √£±‚«œ∏È µ»¥Ÿ.
                */
            }
        }
        else if (query == 'B') {
            if (regions[indexlist[regionID1 - KEYOFFSET]].isFlood == 1 || regions[indexlist[regionID2 - KEYOFFSET]].isFlood == 1) {
                printf("None\n"); //√‚πﬂ¡ˆ≥™ µµ¬¯¡ˆ∞° ƒßºˆµ» ∞ÊøÏ
                continue;
            }
            else {
                tree_cnt = dijkstra(adjlist, regionID1, regionID2, n, dist, regions);
                if (dist[indexlist[regionID2 - KEYOFFSET]] == MAXDIST) {
                    printf("None\n");
                    continue;
                }
                dijkstra2(adjlist, regionID1, regionID2, n, dist, regions);
                
                //printf("%d %d %s %s\n", tree_cnt,
                //    dist[indexlist[regionID2 - KEYOFFSET]],
                //    regions[indexlist[regionID1-KEYOFFSET]].regionName,
                //    regions[indexlist[regionID2-KEYOFFSET]].regionName);

                /*
                ∞Ê∑Œ √£¥¬ πÆ¡¶¥¬ ø™¿∏∑Œ ∞Ê∑Œ √£±‚«œ∏È µ»¥Ÿ.
                */
            }
        }
    }
    delete[] regions;
    delete[] dist;
    delete[] adjlist;
    return 0;
}


void printAdjlist(vector<pair<int, int>>* adjlist, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < adjlist[i].size(); j++) {
            cout << adjlist[i][j].first << " " << adjlist[i][j].second << " | ";
        }
        cout << "\n";
    }
}
