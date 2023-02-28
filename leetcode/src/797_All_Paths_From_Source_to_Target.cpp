#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

// 797_All_Paths_From_Source_to_Target

// https://leetcode.com/problems/all-paths-from-source-to-target/description/4

// directed asyclic graph 에서 node 0 에서 node n-1 까지 가는 경로를 모두 리턴하라.

// REMEMBER
// 시간되면 다시 풀어봐. 좋은 문제.
//
// corner case들을 생각해봐라. 예를 들어.....
// - 만일 terminal node가 n-1 이 아니라면?

class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph)
    {
        // return method_backtracking(graph);
        return method_dp(graph);
    }

private:
    // REMEMBER 다시 한번 눈여겨 볼 것.
    vector<vector<int>> method_backtracking(vector<vector<int>>& graph)
    {
        vector<int> path{0};
        vector<vector<int>> result;

        backtrack(graph, 0, path, result);

        return result;
    }

    void backtrack(vector<vector<int>>& graph, int node, vector<int>& path, vector<vector<int>>& result)
    {
        if (node == graph.size() - 1)
        {
            result.emplace_back(path);
            return;
        }

        for (int k = 0; k < graph[node].size(); k++)
        {
            path.emplace_back(graph[node][k]);
            backtrack(graph, graph[node][k], path, result);
            path.pop_back();
        }
    }

private:
    vector<vector<int>> method_dp(vector<vector<int>>& graph)
    {
        int target = int(graph.size()) - 1;
        map<int, vector<vector<int>>> memo;

        map<int, vector<vector<int>>> m;

        return paths_to_target(graph, 0, graph.size() - 1, m);
    }


    vector<vector<int>> paths_to_target(vector<vector<int>>& graph, int node, int target, map<int, vector<vector<int>>> &m)
    {
        auto found = m.find(node);
        if (found != m.end())
            return found->second;

        if (node == target)
        {
            return m[target] = {{target}};
        }

        vector<vector<int>> result;

        for (int next_node: graph[node])
        {
            auto &&vv = paths_to_target(graph, next_node, target, m);
            std::for_each(
                vv.begin(), vv.end(),
                [node, &result](vector<int> &v) {
                    v.insert(v.begin(), node);
                    result.emplace_back(v);
            });
        }

        return result;
    };

};
