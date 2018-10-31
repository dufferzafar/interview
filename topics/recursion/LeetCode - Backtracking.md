
# LeetCode - Backtracking

https://leetcode.com/tag/backtracking/

## 257. Binary Tree Paths

Given a binary tree, return all root-to-leaf paths. 

https://leetcode.com/problems/binary-tree-paths/

```cpp
typedef vector<string> vs;

class Solution {
public:
    
    void rtlp(TreeNode* root, string path, vs& all) {
        
        if (!root) return;
        
    // Choose:
        // This creates as many string objects as the height of the tree
        // Things would become tricky if we were to pass path by reference!
        string npath;
        
        if (path.empty())
            npath = to_string(root->val);
        else
            npath = path + "->" + to_string(root->val);
        
        // At the leaf!
        if(!root->left && !root->right) {
            all.push_back(npath);
            return;
        }
        
    // Explore:
        if (root->left) rtlp(root->left, npath, all);
        if (root->right) rtlp(root->right, npath, all);
        
    // Unchoose:
        // Happens automatically when the stack unwinds?
        
    }
    
    vs binaryTreePaths(TreeNode* root) {
        vs all;
        rtlp(root, "", all);
        return all;
    }
};
```
## 46. Permutations

https://leetcode.com/problems/permutations/

Given a collection of distinct integers, return all possible permutations.

**Using vector to build a permutation**:

```cpp
typedef vector<int> vi;
typedef vector<vi> vvi;

class Solution {
public:
    
    void permutations(vi& nums, vi& perm, vvi& all) 
    {
        if (nums.empty()) {
            if (!perm.empty()) 
                all.push_back(perm);
            return;
        }
        
        // For all choices
        for(int i = 0; i < (int) nums.size(); ++i) {
            
            int n = nums[i];
            auto idx = nums.begin() + i;
            
            // Choose
            perm.push_back(n);
            nums.erase(idx);
            
            // Explore
            permutations(nums, perm, all);
            
            // Unchoose
            nums.insert(idx, n);
            perm.pop_back();
        }

    }
    
    vvi permute(vi& nums) {
        vvi all; vi perm;
        perms(nums, perm, all);
        return all;
    }
};
```

**Using Swaps - more efficient?**:

```cpp
typedef vector<int> vi;
typedef vector<vi> vvi;

class Solution {
public:
    
    void permutations(vi& nums, int start, vvi& all) 
    {
        if (start == (int) nums.size()) {
            all.push_back(nums);
            return;
        }
        
        // For all choices:
        for(int i = start; i < (int) nums.size(); ++i) 
        {
            // Choose :
            swap(nums[i], nums[start]);
        
            // Explore :
            permutations(nums, start + 1, all);
        
            // Unchoose:
            swap(nums[i], nums[start]);            
        }
    }
    
    vvi permute(vi& nums) {
        vvi all; 
        perms(nums, 0, all);
        return all;
    }
};
```
