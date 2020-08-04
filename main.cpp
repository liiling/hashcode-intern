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
    
    // (improvement, (cache, video))
    // Find cache location that give shighest improvement.
    priority_queue<pair<int, pair<int, int>>> q;
    for (int c = 0; c < problem.C; ++c) {
        for (int v = 0; v < problem.V; ++v) {
            int benefit = improvement(problem, solution, v, c);
            q.push({benefit, {c, v}});
        }
    }

    while (!q.empty()) {
        auto d = q.top();
        q.pop();
        int benefit = d.first;
        int c = d.second.first;
        int v = d.second.second;
        // Does it fit and not already exist?
        auto& cache = solution.caches[c];
        auto& video = problem.videos[v];
        if (video.size <= cache.remaining && !cache.cached_videos.count(v)) {
            cache.remaining -= video.size;
            cache.cached_videos.insert(v);
        }
    }

    print(cout, solution);
    return 0;
}
