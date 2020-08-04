#include "header.h"


long long L(Problem& problem, Solution& solution, int video, int e) {
    Endpoint& endpoint = problem.endpoints[e];
    int requests = problem.videos[video].requests_from_endpoint[e];
    int min_latency = endpoint.L_d;
    for (auto& connection : endpoint.connections) {
        int cache = connection.first, latency = connection.second;
        if (solution.caches[cache].cached_videos.count(video)) {
            min_latency = min(min_latency, latency);
        }
    }
    return min_latency * (long long)requests;
}

// Add video to cache
int improvement(Problem& problem, Solution& solution, int video, int cache) {
    for (pair<int, int> request : problem.videos[video].requests_from_endpoint) {
        int endpoint = request.first, n = request.second;

    }
}

int main() {
    Problem problem = read_problem(cin);
    Solution solution(problem);


    print(cout, solution);
    return 0;
}
