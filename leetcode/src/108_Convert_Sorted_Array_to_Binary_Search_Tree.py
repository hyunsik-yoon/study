"""
108. Convert Sorted Array to Binary Search Tree

https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/

make an array of int in ascending order into height-balanced BST,
where height-balanced BST is a binary tree in which the depth of the two subtrees of
every node never differs by more than one.
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def sortedArrayToBST(self, nums: List[int]) -> Optional[TreeNode]:

        # REMEMBER
        #   python slicing is slow
        #   With nums[10:100], this actually copies number from 10 to 99 (end is exclusive)

        print(nums)

        if len(nums) == 0:
            return None

        if len(nums) == 1:
            return TreeNode(nums[0])

        mid = len(nums) // 2

        root = TreeNode(nums[mid])

        if mid < 0:
            root.left = None
        else:
            root.left = self.sortedArrayToBST(nums[:mid])

        if mid + 1 >= len(nums):
            root.right = None
        else:
            root.right = self.sortedArrayToBST(nums[mid+1:])

        return root
