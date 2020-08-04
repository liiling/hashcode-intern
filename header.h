#include <bits/stdc++.h>
using namespace std;

struct Endpoint {
    int L_d, K;
    map<int, int> connected_caches; // cache_server -> latency
};

struct Request {
    int R_v, R_e, R_n;
};

struct Video {
    int size;
    map<int, int> requests_from_endpoint; // endpoint -> #requests
};

struct Problem {
    int V, E, R, C, X;
    vector<Video> videos;
    vector<Endpoint> endpoints;
    vector<Request> requests;
};

Problem read_problem(istream& s) {
    Problem problem;
    s >> problem.V >> problem.E >> problem.R >> problem.C >> problem.X;
    problem.videos.resize(problem.V);
    for (Video& video : problem.videos) {
        s >> video.size;
    }
    problem.endpoints.resize(problem.E);
    for (Endpoint& endpoint : problem.endpoints) {
        s >> endpoint.L_d >> endpoint.K;
        for (int i = 0; i < endpoint.K; i++) {
            int cache, latency;
            s >> cache >> latency;
            endpoint.connected_caches[cache] = latency;
        }
    }
    problem.requests.resize(problem.R);
    for (Request& request : problem.requests) {
        s >> request.R_v >> request.R_e >> request.R_n;
        problem.videos[request.R_v].requests_from_endpoint[request.R_e] += request.R_n;
    }
    return problem;
}

struct Cache {
    int remaining;
    set<int> cached_videos;
};

struct Solution {
    vector<Cache> caches;
    Solution(Problem& problem){
        caches.resize(problem.C);
        for (Cache& cache : caches) {
            cache.remaining = problem.X;
        }
    }
};

void print(ostream& o, Solution& solution) {
    o << solution.caches.size() << endl;
    for (int i = 0; i < (int)solution.caches.size(); i++) {
        o << i;
        for (int video : solution.caches[i].cached_videos) {
            o << " " << video;
        }
        o << endl;
    }
}

int score(Problem& problem, Solution& solution) {
    return 0;
}