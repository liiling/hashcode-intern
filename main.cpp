#include "header.h"

// latency: send video to endpoint e
int L(Problem& problem, Solution& solution, int video, int e) {
    Endpoint& endpoint = problem.endpoints[e];
    int min_latency = endpoint.L_d;
    for (auto& connection : endpoint.connected_caches) {
        int cache = connection.first, latency = connection.second;
        if (solution.caches[cache].cached_videos.count(video)) {
            min_latency = min(min_latency, latency);
        }
    }
    return min_latency;
}

// Add video to cache
long long improvement(Problem& problem, Solution& solution, int video, int cache) {
    long long score_increase = 0;
    for (pair<int, int> request : problem.videos[video].requests_from_endpoint) {
        int n = request.second;
        int e = request.first;
        Endpoint& endpoint = problem.endpoints[e];
        if (!endpoint.connected_caches.count(cache)) {
            continue;
        }

        int current_latency = L(problem, solution, video, e);
        int new_latency = min(current_latency, endpoint.connected_caches[cache]);
        score_increase += (current_latency - new_latency)*n;
    }
    return score_increase;
}

int main() {
    Problem problem = read_problem(cin);
    Solution solution(problem);


    print(cout, solution);
    return 0;
}
