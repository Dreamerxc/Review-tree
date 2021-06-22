## 翻转二叉树
- 采用递归法

-

	TreeNode* invertTree(TreeNode* root) {
        if(root==nullptr) return root;
        TreeNode *l = invertTree(root->right);
        TreeNode *r = invertTree(root->left);
        root->left = l;
        root->right = r;
        return root;
    }

- 采用队列层次遍历

-

	TreeNode* invertTree(TreeNode* root) {
        if(root==nullptr) return nullptr;
        queue<TreeNode*> que;
        que.push(root);
        TreeNode *cur,*p;
        while(!que.empty())
        {
            cur = que.front();
            que.pop();
            p = cur->left;
            cur->left = cur->right;
            cur->right = p;
            if(cur->left!=nullptr) que.push(cur->left);
            if(cur->right!=nullptr) que.push(cur->right);
        }
        return root;
	}

## 总结
- 采用队列来层次遍历是利用队列先进先出的特点，将叶子节点保存进队列中，避免交换后顺序不一样。