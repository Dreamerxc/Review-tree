## 要求
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

## 代码
- 递归

-

	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root||root==p||root==q) return root;
        TreeNode *first = lowestCommonAncestor(root->left,p,q);
        TreeNode *second = lowestCommonAncestor(root->right,p,q);
        if(first&&second) return root;  //如果first和second都找到了，就可以返回根节点。
        return first?first:second;  //如果first找到了就赋给second。
    }


## 总结
- 递归时先从当前头节点递归，找到两个节点位置，保存到first和second.如果first和second都不为空，则返回根节点。