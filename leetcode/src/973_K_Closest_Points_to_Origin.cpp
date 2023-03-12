// 973_K_Closest_Points_to_Origin

// https://leetcode.com/problems/k-closest-points-to-origin/description/

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k)
    {
        // return method_nlogn(points, k);
        return method_nlogk(points, k);
    }

private:
    vector<vector<int>> method_nlogn(vector<vector<int>>& points, int k)
    {
        auto compare = [](vector<int> &a, vector<int> &b) {
            return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
        };

        std::sort(points.begin(), points.end(), compare);

        return vector<vector<int>>(points.begin(), points.begin() + k);
    }

    vector<vector<int>> method_nlogk(vector<vector<int>>& points, int k)
    {
        // maintain minheap of size k
        auto compare = [](const vector<int> &a, const vector<int> &b) {
            return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
        };

        // REMEMBER
        //      make_heap을 쓰고 pop_heap()의 전/후의 ans.size()는 동일하다.
        //      pop_heap()는 head 를 tail 에 위치시켜버림...
        //      그래서 heap의 사이즈를 알기가 좀 애매하다.
        //      따라서, make_heap 말고 priority _queue를 쓰는게 나을 듯.
        /*
        vector<vector<int>> ans;
        make_heap(ans.begin(), ans.end(), compare);

        // maintain ans of size k
        for (auto &point : points)
        {
            // place new item at the end
            ans.emplace_back(point);
            // heapify
            push_heap(ans.begin(), ans.end(), compare);

            if (ans.size() > k)
                pop_heap(ans.begin(), ans.end(), compare);   // ans.front()를 삭제후 heapify
            // Note: 제일 큰 값을 가져오려면
            // ans.front() 를 보면 됨.
        }

        return ans;
        */

        // REMEMBER
        //   priority_queue declaration
        priority_queue<vector<int>, vector<vector<int>>, decltype(compare)> pq(compare);

        for (auto &point: points)
        {
            pq.push(point);

            if (pq.size() > k)
                pq.pop();
        }

        vector<vector<int>> ans;
        while(!pq.empty())
        {
            auto point = pq.top();
            pq.pop();
            ans.emplace_back(point);
        }

        return ans;
    }
};
